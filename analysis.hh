#ifndef ANALYSIS_HH
#define ANALYSIS_HH

#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

class MyAnalysis
{
public:
    MyAnalysis();
    ~MyAnalysis();
    void setActivity(G4double);

private:
    G4double InitialActivity;
};

#endif