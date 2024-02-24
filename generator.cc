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