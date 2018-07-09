#include "histograms.cc"
void RUNhistograms(){

  histograms *a =  new histograms(1);
  histograms *b = new histograms(36);
  //a->Plot();
  //b->Plot();
  a->makeTable("testFile1.LTX", "Jack Schrott");
  b->makeTable("testFile36.LTX", "Jack Schrott");
}
