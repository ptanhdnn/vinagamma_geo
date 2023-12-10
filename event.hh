#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "G4AnalysisManager.hh"
#include "G4SDManager.hh"
#include "detector.hh"

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction();
    ~MyEventAction();

    virtual void BeginOfEventAction(const G4Event* event) override;
    virtual void EndOfEventAction(const G4Event* event) override;

private:
    MySensitiveDetector *detector;

    std::map<G4ThreeVector, G4double> doseMap;
};

#endif