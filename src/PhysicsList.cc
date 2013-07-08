/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : src/PhysicsList.cc                                                *
*Header  : include/PhysicsList.hh                                            *
******************************************************************************
* - Options for physics                                                      *
\*****************************************************************************/

#include "PhysicsList.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleTypes.hh"
#include "G4IonConstructor.hh"
#include "G4ProcessManager.hh"
#include "G4RadioactiveDecay.hh"

#include "G4KleinNishinaModel.hh"
#include "G4PEEffectFluoModel.hh"
#include "G4XrayRayleighModel.hh"
#include "G4LivermoreGammaConversionModel.hh"
#include "G4LivermoreIonisationModel.hh"
#include "G4LivermoreBremsstrahlungModel.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh" 
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4hIonisation.hh"
#include "G4hMultipleScattering.hh"
#include "G4Decay.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4EmProcessOptions.hh"
#include "G4LossTableManager.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

PhysicsList::PhysicsList() : G4VUserPhysicsList()
{

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

PhysicsList::~PhysicsList()
{ 

}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void PhysicsList::ConstructParticle()
{
  G4Geantino::GeantinoDefinition();
  G4Gamma::GammaDefinition();
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4Proton::ProtonDefinition();
  G4Neutron::NeutronDefinition();  
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();  
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void PhysicsList::ConstructProcess()
{
  AddTransportation();
  RadioactiveDecay();
  GeneralPhysics();
  AtomicDeexcitation();
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void PhysicsList::GeneralPhysics()
{
  G4ParticleTable::G4PTblDicIterator* par_iter = G4ParticleTable::GetParticleTable()->GetIterator();
  par_iter->reset();
  while( (*par_iter)() ){
    G4ParticleDefinition* particle = par_iter->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    
    if (particleName == "gamma"){	
      G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
      thePhotoElectricEffect->SetModel(new G4PEEffectFluoModel());      	
      pmanager->AddDiscreteProcess(thePhotoElectricEffect);
      
      G4ComptonScattering* theComptonScattering = new G4ComptonScattering();	
      theComptonScattering->SetModel(new G4KleinNishinaModel());
      pmanager->AddDiscreteProcess(theComptonScattering);
      
      G4GammaConversion* theGammaConversion = new G4GammaConversion();
      theGammaConversion->SetModel(new G4LivermoreGammaConversionModel());
      pmanager->AddDiscreteProcess(theGammaConversion);
      
      G4RayleighScattering* theRayleigh = new G4RayleighScattering();
      theRayleigh->SetModel(new G4XrayRayleighModel());
      pmanager->AddDiscreteProcess(theRayleigh);
    }
    if (particleName == "e-"){
      G4eMultipleScattering* msc = new G4eMultipleScattering();
      msc->SetStepLimitType(fUseDistanceToBoundary);
      pmanager->AddProcess(msc,-1,1,1);
      
      G4eIonisation* eIoni = new G4eIonisation();
      eIoni->SetEmModel(new G4LivermoreIonisationModel());
      pmanager->AddProcess(eIoni,-1,2,2);
      
      G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
      eBrem->SetEmModel(new G4LivermoreBremsstrahlungModel());
      pmanager->AddProcess(eBrem,-1,3,3);
    }
    if (particleName == "e+"){
      pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);
    }
    if (particleName == "GenericIon"){
      pmanager->AddProcess(new G4ionIonisation(),-1, 2, 2);
    }		

    G4Decay* theDecayProcess = new G4Decay();
    if (theDecayProcess->IsApplicable(*particle)) { 
      pmanager ->AddProcess(theDecayProcess);
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void PhysicsList::AtomicDeexcitation()
{
  G4UAtomicDeexcitation* di = new G4UAtomicDeexcitation;
  G4LossTableManager::Instance()->SetAtomDeexcitation(di);
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void PhysicsList::RadioactiveDecay()
{
  G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
  radioactiveDecay->SetHLThreshold(-1.*s);
  radioactiveDecay->SetICM(true);		//Internal Conversion
  radioactiveDecay->SetARM(true);		//Atomic Rearangement
  G4ProcessManager* pmanager = G4GenericIon::GenericIon()->GetProcessManager(); 
  pmanager->AddProcess(radioactiveDecay, 0, -1, 1);    
}

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

void PhysicsList::SetCuts()
{
  SetCutsWithDefault();
  //SetCutValue(0.001*mm, "gamma");
  //SetCutValue(0.001*mm, "e-");
  //SetCutValue(0.001*mm, "e+");
}

/*****************************************************************************/
