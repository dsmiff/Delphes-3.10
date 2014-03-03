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
  
  TH1 *histJetPT = new TH1F("Jet_PT", "Jet P_{T}", 100, 0.0, 100.0);
  TH1 *histJetEta = new TH1F("Jet_Eta", "Jet_Eta", 50, -4, 4);
  TH1 *histJetPhi = new TH1F("Jet_Phi", "Jet_Phi", 50, 0, 7);
  TH1 *histGenJetPT = new TH1F("GenJet_PT", "GenJet_P{T}", 100, 0.0, 100.0);


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
	    cout << jet->PT << endl;
	    // ScalarHT *ht = (ScalarHT*) branchScalarHT->At(j);
	    // cout << ht->HT << endl;
  }
       
       


    }

  TFile *JetAnalysis = new TFile("JetAnalysis.root","RECREATE");
  histJetPT->Write();
  //histGenJetPT->Write();

}
