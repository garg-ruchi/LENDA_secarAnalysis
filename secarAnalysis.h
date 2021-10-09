//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 30 21:09:48 2021 by ROOT version 6.22/08
// from TTree t/FP Tree
// found on file: /Users/ruchigarg/Desktop/SECAR/test_run0618-00_10us.root
//////////////////////////////////////////////////////////

#ifndef secarAnalysis_h
#define secarAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "graphicalCut.C"
#include "sortBGOHits.C"
#include "sortMCPHits.C"
#include "sortICHits.C"
#include "sortSiHits.C"
#include "sortLENDAHits.C"
#include "sortLSciHits.C"

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class secarAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<double> *time_RFQ_JENSA;

   vector<int>     *energy_Pulser_JENSA;
   vector<double>  *time_Pulser_JENSA;

   vector<int>     *energy_SiMon1;
   vector<double>  *time_SiMon1;
   Int_t           mult_SiMon1;
   vector<int>     *energy_SiMon2;
   vector<double>  *time_SiMon2;
   Int_t           mult_SiMon2;

   vector<int>     *chan_LENDA;
   vector<int>     *energy_LENDA;
   vector<double>  *time_LENDA;
   Int_t           mult_LENDA;

   vector<int>     *chan_LScin;
   vector<int>     *energy_LScin;
   vector<double>  *time_LScin;
   Int_t           mult_LScin;

   vector<int>     *energy_UMCP_t;
   vector<double>  *time_UMCP_t;
   Int_t           mult_UMCP_t;

   vector<int>     *energy_IC_dE;
   vector<double>  *time_IC_dE;
   Int_t           mult_IC_dE;

   vector<int>     *chan_Si;
   vector<int>     *energy_Si;
   vector<double>  *time_Si;
   Int_t           mult_Si;

   vector<int>     *energy_Pulser_FP;
   vector<double>  *time_Pulser_FP;
   Double_t        tmax;
   Double_t        trigger;

   // List of branches
   TBranch        *b_time_RFQ_JENSA;

   TBranch        *b_energy_Pulser_JENSA;   //!
   TBranch        *b_time_Pulser_JENSA;   //!

   TBranch        *b_energy_SiMon1;   //!
   TBranch        *b_time_SiMon1;   //!
   TBranch        *b_m_SiMon1;   //!
   TBranch        *b_energy_SiMon2;   //!
   TBranch        *b_time_SiMon2;   //!
   TBranch        *b_m_SiMon2;   //!

   TBranch        *b_chan_LENDA;   //!
   TBranch        *b_energy_LENDA;   //!
   TBranch        *b_time_LENDA;   //!
   TBranch        *b_m_LENDA;   //!

   TBranch        *b_chan_LScin;   //!
   TBranch        *b_energy_LScin;   //!
   TBranch        *b_time_LScin;   //!
   TBranch        *b_m_LScin;   //!

   TBranch        *b_energy_UMCP_t;   //!
   TBranch        *b_time_UMCP_t;   //!
   TBranch        *b_m_UMCP_t;   //!

   TBranch        *b_energy_IC_dE;   //!
   TBranch        *b_time_IC_dE;   //!
   TBranch        *b_m_IC_dE;   //!

   TBranch        *b_chan_Si;   //!
   TBranch        *b_energy_Si;   //!
   TBranch        *b_time_Si;   //!
   TBranch        *b_m_Si;   //!

   TBranch        *b_energy_Pulser_FP;   //!
   TBranch        *b_time_Pulser_FP;   //!
   TBranch        *b_tmax;   //!
   TBranch        *b_time;   //!

   secarAnalysis(TTree *tree=0);
   virtual ~secarAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString fileOutName, int run);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

};

#endif

#ifdef secarAnalysis_cxx
secarAnalysis::secarAnalysis(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   Init(tree);
}

