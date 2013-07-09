/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : include/DetectorConstruction.hh                                   *
*Source  : src/DetectorConstruction.cc                                       *
******************************************************************************
* - Header for src/DetectorConstruction.cc                                   *
\*****************************************************************************/

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class SensitiveDetector;
class G4Material;

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
  DetectorConstruction();
  ~DetectorConstruction();
  
  G4VPhysicalVolume* Construct();                 
  
  private:
  
  void DefineMaterials();
  void BuildDetector();

  G4double worldSize;    

  G4Material* Air; 
  G4Material* CdZnTe;
  
  G4VSolid* World_sol;  
  G4LogicalVolume* World_log;  
  G4VPhysicalVolume* World_phys;  

};

#endif

/*****************************************************************************/
