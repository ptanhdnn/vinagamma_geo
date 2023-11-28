#include "construction.hh"
#include "G4PVParameterised.hh"

typedef G4LogicalVolume G4LV;
typedef G4PVPlacement G4PVP;
typedef G4VisAttributes G4VA;

MyDetectorConstruction::MyDetectorConstruction()
{}
MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::createSmallBox(G4LogicalVolume *motherVolume, G4int i, G4int j, G4int k) {
    G4NistManager *nistManager = G4NistManager::Instance();
    // Tạo phần vật liệu của vỏ thùng là nhôm
    G4Material *boxMaterial = nistManager->FindOrBuildMaterial("G4_Al");
    // Tạo phần vật liệu của nắp thùng là không khí
    G4Material *topMaterial = nistManager->FindOrBuildMaterial("G4_AIR");

    G4double boxX = 30.0 * cm; // Chiều dài thùng hàng
    G4double boxY = 20.0 * cm; // Chiều rộng thùng hàng
    G4double boxZ = 40.0 * cm; // Chiều cao thùng hàng
    G4Box *solidOriginalBox = new G4Box("OriginalBox", boxX, boxY, boxZ);

    // Tạo phần thể tích không gian vật liệu bên trong thùng hàng
    G4double insideBoxX = 29.5 *cm;
    G4double insideBoxY = 19.5 *cm;
    G4double insideBoxZ = 39.5 *cm;
    G4Box *solidPackage = new G4Box("package", insideBoxX, insideBoxY, insideBoxZ);
    G4SubtractionSolid *solidBox = new G4SubtractionSolid("BoxSolid", solidOriginalBox, solidPackage);
    G4LogicalVolume *logicPackage = new G4LogicalVolume(solidPackage, boxMaterial, "packageLogical");
    G4LogicalVolume *logicBox = new G4LogicalVolume(solidBox, boxMaterial, "boxLogical");   //thùng hàng

    // Geant4 sẽ đặt vị trí tại tâm của các thùng hàng không phải tại cạnh của box
    //  nên sẽ phải trừ 1 nửa kích thước của các chiều của thùng hàng
    /*
    Các tọa độ X, Y, Z tương ứng với ngang (4 box), dài(8 box), và cao (2 box)
    do kích thước ban đầu đặt X,Y,Z theo 1 box ở trên.
    Với posX: 1box (30*2) *4 +15cm ở giữa 2 box + 5*2cm (mỗi bên cách khung motherBox 5cm) = 265cm
              265cm = 2 *132.5cm = kích thước chiều X của motherBox => OK
            * Lẽ ra vị trí đầu tiên của posX sẽ phải bắt đầu từ -(132.5-5(cách khung 5cm)cm)
              là vị trí -127.5cm. Nhưng Geant4 đặt vị trí tại tâm của thùng hàng nên vị trí ban đầu
              phải dịch +30cm (bằng nửa chiều dài của box X) => -127.5 +30 = -97.5cm

    Với tương tự posY thì vị trí của box đầu tiên theo trục Y là -(165 -5 -20)= -145cm
    Với posZ -(90 -5 -40) = -45cm
    */
    G4double posX = -97.5 *cm + 30.0 * 2 * i * cm + (i/2) * 15.0 *cm;
    G4double posY = -140.0 *cm + 20.0 * 2 * j * cm;
    G4double posZ = -45.0 *cm + 40.0 * 2 * k *cm +k *10.0 *cm;
    G4ThreeVector position = G4ThreeVector(posX, posY, posZ);

    G4VPhysicalVolume *physicalBox = new G4PVPlacement(0, position, logicBox, "BoxPhysical", motherVolume, false, 0);

     // Tạo phần thể tích nắp, thay bằng không khí
    G4double topBoxX = 29.5 *cm;
    G4double topBoxY = 19.5 *cm;
    G4double topBoxZ = 0.25 *cm;
    G4Box *solidTop = new G4Box("solidTop", topBoxX, topBoxY, topBoxZ);
    G4LogicalVolume *logicTop = new G4LogicalVolume(solidTop, topMaterial, "topLogical");

    G4double posTopX = -97.5 *cm + 30.0 * 2 * i * cm + (i/2) * 15.0 *cm;
    G4double posTopY = -140.0 *cm + 20.0 * 2 * j * cm;
    G4double posTopZ = -5.25 *cm + 40.0 * 2 * k *cm + k *10.0 *cm;
    G4ThreeVector posTop = G4ThreeVector(posTopX, posTopY, posTopZ);

    G4VPhysicalVolume *physicalTop = new G4PVPlacement(0, posTop, logicTop, "TopPhysical", motherVolume, false, 0);

    // Màu sắc của logicBox
    G4VisAttributes *visAttributesBox = new G4VisAttributes(G4Colour(1.0, 0.5, 1.0));
    logicBox->SetVisAttributes(visAttributesBox);

    // Màu sắc của logicPackage
    G4VisAttributes *visAttributesPackage = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    logicPackage->SetVisAttributes(visAttributesPackage);

    G4VisAttributes *visTop = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    logicTop->SetVisAttributes(visTop);

    createDetector(motherVolume, posX-boxX, posY-boxY, posZ-boxZ);

    return physicalBox;
}

