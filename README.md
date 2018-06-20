# WHLooper_2018
Scripts to loop through CMS3 class files, do analysis, create histograms, and produce plots.

# Download

$ git clone https://github.com/jackschrott/WHLooper_2018.git

# Running
After creating a CMS3 class file (see https://github.com/cmstas/Software/tree/master/makeCMS3ClassFiles), replace the ScanChain.C created by makeCMS3ClassFiles.C with the one included in this repository, and add Plot.C to the same directory. Then run ScanChain.C by running the following:

$ root -l doAll.C

This should create a file called histograms.root in the same directory. To create the plots, run Plot.C

$ root -l Plot.C
