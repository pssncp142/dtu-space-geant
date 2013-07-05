/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : src/Run.cc                                                        *
*Header  : include/Run.hh                                                    *
******************************************************************************
* - This part is for data collection for every event                         *
\*****************************************************************************/

#include "Run.hh"
#include "TrackHit.hh"

#include "G4SDManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "globals.hh"

#include <vector>
#include <ctime>

using namespace std;

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

Run::Run(const vector<G4String> SDName)
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

Run::~Run()
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void Run::RecordEvent(const G4Event* aEvent)
{

  G4HCofThisEvent* HCE;
  G4SDManager* fSDM;
  G4int collectionID,percent,NbHits;
  G4double fperc;
  G4long totEventNum;
  TrackHitCollection* HC;  
  time_t elpsT,leftT,startT,lastT;
  char buffer [100];

  numberOfEvent++; 

  totEventNum = (G4long)GetNumberOfEventToBeProcessed();
  fperc = numberOfEvent * 100.0 / totEventNum;
  percent = (G4int)(fperc);

  if (numberOfEvent <= 1) { startT = time(NULL); lastT = startT; }
      
  if ( numberOfEvent == 1 || percent == fperc || time(NULL) - lastT >=1 )  {
    G4cout << "\rProgress: [";
      
    for (int i = 0; i < (percent+1)/2; i++){
      G4cout << ":";
    }
      
    for (int i = (percent+1)/2; i < 50; i++){
      G4cout << " ";
    }
    G4cout << "]" << percent << "%";
    
    elpsT = time(NULL) - startT;
    leftT = (G4double)elpsT / (G4double)numberOfEvent * (G4double)totEventNum;
    
    sprintf(buffer, "  ==> TE: %02d:%02d:%02d / TR: %02d:%02d:%02d   ", (G4int)elpsT/3600, ((G4int)elpsT%3600)/60, (G4int)elpsT%60, (G4int)leftT/3600, ((G4int)leftT%3600)/60, (G4int)leftT%60);
    G4cout << buffer;
      
    lastT = time(NULL);
  }
  G4cout.flush();
  if ( numberOfEvent == totEventNum ) G4cout << G4endl;
  
  HCE = aEvent->GetHCofThisEvent();
  if (!HCE) return;
  fSDM = G4SDManager::GetSDMpointer();
  collectionID = fSDM->GetCollectionID("HitCollection");
  HC = (TrackHitCollection*)(HCE->GetHC(collectionID));  
  NbHits = HC->entries();
  
}

/*****************************************************************************/
