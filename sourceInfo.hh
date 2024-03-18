#ifndef SOURCEINFORMATION_HH
#define SOURCEINFORMATION_HH
#include "globals.hh"
#include <vector>

class sourceInformation

{
public:
    bool CheckActivitySourceRod(G4String nameFrame, G4String nameModule, G4int noRod);
// module A
    std::vector<G4String> SourceRodNamesModuleAF2 = {"889C","AP1","886C","AP0","AC6","887C","AK2"};
    std::vector<G4int> SourceRodPosModuleAF2 = {23,25,27,29,32,34,36};
    std::vector<G4double> ActivitySourceRodsModuleAF2 = {8.25, 6.45, 8.16, 6.59, 6.61, 8.24, 6.40};
// module B
    std::vector<G4String> SourceRodNamesModuleBF2 = {"884C","27X","893C","25X","AC7","958C","AK3"};
    std::vector<G4int> SourceRodPosModuleBF2 = {23,25,27,29,32,34,36};
    std::vector<G4double> ActivitySourceRodsModuleBF2 = {7.44, 6.33, 8.09, 6.51, 6.70, 9.17, 6.44};
// module C
    std::vector<G4String> SourceRodNamesModuleCF2 = {"AK4","AP8","957C","AC5","956C","AC8","956C","AP7"};
    std::vector<G4int> SourceRodPosModuleCF2 = {1,4,6,8,10,12,14,16};
    std::vector<G4double> ActivitySourceRodsModuleCF2 = {6.29, 6.62, 8.61, 6.97, 9.17, 6.47, 8.72, 6.36};
// module D    
    std::vector<G4String> SourceRodNamesModuleDF2 = {"AK0","955C","AC4","891C","AP3","816C","AP6","AP2"};
    std::vector<G4int> SourceRodPosModuleDF2 = {1,3,5,7,9,11,13,17};
    std::vector<G4double> ActivitySourceRodsModuleDF2 = {6.51, 8.68, 6.60, 8.27, 6.54, 8.30, 6.64, 6.82};

private:
    std::vector<G4String> nameOfModule = {"A", "B", "C", "D"};
};
#endif // SOURCEINFORMATION_HH

