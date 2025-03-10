#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "construction.hh"
#include "action.hh"
#include "physics.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv)
{
    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    runManager->Initialize();

    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    // Open the visualization with OGL
    UImanager->ApplyCommand("/vis/open OGL");
    
    // Set the viewpoint and visibility
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate -1");
    UImanager->ApplyCommand("/vis/geometry/set/visibility logicWorld 0 false");
    UImanager->ApplyCommand("/vis/scene/add/hits");
    
    // Change visualization style to wireframe
    UImanager->ApplyCommand("/vis/viewer/set/style wireframe");

    // Start the recursive geometry test
    UImanager->ApplyCommand("/geometry/test/recursion_start");
    
    // Optionally check for overlaps
    UImanager->ApplyCommand("/geometry/test/overlaps"); // Uncomment if available in your Geant4 version
    
    // You could also visualize the geometry after the recursion test
    UImanager->ApplyCommand("/vis/scene/add/volume");

    ui->SessionStart();

    return 0;
} 
