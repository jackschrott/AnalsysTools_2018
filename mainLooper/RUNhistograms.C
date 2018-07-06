#include "histograms.cc"
void RUNhistograms(){

  histograms a;
  a.Plot();
  a.makeTable("testFile.LTX", "Jack Schrott");
}
