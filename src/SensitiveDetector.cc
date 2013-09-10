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
  } else if (sname == "/det/bot"){
    collectionName.insert(HCname="HitColl_bot");
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
  } else if(SensitiveDetectorName == "bot"){
    HitColl_bot = new TrackHitCollection(SensitiveDetectorName,collectionName[0]);
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hitsColl->AddHitsCollection(HCID,HitColl_bot); 
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
  if(aTrack->GetParentID() != 0)
    thisHit->SetCreProcName(aTrack->GetCreatorProcess()->GetProcessName());
  else
    thisHit->SetCreProcName("vert");
  thisHit->SetProcName(postStep->GetProcessDefinedStep()->GetProcessName());
  thisHit->SetLocTime(aTrack->GetLocalTime());
  thisHit->SetParPos(aTrack->GetPosition());
  thisHit->SetParVertPos(aTrack->GetVertexPosition());
  thisHit->SetParPostPos(postStep->GetPosition());
  thisHit->SetParPrePos(preStep->GetPosition());
  thisHit->SetParMomDir(aTrack->GetMomentumDirection());
  thisHit->SetParVertMomDir(aTrack->GetVertexMomentumDirection());
  thisHit->SetParPostMomDir(postStep->GetMomentumDirection());   
  thisHit->SetParPreMomDir(preStep->GetMomentumDirection());  
  thisHit->SetParMom(aTrack->GetMomentum());
  thisHit->SetParPostMom(postStep->GetMomentum());
  thisHit->SetParPreMom(preStep->GetMomentum());
  thisHit->SetParKin(aTrack->GetKineticEnergy());
  thisHit->SetParVertKin(aTrack->GetVertexKineticEnergy());
  thisHit->SetParPostKin(postStep->GetKineticEnergy());
  thisHit->SetParPreKin(preStep->GetKineticEnergy());
  thisHit->SetParPol(aTrack->GetPolarization());
  thisHit->SetEnDep(aStep->GetTotalEnergyDeposit());
  
  if(SensitiveDetectorName == "ins")
    HitColl_ins->insert(thisHit);
  else if(SensitiveDetectorName == "out")
    HitColl_out->insert(thisHit);
  else if(SensitiveDetectorName == "bot")
    HitColl_bot->insert(thisHit);


  return 0;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hitsColl)
{
  //TrackHit* thisHit = new TrackHit();
  //HitCollection->insert( thisHit );
}

/*****************************************************************************/
