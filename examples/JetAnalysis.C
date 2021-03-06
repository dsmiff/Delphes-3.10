/*
Macro to analyse only Jet properties on a Delphes ROOT output
Dominic Smith 
Febuary 2014

To run: 

root -l examples/JetAnalysis\(\"delphes_file.root\"\)

*/

//------------------------------

#include "TFile.h"
#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "TClonesArray.h"




void JetAnalysis(const char *intputFile)
{

  gSystem->Load("libDelphes");
  
  // Create chain of ROOT trees

  TChain chain("Delphes");
  chain.Add(intputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();


  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchGenJet = treeReader->UseBranch("GenJet");
  //  TClonesArray *branchScalarHT = treeReader->UseBranch("ScalarHT");



  // Declaring histos
  
  TH1 *histJetPT = new TH1F("Jet_PT", "Jet P_{T}", 100, 0.0, 500.0);
  TH1 *histGenMass = new TH1F("GenJetMass","GenJetMass", 200, 0, 100);
  TH1 *histJetEta = new TH1F("Jet_Eta", "Jet_Eta", 50, -4, 4);
  TH1 *histJetPhi = new TH1F("Jet_Phi", "Jet_Phi", 50, 0, 7);
  TH1 *histGenJetPT = new TH1F("GenJet_PT", "GenJet_P{T}", 100, 0.0, 100.0);
  TH1 *JetMass = new TH1F("JetMass","Jet Mass",200, -100, 200);
  TH2 *JetMassvsPT = new TH2F("JetMassvsPT","JetMassvsPT",200, 0, 400, 200, 0, 50);
  TH2 *GenJetMassvsPT = new TH2F("GenMassvsPT","GenMassvsPT",200, 0, 400, 200, -50, 300);

  for(Int_t i=0; i < numberOfEntries; i++)
    {
      treeReader->ReadEntry(i);
      int JetPT;

      cout << "\n***************************" << endl;
      cout << "\nNEW EVENT [" << i << "]"<< endl;
      
	for(Int_t j=0; j < branchJet->GetEntriesFast(); j++)
	  {

	    Jet *jet = (Jet*) branchJet->At(j);
	    histJetPT->Fill(jet->PT);
	    //	    cout << "Jet Mass: " << jet->Mass << endl;
	    JetMass->Fill(jet->Mass);
	    JetMassvsPT->Fill(jet->PT,jet->Mass);
	    //	    cout << jet->PT << endl;
	    // ScalarHT *ht = (ScalarHT*) branchScalarHT->At(j);
	    // cout << ht->HT << endl;
	  }
	for(Int_t k=0; k < branchGenJet->GetEntriesFast(); k++)
	  {
	    
	    Jet *genjet = (Jet*) branchGenJet->At(k);
	    histGenMass->Fill(genjet->Mass);
	    histGenJetPT->Fill(genjet->PT);
	  
	    GenJetMassvsPT->Fill(genjet->PT,genjet->Mass);
	    
	    
	  }



       
       


    }

  TFile *JetAnalysis = new TFile("JetAnalysis.root","RECREATE");
  histJetPT->Write();
  JetMass->Write();
  JetMassvsPT->Write();
  histGenMass->Write();
  GenJetMassvsPT->Write();
  histGenJetPT->Write();
  JetAnalysis->Close();

}
