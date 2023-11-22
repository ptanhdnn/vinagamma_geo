#include "analysis.hh"

MyAnalysis::MyAnalysis()
{}
MyAnalysis::~MyAnalysis()
{}

void MyAnalysis::setActivity(G4double newActivity)
{
    InitialActivity = newActivity;
    G4cout<<"Initial activity: "<<InitialActivity/becquerel<<" Bq."<<G4endl;
}