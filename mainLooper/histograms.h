#include <iostream>
#include <vector>
#include "TROOT.h"
#include "TAxis.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1F.h"

class histograms {
 public :

  // Declaring methods
  virtual void Plot();
  virtual void makeTable(const char* fileName, const char* authorName);

  // Declaring histograms                                                                                                                                                       
  Double_t luminosity;

  TH1F *ht;
  TH1F *ht_tt;
  TH1F *ht_wjets;
  TH1F *ht_zinv;
  TH1F *met_pt;
  TH1F *met_pt_tt;
  TH1F *met_pt_wjets;
  TH1F *met_pt_zinv;
  TH1F *mt2;
  TH1F *mt2_tt;
  TH1F *mt2_wjets;
  TH1F *mt2_zinv;
  TH1F *nJet30;
  TH1F *nJet30_tt;
  TH1F *nJet30_wjets;
  TH1F *nJet30_zinv;

  TAxis *ht_x;
  TAxis *met_pt_x;
  TAxis *mt2_x;
  TAxis *nJet30_x;

  std::vector<int> bounds;

  Int_t ht_a;
  Int_t ht_b;
  Int_t ht_c;
  Int_t ht_d;
  Int_t met_pt_a;
  Int_t met_pt_b;
  Int_t met_pt_c;
  Int_t met_pt_d;
  Int_t mt2_a;
  Int_t mt2_b;
  Int_t mt2_c;
  Int_t mt2_d;
  Int_t nJet30_a;
  Int_t nJet30_b;
  Int_t nJet30_c;
  Int_t nJet30_d;

  Double_t ht_n1, ht_n1_err;
  Double_t ht_n2, ht_n2_err;
  Double_t ht_n3, ht_n3_err;
  Double_t ht_tt_n1, ht_tt_n1_err;
  Double_t ht_tt_n2, ht_tt_n2_err;
  Double_t ht_tt_n3, ht_tt_n3_err;
  Double_t ht_wjets_n1, ht_wjets_n1_err;
  Double_t ht_wjets_n2, ht_wjets_n2_err;
  Double_t ht_wjets_n3, ht_wjets_n3_err;
  Double_t ht_zinv_n1, ht_zinv_n1_err;
  Double_t ht_zinv_n2, ht_zinv_n2_err;
  Double_t ht_zinv_n3, ht_zinv_n3_err;
  Double_t met_pt_n1, met_pt_n1_err;
  Double_t met_pt_n2, met_pt_n2_err;
  Double_t met_pt_n3, met_pt_n3_err;
  Double_t met_pt_tt_n1, met_pt_tt_n1_err;
  Double_t met_pt_tt_n2, met_pt_tt_n2_err;
  Double_t met_pt_tt_n3, met_pt_tt_n3_err;
  Double_t met_pt_wjets_n1, met_pt_wjets_n1_err;
  Double_t met_pt_wjets_n2, met_pt_wjets_n2_err;
  Double_t met_pt_wjets_n3, met_pt_wjets_n3_err;
  Double_t met_pt_zinv_n1, met_pt_zinv_n1_err;
  Double_t met_pt_zinv_n2, met_pt_zinv_n2_err;
  Double_t met_pt_zinv_n3, met_pt_zinv_n3_err;
  Double_t mt2_n1, mt2_n1_err;
  Double_t mt2_n2, mt2_n2_err;
  Double_t mt2_n3, mt2_n3_err;
  Double_t mt2_tt_n1, mt2_tt_n1_err;
  Double_t mt2_tt_n2, mt2_tt_n2_err;
  Double_t mt2_tt_n3, mt2_tt_n3_err;
  Double_t mt2_wjets_n1, mt2_wjets_n1_err;
  Double_t mt2_wjets_n2, mt2_wjets_n2_err;
  Double_t mt2_wjets_n3, mt2_wjets_n3_err;
  Double_t mt2_zinv_n1, mt2_zinv_n1_err;
  Double_t mt2_zinv_n2, mt2_zinv_n2_err;
  Double_t mt2_zinv_n3, mt2_zinv_n3_err;
  Double_t nJet30_n1, nJet30_n1_err;
  Double_t nJet30_n2, nJet30_n2_err;
  Double_t nJet30_n3, nJet30_n3_err;
  Double_t nJet30_tt_n1, nJet30_tt_n1_err;
  Double_t nJet30_tt_n2, nJet30_tt_n2_err;
  Double_t nJet30_tt_n3, nJet30_tt_n3_err;
  Double_t nJet30_wjets_n1, nJet30_wjets_n1_err;
  Double_t nJet30_wjets_n2, nJet30_wjets_n2_err;
  Double_t nJet30_wjets_n3, nJet30_wjets_n3_err;
  Double_t nJet30_zinv_n1, nJet30_zinv_n1_err;
  Double_t nJet30_zinv_n2, nJet30_zinv_n2_err;
  Double_t nJet30_zinv_n3, nJet30_zinv_n3_err;

