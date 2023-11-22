#include<iostream>

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "analysis.hh"


int main(int argc, char** argv)
{
    auto *runManager = G4RunManagerFactory::CreateRunManager();
    G4int nThreads = 4;
    runManager.SetNumberOfThread(nThreads);

    G4UIExecutive* ui = 0;
	if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
	}

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

    auto *ptrAnalysis = new MyAnalysis();
    G4double activity  = 1000000 * becquerel;//Activity is set via run.mac file
	ptrAnalysis->SetActivity(activity);
    // G4RunManager *runManager = new G4RunManager();

    // runManager->SetUserInitialization(new MyDetectorConstruction());
    // runManager->SetUserInitialization(new MyPhysicsList());
    // runManager->SetUserInitialization(new MyActionInitialization());
    // runManager->Initialize();

    // G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    // G4VisManager *visManager = new G4VisExecutive();
    // visManager->Initialize();

    // G4UImanager *UImanager = G4UImanager::GetUIpointer();
    // // UImanager->ApplyCommand("/vis/open OGL");
    // // UImanager->ApplyCommand("/vis/drawVolume");
    // // UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    // // UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    // // UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    // UImanager->ApplyCommand("/run/beamOn 10");
    // ui->SessionStart();

    return 0;
}