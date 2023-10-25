#include "construction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"

MyDetectorConstruction::MyDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume* MyDetectorConstruction::createSmallBox(G4LogicalVolume* motherVolume, G4int index) {
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* waterMaterial = nistManager->FindOrBuildMaterial("G4_WATER");

    G4double boxX = 30.0 * cm; // Chiều dài
    G4double boxY = 20.0 * cm; // Chiều rộng
    G4double boxZ = 40.0 * cm; // Chiều cao
    G4Box* solidBox = new G4Box("DetectorBox", boxX, boxY, boxZ);

    G4LogicalVolume* logicBox = new G4LogicalVolume(solidBox, waterMaterial, "BoxLogical");

    // Tính toán vị trí dựa trên chỉ số
    G4double posX = -120.0 * cm + (index % 4) * boxX;
    G4double posY = -80.0 * cm + ((index / 4) % 8) * boxY;
    G4double posZ = -40.0 * cm + (index / 32) * boxZ;
    G4ThreeVector position = G4ThreeVector(posX, posY, posZ);

    G4RotationMatrix* noRotation = nullptr;

    G4VPhysicalVolume* physicalBox = new G4PVPlacement(noRotation, position, logicBox, "BoxPhysical", motherVolume, false, index);

    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
    logicBox->SetVisAttributes(visAttributes);

    return physicalBox;
}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* airMaterial = nistManager->FindOrBuildMaterial("G4_AIR");

    G4double worldSizeX = 120.0 * cm;
    G4double worldSizeY = 160.0 * cm;
    G4double worldSizeZ = 80.0 * cm;
    G4Box* solidWorld = new G4Box("World", worldSizeX, worldSizeY, worldSizeZ);
    logicWorld = new G4LogicalVolume(solidWorld, airMaterial, "World");

    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    logicWorld->SetVisAttributes(visAttributes);

    G4int numDetectors = 32; // 4 hàng x 8 cột x 2 tầng
    for (G4int i = 0; i < numDetectors; i++) {
        createSmallBox(logicWorld, i);
    }

    return new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);
}
