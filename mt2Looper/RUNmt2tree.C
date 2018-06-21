#include "mt2tree.cc"
void RUNmt2tree(){
  TChain *chain = new TChain("mt2","");
  chain->Add("/nfs-6/userdata/mt2/V00-08-18_WHstudy/TChiWH_700_1_part1.root");
  mt2tree a(chain);
  a.Loop();
}
