#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TH1.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TGraph.h>
#include <TMath.h>
#include <TRefArray.h>
#include <TLegend.h>
#include <TObject.h>
#include <THistPainter.h>
#include <iostream>

using namespace std;

int MyClass::GetNJets(){

  Int_t njet = 0;

  for(unsigned int t=0; t<sizeof(Jet_PT); t++){
    if(Jet_PT[t]<10) continue;
      njet++;
  }
    std::cout << "# jets: " << njet << std::endl;
    return njet;

}


// Would be good to look at delta phi cut between each jet and MHT. Would be a good method to discriminate from jet mismeasurements. 

int MyClass::AnalyseParticles(){

// Assigning particles their TLorentzVectors
// Need count ticker for non desirable particles, otherwise if statement loops infinitely  

  int nlsp = 0;
  int nglu = 0;
  int ntop = 0;
  int nstp = 0;
  int nwbosons=0;

for(unsigned int r=0; r<sizeof(Particle_PID); ){

  int count = 0;

    if(abs(Particle_PID[r]) == 1000022 && nlsp ==0){
      LSP1.SetPx(Particle_Px[r]);
      LSP1.SetPy(Particle_Py[r]);
      LSP1.SetPz(Particle_Pz[r]);
      LSP1.SetE(Particle_E[r]);
      nlsp++;
      count++;
      r++;
  }
    if(abs(Particle_PID[r]) == 1000022 && nlsp == 1){   
      LSP2.SetPx(Particle_Px[r]);
      LSP2.SetPy(Particle_Py[r]);
      LSP2.SetPz(Particle_Pz[r]);
      LSP2.SetE(Particle_E[r]);
      nlsp++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 1000021 && nglu == 0){
      g1.SetPx(Particle_Px[r]);
      g1.SetPy(Particle_Py[r]);
      g1.SetPz(Particle_Pz[r]);
      g1.SetE(Particle_E[r]);
      nglu++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 1000021 && nglu == 1){
      g2.SetPx(Particle_Px[r]);
      g2.SetPy(Particle_Py[r]);
      g2.SetPz(Particle_Pz[r]);
      g2.SetE(Particle_E[r]);
      nglu++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 1000006 && nstp ==0){
      stop1.SetPx(Particle_Px[r]);
      stop1.SetPy(Particle_Py[r]);
      stop1.SetPz(Particle_Pz[r]);
      stop1.SetE(Particle_E[r]);
      nstp++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 1000006 && nstp ==1){
      stop2.SetPx(Particle_Px[r]);
      stop2.SetPy(Particle_Py[r]);
      stop2.SetPz(Particle_Pz[r]);
      stop2.SetE(Particle_E[r]);
      nstp++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 6 && ntop == 0){
      top1.SetPx(Particle_Px[r]);
      top1.SetPy(Particle_Py[r]);
      top1.SetPz(Particle_Pz[r]);
      top1.SetE(Particle_E[r]);
      ntop++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 6 && ntop ==1){
      top2.SetPx(Particle_Px[r]);
      top2.SetPy(Particle_Py[r]);
      top2.SetPz(Particle_Pz[r]);
      top2.SetE(Particle_E[r]);
      ntop++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 6 && ntop ==2){
      top3.SetPx(Particle_Px[r]);
      top3.SetPy(Particle_Py[r]);
      top3.SetPz(Particle_Pz[r]);
      top3.SetE(Particle_E[r]);
      ntop++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 6 && ntop == 3){
      top4.SetPx(Particle_Px[r]);
      top4.SetPy(Particle_Py[r]);
      top4.SetPz(Particle_Pz[r]);
      top4.SetE(Particle_E[r]);
      ntop++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 24 && nwbosons == 0){
      W1.SetPx(Particle_Px[r]);
      W1.SetPy(Particle_Py[r]);
      W1.SetPz(Particle_Pz[r]);
      W1.SetE(Particle_E[r]);
      nwbosons++;
      count++;
      r++;
    }
    if(abs(Particle_PID[r]) == 24 && nwbosons == 1){
      W2.SetPx(Particle_Px[r]);
      W2.SetPy(Particle_Py[r]);
      W2.SetPz(Particle_Pz[r]);
      W2.SetE(Particle_E[r]);
      nwbosons++;
      count++;
      r++;
    }   
    if(abs(Particle_PID[r]) == 24 && nwbosons == 2){
      W3.SetPx(Particle_Px[r]);
      W3.SetPy(Particle_Py[r]);
      W3.SetPz(Particle_Pz[r]);
      W3.SetE(Particle_E[r]);
      nwbosons++;
      count++;
      r++;
    }   
    if(abs(Particle_PID[r]) == 24 && nwbosons == 3){
      W4.SetPx(Particle_Px[r]);
      W4.SetPy(Particle_Py[r]);
      W4.SetPz(Particle_Pz[r]);
      W4.SetE(Particle_E[r]);
      nwbosons++;
      count++;
      r++;
    }      
    if(count == 0){
      r++;
    }
 }


// Clarity test
  if( nglu != nlsp ){
    std::cout << "Not an equal amount of LSPs and Gluinos" << std::endl;
  }
  if( ntop != nwbosons){
    std::cout << "Not an equal amount of W and tops" << std::endl;
  }

  ISR = g1 + g2;
  if( ISR.Pt() != 0 ){
  std::cout << "System boosted: " << ISR.Pt() << std::endl;
  _ISR->Fill(ISR.Pt());
  }

}





