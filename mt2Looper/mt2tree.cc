#define mt2tree_cxx
#include "mt2tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void mt2tree::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L mt2tree.C
//      Root > mt2tree t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   // Creating Histograms
   TH1F *htH = new TH1F("ht", "ht", 100,0,3000);
   TH1F *met_ptH = new TH1F("met_pt", "met_pt", 100, 0, 2500);
   TH1F *mt2H = new TH1F("mt2", "mt2", 100, 0, 1500);
   TH1F *nJet30H = new TH1F("nJet30", "nJet30", 11, 0, 11);

   TH1F *ht_cutH = new TH1F("ht_cut", "ht", 100,0,3000);
   TH1F *met_pt_cutH = new TH1F("met_pt_cut", "met_pt", 100, 0, 2500);
   TH1F *mt2_cutH = new TH1F("mt2_cut", "mt2", 100, 0, 1500);
   TH1F *nJet30_cutH = new TH1F("nJet30_cut", "nJet30", 11, 0, 11);

   TH1F *genLep_ptH = new TH1F("genLep_pt", "genLep_pt", 100,0, 1200);
   TH1F *genTau_ptH = new TH1F("genTau_pt", "genTau_pt", 100, 0, 1200);
   TH1F *genGamma_ptH = new TH1F("genGamma_pt", "genGamma_pt", 100, 0, 250);
   TH1F *genStat23_ptH = new TH1F("genStat23_pt", "genStat23_pt", 100, 0, 2500);

   TH1F *genPart_ptH = new TH1F("genPart_ptH", "genPart_ptH", 100, 0, 2500);
   TH1F *genPart_etaH = new TH1F("genPart_etaH", "genPart_etaH", 100, -3000, 3000);
   TH1F *genPart_phiH = new TH1F("genPart_phiH", "genPart_phiH", 100, -4, 4);
   TH1F *genPart_massH = new TH1F("genPart_massH", "genPart_massH", 100, -100, 800);
   TH1F *genPart_pdgIdH = new TH1F("genPart_pdgIdH", "genPart_pdgIdH", 100, -1010, 1010);
   TH1F *genPart_statusH = new TH1F("genPart_statusH", "genPart_statusH", 100, 0, 90);
   TH1F *genPart_chargeH = new TH1F("genPart_chargeH", "genPart_chargeH", 100, -3, 3);
   TH1F *genPart_motherIdH = new TH1F("genPart_motherIdH", "genPart_motherIdH", 100, -1010, 1010);
   TH1F *genPart_grandmotherIdH = new TH1F("genPart_grandmotherIdH", "genPart_grandmotherIdH", 100, -50, 50);
   
   TH1F *Higgs_mass = new TH1F("Higgs_mass", "Higgs_mass", 100, 0, 200);
   TH1F *Higgs_pt = new TH1F("Higgs_pt", "Higgs_pt", 100, 0, 2500);
   TH1F *W_mass = new TH1F("W_mass", "W_mass", 100, 0, 1000);
   TH1F *W_pt = new TH1F("W_pt", "W_pt", 100, 0, 3000);
   TH1F *H_decays = new TH1F("H_decays", "pdgId H_decays", 100, -20, 20);
   TH1F *W_decays = new TH1F("W_decays", "pdgId W_decays", 100, -20, 20);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      /********************************************************************************************/
      /********************************************************************************************/
      //Alalysis Code
      double ht_tmp = ht;
      double met_pt_tmp = met_pt;
      double mt2_tmp = mt2;
      double nJet30_tmp = nJet30;

      if(!std::isnan(ht_tmp)) htH->Fill(ht);
      if(!std::isnan(met_pt_tmp)) met_ptH->Fill(met_pt);
      if(!std::isnan(mt2_tmp)) mt2H->Fill(mt2_tmp);
      if(!std::isnan(nJet30_tmp)) nJet30H->Fill(nJet30);

      // Applying cuts to data
      if((nMuons10==0 && nElectrons10==0 && nPFLep5LowMT == 0 && nPFHad10LowMT == 0) && // lepveto cut
	 (HLT_PFHT900 || HLT_PFJet450 || HLT_PFHT300_PFMET110 || HLT_PFMET120_PFMHT120 || HLT_PFMETNoMu120_PFMHTNoMu120) && // trigs cut
	 ((nVert > 0) && (nJet30 > 1) && (deltaPhiMin > 0.3) && (diffMetMht/met_pt < 0.5) && (mt2 > 200)
	  && ( (ht > 250 && met_pt > 250) || (ht > 1000 && met_pt > 30) )) && // srbase cut
	 (Flag_eeBadScFilter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_globalTightHalo2016Filter
	  && Flag_badMuonFilter && Flag_goodVertices && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_badChargedHadronFilter
	  && nJet30FailId == 0 && met_miniaodPt / met_caloPt < 5.0 && nJet200MuFrac50DphiMet == 0)) { // filters cut
	  // Fill the following Histograms
	  if(!std::isnan(ht_tmp)) ht_cutH->Fill(ht);
	  if(!std::isnan(met_pt_tmp)) met_pt_cutH->Fill(met_pt);
	  if(!std::isnan(mt2_tmp)) mt2_cutH->Fill(mt2_tmp);
	  if(!std::isnan(nJet30_tmp)) nJet30_cutH->Fill(nJet30);
      }

      for (unsigned int i=0; i<=ngenLep; i++) {if(!std::isnan(genLep_pt[i])) {genLep_ptH->Fill(genLep_pt[i]);}}
      for (unsigned int i=0; i<=ngenGamma; i++) {if(!std::isnan(genGamma_pt[i])) {genGamma_ptH->Fill(genGamma_pt[i]);}}
      for (unsigned int i=0; i<=ngenTau; i++) {if(!std::isnan(genTau_pt[i])) {genTau_ptH->Fill(genTau_pt[i]);}}
      for (unsigned int i=0; i<=ngenStat23; i++) {if(!std::isnan(genStat23_pt[i])) {genStat23_ptH->Fill(genStat23_pt[i]);}}
      
      for (unsigned int i=0; i<=ngenPart; i++) {
	if(!std::isnan(genPart_pt[i])) genPart_ptH->Fill(genPart_pt[i]);
	if(!std::isnan(genPart_eta[i])) genPart_etaH->Fill(genPart_eta[i]);
	if(!std::isnan(genPart_phi[i])) genPart_phiH->Fill(genPart_phi[i]);
	if(!std::isnan(genPart_mass[i])) genPart_massH->Fill(genPart_mass[i]);
	if(!std::isnan(genPart_pdgId[i])) genPart_pdgIdH->Fill(genPart_pdgId[i]);
	if(!std::isnan(genPart_status[i])) genPart_statusH->Fill(genPart_status[i]);
	if(!std::isnan(genPart_charge[i])) genPart_chargeH->Fill(genPart_charge[i]);
	if(!std::isnan(genPart_motherId[i])) genPart_motherIdH->Fill(genPart_motherId[i]);
	//if(!std::isnan(genPart_grandmotherId[i])) genPart_grandmotherIdH->Fill(genPart_grandmotherId[i]);
	if(!std::isnan(genPart_mass[i]) && genPart_pdgId[i]==25) Higgs_mass->Fill(genPart_mass[i]);
	if(!std::isnan(genPart_pt[i]) && genPart_pdgId[i]==25) Higgs_pt->Fill(genPart_pt[i]);
	if(!std::isnan(genPart_mass[i]) && genPart_pdgId[i]==24) W_mass->Fill(genPart_mass[i]);
	if(!std::isnan(genPart_pt[i]) && genPart_pdgId[i]==24) W_pt->Fill(genPart_pt[i]);
	if(!std::isnan(genPart_pdgId[i]) && genPart_motherId[i]==25) H_decays->Fill(genPart_pdgId[i]);
	if(!std::isnan(genPart_pdgId[i]) && genPart_motherId[i]==abs(24)) W_decays->Fill(genPart_pdgId[i]);
      }     

   }
   
   // Write histograms to root file
   TFile *f = new TFile("histograms.root", "RECREATE");
   if ( f->IsOpen() ) printf("File opened successfully\n");
   
   htH->Write("ht");
   met_ptH->Write("met_pt");
   mt2H->Write("mt2");
   nJet30H->Write("nJet30");
   ht_cutH->Write("ht_cut");
   met_pt_cutH->Write("met_pt_cut");
   mt2_cutH->Write("mt2_cut");
   nJet30_cutH->Write("nJet30_cut");
   genLep_ptH->Write("genLep_pt");
   genGamma_ptH->Write("genGamma_pt");
   genTau_ptH->Write("genTau_pt");
   genStat23_ptH->Write("genStat23_pt");
   genPart_ptH->Write("genPart_pt");
   genPart_etaH->Write("genPart_eta");
   genPart_massH->Write("genPart_mass");
   genPart_pdgIdH->Write("genPart_pdgId");
   genPart_statusH->Write("genPart_status");
   genPart_chargeH->Write("genPart_charge");
   genPart_motherIdH->Write("genPart_motherId");
   genPart_grandmotherIdH->Write("genPart_grandmotherId");
   Higgs_mass->Write("Higgs_mass");
   Higgs_pt->Write("Higgs_pt");
   W_mass->Write("W_mass");
   W_pt->Write("W_pt");
   H_decays->Write("H_decays");
   W_decays->Write("W_decays");
   
   f->Write();
   f->Close();
}
