#include "event.hh"

MyEventAction::MyEventAction(MyRunAction* runAction): fRunAction(runAction)
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep = 0.;
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
    
}