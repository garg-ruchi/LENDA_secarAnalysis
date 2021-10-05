#include "secarAnalysis.h"

struct icDTO{
  vector<double> energyCal;
  vector<int> chan;
  vector<double> time;
};

icDTO sortICHits(int mult_IC_dE, vector<int> *energy_IC_dE, vector<double> *time_IC_dE, double IC_gain, double IC_offset){
  icDTO icHit;
  if(mult_IC_dE>0 && mult_IC_dE<10){
    for(int i=0; i<mult_IC_dE; i++){
      icHit.energyCal.push_back(IC_offset + IC_gain*(*energy_IC_dE)[i]);
      icHit.time.push_back((*time_IC_dE)[i]);
    }
  }
  return icHit;
}
