/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : src/TrackHit.cc                                                   *
*Header  : include/TrachHit.hh                                               *
******************************************************************************
* - Information array for the events                                         *
\*****************************************************************************/

#include "TrackHit.hh"

#include "G4VHit.hh"

G4Allocator<TrackHit> TrackHitAllocator;

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

TrackHit::TrackHit()
{
	
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

TrackHit::TrackHit(const TrackHit& right) : G4VHit()
{
	
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

TrackHit::~TrackHit()
{
	
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

const TrackHit& TrackHit::operator=(const TrackHit& right)
{
  return *this;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

G4int TrackHit::operator==(const TrackHit& right) const
{
  return (this==&right) ? 1 : 0;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void TrackHit::Print()
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void TrackHit::Draw()
{

}

/*****************************************************************************/
