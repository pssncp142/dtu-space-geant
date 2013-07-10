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
#include "G4ThreeVector.hh"
#include "globals.hh"

#include <vector>
#include <ctime>
#include <fstream>

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

  Timing();

  G4HCofThisEvent* HCE;
  TrackHitCollection* HC[2];  
  G4int NbHits[5];
  ofstream ofs;
  TrackHit* hit;

  G4ThreeVector tmp_vect;
  double tmp_d;
  int tmp_i;

  HCE = aEvent->GetHCofThisEvent();
  if (!HCE) return;
  for(int i=0;i<2;i++){
    HC[i] = (TrackHitCollection*)(HCE->GetHC(i));  
    NbHits[i] = HC[i]->entries();
  }

  NbHits[2]=0; NbHits[3]=0;
  for(int i=0; i<2; i++){
    for(int j=0; j<NbHits[i]; j++){
      hit = (*HC[i])[j];
      if(hit->GetParName() == "gamma" && hit->GetParentID() == 0 && hit->GetProcName() != "Transportation"){
	NbHits[2+i]++;
      }
    }
  }
  NbHits[4] = NbHits[2] + NbHits[3];

  hit = (*HC[0])[0];
  ofs.open("data.bin",iostream::app);
  tmp_i = NbHits[4];
  ofs.write((char*)&tmp_i,sizeof(int));
  tmp_vect = hit->GetParVertPos();
  tmp_d = tmp_vect.getX();
  ofs.write((char*)&tmp_d,sizeof(double));
  tmp_d = tmp_vect.getY();
  ofs.write((char*)&tmp_d,sizeof(double));
  tmp_d = tmp_vect.getZ();
  ofs.write((char*)&tmp_d,sizeof(double));
  tmp_vect = hit->GetParVertMomDir();
  tmp_d = tmp_vect.getX();
  ofs.write((char*)&tmp_d,sizeof(double));
  tmp_d = tmp_vect.getY();
  ofs.write((char*)&tmp_d,sizeof(double));
  tmp_d = tmp_vect.getZ();
  ofs.write((char*)&tmp_d,sizeof(double));
  tmp_d = hit->GetParVertKin()*1000;
  ofs.write((char*)&tmp_d,sizeof(double));

  for(int i=0; i<2; i++){
    for(int j=0; j<NbHits[i]; j++){
      hit = (*HC[i])[j];
      if(hit->GetParName() == "gamma" && hit->GetParentID() == 0 && hit->GetProcName() != "Transportation"){
	if(hit->GetProcName() == "compt"){
	  tmp_i = 0;
	  ofs.write((char*)&tmp_i,sizeof(int));
	} else if(hit->GetProcName() == "phot") {
	  tmp_i = 1;
	  ofs.write((char*)&tmp_i,sizeof(int));
	} else if(hit->GetProcName() == "Rayl") {
	  tmp_i = 2;
	  ofs.write((char*)&tmp_i,sizeof(int));
	}
	if(hit->GetDetName() == "ins"){
	  tmp_i = 0;
	  ofs.write((char*)&tmp_i,sizeof(int));
	} else if(hit->GetDetName() == "out") {
	  tmp_i = 1;
	  ofs.write((char*)&tmp_i,sizeof(int));
	}
	tmp_vect = hit->GetParPos();
	tmp_d = tmp_vect.getX();
	ofs.write((char*)&tmp_d,sizeof(double));
	tmp_d = tmp_vect.getY();
	ofs.write((char*)&tmp_d,sizeof(double));
	tmp_d = tmp_vect.getZ();
	ofs.write((char*)&tmp_d,sizeof(double));
	tmp_vect = hit->GetParPreMomDir();
	tmp_d = tmp_vect.getX();
	ofs.write((char*)&tmp_d,sizeof(double));
	tmp_d = tmp_vect.getY();
	ofs.write((char*)&tmp_d,sizeof(double));
	tmp_d = tmp_vect.getZ();
	ofs.write((char*)&tmp_d,sizeof(double));
	tmp_vect = hit->GetParMomDir();
	tmp_d = tmp_vect.getX();
	ofs.write((char*)&tmp_d,sizeof(double));
	tmp_d = tmp_vect.getY();
	ofs.write((char*)&tmp_d,sizeof(double));
	tmp_d = tmp_vect.getZ();
	ofs.write((char*)&tmp_d,sizeof(double));
	tmp_d = (hit->GetParPreKin() - hit->GetParKin())*1000;
	ofs.write((char*)&tmp_d,sizeof(double));
      }
    }
  }

  ofs.close();

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
