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
    
    if (volume != fScoringVolume) return;
    
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep);
}