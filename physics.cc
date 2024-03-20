#include "physics.hh"

#include "G4UnitsTable.hh"
#include "G4ParticleTypes.hh"
#include "G4IonConstructor.hh"
#include "G4PhysicsListHelper.hh"
#include "G4RadioactiveDecay.hh"
#include "G4SystemOfUnits.hh"
#include "G4NuclideTable.hh"
//for gamma
#include "G4ComptonScattering.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"
//for e- and e+
#include "G4eIonisation.hh"
#include "G4eMultipleScattering.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4StepLimiter.hh"
PhysicsList::PhysicsList()
: G4VUserPhysicsList()
{
  //add new units for radioActive decays
  //
  const G4double minute = 60*second;
  const G4double hour   = 60*minute;
  const G4double day    = 24*hour;
  const G4double year   = 365*day;
  new G4UnitDefinition("minute", "min", "Time", minute);
  new G4UnitDefinition("hour",   "h",   "Time", hour);
  new G4UnitDefinition("day",    "d",   "Time", day);
  new G4UnitDefinition("year",   "y",   "Time", year);
}

PhysicsList::~PhysicsList()
{ }

void PhysicsList::ConstructParticle()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();

  // baryons
  G4Proton::ProtonDefinition();
  G4Neutron::NeutronDefinition();

  // ions
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();
}


void PhysicsList::ConstructProcess()
{
  AddTransportation();
  G4PhysicsListHelper* ph =G4PhysicsListHelper::GetPhysicsListHelper();
  GetParticleIterator()->reset();
  while ((*GetParticleIterator())())
    {
      G4ParticleDefinition* particle=GetParticleIterator()->value();
      G4String partName=particle->GetParticleName();
      if (partName=="GenericIon")
        {
          G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
          radioactiveDecay->SetARM(false);               //Atomic Rearangement
          ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
        }
      else if (partName=="gamma")
        {
      //ph->RegisterProcess(new G4StepLimiter(),particle);
          ph->RegisterProcess(new G4ComptonScattering(),particle);
          ph->RegisterProcess(new G4PhotoElectricEffect(),particle);
          ph->RegisterProcess(new G4GammaConversion(),particle);
      ph->RegisterProcess(new G4RayleighScattering,particle);
        }
       else if (partName == "e-" || partName == "e+")
        {
          ph->RegisterProcess(new G4eMultipleScattering(),particle);
          ph->RegisterProcess(new G4eBremsstrahlung(),particle);
          ph->RegisterProcess(new G4eIonisation(),particle);
          if (partName == "e+")
            ph->RegisterProcess(new G4eplusAnnihilation(),particle);
        }

    }
  // mandatory for G4NuclideTable
  //
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1*picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0*eV);
}


void PhysicsList::SetCuts()
{
  SetCutsWithDefault();
}
