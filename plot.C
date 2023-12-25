#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH3D.h"

void plot() {
    // Open the ROOT file
    TFile *file = TFile::Open("doseMap.root");

    // Check if the file is opened successfully
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file doseMap.root" << std::endl;
        return;
    }

    // Get the ntuple from the file
    TTree *ntuple = dynamic_cast<TTree*>(file->Get("Dose"));

    // Check if the ntuple exists
    if (!ntuple) {
        std::cerr << "Ntuple not found in the file" << std::endl;
        file->Close();
        return;
    }

    // Create histograms
    TH2D *hDoseMapXY = new TH2D("hDoseMapXY", "Dose Map XY", 100, -132.0, 132.0, 100, -132.0, 132.0);
    TH2D *hDoseMapXZ = new TH2D("hDoseMapXZ", "Dose Map XZ", 100, -132.0, 132.0, 50, -90.0, 90.0);
    TH3D *hDoseMap3D = new TH3D("hDoseMap3D", "Dose Map 3D", 100, -132.0, 132.0, 100, -132.0, 132.0, 50, -90.0, 90.0);

    // Variables to store data from the ntuple
    double Dose, XDet, YDet, ZDet;

    // Set the branch addresses
    ntuple->SetBranchAddress("Dose", &Dose);
    ntuple->SetBranchAddress("XDet", &XDet);
    ntuple->SetBranchAddress("YDet", &YDet);
    ntuple->SetBranchAddress("ZDet", &ZDet);

    // Loop over entries in the ntuple
    Long64_t nentries = ntuple->GetEntries();
    for (Long64_t i = 0; i < nentries; ++i) {
        ntuple->GetEntry(i);

        // Fill histograms with ntuple data
        hDoseMapXY->Fill(XDet, YDet, Dose);
        hDoseMapXZ->Fill(XDet, ZDet, Dose);
        hDoseMap3D->Fill(XDet, YDet, ZDet, Dose);
    }

    // Draw histograms
    hDoseMapXY->Draw("colz");
    hDoseMapXZ->Draw("colz");
    hDoseMap3D->Draw("BOX1");

    // Close the ROOT file
    file->Close();
}
