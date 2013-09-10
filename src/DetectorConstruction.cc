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
#include "G4RotationMatrix.hh"

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
  World_log = new G4LogicalVolume(World_sol,Gal,"World");		
  World_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),World_log,"World",0,false,0);  
  World_log->SetVisAttributes(G4VisAttributes::Invisible);

  BuildDetector();
           
  return World_phys;

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void DetectorConstruction::BuildDetector(){

  G4double ins_h = 5*cm;
  G4double ins_t = 5*cm;
  G4double out_h = 10*cm;
  G4double out_t = 2*cm;
  G4double blank = 0.5*cm;
  G4double bot_t = 2*cm;
  G4RotationMatrix *rotm = new G4RotationMatrix();
  G4ThreeVector pos;
  rotm->rotateZ(90*degree);
  
  G4VSolid* ins_sol = new G4Box("ins_sol",ins_h*0.5,ins_h*0.5,ins_t*0.5);
  G4VSolid* out_surf_sol = new G4Box("out_surf_sol",ins_h*0.5+blank,out_t*0.5,out_h*0.5);
  G4VSolid* out_edge_sol = new G4Box("out_edge_sol",out_t*0.5,out_t*0.5,out_h*0.5);
  G4VSolid* bot_sol= new G4Box("bot_sol",ins_h*0.5+blank,ins_h*0.5+blank,bot_t*0.5);

  G4LogicalVolume* ins_log = new G4LogicalVolume(ins_sol,Si,"ins_log");
  G4LogicalVolume* out_surf_log = new G4LogicalVolume(out_surf_sol,CdZnTe,"out_surf_log");
  G4LogicalVolume* out_edge_log = new G4LogicalVolume(out_edge_sol,CdZnTe,"out_edge_log");
  G4LogicalVolume* bot_log = new G4LogicalVolume(bot_sol,CdZnTe,"bot_log");
  ins_log->SetVisAttributes(G4Color::Yellow());
  out_surf_log->SetVisAttributes(G4Color::Magenta());
  out_edge_log->SetVisAttributes(G4Color::Magenta());
  bot_log->SetVisAttributes(G4Color::Blue());

  G4VPhysicalVolume* ins_phys;
  pos = G4ThreeVector(0,0,-ins_h*0.5);
  ins_phys = new G4PVPlacement(0,pos,ins_log,"ins_phys",World_log,0,0,true);

  G4VPhysicalVolume* out_surf_phys;
  pos = G4ThreeVector(0,blank+ins_h*0.5+out_t*0.5,-ins_h*0.5);
  out_surf_phys = new G4PVPlacement(0,pos,out_surf_log,"out_surf_phys",World_log,0,0,true);
  pos = G4ThreeVector(0,-blank-ins_h*0.5-out_t*0.5,-ins_h*0.5);
  out_surf_phys = new G4PVPlacement(0,pos,out_surf_log,"out_surf_phys",World_log,0,0,true);
  pos = G4ThreeVector(+blank+ins_h*0.5+out_t*0.5,0,-ins_h*0.5);
  out_surf_phys = new G4PVPlacement(rotm,pos,out_surf_log,"out_surf_phys",World_log,0,0,true);
  pos = G4ThreeVector(-blank-ins_h*0.5-out_t*0.5,0,-ins_h*0.5);
  out_surf_phys = new G4PVPlacement(rotm,pos,out_surf_log,"out_surf_phys",World_log,0,0,true);

  G4VPhysicalVolume* out_edge_phys;
  pos = G4ThreeVector(blank+ins_h*0.5+out_t*0.5,blank+ins_h*0.5+out_t*0.5,-ins_h*0.5);
  out_surf_phys = new G4PVPlacement(0,pos,out_edge_log,"out_edge_phys",World_log,0,0,true);
  pos = G4ThreeVector(-blank-ins_h*0.5-out_t*0.5,blank+ins_h*0.5+out_t*0.5,-ins_h*0.5);
  out_surf_phys = new G4PVPlacement(0,pos,out_edge_log,"out_edge_phys",World_log,0,0,true);
  pos = G4ThreeVector(blank+ins_h*0.5+out_t*0.5,-blank-ins_h*0.5-out_t*0.5,-ins_h*0.5);
  out_surf_phys = new G4PVPlacement(0,pos,out_edge_log,"out_edge_phys",World_log,0,0,true);
  pos = G4ThreeVector(-blank-ins_h*0.5-out_t*0.5,-blank-ins_h*0.5-out_t*0.5,-ins_h*0.5);
  out_surf_phys = new G4PVPlacement(0,pos,out_edge_log,"out_edge_phys",World_log,0,0,true);

  G4VPhysicalVolume* bot_phys;
  pos = G4ThreeVector(0,0,-ins_h*0.5-out_h*0.5+bot_t*0.5);
  bot_phys = new G4PVPlacement(0,pos,bot_log,"bot_phys",World_log,0,0,true);

  SensitiveDetector *sens_ins = new SensitiveDetector("/det/ins");
  SensitiveDetector *sens_out = new SensitiveDetector("/det/out");
  ins_log->SetSensitiveDetector(sens_ins);
  out_surf_log->SetSensitiveDetector(sens_out);
  out_edge_log->SetSensitiveDetector(sens_out);
  bot_log->SetSensitiveDetector(sens_out);
  G4SDManager *SDMan = G4SDManager::GetSDMpointer();
  SDMan->AddNewDetector(sens_ins);
  SDMan->AddNewDetector(sens_out);

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

/*void DetectorConstruction::BuildDetector(){

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
  G4LogicalVolume* det_ins_log = new G4LogicalVolume(det_ins_sol,Ge,"det_ins_log");  
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
*/
/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

#define GET_MATERIAL G4NistManager::Instance()->FindOrBuildMaterial

void DetectorConstruction::DefineMaterials(){

  G4String symbol;
  G4int z,ncomponents,natoms;
  G4double a,density;

  Air = GET_MATERIAL("G4_Air");
  Gal = GET_MATERIAL("G4_Galactic");
  Si = GET_MATERIAL("G4_Si");
  Ge = GET_MATERIAL("G4_Ge");

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
