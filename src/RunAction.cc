/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : src/RunAction.cc                                                  *
*Header  : include/RunAction.hh                                              *
******************************************************************************
* - Jobs for the start and the end of the run                                *
\*****************************************************************************/

#include "RunAction.hh"
#include "Run.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

RunAction::RunAction()
{
  SDName.push_back("SensDetector");	
  NofRuns = 0;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

RunAction::~RunAction()
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

G4Run* RunAction::GenerateRun()
{
  Run* userRun = new Run(SDName);
  return userRun;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void RunAction::BeginOfRunAction(const G4Run* myRun)
{
  if (NofRuns >= 0)
    G4cout << G4endl <<
      "* + + + + + + + + + + + + + + + + + | Run (" << ++NofRuns << ") started | + + + + + + + + + + + + + + + + *" << 
      G4endl;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void RunAction::EndOfRunAction(const G4Run* myRun)
{

  if (NofRuns != 0)
    G4cout << G4endl << 
      "* + + + + + + + + + + + + + + + + + | Run (" << NofRuns << ")  finished | + + + + + + + + + + + + + + + *" << 
      G4endl;
}

/*****************************************************************************/