int MyClass::TopPolarisation(){

Double_t angle;       // Polar angle between top quark and respective lepton
Double_t phi;         // Azimuthal angle between top quark and respective lepton

// NB if more than one of the same leptons exists (likely the case with muons), polar angle of each is added to the histo (rather than ommitting it)
 
for(unsigned int p=0; p<sizeof(Particle_PID); p++){
  if(Particle_Status[p] == 1){
    if(abs(Particle_PID[p]) == 11){
      std::cout << "Found a final state electron/positron" << std::endl;
      std::cout << "Electron mother index: " << Particle_M1[p] << std::endl;
      Electron.SetPx(Particle_Px[p]);
      Electron.SetPy(Particle_Py[p]);
      Electron.SetPz(Particle_Pz[p]);
      Electron.SetE(Particle_E[p]);
    if(abs(Particle_PID[Particle_M1[p]]) == 24){
      std::cout << "---> W boson from a top decay" << std::endl;
      We.SetPx(Particle_Px[Particle_M1[p]]);
      We.SetPy(Particle_Py[Particle_M1[p]]);
      We.SetPz(Particle_Pz[Particle_M1[p]]);
      We.SetE(Particle_E[Particle_M1[p]]);
      // Calculate del R between this W boson and each top quark
      delRelectron[0] = sqrt(pow((We.Eta() - top1.Eta()),2) + pow((We.Phi() - top1.Phi()),2));
      delRelectron[1] = sqrt(pow((We.Eta() - top2.Eta()),2) + pow((We.Phi() - top2.Phi()),2));
      delRelectron[2] = sqrt(pow((We.Eta() - top3.Eta()),2) + pow((We.Phi() - top3.Phi()),2));
      delRelectron[3] = sqrt(pow((We.Eta() - top4.Eta()),2) + pow((We.Phi() - top4.Phi()),2));
    }  
    if(delRelectron[0] < 0.5){
      angle = Electron.Angle(top1.Vect());
      Double_t dotEE = (Electron.Px()*top1.Px() + Electron.Py()*top1.Py());
      Double_t modEE = (Electron.Pt()*top1.Pt());
      phi = acos(dotEE/modEE);
      if(top1.Px() < 0){
        phi = (2*pi - phi);
      }
      _polarangle1->Fill(angle);
      _phi1->Fill(phi);
    }
    else if(delRelectron[1] < 0.5){
      angle = Electron.Angle(top2.Vect());
      Double_t dotEE = (Electron.Px()*top2.Px() + Electron.Py()*top2.Py());
      Double_t modEE = (Electron.Pt()*top2.Pt());
      phi = acos(dotEE/modEE);
      if(top2.Px() < 0){
        phi = (2*pi - phi);
      }
      _polarangle1->Fill(angle);
      _phi1->Fill(phi);
    }
    else if(delRelectron[2] < 0.5){
      angle = Electron.Angle(top3.Vect());
      Double_t dotEE = (Electron.Px()*top3.Px() + Electron.Py()*top3.Py());
      Double_t modEE = (Electron.Pt()*top3.Pt());
      phi = acos(dotEE/modEE);
      if(top3.Px() < 0){
        phi = (2*pi - phi);
      }
      _polarangle1->Fill(angle);
      _phi1->Fill(phi);
    }
    else if(delRelectron[3] < 0.5){
      angle = Electron.Angle(top4.Vect());
      Double_t dotEE = (Electron.Px()*top4.Px() + Electron.Py()*top4.Py());
      Double_t modEE = (Electron.Pt()*top4.Pt());
      phi = acos(dotEE/modEE);
      if(top4.Px() < 0){
        phi = (2*pi - phi);
      }
      _polarangle1->Fill(angle);
      _phi1->Fill(phi);
    }
  }

    if(abs(Particle_PID[p]) == 13){
      std::cout << "Found a final state muon/antimuon" << std::endl;
      std::cout << "Muon mother index: " << Particle_M1[p] << std::endl;
      Muon.SetPx(Particle_Px[p]);
      Muon.SetPy(Particle_Py[p]);
      Muon.SetPz(Particle_Pz[p]);
      Muon.SetE(Particle_E[p]);
    if(abs(Particle_PID[Particle_M1[p]]) == 24){
      std::cout << "---> W boson from a top decay" << std::endl;
      Wmu.SetPx(Particle_Px[Particle_M1[p]]);
      Wmu.SetPy(Particle_Py[Particle_M1[p]]);
      Wmu.SetPz(Particle_Pz[Particle_M1[p]]);
      Wmu.SetE(Particle_E[Particle_M1[p]]); 
      // Calculate del R between this W boson and each top quark
      delRmu[0] = sqrt(pow((Wmu.Eta() - top1.Eta()),2) + pow((Wmu.Phi() - top1.Phi()),2));
      delRmu[1] = sqrt(pow((Wmu.Eta() - top2.Eta()),2) + pow((Wmu.Phi() - top2.Phi()),2));
      delRmu[2] = sqrt(pow((Wmu.Eta() - top3.Eta()),2) + pow((Wmu.Phi() - top3.Phi()),2));
      delRmu[3] = sqrt(pow((Wmu.Eta() - top4.Eta()),2) + pow((Wmu.Phi() - top4.Phi()),2));
    }
    if(delRmu[0] < 0.5){
      angle = Muon.Angle(top1.Vect());
      Double_t dotMM = (Muon.Px()*top1.Px() + Muon.Py()*top1.Py());
      Double_t modMM = (Muon.Pt()*top1.Pt());
      phi = acos(dotMM/modMM);
     std::cout << "PHI : " << phi << std::endl;
     if(top1.Px() < 0){
      phi = (2*pi - phi);
     }
      _polarangle2->Fill(angle);
      _phi2->Fill(phi);
    }
    else if(delRmu[1] < 0.5){
      angle = Muon.Angle(top2.Vect());
      Double_t dotMM = (Muon.Px()*top2.Px() + Muon.Py()*top2.Py());
      Double_t modMM = (Muon.Pt()*top2.Pt());
      phi = acos(dotMM/modMM);
     std::cout << "PHI : " << phi << std::endl;
     if(top2.Px() < 0){
      phi = (2*pi - phi);
     }
      _polarangle2->Fill(angle);
      _phi2->Fill(phi);
    }
    else if(delRmu[2] < 0.5){
      angle = Muon.Angle(top3.Vect());
      Double_t dotMM = (Muon.Px()*top3.Px() + Muon.Py()*top3.Py());
      Double_t modMM = (Muon.Pt()*top3.Pt());
      phi = acos(dotMM/modMM);
     std::cout << "PHI : " << phi << std::endl;
     if(top3.Px() < 0){
      phi = (2*pi - phi);
     }
      _polarangle2->Fill(angle);
      _phi2->Fill(phi);
    }
    else if(delRmu[3] <  0.5){
      angle = Muon.Angle(top4.Vect());
      Double_t dotMM = (Muon.Px()*top4.Px() + Muon.Py()*top4.Py());
      Double_t modMM = (Muon.Pt()*top4.Pt());
      phi = acos(dotMM/modMM);
     std::cout << "PHI : " << phi << std::endl;
     if(top4.Px() < 0){
      phi = (2*pi - phi);
     }
      _polarangle2->Fill(angle);
      _phi2->Fill(phi);
    }
  }

    if(abs(Particle_PID[p]) == 15){
      std::cout << "Found a final state tauon/antitauon" << std::endl;
      std::cout << "Tauon mother index: " << Particle_M1[p] << std::endl;
      Tauon.SetPx(Particle_Px[p]);
      Tauon.SetPy(Particle_Py[p]);
      Tauon.SetPz(Particle_Pz[p]);
      Tauon.SetE(Particle_E[p]);
    if(abs(Particle_PID[Particle_M1[p]]) == 24){
      std::cout << "---> W boson from a top decay" << std::endl;
      Wtau.SetPx(Particle_Px[Particle_M1[p]]);
      Wtau.SetPy(Particle_Py[Particle_M1[p]]);
      Wtau.SetPz(Particle_Pz[Particle_M1[p]]);
      Wtau.SetE(Particle_E[Particle_M1[p]]);
      // Calculate del R between this W boson and each top quark
      delRtauon[0] = sqrt(pow((Wtau.Eta() - top1.Eta()),2) + pow((Wtau.Phi() - top1.Phi()),2));
      delRtauon[1] = sqrt(pow((Wtau.Eta() - top2.Eta()),2) + pow((Wtau.Phi() - top2.Phi()),2));
      delRtauon[2] = sqrt(pow((Wtau.Eta() - top3.Eta()),2) + pow((Wtau.Phi() - top3.Phi()),2));
      delRtauon[3] = sqrt(pow((Wtau.Eta() - top4.Eta()),2) + pow((Wtau.Phi() - top4.Phi()),2));
    }
    if(delRtauon[0] < 0.5){
      angle = Tauon.Angle(top1.Vect());
      Double_t dotTT = (Tauon.Px()*top1.Px() + Tauon.Py()*top1.Py());
      Double_t modTT = (Tauon.Pt()*top1.Pt());
      phi = acos(dotTT/modTT);
     if(top1.Px() < 0){
      phi = (2*pi - phi);
     }
      _polarangle3->Fill(angle);
      _phi3->Fill(phi);
    }
    else if(delRtauon[1] < 0.5){
      angle = Tauon.Angle(top2.Vect());
      Double_t dotTT = (Tauon.Px()*top2.Px() + Tauon.Py()*top2.Py());
      Double_t modTT = (Tauon.Pt()*top2.Pt());
      phi = acos(dotTT/modTT);
     if(top2.Px() < 0){
      phi = (2*pi - phi);
     }
      _polarangle3->Fill(angle);
      _phi3->Fill(phi);
    }
    else if(delRtauon[2] < 0.5){
      angle = Tauon.Angle(top3.Vect());
      Double_t dotTT = (Tauon.Px()*top3.Px() + Tauon.Py()*top3.Py());
      Double_t modTT = (Tauon.Pt()*top3.Pt());
      phi = acos(dotTT/modTT);
     if(top3.Px() < 0){
      phi = (2*pi - phi);
     }
      _polarangle3->Fill(angle);
      _phi3->Fill(phi);
    }
    else if(delRtauon[3] < 0.5){
      angle = Tauon.Angle(top4.Vect());
      Double_t dotTT = (Tauon.Px()*top4.Px() + Tauon.Py()*top4.Py());
      Double_t modTT = (Tauon.Pt()*top4.Pt());
      phi = acos(dotTT/modTT);
     if(top4.Px() < 0){
      phi = (2*pi - phi);
     }
      _polarangle3->Fill(angle);
      _phi3->Fill(phi);
    }
   }
  }

  if(abs(Particle_PID[p]) == 24){
   std::cout << "Found a W boson at index: " << p << std::endl;
  }
 }



}





