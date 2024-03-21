#include "action.hh"

 MyActionInitialization :: MyActionInitialization ()
{
    masterGPS = new G4GeneralParticleSource();
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
    masterGPS->SetParticleDefinition(particle);
}

 MyActionInitialization :: ~MyActionInitialization ()
{
    delete masterGPS;
}

void MyActionInitialization::BuildForMaster() const
{
    auto eventAction = new MyEventAction;
    SetUserAction(new MyRunAction(eventAction));
}

void MyActionInitialization::Build() const
{
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);

    MyEventAction *eventAction = new MyEventAction();
    SetUserAction(eventAction);
    
    MyRunAction *runAction = new MyRunAction(eventAction);
    SetUserAction(runAction);
}

