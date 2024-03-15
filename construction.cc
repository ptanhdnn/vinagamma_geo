#include "construction.hh"
#include "G4PVParameterised.hh"

MyDetectorConstruction::MyDetectorConstruction()
{
    // totalNo = 0;
    G4double pVwater = 4.*perCent;
    G4double pVclobenzen = 24.*perCent;
    G4double pVEthanol = 72.*perCent;
    G4double denWater  = 1.*g/cm3;
    G4double denCloBenzen = 1.11*g/cm3;
    G4double denEthanol = 789*kg/m3;
    
    G4NistManager *nistManager = G4NistManager::Instance();

    denECB =  pVwater*denWater + pVclobenzen*denCloBenzen + pVEthanol*denEthanol;
    G4double pMwater = pVwater*denWater/(pVwater*denWater + pVclobenzen*denCloBenzen + pVEthanol*denEthanol);
    G4double pMclobenzen = pVclobenzen*denCloBenzen/(pVwater*denWater + pVclobenzen*denCloBenzen + pVEthanol*denEthanol);
    G4double pMethanol = pVEthanol*denEthanol/(pVwater*denWater + pVclobenzen*denCloBenzen + pVEthanol*denEthanol);
    G4Material* water = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
    G4Material* clobenzen = G4NistManager::Instance()->FindOrBuildMaterial("G4_CHLOROBENZENE");
    G4Material* ethanol = G4NistManager::Instance()->FindOrBuildMaterial("G4_ETHYL_ALCOHOL");
    ECB = new G4Material("ECB",denECB,3);
    ECB->AddMaterial(water,pMwater);
    ECB->AddMaterial(clobenzen,pMclobenzen);
    ECB->AddMaterial(ethanol,pMethanol);
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::createSmallBox(G4LogicalVolume *motherVolume, G4int i, G4int j, G4int k, G4int totalNo) {
    G4NistManager *nistManager = G4NistManager::Instance();
    // Tạo phần vật liệu của vỏ thùng là nhôm
    G4Material *boxMaterial = nistManager->FindOrBuildMaterial("G4_Al");
    // vật liệu của nắp thùng là không khí
    G4Material *air = nistManager->FindOrBuildMaterial("G4_AIR");
    // vật liệu dummy
    G4Material *dummyMaterial = nistManager->FindOrBuildMaterial("G4_Fe");

    G4double thickOfBox = 0.3 *cm;

    G4double airGap = 1. *cm;

// thùng hàng
    G4double boxX = 30.0 * cm; // Chiều dài
    G4double boxY = 20.0 * cm; // Chiều rộng
    G4double boxZ = 40.0 * cm; // Chiều cao

// Dummy
    // kích thước dummy = kích thước thùng hàng - bề dày - airGap
    G4double dummyX = 28.7 * cm; // Chiều dài
    G4double dummyY = 18.7 * cm; // Chiều rộng
    G4double dummyZ = 38.7 * cm; // Chiều cao

    G4Box *solidOuterBox = new G4Box("OuterBox", boxX, boxY, boxZ);
    G4LogicalVolume *logicOuterBox = new G4LogicalVolume(solidOuterBox, boxMaterial, "boxLVs");    
    G4Box *solidInnerBox = new G4Box("innerBox", boxX-thickOfBox, boxY-thickOfBox, boxZ-thickOfBox);
    G4LogicalVolume *logicInnerBox = new G4LogicalVolume(solidInnerBox, air, "airGapLVs");

    G4Box *solidOuterDummy = new G4Box("OuterDummy", dummyX, dummyY, dummyZ);
    G4LogicalVolume *logicOuterDummy = new G4LogicalVolume(solidOuterDummy, dummyMaterial, "dummyLVs");
    G4Box *solidInnerDummy = new G4Box("InnerDummy", dummyX-thickOfBox, dummyY-thickOfBox, dummyZ-thickOfBox);
    G4LogicalVolume *logicInnerDummy = new G4LogicalVolume(solidInnerDummy, air, "airLVs");

    // G4SubtractionSolid *solidBox = new G4SubtractionSolid("BoxSolid", solidOuterBox, solidInnerBox);

    // G4LogicalVolume *logicPac = new G4LogicalVolume(solidPackage, boxMaterial, "packageLogical");
    // G4LogicalVolume *logicBox = new G4LogicalVolume(solidBox, boxMaterial, "boxLogical");   /

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

    G4VPhysicalVolume *physicalBox = new G4PVPlacement(0, position, logicOuterBox, "BoxPhysical", motherVolume, false, 0);
    G4VPhysicalVolume *physicalDummy = new G4PVPlacement(0, position, logicOuterDummy, "DummyPhysical", motherVolume, false, 0);

     // Tạo phần thể tích nắp, thay bằng không khí
    G4double topBoxX = 29.5 *cm;
    G4double topBoxY = 19.5 *cm;
    G4double topBoxZ = 0.25 *cm;
    G4Box *solidTop = new G4Box("solidTop", topBoxX, topBoxY, topBoxZ);
    G4LogicalVolume *logicTop = new G4LogicalVolume(solidTop, air, "topLogical");

    G4double posTopX = -97.5 *cm + 30.0 * 2 * i * cm + (i/2) * 15.0 *cm;
    G4double posTopY = -140.0 *cm + 20.0 * 2 * j * cm;
    G4double posTopZ = -5.25 *cm + 40.0 * 2 * k *cm + k *10.0 *cm;
    G4ThreeVector posTop = G4ThreeVector(posTopX, posTopY, posTopZ);

    G4VPhysicalVolume *physicalTop = new G4PVPlacement(0, posTop, logicTop, "TopPhysical", motherVolume, false, 0);

    // // Màu sắc của logicBox
    // G4VisAttributes *visAttributesBox = new G4VisAttributes(G4Colour(1.0, 0.5, 1.0));
    // logicBox->SetVisAttributes(visAttributesBox);

    // // Màu sắc của logicPackage
    // G4VisAttributes *visAttributesPackage = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    // logicPackage->SetVisAttributes(visAttributesPackage);

    // G4VisAttributes *visTop = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    // logicTop->SetVisAttributes(visTop);

    // ===================================================================================
    // Tạo các detector trong mỗi thùng hàng
    // ===================================================================================    
    createDetector(motherVolume, posX-boxX, posY-boxY, posZ-boxZ, totalNo);

    return physicalBox;
}

G4VPhysicalVolume *MyDetectorConstruction::createSourceRod(G4LogicalVolume *motherVolume, G4String nameSource, G4int noRod, G4String nameFrame, G4double posRodX, G4double posRodY, G4double posRodZ)
{
    G4ThreeVector posRod = G4ThreeVector(posRodX, posRodY, posRodZ);

    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *rodMaterial = nistManager->FindOrBuildMaterial("G4_Co");
    G4Material *shellMaterial = nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");         // khai báo vỏ thanh inox cho thanh nguồn

// khai báo thanh nguồn bên trong
    G4Tubs *rodSolid = new G4Tubs("CoRod", 0., dRod/2., lRod/2., 0*deg, 360*deg);
    G4String rodName = nameSource + "_" + nameFrame + "_" + std::to_string(noRod) + "_RodLVs";
    G4LogicalVolume *rodLVs = new G4LogicalVolume(rodSolid, rodMaterial, rodName);
    G4VPhysicalVolume *physicalRod = new G4PVPlacement(0, posRod, rodLVs, "RodPhys", motherVolume, false, 0);

// khai báo vỏ nguồn bên ngoài
    G4Tubs *shellSolid = new G4Tubs("CoShell", dRod/2., dShell/2., lShell/2., 0*deg, 360*deg);
    G4LogicalVolume *shellLVs = new G4LogicalVolume(shellSolid, shellMaterial,"SourceShell");
    G4VPhysicalVolume *physicalShell = new G4PVPlacement(0, posRod, shellLVs, "ShellPhys", motherVolume, false, 0);

    G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour(0.0, 0.5, 0.3));
    shellLVs->SetVisAttributes(visAttributes);
}

