void Update_em() {
  TString fileName = "/nfs/dust/cms/user/rasp/Run/emu_datacards_sys_UL/BDT_fine/bbH_em_2018.root";
  TFile * file = new TFile(fileName,"UPDATE");
  TH1D * hist = (TH1D*)file->Get("em_cat3_NbtagGe1/data_obs");
  double bin31 = 712.;
  double bin30 = 839.;
  hist->SetBinContent(31,bin31);
  hist->SetBinError(31,TMath::Sqrt(bin31));
  hist->SetBinContent(30,bin30);
  hist->SetBinError(30,TMath::Sqrt(bin30));
  file->cd("em_cat3_NbtagGe1");
  hist->Write("data_obs");
  file->Close();

}
