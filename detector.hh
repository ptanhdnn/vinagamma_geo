/*
* Detetor construction class to define the materials and geometry
*/

#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

#include "trackerhit.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
    MySensitiveDetector(const G4String& name,
                        const G4String& hitCollectionName);
    ~MySensitiveDetector();

    void Initialize(G4HCofThisEvent *hitCollection);
    G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
    void EndOfEvent(G4HCofThisEvent *hitCollection);

private:
    TrackerHitsCollection *fHitsCollection = nullptr;
};

#endif