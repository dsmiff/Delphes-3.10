//------------------------------------------------------------------------------
#include "TFile.h"
#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "TClonesArray.h"


void GenJetAnalysis()
{ 


  
  int len;
  static Float_t PT = 0;
  TFile *f = new TFile("../delphes_MG_NEW.root");
  TTree *t = (TTree*)f->Get("Delphes");

  TBranch *j = t->GetBranch("GenJet.PT");
  t->SetMakeClass(1);
  t->SetBranchAddress("GenJet",&len);
  j->SetAddress(&PT);



  Long64_t numberOfEntries = Delphes->GetEntries();

  
  for(int i=0; i<5; i++)
    {
      j->GetEntry(i);
      
      cout << " PT : " << PT << endl;

      
    }



}
