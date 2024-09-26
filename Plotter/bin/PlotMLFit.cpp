using namespace std;

#include "DesyTauAnalyses/Plotter/bin/HttStylesNew.cc"
#include "DesyTauAnalyses/Plotter/bin/CMS_lumi.C"
#include "DesyTauAnalyses/Plotter/interface/settings.h"
#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TSystem.h"
#include <iostream>
#include <map>
#include <vector>
#include "DesyTauAnalyses/Common/interface/Config.h"
#include "TGraphAsymmErrors.h"

std::map<TString, TString> catMap_tt = {
  {"bbhtt_tt_1_13TeV","bbH"},
  {"bbhtt_tt_2_13TeV","Fakes"},
  {"bbhtt_tt_3_13TeV","Drell-Yan"},
  {"bbhtt_tt_4_13TeV","TTbar"}
};

std::map<TString, TString> catMap_em = {
  {"bbhtt_em_1_13TeV","TTbar"},
  {"bbhtt_em_2_13TeV","bbHtautau"},
  {"bbhtt_em_3_13TeV","bbHWW"}
};

std::map<TString, TString> lumiLegend = {
  {"2018","2018, 59.8 fb^{-1}"},
  {"2017","2017, 41.5 fb^{-1}"},
  {"2016","2016, 36.3 fb^{-1}"}
};

void Check(TH1D * hist, TString name) {
  if (hist==NULL) {
    std::cout << "histogram " << name << " is absent in the datacards file... quitting" << std::endl;
    exit(-1);
  }
}

