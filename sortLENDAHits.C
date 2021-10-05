#include "secarAnalysis.h"

struct lendaDTO{
  vector<double> energy_T, energy_B;
  vector<int> pmt_T, pmt_B;
  vector<double> time_T, time_B;
};

//chan_LENDA comes from the createEvent and ranges from 0 to 41 ???
lendaDTO sortLENDAHits(int mult_LENDA, vector<int> *energy_LENDA, vector<int> *chan_LENDA, vector<double> *time_LENDA, int side_LENDA[42], int bar_LENDA[42]){
  lendaDTO LENDAHit;
  if(mult_LENDA>0 && mult_LENDA<42){
    for(int i=0; i<mult_LENDA; i++){
      if(side_LENDA[(*chan_LENDA)[i]]==0){
        LENDAHit.energy_T.push_back((*energy_LENDA)[i]);
        LENDAHit.pmt_T.push_back(bar_LENDA[(*chan_LENDA)[i]]);
        LENDAHit.time_T.push_back((*time_LENDA)[i]);
      }
      else if(side_LENDA[(*chan_LENDA)[i]]==1){
        LENDAHit.energy_B.push_back((*energy_LENDA)[i]);
        LENDAHit.pmt_B.push_back(bar_LENDA[(*chan_LENDA)[i]]);
        LENDAHit.time_B.push_back((*time_LENDA)[i]);
      }
    }
  }
  return LENDAHit;
}
