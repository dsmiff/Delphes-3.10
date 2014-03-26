// This macro investigates the bug with the MC-@NLO dataset in that it replicates W and b quarks. 


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
  Long64_t numberOfEntries = treeReader->GetEntries();

  Long64_t nw = 0;
  Long64_t nb = 0;


  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle;
  GenParticle *Mother;

  for(Int_t i=0; i <  numberOfEntries; i++)
    {
      treeReader->ReadEntry(i);

      nb = 0;
      nw = 0;

      cout << " " << endl;
      cout << "NEW ENTRY" << endl;
      cout << " " << endl;

      for(Int_t j=0; j <  branchParticle->GetEntriesFast(); j++)
	{
	  particle = (GenParticle*) branchParticle->At(j);
	  pdgCode = TMath::Abs(particle->PID);
	  motherIndex = particle->M1;
	  Mother = (GenParticle*) branchParticle->At(motherIndex);
	 
	  if(pdgCode == 24)
	    {
	      cout << "\nFound a W boson!" << endl;
	      cout << "----> Mother index: " << motherIndex << endl;
	      cout << "--------> Mother pdg: " << Mother->PID << endl;
	      nw++;
	      if(TMath::Abs(Mother->PID) == 6){
		cout <<  "-------------> W comes from a top" << endl;
	      }
   	    }
	
	  else if(pdgCode == 5)
	    {
	      cout << "Found a b quark!" << endl;
	      cout << "------> Mother index: "<< motherIndex << endl;
	      cout << "- --------> Mother pdg: " << Mother->PID << endl;
	      nb++;
	      if(TMath::Abs(Mother->PID) == 6){
		cout << "------------------> b comes from a top" << endl;
	      }

	    }
	  
	  if(nb == nw){
	    //	    cout << "Equal amount of Ws and bs" << endl;
	  }

	  else if(pdgCode == 11)
	    {
	      cout << "Found an electron" << endl;
	    }
	  else if(pdgCode == 13)
	    {
	      cout << "Found a muon" << endl;
	    }

	  else if(pdgCode == 6)
	    {
	      cout << "Found a top quark" << endl;
	    }
	}


    }
}
