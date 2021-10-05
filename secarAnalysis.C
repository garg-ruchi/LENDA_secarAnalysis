#define secarAnalysis_cxx
#include "secarAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void secarAnalysis::Loop(TString fileOutName, int run)
{
//=====================================================================//
//=================== Energy Calibration Parameters ===================//
//=====================================================================//
  int Si_side[72];
  int Si_strip[72];
  double Si_gain[72];
  double Si_offset[72];
  ifstream f_SiMap("SiMap.dat");
  for(int i=0; i<72; i++){
    f_SiMap >> Si_side[i] >> Si_strip[i] >> Si_gain[i] >> Si_offset[i];
  }

  int side_LENDA[42];
  int bar_LENDA[42];
  ifstream f_LENDAMap("LENDAMap.dat");
  for(int i=0; i<42; i++){
    f_LENDAMap >> side_LENDA[i] >> bar_LENDA[i];
  }

  double IC_dE_gain = 0.541;
  double IC_dE_offset = 0;
//-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-//

//=====================================================================//
//========================== User Variables ===========================//
//=====================================================================//
  mcpDTO mcpHit;
  icDTO icHit;
  SiDTO SiHit;
  lendaDTO LENDAHit;
//-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-//

//=====================================================================//
//============================= Histograms ============================//
//=====================================================================//

  // Si histograms
  TList *Si = new TList(); // Add every new histogram to this list!!!
  TH1D *h_m_SiF = new TH1D("h_m_SiF","Si front multiplicity",32,0,32);
  Si->Add(h_m_SiF);
  TH1D *h_e_SiF = new TH1D("h_e_SiF","Calibrated Si front",4000,0,200000);
  Si->Add(h_e_SiF);
  TH2D *h_ep_SiF = new TH2D("h_ep_SiF","Calibrated Si front energy vs strip number",4000,0,200000,32,0,32);
  Si->Add(h_ep_SiF);
  TH1D *h_m_SiB = new TH1D("h_m_SiB","Si back multiplicity",32,0,32);
  Si->Add(h_m_SiB);
  TH1D *h_e_SiB = new TH1D("h_e_SiB","Calibrated Si back",4000,0,200000);
  Si->Add(h_e_SiB);
  TH2D *h_ep_SiB = new TH2D("h_ep_SiB","Calibrated Si back energy vs strip number",4000,0,200000,32,0,32);
  Si->Add(h_ep_SiB);
  TH1D *h_e_SiFBdiff = new TH1D("h_e_SiFBdiff","Calibrated Si back",200,-1000,1000);
  Si->Add(h_e_SiFBdiff);
  TH2D *h_e_SiFB = new TH2D("h_e_SiFB","Si front vs back energy",4000,0,200000,4000,0,200000);
  Si->Add(h_e_SiFB);
  TH2D *h_p_Si = new TH2D("h_p_Si","Si hit position",32,0,32,32,0,32);
  Si->Add(h_p_Si);
  TH1I *h_e_SiGood = new TH1I("h_e_SiGood","Calibrated energy Si good hits",4000,0,200000);
  Si->Add(h_e_SiGood);
  TH1I *h_e_SiGood_cen = new TH1I("h_e_SiGood_cen","Calibrated energy (center) Si good hits",4000,0,200000);
  Si->Add(h_e_SiGood_cen);
  TH1I *h_e_SiGood_edg = new TH1I("h_e_SiGood_edg","Calibrated energy (edge) Si good hits",4000,0,200000);
  Si->Add(h_e_SiGood_edg);
  TH2D *h_p_SiGood = new TH2D("h_p_SiGood","Si hit position for good hits",32,0,32,32,0,32);
  Si->Add(h_p_SiGood);

  // LENDA histograms
  TList *LENDA = new TList(); // Add every new histogram to this list!!!
  TH1D *h_m_LENDA_T = new TH1D("h_m_LENDA_T","LENDA top multiplicity",21,0,21);
  LENDA->Add(h_m_LENDA_T);
  TH1D *h_e_LENDA_T = new TH1D("h_e_LENDA_T","Energy LENDA top pmt",4000,0,200000);
  LENDA->Add(h_e_LENDA_T);
  TH1D *h_t_LENDA_T = new TH1D("h_t_LENDA_T","Timing LENDA top pmt",4000,0,2E11);
  LENDA->Add(h_t_LENDA_T);
  TH1D *h_m_LENDA_B = new TH1D("h_m_LENDA_B","LENDA bottom multiplicity",21,0,21);
  LENDA->Add(h_m_LENDA_B);
  TH1D *h_e_LENDA_B = new TH1D("h_e_LENDA_B","Energy LENDA bottom",4000,0,200000);
  LENDA->Add(h_e_LENDA_B);
  TH1D *h_t_LENDA_B = new TH1D("h_t_LENDA_B","Timing LENDA bottom pmt",4000,0,2E11);
  LENDA->Add(h_t_LENDA_B);
  TH1D *h_e_LENDA_ave = new TH1D("h_e_LENDA_ave","Average Energy LENDA bar",4000,0,200000);
  LENDA->Add(h_e_LENDA_ave);
  TH2D *h_eb_LENDA = new TH2D("h_eb_LENDA","Average Energy vs LENDA bar",4000,0,200000,21,0,21);
  LENDA->Add(h_eb_LENDA);
  TH1D *h_t_LENDA_diff = new TH1D("h_t_LENDA_diff","LENDA time Top vd Bottom",2000,-2000,2000);
  LENDA->Add(h_t_LENDA_diff);

  // IC histograms
  TList *IC = new TList();
  TH1D *h_m_IC_dE = new TH1D("h_m_IC_dE","IC_dE multiplicity",20,0,20);
  IC->Add(h_m_IC_dE);
  TH1D *h_e_IC_dE = new TH1D("h_e_IC_dE","calibrated IC dE",4000,0,200000);
  IC->Add(h_e_IC_dE);

  // MCP histograms
  TList *MCP = new TList();
  TH1D *h_m_UMCPt = new TH1D("h_m_UMCPt","MCP timing multiplicity",20,0,20);
  MCP->Add(h_m_UMCPt);

  // Si - IC conincidence histograms
  TList *IC_Si = new TList();
  TH2D *h_pid = new TH2D("h_pid","IC_dE vs Si",4000,0,200000,4000,0,200000);//4500,0,4500,3500,0,3500);
  IC_Si->Add(h_pid);
  TH2D *h_pid_corr = new TH2D("h_pid_corr","IC_dE vs Si, edge effect corrected",4000,0,200000,4000,0,200000);//4500,0,4500,3500,0,3500);
  IC_Si->Add(h_pid_corr);
  TH2D *h_pid_cen = new TH2D("h_pid_cen","IC_dE vs Si center",4000,0,200000,4000,0,200000);//4500,0,4500,3500,0,3500);
  IC_Si->Add(h_pid_cen);
  TH2D *h_pid_edg = new TH2D("h_pid_edg","IC_dE vs Si edge",4000,0,200000,4000,0,200000);//4500,0,4500,3500,0,3500);
  IC_Si->Add(h_pid_edg);
  TH2D *h_pid_edg_corr = new TH2D("h_pid_edg_corr","IC_dE vs Si edge (energy corrected)",4000,0,200000,4000,0,200000);//4500,0,4500,3500,0,3500);
  IC_Si->Add(h_pid_edg_corr);
  TH1D *h_e_Si_coin_dE = new TH1D("h_e_Si_coin_dE","Si energy with dE>0",4000,0,200000);
  IC_Si->Add(h_e_Si_coin_dE);
  TH1D *h_e_Si_coin_dE_cen = new TH1D("h_e_Si_coin_dE_cen","Si energy (center) with dE>0",4000,0,200000);
  IC_Si->Add(h_e_Si_coin_dE_cen);
  TH1D *h_e_Si_coin_dE_edg = new TH1D("h_e_Si_coin_dE_edg","Si energy (edge) with dE>0",4000,0,200000);
  IC_Si->Add(h_e_Si_coin_dE_edg);
  TH2D *h_Si_hit1a = new TH2D("h_Si_hit1a","FP Si hit pattern on blob 1a",32,0,32,32,0,32);
  IC_Si->Add(h_Si_hit1a);
  TH2D *h_Si_hit1b = new TH2D("h_Si_hit1b","FP Si hit pattern on blob 1b",32,0,32,32,0,32);
  IC_Si->Add(h_Si_hit1b);
  TH2D *h_Si_hit2 = new TH2D("h_Si_hit2","FP Si hit pattern on blob 2",32,0,32,32,0,32);
  IC_Si->Add(h_Si_hit2);

  // MCP - Si coincidence histograms
  TList *MCP_Si = new TList();
  TH1D *h_t_MCP_Si = new TH1D("h_t_MCP_Si","time difference between MCPs and Si",1000,0,4000);
  MCP_Si->Add(h_t_MCP_Si);
  TH2D *h_et_MCP_Si = new TH2D("h_et_MCP_Si","time difference between MCPs and Si vs Si energy",4000,0,200000,250,0,1000);
  MCP_Si->Add(h_et_MCP_Si);

  // LENDA - Si conincidence histograms
  TList *LENDA_Si = new TList();
  TH2D *h_et_LENDA_Si = new TH2D("h_et_LENDA_Si","time difference between MCPs and Si vs Si energy",4000,0,200000,2500,0,10000);
  LENDA_Si->Add(h_et_LENDA_Si);

  // MCP - IC - Si coincidence histograms
  TList *MCP_IC_Si = new TList();
  TH1D *h_t_MCP_Si1 = new TH1D("h_t_MCP_Si1","time difference between MCPs and Si gated on blob1 recoils",1000,0,4000);
  MCP_IC_Si->Add(h_t_MCP_Si1);
  TH1D *h_t_MCP_Si2 = new TH1D("h_t_MCP_Si2","time difference between MCPs and Si gated on blob2 recoils",1000,0,4000);
  MCP_IC_Si->Add(h_t_MCP_Si2);
  TH1D *h_t_MCP_Si3 = new TH1D("h_t_MCP_Si3","time difference between MCPs and Si gated on dE>0",1000,0,4000);
  MCP_IC_Si->Add(h_t_MCP_Si3);
  TH2D *h_pid_MCP = new TH2D("h_pid_MCP","pid with MCP signal",4000,0,200000,4000,0,200000);
  MCP_IC_Si->Add(h_pid_MCP);
  TH2D *h_ICdE_SiMCPtime = new TH2D("h_ICdE_SiMCPtime","MCP-Si time vs IC_dE energy",4000,0,200000,250,0,1000);
  MCP_IC_Si->Add(h_ICdE_SiMCPtime);
  TH2D *h_ICdE_SiMCPtime_SiEGate = new TH2D("h_ICdE_SiMCPtime_SiEGate","MCP-Si time vs IC_dE energy with Si E > 25000",4000,0,200000,250,0,1000);
  MCP_IC_Si->Add(h_ICdE_SiMCPtime_SiEGate);
//-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-//

//=====================================================================//
//================================ Cuts ===============================//
//=====================================================================//

  // Upper and lower limits on Si and IC_dE energies for pid blobs
  int blob1a_Si[2], blob1a_dE[2], blob1b_Si[2], blob1b_dE[2], blob2_Si[2], blob2_dE[2];
  int BGO_Si_time[2], MCP_Si_time[2];
  ifstream f_limits("limits.dat");
  int temp[17];
  while(!f_limits.eof()){
    f_limits >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4] >> temp[5] >> temp[6] >> temp[7] >> temp[8] >> temp[9] >> temp[10] >> temp[11] >> temp[12] >> temp[13] >> temp[14] >> temp[15] >> temp[16];
    if(temp[0]==run){
      for(int i=0; i<2; i++){
        blob1a_Si[i] = temp[i+1];
        blob1a_dE[i] = temp[i+3];
        blob1b_Si[i] = temp[i+5];
        blob1b_dE[i] = temp[i+7];
        blob2_Si[i] = temp[i+9];
        blob2_dE[i] = temp[i+11];
        BGO_Si_time[i] = temp[i+13];
        MCP_Si_time[i] = temp[i+15];
      }
      break;
    }
  }
  f_limits.close();

  // These following bool variables are used for applying event selection condition when filling histograms.
  bool pid_blob1a, pid_blob1b, pid_blob2, time_BGO_Si, time_MCP_Si;

  // Purpose of the following TCutG (graphical cuts) is just to have visual on the cuts.
  TList *cuts = new TList();
  TCutG *cut_blob1a = graphicalCut(blob1a_Si, blob1a_dE, "cut_blob1a");
  cuts->Add(cut_blob1a);
  TCutG *cut_blob1b = graphicalCut(blob1b_Si, blob1b_dE, "cut_blob1b");
  cuts->Add(cut_blob1b);
  TCutG *cut_blob2 = graphicalCut(blob2_Si, blob2_dE, "cut_blob2");
  cuts->Add(cut_blob2);
