#include "stepping.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "construction.hh"
#include "event.hh"


MySteppingAction::MySteppingAction(MyEventAction *eventAction)
: fEventAction(eventAction), fScoringVolume(nullptr)
{}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
    if (!fScoringVolume){
        const auto detConstruction = static_cast<const MyDetectorConstruction*>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction()
        );
        fScoringVolume = detConstruction->GetScoringVolume();
    }
    G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    // G4cout << "Check the name of Volume in step:" << G4endl;
    // for (size_t i = 0; i < fConstruction->detectorLVs.size(); ++i) {
    //     G4cout << " name: " << fConstruction->detectorLVs[i]->GetName() << G4endl;
    // }
    G4cout << "volumeName: " << volume->GetName() << G4endl;
    // G4double edep = aStep->GetTotalEnergyDeposit();
    // if(edep == 0.) return false;
    // auto newHit = new TrackerHit();
    // newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
    // newHit->SetDetectorNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
    // newHit->SetEdep(edep);
    // newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());

    // fHitsCollection->insert( newHit );
    if(volume->GetName() == "detector_LV"){
        G4double edep = step->GetTotalEnergyDeposit();
        G4cout << "Energy: " << edep <<G4endl;
    }
}

    // // Trích xuất chỉ số i, j, k từ tên
    // size_t found_i = volumeName.find("_");
    // size_t found_j = volumeName.find("_", found_i + 1);
    // size_t found_k = volumeName.find("_", found_j + 1);

    // G4int i = std::stoi(volumeName.substr(found_i + 1, found_j - found_i - 1));
    // G4int j = std::stoi(volumeName.substr(found_j + 1, found_k - found_j - 1));
    // G4int k = std::stoi(volumeName.substr(found_k + 1));

    //     if (found_i != G4String::npos && found_j != G4String::npos && found_k != G4String::npos) {
    //         G4int i = std::stoi(volumeName.substr(found_i + 3, found_j - found_i - 3));
    //         G4int j = std::stoi(volumeName.substr(found_j + 3, found_k - found_j - 3));
    //         G4int k = std::stoi(volumeName.substr(found_k + 3));

    //         // Tính liều lượng năng lượng và thêm vào sự kiện
    //         G4double edepStep = step->GetTotalEnergyDeposit();
    //         fEventAction->AddEdepToBox(i, j, k, edepStep);
    //     }

    // // Kiểm tra xem volume có phải là thùng hàng đang được quan tâm không
    // if (volume == fScoringVolume) {
    //     // Lấy tên của volume
    //     G4String volumeName = volume->GetName();

    //     // Trích xuất chỉ số i, j, k từ tên
    //     size_t found_i = volumeName.find("_i_");
    //     size_t found_j = volumeName.find("_j_");
    //     size_t found_k = volumeName.find("_k_");

    //     if (found_i != G4String::npos && found_j != G4String::npos && found_k != G4String::npos) {
    //         G4int i = std::stoi(volumeName.substr(found_i + 3, found_j - found_i - 3));
    //         G4int j = std::stoi(volumeName.substr(found_j + 3, found_k - found_j - 3));
    //         G4int k = std::stoi(volumeName.substr(found_k + 3));

    //         // Tính liều lượng năng lượng và thêm vào sự kiện
    //         G4double edepStep = step->GetTotalEnergyDeposit();
    //         fEventAction->AddEdepToBox(i, j, k, edepStep);
    //     }
    // }
