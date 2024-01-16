#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4SDManager.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4VPhysicalVolume *createSmallBox(G4LogicalVolume *motherVolume, G4int i, G4int j, G4int k, G4int);
    G4VPhysicalVolume *createSourceFrame(G4LogicalVolume *motherVolume);
    G4VPhysicalVolume *createSourceRod(G4LogicalVolume *motherVolume, G4double posRodX, G4double posRodY, G4double posRodZ);
    G4VPhysicalVolume *createDetector(G4LogicalVolume *motherVolume, G4double posX, G4double posY, G4double posZ, G4int totalNo);

    G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;};
    virtual G4VPhysicalVolume *Construct();
    // std::vector<G4LogicalVolume*> detectorLVs;

    G4int totalNo;

protected:
    G4LogicalVolume *fScoringVolume = nullptr;

private:
    G4LogicalVolume *logicDetector, *logicWorld;
    // MySensitiveDetector *senDet = new MySensitiveDetector("SensitiveDetector");

    virtual void ConstructSDandField();
    G4LogicalVolume* flv_voxel;

    // Khai báo thanh nguồn
    G4double dRod = 9.64 *mm;
    G4double dShell = 11.1 *mm;
    G4double lRod = 450. *mm;
    G4double lShell = 451.6 *mm;
    G4double massRod = 291. *g;
    G4double densityInox = 8. *g/cm3;
    G4double distance2rods = 2.6 *mm;
    G4double distanceAB = 150. *mm;
    G4double distanceAC = 250. *mm;

    //////////////////////////////////////////////////////////
    //                          //                          //
    //                          //                          //
    //                          //                          //
    //            A             //            B             //
    //                          //                          //
    //                          //                          //
    //                          //                          //
    //////////////////////////////////////////////////////////
    //                          //                          //
    //                          //                          //
    //                          //                          //
    //            C             //             D            //
    //                          //                          //
    //                          //                          //
    //                          //                          //
    //////////////////////////////////////////////////////////
};

#endif
