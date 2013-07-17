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
#include "globals.hh"

#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4PhysicalConstants.hh"
#include "G4Color.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4ThreeVector.hh"

G4ThreeVector DetectorConstruction::origin;

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

DetectorConstruction::DetectorConstruction()
{
  worldSize = 1*m;
  
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/


DetectorConstruction::~DetectorConstruction()
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  DefineMaterials();

  World_sol = new G4Box("World",worldSize/2,worldSize/2,worldSize/2);   
  World_log = new G4LogicalVolume(World_sol,Air,"World");		
  World_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),World_log,"World",0,false,0);  
  World_log->SetVisAttributes(G4VisAttributes::Invisible);

  BuildDetector();
           
  return World_phys;

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void DetectorConstruction::BuildDetector(){

  G4int n_det = 100;
  G4double det_ins_width = 0.35*0.5*mm;
  G4double det_ins_blank = 0.15*mm;
  G4double det_ins_radius = 2.5*cm;

  G4double det_ins_rep_width = det_ins_width*2+det_ins_blank;
  G4double det_ins_cont_width = n_det*det_ins_rep_width*0.5;
  G4ThreeVector det_ins_pos = G4ThreeVector(0,0,-det_ins_cont_width);

  G4VSolid* det_ins_cont_sol = new G4Tubs("det_ins_cont_sol",0,det_ins_radius,det_ins_cont_width,0,2*pi*radian);
  G4LogicalVolume *det_ins_cont_log = new G4LogicalVolume(det_ins_cont_sol,Air,"det_ins_cont_log");
  G4VPhysicalVolume* det_ins_cont_phys = new G4PVPlacement(0,det_ins_pos,det_ins_cont_log,"det_ins_cont_phys",World_log,0,0,false);
  det_ins_cont_log->SetVisAttributes(G4VisAttributes::Invisible);
  G4VSolid* det_ins_sol = new G4Tubs("det_ins_sol",0,det_ins_radius,det_ins_width,0,2*pi);
  G4LogicalVolume* det_ins_log = new G4LogicalVolume(det_ins_sol,Si,"det_ins_log");  
  G4VPhysicalVolume* det_ins_phys = new G4PVReplica("det_ins_phys",det_ins_log,det_ins_cont_phys,kZAxis,n_det,det_ins_rep_width,0);
  det_ins_log->SetVisAttributes(G4Color::Yellow());

  G4double det_bot_width = 1*0.5*cm;
  G4double det_out_radius_diff = 1.5*cm;
  G4double det_out_thick = 1.*cm;
  G4double det_out_outer_radius = det_ins_radius+det_out_radius_diff;
  G4double det_out_inner_radius = det_ins_radius+det_out_radius_diff-det_out_thick;
  G4double det_out_width_diff = 1*0.5*cm;
  G4double det_out_width = det_ins_cont_width + det_out_width_diff+det_bot_width;
  G4ThreeVector det_out_pos = G4ThreeVector(0,0,-det_out_width);

  G4VSolid* det_out_sol = new G4Tubs("det_out_sol",det_out_inner_radius,det_out_outer_radius,det_out_width,0,2*pi*radian);
  G4LogicalVolume* det_out_log = new G4LogicalVolume(det_out_sol,CdZnTe,"det_out_log");
  G4VPhysicalVolume* det_out_phys = new G4PVPlacement(0,det_out_pos,det_out_log,"det_out_phys",World_log,0,0,false);
  det_out_log->SetVisAttributes(G4Color::Blue());

  //det_bot_width is somewhere above
  G4double det_bot_radius = det_out_inner_radius;
  G4ThreeVector det_bot_pos = G4ThreeVector(0,0,-det_out_width*2+det_bot_width);
  
  G4VSolid* det_bot_sol = new G4Tubs("det_bot_sol",0,det_bot_radius,det_bot_width,0,2*pi*radian);
  G4LogicalVolume* det_bot_log = new G4LogicalVolume(det_bot_sol,CdZnTe,"det_bot_log");
  G4VPhysicalVolume* det_bot_phys = new G4PVPlacement(0,det_bot_pos,det_bot_log,"det_bot_phys",World_log,0,0,false);
  det_bot_log->SetVisAttributes(G4Color::Magenta());

  G4ThreeVector origin = G4ThreeVector(0,0,-det_out_width);

  SensitiveDetector *sens_det_ins = new SensitiveDetector("/det/ins");
  SensitiveDetector *sens_det_out = new SensitiveDetector("/det/out");
  SensitiveDetector *sens_det_bot = new SensitiveDetector("/det/bot");
  det_ins_log->SetSensitiveDetector(sens_det_ins);
  det_out_log->SetSensitiveDetector(sens_det_out);
  det_bot_log->SetSensitiveDetector(sens_det_bot);

  G4SDManager *SDMan = G4SDManager::GetSDMpointer();
  SDMan->AddNewDetector(sens_det_ins);
  SDMan->AddNewDetector(sens_det_out);
  SDMan->AddNewDetector(sens_det_bot);

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

#define GET_MATERIAL G4NistManager::Instance()->FindOrBuildMaterial

void DetectorConstruction::DefineMaterials(){

  G4String symbol;
  G4int z,ncomponents,natoms;
  G4double a,density;

  Air = GET_MATERIAL("G4_AIR");
  Si = GET_MATERIAL("G4_Si");

  //CdZnTe
  G4Element* Cd = new G4Element("Cadmium", symbol="Cd", z=48, a=112.411*g/mole);
  G4Element* Zn = new G4Element("Zinc", symbol="Zn", z=30, a=65.39*g/mole);
  G4Element* Te = new G4Element("Tellurium", symbol="Te", z=52, a=127.6*g/mole);
  CdZnTe = new G4Material("CdZnTe",density=5.78*g/cm3,ncomponents=3);
  CdZnTe->AddElement(Cd,natoms=9);
  CdZnTe->AddElement(Zn,natoms=1);
  CdZnTe->AddElement(Te,natoms=10);
  
}

#undef GET_MATERIAL

/*****************************************************************************/