//-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-//

  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  int previous = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    // Print out progress
    int progress = jentry*100/nentries;
    if(progress>previous){
      cout << "Progress = " << progress << "% " << '\r' << flush;
      previous=progress;
    }

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    mcpHit = sortMCPHits(mult_UMCP_t, time_UMCP_t);
    icHit = sortICHits(mult_IC_dE, energy_IC_dE, time_IC_dE, IC_dE_gain, IC_dE_offset);
    SiHit = sortSiHits(mult_Si, energy_Si, chan_Si, time_Si, Si_side, Si_strip, Si_gain, Si_offset, 2500);
    LENDAHit = sortLENDAHits(mult_LENDA, energy_LENDA, chan_LENDA, time_LENDA, side_LENDA, bar_LENDA);

//=========Multiplicity histograms=========//
    h_m_SiF->Fill(SiHit.strip_F.size());
    h_m_SiB->Fill(SiHit.strip_B.size());
    h_m_LENDA_T->Fill(LENDAHit.pmt_T.size());
    h_m_LENDA_B->Fill(LENDAHit.pmt_B.size());
    h_m_IC_dE->Fill(mult_IC_dE);
    h_m_UMCPt->Fill(mult_UMCP_t);

//=============Si histograms===============//
    if(mult_Si>0 && mult_Si<72){
      for(int i=0; i<SiHit.strip_F.size(); i++){
        h_e_SiF->Fill(SiHit.energyCal_F[i]);
        h_ep_SiF->Fill(SiHit.energyCal_F[i], SiHit.strip_F[i]);
        for(int j=0; j<SiHit.strip_B.size(); j++){
          h_e_SiFB->Fill(SiHit.energyCal_F[i],SiHit.energyCal_B[j]);
          h_e_SiFBdiff->Fill(SiHit.energyCal_F[i]-SiHit.energyCal_B[j]);
          h_p_Si->Fill(SiHit.strip_F[i],SiHit.strip_B[j]);
        }
      }
      for(int i=0; i<SiHit.strip_B.size(); i++){
        h_e_SiB->Fill(SiHit.energyCal_B[i]);
        h_ep_SiB->Fill(SiHit.energyCal_B[i], SiHit.strip_B[i]);
      }
      for(int i=0; i<SiHit.energyCal_Good.size(); i++){
        h_e_SiGood->Fill(SiHit.energyCal_Good[i]);
        h_p_SiGood->Fill(SiHit.strip_GoodF[i],SiHit.strip_GoodB[i]);
        if(SiHit.strip_GoodF[i]>2 && SiHit.strip_GoodF[i]<26 && SiHit.strip_GoodB[i]>2 && SiHit.strip_GoodB[i]<26) h_e_SiGood_cen->Fill(SiHit.energyCal_Good[i]);
        else h_e_SiGood_edg->Fill(SiHit.energyCal_Good[i]);
      }
    }

