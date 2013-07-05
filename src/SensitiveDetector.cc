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

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

SensitiveDetector::SensitiveDetector(G4String sname) : G4VSensitiveDetector(sname)
{
  G4String HCname; 
  collectionName.insert(HCname="HitCollection");
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

SensitiveDetector::~SensitiveDetector()
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void SensitiveDetector::Initialize(G4HCofThisEvent* hitsColl)
{
  HitCollection = new TrackHitCollection(SensitiveDetectorName,collectionName[0]);
  G4int HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hitsColl->AddHitsCollection(HCID,HitCollection); 
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

G4bool SensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory* THist)
{
  G4Track* aTrack = aStep->GetTrack();
  G4StepPoint* preStep = aStep->GetPreStepPoint();
  G4StepPoint* postStep = aStep->GetPostStepPoint();	
  
  TrackHit* thisHit = new TrackHit();

  HitCollection->insert(thisHit);
  return 0;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hitsColl)
{
  //TrackHit* thisHit = new TrackHit();

  //HitCollection->insert( thisHit );
}

/*****************************************************************************/
