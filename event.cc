#include "event.hh"

MyEventAction::MyEventAction()
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
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