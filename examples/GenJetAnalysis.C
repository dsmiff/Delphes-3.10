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
  TFile *f = new TFile("../delphes_MG_TEST.root");
  TTree *fChain = (TTree*)f->Get("Delphes");

  TBranch *j = fChain->GetBranch("GenJet.PT");
  fChain->SetMakeClass(1);
  fChain->SetBranchAddress("GenJet",&len);
  j->SetAddress(&PT);



  Long64_t numberOfEntries = fChain->GetEntries();


  cout << "Entries : " << numberOfEntries << endl;

  // Problem here

  for(int k=0; k<numberOfEntries; k++)
    {
      fChain->GetEntry(k);
      cout << "NEW EVENT [" << k << " of " << numberOfEntries << "] " << endl;
    }
  
  
  for(int i=0; i<5; i++)
    {
     
      j->GetEntry(i);
      cout << " PT : " << PT << endl;

      
    }



}
