#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4Accumulable.hh"

#include "construction.hh"
#include "detector.hh"
#include "generator.hh"
#include "event.hh"

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction(MyEventAction *eventAction);
    ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run*) override;
    virtual void EndOfRunAction(const G4Run*) override;

    G4AnalysisManager *manager;

private:
    MyEventAction *fEventAction = nullptr;
};

#endif