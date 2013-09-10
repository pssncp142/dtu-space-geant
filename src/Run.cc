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

/*void Run::RecordEvent(const G4Event* aEvent){

  Timing();
  
  G4HCofThisEvent* HCE;
  TrackHitCollection* HC[3];  
  G4int NbHits[2];
  G4int ENbHits[2]={0};
  ofstream txt,bin;
  TrackHit* hit;
  double dtmp;
  int tot_ev;
  G4ThreeVector vtmp;
  
  HCE = aEvent->GetHCofThisEvent();
  if (!HCE) return;

  txt.open("data.txt",iostream::app);
  for(int i=0;i<2;i++){
    HC[i] = (TrackHitCollection*)(HCE->GetHC(i));  
    NbHits[i] = HC[i]->entries();
    for(int j=0;j<NbHits[i];j++){
      hit = (*HC[i])[j]; 
      if(hit->GetProcName() != "Transportation"){
	txt << hit->GetParentID() << " "
	    << hit->GetTrackID() << " "
	    << hit->GetParName() << " "
	    << hit->GetCreProcName() << " "
	    << hit->GetProcName() << " "
	    << hit->GetLocTime()*1e5 << " "
	    << hit->GetDetName() << " "
	    << hit->GetParPos() << " "
	    << hit->GetEnDep()*1e3 << " "
	    << G4endl;
	ENbHits[i]++;
      }
    }
  }
  cout << ENbHits[0] << " " << ENbHits[1] << endl;
  if(NbHits[0]+NbHits[1] != 0)
    txt << G4endl;
  txt.close();

  for(int i=0; i<2; i++){
    tot_ev = ENbHits[0]+ENbHits[1];
    if(tot_ev!=0){
      bin.open("data.bin",iostream::app);
      if(i==0)
	bin.write((char*)&tot_ev,sizeof(int));
      for(int j=0; j<NbHits[i]; j++){
	hit = (*HC[i])[j]; 
	if(hit->GetProcName() != "Transportation"){
	  vtmp = hit->GetParPos();
	  dtmp = vtmp.getX();
	  bin.write((char*)&dtmp,sizeof(double));
	  dtmp = vtmp.getY();
	  bin.write((char*)&dtmp,sizeof(double));
	  dtmp = vtmp.getZ();
	  bin.write((char*)&dtmp,sizeof(double));
	  dtmp = hit->GetEnDep()*1e3;
	  bin.write((char*)&dtmp,sizeof(double));
	}
      }
      bin.close();
    }
  }

  }*/

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void Run::RecordEvent(const G4Event* aEvent)
{

  Timing();

  G4HCofThisEvent* HCE;
  TrackHitCollection* HC[2];  
  G4int NbHits[5];
  ofstream ofs,ofs1;
  TrackHit* hit;
  char a = 'a';

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

  if(NbHits[2]>0){
    hit = (*HC[0])[0]; 
  } else if(NbHits[3]>0) {
    hit = (*HC[1])[0];
  }

  ofs.open("data.bin",iostream::app);
  ofs1.open("a.txt",iostream::app);

  if(NbHits[2]>0 || NbHits[3]>0){
    ofs.write((char*)&a,sizeof(char));
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
  }

  for(int i=0; i<2; i++){
    for(int j=0; j<NbHits[i]; j++){
      hit = (*HC[i])[j];

      /*if((hit->GetParVertKin() == hit->GetParPreKin()) && hit->GetParentID() == 0
	   && hit->GetDetName() == "ins" && hit->GetProcName() == "compt" && hit->GetProcName() != "Transportation" ){
	G4ThreeVector mom1,mom2;
	G4double ang,en1,en2;
	mom1 = hit->GetParPostMomDir();
	mom2 = hit->GetParPreMomDir();
	en1 = hit->GetParPostKin();
	en2 = hit->GetParPreKin();
	ang = acos(mom1.dot(mom2)/(mom1.mag()*mom2.mag()));
	ofs1 << ang << " " 
	     << hit->GetParPreKin()*1000 << " " << 1/(1/(hit->GetParKin()*1000)+1/511.*(cos(ang)-1)) << " " << hit->GetParKin()*1000 << G4endl;
	     }*/
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
	} else if(hit->GetDetName() == "bot") {
	  tmp_i = 2;
	  ofs.write((char*)&tmp_i,sizeof(int));
	}
	tmp_d = hit->GetLocTime();
	ofs.write((char*)&tmp_d,sizeof(double));
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
  ofs1.close();

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
