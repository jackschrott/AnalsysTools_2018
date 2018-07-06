/* C++                                                                                                                                                                                                          
 * Author: Jack Schrott (fnal)                                                                                                                                                                                  
 * Date: 06/20/2018                                                                                                                                                                                             
 ****************************                                                                                                                                                                                   
 */

#include <iostream>
#include <vector>
#include <numeric>

// ROOT                                                                                                                                                                                                        
#include "histograms.h"
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
#include "THStack.h"

using namespace std;

void histograms::Plot() {

  // Creating canvases
  TCanvas *c_1 = new TCanvas("c_1", "Plots", 200, 200, 900, 700);
  c_1->Divide(2,2);

  THStack *ht_stack = new THStack("ht","");
  THStack *met_pt_stack = new THStack("met_pt","");
  THStack *mt2_stack = new THStack("mt2","");
  THStack *nJet30_stack = new THStack("nJet30","");

  // Setting colors
  ht->SetFillColor(kOrange);
  ht_tt->SetFillColor(kBlue);
  ht_wjets->SetFillColor(kGreen);
  ht_zinv->SetFillColor(kRed);
  met_pt->SetFillColor(kOrange);
  met_pt_tt->SetFillColor(kBlue);
  met_pt_wjets->SetFillColor(kGreen);
  met_pt_zinv->SetFillColor(kRed);
  mt2->SetFillColor(kOrange);
  mt2_tt->SetFillColor(kBlue);
  mt2_wjets->SetFillColor(kGreen);
  mt2_zinv->SetFillColor(kRed);
  nJet30->SetFillColor(kOrange);
  nJet30_tt->SetFillColor(kBlue);
  nJet30_wjets->SetFillColor(kGreen);
  nJet30_zinv->SetFillColor(kRed);

  // Adding to TH1Stacks
  ht_stack->Add(ht_tt);
  ht_stack->Add(ht_wjets);
  ht_stack->Add(ht_zinv);
  ht_stack->Add(ht);
  met_pt_stack->Add(met_pt_tt);
  met_pt_stack->Add(met_pt_wjets);
  met_pt_stack->Add(met_pt_zinv);
  met_pt_stack->Add(met_pt);
  mt2_stack->Add(mt2_tt);
  mt2_stack->Add(mt2_wjets);
  mt2_stack->Add(mt2_zinv);
  mt2_stack->Add(mt2);
  nJet30_stack->Add(nJet30_tt);
  nJet30_stack->Add(nJet30_wjets);
  nJet30_stack->Add(nJet30_zinv);
  nJet30_stack->Add(nJet30);

  // Adding legends
  TLegend *legend1 = new TLegend(0.68, 0.75, 0.98, 0.95);
  TLegend *legend2 = new TLegend(0.68, 0.75, 0.98, 0.95);
  TLegend *legend4 = new TLegend(0.68, 0.75, 0.98, 0.95);
  TLegend *legend3 = new TLegend(0.68, 0.75, 0.98, 0.95);
  legend1->SetHeader("Legend","C"); // option "C" allows to center the header
  legend2->SetHeader("Legend","C"); // option "C" allows to center the header
  legend3->SetHeader("Legend","C"); // option "C" allows to center the header
  legend4->SetHeader("Legend","C"); // option "C" allows to center the header
  legend1->AddEntry(ht,"WH", "f");
  legend1->AddEntry(ht_tt, "t#bar{t}", "f");
  legend1->AddEntry(ht_wjets, "Wjets", "f");
  legend1->AddEntry(ht_zinv, "Zinv", "f");
  legend2->AddEntry(met_pt,"WH", "f");
  legend2->AddEntry(met_pt_tt, "t#bar{t}", "f");
  legend2->AddEntry(met_pt_wjets, "Wjets", "f");
  legend2->AddEntry(met_pt_zinv, "Zinv", "f");
  legend3->AddEntry(mt2,"WH", "f");
  legend3->AddEntry(mt2_tt, "t#bar{t}", "f");
  legend3->AddEntry(mt2_wjets, "Wjets", "f");
  legend3->AddEntry(mt2_zinv, "Zinv", "f");
  legend4->AddEntry(nJet30,"WH", "f");
  legend4->AddEntry(nJet30_tt, "t#bar{t}", "f");
  legend4->AddEntry(nJet30_wjets, "Wjets", "f");
  legend4->AddEntry(nJet30_zinv, "Zinv", "f");

  // Drawing to Canvas                                                                                                                                                                                         
  gStyle->SetOptStat(0);
  c_1->cd(1);
  ht_stack->Draw("hist");
  legend1->Draw("sames");
  ht_stack->GetXaxis()->SetTitle("H_{t}^{miss} [GeV]");
  c_1->cd(1)->Modified();
  c_1->cd(2);
  met_pt_stack->Draw("hist");
  legend2->Draw("sames");
  met_pt_stack->GetXaxis()->SetTitle("Met_{pt} [GeV]");
  c_1->cd(2)->Modified();
  c_1->cd(3);
  mt2_stack->Draw("hist");
  legend3->Draw("sames");
  mt2_stack->GetXaxis()->SetTitle("Mt2 [GeV]");
  c_1->cd(3)->Modified();
  c_1->cd(4);
  nJet30_stack->Draw("hist");
  legend4->Draw("sames");
  nJet30_stack->GetXaxis()->SetTitle("nJet30 [N]");
  c_1->cd(4)->Modified();
}

