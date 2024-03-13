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
#ifdef G4MULTITHREADED
    G4cout << "Running the multithreaded process" << G4endl;
    runManager->SetNumberOfThreads(30);
#endif

    G4UIExecutive* ui = 0;
	if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
	}


    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

    auto *ptrAnalysis = new MyAnalysis();
    G4double activity  = 1000000 * becquerel;//Activity is set via run.mac file
	ptrAnalysis->setActivity(activity);

    runManager->Initialize();

    // G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    // UImanager->ApplyCommand("/vis/open OGL");
    // UImanager->ApplyCommand("/vis/drawVolume");
    // UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    // UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    // UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    // UImanager->ApplyCommand("/vis/scene/add/axes");
    if ( !ui ) {
    // execute an argument macro file if exist
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    } else {
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        if (ui->IsGUI()) {
            UImanager->ApplyCommand("/control/execute gui.mac");
        }
    // start interactive session
        ui->SessionStart();
        delete ui;
    }
    // UImanager->ApplyCommand("/control/execute run.mac");
    // ui->SessionStart();

    return 0;
}