int MyClass::JetAnalysis(){

  for(unsigned int k=0; k<sizeof(Jet_PT); k++){
    if(Jet_PT[k] > 20. && Jet_Mass[k] > 0.1){
    Jet_ET[k] = sqrt(pow(Jet_PT[k],2) + pow(Jet_Mass[k],2)); // The transverse energy of each jet
    HT+=Jet_ET[k];                                            // The scalar sum of the transverse energy of each jet as given by the note
    _JetPT->Fill(Jet_PT[k]);
    njets++;
    if(HT<8) continue;
     _HT->Fill(HT);
    }
    if(GenJet_PT[k] > 20.){
      _h_genjetPt->Fill(GenJet_PT[k]);
    }
    if(abs(Particle_PID[k]) == 6){                    // For top quarks
    _ttbar_jetpt->Fill(Jet_PT[k]);
    _ttbar_genjetpt->Fill(GenJet_PT[k]);
    } 
  jet.SetPtEtaPhiM(Jet_PT[k], Jet_Eta[k], Jet_Phi[k], Jet_Mass[k]);         // Arrange jets in order of Pt
  Jets.push_back(jet);
}

  sort(Jets.begin(), Jets.end(), order_gt());
  //std::cout << "1st Jet Pt: " << Jets.at(0).Pt() << std::endl;


  _JetLego1->Fill(Jets.at(0).Pt(),Jets.at(0).Eta()); //Highest Pt jet
  _JetLego2->Fill(Jets.at(1).Pt(),Jets.at(1).Eta());
  _JetLego3->Fill(Jets.at(2).Pt(),Jets.at(2).Eta());
  _JetLego4->Fill(Jets.at(3).Pt(),Jets.at(3).Eta());

  _JetPt1->Fill(Jets.at(0).Pt());
  _JetPt2->Fill(Jets.at(1).Pt());
  _JetPt3->Fill(Jets.at(2).Pt());
  _JetPt4->Fill(Jets.at(3).Pt());

  Jets.clear();



}

