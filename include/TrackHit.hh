/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : include/TrackHit.hh                                               *
*Source  : src/TrachHit.cc                                                   *
******************************************************************************
* - Information array for the events                                         *
\*****************************************************************************/

#ifndef TrackHit_h
#define TrackHit_h 1

#include "G4VHit.hh" 
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

class TrackHit : public G4VHit
{

public :
  TrackHit();
  ~TrackHit();
  TrackHit(const TrackHit &right);
  
  const TrackHit& operator=(const TrackHit&);
  G4int operator==(const TrackHit&) const;
  
  inline void * operator new(size_t);
  inline void operator delete(void *aHit);

  void Draw();
  void Print();

  G4int GetParentID(){return parentID;};
  G4int GetTrackID(){return trackID;};
  G4String GetParName(){return parName;};
  G4String GetDetName(){return detName;};
  G4String GetProcName(){return procName;};
  G4String GetCreProcName(){return creProcName;};
  G4double GetLocTime(){return locTime;};
  G4ThreeVector GetParPos(){return parPos;};
  G4ThreeVector GetParVertPos(){return parVertPos;};
  G4ThreeVector GetParPostPos(){return parPostPos;};
  G4ThreeVector GetParPrePos(){return parPrePos;};
  G4ThreeVector GetParMomDir(){return parMomDir;};
  G4ThreeVector GetParVertMomDir(){return parVertMomDir;};
  G4ThreeVector GetParPostMomDir(){return parPostMomDir;};
  G4ThreeVector GetParPreMomDir(){return parPreMomDir;};
  G4ThreeVector GetParMom(){return parMom;};
  G4ThreeVector GetParPostMom(){return parPostMom;};
  G4ThreeVector GetParPreMom(){return parPreMom;};
  G4ThreeVector GetParPol(){return parPol;};
  G4double GetParKin(){return parKin;};
  G4double GetParVertKin(){return parVertKin;};
  G4double GetParPostKin(){return parPostKin;};
  G4double GetParPreKin(){return parPreKin;};
  G4double GetEnDep(){return enDep;}

  void SetParentID(G4int val){parentID=val;};
  void SetTrackID(G4int val){trackID=val;};
  void SetParName(G4String val){parName=val;};
  void SetDetName(G4String val){detName=val;};
  void SetProcName(G4String val){procName=val;};
  void SetCreProcName(G4String val){creProcName=val;};
  void SetLocTime(G4double val){locTime=val;};
  void SetParPos(G4ThreeVector val){parPos=val;};
  void SetParVertPos(G4ThreeVector val){parVertPos=val;};
  void SetParPostPos(G4ThreeVector val){parPostPos=val;};
  void SetParPrePos(G4ThreeVector val){parPrePos=val;};
  void SetParMomDir(G4ThreeVector val){parMomDir=val;};
  void SetParVertMomDir(G4ThreeVector val){parVertMomDir=val;};
  void SetParPostMomDir(G4ThreeVector val){parPostMomDir=val;};
  void SetParPreMomDir(G4ThreeVector val){parPreMomDir=val;};
  void SetParMom(G4ThreeVector val){parMom=val;};
  void SetParPostMom(G4ThreeVector val){parPostMom=val;};
  void SetParPreMom(G4ThreeVector val){parPreMom=val;};
  void SetParPol(G4ThreeVector val){parPol=val;};
  void SetParKin(G4double val){parKin=val;};
  void SetParVertKin(G4double val){parVertKin=val;};
  void SetParPostKin(G4double val){parPostKin=val;};
  void SetParPreKin(G4double val){parPreKin=val;};
  void SetEnDep(G4double val){enDep=val;}

private :	  
  G4int parentID;
  G4int trackID;
  G4String parName;
  G4String detName;
  G4String procName;
  G4String creProcName;
  G4double locTime;
  G4ThreeVector parPos;
  G4ThreeVector parVertPos;
  G4ThreeVector parPostPos;
  G4ThreeVector parPrePos;
  G4ThreeVector parMomDir;
  G4ThreeVector parVertMomDir;
  G4ThreeVector parPostMomDir;
  G4ThreeVector parPreMomDir;
  G4ThreeVector parMom;
  G4ThreeVector parPostMom;
  G4ThreeVector parPreMom;
  G4ThreeVector parPol;
  G4double parKin;
  G4double parVertKin;
  G4double parPostKin;
  G4double parPreKin;
  G4double enDep;

};

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

typedef G4THitsCollection<TrackHit> TrackHitCollection;
extern G4Allocator<TrackHit> TrackHitAllocator;

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void* TrackHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) TrackHitAllocator.MallocSingle();
  return aHit;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void TrackHit::operator delete(void *aHit)
{
  TrackHitAllocator.FreeSingle((TrackHit*) aHit);
}

#endif

/*****************************************************************************/
