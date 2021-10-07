#include "secarAnalysis.h"

struct lendaDTO{
  vector<double> energy_T, energy_B;
  vector<int> pmt_T, pmt_B;
  vector<double> time_T, time_B;
  vector<int> barGood;
  vector<double> energyGood;
  vector<double> timeGood;
};

//chan_LENDA comes from the createEvent and ranges from 0 to 41 ???
lendaDTO sortLENDAHits(int mult_LENDA, vector<int> *energy_LENDA, vector<int> *chan_LENDA, vector<double> *time_LENDA, int side_LENDA[42], int bar_LENDA[42]){
  cout << "In" << endl;
  lendaDTO LENDAHit;
  cout << __LINE__ << endl;
  if(mult_LENDA>1 && mult_LENDA<42){
    for(int i=0; i<mult_LENDA; i++){
      if(side_LENDA[(*chan_LENDA)[i]]==0){
        LENDAHit.energy_T.push_back((*energy_LENDA)[i]);
        LENDAHit.pmt_T.push_back(bar_LENDA[(*chan_LENDA)[i]]);
        LENDAHit.time_T.push_back((*time_LENDA)[i]);
      }
      cout << __LINE__ << endl;
      else if(side_LENDA[(*chan_LENDA)[i]]==1){
        LENDAHit.energy_B.push_back((*energy_LENDA)[i]);
        LENDAHit.pmt_B.push_back(bar_LENDA[(*chan_LENDA)[i]]);
        LENDAHit.time_B.push_back((*time_LENDA)[i]);
      }
    }
    cout << __LINE__ << endl;
    if(LENDAHit.pmt_T.size()>0 && LENDAHit.pmt_B.size()>0){
      for(int i=0; i<LENDAHit.pmt_T.size(); i++){
        for(int j=0; j<LENDAHit.pmt_B.size(); j++){
          if(LENDAHit.pmt_T[i]==LENDAHit.pmt_B[j] && abs(LENDAHit.time_T[i]-LENDAHit.time_B[j])<10){
            LENDAHit.barGood.push_back(LENDAHit.pmt_T[i]);
            LENDAHit.energyGood.push_back(sqrt(LENDAHit.energy_T[i]*LENDAHit.energy_B[j]));
            LENDAHit.timeGood.push_back((LENDAHit.time_T[i]+LENDAHit.time_B[j])/2);
          }
        }
      }
    }
    cout << __LINE__ << endl;
  }
  cout << "out" << endl;
  return LENDAHit;
}