int MyClass::GenJetAnalysis()
{
  // Look for W bosons and b quarks with same top quark parent and plot Delta R between W and b against top Pt

  int nw=0;
  int nt=0;
  int nb=0;


    for(unsigned int j=0; j<sizeof(Particle_PID); j++){

      int gen_count =0;

          if(abs(Particle_PID[j]) == 24 && nw==0){
            Gen_W1.SetPx(Particle_Px[j]);
            Gen_W1.SetPy(Particle_Py[j]);
            Gen_W1.SetPz(Particle_Pz[j]);
            Gen_W1.SetE(Particle_E[j]);
            nw++;
            W_Mindex = Particle_M1[j];

            if(abs(Particle_PID[Particle_M1[j]]) == 6 && nt==0){
              Gen_Top1.SetPx(Particle_Px[Particle_M1[j]]);
              Gen_Top1.SetPy(Particle_Py[Particle_M1[j]]);
              Gen_Top1.SetPz(Particle_Pz[Particle_M1[j]]);
              Gen_Top1.SetE(Particle_E[Particle_M1[j]]);
              _Gen_Top1->Fill(Gen_Top1.Pt());
              std::cout << "Top1 Pt: " << Gen_Top1.Pt() << std::endl;
              gen_count++;
              j++;
              nt++;
            }
          }
        if(abs(Particle_PID[j]) == 5 && nb ==0){
          Gen_b1.SetPx(Particle_Px[j]);
          Gen_b1.SetPy(Particle_Py[j]);
          Gen_b1.SetPz(Particle_Pz[j]);
          Gen_b1.SetE(Particle_E[j]);
          nb++;
          b_Mindex = Particle_M1[j];
          if(abs(Particle_PID[Particle_M1[j]]) == 6 && b_Mindex == W_Mindex){

            DelR_W_b1 = sqrt(pow((Gen_W1.Eta() - Gen_b1.Eta()),2) + pow((Gen_W1.Phi() - Gen_b1.Phi()), 2));
            _DelR_W_b1->Fill(Gen_Top1.Pt() ,DelR_W_b1);

            gen_count++;
            j++;
          }
        }

        // Second W and b

        if(abs(Particle_PID[j]) == 24 && nw==1){
          Gen_W2.SetPx(Particle_Px[j]);
          Gen_W2.SetPy(Particle_Py[j]);
          Gen_W2.SetPz(Particle_Pz[j]);
          Gen_W2.SetE(Particle_E[j]);
          nw++;
          W_Mindex = Particle_M1[j];


          if(abs(Particle_PID[Particle_M1[j]]) == 6 && nt==1){
              Gen_Top2.SetPx(Particle_Px[Particle_M1[j]]);
              Gen_Top2.SetPy(Particle_Py[Particle_M1[j]]);
              Gen_Top2.SetPz(Particle_Pz[Particle_M1[j]]);
              Gen_Top2.SetE(Particle_E[Particle_M1[j]]);
              _Gen_Top2->Fill(Gen_Top2.Pt());
              std::cout << "Top2 Pt: " << Gen_Top2.Pt() << std::endl;
              gen_count++;
              j++;
              nt++; 
          }
        }

        if(abs(Particle_PID[j]) == 5 && nb ==1){
          Gen_b2.SetPx(Particle_Px[j]);
          Gen_b2.SetPy(Particle_Py[j]);
          Gen_b2.SetPz(Particle_Pz[j]);
          Gen_b2.SetE(Particle_E[j]);
          nb++;
          b_Mindex = Particle_M1[j];

                  
              if(abs(Particle_PID[Particle_M1[j]]) == 6 && b_Mindex == W_Mindex){

            DelR_W_b2 = sqrt(pow((Gen_W2.Eta() - Gen_b2.Eta()),2) + pow((Gen_W2.Phi() - Gen_b2.Phi()), 2));
            _DelR_W_b2->Fill(Gen_Top2.Pt(), DelR_W_b2);

            gen_count++;
            j++;
          }
        }

        // Third W and b

        if(abs(Particle_PID[j]) == 24 && nw==2){
          Gen_W3.SetPx(Particle_Px[j]);
          Gen_W3.SetPy(Particle_Py[j]);
          Gen_W3.SetPz(Particle_Pz[j]);
          Gen_W3.SetE(Particle_E[j]);
          nw++;
          W_Mindex = Particle_M1[j];

          if(abs(Particle_PID[Particle_M1[j]]) == 6 && nt==2){
              Gen_Top3.SetPx(Particle_Px[Particle_M1[j]]);
              Gen_Top3.SetPy(Particle_Py[Particle_M1[j]]);
              Gen_Top3.SetPz(Particle_Pz[Particle_M1[j]]);
              Gen_Top3.SetE(Particle_E[Particle_M1[j]]);
              _Gen_Top3->Fill(Gen_Top3.Pt());
              std::cout << "Top3 Pt: " << Gen_Top3.Pt() << std::endl;
              gen_count++;
              j++;
              nt++;
          }
        }

        if(abs(Particle_PID[j]) == 5 && nb ==2){
          Gen_b3.SetPx(Particle_Px[j]);
          Gen_b3.SetPy(Particle_Py[j]);
          Gen_b3.SetPz(Particle_Pz[j]);
          Gen_b3.SetE(Particle_E[j]);
          nb++;
          b_Mindex = Particle_M1[j];

                  
              if(abs(Particle_PID[Particle_M1[j]]) == 6 && b_Mindex == W_Mindex){


            DelR_W_b3 = sqrt(pow((Gen_W3.Eta() - Gen_b3.Eta()),2) + pow((Gen_W3.Phi() - Gen_b3.Phi()), 2));
            _DelR_W_b3->Fill(Gen_Top3.Pt(), DelR_W_b3);

            gen_count++;
            j++;
          }
        }

        // Fourth W and b


        if(abs(Particle_PID[j]) == 24 && nw==3){
          Gen_W4.SetPx(Particle_Px[j]);
          Gen_W4.SetPy(Particle_Py[j]);
          Gen_W4.SetPz(Particle_Pz[j]);
          Gen_W4.SetE(Particle_E[j]);
          nw++;
          W_Mindex = Particle_M1[j];


          if(abs(Particle_PID[Particle_M1[j]]) == 6 && nt==3){
              Gen_Top4.SetPx(Particle_Px[Particle_M1[j]]);
              Gen_Top4.SetPy(Particle_Py[Particle_M1[j]]);
              Gen_Top4.SetPz(Particle_Pz[Particle_M1[j]]);
              Gen_Top4.SetE(Particle_E[Particle_M1[j]]);
              _Gen_Top4->Fill(Gen_Top4.Pt());
              std::cout << "Top4 Pt: " <<Gen_Top4.Pt() << std::endl;
              gen_count++;
              j++;
              nt++;
          }
        }

        if(abs(Particle_PID[j]) == 5 && nb ==3){
          Gen_b4.SetPx(Particle_Px[j]);
          Gen_b4.SetPy(Particle_Py[j]);
          Gen_b4.SetPz(Particle_Pz[j]);
          Gen_b4.SetE(Particle_E[j]);
          nb++;
          b_Mindex = Particle_M1[j];

                  
              if(abs(Particle_PID[Particle_M1[j]]) == 6 && b_Mindex == W_Mindex){


            DelR_W_b4 = sqrt(pow((Gen_W4.Eta() - Gen_b4.Eta()),2) + pow((Gen_W4.Phi() - Gen_b4.Phi()), 2));
            _DelR_W_b4->Fill(Gen_Top4.Pt(), DelR_W_b4);

            gen_count++;
            j++;
          }
        }    
    }







  for(unsigned int i=0; i<sizeof(GenJet_PT); i++)
    {
   

      if(GenJet_PT[i] < 20) continue;
      _GenJetPThisto->Fill(GenJet_PT[i]);      // Feed this histo into JetPT TFile -> PURITY
      // need same cuts , Jet PT > 20 < GenJet PT 
   
    genjet.SetPtEtaPhiM(GenJet_PT[i], GenJet_Eta[i], GenJet_Phi[i], GenJet_Mass[i]);         // Arrange jets in order of Pt
    GenJets.push_back(genjet);
 }

  sort(GenJets.begin(), GenJets.end(), order_gt());
  //std::cout << "1st Jet Pt: " << Jets.at(0).Pt() << std::endl;


  _GenJetPt1->Fill(GenJets.at(0).Pt());
  _GenJetPt2->Fill(GenJets.at(1).Pt());
  _GenJetPt3->Fill(GenJets.at(2).Pt());
  _GenJetPt4->Fill(GenJets.at(3).Pt());

  GenJets.clear();

}



