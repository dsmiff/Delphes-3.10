#include "TLorentzVector.h"
#include <vector>
#include <algorithm>

struct TestPlots
{
  TH1 *_JetPT;
  TH1 *_SubJetPT;
  TH1 *_SubJetPT2;

};




//------------------------------------------------------------------------------

class ExRootResult;
class ExRootTreeReader;

//------------------------------------------------------------------------------

void BookHistograms(ExRootResult *result, TestPlots *plots)
{
  TLegend *legend;
  TPaveText *comment;


  plots->_JetPT = result->AddHist1D(
    "jet pt", "Jet P_{T}","Jet P_{T}", "Events",
    100, 0.0, 1000);

  plots->_SubJetPT = result->AddHist1D("subjet1 pt", "subjet1 pt", "P_{T}", "Events", 100, 0.0, 1000);
  plots->_SubJetPT2 = result->AddHist1D("subjet2 pt", "subjet2 pt", "P_{T}", "Events", 100, 0.0, 1000);
}

//------------------------------------------------------------------------------

void AnalyseEvents(ExRootTreeReader *treeReader, TestPlots *plots)
{

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchPhoton = treeReader->UseBranch("Photon");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");

  TClonesArray *branchEFlowTrack = treeReader->UseBranch("EFlowTrack");  // These 3 are used in finding reco jets
  TClonesArray *branchEFlowTower = treeReader->UseBranch("EFlowTower");  // 
  TClonesArray *branchEFlowMuon = treeReader->UseBranch("EFlowMuon");    // 
  TClonesArray *branchJet = treeReader->UseBranch("Jet");

  //  Long64_t allEntries = treeReader->GetEntries();
    Long64_t allEntries = 1000;


  cout << "** Chain contains " << allEntries << " events" << endl;

  GenParticle *particle;
  Electron *electron;
  Photon *photon;
  Muon *muon;

  Track *track;
  Tower *tower;

  Jet *jet;
  Jet *subjet[2];
  TObject *object;
  TObjArray *objects[2];

  TLorentzVector momentum;
  //  TLorentzVector momentum2;
  std::vector<TLorentzVector> Subjets;


  // Loop over all events
  for(Long64_t entry = 0; entry < allEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    std::cout << "\n ** NEW ENTRY ** : " << entry << std::endl;

    // Loop over all jets in event. Up to here successfully returns the PT of ecah jet per event 
    for(i = 0; i < branchJet->GetEntriesFast(); ++i)
    {
      
      std::cout << "\nNew jet" << std::endl;

      jet = (Jet*) branchJet->At(i);

      momentum.SetPxPyPzE(0.0, 0.0, 0.0, 0.0);
      //  momentum2.SetPxPyPzE(0.0,0.0,0.0,0.0);

      std::cout << "Jet Constituents: " << jet->Constituents.GetEntriesFast() << std::endl;

      plots->_JetPT->Fill(jet->PT);



      // Loop over all jet's constituents
      for(j = 0; j < jet->Constituents.GetEntriesFast(); ++j)
      {
        object = jet->Constituents.At(j);

	

        // Check if the constituent is accessible, if object exists then continue
	// Would want to push the different momentum TLorentzVectors into a vector


        if(object == 0) continue;
	

        if(object->IsA() == GenParticle::Class())
        {
          momentum += ((GenParticle*) object)->P4();
	  std::cout << "momentum:" << momentum.Pt() << std::endl;
	}
        else if(object->IsA() == Track::Class())
        {
          momentum += ((Track*) object)->P4();
	  std::cout << "momentum2: " << momentum.Pt() << std::endl;
        }
        else if(object->IsA() == Tower::Class())
        {
          momentum += ((Tower*) object)->P4();
	  std::cout << "momentum3 :" << momentum.Pt() << std::endl;
	  //  plots->_SubJetPT->Fill(momentum.Pt());
	  //	  Subjets.push_back(momentum);
	}
        else if(object->IsA() == Muon::Class())
        {
          momentum += ((Muon*) object)->P4();
	  std::cout << "momentum4: " << momentum.Pt() << std::endl;
        }

	Subjets.push_back(momentum);
      }
     
        std::cout << "PT: " << Subjets.at(0).Pt() << std::endl;
       	std::cout << "Jet PT : " << jet->PT << std::endl;
      
	Subjets.clear();
    }
  




  }
}

//------------------------------------------------------------------------------

void PrintHistograms(ExRootResult *result, TestPlots *plots)
{
  result->Print("png");
  std::cout << "JetPT entries: " << plots->_JetPT->GetEntries() << std::endl;
  std::cout << "Subjet entries: " << plots->_SubJetPT->GetEntries() << std::endl;

}

//------------------------------------------------------------------------------

void JetConstituents(const char *inputFile)
{
  gSystem->Load("libDelphes");

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);
  ExRootResult *result = new ExRootResult();

  TestPlots *plots = new TestPlots;

  BookHistograms(result, plots);

  AnalyseEvents(treeReader, plots);

  PrintHistograms(result, plots);

  result->Write("results.root");

  cout << "** Exiting..." << endl;

  delete plots;
  delete result;
  delete treeReader;
  delete chain;



}

//------------------------------------------------------------------------------
