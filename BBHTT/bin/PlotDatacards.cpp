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

void Plot(TString filename,
	  TString  era,
	  TString channel,
	  TString category,
	  std::vector<float> bins={0.25,0.4,0.55,0.7,0.85,1.},
	  TString xtitle="BDT score",
	  float xmin_blind=0.7,
	  float xmax_blind=1.,
	  bool blindData=false 
	  ) {

  TFile * file=new TFile(filename);
  if (file->IsZombie()) {
    std::cout << "cannot open RooT file " << filename << std::endl;
    exit(EXIT_FAILURE);
  }


  gStyle->SetOptStat(0000);

  bool plotLegend = true;
  bool legRight = true;
  bool logY = false;
  bool logX = false;
  float yLower = 10;
  float scaleYUpper = 20;
  //  TString xtitle = "m_{#tau#tau} (GeV)";
  TString ytitle = "Events";


  int nbins = bins.size() - 1;
  float xbins[200];
  for (unsigned int iB=0; iB<bins.size(); ++iB)
    xbins[iB] = bins[iB];

  TH1D * histData_ = (TH1D*)file->Get(category+"/data_obs");
  if (histData_==NULL) {
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
  TH1D * histData = (TH1D*)TH1DtoTH1D(histData_,nbins,xbins,true,"_rebinned");

  TH1D * TT_  = (TH1D*)file->Get(category+"/TTL");
  TH1D * ZTT_ = (TH1D*)file->Get(category+"/EMB");
  TH1D * ZLL_ = (TH1D*)file->Get(category+"/ZL");
  TH1D * EWK_ = (TH1D*)file->Get(category+"/VVL"); 
  TH1D * QCD_ = NULL;
  if(channel=="em")
    QCD_ = (TH1D*)file->Get(category+"/QCD");
  else
    QCD_ = (TH1D*)file->Get(category+"/jetFakes");

  TH1D * wFakes_ = NULL;
  if(channel=="tt")
    wFakes_ = (TH1D*)file->Get(category+"/wFakes");

  std::cout << TT_ << " " << ZTT_ << " " << ZLL_ << " " << EWK_ << " " << QCD_ << " " << wFakes_ << std::endl;

  TH1D * ggH_ = (TH1D*)file->Get(category+"/ggHbb125");
  TH1D * bbH_ = (TH1D*)file->Get(category+"/bbH125");
  std::cout << ggH_ << " " << bbH_ << std::endl;

  TH1D * TT = (TH1D*)TH1DtoTH1D(TT_,nbins,xbins,true,"_rebinned");
  TH1D * ZTT = (TH1D*)TH1DtoTH1D(ZTT_,nbins,xbins,true,"_rebinned");
  TH1D * ZLL = (TH1D*)TH1DtoTH1D(ZLL_,nbins,xbins,true,"_rebinned");
  TH1D * QCD = (TH1D*)TH1DtoTH1D(QCD_,nbins,xbins,true,"_rebinned");
  TH1D * EWK = (TH1D*)TH1DtoTH1D(EWK_,nbins,xbins,true,"_rebinned");
  TH1D * wFakes = NULL;
  if(channel=="tt")
    wFakes = (TH1D*)TH1DtoTH1D(wFakes_,nbins,xbins,true,"_rebinned");
  TH1D * ggH = (TH1D*)TH1DtoTH1D(ggH_,nbins,xbins,true,"_rebinned");
  TH1D * bbH = (TH1D*)TH1DtoTH1D(bbH_,nbins,xbins,true,"_rebinned");
  bbH->Add(bbH,ggH);

  std::cout << std::endl;

  int nBins = histData->GetNbinsX();

  std::cout << "Top        : " << TT->GetSumOfWeights() << std::endl;
  std::cout << "EWK        : " << EWK->GetSumOfWeights() << std::endl;
  std::cout << "QCD   : " << QCD->GetSumOfWeights() << std::endl;
  if(channel=="tt")
    std::cout << "wFakes     : " << wFakes->GetSumOfWeights() << std::endl;
  std::cout << "ZLL        : " << ZLL->GetSumOfWeights() << std::endl;
  std::cout << "ZTT        : " << ZTT->GetSumOfWeights() << std::endl;
  
  if(channel=="tt")
    QCD->Add(QCD,wFakes);

  //  adding normalization systematics
  double ZTT_norm = 0.04; //  normalization ZTT :  4% (EMBEDDED)
  double EWK_norm = 0.05; //  normalization EWK :  5%
  double QCD_norm = 0.07; //  normalization Fakes : 10%
  double ZLL_mtau = 0.10; //  l->tau fake rate ZLL : 10%
  double TT_norm  = 0.06; //  normalization TT  :  6%

  double eff_Emb = 0.04;
  double eff_MC  = 0.04;

  for (int iB=1; iB<=nBins; ++iB) {

    float ztt  = ZTT->GetBinContent(iB);
    float ztte = ZTT->GetBinError(iB);
    ztte = TMath::Sqrt(ztte*ztte+ztt*ztt*(ZTT_norm*ZTT_norm+eff_Emb*eff_Emb));
    ZTT->SetBinError(iB,ztte);

    float ewk  = EWK->GetBinContent(iB);
    float ewke = EWK->GetBinError(iB);
    ewke = TMath::Sqrt(ewke*ewke+ewk*ewk*(EWK_norm*EWK_norm+eff_MC*eff_MC));
    EWK->SetBinError(iB,ewke);

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
  EWK->Add(EWK,TT);
  EWK->Add(EWK,ZLL);
  ZTT->Add(ZTT,EWK);
  QCD->Add(QCD,ZTT);

  std::cout << std::endl;
  std::cout << "Model : " << QCD->GetSumOfWeights() << std::endl;
  std::cout << "Data  : " << histData->GetSumOfWeights() << std::endl;
  std::cout << "ratio = " << histData->GetSumOfWeights()/QCD->GetSumOfWeights() << std::endl;
  std::cout << "bbH   = " << bbH->GetSumOfWeights() << std::endl;
  std::cout << std::endl;
  bbH->Scale(100);

  TH1D * bkgdErr = (TH1D*)QCD->Clone("bkgdErr");
  bkgdErr->SetFillStyle(3013);
  bkgdErr->SetFillColor(1);
  bkgdErr->SetMarkerStyle(21);
  bkgdErr->SetMarkerSize(0);
  
  for (int iB=1; iB<=nBins; ++iB) {
    TT->SetBinError(iB,0);
    EWK->SetBinError(iB,0);
    ZLL->SetBinError(iB,0);
    ZTT->SetBinError(iB,0);
    QCD->SetBinError(iB,0);
    bbH->SetBinError(iB,0);
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
  InitHist(EWK,"","",TColor::GetColor("#DE5A6A"),1001);
  InitHist(ZLL,"","",TColor::GetColor("#4496C8"),1001);
  InitHist(ZTT,"","",TColor::GetColor("#FFCC66"),1001);
  bbH->SetLineStyle(1);
  bbH->SetLineColor(2);
  bbH->SetLineWidth(2);

  histData->GetXaxis()->SetTitle(xtitle);
  histData->GetYaxis()->SetTitle(ytitle);
  histData->GetXaxis()->SetRangeUser(31,239);
  histData->GetYaxis()->SetTitleOffset(1.3);
  histData->GetYaxis()->SetTitleSize(0.06);

  QCD->GetXaxis()->SetTitle(xtitle);
  QCD->GetYaxis()->SetTitle(ytitle);
  QCD->GetXaxis()->SetRangeUser(31,239);
  QCD->GetYaxis()->SetTitleOffset(1.3);
  QCD->GetYaxis()->SetTitleSize(0.06);

  float yUpper = QCD->GetMaximum();

  histData->GetYaxis()->SetRangeUser(0,1.2*yUpper);
  QCD->GetYaxis()->SetRangeUser(0,1.2*yUpper);

  if (logY) {
    histData->GetYaxis()->SetRangeUser(yLower,scaleYUpper*yUpper);
    QCD->GetYaxis()->SetRangeUser(yLower,scaleYUpper*yUpper);
  }

  histData->SetMarkerSize(1.4);
  histData->GetXaxis()->SetLabelSize(0);
  histData->GetYaxis()->SetLabelSize(0.06);

  QCD->GetXaxis()->SetLabelSize(0);
  QCD->GetYaxis()->SetLabelSize(0.06);
  
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
  QCD->SetTitle(category+" : "+era);

  QCD->Draw("h");
  ZTT->Draw("sameh");
  EWK->Draw("sameh");
  TT->Draw("sameh");
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
  leg->AddEntry(QCD,"QCD","f");
  leg->AddEntry(ZTT,"Z#rightarrow #tau#tau","f");
  leg->AddEntry(EWK,"electroweak","f");
  leg->AddEntry(TT,"t#bar{t}","f");
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
  TString plotfile=(TString) cmsswBase + "/src/DesyTauAnalyses/BBHTT/test/datacards/plots/";

  canv1->Print(plotfile+channel+"-"+category+"_"+era+".png");
  std::cout << std::endl; 
  std::cout << "+++++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << std::endl;
  delete file;

}

int main(int argc, char * argv[]) {

  if (argc<3) {
    std::cout << "Usage : PlotDatacards [channel] [era] [label=NbtagGt1,Nbtag1,Nbtag0]" << std::endl;
    exit(-1);
  }

  TString channel(argv[1]);
  TString era(argv[2]);
  TString label="";
  if(argc==4)
    label=TString(argv[3]);
    
  string cmsswBase = (getenv("CMSSW_BASE"));

  TString filename=(TString) cmsswBase + "/src/DesyTauAnalyses/BBHTT/test/datacards/datacards";
  if(channel=="em")filename+="EMu_"+era+"/htt_em_bbh.root";
  else filename+="TT_"+era+"/htt_tt_bbh.root";

  bool blindData = false;


  TString xtitle("BDT Score");

  vector<float>bins={0.25,0.4,0.55,0.7,0.85,1.};

  if(label!="")
    label=(TString)"_"+label;

  vector<TString> categories = 
    {
      channel+"_cat0"+label,
      channel+"_cat1"+label,
      channel+"_cat2"+label,
      channel+"_cat3"+label
    };

  std::cout << "processing era " << era << std::endl;
  
  for (auto category : categories) {
    cout << "Run on category: " << category <<endl;
    if (category.Contains("cat0")) 
      blindData = true;
    else
      blindData = false;
    Plot(filename,era,channel,category,bins,xtitle);	
  }
}
  

