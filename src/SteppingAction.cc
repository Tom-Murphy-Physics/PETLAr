#include <cmath>
#include "SteppingAction.hh"



SteppingAction::SteppingAction()
{
  // fRunAction = runAction;
}



SteppingAction::~SteppingAction()
{}



void SteppingAction::UserSteppingAction(const G4Step *step)
{
  //Infomration that is added to the ROOT file

  //track length 
  G4ThreeVector x = step->GetDeltaPosition();
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(0,0, sqrt(x[0]*x[0]+x[1]*x[1]));

  //track ID
  G4int track_id = step->GetTrack()->GetTrackID();
  man->FillNtupleIColumn(1,track_id);
  
  //Event ID
  G4int event_id = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  man->FillNtupleIColumn(2,event_id);

  //Delta Z distance  
  man->FillNtupleDColumn(3, x[2]);

  //Change in energy
  G4double delta_E = step->GetDeltaEnergy();
  man->FillNtupleDColumn(4,delta_E);

  //Type of particle
  G4String name = step->GetTrack()->GetParticleDefinition()->GetParticleName();
  G4int type = 0;
  if (name=="gamma"){type = 0;}
  else if (name=="e-"){type = 1;}
  else {type = 2;}
  man->FillNtupleIColumn(5,type);

  man->AddNtupleRow(0);
}
void SteppingAction::stop(const G4Step *step)
{
  G4Track* track = step->GetTrack();
  G4ParticleDefinition* particleType = track->GetDefinition();

  //if(particleType == G4OpticalPhoton::OpticalPhotonDefinition()) track ->SetTrackStatus(fStopAndKill);
}