int MyClass::METAnalysis(){

  for(unsigned int j=0; j<sizeof(MissingET_MET); j++){
    if(MissingET_MET[j]> 5){
      _MET_histo->Fill(MissingET_MET[j]);
   }
  }

}





int MyClass::TopAnalysis(){

   Double_t Pt_top[sizeof(Particle_PT)];

  for(unsigned int q=0; q<sizeof(Particle_PT); q++){
    if(abs(Particle_PID[q]) == 6 && Particle_Status[q] == 2) {             
   //   std::cout << "Found a top quark" << std::endl;
      _TopPt->Fill(Particle_PT[q]);                                         
      Pt_top[q] = Particle_PT[q];
    }
    if(abs(Particle_PID[q]) == 6 && Particle_PID[Particle_M1[q]] == 1000021){           // 1000021 is a gluino
      _Top_Gluino->Fill(Particle_PT[q]);
      ngluino++;
    }
    if(abs(Particle_PID[q]) == 6 && abs(Particle_PID[Particle_M1[q]]) == 1000006){      //  1000006 is a stop
      _Top_Stop->Fill(Particle_PT[q]);         
    nstop++;
    }
  }
    if(ngluino != nstop){
      std::cout << "WRONG" << ngluino << nstop << std::endl;
    }

// Would be good to add polar angle (between lepton and top direction) vs top boost. The top polarisation can leave an imprint
// in the kinematic distributions of decays products. Idea would be start by isolating leptons and assign them TLorentzVectors
// ensure that the isolated leptons have come from top quarks.
// In the case of heavily boosted tops, the decay products get collimated.

    TopBoost1 = abs(top1.Pt())/top1.E();
    TopBoost2 = abs(top2.Pt())/top2.E();
    TopBoost3 = abs(top3.Pt())/top3.E();
    TopBoost4 = abs(top4.Pt())/top4.E();

  }






  int MyClass::ScalarHTAnalysis(){

    for(unsigned int z=0; z<sizeof(ScalarHT_HT); z++){
   // if(ScalarHT_HT[z] < 10) continue;
      if(Jet_PT[z] > 20. && Jet_Mass[z] > 0.1){
        if(ScalarHT_HT[z] < 8) continue;
          _ScalarHT->Fill(ScalarHT_HT[z]);
          std::cout << "Scalar HT: " << ScalarHT_HT[z] << std::endl;
        }
      }
  }





