#include "generator.hh"

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
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "gamma";
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
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

    // Tạo hướng ngẫu nhiên cho các hạt trong không gian 3D
    G4double theta = G4UniformRand() * CLHEP::pi;  // Góc θ ngẫu nhiên
    G4double phi = G4UniformRand() * 2 * CLHEP::pi;  // Góc φ ngẫu nhiên

    G4ThreeVector mom(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));  // Hướng ngẫu nhiên

    G4double energy = (G4UniformRand() < 0.5) ? 1.17 * MeV : 1.33 * MeV;

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(energy);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}