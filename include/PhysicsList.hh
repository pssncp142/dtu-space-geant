/*****************************************************************************\
*Author  : Yigit Dallilar                                                    *
*Date    : 05.07.2013                                                        *
*Project :                                                                   *
*Place   : DTU Space                                                         *
*Name    : include/PhysicsList.hh                                            *
*Source  : src/PhysicsList.cc                                                *
******************************************************************************
* - Options for physics                                                      *
\*****************************************************************************/

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"

/*ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo*/

class PhysicsList: public G4VUserPhysicsList
{

public:
    PhysicsList();
   ~PhysicsList();

protected:
    
  void ConstructParticle();
  void ConstructProcess(); 
  void RadioactiveDecay();
  void AtomicDeexcitation();
  void GeneralPhysics();
  void SetCuts();   
};

#endif

/*****************************************************************************/