void MyClass::Loop()
{
 
  Bool_t printout = 0;

// Declaring histograms

  TH1::SetDefaultSumw2();

  _JetPT = new TH1D("jetPt", "jetPt", 200, 0., 900.);
  _h_genjetPt = new TH1D("genjetPt", "genjetPt", 200, 0., 900.);
  _ttbar_jetpt = new TH1D("ttbar_jetpt", "ttbar_jetpt", 200, 0., 200.);
  _ttbar_genjetpt = new TH1D("ttbar_genjetpt", "ttbar_genjetpt", 200, 0., 200.);
  _tmass = new TH1D("tmass", "tmass", 200, 0., 400.);
  _TopPt = new TH1D("TopPt", "TopPt", 200, 0., 800.);
  _Top_Gluino = new TH1D("Top_Gluino", "Top_Gluino", 200, 0., 800.);
  _Top_Stop = new TH1D("Top_Stop", "Top_Stop", 200, 0., 800.);
  _MET_histo = new TH1D("MET_histo", "MET_histo", 200, 0., 2500.);
  _HT = new TH1D("HT", "HT", 200, 0., 1500.);
  _ISR = new TH1D("ISR", "ISR", 200, 0., 500);
  _ScalarHT = new TH1D("ScalarHT","ScalarHT", 200, 200, 2600);
  _JetPt1 = new TH1D("_JetPt1", "1st leading Jet Pt", 200, 0., 900.);
  _JetPt2 = new TH1D("_JetPt2", "2nd leading Jet Pt", 200, 0., 900.);
  _JetPt3 = new TH1D("_JetPt3", "3rd leading Jet Pt", 200, 0., 900.);
  _JetPt4 = new TH1D("_JetPt4", "4th leading Jet Pt", 200, 0., 900.);
  _JetLego1 = new TH2F("JetLego1","Jet Lego plot", 200, 0, 600,  50, -5, 5);
  _JetLego2 = new TH2F("JetLego2","Jet Lego plot", 200, 0, 600,  50, -5, 5);
  _JetLego3 = new TH2F("JetLego3","Jet Lego plot", 200, 0, 600,  50, -5, 5);
  _JetLego4 = new TH2F("JetLego4","Jet Lego plot", 200, 0, 600,  50, -5, 5);
  _polarangle1 = new TH1F("polarangle1","polarangle1", 50, 0.0, 4);
  _polarangle2 = new TH1F("polarangle2","polarangle2", 50, 0.0, 4);
  _polarangle3 = new TH1F("polarangle3","polarangle3", 50, 0.0, 4);
  _phi1 = new TH1F("phi1","phi1", 50, 0.0, 7);
  _phi2 = new TH1F("phi2","phi2", 50, 0.0, 7);
  _phi3 = new TH1F("phi3","phi3", 50, 0.0, 7);
  _GenJetPThisto = new TH1D("GenJetPT", "GenJet_P{T}", 200, 0.0, 900);
  _GenJetPt1 = new TH1D("GenJetPt1", "GenJetPt1", 200, 0., 900);
  _GenJetPt2 = new TH1D("GenJetPt2", "GenJetPt2", 200, 0., 900);
  _GenJetPt3 = new TH1D("GenJetPt3", "GenJetPt3", 200, 0., 900);
  _GenJetPt4 = new TH1D("GenJetPt4", "GenJetPt4", 200, 0., 900);
  _DelR_W_b1 = new TH2F("DeltaR_W_b1", "DelR_W_b1", 200, 0, 900, 50, 0., 8);
  _DelR_W_b2 = new TH2F("DeltaR_W_b2", "DelR_W_b2", 200, 0, 900, 50, 0., 8);  
  _DelR_W_b3 = new TH2F("DeltaR_W_b3", "DelR_W_b3", 200, 0, 900, 50, 0., 8);    
  _DelR_W_b4 = new TH2F("DeltaR_W_b4", "DelR_W_b4", 200, 0, 900, 50, 0., 8);  
  _Gen_Top1 = new TH1D("Gen_Top1", "Gen_Top1.PT", 200, 0., 800);
  _Gen_Top2 = new TH1D("Gen_Top2", "Gen_Top2.PT", 200, 0., 800);
  _Gen_Top3 = new TH1D("Gen_Top3", "Gen_Top3.PT", 200, 0., 800);
  _Gen_Top4 = new TH1D("Gen_Top4", "Gen_Top4.PT", 200, 0., 800);


Long64_t nentries = fChain->GetEntries();
//Long64_t nentries = 1000;

//Long64_t nents = b_Particle_PID->GetEntries();

for(int i = 0; i<nentries; i++){
  fChain->GetEntry(i);
  if ( printout ) continue;
   std::cout << "\n**********************************" << std::endl;  
   std::cout << "\nNEW EVENT [" << i << " of " << nentries << "]" << std::endl;

    We = TLorentzVector(0,0,0,0);    // Need to reset the W boson TLorentzVectors for each event
    Wmu = TLorentzVector(0,0,0,0);
    Wtau = TLorentzVector(0,0,0,0);
    Electron = TLorentzVector(0,0,0,0);
    Muon = TLorentzVector(0,0,0,0);
    Tauon = TLorentzVector(0,0,0,0); 


// Initiliase functions

int NJETS = GetNJets();
int ANALYSEPARTICLES = AnalyseParticles();
int TOPPOLARISATION = TopPolarisation();
int JETANALYSIS = JetAnalysis();
int METANALYSIS = METAnalysis();
int TOPANALYSIS = TopAnalysis();
int SCALARHTANALYSIS = ScalarHTAnalysis();
int GENANALYSIS = GenJetAnalysis();

}

// Printing histograms


TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 600, 400);
TCanvas *c2 = new TCanvas("c2", "c2", 200, 10, 600, 400);
TCanvas *c3 = new TCanvas("c3", "c3", 200, 10, 600, 400);
TCanvas *c4 = new TCanvas("c4", "c4", 200, 10, 600, 400);
TCanvas *c7 = new TCanvas("c7", "c7", 200, 10, 600, 400);
TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);


