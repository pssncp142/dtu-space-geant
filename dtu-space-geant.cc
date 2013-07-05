/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : dtu-space-geant.cc                                                *
******************************************************************************
* - main file for the simulation                                             *
\*****************************************************************************/

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#endif

#include "G4RunManager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

#include "Randomize.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

int main(int argc,char** argv) {

  G4UImanager* UI = G4UImanager::GetUIpointer();  

  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  
  G4RunManager * runManager = new G4RunManager;

  DetectorConstruction* detCon = new DetectorConstruction();
  runManager->SetUserInitialization(detCon);

  PhysicsList* physList = new PhysicsList();
  runManager->SetUserInitialization(physList);  

  PrimaryGeneratorAction* prim  = new PrimaryGeneratorAction();        
  runManager->SetUserAction(prim);

  RunAction* runAct = new RunAction();
  runManager->SetUserAction(runAct);

  runManager->Initialize();
      
#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  UI->ApplyCommand("/control/execute vis.mac");          
#endif

#ifdef G4UI_USE
  G4UIExecutive * ui = new G4UIExecutive(argc,argv);      
  ui->SessionStart();
  delete ui;
#endif
     
#ifdef G4VIS_USE
  delete visManager;
#endif     

  delete runManager;

  return 0;
}

/*****************************************************************************/


