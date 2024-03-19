#include "sourceInfo.hh"

bool sourceInformation::CheckActivitySourceRod(G4String nameFrame, G4String nameModule, G4int noRod)
{
    auto it = std::find(nameOfModule.begin(), nameOfModule.end(), nameModule);
    if(it != nameOfModule.end()){
        auto it2 = std::find(SourceRodPosModuleAF2.begin(), SourceRodPosModuleAF2.end(), noRod);
        if (it2 != SourceRodPosModuleAF2.end()){
            G4int indexRod = std::distance(SourceRodPosModuleAF2.begin(), it2);
            return true;
        }
        return false;
    }
    return false;
}

G4int sourceInformation::GetBeamRod()
{
    G4double randNumber = G4UniformRand()*6;
    return SourceRodPosModuleBF2[randNumber];
}