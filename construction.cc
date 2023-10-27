#include "construction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}
MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::createSmallBox(G4LogicalVolume *motherVolume, G4int i, G4int j, G4int k) {
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* waterMaterial = nistManager->FindOrBuildMaterial("G4_WATER");

    G4double boxX = 30.0 * cm; // Chiều dài
    G4double boxY = 20.0 * cm; // Chiều rộng
    G4double boxZ = 40.0 * cm; // Chiều cao
    G4Box* solidBox = new G4Box("DetectorBox", boxX, boxY, boxZ);

    G4LogicalVolume* logicBox = new G4LogicalVolume(solidBox, waterMaterial, "BoxLogical");

    // Nó sẽ đặt vị trí tại tâm của các thùng hàng
    //  nên sẽ phải trừ 1 nửa kích thước các chiều
    
    G4double posX = -97.5 *cm + 30.0 * 2 * i * cm + (i/2) * 15.0 *cm;
    G4double posY = -140.0 *cm + 20.0 * 2 * j * cm;
    G4double posZ = -50.0 *cm + 40.0 * 2 * k *cm;
    G4ThreeVector position = G4ThreeVector(posX, posY, 5.0 *cm + posZ + k * 10.0 *cm); // trục z cách mỗi đầu 5cm, giữa 2 thùng hàng cách nhau 10cm.

    G4RotationMatrix* noRotation = nullptr;

    G4VPhysicalVolume* physicalBox = new G4PVPlacement(noRotation, position, logicBox, "BoxPhysical", motherVolume, false, 0);

    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0, 0.5, 1.0));
    logicBox->SetVisAttributes(visAttributes);

    return physicalBox;
}

G4VPhysicalVolume *MyDetectorConstruction::createSourceBox(G4LogicalVolume *motherVolume){
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* sourceMaterial = nistManager->FindOrBuildMaterial("G4_Co");

    G4double sourceX = 12.0 *cm;
    G4double sourceY = 120.0 *cm;
    G4double sourceZ = 85.0 *cm;
    G4Box *solidSource = new G4Box("SourceCobalt", sourceX, sourceY, sourceZ);
    G4LogicalVolume* logicSource = new G4LogicalVolume(solidSource, sourceMaterial, "sourceLogical");

    G4double posSourceX = -0.5 *cm;
    G4double posSourceY = -5.0 *cm;
    G4double posSourceZ = -5.0 *cm;
    G4ThreeVector posSource = G4ThreeVector(posSourceX, posSourceY, posSourceZ);

    G4RotationMatrix* noRotation = nullptr;

    G4VPhysicalVolume* physicalSource = new G4PVPlacement(noRotation, posSource, logicSource, "sourcePhysical", motherVolume, false, 0);

    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0.0, 0.3, 0.5));
    logicSource->SetVisAttributes(visAttributes);

    return physicalSource;
}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* airMaterial = nistManager->FindOrBuildMaterial("G4_AIR");

    G4double worldSizeX = 132.5 * cm;
    G4double worldSizeY = 165.0 * cm;
    G4double worldSizeZ = 90.0 * cm;
    G4Box* solidWorld = new G4Box("World", worldSizeX, worldSizeY, worldSizeZ);
    logicWorld = new G4LogicalVolume(solidWorld, airMaterial, "World");

    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    logicWorld->SetVisAttributes(visAttributes);

    for (G4int k=0; k<2; k++){
        for (G4int j=0; j<8; j++){
            for (G4int i=0; i<4; i++){
                createSmallBox(logicWorld, i, j, k);
            }
        }
    }
    // createSourceBox(logicWorld);

    return new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "World", nullptr, false, 0);
}
