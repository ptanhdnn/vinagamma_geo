#ifndef ANALYSIS_HH
#define ANALYSIS_HH

#include "G4AnalysisManager.hh"

class MyAnalysis
{
private:
    MyAnalysis();

public:
    ~MyAnalysis();
    void setActivity(G4double);

private:
    G4double InitialActivity;
};

#endif