G4VPhysicalVolume *MyDetectorConstruction::createSourceBox(G4LogicalVolume *motherVolume){
    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *sourceMaterial = nistManager->FindOrBuildMaterial("G4_Co");

    G4double sourceX = 6.0 *cm;
    G4double sourceY = 60.0 *cm;
    G4double sourceZ = 42.5 *cm;
    G4Box *solidSource = new G4Box("SourceCobalt", sourceX, sourceY, sourceZ);
    G4LogicalVolume *logicSource = new G4LogicalVolume(solidSource, sourceMaterial, "sourceLogical");

    // G4double posSourceX = -0.5 *cm;
    // G4double posSourceY = -5.0 *cm;
    // G4double posSourceZ = -5.0 *cm;
    G4ThreeVector posSource = G4ThreeVector(0., 0., 0.);

    G4VPhysicalVolume *physicalSource = new G4PVPlacement(0, posSource, logicSource, "sourcePhysical", motherVolume, false, 0);

    G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour(0.0, 0.3, 0.5));
    logicSource->SetVisAttributes(visAttributes);

    return physicalSource;
}

G4VPhysicalVolume *MyDetectorConstruction::createDetector(G4LogicalVolume *motherVolume, G4double posX, G4double posY, G4double posZ){
    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *detMaterial = nistManager->FindOrBuildMaterial("G4_AIR");

    G4double detSizeX = 2.95 *cm;
    G4double detSizeY = 1.95 *cm;
    G4double detSizeZ = 3.95 *cm;
    // G4cout << "+++++++++++++++++++++++++++++++++++++++++++++" << G4endl;
    // G4cout << "posDetX in loop: " << G4endl;
    for (G4int k=0; k<10; k++){
        for (G4int j=0; j<10; j++){
            for (G4int i=0; i<10;i++){
                G4Box *solidDetector = new G4Box("solidDet", detSizeX*2, detSizeY*2, detSizeZ*2);
                logicDetector = new G4LogicalVolume(solidDetector, detMaterial, "detector_LV");
                G4double posDetX = posX + detSizeX * (i+1);
                G4double posDetY = posY + detSizeY *(j+1);
                G4double posDetZ = posZ + detSizeZ *(k+1);
                G4ThreeVector posDet = G4ThreeVector(posDetX, posDetY, posDetZ);
                // G4cout << posDetX << G4endl;
                G4VPhysicalVolume *physicalDetector = new G4PVPlacement(0, posDet, logicDetector, "detPhysical", motherVolume, false, 0);
                // detectorLVs.push_back(logicDetector);
            }
        }
    }
    // fScoringVolume = logicDetector;
    // In ra tên của tất cả các detector
    // for (size_t i = 0; i < detectorLVs.size(); ++i) {
    //     G4cout << "Detector " << detectorLVs.size() << " name: " << detectorLVs[i]->GetName() << G4endl;
    // }
}

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *airMaterial = nistManager->FindOrBuildMaterial("G4_AIR");
    G4Material *detMaterial = nistManager->FindOrBuildMaterial("G4_WATER");

    G4double worldSizeX = 132.5 *cm;
    G4double worldSizeY = 165.0 *cm;
    G4double worldSizeZ = 90.0 *cm;
    G4Box *solidWorld = new G4Box("World", worldSizeX, worldSizeY, worldSizeZ);
    logicWorld = new G4LogicalVolume(solidWorld, airMaterial, "World");

    G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    logicWorld->SetVisAttributes(visAttributes);

    for (G4int k=0; k<1; k++){
        for (G4int j=0; j<4; j++){
            for (G4int i=0; i<2; i++){
                createSmallBox(logicWorld, i, j, k);
            }
        }
    }

    createSourceBox(logicWorld);

    ConstructSDandField();
    // delete senDet;

    return new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "World", nullptr, false, 0);

}

void MyDetectorConstruction::ConstructSDandField()
{
    G4cout << "Start calling SD part: " << G4endl;
    G4String trackerDetetectorSDname = "TrackerDetSD";
    auto aTrackerSD = new MySensitiveDetector(trackerDetetectorSDname, "TrackerHitCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
    SetSensitiveDetector("detector_LV", aTrackerSD, true);
}