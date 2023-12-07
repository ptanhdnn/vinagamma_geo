#include "event.hh"

MyEventAction::MyEventAction()
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    G4cout << "From begining of EventAction" <<G4endl;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    // auto detectorSD = G4SDManager::GetSDMpointer()->FindSensitiveDetector("TrackerDetSD");
    // if(detectorSD){
    //     auto hitCollection = detectorSD->GetCollectionName("TrackerHitCollection");
    //     if(hitCollection){
    //         for(auto it = hitCollection.begin(); it != hitCollection.end(); it++){
    //             auto hit = *it;
    //             G4ThreeVector position = hit->GetPos();

    //         }
    //     }
    // }
    G4cout << "This is end of eventAction process." << G4endl;
    G4SDManager *sdManager = G4SDManager::GetSDMpointer();
    G4HCtable *hcTable = sdManager->GetHCtable();
    G4int nEntries = hcTable->entries();
    G4cout << nEntries << G4endl;
    if (nEntries == 0) {
        G4cout << "There is no detector register" << G4endl;
        return;
    }
    
    for (G4int i = 0; i < nEntries; ++i) {
        G4String detectorName = hcTable->GetSDname(i);
        G4cout << "Detector " << i << ": " << detectorName << G4endl;
    }

    auto manager = G4AnalysisManager::Instance();
    for (auto it = doseMap.begin(); it != doseMap.end(); it++){
        G4ThreeVector posDet = it->first;
        G4double      edep   = it->second;

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