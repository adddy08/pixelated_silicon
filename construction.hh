#ifndef CONSTRUCTION_HH

#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "detector.hh"
#include "G4Polyhedra.hh"
#include "G4VisAttributes.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4ProductionCuts.hh"
#include "G4RegionStore.hh"
#include "G4UserLimits.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
    virtual G4VPhysicalVolume *Construct();

private:
    G4LogicalVolume *logicDetector;  
    G4LogicalVolume *logicPixel;  // Added: Ensuring logicPixel is defined in header
    G4LogicalVolume *fScoringVolume;

    virtual void ConstructSDandField();
};

#endif

