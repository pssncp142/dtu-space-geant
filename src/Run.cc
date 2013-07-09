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
  numberOfEvent=0;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

Run::~Run()
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void Run::RecordEvent(const G4Event* aEvent)
{
  G4HCofThisEvent* HCE;
  TrackHitCollection* HC;  
  G4int NbHits;

  Timing();

  HCE = aEvent->GetHCofThisEvent();
  if (!HCE) return;
  //G4cout<<G4endl;
  for(int i=0; i<2; i++){
    HC = (TrackHitCollection*)(HCE->GetHC(i));  
    NbHits = HC->entries();
    for(int j=0; j<NbHits; j++){
      TrackHit* hit = (*HC)[j];
      /*if(hit->GetParName() == "gamma" && hit->GetProcName() != "Transportation"){
	G4cout <<hit->GetParentID()<< " " <<hit->GetTrackID()<< " " <<hit->GetParName()<< " " <<hit->GetDetName()<< " " <<hit->GetProcName()<< " " << G4endl; 
	G4cout << "Time  : " <<hit->GetLocTime()<< G4endl;
	G4cout << "Previous // Current" << G4endl;
	G4cout << "Positions  : " <<hit->GetParPrePos()<< " // " <<hit->GetParPos()<< G4endl;
	G4cout << "Momentum   : " <<hit->GetParPreMom()<< " // " <<hit->GetParMom()<< G4endl;	
	G4cout << "Kinetic    : " <<hit->GetParPreKin()<< " // " <<hit->GetParKin()<< G4endl;
	}*/
    }
  }
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void Run::Timing(){
  G4int dperc;
  G4double fperc;
  G4long totEventNum;
  time_t leftT,startT,lastT;
  char buffer[100];
  
  numberOfEvent++; 

  totEventNum = (G4long)GetNumberOfEventToBeProcessed();
  fperc = numberOfEvent * 100.0 / totEventNum;
  dperc = (G4int) fperc;

  G4cout << "\r*Progress : [";
  for(int i=0;i<dperc/4;i++) G4cout << ":";
  for(int i=0;i<25-dperc/4;i++) G4cout << " ";
  G4cout << "] " << dperc << "%";
  G4cout.flush();
  
}
/*****************************************************************************/
