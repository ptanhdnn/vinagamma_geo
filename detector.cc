#include "detector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"

std::map<G4ThreeVector, G4double> MySensitiveDetector::doseMap;

MySensitiveDetector::MySensitiveDetector(const G4String& name,
                                        const G4String& hitsCollectionName)
    :G4VSensitiveDetector(name)
{
    collectionName.insert(hitsCollectionName);  //collectionName là biến có sẵn để trả về các HitsCollection ID
}

MySensitiveDetector::~MySensitiveDetector()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void MySensitiveDetector::Initialize(G4HCofThisEvent *hce)
{
    // G4cout << "This is the Initialize process." << G4endl;
    fHitsCollection = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]);
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hce->AddHitsCollection(hcID, fHitsCollection);
    // G4cout << "fHitsCollection and hcID: " << fHitsCollection << hcID << G4endl;
    // G4cout << "This is end of Initialize process." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    // G4cout << "This is process Hits. " <<G4endl;
    G4Track *track = aStep->GetTrack();

    // G4ThreeVector startPosition = track->GetVertexPosition();
    // G4ThreeVector endPosition = track->GetPosition();
    // G4double stepLength = aStep->GetStepLength();
    // G4double kineticEnergy = aStep->GetPreStepPoint()->GetKineticEnergy();

    // G4cout << "Start position: " << startPosition << G4endl;
    // G4cout << "End position: " << endPosition << G4endl;
    // G4cout << "Step length: " << stepLength << G4endl;
    // G4cout << "Kinetic energy: " << kineticEnergy << G4endl;
    // Get copy number and physical volume information
    const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
    // G4int copyNo = touchable->GetCopyNumber();
    G4VPhysicalVolume* physVol = touchable->GetVolume();
    G4String detName = physVol->GetName();
    // G4cout << "Detector Name: " << detName <<G4endl;
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4double edep = aStep->GetTotalEnergyDeposit();
    if(edep > 0.){
        const auto detConstruction = static_cast<const MyDetectorConstruction*>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction()
    );
        // G4cout << "This is process Hits. 2 " <<G4endl;
        G4double mass = detConstruction->GetScoringVolume()->GetMass();
        // G4cout << "This is process Hits. 3 " <<G4endl;
        
        
        // // Get copy number and physical volume information
        // const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
        // G4int copyNo = touchable->GetCopyNumber();
        // G4VPhysicalVolume* physVol = touchable->GetVolume();
        // G4String detName = physVol->GetName();
        // G4cout << "Detector Name: " << detName <<G4endl;
        // G4ThreeVector posDetector = physVol->GetTranslation();

        TrackerHit *newHit = new TrackerHit();
        newHit->SetDose(edep/mass);
        // newHit->SetTrackID(track->GetTrackID());
        // newHit->SetDetectorNb(copyNo);
        newHit->SetPos(posDetector);
        fHitsCollection->insert(newHit);
    }
    
  
    return true;
}

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    G4int nofHits = fHitsCollection->entries();
    if (nofHits > 0){
        // G4cout << G4endl
        // << "-------->Hits Collection: in this event they are " << nofHits
        // << " hits in the tracker detector: " << G4endl;
        for ( G4int i=0; i<nofHits; i++ ){
            TrackerHit *hit = (*fHitsCollection)[i];
            G4double aDose = hit->GetDose();
            if (aDose > 0.){
                G4ThreeVector posDet = hit->GetPos();
                // eventAction->AddDoseMap(posDet, aDose);
                auto it = doseMap.find(posDet);
                if(it != doseMap.end()){
                    it->second += aDose;
                } else {
                    doseMap[posDet] = aDose;
                }
            }
            G4cout << "=================================================" << G4endl;
        }
    }
}

std::map<G4ThreeVector, G4double>MySensitiveDetector::GetDoseMap()
{
    return doseMap;
}