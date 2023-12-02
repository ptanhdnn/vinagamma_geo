#include "trackerhit.hh"

// Defind the allocator outside any function
G4ThreadLocal G4Allocator<TrackerHit> *TrackerHitAllocator = nullptr;

TrackerHit :: TrackerHit()
{}

TrackerHit ::~TrackerHit()
{}

void TrackerHit::Print()
{
  // G4cout
  //    << "Edep: "
  //    << std::setw(7) << G4BestUnit(fEdep,"Energy")
  //    << " track length: "
  //    << std::setw(7) << G4BestUnit( fTrackLength,"Length")
  //    << G4endl;
}