class ExRootResult;
class ExRootTreeReader;


void AnalyseEvents(ExRootTreeReader *treeReader)
{

  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchPhoton = treeReader->UseBranch("Photon");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");

  // Pick out branches used in reco jet finding

  TClonesArray *branchEFlowTrack = treeReader->UseBranch("EFlowTrack");   
  TClonesArray *branchEFlowTower = treeReader->UseBranch("EFlowTower");
  TClonesArray *branchEFlowMuon = treeReader->UseBranch("EFlowMuon");   // Muons get filtered out in Unique object finding so should be included in jet finding
 
  // Pick out reco jet branch
  
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  
  Long64_t allEntries = treeReader->GetEntries();
  
  std::cout << " ** Chain contains: " << allEntries << " events" << std::endl;

  GenParticle *particle;
  Electron *electron;
  Photon *photon;
  Muon *muon;
  
  Track *track;
  Tower *tower;

  Jet *jet;
  TObject *object;


  TLorentzVector momentum;

  // Loop over all events
  
  for(Long64_t entry = 0; entry < allEntries; entry++)
    {
      treeReader->ReadEntry(entry);
      std::cout << "\n** NEW ENTRY ** : " << entry << std::endl;
      

      // Loop over jets

      for(Int_t i =0; i < branchJet->GetEntriesFast(); ++i)
	{

	  std::cout << "New jet" << std::endl;
	  
	  jet = (Jet*) branchJet->At(i);
	  
	  momentum.SetPxPyPzE(0.0,0.0,0.0,0.0);
	  
	  // Number of constituents per jet:
	  
	  std::cout << "# Constituents: " << jet->Constituents.GetEntriesFast() << std::endl;


     // Loop over jet constituents

      for(Int_t j=0; j < jet->Constituents.GetEntriesFast(); ++j)
	{
	  object = jet->Constituents.At(j);
	  


	  if(object == 0) continue;
	
	  // Sieve out what the constituent is: a track, tower, or muon (expect not here)
	  // Bare in mind this doesn't tell us what the constituent is, only how the jet was constructed given the 'type' of constituent
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
	    }
	  else if(object->IsA() == Muon::Class())
	    {
	      momentum += ((Muon*) object)->P4();
	      std::cout << "momentum4: " << momentum.Pt() << std::endl;
	    }
	}
      
      std::cout << "Jet PT: " << jet->PT << std::endl;
      // Now compare PT of constituent type against PT of jet
      // Note that the jets have been passed through the energy scaling module, whereas the tracks and towers have not
      // This will no doubt yield different values. Can check by removing scale factor (1.08) to orignal jet

      Double_t diffPT = TMath::Abs(jet->PT - momentum.Pt());
      std::cout << "Diff in PT: " << diffPT << std::endl;

  // To get PID of jet constituents could try something like:
  /*
  for(Int_t k=0; k < jet->Particles.GetEntriesFast(); ++k)
    {

      particle = (GenParticle*) jet->Particle.At(k);
      std::cout << "PID of jet constituents: "<< ((GenParticle*) particle)->PID << std::endl;

    }*/
	}
    }


}




int JetConstituents(const char *inputFile)
{
  gSystem->Load("libDelphes");

  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);
  
  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);
  ExRootResult *result = new ExRootResult();

  AnalyseEvents(treeReader);
}