G4VPhysicalVolume *MyDetectorConstruction::createSourceFrame(G4LogicalVolume *motherVolume)
{
/*
    G4double dRod = 9.64 *mm;
    G4double dShell = 11.1 *mm;
    G4double lRod = 450. *mm;
    G4double lShell = 451.6 *mm;
    G4double massRod = 291. *g;
    G4double densityInox = 8. *g/cm3;

    Khoảng cách giữa 2 tầng ngang là 15cm
    khoảng cách giữa 2 tầng dọc là 25cm

    ////////////////////////////YY////////////////////////////
    //                          //                          //
    //                          //                          //
    //                          //                          //
    //            A             //            B             //
    //                          //                          //
    //                          //                          //
    //                          //                          //
    ZZ//////////////////////////////////////////////////////ZZ
    //                          //                          //
    //                          //                          //
    //                          //                          //
    //            C             //             D            //
    //                          //                          //
    //                          //                          //
    //                          //                          //
    ////////////////////////////YY////////////////////////////
*/      
    
    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *AlMaterial = nistManager->FindOrBuildMaterial("G4_Al");
    G4Material *air = nistManager->FindOrBuildMaterial("G4_AIR");

    G4int noOfRods = 38;
    G4double frameX = dShell;
    G4double frameY = 2 * (noOfRods * dShell + (noOfRods - 1) * distance2rods + distanceAB);
    G4double frameZ = 2 * distanceAC + 2 * lShell;

    G4Box *solidFrame = new G4Box("SourceCobalt", frameX, frameY, frameZ);
    G4LogicalVolume *frameLVs = new G4LogicalVolume(solidFrame, air, "FrameLogical");

    for (G4int i = 0; i < noOfRods; i ++){
        // Frame 1 (left)
        createSourceRod(motherVolume, "F1", i, "A", 0., -frameY - distanceAB/2. - (i+0.5) * dShell, distanceAC/2. + lShell/2.);
        createSourceRod(motherVolume, "F1", i, "B", 0., -frameY + distanceAB/2. + (i+0.5) * dShell, distanceAC/2. + lShell/2.);
        createSourceRod(motherVolume, "F1", i, "C", 0., -frameY - distanceAB/2. - (i+0.5) * dShell, - distanceAC/2. - lShell/2.);
        createSourceRod(motherVolume, "F1", i, "D", 0., -frameY + distanceAB/2. + (i+0.5) * dShell, - distanceAC/2. - lShell/2.);

        // Frame 2
        createSourceRod(motherVolume, "F2", i, "A", 0., - distanceAB/2. - (i+0.5) * dShell, distanceAC/2. + lShell/2.);
        createSourceRod(motherVolume, "F2", i, "B", 0., distanceAB/2. + (i+0.5) * dShell, distanceAC/2. + lShell/2.);
        createSourceRod(motherVolume, "F2", i, "C", 0., - distanceAB/2. - (i+0.5) * dShell, - distanceAC/2. - lShell/2.);
        createSourceRod(motherVolume, "F2", i, "D", 0., distanceAB/2. + (i+0.5) * dShell, - distanceAC/2. - lShell/2.);

        // // Frame 3 (right)
        createSourceRod(motherVolume, "F3", i, "A", 0., frameY - distanceAB/2. - (i+0.5) * dShell, distanceAC/2. + lShell/2.);
        createSourceRod(motherVolume, "F3", i, "B", 0., frameY + distanceAB/2. + (i+0.5) * dShell, distanceAC/2. + lShell/2.);
        createSourceRod(motherVolume, "F3", i, "C", 0., frameY - distanceAB/2. - (i+0.5) * dShell, - distanceAC/2. - lShell/2.);
        createSourceRod(motherVolume, "F3", i, "D", 0., frameY + distanceAB/2. + (i+0.5) * dShell, - distanceAC/2. - lShell/2.);
    }
}

