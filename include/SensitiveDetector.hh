/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : include/SensitiveDetector.cc                                      *
*Source  : src/SensitiveDetector.cc                                          *
******************************************************************************
* - Collects info and add them to HitsCollection                             *
\*****************************************************************************/

#ifndef SensitiveDetector_h
#define SensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "TrackHit.hh"
#include "globals.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

class SensitiveDetector : public G4VSensitiveDetector
{

public : 
  SensitiveDetector(G4String);
  SensitiveDetector(const G4VSensitiveDetector &right);
  ~SensitiveDetector();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private :
  TrackHitCollection* HitColl_ins;
  TrackHitCollection* HitColl_out;

};

#endif

/*****************************************************************************/
