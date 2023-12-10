#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    // Electromagnetic physics
    RegisterPhysics(new G4EmStandardPhysics);

    // Optical physics
    RegisterPhysics(new G4OpticalPhysics);

    // Decay physics
    RegisterPhysics(new G4DecayPhysics);
    
    // Radioactive Decay Physics
    RegisterPhysics(new G4RadioactiveDecayPhysics);
}

MyPhysicsList::~MyPhysicsList()
{}