c1->Clear();
TFile *Jet_PT = new TFile("JetPT_tag_1.root", "RECREATE");
_JetPT->Write();
_GenJetPThisto->Write();

c2->Clear();
_tmass->Draw("hist");
//c2->Print("top_mass.pdf");

c3->Clear();
_TopPt->Draw("hist");
//c3->Print("TopPt.pdf");

c4->Clear();
TFile *PTgluino_stop = new TFile("PTgluino_MG_500_300.root","RECREATE");
_Top_Gluino->Draw("hist");
_Top_Gluino->Write();
_Top_Gluino->SetTitle("P_{T} from stop (500 GeV) and gluino (600 GeV) ");
_Top_Gluino->GetXaxis()->SetTitle("P_{T} of top");
_Top_Gluino->GetYaxis()->SetTitle("Entries");
_Top_Stop->Draw("SAME");
_Top_Stop->SetLineColor(2);
_Top_Stop->Draw("SAME");
leg->AddEntry(_Top_Gluino, "PT of top from gluino", "l");
leg->AddEntry(_Top_Stop, "PT of top from stop", "l");
leg->Draw();
c4->Print("PtTopGluino.pdf");

c7->Clear();
_DelR_W_b1->Draw("hist");

TFile *DeltaR_TopPT = new TFile("DeltaR_TopPT_500_300.root", "RECREATE");
_DelR_W_b1->Write();
_DelR_W_b2->Write();
_DelR_W_b3->Write();
_DelR_W_b4->Write();
_Gen_Top1->Write();
_Gen_Top2->Write();
_Gen_Top3->Write();
_Gen_Top4->Write();

