/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : include/Run.hh                                                    *
*Source  : src/Run.cc                                                        *
******************************************************************************
* - This part is for data collection for every event                         *
\*****************************************************************************/

#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

class Run : public G4Run 
{

public :
  Run(const std::vector<G4String> SDName);
  ~Run();
  void RecordEvent(const G4Event*);
private :
  void Timing();
	
};

#endif

/*****************************************************************************/
