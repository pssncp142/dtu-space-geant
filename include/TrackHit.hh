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
  
private :	

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
