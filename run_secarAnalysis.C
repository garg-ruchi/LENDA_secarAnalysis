#include "secarAnalysis.h"
#include "secarAnalysis.C"

void run_secarAnalysis(TString fileIn, TString fileOut, int run){
//=====================================================================//
//========================= Edit these inputs =========================//
//=====================================================================//
  // char addressIn[50] = "~/Desktop/SECAR/data/"; // Input files address
  // char addressOut[50] = "./histFiles"; // Change this to rename the directory where the output files will be saved
  // int runlist[] = {708, 710};// Runs to be analysed.
  // //{708, 709, 710, 711, 712, 713}
  // //{702, 703, 704, 705, 706}
  // //{675, 676, 677}
  // //{678, 679, 680, 681, 682, 683, 684, 685}
  // //{554, 555, 556, 557}
  // //{558, 559, 560, 561, 563, 564, 565, 566, 567}
  // //568, 569, 570, 571, 573, 574
  // //576, 577, 578
  // //592, 593, 594, 595, 596, 597, 598, 599, 600, 601, 602, 604, 606, 607

//-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-//

TFile *fin = new TFile(fileIn);
TTree *tin = (TTree*)fin->Get("t");
secarAnalysis *m = new secarAnalysis(tin);// Instantiate a secarAnalysis object, here called m.
m->Loop(fileOut, run);// Call Loop(TString fileOutName) function (loops over all entries) from the secarAnalysis class.

fin->Close();
fin->Delete();
delete m;

}
