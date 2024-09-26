#include "HttStylesNew.cc"

//   ratioH->GetYaxis()->SetRangeUser(0.801,1.199);
void CompSamples(
		 TString era = "2018",
		 TString var = "m_vis",
		 //		 TString var = "idisoweight_2",
		 TString sample1 = "DYJetsToLL_M-50",
		 TString sample2 = "DYJetsToLL_M-50",		 
		 bool applyWeight = true,
		 TString weight = "1.0",
		 bool isNorm = true,
		 int Nbins =       50,
		 float xmin =       0,
		 float xmax =     250,
		 float yratioMin = 0.601,
		 float yratioMax = 1.399,
		 float s2 = 1.0
		 ) {

  bool logX = false;
  bool logY = false;

  TString fileName1 = "/nfs/dust/cms/user/rasp/Run/tautau/"+era+"/"+sample1+".root";
  TString fileName2 = "/nfs/dust/cms/user/rasp/Run/tautau_UL/"+era+"/"+sample2+".root";

  //  TString Selection("trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5&&os>0.5&&TMath::Abs(eta_1)<2.1&&TMath::Abs(eta_2)<2.1");
  TString Selection("trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5&&os>0.5&&TMath::Abs(eta_1)<2.1&&TMath::Abs(eta_2)<2.1");

  TString cutsTaus("&&byMediumDeepTau2017v2p1VSjet_1>0.5&&byMediumDeepTau2017v2p1VSjet_2>0.5");
  TString genMatchCuts("&&gen_match_1==5&&gen_match_2==5");
  Selection += cutsTaus;
  Selection += genMatchCuts;
  if (applyWeight) Selection = weight+"*(" + Selection + ")";


  SetStyle();

  TFile * file1 = new TFile(fileName1);
  TTree * tree1 = (TTree*)file1->Get("TauCheck");
  TFile * file2 = new TFile(fileName2);
  TTree * tree2 = (TTree*)file2->Get("TauCheck");
  TH1D * hist1 = new TH1D("hist1","",Nbins,xmin,xmax);
  TH1D * hist2 = new TH1D("hist2","",Nbins,xmin,xmax);
  TH1D * histEv1 = (TH1D*)file1->Get("nWeightedEvents");
  TH1D * histEv2 = (TH1D*)file2->Get("nWeightedEvents");

  double nev1 = histEv1->GetSumOfWeights();
  double nev2 = histEv2->GetSumOfWeights();
  
  double scale1 = 1.;
  double scale2 = 1.;
  
  if (isNorm) {
    scale1 = 10000000.0/nev1;
    scale2 = 10000000.0/nev2;
  }


  TCanvas * dummy = new TCanvas("dummy","",600,600);
  tree1->Draw(var+">>hist1",Selection);
  tree2->Draw(var+">>hist2",Selection);
  delete dummy;

  hist1->Scale(scale1);
  hist2->Scale(scale2);

  for (int iB=1; iB<=Nbins; ++iB) {
    double xOld = hist1->GetBinContent(iB);
    double xNew = hist2->GetBinContent(iB);
    double eOld = hist1->GetBinError(iB);
    double eNew = hist2->GetBinError(iB);
    double xl = hist1->GetBinLowEdge(iB);
    double xu = hist2->GetBinLowEdge(iB+1);
    printf("[%3i,%3i] nom = %7.2f +/- %7.2f   rel = %7.2f +/- %7.2f\n",int(xl),int(xu),xOld,eOld,xNew,eNew);

  }

  InitSignal(hist2);
  InitSignal(hist1);

  hist2->SetLineColor(2);
  hist2->SetLineStyle(1);
  hist2->SetMarkerSize(0);
  hist2->SetMarkerColor(2);

  hist1->SetLineColor(4);
  hist1->SetMarkerColor(4);
  hist1->SetLineStyle(1);
  hist1->SetMarkerSize(0);
  hist1->GetXaxis()->SetLabelSize(0.0);
  hist2->GetXaxis()->SetLabelSize(0.0);

  float maxY = hist1->GetMaximum();
  if (hist2->GetMaximum()>maxY) maxY = hist2->GetMaximum();
  hist1->GetYaxis()->SetRangeUser(0.,1.2*maxY);
  hist2->GetYaxis()->SetRangeUser(0.,1.2*maxY);
  hist2->GetXaxis()->SetTitle(var);
  hist1->GetXaxis()->SetTitle(var);


  TCanvas * canv1 = MakeCanvas("canv1", "", 600, 700);
  TPad * upper = new TPad("upper", "pad",0,0.31,1,1);
  upper->Draw();
  upper->cd();
  upper->SetFillColor(0);
  upper->SetBorderMode(0);
  upper->SetBorderSize(10);
  upper->SetTickx(1);
  upper->SetTicky(1);
  upper->SetLeftMargin(0.17);
  upper->SetRightMargin(0.05);
  upper->SetBottomMargin(0.02);
  upper->SetFrameFillStyle(0);
  upper->SetFrameLineStyle(0);
  upper->SetFrameLineWidth(2);
  upper->SetFrameBorderMode(0);
  upper->SetFrameBorderSize(10);
  upper->SetFrameFillStyle(0);
  upper->SetFrameLineStyle(0);
  upper->SetFrameLineWidth(2);
  upper->SetFrameBorderMode(0);
  upper->SetFrameBorderSize(10);

  hist2->Draw("h");
  hist1->Draw("hsame");

  TLegend * leg = new TLegend(0.6,0.6,0.9,0.9);
  SetLegendStyle(leg);
  leg->SetHeader(sample1);
  leg->AddEntry(hist2,"UL","l");
  leg->AddEntry(hist1,"PreL","l");
  leg->Draw();

  if (logY) upper->SetLogy(true);
  if (logX) upper->SetLogx(true);
  upper->Draw("SAME");
  upper->RedrawAxis();
  upper->Modified();
  upper->Update();
  canv1->cd();

  TH1D * ratioH = (TH1D*)hist2->Clone("ratioH");
  for (int iB=1; iB<=Nbins; ++iB) {
    float num = hist2->GetBinContent(iB);
    float numE = hist2->GetBinError(iB);
    float den = hist1->GetBinContent(iB);
    if (den>0.0) {
      float ratio = num/den;
      float eratio = numE/den; 
      ratioH->SetBinContent(iB,ratio);
      ratioH->SetBinError(iB,eratio);
    }
    else {
      ratioH->SetBinContent(iB,1000.);
      ratioH->SetBinError(iB,0.);
    }
  }

  ratioH->GetXaxis()->SetTitle(var);
  ratioH->GetYaxis()->SetRangeUser(yratioMin,yratioMax);
  ratioH->GetYaxis()->SetNdivisions(505);
  ratioH->GetXaxis()->SetLabelFont(42);
  ratioH->GetXaxis()->SetLabelOffset(0.04);
  ratioH->GetXaxis()->SetLabelSize(0.14);
  ratioH->GetXaxis()->SetTitleSize(0.13);
  ratioH->GetXaxis()->SetTitleOffset(1.2);
  ratioH->GetYaxis()->SetTitle("ratio");
  ratioH->GetYaxis()->SetLabelFont(42);
  ratioH->GetYaxis()->SetLabelOffset(0.015);
  ratioH->GetYaxis()->SetLabelSize(0.13);
  ratioH->GetYaxis()->SetTitleSize(0.14);
  ratioH->GetYaxis()->SetTitleOffset(0.5);
  ratioH->GetXaxis()->SetTickLength(0.07);
  ratioH->GetYaxis()->SetTickLength(0.04);
  ratioH->GetYaxis()->SetLabelOffset(0.01);
  

  // ------------>Primitives in pad: lower
  TPad * lower = new TPad("lower", "pad",0,0,1,0.30);
  lower->Draw();
  lower->cd();
  lower->SetFillColor(0);
  lower->SetBorderMode(0);
  lower->SetBorderSize(10);
  lower->SetGridy();
  lower->SetTickx(1);
  lower->SetTicky(1);
  lower->SetLeftMargin(0.17);
  lower->SetRightMargin(0.05);
  lower->SetTopMargin(0.026);
  lower->SetBottomMargin(0.35);
  lower->SetFrameFillStyle(0);
  lower->SetFrameLineStyle(0);
  lower->SetFrameLineWidth(2);
  lower->SetFrameBorderMode(0);
  lower->SetFrameBorderSize(10);
  lower->SetFrameFillStyle(0);
  lower->SetFrameLineStyle(0);
  lower->SetFrameLineWidth(2);
  lower->SetFrameBorderMode(0);
  lower->SetFrameBorderSize(10);

  ratioH->Draw("e1");

  lower->Modified();
  lower->RedrawAxis();
  if (logX) lower->SetLogx(true);
  canv1->cd();
  canv1->Modified();
  canv1->cd();
  canv1->SetSelected(canv1);
  canv1->Update();
  canv1->Print("comp_"+sample1+"_"+era+"_"+var+".png");

  std::cout << "pre-legacy   (initial) : " << nev1 << std::endl;
  std::cout << "ultra-legacy (initial) : " << nev2 << std::endl;
  std::cout << "pre-legacy   (entries) : " << hist1->GetEntries() << std::endl;
  std::cout << "ultra-legacy (entries) : " << hist2->GetEntries() << std::endl;
  std::cout << "pre-legacy   (yield)   : " << hist1->GetSumOfWeights() << std::endl;
  std::cout << "ultra-legacy (yield)   : " << hist2->GetSumOfWeights() << std::endl;
  std::cout << "pre-legacy   (mean)    : " << hist1->GetMean() << std::endl;
  std::cout << "ultra-legacy (mean)    : " << hist2->GetMean() << std::endl;
  std::cout << "pre-lgacy    (RMS)     : " << hist1->GetRMS() << std::endl;
  std::cout << "ultra-legacy (RMS)     : " << hist2->GetRMS() << std::endl;
  double ratio = hist2->GetSumOfWeights()/hist1->GetSumOfWeights();
  std::cout << "ratio UL/PreL          : " << ratio << std::endl;

}
