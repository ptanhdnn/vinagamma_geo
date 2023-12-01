#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "G4AnalysisManager.hh"

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction();
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event* event) override;
    virtual void EndOfEventAction(const G4Event* event) override;

    void AddEdep(G4double edep) {fEdep += edep;}
    std::map<G4ThreeVector, G4double> doseMap;

private:
    // MyRunAction *fRunAction = nullptr;
    G4double fEdep = 0.;
};

#endif