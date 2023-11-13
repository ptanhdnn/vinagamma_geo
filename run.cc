#include "run.hh"

MyRunAction::MyRunAction()
{
    auto manager = G4AnalysisManager::Instance();
    manager->SetDefaultFileType("root");
    manager->SetNtupleMerging(true);
    manager->SetVerboseLevel(1);
    manager->SetFileName("data");

    manager->CreateNtuple("Hits", "Hits");
    manager->CreateNtupleIColumn("fEvent");
    manager->CreateNtupleDColumn("fX");
    manager->CreateNtupleDColumn("fY");
    manager->CreateNtupleDColumn("fZ");
    manager->FinishNtuple();

}
MyRunAction::~MyRunAction()
{}
void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    auto manager = G4AnalysisManager::Instance();
    manager->OpenFile();
    
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    auto manager = G4AnalysisManager::Instance();
    manager->Write();
    manager->CloseFile();
}