#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4RandomDirection.hh"
#include "G4RadioactiveDecay.hh"
#include "G4DecayTable.hh"
#include "G4NistManager.hh"
#include "G4Isotope.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
private:
    G4ParticleGun *fParticleGun;
    G4ThreeVector generateBeamFrame();
    G4ThreeVector SetPositionOfBeam(G4String nameSource, G4String nameFrame, G4int noRod);

    G4double positionOfFrameY, positionOfFrameZ;

public:
    MyPrimaryGenerator ();
    ~MyPrimaryGenerator ();

    virtual void GeneratePrimaries(G4Event*anEvent);
    
};

#endif