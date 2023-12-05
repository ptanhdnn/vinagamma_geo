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
    // G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    // G4String particleName = "gamma";
    // G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
    // Create a G4GeneralParticleSource object
    // Define the half-life of Co-60 in seconds
    // G4long seed = time(nullptr);
    // CLHEP::HepRandom::setTheSeed(seed);
    double halfLifeInSeconds = 5.26 * 365.25 * 24 * 3600; // 5.26 years
    double activityCi = 187.0; // Activity in kiloCuries
    double lambda = log(2.0) / halfLifeInSeconds; // Calculate decay constant

    // Calculate the number of decays per second (Becquerels)
    double activityBq = activityCi * 1e3 * 3.7e10; // 1 Ci = 3.7e10 Bq
    double decayConstant = lambda * activityBq;

    // Create a G4RadioactiveDecay object
    G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();

    // Create a G4DecayTable and set the decay constant for Co-60
    // G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
    // radioactiveDecay->SetDecayConstant(lambda); // Set decay constant for Co-60
    // radioactiveDecay->SetDecayMode(G4RadioactiveDecay::DecayMode::kBranchingRatios);
    // radioactiveDecay->AddBranch(new G4RadioactiveDecayChannel("gamma", 1.0));

    // Define the Cobalt60
    G4String elementName = "Cobalt";
    G4int atomicNumber = 27;
    G4int atomicMass = 60;
    G4double abundance = 100.0 * perCent;
    G4Isotope *isotope = new G4Isotope(elementName, atomicNumber, atomicMass, abundance);
    
    // Register the isotope into the G4NistManager
    // G4NistManager *nistManager = G4NistManager::Instance();
    // nistManager->Insert(isotope);
    // isotope->SetDecayTable(decayTable);

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
    // fParticleGun->SetCurrentSourceIntensity(decayConstant);
    // fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}