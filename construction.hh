#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4VPhysicalVolume* createSmallBox(G4LogicalVolume* motherVolume, G4int i, G4int j, G4int k);
    G4VPhysicalVolume* createSourceBox(G4LogicalVolume* motherVolume);

    virtual G4VPhysicalVolume* Construct();

private:
    G4LogicalVolume* logicWorld;
};

#endif