void histograms::makeTable(const char* fileName, const char* authorName) {

  ofstream codef;
  time_t now = time(0);
  char* dt = ctime(&now);
  Double_t value = 000;

  codef.open(fileName);
  codef << "\\documentclass{article}" << endl;
  codef << "\\usepackage{caption}" << endl;
  codef << "\\usepackage{amsmath}" << endl;
  codef << "\\usepackage{graphicx}" << endl;
  codef << "\\usepackage{esvect}" << endl;
  codef << "\\usepackage{braket}" << endl;
  codef << "\\usepackage{amssymb}%" << endl;
  codef << "\\usepackage{float}" << endl;
  codef << "\\usepackage{graphicx,float}" << endl;
  codef << "\\usepackage{geometry}     % See geometry.pdf to learn the layout options. There are lots." << endl;
  codef << "\\usepackage{booktabs}%Added line for Pandas exporting" << endl;
  codef << "\\geometry{letterpaper}  % ... or a4paper or a5paper or ..." << endl;
  codef << "" << endl;
  codef << "\\begin{document}" << endl;
  codef << "\\title{Expected Event Count Summary}" << endl;
  codef << "\\author{Created by: "<< authorName <<"}" << endl;
  codef << "\\date{"<< dt <<"}" << endl;
  codef << "\\maketitle" << endl;
  codef << "\\begin{table} [H]" << endl;
  codef << "\\begin{center}" << endl;
  codef << "\\begin{tabular}{r|r|r|r}" << endl;
  codef << "\\toprule" << endl;
  codef << "Process  & $"<<bounds[0]<<"\\leq H_T^{miss}\\leq "<<bounds[1]<<"\\,$Gev & $"
	<<bounds[1]<<"< H_T^{miss}\\leq "<<bounds[2]<<"\\,$Gev & $H_T^{miss}> "<<bounds[2]<<"\\,$Gev \\\\" << endl;
  codef << "\\midrule" << endl;
  codef << "$WH$ & $"<< ht_n1 <<"\\pm"<< ht_n1_err <<"$ & $"<< ht_n2 <<"\\pm"
	<< ht_n2_err <<"$ &  $"<< ht_n3 <<"\\pm"<< ht_n3_err << "$ \\\\" << endl;
  codef << "$t\\bar{t}$ & $"<< ht_tt_n1 <<"\\pm"<< ht_tt_n1_err <<"$ &  $"<< ht_tt_n2 <<"\\pm"
	<< ht_tt_n2_err <<"$ &  $"<< ht_tt_n3 <<"\\pm"<< ht_tt_n3_err <<"$ \\\\" << endl;
  codef << "$W + jets$ & $"<< ht_wjets_n3 <<"\\pm"<< ht_wjets_n1_err <<"$ &  $"<< ht_wjets_n2 <<"\\pm"
	<< ht_wjets_n2_err <<"$ &  $"<< ht_wjets_n3 <<"\\pm"<< ht_wjets_n2_err <<"$ \\\\" << endl;
  codef << "$Zinv$ & $"<< ht_zinv_n1 <<"\\pm"<< ht_zinv_n1_err <<"$ &  $"<< ht_zinv_n2 <<"\\pm"
	<< ht_zinv_n2_err <<"$ &  $"<< ht_zinv_n3 <<"\\pm"<< ht_zinv_n3_err <<"$ \\\\" << endl;
  codef << "Rare SM events & $"<< value <<"\\pm"<< value <<"$ & $"<< value <<"\\pm"
	<< value <<"$ & $"<< value <<"\\pm"<< value <<"$ \\\\" << endl;
  codef << "\\toprule" << endl;
  codef << "Process  & $"<<bounds[4]<<"\\leq Met_{pt}\\leq "<<bounds[5]<<"\\,$Gev & $"<<bounds[5]<<"< Met_{pt}\\leq "
	<<bounds[6]<<"\\,$Gev & $Met_{pt}> "<<bounds[6]<<"\\,$Gev \\\\" << endl;
  codef << "\\midrule" << endl;
  codef << "$WH$ & $"<< met_pt_n1 <<"\\pm"<< met_pt_n1_err <<"$ & $"<< met_pt_n2 <<"\\pm"
        << met_pt_n2_err <<"$ &  $"<< met_pt_n3 <<"\\pm"<< met_pt_n3_err << "$ \\\\" << endl;
  codef << "$t\\bar{t}$ & $"<< met_pt_tt_n1 <<"\\pm"<< met_pt_tt_n1_err <<"$ &  $"<< met_pt_tt_n2 <<"\\pm"
        << met_pt_tt_n2_err <<"$ &  $"<< met_pt_tt_n3 <<"\\pm"<< met_pt_tt_n3_err <<"$ \\\\" << endl;
  codef << "$W + jets$ & $"<< met_pt_wjets_n3 <<"\\pm"<< met_pt_wjets_n1_err <<"$ &  $"<< met_pt_wjets_n2 <<"\\pm"
        << met_pt_wjets_n2_err <<"$ &  $"<< met_pt_wjets_n3 <<"\\pm"<< met_pt_wjets_n2_err <<"$ \\\\" << endl;
  codef << "$Zinv$ & $"<< met_pt_zinv_n1 <<"\\pm"<< met_pt_zinv_n1_err <<"$ &  $"<< met_pt_zinv_n2 <<"\\pm"
        << met_pt_zinv_n2_err <<"$ &  $"<< met_pt_zinv_n3 <<"\\pm"<< met_pt_zinv_n3_err <<"$ \\\\" << endl;
  codef << "Rare SM events & $"<< value <<"\\pm"<< value <<"$ & $"<< value <<"\\pm"
        << value <<"$ & $"<< value <<"\\pm"<< value <<"$ \\\\" << endl;
  codef << "\\toprule" << endl;
  codef << "Process  & $"<<bounds[8]<<"\\leq M_{T2}\\leq "<<bounds[9]<<"\\,$Gev & $"<<bounds[9]<<"< M_{T2}\\leq "
	<<bounds[10]<<"\\,$Gev & $M_{T2}> "<<bounds[10]<<"\\,$Gev \\\\" << endl;
  codef << "\\midrule" << endl;
  codef << "$WH$ & $"<< mt2_n1 <<"\\pm"<< mt2_n1_err <<"$ & $"<< mt2_n2 <<"\\pm"
        << mt2_n2_err <<"$ &  $"<< mt2_n3 <<"\\pm"<< mt2_n3_err << "$ \\\\" << endl;
  codef << "$t\\bar{t}$ & $"<< mt2_tt_n1 <<"\\pm"<< mt2_tt_n1_err <<"$ &  $"<< mt2_tt_n2 <<"\\pm"
        << mt2_tt_n2_err <<"$ &  $"<< mt2_tt_n3 <<"\\pm"<< mt2_tt_n3_err <<"$ \\\\" << endl;
  codef << "$W + jets$ & $"<< mt2_wjets_n3 <<"\\pm"<< mt2_wjets_n1_err <<"$ &  $"<< mt2_wjets_n2 <<"\\pm"
        << mt2_wjets_n2_err <<"$ &  $"<< mt2_wjets_n3 <<"\\pm"<< mt2_wjets_n2_err <<"$ \\\\" << endl;
  codef << "$Zinv$ & $"<< mt2_zinv_n1 <<"\\pm"<< mt2_zinv_n1_err <<"$ &  $"<< mt2_zinv_n2 <<"\\pm"
        << mt2_zinv_n2_err <<"$ &  $"<< mt2_zinv_n3 <<"\\pm"<< mt2_zinv_n3_err <<"$ \\\\" << endl;
  codef << "Rare SM events & $"<< value <<"\\pm"<< value <<"$ & $"<< value <<"\\pm"
        << value <<"$ & $"<< value <<"\\pm"<< value <<"$ \\\\" << endl;
  codef << "\\toprule" << endl;
  codef << "Process  & $nJet30="<<bounds[12]<<"\\,$Gev & $nJet30="<<bounds[14]<<"\\,$Gev & $nJet30="<<bounds[15]<<"\\,$Gev \\\\" << endl;
  codef << "\\midrule" << endl;
  codef << "$WH$ & $"<< nJet30_n1 <<"\\pm"<< nJet30_n1_err <<"$ & $"<< nJet30_n2 <<"\\pm"
        << nJet30_n2_err <<"$ &  $"<< nJet30_n3 <<"\\pm"<< nJet30_n3_err << "$ \\\\" << endl;
  codef << "$t\\bar{t}$ & $"<< nJet30_tt_n1 <<"\\pm"<< nJet30_tt_n1_err <<"$ &  $"<< nJet30_tt_n2 <<"\\pm"
        << nJet30_tt_n2_err <<"$ &  $"<< nJet30_tt_n3 <<"\\pm"<< nJet30_tt_n3_err <<"$ \\\\" << endl;
  codef << "$W + jets$ & $"<< nJet30_wjets_n3 <<"\\pm"<< nJet30_wjets_n1_err <<"$ &  $"<< nJet30_wjets_n2 <<"\\pm"
        << nJet30_wjets_n2_err <<"$ &  $"<< nJet30_wjets_n3 <<"\\pm"<< nJet30_wjets_n2_err <<"$ \\\\" << endl;
  codef << "$Zinv$ & $"<< nJet30_zinv_n1 <<"\\pm"<< nJet30_zinv_n1_err <<"$ &  $"<< nJet30_zinv_n2 <<"\\pm"
        << nJet30_zinv_n2_err <<"$ &  $"<< nJet30_zinv_n3 <<"\\pm"<< nJet30_zinv_n3_err <<"$ \\\\" << endl;
  codef << "Rare SM events & $"<< value <<"\\pm"<< value <<"$ & $"<< value <<"\\pm"
        << value <<"$ & $"<< value <<"\\pm"<< value <<"$ \\\\" << endl;
  codef << "\\bottomrule" << endl;
  codef << "\\end{tabular}" << endl;
  codef << "\\caption{Expected Number of Events} \\label{tab:raw data}" << endl;
  codef << "\\end{center}" << endl;
  codef << "\\end{table}" << endl;
  codef << "\\end{document}" << endl;
  codef.close();
}
