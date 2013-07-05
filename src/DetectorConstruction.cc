/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : src/DetectorConstruction.cc                                       *
*Header  : include/DetectorConstruction.hh                                   *
******************************************************************************
* - Geometry definitions                                                     *
\*****************************************************************************/

#include "G4RunManager.hh"
#include "G4SDManager.hh"

#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.h"
#include "G4NistManager.hh"

#include "G4Box.h"

#include "G4ThreeVector.h"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

DetectorConstruction::DetectorConstruction()
{
  worldSize = 200*m;
  
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/


DetectorConstruction::~DetectorConstruction()
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  
  World_sol = new G4Box("World",worldSize/2,worldSize/2,worldSize/2);   
  World_log = new G4LogicalVolume(World_sol,Air,"World");		
  World_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),World_log,"World",0,false,0);  
  World_log->SetVisAttributes(G4VisAttributes::Invisible);
    
  sensDet = new SensitiveDetector("/SensDetector");
     
  return World_phys;

}

#define GET_MATERIAL G4NistManager::Instance()->FindOrBuildMaterial

void Detector::DefineMaterials(){
  Air = GET_MATERIAL("G4_AIR");
}

/*****************************************************************************/