TFile *PTstop_top = new TFile("PT_MG_500_300.root", "RECREATE");
_Top_Stop->Write();

TFile *f = new TFile("MET_MG_500_300.root", "RECREATE");
_MET_histo->Write();

TFile *g = new TFile("HT_MG_500_300.root", "RECREATE");
_HT->Write();

TFile *ISR = new TFile("ISR_MG_500_300.root", "RECREATE");
_ISR->Write();

TFile *ScalarHT = new TFile("ScalarHT_MG_500_300.root","RECREATE");
_ScalarHT->Write();

TFile *JetsPt1 = new TFile("LeadingJetPt_MG_500_300.root", "RECREATE");
_JetPt1->Write();
_JetPt2->Write();
_JetPt3->Write();
_JetPt4->Write();
_GenJetPt1->Write();
_GenJetPt2->Write();
_GenJetPt3->Write();
_GenJetPt4->Write();


TFile *JetLego = new TFile("JetLego_MG_500_300.root", "RECREATE");
_JetLego1->Write();
_JetLego2->Write();
_JetLego3->Write();
_JetLego4->Write();

TFile *angles = new TFile("angle1_MG_500_300.root","RECREATE");
_polarangle1->Write();
_polarangle2->Write();
_polarangle3->Write();
_phi1->Write();
_phi2->Write();
_phi3->Write();




}
/*
int  run(){

  MyClass m;
  
  m.Loop();

  return 0;
}
*/




