/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : src/SensitiveDetector.cc                                          *
*Header  : include/SensitiveDetector.hh                                      *
******************************************************************************
* - Collects info and add them to HitsCollection                             *
\*****************************************************************************/

#include "SensitiveDetector.hh"
#include "TrackHit.hh"

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

SensitiveDetector::SensitiveDetector(G4String sname) : G4VSensitiveDetector(sname)
{
  G4String HCname; 
  if(sname == "/det/ins"){
    collectionName.insert(HCname="HitColl_ins");
  } else if (sname == "/det/out"){
    collectionName.insert(HCname="HitColl_out");
  }
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

SensitiveDetector::~SensitiveDetector()
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void SensitiveDetector::Initialize(G4HCofThisEvent* hitsColl)
{
  G4int HCID;
  if(SensitiveDetectorName == "ins"){
    HitColl_ins = new TrackHitCollection(SensitiveDetectorName,collectionName[0]);
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hitsColl->AddHitsCollection(HCID,HitColl_ins); 
  } else if(SensitiveDetectorName == "out"){
    HitColl_out = new TrackHitCollection(SensitiveDetectorName,collectionName[0]);
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hitsColl->AddHitsCollection(HCID,HitColl_out); 
  }
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

G4bool SensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory* THist)
{
  G4Track* aTrack = aStep->GetTrack();
  G4StepPoint* preStep = aStep->GetPreStepPoint();
  G4StepPoint* postStep = aStep->GetPostStepPoint();  
  TrackHit* thisHit = new TrackHit();
  
  thisHit->SetParentID(aTrack->GetParentID());
  thisHit->SetTrackID(aTrack->GetTrackID());
  thisHit->SetParName(aTrack->GetDefinition()->GetParticleName());
  thisHit->SetDetName(preStep->GetSensitiveDetector()->GetName());
  thisHit->SetProcName(postStep->GetProcessDefinedStep()->GetProcessName());
  thisHit->SetLocTime(aTrack->GetLocalTime());
  thisHit->SetParPos(aTrack->GetPosition());
  thisHit->SetParPostPos(postStep->GetPosition());
  thisHit->SetParPrePos(preStep->GetPosition());
  thisHit->SetParMom(aTrack->GetMomentum());
  thisHit->SetParPostMom(postStep->GetMomentum());
  thisHit->SetParPreMom(preStep->GetMomentum());
  thisHit->SetParKin(aTrack->GetKineticEnergy());
  thisHit->SetParPostKin(postStep->GetKineticEnergy());
  thisHit->SetParPreKin(preStep->GetKineticEnergy());

  if(SensitiveDetectorName == "ins")
    HitColl_ins->insert(thisHit);
  else if(SensitiveDetectorName == "out")
    HitColl_out->insert(thisHit);
  return 0;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hitsColl)
{
  //TrackHit* thisHit = new TrackHit();
  //HitCollection->insert( thisHit );
}

/*****************************************************************************/