void Plot(TFile * file,
	  TString era,
	  TString channel,
	  TString cat,
	  bool postfit,
	  TString xtitle,
	  bool logY,
	  bool plotLegend,
	  bool legRight,
	  bool blindData, 
	  float xmin_blind,
	  float xmax_blind,
	  float XMin,
	  float XMax,
	  float YMin,
	  float YMax,
	  TString outputdir
	  ) {

  gStyle->SetOptStat(0000);

  bool logX = false;
  float yLower = 0.5;
  float scaleYUpper = 1000;
  if (channel=="em") scaleYUpper = 1000;
  TString ytitle = "Events";

  TString category = "shapes_prefit/" + cat + era;
  if (postfit)
    category = "shapes_fit_s/" + cat + era;

  std::cout << category << std::endl;

  //  TH1D * histData = (TH1D*)file->Get(category+"/data_obs");
  TGraphAsymmErrors * graphData = (TGraphAsymmErrors*)file->Get(category+"/data");
  TH1D * totalBkg = (TH1D*)file->Get(category+"/total_background");
  if (graphData==NULL||totalBkg==NULL) {
    std::cout << "  category "  << category << " does not exist" << std::endl;
    std::cout << "  nothing is done... " << std::endl;
    std::cout << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++" << std::endl;
    std::cout << std::endl;
    return;  
  }
  else {
    std::cout << std::endl;
    std::cout << "processing era/category : " << era << "/" << category << std::endl;
    std::cout << std::endl;
  }
  int nBins = totalBkg->GetNbinsX();
  TH1D * histData = (TH1D*)totalBkg->Clone("histData");
  TH1D * H125 = (TH1D*)totalBkg->Clone("H125");
  for (int iB=0; iB<nBins; ++iB) {
    double xData = graphData->GetY()[iB];
    double eData = TMath::Sqrt(xData);
    histData->SetBinContent(iB+1,xData);
    histData->SetBinError(iB+1,eData);
  }
  

  TH1D * VV  = (TH1D*)file->Get(category+"/VV");
  TH1D * TT  = (TH1D*)file->Get(category+"/TT");
  TH1D * ST  = (TH1D*)file->Get(category+"/ST");
  TH1D * ZTT = (TH1D*)file->Get(category+"/ZTT");
  TH1D * ZLL = (TH1D*)file->Get(category+"/ZL");
  TH1D * W   = NULL;
  if (channel=="em") (TH1D*)file->Get(category+"/W");
  else {
    W = (TH1D*)totalBkg->Clone("WJets");
    for (int iB=1; iB<=nBins; ++iB) {
      W->SetBinContent(iB,0);
      W->SetBinError(iB,0);
    }
  }
  Check(VV,"VV"); Check(TT,"TT"); Check(ST,"ST"); Check(ZTT,"ZTT"); Check(ZLL,"ZL"); 
  if (channel=="") Check(W,"W");

  TH1D * QCD = NULL;
  if(channel=="em") {
    QCD = (TH1D*)file->Get(category+"/QCD");
    Check(QCD,"QCD");
  }
  else {
    QCD = (TH1D*)file->Get(category+"/jetFakes");
    Check(QCD,"jetFakes");
  }

  TH1D * wFakes = NULL;
  if(channel=="tt") {
    wFakes = (TH1D*)file->Get(category+"/wFakes");
    Check(wFakes,"wFakes");
  }

  //  std::cout << TT << " " << ZTT << " " << ZLL << " " << ST << " " << W << " " << QCD << " " << wFakes << std::endl;

  TH1D * ggH = (TH1D*)file->Get(category+"/ggH_htt");
  TH1D * qqH = (TH1D*)file->Get(category+"/qqH125");
  TH1D * WH  = (TH1D*)file->Get(category+"/WH125");
  TH1D * ZH  = (TH1D*)file->Get(category+"/ZH125");
  Check(ggH,"ggH_tt"); Check(qqH,"qqH125"); Check(WH,"WH125"); Check(ZH,"ZH125");

  TH1D * bbH_yt2 = (TH1D*)file->Get(category+"/ggH_bb_htt");
  TH1D * bbH_yb2 = (TH1D*)file->Get(category+"/bbH_htt");
  Check(bbH_yt2,"ggH_bb_htt"); Check(bbH_yb2,"bbH_htt"); 
  
  TH1D * ggHWW = NULL;
  TH1D * qqHWW = NULL;
  TH1D * WHWW = NULL;
  TH1D * ZHWW = NULL;

  // FIX ME : Add bbHWW templates for em
  TH1D * bbHWW_yt2 = NULL;
  TH1D * bbHWW_yb2 = NULL;

  if (channel=="em") {
    ggHWW = (TH1D*)file->Get(category+"/ggH_hww");
    qqHWW = (TH1D*)file->Get(category+"/qqHWW125");
    WHWW  = (TH1D*)file->Get(category+"/WHWW125");
    ZHWW  = (TH1D*)file->Get(category+"/ZHWW125");
    Check(ggHWW,"ggHWW125"); Check(qqHWW,"qqHWW125"); Check(WHWW,"WHWW125"); Check(ZHWW,"ZHWW125");
    bbHWW_yb2 = (TH1D*)file->Get(category+"/bbH_hww");
    bbHWW_yt2 = (TH1D*)file->Get(category+"/ggH_bb_hww");
    Check(bbHWW_yb2,"bbH_hww");Check(bbHWW_yt2,"ggH_bb_hww");
  }

  double xTT = TT->GetSumOfWeights();
  double xEWK = VV->GetSumOfWeights() + W->GetSumOfWeights() + ST->GetSumOfWeights() + ZLL->GetSumOfWeights();
  double xQCD =  QCD->GetSumOfWeights();
  if (channel=="tt") xQCD += wFakes->GetSumOfWeights();
  double xDY = ZTT->GetSumOfWeights();
  double xHiggs = ggH->GetSumOfWeights() + qqH->GetSumOfWeights() + WH->GetSumOfWeights() + ZH->GetSumOfWeights();
  if (channel=="em") xHiggs += ggHWW->GetSumOfWeights() + qqHWW->GetSumOfWeights() + WHWW->GetSumOfWeights() + ZHWW->GetSumOfWeights();
  double xTotal = xTT+xEWK+xDY+xQCD+xHiggs;
  double xData = histData->GetSumOfWeights();
  std::cout << "Top     : " << xTT << std::endl;
  std::cout << "EWK     : " << xEWK << std::endl;
  std::cout << "ZTT     : " << xDY << std::endl;
  if(channel=="em")
    std::cout << "QCD     : " << xQCD << std::endl;
  else
    std::cout << "Fakes   : " << xQCD << std::endl;
  std::cout << "Higgs  : " << xHiggs << std::endl;
  std::cout << "Total  : " << xTotal << std::endl;
  std::cout << "Data   : " << xData << std::endl;
  std::cout << "ratio  = " << xData/xTotal << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "ggH   : " << ggH->GetSumOfWeights() << std::endl;
  std::cout << "qqH   : " << qqH->GetSumOfWeights() << std::endl;
  std::cout << "WH    : " << WH->GetSumOfWeights() << std::endl;
  std::cout << "ZH    : " << ZH->GetSumOfWeights() << std::endl;
  if (channel=="em") {
    std::cout << "ggHWW : " << ggHWW->GetSumOfWeights() << std::endl;
    std::cout << "qqHWW : " << qqHWW->GetSumOfWeights() << std::endl;
    std::cout << "WHWW  : " << WHWW->GetSumOfWeights() << std::endl;
    std::cout << "ZHWW  : " << ZHWW->GetSumOfWeights() << std::endl;
  }  
  std::cout << std::endl;
  std::cout << "bbH_yt2       : " << bbH_yt2->GetSumOfWeights() << std::endl;
  std::cout << "bbH_yb2       : " << bbH_yb2->GetSumOfWeights() << std::endl;
  if (channel=="em") {
    std::cout << "bbHWW_yt2     : " << bbHWW_yt2->GetSumOfWeights() << std::endl;
    std::cout << "bbHWW_yb2     : " << bbHWW_yb2->GetSumOfWeights() << std::endl;
  }
  std::cout << std::endl;

  ggH->Add(ggH,qqH);
  ggH->Add(ggH,WH);
  ggH->Add(ggH,ZH);
  if (channel=="em") {
    ggH->Add(ggH,ggHWW);
    ggH->Add(ggH,qqHWW);
    ggH->Add(ggH,WHWW);
    ggH->Add(ggH,ZHWW);
  }

  VV->Add(VV,ST);
  VV->Add(VV,W);

  TH1D * bbH = (TH1D*)bbH_yb2->Clone("bbH");
  bbH->Add(bbH,bbH_yt2);

  TH1D * bbHWW = NULL;
  if (channel=="em") {
    bbHWW = (TH1D*)bbHWW_yb2->Clone("bbHWW");
    bbHWW->Add(bbHWW,bbHWW_yt2);
  }

  if(channel=="tt")
    QCD->Add(QCD,wFakes);


  VV->Add(VV,ZLL);
  TT->Add(TT,VV);
  QCD->Add(QCD,TT);
  ZTT->Add(ZTT,QCD);
  ggH->Add(ggH,ZTT);

  std::cout << std::endl;
  //  std::cout << "Model    = " << ggH->GetSumOfWeights() << std::endl;
  //  std::cout << "Data     = " << histData->GetSumOfWeights() << std::endl;
  std::cout << "bbH_bb   = " << bbH->GetSumOfWeights() << std::endl;
  bbH->Scale(50);
  std::cout << std::endl;
  if (channel=="em") {
    std::cout << "bbHWW_tot = " << bbHWW->GetSumOfWeights() << std::endl;
    //    bbH->Add(bbH,bbHWW);
    bbHWW->Scale(50);
  }

  TH1D * bkgdErr = (TH1D*)totalBkg->Clone("bkgdErr");
  bkgdErr->SetFillStyle(3013);
  bkgdErr->SetFillColor(1);
  bkgdErr->SetMarkerStyle(21);
  bkgdErr->SetMarkerSize(0);
  
  for (int iB=1; iB<=nBins; ++iB) {
    TT->SetBinError(iB,0);
    VV->SetBinError(iB,0);
    ZLL->SetBinError(iB,0);
    ZTT->SetBinError(iB,0);
    QCD->SetBinError(iB,0);
    bbH->SetBinError(iB,0);
    if (channel=="em") bbHWW->SetBinError(iB,0);
    ggH->SetBinError(iB,0);
    H125->SetBinError(iB,0);
  }
  float chi2 = 0;
  for (int iB=1; iB<=nBins; ++iB) {
    float xData = histData->GetBinContent(iB);
    float xMC = bkgdErr->GetBinContent(iB);
    float eMC = bkgdErr->GetBinError(iB);
    float err2 = xMC+eMC*eMC;
    if (xMC>1e-1) {
      float diff2 = (xData-xMC)*(xData-xMC);
      chi2 += diff2/err2;
    }
  }
  std::cout << std::endl;
  std::cout << "Chi2/ndof = " << chi2 << "/" << nBins << std::endl;
  std::cout << "Prob = " << TMath::Prob(chi2,double(nBins)) << std::endl;
  std::cout << std::endl;


  if (blindData) {
    for (int iB=1; iB<=nBins; ++iB) {
      float center = histData->GetXaxis()->GetBinCenter(iB);
      if (center>xmin_blind&&center<xmax_blind) {
	histData->SetBinContent(iB,1e+8);
	histData->SetBinError(iB,0);
      }
    }
  }

  InitData(histData);

  InitHist(QCD,"","",TColor::GetColor("#c6f74a"),1001);
  InitHist(TT,"","",TColor::GetColor("#9999CC"),1001);
  InitHist(VV,"","",TColor::GetColor("#DE5A6A"),1001);
  InitHist(ZTT,"","",TColor::GetColor("#FFCC66"),1001);
  InitHist(ggH,"","",TColor::GetColor("#FFCCFF"),1001);
  InitHist(H125,"","",TColor::GetColor("#FFCCFF"),1001);
  bbH->SetLineStyle(1);
  bbH->SetLineColor(4);
  bbH->SetLineWidth(3);
  if (channel=="em") {
    bbHWW->SetLineStyle(1);
    bbHWW->SetLineColor(2);
    bbHWW->SetLineWidth(3);
  }
  histData->GetXaxis()->SetTitle(xtitle);
  histData->GetYaxis()->SetTitle(ytitle);
  //  histData->GetXaxis()->SetRangeUser(31,239);
  histData->GetYaxis()->SetTitleOffset(1.3);
  histData->GetYaxis()->SetTitleSize(0.06);

  ggH->GetXaxis()->SetTitle(xtitle);
  ggH->GetYaxis()->SetTitle(ytitle);
  //  ggH->GetXaxis()->SetRangeUser(31,239);
  ggH->GetYaxis()->SetTitleOffset(1.3);
  ggH->GetYaxis()->SetTitleSize(0.06);

  float yUpper = QCD->GetMaximum();

  histData->GetYaxis()->SetRangeUser(0,1.4*yUpper);
  H125->GetYaxis()->SetRangeUser(0,1.4*yUpper);
  histData->GetXaxis()->SetRangeUser(XMin,XMax);
  H125->GetXaxis()->SetRangeUser(XMin,XMax);  

  if (logY) {
    histData->GetYaxis()->SetRangeUser(yLower,scaleYUpper*yUpper);
    H125->GetYaxis()->SetRangeUser(yLower,scaleYUpper*yUpper);
  }

  histData->SetMarkerSize(1.4);
  histData->GetXaxis()->SetLabelSize(0);
  histData->GetYaxis()->SetLabelSize(0.06);

  ggH->GetXaxis()->SetLabelSize(0);
  ggH->GetYaxis()->SetLabelSize(0.06);
  
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

  //  histData->SetTitle(category+" : "+era);
  //  ggH->SetTitle(category+" : "+era);

  H125->Draw("h");
  ZTT->Draw("sameh");
  QCD->Draw("sameh");
  TT->Draw("sameh");
  VV->Draw("sameh");
  bkgdErr->Draw("e2same");
  histData->Draw("e1same");
  bbH->Draw("sameh");
  if (channel=="em") bbHWW->Draw("sameh");

  TLegend * leg;
  if (legRight) leg = new TLegend(0.7,0.55,0.90,0.85);
  else leg = new TLegend(0.20,0.55,0.45,0.87);
  SetLegendStyle(leg);
  leg->SetTextSize(0.04);
  leg->AddEntry(histData,"Data","lp");
  leg->AddEntry(H125,"H(125)","f");
  leg->AddEntry(ZTT,"Z#rightarrow #tau#tau","f");
  if (channel=="tt")
    leg->AddEntry(QCD,"j#rightarrow#tau mis-id","f");
  else
    leg->AddEntry(QCD,"QCD","f");
  leg->AddEntry(TT,"t#bar{t}","f");
  leg->AddEntry(VV,"electroweak","f");
  leg->AddEntry(bbH,"bbH#tau#tau(x50)","l");
  if (channel=="em") leg->AddEntry(bbHWW,"bbHWW(x50)","l");
  if (plotLegend) leg->Draw();

  lumi_13TeV = lumiLegend[era];
  writeExtraText = true;
  extraText = "Preliminary";
  CMS_lumi(upper,4,33);

  if (logY) upper->SetLogy(true);
  if (logX) upper->SetLogx(true);
  

    
  upper->Draw("SAME");
  upper->RedrawAxis();
  upper->Modified();
  upper->Update();
  canv1->cd();

  TH1D * ratioH = (TH1D*)histData->Clone("ratioH");
  TH1D * ratioErrH = (TH1D*)bkgdErr->Clone("ratioErrH");
  ratioH->SetMarkerColor(1);
  ratioH->SetMarkerStyle(20);
  ratioH->SetMarkerSize(1.2);
  ratioH->SetLineColor(1);
  ratioH->GetYaxis()->SetRangeUser(YMin,YMax);
  ratioH->GetYaxis()->SetNdivisions(505);
  ratioH->GetXaxis()->SetLabelFont(42);
  ratioH->GetXaxis()->SetLabelOffset(0.04);
  ratioH->GetXaxis()->SetLabelSize(0.14);
  ratioH->GetXaxis()->SetTitleSize(0.13);
  ratioH->GetXaxis()->SetTitleOffset(1.2);
  ratioH->GetYaxis()->SetTitle("obs/exp");
  ratioH->GetYaxis()->SetLabelFont(42);
  ratioH->GetYaxis()->SetLabelOffset(0.015);
  ratioH->GetYaxis()->SetLabelSize(0.13);
  ratioH->GetYaxis()->SetTitleSize(0.14);
  ratioH->GetYaxis()->SetTitleOffset(0.5);
  ratioH->GetXaxis()->SetTickLength(0.07);
  ratioH->GetYaxis()->SetTickLength(0.04);
  ratioH->GetYaxis()->SetLabelOffset(0.01);

  for (int iB=1; iB<=nBins; ++iB) {
    float x1 = histData->GetBinContent(iB);
    float x2 = bkgdErr->GetBinContent(iB);
    ratioErrH->SetBinContent(iB,1.0);
    ratioErrH->SetBinError(iB,0.0);
    float xBkg = bkgdErr->GetBinContent(iB);
    float errBkg = bkgdErr->GetBinError(iB);
    if (xBkg>0) {
      float relErr = errBkg/xBkg;
      ratioErrH->SetBinError(iB,relErr);

    }
    if (x1>0&&x2>0) {
      float e1 = histData->GetBinError(iB);
      float ratio = x1/x2;
      float eratio = e1/x2;
      ratioH->SetBinContent(iB,ratio);
      ratioH->SetBinError(iB,eratio);
    }
    else {
      ratioH->SetBinContent(iB,1000);
    }
  }

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

  ratioH->SetTitle("");
  ratioH->Draw("e1");
  ratioErrH->Draw("e2same");
  ratioH->Draw("e1same");

  lower->Modified();
  lower->RedrawAxis();
  if (logX) lower->SetLogx(true);
  canv1->cd();
  canv1->Modified();
  canv1->cd();
  canv1->SetSelected(canv1);
  canv1->Update();
    
  string cmsswBase = (getenv("CMSSW_BASE"));

  canv1->Print(outputdir+"/"+cat+era+".png");
  std::cout << std::endl; 
  std::cout << "+++++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << std::endl;
  delete file;

}

