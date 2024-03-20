#include "generator.hh"
#include "sourceInfo.hh"

#include <ctime>

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particleDef = particleTable->FindParticle("geantino");
    fParticleGun->SetParticleDefinition(particleDef);
    fParticleGun->SetParticleEnergy(100.*MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // G4cout << "Start beam" << G4endl;
    G4long seed = time(nullptr);
    CLHEP::HepRandom::setTheSeed(seed);

    // Define the Cobalt60
    if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {
        G4int Z = 27, A = 60;
        G4double ionCharge   = 0.*eplus;
        G4double excitEnergy = 0*keV;

        G4ParticleDefinition* ion
            = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(ionCharge);
    }
    // G4double energy = 0. *keV;

    G4ThreeVector posGenBeam = generateBeamFrame();
/*
    // Bước 2: Đặt vị trí pos tại một vị trí ngẫu nhiên trong hình trụ Cobalt
    G4double cobaltSourceRadius = 1.0 * cm; // Bán kính của hình trụ
    G4double cobaltSourceHeight = 10.0 * cm; // Chiều dài của hình trụ

    G4double randomRadius = cobaltSourceRadius * std::sqrt(G4UniformRand()); // Bán kính ngẫu nhiên trong hình trụ

    G4double randomAngle = G4UniformRand() * 2 * CLHEP::pi; // Góc ngẫu nhiên trong hình trụ

    G4double x = randomRadius * std::cos(randomAngle);
    G4double y = randomRadius * std::sin(randomAngle);
    G4double z = G4UniformRand() * cobaltSourceHeight; // Chọn một chiều dài ngẫu nhiên trong hình trụ

    G4ThreeVector pos(x, y, z);
*/
    // G4double cobaltX = (G4UniformRand() <0.5) ? -0.5 *cm : 0.5 *cm;
    // G4double cobaltY = 20 * (G4UniformRand() - 0.5) *cm;
    // G4double cobaltZ = 20 * (G4UniformRand() - 0.5) *cm;
    // G4ThreeVector pos(cobaltX, cobaltY, cobaltZ);

    // // Tạo hướng ngẫu nhiên cho các hạt trong không gian 3D
    // G4double theta = G4UniformRand() * CLHEP::pi;  // Góc θ ngẫu nhiên
    // G4double phi = G4UniformRand() * 2 * CLHEP::pi;  // Góc φ ngẫu nhiên

    G4double theta = -CLHEP::pi/4;
    G4double phi = 0.5*CLHEP::pi/3;

    G4ThreeVector mom(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));  // Hướng ngẫu nhiên

    // G4double energy = 10. *MeV;

    fParticleGun->SetParticlePosition(posGenBeam);
    fParticleGun->SetParticleMomentumDirection(mom);

    fParticleGun->GeneratePrimaryVertex(anEvent);
    // G4cout << "End beam" << G4endl;
}

// chọn random thanh nguồn phát với tên các thanh rodLVs
G4ThreeVector MyPrimaryGenerator::generateBeamFrame()
{
    // G4double randNumber = G4UniformRand();
    // G4double randSource = G4UniformRand();

    // G4int noSource = std::round(randSource*2) + 1;
    // G4String nameSource = "F1";
    // switch (noSource)
    // {
    // case 2:
    //     nameSource = "F2";
    //     break;
    // case 3:
    //     nameSource = "F3";
    //     break;
    // }

    // G4int noFrame = std::round(randNumber*3) + 1;
    // G4String nameFrame = "A";
    // switch (noFrame)
    // {
    // case 2:
    //     nameFrame = "B";
    //     break;
    // case 3:
    //     nameFrame = "C";
    //     break;
    // case 4:
    //     nameFrame = "D";
    //     break;
    // }



    // G4int noRod = std::round(randNumber*37);

    sourceInformation mySourceInfo;

    G4int numberOfRod = mySourceInfo.GetBeamRod();

    // if(mySourceInfo.CheckActivitySourceRod(nameSource, nameFrame, noRod)){
    //     G4String nameRodLV = nameSource + "_" + nameFrame + "_" + std::to_string(noRod) + "_RodLVs";
    // G4LogicalVolume *rodLV =  G4LogicalVolumeStore::GetInstance()->GetVolume(nameRodLV);
    // if (!rodLV) {
    //     G4cerr << "Logical volume not found: " << nameRodLV << G4endl;
    //     return G4ThreeVector();
    // }
    // G4cout << "name of rod logical volume: " << rodLV->GetName() << G4endl;

    return SetPositionOfBeam("F2", "B", numberOfRod);
    // }
    
}

