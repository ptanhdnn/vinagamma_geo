#ifndef TRACKERHIT_HH
#define TRACKERHIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class TrackerHit : public G4VHit
{
public:
    TrackerHit();
    ~TrackerHit();

    // Set method
    void SetTrackID  (G4int track)      { fTrackID = track; };
    void SetDetectorNb(G4int det)      { fDetectorNb = det; };
    void SetEdep     (G4double de)      { fEdep = de; };
    void SetPos      (G4ThreeVector xyz){ fPos = xyz; };

    // Get methods
    G4int GetTrackID() const     { return fTrackID; };
    G4int GetDetectorNb() const   { return fDetectorNb; };
    G4double GetEdep() const     { return fEdep; };
    G4ThreeVector GetPos() const { return fPos; };

private:
    G4int         fTrackID = -1;
    G4int         fDetectorNb = -1;
    G4double      fEdep = 0.;
    G4ThreeVector fPos;
};

using TrackerHitsCollection = G4THitsCollection<TrackerHit>;

#endif