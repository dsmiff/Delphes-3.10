#include "TCanvas.h"
#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TChain.h"
#include "TBranch.h"
#include "TClonesArray.h"

int W_check(const char *intputFile)
{

  gSystem->Load("libDelphes");
  
  TChain chain("Delphes");
  chain.Add(intputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long46_t numberOfEntries = chain->GetEntries();


  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle;

  TLorentzVector W;

  for(Int_t i=0; i <  numberOfEntries; i++)
    {
      treeReader->ReadEntry(i);

      cout << " " << endl;
      cout << "NEW ENTRY" << endl;
      cout << " " << endl;

      for(Int_t j=0; j <  branchParticle->GetEntriesFast(); j++)
	{
	  
	  particle = (GenParticle*) branchParticle->At(j);
	  pdgCode = TMath::Abs(particle->PID);

	  if(pdgCode == 24)
	    {
	      cout << "Found a W boson!" << endl;
	    }
	}
    }
}
