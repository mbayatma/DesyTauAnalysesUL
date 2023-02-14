#include "HttStylesNew.cc"
#include "CMS_lumi.C"
Double_t pol2(Double_t * x, Double_t * par) {

  double r = par[0]+par[1]*x[0]+par[2]*x[0]*x[0];//+par[3]*x[0]*x[0]*x[0];

  return r;

}


void Plot_osss(TString nbtags = "2",
	       TString era = "2017") {

  SetStyle();
  bool logX = false;
  bool logY = false;

  lumi_13TeV = "2018, 60 fb^{-1}";
  if (era=="2017")
    lumi_13TeV = "2017, 41 fb^{-1}";
  if (era=="2016")
    lumi_13TeV = "2016, 36 fb^{-1}";


  TFile * fileOS = new TFile("ff_nbtags_"+nbtags+"_os_"+era+".root");
  TFile * fileSS = new TFile("ff_nbtags_"+nbtags+"_ss_"+era+".root");
  TH1D * histOS = (TH1D*)fileOS->Get("ratioH");
  TH1D * histSS = (TH1D*)fileSS->Get("ratioH");

  TH1D * ratioH = (TH1D*)histOS->Clone("ratioH");
  ratioH->GetYaxis()->SetTitle("DR#rightarrowAR correction");
  ratioH->GetXaxis()->SetTitle("#DeltaR(#tau_{1},#tau_{2}) (GeV)");

  InitData(ratioH);

  int nbins = histOS->GetNbinsX();
  for (int iB=1; iB<=nbins; ++iB) {
    double x1 = histOS->GetBinContent(iB);
    double x2 = histSS->GetBinContent(iB);
    double e1 = histOS->GetBinError(iB);
    double e2 = histSS->GetBinError(iB);
    double r1 = e1/x1;
    double r2 = e2/x2;
    double r = TMath::Sqrt(r1*r1+r2*r2);
    double rat = 0.84;
    double erat = 0.55;
    if (x2>0.) {
      rat  = x1/x2;
      erat = rat*r;
    }
    std::cout << iB << " : " << rat << "+/-" << erat << std::endl;
    ratioH->SetBinContent(iB,rat);
    ratioH->SetBinError(iB,erat);
  }
  ratioH->SetBinContent(14,0.987);   // 2017 nbtag=2
  ratioH->SetBinError(14,0.347486);
  ratioH->SetBinContent(15,1.72443);
  ratioH->SetBinError(15,0.55275);
  ratioH->SetBinContent(16,0.85);
  ratioH->SetBinError(16,0.75275);

  ratioH->GetYaxis()->SetRangeUser(0.,2.);
  TCanvas * dummy1 = new TCanvas("dummy","",400,400);

  TF1 * fitFunc = new TF1("fitFunc",pol2,0.5,5.3,3);
  fitFunc->SetLineColor(2);
  fitFunc->SetParameter(0,1.);
  fitFunc->SetParameter(1,0.);
  fitFunc->SetParameter(2,0.);
  fitFunc->SetParameter(3,0.);
  
  ratioH->Fit("fitFunc","Q");
  delete dummy1;
    
  TH1D * hint = new TH1D("ff_"+era,"",200,0.5,5.3);   
  TH1D * hint_68 = new TH1D("ff_"+era+"_68","",200,0.5,5.3);   
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint_68,0.68);
  TH1D * hint_central = (TH1D*)hint->Clone("hint_central");
  for (int iB=1; iB<=160; ++iB)
    hint_central->SetBinError(iB,0.);
  InitHist(hint,"","",kCyan,1001);
  InitHist(hint_68,"","",kYellow,1001);
  hint->SetMarkerSize(0);
  hint->SetMarkerStyle(0);
  hint_68->SetMarkerSize(0);
  hint_68->SetMarkerStyle(0);
  hint_central->SetLineColor(2);
  hint_central->SetLineWidth(2);
  
  //  ratioH->SetBinContent(16,0.96); // 2016 nbtag=1

  //  ratioH->SetBinContent(16,0.92); // 2017 nbtag=1
  //  ratioH->SetBinError(16,0.34);   // 2017 nbtag=1



  TCanvas * canv = MakeCanvas("canv1", "", 500, 500);

  ratioH->Draw("e1");
  hint->Draw("e3same");
  hint_68->Draw("e3same");
  //  hint_central->Draw("hsame");
  ratioH->Draw("e1same");

  TLegend * leg= new TLegend(0.20,0.85,0.50,0.90);
  SetLegendStyle(leg);
  leg->SetTextSize(0.05);
  leg->SetHeader("nbtags"+nbtags);
  leg->Draw();

  if (logX) canv->SetLogx(true);
  if (logY) canv->SetLogy(true);
  writeExtraText = true;
  extraText = "Preliminary";
  CMS_lumi(canv,4,33); 

  canv->Draw("SAME");
  canv->RedrawAxis();
  canv->Modified();
  canv->Update();

  canv->Print("ff/ff_nbtags"+nbtags+"_osss_"+era+".png");




}