secarAnalysis::~secarAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t secarAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t secarAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void secarAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   time_RFQ_JENSA = 0;

   energy_Pulser_JENSA = 0;
   time_Pulser_JENSA = 0;

   energy_SiMon1 = 0;
   time_SiMon1 = 0;
   energy_SiMon2 = 0;
   time_SiMon2 = 0;

   chan_LENDA = 0;
   energy_LENDA = 0;
   time_LENDA = 0;

   chan_LScin = 0;
   energy_LScin = 0;
   time_LScin = 0;

   energy_UMCP_t = 0;
   time_UMCP_t = 0;

   energy_IC_dE = 0;
   time_IC_dE = 0;

   chan_Si = 0;
   energy_Si = 0;
   time_Si = 0;

   energy_Pulser_FP = 0;
   time_Pulser_FP = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("time_RFQ_JENSA", &time_RFQ_JENSA, &b_time_RFQ_JENSA);

   fChain->SetBranchAddress("energy_Pulser_JENSA", &energy_Pulser_JENSA, &b_energy_Pulser_JENSA);
   fChain->SetBranchAddress("time_Pulser_JENSA", &time_Pulser_JENSA, &b_time_Pulser_JENSA);

   fChain->SetBranchAddress("energy_SiMon1", &energy_SiMon1, &b_energy_SiMon1);
   fChain->SetBranchAddress("time_SiMon1", &time_SiMon1, &b_time_SiMon1);
   fChain->SetBranchAddress("mult_SiMon1", &mult_SiMon1, &b_m_SiMon1);
   fChain->SetBranchAddress("energy_SiMon2", &energy_SiMon2, &b_energy_SiMon2);
   fChain->SetBranchAddress("time_SiMon2", &time_SiMon2, &b_time_SiMon2);
   fChain->SetBranchAddress("mult_SiMon2", &mult_SiMon2, &b_m_SiMon2);

   fChain->SetBranchAddress("chan_LENDA", &chan_LENDA, &b_chan_LENDA);
   fChain->SetBranchAddress("energy_LENDA", &energy_LENDA, &b_energy_LENDA);
   fChain->SetBranchAddress("time_LENDA", &time_LENDA, &b_time_LENDA);
   fChain->SetBranchAddress("mult_LENDA", &mult_LENDA, &b_m_LENDA);

   fChain->SetBranchAddress("chan_LScin", &chan_LScin, &b_chan_LScin);
   fChain->SetBranchAddress("energy_LScin", &energy_LScin, &b_energy_LScin);
   fChain->SetBranchAddress("time_LScin", &time_LScin, &b_time_LScin);
   fChain->SetBranchAddress("mult_LScin", &mult_LScin, &b_m_LScin);

   fChain->SetBranchAddress("energy_UMCP_t", &energy_UMCP_t, &b_energy_UMCP_t);
   fChain->SetBranchAddress("time_UMCP_t", &time_UMCP_t, &b_time_UMCP_t);
   fChain->SetBranchAddress("mult_UMCP_t", &mult_UMCP_t, &b_m_UMCP_t);

   fChain->SetBranchAddress("energy_IC_dE", &energy_IC_dE, &b_energy_IC_dE);
   fChain->SetBranchAddress("time_IC_dE", &time_IC_dE, &b_time_IC_dE);
   fChain->SetBranchAddress("mult_IC_dE", &mult_IC_dE, &b_m_IC_dE);

   fChain->SetBranchAddress("chan_Si", &chan_Si, &b_chan_Si);
   fChain->SetBranchAddress("energy_Si", &energy_Si, &b_energy_Si);
   fChain->SetBranchAddress("time_Si", &time_Si, &b_time_Si);
   fChain->SetBranchAddress("mult_Si", &mult_Si, &b_m_Si);

   fChain->SetBranchAddress("energy_Pulser_FP", &energy_Pulser_FP, &b_energy_Pulser_FP);
   fChain->SetBranchAddress("time_Pulser_FP", &time_Pulser_FP, &b_time_Pulser_FP);

   fChain->SetBranchAddress("tmax", &tmax, &b_tmax);
   fChain->SetBranchAddress("trigger", &trigger, &b_time);
   Notify();
}

Bool_t secarAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void secarAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t secarAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef secarAnalysis_cxx
