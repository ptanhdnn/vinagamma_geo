void plot()
{
  TH3D *h3 = new TH3D("h3", "Dose map", 40, -400, -200, 80, -1000.0, -200., 20, -700, -100);

  TFile *file = new TFile("doseMap.root", "READ");

  TTree *tree = (TTree *)file->Get("Dose");

  double x, y, z, dose;

  // Lấy dữ liệu từ ntuple
  tree->SetBranchAddress("XDet", &x);
  tree->SetBranchAddress("YDet", &y);
  tree->SetBranchAddress("ZDet", &z);
  tree->SetBranchAddress("Dose", &dose);

  // Thêm các điểm dữ liệu vào biểu đồ
  for (int i = 0; i < tree->GetEntries(); i++)
  {
    tree->GetEntry(i);
    h3->Fill(x, y, z, dose);
  }

  h3->Draw();
}