G4ThreeVector MyPrimaryGenerator::SetPositionOfBeam(G4String nameSource, G4String nameFrame, G4int noRod)
{
    // Bước 2: Đặt vị trí pos tại một vị trí ngẫu nhiên trong hình trụ Cobalt

    G4double dRod = 9.64 *mm;
    G4double dShell = 11.1 *mm;
    G4double lRod = 450. *mm;
    G4double lShell = 451.6 *mm;
    G4double distance2rods = 2.6 *mm;
    G4double distanceAB = 50. *mm; //150*mm
    G4double distanceAC = 250. *mm;
    G4double distanceBetween2Frame = 2* 150. *mm;

    // Định nghĩa vị trí tọa độ theo thanh

    G4double positionOfSource = 0. *mm;
    if(nameSource == "F1"){
        positionOfSource = 2 * (38 * dShell + 37 * distance2rods + distanceAB);
    } else if(nameSource == "F3"){
        positionOfSource = - 2 * (38 * dShell + 37 * distance2rods + distanceAB);
    }
    
    if(nameFrame == "A"){
        G4double positionOfFrameY = -distanceAB/2. - (noRod+1) * dShell;
        G4double positionOfFrameZ = distanceAC/2. + lShell/2.;
    } else if(nameFrame == "B"){
        G4double positionOfFrameY =  distanceAB/2. + (noRod+1) * dShell;
        G4double positionOfFrameZ = distanceAC/2. + lShell/2.;
    } else if(nameFrame == "C"){
        G4double positionOfFrameY = -distanceAB/2. - (noRod+1) * dShell;
        G4double positionOfFrameZ = - distanceAC/2. - lShell/2.;
    } else if(nameFrame == "D"){
        G4double positionOfFrameY = distanceAB/2. + (noRod+1) * dShell;
        G4double positionOfFrameZ = - distanceAC/2. - lShell/2.;
    }

    G4double positionOfRodY = positionOfSource + positionOfFrameY;

    G4double positionOfRodZ = positionOfSource + positionOfFrameZ;

    G4double randomRadius = dRod/2. * std::sqrt(G4UniformRand()); // Bán kính ngẫu nhiên trong hình trụ

    G4double randomAngle = G4UniformRand() * 2 * CLHEP::pi; // Góc ngẫu nhiên trong hình trụ

    G4double x = randomRadius * std::cos(randomAngle);
    G4double y = randomRadius * std::sin(randomAngle) + positionOfRodY;
    G4double z = G4UniformRand() * lRod + positionOfRodZ; // Chọn một chiều dài ngẫu nhiên trong hình trụ

    G4ThreeVector pos(x, y, z);

    return pos;
}

/*
G4VPhysicalVolume *MyPrimaryGenerator::createSourceRod(G4LogicalVolume *motherVolume, G4int noRod, G4String nameFrame, G4double posRodX, G4double posRodY, G4double posRodZ)
{
    G4ThreeVector posRod = G4ThreeVector(posRodX, posRodY, posRodZ);

    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *rodMaterial = nistManager->FindOrBuildMaterial("G4_Co");
    G4Material *shellMaterial = nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");         // khai báo vỏ thanh inox cho thanh nguồn

// khai báo thanh nguồn bên trong
    G4Tubs *rodSolid = new G4Tubs("CoRod", 0., dRod/2., lRod/2., 0*deg, 360*deg);
    G4String rodName = nameFrame + "_" + std::to_string(noRod) + "_RodLVs";
    G4LogicalVolume *rodLVs = new G4LogicalVolume(rodSolid, rodMaterial, rodName);
    G4VPhysicalVolume *physicalRod = new G4PVPlacement(0, posRod, rodLVs, "RodPhys", motherVolume, false, 0);

// khai báo vỏ nguồn bên ngoài
    G4Tubs *shellSolid = new G4Tubs("CoShell", dRod/2., dShell/2., lShell/2., 0*deg,360*deg);
    G4LogicalVolume *shellLVs = new G4LogicalVolume(shellSolid, shellMaterial,"SourceShell");
    G4VPhysicalVolume *physicalShell = new G4PVPlacement(0, posRod, shellLVs, "ShellPhys", motherVolume, false, 0);

    G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour(0.0, 0.5, 0.3));
    shellLVs->SetVisAttributes(visAttributes);
}

G4VPhysicalVolume *MyPrimaryGenerator::createSourceFrame(G4LogicalVolume *motherVolume)
{
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
    
    G4NistManager *nistManager = G4NistManager::Instance();
    G4Material *AlMaterial = nistManager->FindOrBuildMaterial("G4_Al");
    G4Material *air = nistManager->FindOrBuildMaterial("G4_AIR");

    G4int noOfRods = 38;
    G4double frameX = 12.0 *mm;
    G4double frameY = noOfRods * dShell + (noOfRods - 1) * distance2rods + 2 * distanceAB/2.;
    G4double frameZ = 2 * distanceAC + 2 * lShell;

    G4Box *solidFrame = new G4Box("SourceCobalt", frameX, frameY, frameZ);
    G4LogicalVolume *frameLVs = new G4LogicalVolume(solidFrame, air, "FrameLogical");

    for (G4int i = 0; i < noOfRods; i ++){
        createSourceRod(motherVolume, i, "A", 0., - distanceAB/2. - (i+1) * dShell, distanceAC/2. + lShell/2.);
        createSourceRod(motherVolume, i, "B", 0., distanceAB/2. + (i+1) * dShell, distanceAC/2. + lShell/2.);
        createSourceRod(motherVolume, i, "C", 0., - distanceAB/2. - (i+1) * dShell, - distanceAC/2. - lShell/2.);
        createSourceRod(motherVolume, i, "D", 0., distanceAB/2. + (i+1) * dShell, - distanceAC/2. - lShell/2.);
    }
}
*/