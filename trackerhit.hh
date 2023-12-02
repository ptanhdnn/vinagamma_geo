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

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    // Set method
    void SetTrackID  (G4int track)      { fTrackID = track; };
    void SetDetectorNb(G4int det)      { fDetectorNb = det; };
    void SetDose     (G4double dose)      { fDose = dose; };
    void SetPos      (G4ThreeVector xyz){ fPos = xyz; };

    // Get methods
    G4int GetTrackID() const     { return fTrackID; };
    G4int GetDetectorNb() const   { return fDetectorNb; };
    G4double GetDose() const     { return fDose; };
    G4ThreeVector GetPos() const { return fPos; };
    void Print();

private:
    G4int         fTrackID = -1;
    G4int         fDetectorNb = -1;
    G4double      fDose = 0.;
    G4ThreeVector fPos;
};

using TrackerHitsCollection = G4THitsCollection<TrackerHit>;
// extern G4Allocator<TrackerHit> TrackerHitAllocator;
extern G4ThreadLocal G4Allocator<TrackerHit> *TrackerHitAllocator;

inline void* TrackerHit::operator new(size_t)
{
    if(!TrackerHitAllocator)
        TrackerHitAllocator = new G4Allocator<TrackerHit>;
    return (void *) TrackerHitAllocator->MallocSingle();
}

inline void TrackerHit::operator delete(void *aHit)
{
    TrackerHitAllocator->FreeSingle((TrackerHit*) aHit);
}

#endif