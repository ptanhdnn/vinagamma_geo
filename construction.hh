#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4VPhysicalVolume* createSmallBox(G4LogicalVolume* motherVolume, G4int index);

    virtual G4VPhysicalVolume* Construct();

private:
    G4LogicalVolume* logicWorld;
};

#endif