G4VPhysicalVolume *MyDetectorConstruction::createDetector(G4LogicalVolume *motherVolume, G4double posX, G4double posY, G4double posZ, G4int totalNo){

    G4double detSizeX = 2.95 *cm;
    G4double detSizeY = 1.95 *cm;
    G4double detSizeZ = 3.95 *cm;

    G4double d_det = 1.5 *cm;
    G4double h_det = 6.0 *cm;
    detMass  = CLHEP::pi * (d_det/2) * (d_det/2) * h_det * denECB;

    // G4cout << "+++++++++++++++++++++++++++++++++++++++++++++" << G4endl;
    // G4cout << "posDetX in loop: " << G4endl;
    for (G4int k=0; k<9; k++){  //9
        for (G4int j=0; j<9; j++){
            for (G4int i=0; i<9;i++){
                G4Box *solidDetector = new G4Box("solidDet", detSizeX, detSizeY, detSizeZ);
                G4String detID = std::to_string(totalNo) + "_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k);
                logicDetector = new G4LogicalVolume(solidDetector, ECB, "detLVs_" + detID);
                // G4double posDetX = posX + detSizeX * 2 * (i+1);
                // G4double posDetY = posY + detSizeY * 2 *(j+1);
                G4double posDetX = posX + detSizeX;
                G4double posDetY = posY + detSizeY;
                G4double posDetZ = posZ + detSizeZ * 2 *(k+1);
                G4ThreeVector posDet = G4ThreeVector(posDetX, posDetY, posDetZ);
                G4VPhysicalVolume *physicalDetector = new G4PVPlacement(0, posDet, logicDetector, "detPhys_" + detID, motherVolume, false, totalNo, false);
            }
        }
    }

    for (G4int i = 0; i < 2)

    // for (G4int k =0; k<2; k++){
    //     for (G4int j=0; j<2; j++){
    //         for (G4int i=0; i<2; i++){
    //             G4Box *solidDetector = new G4Box("solidDet", detSizeX, detSizeY, detSizeZ);
    //             G4String detID = std::to_string(totalNo) + "_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k);
    //             logicDetector = new G4LogicalVolume(solidDetector, ECB, "detLVs_" + detID);

    //             G4double posDetX = posX
    //         }
    //     }
    // }
    // G4cout << "===========================================" << G4endl
    //    << "Get Total Number " << totalNo << G4endl
    //    << "==========================================" << G4endl;
}

