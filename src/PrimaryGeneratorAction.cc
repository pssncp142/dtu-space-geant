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
#include "DetectorConstruction.hh"

#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
#include "G4Gamma.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/
 
PrimaryGeneratorAction::PrimaryGeneratorAction()
{  
  particleSource = new G4GeneralParticleSource();
  G4SPSPosDistribution *posDist;
  G4SPSAngDistribution *angDist;
  G4SPSEneDistribution *eneDist;

  //background source
  //particleSource->SetCurrentSourceIntensity(1);
  particleSource->SetParticleDefinition(G4Gamma::GammaDefinition());
  posDist = particleSource->GetCurrentSource()->GetPosDist();
  angDist = particleSource->GetCurrentSource()->GetAngDist();
  eneDist = particleSource->GetCurrentSource()->GetEneDist();
  posDist->SetCentreCoords(DetectorConstruction::origin);
  posDist->SetPosDisType("Surface");
  posDist->SetPosDisShape("Sphere");
  posDist->SetRadius(10*cm);
  angDist->SetAngDistType("iso");
  eneDist->SetEnergyDisType("Gauss");
  eneDist->SetMonoEnergy(600*keV);
  eneDist->SetBeamSigmaInE(250*keV);
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
