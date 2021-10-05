#include "secarAnalysis.h"

struct bgoDTO{
  vector<double> energyCal;
  vector<int> chan;
  vector<double> time;
};

bgoDTO sortBGOHits(int mult_BGO, vector<int> *energy_BGO, vector<int> *chan_BGO, vector<double> *time_BGO, double BGO_gain[14], double BGO_offset[14]){
  bgoDTO bgoHit;
  if(mult_BGO>0 && mult_BGO<28){
    for(int i=0; i<mult_BGO; i++){
      bgoHit.energyCal.push_back(BGO_offset[(*chan_BGO)[i]] + BGO_gain[(*chan_BGO)[i]]*(*energy_BGO)[i]);
      bgoHit.chan.push_back((*chan_BGO)[i]);
      bgoHit.time.push_back((*time_BGO)[i]);
    }
  }
  return bgoHit;
}
