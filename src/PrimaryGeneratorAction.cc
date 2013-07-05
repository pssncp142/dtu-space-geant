/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : src/PrimaryGeneratorAction.cc                                     *
*Header  : include/PrimaryGeneratorAction.hh                                 *
******************************************************************************
* - Source control code                                                      *
\*****************************************************************************/

#include "PrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/
 
PrimaryGeneratorAction::PrimaryGeneratorAction()
{  
  particleSource = new G4GeneralParticleSource();
}   

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleSource;
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
  particleSource->GeneratePrimaryVertex(anEvent);
}

/*****************************************************************************/
