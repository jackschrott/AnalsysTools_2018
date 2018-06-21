# cms3Looper
to be used with makeCMS3ClassFiles.C. Creates histograms, writes them to a root file, and plots them.

# Running
After creating a CMS3 class file (see https://github.com/cmstas/Software/tree/master/makeCMS3ClassFiles), replace the ScanChain.C created by makeCMS3ClassFiles.C with the one included in this repository, and add Plot.C to the same directory. Then run ScanChain.C by running the following:

$ root -l doAll.C

This should create a file called histograms.root in the same directory. To create the plots, run Plot.C

$ root -l Plot.C
