#include "event.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
    fEdep = 0.;
}
MyEventAction::~MyEventAction()
{}
void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    G4cout << "Energy deposition: " << G4endl;
    G4AnalysisManager *manager = G4AnalysisManager::Instance();
    manager->FillNtupleDColumn(4, fEdep);
    manager->AddNtupleRow(1);
}