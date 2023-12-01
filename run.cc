#include "run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AccumulableManager.hh"

MyRunAction::MyRunAction()
{
    const G4double milligray = 1.e-3*gray;
    const G4double microgray = 1.e-6*gray;
    const G4double nanogray  = 1.e-9*gray;
    const G4double picogray  = 1.e-12*gray;

    new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
    new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
    new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
    new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

    // G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    // accumulableManager->RegisterAccumulable(fEdep);

    auto manager = G4AnalysisManager::Instance();
    manager->SetDefaultFileType("root");
    manager->SetNtupleMerging(true);
    manager->SetVerboseLevel(1);
    manager->SetFileName("doseData");

    manager->CreateNtuple("Dose", "Dose data");
    manager->CreateNtupleDColumn("Dose");
    manager->CreateNtupleDColumn("XDet");
    manager->CreateNtupleDColumn("YDet");
    manager->CreateNtupleDColumn("ZDet");
    manager->CreateNtupleIColumn("EventID");
    manager->FinishNtuple();

    manager->SetNtupleFileName(0, "DoseMapnTuple");
}
MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    auto manager = G4AnalysisManager::Instance();
    manager->Reset();
    manager->OpenFile();
    
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    // G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
    // accumulableManager->Merge();

    // G4double edep = fEdep.GetValue();
    // G4double edep2 = fEdep2.GetValue();

    // G4double rms = edep2 - edep*edep/nofEvent;
    // if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;

    // const auto detConstruction = static_cast<const MyDetectorConstruction*>(
    //     G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    // G4double mass = detConstruction->GetScoringVolume()->GetMass();
    // G4double dose = edep/mass;
    // G4double rmsDose = rms/mass;

    auto manager = G4AnalysisManager::Instance();
    manager->Write();
    manager->CloseFile();
}

void MyRunAction::AddEdep(G4double edep)
{
    fEdep  += edep;
    fEdep2 += edep*edep;
}