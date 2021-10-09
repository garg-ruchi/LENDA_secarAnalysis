#include "secarAnalysis.h"

struct lscintDTO{
  vector<double> energyCal;
  vector<int> chan;
  vector<double> time;
};

lscintDTO sortLScintHits(int mult_LScint, vector<int> *energy_LScint, vector<int> *chan_LScint, vector<double> *time_LScint){
  lscintDTO lscintHit;
  if(mult_LScint>0 && mult_LScint<4){
    cout << __LINE__ << endl;
    for(int i=0; i<mult_LScint; i++){
      cout << __LINE__ << endl;
      lscintHit.energyCal.push_back((*energy_LScint)[i]);
      cout << __LINE__ << endl;
      lscintHit.chan.push_back((*chan_LScint)[i]);
      cout << __LINE__ << endl;
      lscintHit.time.push_back((*time_LScint)[i]);
      cout << __LINE__ << endl;
    }
    cout << __LINE__ << endl;
  }
  return lscintHit;
}
