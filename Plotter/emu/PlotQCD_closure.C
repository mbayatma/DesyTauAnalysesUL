#include "HttStylesNew.cc"
#include "CMS_lumi.C"

void PlotQCD_closure(TString era = "2016",
		     bool extrap = false
		     // TString histName = "IsolationCorrection"
		     ) {

  SetStyle();

  TString histName = "NonClosureCorrection";
  if (extrap)
    histName = "IsolationCorrection";

  TString fileName = "/nfs/dust/cms/user/rasp/CMSSW/Update/CMSSW_10_6_26/src/DesyTauAnalyses/Common/data/QCDweights_" + era + ".root"; 

  TFile * file = new TFile(fileName);
  TH1D * hist = (TH1D*)file->Get(histName);
  int nBinsX = hist->GetNbinsX();
  int nBinsY = hist->GetNbinsY();
  std::cout << "nBinsX = " << nBinsX << std::endl;
  std::cout << "nBinsY = " << nBinsY << std::endl;
  std::cout << std::endl;
  std::cout << "binsX -> " << std::endl;
  for (int iB=1; iB<=nBinsX; ++iB) {
    float xmin = hist->GetXaxis()->GetBinLowEdge(iB);
    float xmax = hist->GetXaxis()->GetBinLowEdge(iB+1);
    std::cout << iB << "[" << xmin << "-" << xmax << "]" << std::endl; 
  }
  std::cout << std::endl;
  std::cout << "binsY -> " << std::endl;
  double binsX[5] = {10,20,25,30,100};
  double binsY[5] = {10,20,25,30,100};

  for (int iB=1; iB<=nBinsX; ++iB) {
    float xmin = hist->GetYaxis()->GetBinLowEdge(iB);
    float xmax = hist->GetYaxis()->GetBinLowEdge(iB+1);
    std::cout << iB << "[" << xmin << "-" << xmax << "]" << std::endl; 
  }

  TH2D * histNew = new TH2D("histNew","",nBinsX,binsX,nBinsY,binsY);
  for (int iB=1; iB<=nBinsX; ++iB) {
    for (int jB=1; jB<=nBinsY; ++jB) {
      double x = hist->GetBinContent(iB,jB);
      double y = 0.01*floor(100.*x);
      histNew->SetBinContent(iB,jB,y);
    }
  }
  histNew->GetXaxis()->SetTitle("muon p_{T} [GeV]");
  histNew->GetYaxis()->SetTitle("electron p_{T} [GeV]");
  histNew->GetXaxis()->SetNdivisions(505);
  histNew->GetYaxis()->SetNdivisions(505);

  TCanvas * canv = MakeCanvas("canv","canv",600,600);
  histNew->SetMarkerSize(1.6);
  histNew->Draw("text");
  canv->SetLogx(true);
  canv->SetLogy(true);
  for (int i=1; i<nBinsX; ++i) {
    TLine * line = new TLine(10, binsY[i], 100, binsY[i]);
    line->SetLineStyle(3);
    line->Draw();
  }
  for (int i=1; i<nBinsX; ++i) {
    TLine * line = new TLine(binsX[i], 10, binsX[i], 100);
    line->SetLineStyle(3);
    line->Draw();
  }
  lumi_13TeV = "2018, 59.7 fb^{-1}";
  if (era=="2017")
    lumi_13TeV = "2017, 41.5 fb^{-1}";
  if (era=="2016")
    lumi_13TeV = "2016, 35.9 fb^{-1}";
  writeExtraText = true;
  extraText = "";
  CMS_lumi(canv,4,33); 

  canv->Update();
  
  if (extrap)
    canv->Print("iso_correction_"+era+".pdf","Portrait pdf");
  else
    canv->Print("non_closure_correction_pt_"+era+".pdf","Portrait pdf");

}
