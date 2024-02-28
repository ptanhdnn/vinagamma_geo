#include "generator.hh"
#include <ctime>

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4long seed = time(nullptr);
    CLHEP::HepRandom::setTheSeed(seed);
    double halfLifeInSeconds = 5.26 * 365.25 * 24 * 3600; // 5.26 years
    double activityCi = 187.0; // Activity in kiloCuries
    double lambda = log(2.0) / halfLifeInSeconds; // Calculate decay constant

    // Calculate the number of decays per second (Becquerels)
    double activityBq = activityCi * 1e3 * 3.7e10; // 1 Ci = 3.7e10 Bq
    double decayConstant = lambda * activityBq;

    // Define the Cobalt60
    G4String elementName = "Cobalt";
    G4int Z = 27;
    G4int A = 60;
    G4double charge = 0. *eplus;
    // G4double energy = 0. *keV;

    generateBeamFrame();
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
    G4double cobaltX = (G4UniformRand() <0.5) ? -0.5 *cm : 0.5 *cm;
    G4double cobaltY = 20 * (G4UniformRand() - 0.5) *cm;
    G4double cobaltZ = 20 * (G4UniformRand() - 0.5) *cm;
    G4ThreeVector pos(cobaltX, cobaltY, cobaltZ);

    // // Tạo hướng ngẫu nhiên cho các hạt trong không gian 3D
    // G4double theta = G4UniformRand() * CLHEP::pi;  // Góc θ ngẫu nhiên
    // G4double phi = G4UniformRand() * 2 * CLHEP::pi;  // Góc φ ngẫu nhiên

    G4double theta = -CLHEP::pi/4;
    G4double phi = 0.5*CLHEP::pi/3;

    G4ThreeVector mom(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));  // Hướng ngẫu nhiên

    G4double energy = (G4UniformRand() < 0.5) ? 1.17 * MeV : 1.33 * MeV;
    // G4double energy = 10. *MeV;

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy); 
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(energy);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

// chọn random thanh nguồn phát với tên các thanh rodLVs
void MyPrimaryGenerator::generateBeamFrame()
{
    G4double randNumber = G4UniformRand();

    G4int noFrame = std::round(randNumber*4) + 1;
    G4String nameFrame = "A";
    switch (noFrame)
    {
    case 2:
        nameFrame = "B";
        break;
    case 3:
        nameFrame = "C";
        break;
    case 4:
        nameFrame = "D";
        break;
    }

    G4int noRod = std::round(randNumber*38);

    G4String nameRodLV = nameFrame + "_" + std::to_string(noRod) + "_RodLVs";
    G4LogicalVolume *rodLV =  G4LogicalVolumeStore::GetInstance()->GetVolume(nameRodLV);
    G4cout << "name of rod logical volume: " << rodLV->GetName() << G4endl;
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