int main(int argc, char * argv[]) {

  if (argc!=4) {
    std::cout << "Usage : PlotDatacards [era] [category] [channel]" << std::endl;
    exit(-1);
  }

  string cmsswBase = (getenv("CMSSW_BASE"));
  string config_file = cmsswBase + "/src/DesyTauAnalyses/Plotter/datacards/plot_mlfit_"+string(argv[3])+".conf";
  TString era = TString(argv[1]);
  TString category = TString(argv[2]);
  TString channel = TString(argv[3]);

  Config cfg(config_file.c_str());

  TString input_dir = TString(cfg.get<string>("InputDir"));
  bool blindData = cfg.get<bool>("BlindData");
  TString xtitle = TString(cfg.get<string>("Xtitle"));
  float xmin_blind = cfg.get<float>("XminBlind");
  float xmax_blind = cfg.get<float>("XmaxBlind");
  float XMin = cfg.get<float>("XMin");
  float XMax = cfg.get<float>("XMax");
  float YMin = cfg.get<float>("YMin");
  float YMax = cfg.get<float>("YMax");
  bool postfit = cfg.get<bool>("PostFit");
  TString output_dir = TString(cfg.get<string>("PlotDir"));
  bool logY = cfg.get<bool>("logY");
  bool plotLegend = cfg.get<bool>("PlotLegend");
  bool legRight = cfg.get<bool>("LegendRight");

  TFile * file = new TFile(input_dir+"/fitDiagnostics_"+channel+"_data.root");
  if (file->IsZombie()||file==NULL) {
    std::cout << "cannot open RooT file " << input_dir << "/fitDiagnostics_" << channel << "_data.root" << std::endl;
    exit(EXIT_FAILURE);
  }

  SetStyle();

  Plot(file,era,channel,category,postfit,xtitle,logY,plotLegend,legRight,blindData,xmin_blind,xmax_blind,XMin,XMax,YMin,YMax,output_dir);

}
  

