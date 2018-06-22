/* C++
 * Author: Jack Schrott (fnal)
 * Date: 06/20/2018
 ****************************
 * Plots histograms saved in histograms.root file.
 */

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
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveStats.h"

using namespace std;

int Plot() {

  // Loading root file
  TFile *f = new TFile("histograms.root");
  if ( f->IsOpen() ) printf("File opened successfully\n");
    
  // Creating canvases
  //TCanvas *c_1 = new TCanvas("c_1", "Plots", 200, 200, 800, 700);
  //TCanvas *c_2 = new TCanvas("c_2", "genPlots1", 200, 200, 800, 700);
  //TCanvas *c_3 = new TCanvas("c_3", "genPlots2", 200, 200, 800, 700);
  //TCanvas *c_4 = new TCanvas("c_4", "genPlots3", 200, 200, 800, 700);
  TCanvas *c_5 = new TCanvas("c_5", "genPlots4", 200, 200, 800, 700);
  //c_1->Divide(2,2);
  //c_2->Divide(2,2);
  //c_3->Divide(2,2);
  //c_4->Divide(2,2);
  c_5->Divide(2,2);

  // Getting histogramsing into memory
  TH1F *ht = (TH1F*)f->Get("ht");
  TH1F *met_pt = (TH1F*)f->Get("met_pt");
  TH1F *mt2 = (TH1F*)f->Get("mt2");
  TH1F *nJet30 = (TH1F*)f->Get("nJet30");
  TH1F *ht_cut = (TH1F*)f->Get("ht_cut");
  TH1F *met_pt_cut = (TH1F*)f->Get("met_pt_cut");
  TH1F *mt2_cut = (TH1F*)f->Get("mt2_cut");
  TH1F *nJet30_cut = (TH1F*)f->Get("nJet30_cut");
  TH1F *genLep_pt = (TH1F*)f->Get("genLep_pt");
  TH1F *genGamma_pt = (TH1F*)f->Get("genGamma_pt");
  TH1F *genTau_pt = (TH1F*)f->Get("genTau_pt");
  TH1F *genStat23_pt = (TH1F*)f->Get("genStat23_pt");
  TH1F *genPart_pt = (TH1F*)f->Get("genPart_pt");
  TH1F *genPart_eta = (TH1F*)f->Get("genPart_eta");
  TH1F *genPart_mass = (TH1F*)f->Get("genPart_mass");
  TH1F *genPart_pdgId = (TH1F*)f->Get("genPart_pdgId");
  TH1F *genPart_status = (TH1F*)f->Get("genPart_status");
  TH1F *genPart_charge = (TH1F*)f->Get("genPart_charge");
  TH1F *genPart_motherId = (TH1F*)f->Get("genPart_motherId");
  TH1F *Higgs_mass = (TH1F*)f->Get("Higgs_mass");
  TH1F *Higgs_pt = (TH1F*)f->Get("Higgs_pt");
  TH1F *W_mass = (TH1F*)f->Get("W_mass");
  TH1F *W_pt = (TH1F*)f->Get("W_pt");

  // Normalizing
  Double_t ht_norm = 1.0/(ht->Integral());
  Double_t met_pt_norm = 1.0/(met_pt->Integral());
  Double_t mt2_norm = 1.0/(mt2->Integral());
  Double_t nJet30_norm = 1.0/(nJet30->Integral());
  Double_t ht_cut_norm = 1.0/(ht_cut->Integral());
  Double_t met_pt_cut_norm = 1.0/(met_pt_cut->Integral());
  Double_t mt2_cut_norm = 1.0/(mt2_cut->Integral());
  Double_t nJet30_cut_norm = 1.0/(nJet30_cut->Integral());
  Double_t genLep_pt_norm = 1.0/(genLep_pt->Integral());
  Double_t genGamma_pt_norm = 1.0/(genGamma_pt->Integral());
  Double_t genTau_pt_norm = 1.0/(genTau_pt->Integral());
  Double_t genStat23_pt_norm = 1.0/(genStat23_pt->Integral());
  Double_t genPart_pt_norm = 1.0/(genPart_pt->Integral());
  Double_t genPart_eta_norm = 1.0/(genPart_eta->Integral());
  Double_t genPart_mass_norm = 1.0/(genPart_mass->Integral());
  Double_t genPart_pdgId_norm = 1.0/(genPart_pdgId->Integral());
  Double_t genPart_status_norm = 1.0/(genPart_status->Integral());
  Double_t genPart_charge_norm = 1.0/(genPart_charge->Integral());
  Double_t genPart_motherId_norm = 1.0/(genPart_motherId->Integral());
  Double_t Higgs_mass_norm = 1.0/(Higgs_mass->Integral());
  Double_t Higgs_pt_norm = 1.0/(Higgs_pt->Integral());
  Double_t W_mass_norm = 1.0/(W_mass->Integral());
  Double_t W_pt_norm = 1.0/(W_pt->Integral());

  ht->Scale(ht_norm);
  met_pt->Scale(met_pt_norm);
  mt2->Scale(mt2_norm);
  nJet30->Scale(nJet30_norm);
  ht_cut->Scale(ht_cut_norm);
  met_pt_cut->Scale(met_pt_cut_norm);
  mt2_cut->Scale(mt2_cut_norm);
  nJet30_cut->Scale(nJet30_cut_norm);
  genLep_pt->Scale(genLep_pt_norm);
  genGamma_pt->Scale(genGamma_pt_norm);
  genTau_pt->Scale(genTau_pt_norm);
  //genStat23_pt->Scale(genStat23_pt_norm);
  genPart_pt->Scale(genPart_pt_norm);
  genPart_eta->Scale(genPart_eta_norm);
  genPart_mass->Scale(genPart_mass_norm);
  genPart_pdgId->Scale(genPart_pdgId_norm);
  genPart_status->Scale(genPart_status_norm);
  genPart_charge->Scale(genPart_charge_norm);
  genPart_motherId->Scale(genPart_motherId_norm);
  Higgs_mass->Scale(Higgs_mass_norm);
  Higgs_pt->Scale(Higgs_pt_norm);
  W_mass->Scale(W_mass_norm);
  W_pt->Scale(W_pt_norm);

  // Changing appearance
  ht->SetLineColor(kBlue-7);
  met_pt->SetLineColor(kBlue-7);
  mt2->SetLineColor(kBlue-7);
  nJet30->SetLineColor(kBlue-7);
  ht_cut->SetLineColor(kRed-7);
  met_pt_cut->SetLineColor(kRed-7);
  mt2_cut->SetLineColor(kRed-7);
  nJet30_cut->SetLineColor(kRed-7);
    
  // Setting legends
  TLegend *legend1 = new TLegend(0.68, 0.8, 0.98, 0.95);
  legend1->SetHeader("Legend","C"); // option "C" allows to center the header
  legend1->AddEntry(ht,"Before Selection", "f");
  legend1->AddEntry(ht_cut,"After Selection", "f");
    
  TLegend *legend2 = new TLegend(0.68, 0.8, 0.98, 0.95);
  legend2->SetHeader("Legend","C"); // option "C" allows to center the header
  legend2->AddEntry(met_pt,"Before Selection","f");
  legend2->AddEntry(met_pt_cut,"After Selection","f");
    
  TLegend *legend3 = new TLegend(0.68, 0.8, 0.98, 0.95);
  legend3->SetHeader("Legend","C"); // option "C" allows to center the header
  legend3->AddEntry(mt2,"Before Selection","f");
  legend3->AddEntry(mt2_cut,"After Selection","f");
    
  TLegend *legend4 = new TLegend(0.68, 0.8, 0.98, 0.95);
  legend4->SetHeader("Legend","C"); // option "C" allows to center the header
  legend4->AddEntry(nJet30,"Before Selection","f");
  legend4->AddEntry(nJet30_cut,"After Selection","f");
    
  // Drawing Histograms
  /*c_1->cd(1); // Go to panel 1
  ht_cut->Draw("hist");
  gPad->Update();
  TPaveStats *ps = (TPaveStats*)ht_cut->FindObject("stats");
  ps->SetY1NDC(0.62); ps->SetY2NDC(0.78); // Move stats panel
    
  ht->Draw("hist sames");
  gPad->Update();
  ps = (TPaveStats*)ht->FindObject("stats");
  ps->SetY1NDC(0.45); ps->SetY2NDC(0.60);
  legend1->Draw("same");
    
  c_1->cd(2); // Change to panel 2
  met_pt_cut->Draw("hist");
  gPad->Update();
  ps = (TPaveStats*)met_pt_cut->FindObject("stats");
  ps->SetY1NDC(0.62); ps->SetY2NDC(0.78);
    
  met_pt->Draw("hist sames");
  gPad->Update();
  ps = (TPaveStats*)met_pt->FindObject("stats");
  ps->SetY1NDC(0.45); ps->SetY2NDC(0.60);
  legend2->Draw("same");
    
  c_1->cd(3); // Change to panel 3
  mt2_cut->Draw("hist");
  gPad->Update();
  ps = (TPaveStats*)mt2_cut->FindObject("stats");
  ps->SetY1NDC(0.62); ps->SetY2NDC(0.78);
    
  mt2->Draw("hist sames");
  gPad->Update();
  ps = (TPaveStats*)mt2->FindObject("stats");
  ps->SetY1NDC(0.45); ps->SetY2NDC(0.60);
  legend3->Draw("same");

  c_1->cd(4); // Change to panel 4
  nJet30_cut->Draw("hist");
  gPad->Update();
  ps = (TPaveStats*)nJet30_cut->FindObject("stats");
  ps->SetY1NDC(0.62); ps->SetY2NDC(0.78);
    
  nJet30->Draw("hist sames");
  gPad->Update();
  ps = (TPaveStats*)nJet30->FindObject("stats");
  ps->SetY1NDC(0.45); ps->SetY2NDC(0.60);
  legend4->Draw("same");*/
     
  /*c_2->cd(1);
  genLep_pt->Draw("hist");
  c_2->cd(2);
  genGamma_pt->Draw("hist");
  c_2->cd(3);
  genTau_pt->Draw("hist");
  c_2->cd(4);
  genStat23_pt->Draw("hists");*/

  /*c_3->cd(1);
  genPart_pt->Draw("hist");
  c_3->cd(2);
  genPart_eta->Draw("hist");
  c_3->cd(3);
  genPart_mass->Draw("hist");
  c_3->cd(4);
  genPart_pdgId->Draw("hist");
  c_4->cd(1);
  genPart_status->Draw("hist");
  c_4->cd(2);
  genPart_charge->Draw("hist");
  c_4->cd(3);
  genPart_motherId->Draw("hist");*/

  c_5->cd(1);
  Higgs_mass->Draw("hist");
  c_5->cd(2);
  Higgs_pt->Draw("hist");
  c_5->cd(3);
  W_mass->Draw("hist");
  c_5->cd(4);
  W_pt->Draw("hist");

  return 0;
}
