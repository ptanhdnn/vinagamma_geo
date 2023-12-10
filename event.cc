#include "event.hh"

MyEventAction::MyEventAction()
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    G4cout << "==========================================================================" << G4endl
            << "From begining of EventAction" <<G4endl
            << "==========================================================================" << G4endl;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    G4cout << "This is end of eventAction process." << G4endl;
    G4SDManager *sdManager = G4SDManager::GetSDMpointer();
    G4HCtable *hcTable = sdManager->GetHCtable();
    G4int nEntries = hcTable->entries();
    // G4cout << nEntries << G4endl;
    if (nEntries == 0) {
        G4cout << "There is no detector register" << G4endl;
        return;
    }

    doseMap = detector->GetDoseMap();
    // G4cout << "Size of doseMap in end of eventAction: " << doseMap.size() << G4endl;
    // for (const auto& entry : doseMap) {
    //     G4ThreeVector posDet = entry.first;
    //     G4double      edep   = entry.second;
    //     G4cout << "Position: (" << posDet.x() << ", " << posDet.y() << ", " << posDet.z() << "), Edep: " << edep << G4endl;
    // }

    G4cout << "==========================================================================" << G4endl
            << "End of EventAction" <<G4endl
            << "==========================================================================" << G4endl;

    auto manager = G4AnalysisManager::Instance();
    for (auto it = doseMap.begin(); it != doseMap.end(); it++){
        G4ThreeVector posDet = it->first;
        G4double      edep   = it->second;
        // G4cout << posDet << edep << G4endl;

        manager->FillH2(0, posDet.x(), posDet.y());
        manager->FillH2(1, posDet.x(), posDet.z());
        manager->FillH3(2, posDet.x(), posDet.y(), posDet.z(), edep);

        // Fill the ntuple
        manager->FillNtupleDColumn(0, edep);
        manager->FillNtupleDColumn(1, posDet.x());
        manager->FillNtupleDColumn(2, posDet.y());
        manager->FillNtupleDColumn(3, posDet.z());
        manager->AddNtupleRow();
    }
}