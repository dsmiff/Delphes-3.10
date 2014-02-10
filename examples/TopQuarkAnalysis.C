/* 
Macro to analyse top quark properties without having to run MyClass, on a Delphse ROOT output
Dominic Smith
Febuary 2014

To run:

root -l examples/TopQuarkAnalysis.C\(\"delphes_file.root\"\)

*/


void TopQuarkAnalysis(const char *inputFile)
{

  gSystem->Load("libDelphes");
  
  // Create chain of ROOT trees

  TChain chain("Delphes");
  chain.Add(inputFile);
  
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");

  GenParticle *particle;

  // Declaring histos

  TH1 *TopPt = new TH1F("TopPt","Top_P{T}",100, 0.0, 200);
  
  for(Int_t i=0; i < numberOfEntries; i++)
    {
      treeReader->ReadEntry(i);
      int TopPT;

      for(Int_t j=0; j < branchParticle->GetEntriesFast(); j++)
	{

	  particle = (GenParticle*) branchParticle->At(j);
	  pdgCode = TMath::Abs(particle->PID);

	  if(pdgCode == 6)
	    {
	      TopPt->Fill(particle->PT);
	      cout << "Top PT : " << particle->PT << endl;
	    }
	}
      TopPt->Draw();
    }
}


