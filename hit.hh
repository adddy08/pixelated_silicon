#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "globals.hh"

class MyHit : public G4VHit {
public:
    MyHit();
    virtual ~MyHit();

    void SetEdep(G4double edep) { fEdep = edep; }
    G4double GetEdep() const { return fEdep; }

private:
    G4double fEdep; // Energy deposited in this hit
};

typedef G4THitsCollection<MyHit> MyDetectorHitsCollection;

#endif