//=============LENDA histograms===============//
  if(mult_LENDA>1 && mult_LENDA<42){
  	if(LENDAHit.pmt_T.size()>0){
  		for(int i=0; i<LENDAHit.pmt_T.size(); i++){
        h_e_LENDA_T->Fill(LENDAHit.energy_T[i]);
        h_t_LENDA_T->Fill(LENDAHit.time_T[i]);
  		}
  	}
  	if(LENDAHit.pmt_B.size()>0){
  		for(int i=0; i<LENDAHit.pmt_B.size(); i++){
        h_e_LENDA_B->Fill(LENDAHit.energy_B[i]);
        h_t_LENDA_B->Fill(LENDAHit.time_B[i]);
  			if(LENDAHit.pmt_T.size()>0){
  				for(int j=0; j<LENDAHit.pmt_T.size(); j++){
            if(LENDAHit.pmt_T[j]==LENDAHit.pmt_B[i]) h_t_LENDA_diff->Fill(LENDAHit.time_T[j]-LENDAHit.time_B[i]);
  				}
  			}
  		}
  	}
    for(int i=0; i<LENDAHit.energyGood.size(); i++){
      h_e_LENDA_ave->Fill(LENDAHit.energyGood[i]);
    }
  }

//=============IC histograms===============//
    if(mult_IC_dE>0 && mult_IC_dE<28){
      for(int i=0; i<mult_IC_dE; i++){
        if(icHit.energyCal[i]>0) h_e_IC_dE->Fill(icHit.energyCal[i]);
      }
    }

