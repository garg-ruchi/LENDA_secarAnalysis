#include "secarAnalysis.h"

struct lscintDTO{
  vector<double> energyCal;
  vector<int> chan;
  vector<double> time;
};

lscintDTO sortLScintHits(int mult_LScint, vector<int> *energy_LScint, vector<int> *chan_LScint, vector<double> *time_LScint){
  lscintDTO lscintHit;
  if(mult_LScint>0 && mult_LScint<4){
    cout << "IN" << endl;
    for(int i=0; i<mult_LScint; i++){
      lscintHit.energyCal.push_back((*energy_LScint)[i]);
      lscintHit.chan.push_back((*chan_LScint)[i]);
      lscintHit.time.push_back((*time_LScint)[i]);
    }
    cout << "OUT" << endl;
  }
  return lscintHit;
}
