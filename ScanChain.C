// -*- C++ -*-
// Usage:
// > root -b -q doAll.C

#include <iostream>
#include <vector>
#include <numeric>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveStats.h"

// CMS3
#include "CMS3.cc"

using namespace std;
using namespace tas;

int ScanChain(TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // Creating Histograms
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
 
  TH1F *ht = new TH1F("ht", "ht", 100,0,3000);
  TH1F *met_pt = new TH1F("met_pt", "met_pt", 100, 0, 2500);
  TH1F *mt2 = new TH1F("mt2", "mt2", 100, 0, 1500);
  TH1F *nJet30 = new TH1F("nJet30", "nJet30", 11, 0, 11);

  TH1F *ht_cut = new TH1F("ht_cut", "ht", 100,0,3000);
  TH1F *met_pt_cut = new TH1F("met_pt_cut", "met_pt", 100, 0, 2500);
  TH1F *mt2_cut = new TH1F("mt2_cut", "mt2", 100, 0, 1500);
  TH1F *nJet30_cut = new TH1F("nJet30_cut", "nJet30", 11, 0, 11);
  //ht->SetDirectory(rootdir);

  TH1F *genLep_pt = new TH1F("genLep_pt", "genLep_pt", 100,0, 1200);
  TH1F *genTau_pt = new TH1F("genTau_pt", "genTau_pt", 100, 0, 1200);
  TH1F *genGamma_pt = new TH1F("genGamma_pt", "genGamma_pt", 100, 0, 250);
  TH1F *genStat23_pt = new TH1F("genStat23_pt", "genStat23_pt", 100, 0, 2500);

  // Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if (nEvents >= 0) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile file(currentFile->GetTitle());
    TTree *tree = (TTree*)file.Get("mt2");
    if (fast) TTreeCache::SetLearnEntries(10);
    if (fast) tree->SetCacheSize(128*1024*1024);
    cms3.Init(tree);

    // Loop over Events in current file
    if (nEventsTotal >= nEventsChain) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for (unsigned int event = 0; event < nEventsTree; ++event) {

      // Get Event Content
      if (nEventsTotal >= nEventsChain) continue;
      if (fast) tree->LoadTree(event);
      cms3.GetEntry(event);
      ++nEventsTotal;

      // Progress
      CMS3::progress( nEventsTotal, nEventsChain );

      /********************************************************************************************/
      /********************************************************************************************/
      //Alalysis Code

      ht->Fill(cms3.ht());
      met_pt->Fill(cms3.met_pt());
      double mt2_tmp = cms3.mt2();
      if(!std::isnan(mt2_tmp)) mt2->Fill(mt2_tmp);
      nJet30->Fill(cms3.nJet30());

      // Applying cuts to data
      if((cms3.nMuons10()==0 && cms3.nElectrons10()==0 && cms3.nPFLep5LowMT() == 0 && cms3.nPFHad10LowMT() == 0) && // lepveto cut
	 (cms3.HLT_PFHT900() || cms3.HLT_PFJet450() || cms3.HLT_PFHT300_PFMET110() || cms3.HLT_PFMET120_PFMHT120() || cms3.HLT_PFMETNoMu120_PFMHTNoMu120()) && // trigs cut
	 ((cms3.nVert() > 0) && (cms3.nJet30() > 1) && (cms3.deltaPhiMin() > 0.3) && (cms3.diffMetMht()/cms3.met_pt() < 0.5) && (cms3.mt2() > 200)
	  && ( (cms3.ht() > 250 && cms3.met_pt() > 250) || (cms3.ht() > 1000 && cms3.met_pt() > 30) )) && // srbase cut
	 (cms3.Flag_eeBadScFilter() && cms3.Flag_HBHENoiseFilter() && cms3.Flag_HBHENoiseIsoFilter() && cms3.Flag_globalTightHalo2016Filter()
	  && cms3.Flag_badMuonFilter() && cms3.Flag_goodVertices() && cms3.Flag_EcalDeadCellTriggerPrimitiveFilter() && cms3.Flag_badChargedHadronFilter()
	  && cms3.nJet30FailId() == 0 && cms3.met_miniaodPt() / cms3.met_caloPt() < 5.0 && cms3.nJet200MuFrac50DphiMet() == 0)) { // filters cut
	      // Fill the following Histograms
	      ht_cut->Fill(cms3.ht());
	      met_pt_cut->Fill(cms3.met_pt());
	      if(!std::isnan(mt2_tmp)) mt2_cut->Fill(mt2_tmp);
	      nJet30_cut->Fill(cms3.nJet30());
      }

      genLep_pt->Fill(cms3.genLep_pt());
      genTau_pt->Fill(cms3.genTau_pt());
      //if (cms3.ngenGamma()==1) genGamma_pt->Fill(cms3.genGamma_pt());
      //genStat23_pt->Fill(cms3.genStat23_pt());
      //cout << cms3.ngenGamma() << endl;

    }
      
    // Clean Up
    delete tree;
    file.Close();
  }
  if (nEventsChain != nEventsTotal) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }

  // Write histograms to root file
  TFile *f = new TFile("histograms.root", "NEW");
  if ( f->IsOpen() ) printf("File opened successfully\n");
  ht->Write("ht");
  met_pt->Write("met_pt");
  mt2->Write("mt2");
  nJet30->Write("nJet30");
  ht_cut->Write("ht_cut");
  met_pt_cut->Write("met_pt_cut");
  mt2_cut->Write("mt2_cut");
  nJet30_cut->Write("nJet30_cut");
  f->Write();
  f->Close();
  
  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time: " << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time: " << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return 0;
}
