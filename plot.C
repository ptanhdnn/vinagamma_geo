void plot()
{
  // Khởi tạo một đối tượng TH3D
  TH3D *h3 = new TH3D("h3", "Dose map", 40, -400, -200, 80, -1000.0, -200., 20, -700, -100);

  // Mở tệp dữ liệu geant4
  TFile *file = new TFile("doseMap.root", "READ");

  // Lấy ntuple từ tệp dữ liệu
  TTree *tree = (TTree *)file->Get("Dose");

  // Khởi tạo các biến để lưu trữ dữ liệu từ ntuple
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

  // Vẽ biểu đồ
  h3->Draw();
}