  // Constructor
  histograms(Double_t luminosity) {

    this->luminosity = luminosity;

    // Loading root file                                                                                                                                                          
    TFile *f = new TFile("signal.root");
    TFile *f2 = new TFile("tt_background.root");
    TFile *f3 = new TFile("wjets_background.root");
    TFile *f4 = new TFile("zinv_background.root");
    if ( f->IsOpen() && f2->IsOpen() && f3->IsOpen() && f4->IsOpen()) printf("Files opened successfully\n");

    // Getting histogramsing into memory                                                                                                                                                  
    ht = (TH1F*)f->Get("ht");
    ht_tt = (TH1F*)f2->Get("ht");
    ht_wjets = (TH1F*)f3->Get("ht");
    ht_zinv = (TH1F*)f4->Get("ht");
    met_pt = (TH1F*)f->Get("met_pt");
    met_pt_tt = (TH1F*)f2->Get("met_pt");
    met_pt_wjets = (TH1F*)f3->Get("met_pt");
    met_pt_zinv = (TH1F*)f4->Get("met_pt");
    mt2 = (TH1F*)f->Get("mt2");
    mt2_tt = (TH1F*)f2->Get("mt2");
    mt2_wjets = (TH1F*)f3->Get("mt2");
    mt2_zinv = (TH1F*)f4->Get("mt2");
    nJet30 = (TH1F*)f->Get("nJet30");
    nJet30_tt = (TH1F*)f2->Get("nJet30");
    nJet30_wjets = (TH1F*)f3->Get("nJet30");
    nJet30_zinv = (TH1F*)f4->Get("nJet30");

    ht->Scale(luminosity);
    ht_tt->Scale(luminosity);
    ht_wjets->Scale(luminosity);
    ht_zinv->Scale(luminosity);
    met_pt->Scale(luminosity);
    met_pt_tt->Scale(luminosity);
    met_pt_wjets->Scale(luminosity);
    met_pt_zinv->Scale(luminosity);
    mt2->Scale(luminosity);
    mt2_tt->Scale(luminosity);
    mt2_wjets->Scale(luminosity);
    mt2_zinv->Scale(luminosity);
    nJet30->Scale(luminosity);
    nJet30_tt->Scale(luminosity);
    nJet30_wjets->Scale(luminosity);
    nJet30_zinv->Scale(luminosity);

    bounds = {250,520,1000,2000,250,450,750,2000,200,350,600,1000,2,2,3,4};

    ht_x = ht->GetXaxis();
    met_pt_x = met_pt->GetXaxis();
    mt2_x = mt2->GetXaxis();
    nJet30_x = nJet30->GetXaxis();
   
    ht_a = ht_x->FindBin(bounds[0]);
    ht_b = ht_x->FindBin(bounds[1]);
    ht_c = ht_x->FindBin(bounds[2]);
    ht_d = ht_x->FindBin(bounds[3]);
    met_pt_a = met_pt_x->FindBin(bounds[4]);
    met_pt_b = met_pt_x->FindBin(bounds[5]);
    met_pt_c = met_pt_x->FindBin(bounds[6]);
    met_pt_d = met_pt_x->FindBin(bounds[7]);
    mt2_a = mt2_x->FindBin(bounds[8]);
    mt2_b = mt2_x->FindBin(bounds[9]);
    mt2_c = mt2_x->FindBin(bounds[10]);
    mt2_d = mt2_x->FindBin(bounds[11]);
    nJet30_a = nJet30_x->FindBin(bounds[12]);
    nJet30_b = nJet30_x->FindBin(bounds[13]);
    nJet30_c = nJet30_x->FindBin(bounds[14]);
    nJet30_d = nJet30_x->FindBin(bounds[15]);

    ht_n1 = ht->IntegralAndError(ht_a, ht_b, ht_n1_err);
    ht_n2 = ht->IntegralAndError(ht_b+1, ht_c, ht_n2_err);
    ht_n3 = ht->IntegralAndError(ht_c+1, ht_d, ht_n3_err);
    ht_tt_n1 = ht_tt->IntegralAndError(ht_a, ht_b, ht_tt_n1_err);
    ht_tt_n2 = ht_tt->IntegralAndError(ht_b+1, ht_c, ht_tt_n2_err);
    cout << ht_tt_n2 << endl;
    ht_tt_n3 = ht_tt->IntegralAndError(ht_c+1, ht_d, ht_tt_n3_err);
    ht_wjets_n1 = ht_wjets->IntegralAndError(ht_a, ht_b, ht_wjets_n1_err);
    ht_wjets_n2 = ht_wjets->IntegralAndError(ht_b+1, ht_c, ht_wjets_n2_err);
    cout << ht_wjets_n2 << endl;
    ht_wjets_n3 = ht_wjets->IntegralAndError(ht_c+1, ht_d, ht_wjets_n3_err);
    ht_zinv_n1 = ht_zinv->IntegralAndError(ht_a, ht_b, ht_zinv_n1_err);
    ht_zinv_n2 = ht_zinv->IntegralAndError(ht_b+1, ht_c, ht_zinv_n2_err);
    ht_zinv_n3 = ht_zinv->IntegralAndError(ht_c+1, ht_d, ht_zinv_n3_err);
    met_pt_n1 = met_pt->IntegralAndError(met_pt_a, met_pt_b, met_pt_n1_err);
    met_pt_n2 = met_pt->IntegralAndError(met_pt_b+1, met_pt_c, met_pt_n2_err);
    met_pt_n3 = met_pt->IntegralAndError(met_pt_c+1, met_pt_d, met_pt_n3_err);
    met_pt_tt_n1 = met_pt_tt->IntegralAndError(met_pt_a, met_pt_b, met_pt_tt_n1_err);
    met_pt_tt_n2 = met_pt_tt->IntegralAndError(met_pt_b+1, met_pt_c, met_pt_tt_n2_err);
    met_pt_tt_n3 = met_pt_tt->IntegralAndError(met_pt_c+1, met_pt_d, met_pt_tt_n3_err);
    met_pt_wjets_n1 = met_pt_wjets->IntegralAndError(met_pt_a, met_pt_b, met_pt_wjets_n1_err);
    met_pt_wjets_n2 = met_pt_wjets->IntegralAndError(met_pt_b+1, met_pt_c, met_pt_wjets_n2_err);
    met_pt_wjets_n3 = met_pt_wjets->IntegralAndError(met_pt_c+1, met_pt_d, met_pt_wjets_n3_err);
    met_pt_zinv_n1 = met_pt_zinv->IntegralAndError(met_pt_a, met_pt_b, met_pt_zinv_n1_err);
    met_pt_zinv_n2 = met_pt_zinv->IntegralAndError(met_pt_b+1, met_pt_c, met_pt_zinv_n2_err);
    met_pt_zinv_n3 = met_pt_zinv->IntegralAndError(met_pt_c+1, met_pt_d, met_pt_zinv_n3_err);
    mt2_n1 = mt2->IntegralAndError(mt2_a, mt2_b, mt2_n1_err);
    mt2_n2 = mt2->IntegralAndError(mt2_b+1, mt2_c, mt2_n2_err);
    mt2_n3 = mt2->IntegralAndError(mt2_c+1, mt2_d, mt2_n3_err);
    mt2_tt_n1 = mt2_tt->IntegralAndError(mt2_a, mt2_b, mt2_tt_n1_err);
    mt2_tt_n2 = mt2_tt->IntegralAndError(mt2_b+1, mt2_c, mt2_tt_n2_err);
    mt2_tt_n3 = mt2_tt->IntegralAndError(mt2_c+1, mt2_d, mt2_tt_n3_err);
    mt2_wjets_n1 = mt2_wjets->IntegralAndError(mt2_a, mt2_b, mt2_wjets_n1_err);
    mt2_wjets_n2 = mt2_wjets->IntegralAndError(mt2_b+1, mt2_c, mt2_wjets_n2_err);
    mt2_wjets_n3 = mt2_wjets->IntegralAndError(mt2_c+1, mt2_d, mt2_wjets_n3_err);
    mt2_zinv_n1 = mt2_zinv->IntegralAndError(mt2_a, mt2_b, mt2_zinv_n1_err);
    mt2_zinv_n2 = mt2_zinv->IntegralAndError(mt2_b+1, mt2_c, mt2_zinv_n2_err);
    mt2_zinv_n3 = mt2_zinv->IntegralAndError(mt2_c+1, mt2_d, mt2_zinv_n3_err);
    nJet30_n1 = nJet30->IntegralAndError(nJet30_a, nJet30_b, nJet30_n1_err);
    nJet30_n2 = nJet30->IntegralAndError(nJet30_b+1, nJet30_c, nJet30_n2_err);
    nJet30_n3 = nJet30->IntegralAndError(nJet30_c+1, nJet30_d, nJet30_n3_err);
    nJet30_tt_n1 = nJet30_tt->IntegralAndError(nJet30_a, nJet30_b, nJet30_tt_n1_err);
    nJet30_tt_n2 = nJet30_tt->IntegralAndError(nJet30_b+1, nJet30_c, nJet30_tt_n2_err);
    nJet30_tt_n3 = nJet30_tt->IntegralAndError(nJet30_c+1, nJet30_d, nJet30_tt_n3_err);
    nJet30_wjets_n1 = nJet30_wjets->IntegralAndError(nJet30_a, nJet30_b, nJet30_wjets_n1_err);
    nJet30_wjets_n2 = nJet30_wjets->IntegralAndError(nJet30_b+1, nJet30_c, nJet30_wjets_n2_err);
    nJet30_wjets_n3 = nJet30_wjets->IntegralAndError(nJet30_c+1, nJet30_d, nJet30_wjets_n3_err);
    nJet30_zinv_n1 = nJet30_zinv->IntegralAndError(nJet30_a, nJet30_b, nJet30_zinv_n1_err);
    nJet30_zinv_n2 = nJet30_zinv->IntegralAndError(nJet30_b+1, nJet30_c, nJet30_zinv_n2_err);
    nJet30_zinv_n3 = nJet30_zinv->IntegralAndError(nJet30_c+1, nJet30_d, nJet30_zinv_n3_err);
  }
};
