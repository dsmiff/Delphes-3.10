#include "TCanvas.h"
#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TChain.h"
#include "TBranch.h"
#include "TClonesArray.h"

int GenAnalysis(const char *intputFile)
{

  gSystem->Load("libDelphes");
  
  TChain chain("Delphes");
  chain.Add(intputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  TClonesArray *branchGenJet = treeReader->UseBranch("GenJet");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  

  TH1 *histGenJetPT = new TH1F("histGenJetPT", "histGenJetPT", 100, 0.0, 100);
  


  for(Int_t i=0; i < numberOfEntries; i++)
    {
      
      treeReader->ReadEntry(i);
      int GenJetPT;
      
      cout << "\n*************************************" << endl;
      cout << "\nNEW EVENT [" << i << "] " << endl;
      

      for(Int_t j=0; j < branchJet->GetEntriesFast(); j++)
	{
	  
	  Jet *genjet = (Jet*) branchGenJet->At(j);
	  histGenJetPT->Fill(genjet->PT);
	  
	  cout << "Gen Jet PT: " << genjet->PT << endl;
	}
    }



}
