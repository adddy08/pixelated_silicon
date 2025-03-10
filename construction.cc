#include "construction.hh"
#include "G4SDManager.hh"

MyDetectorConstruction::MyDetectorConstruction() : logicPixel(nullptr) // Initialize to NULL
{
    ConstructSDandField(); // Ensure Sensitive Detector is set
}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();

    // Define materials
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR"); 
    G4Material *Silicon = nist->FindOrBuildMaterial("G4_Si");

    // Define World Volume
    G4Box *solidWorld = new G4Box("solidWorld", 20.0 * m, 20.0 * m, 20.0 * m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, true);

    // Define Single Pixel Size
    G4double pixelSizeX = 3.0 * mm;
    G4double pixelSizeY = 3.0 * mm;
    G4double pixelSizeZ = 5.0 * mm;  // Thickness

    G4Box *solidPixel = new G4Box("solidPixel", pixelSizeX / 2, pixelSizeY / 2, pixelSizeZ / 2);
    logicPixel = new G4LogicalVolume(solidPixel, Silicon, "logicPixel");

    // Set visualization attributes (color blue)
    G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
    visAttributes->SetVisibility(true);
    logicPixel->SetVisAttributes(visAttributes);

    // Define Grid Parameters
    G4int nX = 10, nY = 10; // Number of pixels in X and Y directions
    G4double totalSizeX = nX * pixelSizeX;
    G4double totalSizeY = nY * pixelSizeY;

    G4double startX = -totalSizeX / 2 + pixelSizeX / 2;
    G4double startY = -totalSizeY / 2 + pixelSizeY / 2;

    G4double detectorZ = 10.0 * mm;  // Move detector plane forward

    // Place Pixels in a 10x10 Grid
    for (G4int i = 0; i < nX; i++) {
        for (G4int j = 0; j < nY; j++) {
            G4double posX = startX + i * pixelSizeX;
            G4double posY = startY + j * pixelSizeY;
            new G4PVPlacement(0, G4ThreeVector(posX, posY, detectorZ), logicPixel, "physPixel", logicWorld, false, i * nY + j, true);
        }
    }

    // Set production cuts in energy
    G4ProductionCuts *cuts = new G4ProductionCuts();
    cuts->SetProductionCut(10 * eV, "gamma");    // 10 eV for photons
    cuts->SetProductionCut(10 * eV, "e-");      // 10 eV for electrons
    cuts->SetProductionCut(10 * eV, "e+");      // 10 eV for positrons
    cuts->SetProductionCut(10 * eV, "proton");  // 10 eV for protons (if needed)

    logicWorld->SetUserLimits(new G4UserLimits(1 * nm)); // Optional: Set user limits on step size

    // ✅ **Move the call to `ConstructSDandField()` here!**
    ConstructSDandField();

    return physWorld;
}

// Sensitive Detector Assignment
void MyDetectorConstruction::ConstructSDandField()
{
    if (!logicPixel) {
        G4cerr << "Error: logicPixel is NULL! Sensitive Detector not set." << G4endl;
        return;
    }

    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
    logicPixel->SetSensitiveDetector(sensDet);
    
    G4cout << "Sensitive Detector Assigned to Pixels Successfully!" << G4endl;
}

