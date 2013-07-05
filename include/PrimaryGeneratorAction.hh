/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : include/PrimaryGeneratorAction.hh                                 *
*Source  : src/PrimaryGeneratorAction.cc                                     *
******************************************************************************
* - Source control code                                                      *
\*****************************************************************************/

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
   ~PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);  

  private:
    G4GeneralParticleSource* particleSource;
    
};

#endif

/*****************************************************************************/
