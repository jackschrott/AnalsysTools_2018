#include "mt2tree.cc"
void RUNmt2tree(){
  TChain *chain = new TChain("mt2","");
  chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts/TChiWH_TChiWH_700_1_genparts_part1.root");
  chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts/TChiWH_TChiWH_700_1_genparts_part2.root");
  chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts/TChiWH_TChiWH_700_1_genparts_part3.root");
  chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts/TChiWH_TChiWH_700_1_genparts_part4.root");
  chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/genparts/TChiWH_TChiWH_700_1_genparts_part5.root");
  mt2tree a(chain);
  a.Loop();
}