//==========coincidence histograms==========//
    if(SiHit.energyCal_Good.size()>0){
      for(int i=0; i<SiHit.energyCal_Good.size(); i++){
        if(icHit.energyCal.size()>0){
  //==========Si IC coincidence==========//
          h_e_Si_coin_dE->Fill(SiHit.energyCal_Good[i]);
          for(int j=0; j<icHit.energyCal.size(); j++){
            h_pid->Fill(SiHit.energyCal_Good[i],icHit.energyCal[j]);
            if(SiHit.strip_GoodF[i]>5 && SiHit.strip_GoodF[i]<26 && SiHit.strip_GoodB[i]>5 && SiHit.strip_GoodB[i]<26){
              h_pid_cen->Fill(SiHit.energyCal_Good[i],icHit.energyCal[j]);
              h_pid_corr->Fill(SiHit.energyCal_Good[i],icHit.energyCal[j]);
            }
            else{
              h_pid_edg->Fill(SiHit.energyCal_Good[i],icHit.energyCal[j]);
              h_pid_edg_corr->Fill(SiHit.energyCal_Good[i],icHit.energyCal[j]/0.82);
              h_pid_corr->Fill(SiHit.energyCal_Good[i],icHit.energyCal[j]/0.82);
            }

            pid_blob1a = SiHit.energyCal_Good[i] > blob1a_Si[0] && SiHit.energyCal_Good[i] < blob1a_Si[1] && icHit.energyCal[j] > blob1a_dE[0] && icHit.energyCal[j] < blob1a_dE[1];
            pid_blob1b = SiHit.energyCal_Good[i] > blob1b_Si[0] && SiHit.energyCal_Good[i] < blob1b_Si[1] && icHit.energyCal[j] > blob1b_dE[0] && icHit.energyCal[j] < blob1b_dE[1];
            pid_blob2 = SiHit.energyCal_Good[i] > blob2_Si[0] && SiHit.energyCal_Good[i] < blob2_Si[1] && icHit.energyCal[j] > blob2_dE[0] && icHit.energyCal[j] < blob2_dE[1];

            if(pid_blob1a) h_Si_hit1a->Fill(SiHit.strip_GoodF[i],SiHit.strip_GoodB[j]);
            else if(pid_blob1b) h_Si_hit1b->Fill(SiHit.strip_GoodF[i],SiHit.strip_GoodB[j]);
            else if(pid_blob2) h_Si_hit2->Fill(SiHit.strip_GoodF[i],SiHit.strip_GoodB[j]);

    //==========Si IC MCP coincidence==========//
            if(mcpHit.time.size()>0){
              for(int k=0; k<mcpHit.time.size(); k++){
                if(pid_blob1a || pid_blob1b) h_t_MCP_Si1->Fill(SiHit.time_Good[i]-mcpHit.time[k]);
                else if(pid_blob2) h_t_MCP_Si2->Fill(SiHit.time_Good[i]-mcpHit.time[k]);
                h_t_MCP_Si3->Fill(SiHit.time_Good[i]-mcpHit.time[k]);
                h_pid_MCP->Fill(SiHit.energyCal_Good[i],icHit.energyCal[j]);
                h_ICdE_SiMCPtime->Fill(icHit.energyCal[j],SiHit.time_Good[i]-mcpHit.time[k]);
		            if(SiHit.energyCal_Good[i]>blob1a_Si[0]) h_ICdE_SiMCPtime_SiEGate->Fill(icHit.energyCal[j],SiHit.time_Good[i]-mcpHit.time[k]);
              }
            }
          }
        }
  //==========Si MCP coincidence==========//
        if(mcpHit.time.size()>0){
          for(int j=0; j<mcpHit.time.size(); j++){
            h_t_MCP_Si->Fill(SiHit.time_Good[i]-mcpHit.time[j]);
            h_et_MCP_Si->Fill(SiHit.energyCal_Good[i], SiHit.time_Good[i]-mcpHit.time[j]);
          }
        }
  //==========Si LENDA coincidence==========//
        if(LENDAHit.barGood.size()>0){
          for(int j=0; j<LENDAHit.barGood.size(); j++){
            h_et_LENDA_Si->Fill(SiHit.energyCal_Good[i], SiHit.time_Good[i]-LENDAHit.timeGood[j]);
          }
        }
      }
    }
  }
  TFile *fout = new TFile(fileOutName,"recreate");

  Si->Write("Si",TObject::kSingleKey);
  LENDA->Write("LENDA",TObject::kSingleKey);
  IC->Write("IC",TObject::kSingleKey);
  MCP->Write("MCP",TObject::kSingleKey);
  IC_Si->Write("IC_Si",TObject::kSingleKey);
  MCP_Si->Write("MCP_Si",TObject::kSingleKey);
  MCP_IC_Si->Write("MCP_IC_Si",TObject::kSingleKey);
  cuts->Write("cuts",TObject::kSingleKey);

  fout->Close();

  Si->Delete();
  LENDA->Delete();
  IC->Delete();
  MCP->Delete();
  IC_Si->Delete();
  MCP_Si->Delete();
  MCP_IC_Si->Delete();
  cuts->Delete();

  fout->Delete();
}
