#include "secarAnalysis.h"

TCutG * graphicalCut(int Si[2], int dE[2], TString name){
  TCutG *cutg = new TCutG(name,5);
  cutg->SetPoint(0,Si[0],dE[0]);
  cutg->SetPoint(1,Si[1],dE[0]);
  cutg->SetPoint(2,Si[1],dE[1]);
  cutg->SetPoint(3,Si[0],dE[1]);
  cutg->SetPoint(4,Si[0],dE[0]);
  return cutg;
}
