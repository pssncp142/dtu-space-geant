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
  G4double GetLocTime(){return locTime;};
  G4ThreeVector GetParPos(){return parPos;};
  G4ThreeVector GetParPostPos(){return parPostPos;};
  G4ThreeVector GetParPrePos(){return parPrePos;};
  G4ThreeVector GetParMom(){return parMom;};
  G4ThreeVector GetParPostMom(){return parPostMom;};
  G4ThreeVector GetParPreMom(){return parPreMom;};
  G4double GetParKin(){return parKin;};
  G4double GetParPostKin(){return parPostKin;};
  G4double GetParPreKin(){return parPreKin;};

  void SetParentID(G4int val){parentID=val;};
  void SetTrackID(G4int val){trackID=val;};
  void SetParName(G4String val){parName=val;};
  void SetDetName(G4String val){detName=val;};
  void SetProcName(G4String val){procName=val;};
  void SetLocTime(G4double val){locTime=val;};
  void SetParPos(G4ThreeVector val){parPos=val;};
  void SetParPostPos(G4ThreeVector val){parPostPos=val;};
  void SetParPrePos(G4ThreeVector val){parPrePos=val;};
  void SetParMom(G4ThreeVector val){parMom=val;};
  void SetParPostMom(G4ThreeVector val){parPostMom=val;};
  void SetParPreMom(G4ThreeVector val){parPreMom=val;};
  void SetParKin(G4double val){parKin=val;};
  void SetParPostKin(G4double val){parPostKin=val;};
  void SetParPreKin(G4double val){parPreKin=val;};

private :	  
  G4int parentID;
  G4int trackID;
  G4String parName;
  G4String detName;
  G4String procName;
  G4double locTime;
  G4ThreeVector parPos;
  G4ThreeVector parPostPos;
  G4ThreeVector parPrePos;
  G4ThreeVector parMom;
  G4ThreeVector parPostMom;
  G4ThreeVector parPreMom;
  G4double parKin;
  G4double parPostKin;
  G4double parPreKin;

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
