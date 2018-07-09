#include "evtLooper.cc"
void RUNevtLooper(){
  TChain *WH_chain = new TChain("mt2","");
  TChain *tt_chain = new TChain("mt2","");
  TChain *wjets_chain = new TChain("mt2","");
  TChain *zinv_chain = new TChain("mt2","");

  WH_chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts_idx/TChiWH_TChiWH_700_1_genparts_part1.root");
  WH_chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts_idx/TChiWH_TChiWH_700_1_genparts_part2.root");
  WH_chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts_idx/TChiWH_TChiWH_700_1_genparts_part3.root");
  WH_chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts_idx/TChiWH_TChiWH_700_1_genparts_part4.root");
  WH_chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts_idx/TChiWH_TChiWH_700_1_genparts_part5.root");

  tt_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/ttdl_mg_lo.root");
  tt_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/ttg_amcatnlo_1.root");
  tt_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/tth_bb_1.root");
  tt_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/tth_nonbb_1.root");
  tt_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/ttsl_mg_lo_tbar.root");
  tt_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/ttsl_mg_lo_top.root");
  tt_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/tttt_amcatnlo_1.root");
  tt_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/ttw_mg_lo_1.root");
  tt_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/ttz_mg_lo_1.root");

  wjets_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/wjets_ht100to200.root");
  wjets_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/wjets_ht1200to2500_nonext_1.root");
  wjets_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/wjets_ht200to400.root");
  wjets_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/wjets_ht2500toInf.root");
  wjets_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/wjets_ht400to600.root");
  wjets_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/wjets_ht600to800.root");
  wjets_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/wjets_ht800to1200_ext1_1.root");

  zinv_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/zinv_ht1200to2500_nonext_1.root");
  zinv_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/zinv_ht1200to2500_nonext_1.root");
  zinv_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/zinv_ht200to400_nonext_1.root");
  zinv_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/zinv_ht2500toInf_nonext_1.root");
  zinv_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/zinv_ht400to600_ext1_1.root");
  zinv_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/zinv_ht600to800_nonext_1.root");
  zinv_chain->Add("/nfs-6/userdata/mt2/2016_moriond_results/zinv_ht800to1200_nonext_1.root");

  evtLooper WH_scan(WH_chain);
  //evtLooper tt_scan(tt_chain);
  //evtLooper wjets_scan(wjets_chain);
  //evtLooper zinv_scan(zinv_chain);
  
  WH_scan.sigLoop();
  //tt_scan.bgLoop();
  //wjets_scan.bgLoop();
  //zinv_scan.bgLoop();

  WH_scan.saveHists("signal.root");
  //tt_scan.saveHists("tt_background.root");
  //wjets_scan.saveHists("wjets_background.root");
  //zinv_scan.saveHists("zinv_background.root");
  
}
