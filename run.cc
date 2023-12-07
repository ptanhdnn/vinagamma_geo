#include "run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AccumulableManager.hh"
#include "G4SDManager.hh"
#include "G4HCtable.hh"

MyRunAction::MyRunAction(MyEventAction *eventAction)
 : fEventAction(eventAction)
{
    G4RunManager::GetRunManager()->SetPrintProgress(10);

    const G4double milligray = 1.e-3*gray;
    const G4double microgray = 1.e-6*gray;
    const G4double nanogray  = 1.e-9*gray;
    const G4double picogray  = 1.e-12*gray;

    new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
    new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
    new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
    new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

    // G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    // accumulableManager->RegisterAccumulable(fEdep);

    
    auto manager = G4AnalysisManager::Instance();
    manager->SetDefaultFileType("root");
    manager->SetVerboseLevel(1);
    manager->SetNtupleMerging(true);
    // manager->SetFileName("doseData");

    // Book histogram, ntuple

    // Creating 2D
    manager->CreateH2("Dose Map XY", "Dose Histogram XY",
                        100, -132., 132, 100, -132., 132);
    manager->CreateH2("Dose Map XZ", "Dose Histogram XZ",
                        100, -132., 132, 50, -90., 90);
    
    // Creating 3D
    manager->CreateH3("Dose Map 3D", "Dose Histogram 3D",
                        100, -132., 132, 100, -132., 132, 50, -90, 90);

    // Creating ntuple
    manager->CreateNtuple("Dose", "Dose data");
    manager->CreateNtupleDColumn("Dose");
    manager->CreateNtupleDColumn("XDet");
    manager->CreateNtupleDColumn("YDet");
    manager->CreateNtupleDColumn("ZDet");
    manager->FinishNtuple();

    // manager->SetNtupleFileName(0, "DoseMapnTuple");
}
MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    auto manager = G4AnalysisManager::Instance();
    G4String fileName = "doseMap.root";
    // manager->Reset();
    manager->OpenFile(fileName);

    
}

void MyRunAction::EndOfRunAction(const G4Run* run)
{
    G4SDManager *sdManager = G4SDManager::GetSDMpointer();
    G4HCtable *hcTable = sdManager->GetHCtable();
    G4int nEntries = hcTable->entries();
    G4cout << nEntries << G4endl;
    if (nEntries == 0) {
        G4cout << "There is no detector register" << G4endl;
        return;
    }
    
    for (G4int i = 0; i < nEntries; ++i) {
        G4String detectorName = hcTable->GetSDname(i);
        G4cout << "Detector " << i << ": " << detectorName << G4endl;
    }
    
    auto manager = G4AnalysisManager::Instance();

    // Check if the histograms exist before writing
    if (manager->GetH2(0) && manager->GetH2(1) && manager->GetH3(0))
    {
        // Check if the histograms have entries before writing
        if (manager->GetH2(0)->entries() > 0 && manager->GetH2(1)->entries() > 0 && manager->GetH3(0)->entries() > 0)
        {
            // Write the data to the output file
            manager->Write();
            G4cout << "Data written to the output file." << G4endl;
        }
        else
        {
            G4cout << "No entries in the histograms. Not writing to the output file." << G4endl;
        }
    }
    else
    {
        G4cout << "Histograms do not exist. Not writing to the output file." << G4endl;
    }

    // Close the output file
    manager->CloseFile(false);
}


void MyRunAction::AddEdep(G4double edep)
{
    fEdep  += edep;
    fEdep2 += edep*edep;
}