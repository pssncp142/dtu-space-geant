/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : include/RunAction.cc                                              *
*Source  : src/RunAction.cc                                                  *
******************************************************************************
* - Jobs for the start and the end of the run                                *
\*****************************************************************************/

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <vector>

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

class RunAction : public G4UserRunAction
{

public:
  RunAction();
  ~RunAction();

  G4Run* GenerateRun();
  void   BeginOfRunAction(const G4Run*);
  void   EndOfRunAction(const G4Run*);
    
private:
  G4int NofRuns;
  std::vector<G4String> SDName; 

};

#endif

/*****************************************************************************/
