using namespace std;

#include "DesyTauAnalyses/Plotter/interface/settings.h"
#include "DesyTauAnalyses/Plotter/bin/HttStylesNew.cc"
#include "TString.h"
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TSystem.h"
#include <iostream>
#include <map>
#include <vector>
#include "DesyTauAnalyses/BBHTT/interface/HtoH.h"
#include "DesyTauAnalyses/Common/interface/Config.h"

void Check(TH1D * hist) {
  if (hist==NULL) {
    std::cout << "histogram " << hist->GetName() << " is absent in the datacards file... quitting" << std::endl;
    exit(-1);
  }
}

void Plot(TFile * file,
	  TString era,
	  TString channel,
	  TString category,
	  TString xtitle,
	  bool blindData, 
	  float xmin_blind,
	  float xmax_blind,
	  TString outputdir
	  ) {

  gStyle->SetOptStat(0000);

  bool plotLegend = true;
  bool legRight = true;
  bool logY = false;
  bool logX = false;
  float yLower = 10;
  float scaleYUpper = 20;
  //  TString xtitle = "m_{#tau#tau} (GeV)";
  TString ytitle = "Events";

  TH1D * histData = (TH1D*)file->Get(category+"/data_obs");
  if (histData==NULL) {
    std::cout << "  era/category " << era << "/" << category << " does not exist" << std::endl;
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

  TH1D * VV  = (TH1D*)file->Get(category+"/VV");
  TH1D * TT  = (TH1D*)file->Get(category+"/TT");
  TH1D * ST  = (TH1D*)file->Get(category+"/ST");
  TH1D * ZTT = (TH1D*)file->Get(category+"/ZTT");
  TH1D * ZLL = (TH1D*)file->Get(category+"/ZL");
  TH1D * W   = (TH1D*)file->Get(category+"/W");
  Check(VV); Check(TT); Check(ST); Check(ZTT); Check(ZLL); Check(W);

  TH1D * QCD = NULL;
  if(channel=="em")
    QCD = (TH1D*)file->Get(category+"/QCD");
  else
    QCD = (TH1D*)file->Get(category+"/jetFakes");
  Check(QCD);

  TH1D * wFakes = NULL;
  if(channel=="tt") {
    wFakes = (TH1D*)file->Get(category+"/wFakes");
    Check(wFakes);
  }

  std::cout << TT << " " << ZTT << " " << ZLL << " " << ST << " " << W << " " << QCD << " " << wFakes << std::endl;

  TH1D * ggH = (TH1D*)file->Get(category+"/ggH125");
  TH1D * qqH = (TH1D*)file->Get(category+"/qqH125");
  TH1D * WH  = (TH1D*)file->Get(category+"/WH125");
  TH1D * ZH  = (TH1D*)file->Get(category+"/ZH125");
  Check(ggH); Check(qqH); Check(WH); Check(ZH);

  TH1D * bbH_yt2 = (TH1D*)file->Get(category+"/bbH125_yt2");
  TH1D * bbH_yb2 = (TH1D*)file->Get(category+"/bbH125_yb2");
  TH1D * bbH_ybyt = (TH1D*)file->Get(category+"/bbH125_ybyt");
  Check(bbH_yt2); Check(bbH_yb2), Check(bbH_ybyt);
  
  TH1D * bbH_yb2_nobb = (TH1D*)file->Get(category+"/bbH125_yb2_nobb");
  TH1D * bbH_ybyt_nobb = (TH1D*)file->Get(category+"/bbH125_ybyt_nobb");
  Check(bbH_yb2_nobb); Check(bbH_ybyt_nobb);

  std::cout << "TT   : " << TT->GetSumOfWeights() << std::endl;
  std::cout << "VV   : " << VV->GetSumOfWeights() << std::endl;
  std::cout << "W    : " << W->GetSumOfWeights() << std::endl;
  std::cout << "ST   : " << ST->GetSumOfWeights() << std::endl;
  std::cout << "QCD  : " << QCD->GetSumOfWeights() << std::endl;
  if(channel=="tt")
    std::cout << "wF   : " << wFakes->GetSumOfWeights() << std::endl;
  std::cout << "ZLL  : " << ZLL->GetSumOfWeights() << std::endl;
  std::cout << "ZTT  : " << ZTT->GetSumOfWeights() << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "ggH  : " << ggH->GetSumOfWeights() << std::endl;
  std::cout << "qqH  : " << qqH->GetSumOfWeights() << std::endl;
  std::cout << "WH   : " << WH->GetSumOfWeights() << std::endl;
  std::cout << "ZH   : " << ZH->GetSumOfWeights() << std::endl;
  std::cout << std::endl;
  std::cout << "bbH_yt2       : " << bbH_yt2->GetSumOfWeights() << std::endl;
  std::cout << "bbH_yb2       : " << bbH_yb2->GetSumOfWeights() << std::endl;
  std::cout << "bbH_ybyt      : " << bbH_ybyt->GetSumOfWeights() << std::endl;
  std::cout << "bbH_yb2_nobb  : " << bbH_yb2_nobb->GetSumOfWeights() << std::endl;
  std::cout << "bbH_ybyt_nobb : " << bbH_ybyt_nobb->GetSumOfWeights() << std::endl;
  std::cout << std::endl;

  ggH->Add(ggH,qqH);
  ggH->Add(ggH,WH);
  ggH->Add(ggH,ZH);

  VV->Add(VV,ST);
  VV->Add(VV,W);

  TH1D * bbH = (TH1D*)bbH_yb2->Clone("bbH");
  TH1D * bbH_nobb = (TH1D*)bbH_yb2_nobb->Clone("bbH_nobb");

  bbH->Add(bbH,bbH_yt2);
  bbH->Add(bbH,bbH_ybyt);
  bbH_nobb->Add(bbH_nobb,bbH_ybyt_nobb);

  if(channel=="tt")
    QCD->Add(QCD,wFakes);

  int nBins = histData->GetNbinsX();

  //  adding normalization systematics
  double ZTT_norm = 0.04; //  normalization ZTT :  4% (EMBEDDED)
  double VV_norm = 0.05;  //  normalization EWK :  5%
  double QCD_norm = 0.07; //  normalization Fakes : 10%
  double ZLL_mtau = 0.10; //  l->tau fake rate ZLL : 10%
  double TT_norm  = 0.06; //  normalization TT  :  6%
  double eff_MC  = 0.04;

  for (int iB=1; iB<=nBins; ++iB) {

    float ztt  = ZTT->GetBinContent(iB);
    float ztte = ZTT->GetBinError(iB);
    ztte = TMath::Sqrt(ztte*ztte+ztt*ztt*(ZTT_norm*ZTT_norm+eff_MC*eff_MC));
    ZTT->SetBinError(iB,ztte);

    float ewk  = VV->GetBinContent(iB);
    float ewke = VV->GetBinError(iB);
    ewke = TMath::Sqrt(ewke*ewke+ewk*ewk*(VV_norm*VV_norm+eff_MC*eff_MC));
    VV->SetBinError(iB,ewke);

    float qcd  = QCD->GetBinContent(iB);
    float qcde = QCD->GetBinError(iB);
    qcde = TMath::Sqrt(qcde*qcde+qcd*qcd*QCD_norm*QCD_norm);
    QCD->SetBinError(iB,qcde);
    if (qcd<0) {
      QCD->SetBinContent(iB,0.);
      QCD->SetBinError(iB,0.);
    }

    float tt  = TT->GetBinContent(iB);
    float tte = TT->GetBinError(iB);
    tte = TMath::Sqrt(tte*tte+tt*tt*TT_norm*TT_norm);
    TT->SetBinError(iB,tte);

    float zll  = ZLL->GetBinContent(iB);
    float zlle = ZLL->GetBinError(iB);
    zlle = TMath::Sqrt(zlle*zlle+zll*zll*eff_MC*eff_MC);
    ZLL->SetBinError(iB,zlle);

  }

  VV->Add(VV,ZLL);
  TT->Add(TT,VV);
  QCD->Add(QCD,VV);
  ZTT->Add(ZTT,QCD);
  ggH->Add(ggH,ZTT);

  std::cout << std::endl;
  std::cout << "Model    = " << ggH->GetSumOfWeights() << std::endl;
  std::cout << "Data     = " << histData->GetSumOfWeights() << std::endl;
  std::cout << "ratio    = " << histData->GetSumOfWeights()/QCD->GetSumOfWeights() << std::endl;
  std::cout << "bbH      = " << bbH->GetSumOfWeights() << std::endl;
  std::cout << "bbH_nobb = " << bbH_nobb->GetSumOfWeights() << std::endl; 
  std::cout << std::endl;
  bbH->Scale(100);

  TH1D * bkgdErr = (TH1D*)ggH->Clone("bkgdErr");
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
    ggH->SetBinError(iB,0);
  }
  if (blindData) {
    for (int iB=1; iB<=nBins; ++iB) {
      float center = histData->GetXaxis()->GetBinCenter(iB);
      if (center>xmin_blind&&center<xmax_blind) {
	histData->SetBinContent(iB,1e+7);
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
  bbH->SetLineStyle(1);
  bbH->SetLineColor(2);
  bbH->SetLineWidth(2);

  histData->GetXaxis()->SetTitle(xtitle);
  histData->GetYaxis()->SetTitle(ytitle);
  histData->GetXaxis()->SetRangeUser(31,239);
  histData->GetYaxis()->SetTitleOffset(1.3);
  histData->GetYaxis()->SetTitleSize(0.06);

  ggH->GetXaxis()->SetTitle(xtitle);
  ggH->GetYaxis()->SetTitle(ytitle);
  ggH->GetXaxis()->SetRangeUser(31,239);
  ggH->GetYaxis()->SetTitleOffset(1.3);
  ggH->GetYaxis()->SetTitleSize(0.06);

  float yUpper = QCD->GetMaximum();

  histData->GetYaxis()->SetRangeUser(0,1.2*yUpper);
  ggH->GetYaxis()->SetRangeUser(0,1.2*yUpper);

  if (logY) {
    histData->GetYaxis()->SetRangeUser(yLower,scaleYUpper*yUpper);
    ggH->GetYaxis()->SetRangeUser(yLower,scaleYUpper*yUpper);
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

  histData->SetTitle(category+" : "+era);
  ggH->SetTitle(category+" : "+era);

  ggH->Draw("h");
  ZTT->Draw("sameh");
  QCD->Draw("sameh");
  TT->Draw("sameh");
  VV->Draw("sameh");
  bkgdErr->Draw("e2same");
  histData->Draw("e1same");
  bbH->Draw("sameh");
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

  TLegend * leg;
  if (legRight) leg = new TLegend(0.7,0.55,0.90,0.85);
  else leg = new TLegend(0.20,0.40,0.50,0.70);
  SetLegendStyle(leg);
  leg->SetTextSize(0.04);
  leg->AddEntry(histData,"Data","lp");
  leg->AddEntry(ggH,"H(125)","f");
  leg->AddEntry(ZTT,"Z#rightarrow #tau#tau","f");
  leg->AddEntry(QCD,"QCD","f");
  leg->AddEntry(TT,"t#bar{t}","f");
  leg->AddEntry(VV,"electroweak","f");
  leg->AddEntry(bbH,"bbH(125)x100","l");
  if (plotLegend) leg->Draw();

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
  ratioH->GetYaxis()->SetRangeUser(0.501,1.499);
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

  canv1->Print(outputdir+"/"+channel+"-"+category+"_"+era+".png");
  std::cout << std::endl; 
  std::cout << "+++++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << std::endl;
  delete file;

}

int main(int argc, char * argv[]) {

  if (argc!=2) {
    std::cout << "Usage : PlotDatacards [config]" << std::endl;
    exit(-1);
  }

  string cmsswBase = (getenv("CMSSW_BASE"));
  string config_file = cmsswBase + "/src/DesyTauAnalyses/Plotter/datacards/"+string(argv[1]);
  Config cfg(config_file.c_str());

  TString filename = TString(cfg.get<string>("FileName"));
  TString era = TString(cfg.get<string>("Era"));
  TString channel = TString(cfg.get<string>("Channel"));
  vector<string> categories = cfg.get<vector<string> >("Categories");  
  bool blindData = cfg.get<bool>("BlindData");
  TString xtitle = TString(cfg.get<string>("Xtitle"));
  float xmin_blind = cfg.get<float>("XminBlind");
  float xmax_blind = cfg.get<float>("XmaxBlind");
  string outputdir = cfg.get<string>("PlotDir");

  TFile * file = new TFile(filename);
  if (file->IsZombie()||file==NULL) {
    std::cout << "cannot open RooT file " << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << std::endl;
  std::cout << "processing era " << era << "  channel = " << channel << std::endl;
  std::cout << std::endl;
  for (auto category : categories) {
    cout << "Run on category: " << category <<endl;
    Plot(file,era,channel,TString(category),xtitle,blindData,xmin_blind,xmax_blind,TString(outputdir));	
  }

}
  

