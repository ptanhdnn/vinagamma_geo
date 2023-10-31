#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4VPhysicalVolume *createSmallBox(G4LogicalVolume *motherVolume, G4int i, G4int j, G4int k);
    G4VPhysicalVolume *createSourceBox(G4LogicalVolume *motherVolume);
    G4VPhysicalVolume *createDetector(G4LogicalVolume *motherVolume, G4double posX, G4double posY, G4double posZ);

    virtual G4VPhysicalVolume *Construct();

private:
    G4LogicalVolume *logicWorld;
};

#endif
