#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"

#include "construction.hh"
#include "event.hh"

class MySteppingAction : public G4UserSteppingAction
{
public:
    MySteppingAction(MyEventAction* eventAction);
    ~MySteppingAction();

    void UserSteppingAction(const G4Step*) override;

private:
    MyEventAction *fEventAction = nullptr;
    G4LogicalVolume *fScoringVolume = nullptr;
};

#endif