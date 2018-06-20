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
    TCanvas *c_1 = new TCanvas("c_1", "Plots", 200, 200, 800, 700);
    TCanvas *c_2 = new TCanvas("c_2", "genPlots", 200, 200, 800, 700);
    c_1->Divide(2,2);
    c_2->Divide(2,2);

    // Getting histogramsing into memory
    TH1F *ht = (TH1F*)f->Get("ht");
    TH1F *met_pt = (TH1F*)f->Get("met_pt");
    TH1F *mt2 = (TH1F*)f->Get("mt2");
    TH1F *nJet30 = (TH1F*)f->Get("nJet30");
    TH1F *ht_cut = (TH1F*)f->Get("ht_cut");
    TH1F *met_pt_cut = (TH1F*)f->Get("met_pt_cut");
    TH1F *mt2_cut = (TH1F*)f->Get("mt2_cut");
    TH1F *nJet30_cut = (TH1F*)f->Get("nJet30_cut");

    // Normalizing
    Double_t ht_norm = 1.0/(ht->Integral());
    Double_t met_pt_norm = 1.0/(met_pt->Integral());
    Double_t mt2_norm = 1.0/(mt2->Integral());
    Double_t nJet30_norm = 1.0/(nJet30->Integral());
    Double_t ht_cut_norm = 1.0/(ht_cut->Integral());
    Double_t met_pt_cut_norm = 1.0/(met_pt_cut->Integral());
    Double_t mt2_cut_norm = 1.0/(mt2_cut->Integral());
    Double_t nJet30_cut_norm = 1.0/(nJet30_cut->Integral());
    
    ht->Scale(ht_norm);
    met_pt->Scale(met_pt_norm);
    mt2->Scale(mt2_norm);
    nJet30->Scale(nJet30_norm);
    ht_cut->Scale(ht_cut_norm);
    met_pt_cut->Scale(met_pt_cut_norm);
    mt2_cut->Scale(mt2_cut_norm);
    nJet30_cut->Scale(nJet30_cut_norm);
    
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
    c_1->cd(1); // Go to panel 1
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
    legend4->Draw("same");
     
    return 0;
}