G4VPhysicalVolume *MyDetectorConstruction::createDetectorOutsideSystem(G4LogicalVolume *motherVolume, G4double posX, G4double posY, G4double posZ, G4int totalNo)
{

}

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *airMaterial = nistManager->FindOrBuildMaterial("G4_AIR");

    G4double worldSizeX = 132.5 *cm;
    G4double worldSizeY = 165.0 *cm;
    G4double worldSizeZ = 90.0 *cm;
    G4Box *solidWorld = new G4Box("World", worldSizeX, worldSizeY, worldSizeZ);
    logicWorld = new G4LogicalVolume(solidWorld, airMaterial, "World");

    G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    logicWorld->SetVisAttributes(visAttributes);
    G4int totalNo = 0;
    for (G4int k=0; k<2; k++){                  // tầng
        for (G4int j=0; j<8; j++){              // hàng dài (bề ngang)
            for (G4int i=0; i<4; i++){          // hàng ngắn (bề dọc)
            // theo thứ tự sẽ là từ dưới lên trên, lần lượt hàng dài sẽ thêm 4 ô ngắn
                createSmallBox(logicWorld, i, j, k, totalNo);
                totalNo++;
            }
        }
    }


    createSourceFrame(logicWorld);

    ConstructSDandField();
    // delete senDet;

    return new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "World", nullptr, false, 0);

}

void MyDetectorConstruction::ConstructSDandField()
{
    G4cout << "Create SD collection " << G4endl;
    for(G4int no = 0; no < 8; no++){
        for (G4int k=0; k<9; k++){
            for (G4int j=0; j<9; j++){
                for (G4int i=0; i<9; i++){
                    G4String detName = "detLVs_" + std::to_string(no) + "_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k);
                    G4String hcofDetName = "hc_" + std::to_string(no) + "_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k);
                    auto aTrackerSD = new MySensitiveDetector(detName, hcofDetName);
                    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
                    SetSensitiveDetector(detName, aTrackerSD, true);
                }
            }
        }
    }
}