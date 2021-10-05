#include "secarAnalysis.h"

struct SiDTO{
  vector<double> energyCal_F, energyCal_B;
  vector<int> strip_F, strip_B;
  vector<double> time_F, time_B;
  vector<double> energyCal_Good;
  vector<int> strip_GoodF, strip_GoodB;
  vector<double> time_Good;
};

SiDTO sortSiHits(int mult_Si, vector<int> *energy_Si, vector<int> *chan_Si, vector<double> *time_Si, int Si_side[72], int Si_strip[72], double Si_gain[72], double Si_offset[72], int resolution){
  SiDTO SiHit;
  if(mult_Si>0 && mult_Si<72){
    for(int i=0; i<mult_Si; i++){
      double energy_temp = Si_offset[(*chan_Si)[i]] + Si_gain[(*chan_Si)[i]]*(*energy_Si)[i];
      if(Si_side[(*chan_Si)[i]]==0){
        SiHit.energyCal_F.push_back(energy_temp);
        SiHit.strip_F.push_back(Si_strip[(*chan_Si)[i]]);
        SiHit.time_F.push_back((*time_Si)[i]);
      }
      else if(Si_side[(*chan_Si)[i]]==1){
        SiHit.energyCal_B.push_back(energy_temp);
        SiHit.strip_B.push_back(Si_strip[(*chan_Si)[i]]);
        SiHit.time_B.push_back((*time_Si)[i]);
      }
    }
    if(SiHit.strip_F.size()==2 && SiHit.strip_B.size()==1){
      if(abs(SiHit.strip_F[0]-SiHit.strip_F[1])==1 && abs(SiHit.energyCal_F[0]+SiHit.energyCal_F[1]-SiHit.energyCal_B[0])<resolution){
        SiHit.energyCal_F[0] += SiHit.energyCal_F[1];
        SiHit.energyCal_F.erase(SiHit.energyCal_F.begin()+1);
        SiHit.strip_F.erase(SiHit.strip_F.begin()+1);
        SiHit.time_F.erase(SiHit.time_F.begin()+1);
      }
    }
    if(SiHit.strip_B.size()==2 && SiHit.strip_F.size()==1){
      if(abs(SiHit.strip_B[0]-SiHit.strip_B[1])==1 && abs(SiHit.energyCal_B[0]+SiHit.energyCal_B[1]-SiHit.energyCal_F[0])<resolution){
        SiHit.energyCal_B[0] += SiHit.energyCal_B[1];
        SiHit.energyCal_B.erase(SiHit.energyCal_B.begin()+1);
        SiHit.strip_B.erase(SiHit.strip_B.begin()+1);
        SiHit.time_B.erase(SiHit.time_B.begin()+1);
      }
    }
    if(SiHit.strip_F.size()==2 && SiHit.strip_B.size()==2){
      if(abs(SiHit.strip_F[0]-SiHit.strip_F[1])==1 && abs(SiHit.strip_B[0]-SiHit.strip_B[1])==1 && abs(SiHit.energyCal_F[0]+SiHit.energyCal_F[1]-SiHit.energyCal_B[0]-SiHit.energyCal_B[1])<resolution){
        SiHit.energyCal_F[0] += SiHit.energyCal_F[1];
        SiHit.energyCal_F.erase(SiHit.energyCal_F.begin()+1);
        SiHit.strip_F.erase(SiHit.strip_F.begin()+1);
        SiHit.time_F.erase(SiHit.time_F.begin()+1);
        SiHit.energyCal_B[0] += SiHit.energyCal_B[1];
        SiHit.energyCal_B.erase(SiHit.energyCal_B.begin()+1);
        SiHit.strip_B.erase(SiHit.strip_B.begin()+1);
        SiHit.time_B.erase(SiHit.time_B.begin()+1);
      }
    }
    for(int i=0; i<SiHit.energyCal_F.size(); i++){
      for(int j=0; j<SiHit.energyCal_B.size(); j++){
        if(abs(SiHit.energyCal_F[i]-SiHit.energyCal_B[j])<resolution){
          SiHit.energyCal_Good.push_back((SiHit.energyCal_F[i]+SiHit.energyCal_B[j])/2);
          SiHit.strip_GoodF.push_back(SiHit.strip_F[i]);
          SiHit.strip_GoodB.push_back(SiHit.strip_B[j]);
          SiHit.time_Good.push_back(SiHit.time_F[i]);
        }
      }
    }
  }
  return SiHit;
}

SiDTO clearAll(SiDTO SiHit){//not being used at the moment
  SiHit.energyCal_F.clear();
  SiHit.energyCal_B.clear();
  SiHit.strip_F.clear();
  SiHit.strip_B.clear();
  SiHit.time_F.clear();
  SiHit.time_B.clear();
  SiHit.energyCal_Good.clear();
  SiHit.strip_GoodF.clear();
  SiHit.strip_GoodB.clear();
  SiHit.time_Good.clear();

  return SiHit;
}
