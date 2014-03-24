// Gen level jet consituents

struct TestPlots
{

  TH1 *_GenJetPT;


};

//---------------------------------

class ExRootResult;
class ExRootTreeReader;

//---------------------------------

void BookHistograms(ExRootResult *result, TestPlots *plots)
{

  TLegend *legend;
  TPaveText *comment;

  plots->_GenJetPT = result->AddHist1D("Gen jet P_{T}","Gen jet P_{T}","Gen jet P_{T}", "Events", 100, 0, 1000);

}

//---------------------------------

void AnalyseEvents(ExRootTreeReader *treeReader, TestPlots *plots)
{

  TClonesArray *branchGenJet = treeReader->UseBranch("GenJet");
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchPhoton = treeReader->UseBranch("Photon");
  TClonesArray *branchEFlowTrack = treeReader->UseBranch("EFlowTrack");
  TClonesArray *branchEFlowTower = treeReader->UseBranch("EFlowTower");
  TClonesArray *branchEFlowMuon = treeReader->UseBranch("EFlowMuon");
  
  Long64_t allEntries = treeReader->GetEntries();
  
  cout << "** Chain contains " << allEntries << " events" << endl;

  GenParticle *particle;
  Electron *electron;
  Photon *photon;
  Muon *muon;
  
  Track *track;
  Tower *tower;
  
  Jet *jet;
  Jet *genjet;
  
  TObject *object;
  
  TLorentzVector genparticles;
  TLorentzVector momentum;


  for(Long64_t entry = 0; entry < allEntries; ++entry)
    {

      treeReader->ReadEntry(entry);
      
      std::cout << "\n NEW ENTRY : " << entry << std::endl;

      for(Int_t i = 0; i < branchGenJet->GetEntriesFast(); ++i)
	{
	  
	  std::cout << "\nNew jet" << std::endl;

	  genjet = (Jet*) branchGenJet->At(i);

	  std::cout << "Gen jet constituents: " << genjet->Constituents.GetEntriesFast() << std::endl;
	}
    }
}

//-----------------------------------------

void PrintHistograms(ExRootResult *result, TestPlots *plots)
{
  result->Print("png");
  std::cout << "GenJet entries : " << plots->_GenJetPT->GetEntries() << std::endl;
}

//-----------------------------------------

void GenJetConstituents(const char *intputFile)
{

  gSystem->Load("libDelphes");
  
  TChain *chain = new TChain("Delphes");
  chain->Add(intputFile);
  
  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);
  ExRootResult *result = new ExRootResult();
  
  TestPlots *plots = new TestPlots;
  
  BookHistograms(result, plots);
  
  AnalyseEvents(treeReader, plots);
  
  PrintHistograms(result,plots);
  
  result->Write("genresults.root");
  
  delete plots;
  delete result;
  delete treeReader;
  delete chain;
  
}







