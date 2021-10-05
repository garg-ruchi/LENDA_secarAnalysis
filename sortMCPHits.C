#include "secarAnalysis.h"

struct mcpDTO{
  vector<double> time;
};

mcpDTO sortMCPHits(int mult_UMCP_t, vector<double> *time_UMCP_t){
  mcpDTO mcpHit;
  if(mult_UMCP_t>0 && mult_UMCP_t<30){
    for(int i=0; i<mult_UMCP_t; i++) mcpHit.time.push_back((*time_UMCP_t)[i]);
  }
  return mcpHit;
}
