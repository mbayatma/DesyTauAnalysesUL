#include "DesyTauAnalyses/Plotter/bin/HttStylesNew.cc"
#include "DesyTauAnalyses/Plotter/bin/CMS_lumi.C"
#include "DesyTauAnalyses/Plotter/interface/settings.h"
#include "DesyTauAnalyses/Common/interface/Config.h"

#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1.h"
#include <iostream>
#include <iomanip>

struct SampleAttributes {
  TString name;
  std::vector<TString> sampleNames;
  TString cuts;
  TString cutsSB;
  TString cutsSingleFake;
  TString weight;
  TString weightSB;
  TString weightSingleFake;
  TH1D * hist;
  TH1D * histSB;
  TH1D * histSingleFake;
};


SampleAttributes CreateSampleAttributes(TString name, 
					std::vector<TString> sampleNames,
					TString cuts, 
					TString cutsSB,
					TString cutsSingleFake,
					TString weight,
					TString weightSB,
					TString weightSingleFake,
					int nbins,
					double xmin,
					double xmax) {
  SampleAttributes attr;
  attr.name = name;
  attr.sampleNames = sampleNames;
  attr.cuts = cuts;
  attr.cutsSB = cutsSB;
  attr.cutsSingleFake = cutsSingleFake;
  attr.weight = weight;
  attr.weightSB = weightSB;
  attr.weightSingleFake = weightSingleFake;
  attr.hist = new TH1D(name,"",nbins,xmin,xmax);
  attr.histSB = new TH1D(name+"_SB","",nbins,xmin,xmax);
  attr.histSingleFake = new TH1D(name+"_SingleFake","",nbins,xmin,xmax);
  return attr;
    
}

using namespace std;

map<TString, TString> xtitles = {
  {"pzeta","D_{#zeta} [GeV]"},
  {"pt_1","leading #tau p_{T} [GeV]"},
  {"pt_2","trailing #tau p_{T} [GeV]"},
  {"eta_1","leading #tau #eta"},
  {"eta_2","trailing #tau #eta"},
  {"nbtag","N_{btag}"},
  {"njets","N_{jets}"},
  {"puppimet","puppi E_{T}^{mis} [GeV]"},
  {"m_sv","m_{#tau#tau} [GeV]"},
  {"m_vis","m_{vis} [GeV]"},
  {"mjj","m_{jj} [GeV]"},
  {"jdeta","#eta_{jj} [GeV]"},
  {"jpt_1","leading jet p_{T} [GeV]"},
  {"jpt_2","trailing jet p_{T} [GeV]"},
  {"bpt_1","leading b-jet p_{T} [GeV]"},
  {"bpt_2","trailing b-jet p_{T} [GeV]"},
  {"bcsv_1","b-tag discriminant 1"},
  {"bcsv_1","b-tag discriminant 2"},
  {"dr_tt","#DeltaR(#tau_{1},#tau_{2})"},
  {"pt_tt","p_{T}(#tau#tau) [GeV]"},
  {"pred_class_proba","D_{BDT}"}
};
int main(int argc, char * argv[]) { 

  TH1::SetDefaultSumw2(true);
  TH2::SetDefaultSumw2(true);

  if (argc<6) {
    std::cout << "Code should be run with 5 arguments" << std::endl;
    std::cout << "PlotTauTau [config_file] [var] [nbins] [xmin] [xmax]" << std::endl;
  }

  Config cfg(argv[1]);
  TString Variable(argv[2]);
  TString xtitle("");
  if (xtitles.find(Variable)!=xtitles.end())
    xtitle = xtitles[Variable];
  else
    xtitle = Variable;
  TString ytitle = "Events";
  int nbins  = atoi(argv[3]);
  float xmin = atof(argv[4]);
  float xmax = atof(argv[5]);

  string era_string = cfg.get<string>("Era");
  TString era(era_string);
  string input_dir = cfg.get<string>("InputDir");
  TString dir(input_dir);
  string output_dir = cfg.get<string>("OutputDir");
  TString outputGraphics(output_dir);
    
  SetStyle();

  float yLower =                0.5;
  float scaleYUpper =           10;

  float ymin_ratio = cfg.get<float>("YMin");
  float ymax_ratio = cfg.get<float>("YMax");
  bool plotLegend = cfg.get<bool>("PlotLegend");
  bool legRight = true;
  if (Variable=="bcsv_1"||Variable=="bcsv_2") legRight = false;
  bool logY = cfg.get<bool>("logY");
  bool logX = cfg.get<bool>("logX");
  bool blindData = cfg.get<bool>("BlindData");
  float xmin_blind = cfg.get<float>("xmin_blind");
  float xmax_blind = cfg.get<float>("xmax_blind");
  string additional_cut = cfg.get<string>("AdditionalCut");
  TString AdditionalCut(additional_cut);
  string FileSuffix = cfg.get<string>("FileSuffix");
  float signalScale = cfg.get<float>("SignalScale");
  TString sel_suffix(FileSuffix);
  TString Selection("trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5&&TMath::Abs(eta_1)<2.1&&TMath::Abs(eta_2)<2.1&&m_sv>30&&m_vis>30");

  Selection += AdditionalCut;

  lumi_13TeV = "2018, 59.8 fb^{-1}";
  if (era=="2017")
    lumi_13TeV = "2017, 41.5 fb^{-1}";
  if (era=="2016")
    lumi_13TeV = "2016, 36.3 fb^{-1}";
  if (era=="2016_pre")
    lumi_13TeV = "2016 preVFP, 19.5 fb^{-1}";
  if (era=="2016_post")
    lumi_13TeV = "2016 postVFP, 16.8 fb^{-1}";

  TString Weight("xsec_lumi_weight*");
  TString FFWeight("ff_total*");

  TString WeightQCD = Weight + FFWeight;
  
  TString CutsSR("&&byMediumDeepTau2017v2p1VSjet_1>0.5&&byMediumDeepTau2017v2p1VSjet_2>0.5");
  TString CutsSB("&&byMediumDeepTau2017v2p1VSjet_1<0.5&&byVVVLooseDeepTau2017v2p1VSjet_1>0.5&&byMediumDeepTau2017v2p1VSjet_2>0.5");

  CutsSR = Selection + CutsSR;
  CutsSB = Selection + CutsSB;
  TString mcCutsTauTau("&&gen_match_1==5&&gen_match_2==5");
  TString mcCutsNotTauTau("&&!(gen_match_1==5&&gen_match_2==5)");
  TString mcCutsNotJetFakes("&&gen_match_1<=5&&gen_match_2<=5");

  TString mcCutsSB("&&gen_match_1!=6");
  TString mcCutsSingleFake("&&gen_match_1!=6&&gen_match_2==6");
  TString mcCutsB("&&gen_nbjets_cut>0");
  TString mcCutsNoB("&&gen_nbjets_cut==0");

  TString genCutsSR_B = CutsSR + mcCutsB;
  TString genCutsSR_noB = CutsSR + mcCutsNoB;
  TString genCutsSR_L  = CutsSR + mcCutsNotTauTau + mcCutsNotJetFakes;
  TString genCutsSR_TT = CutsSR + mcCutsTauTau;
  TString genCutsSB = CutsSB + mcCutsSB;
  TString genCutsSB_L = CutsSB + mcCutsSB + mcCutsNotTauTau; 
  TString genCutsSingleFake = CutsSR + mcCutsSingleFake;
  TString genCutsSingleFake_L = CutsSR + mcCutsSingleFake + mcCutsNotTauTau;

  std::vector<TString> DataSamples = {"Tau"};
  std::vector<TString> DYSamples = {"DYJets_amcatnlo"};
  std::vector<TString> WJetsSamples = {"WJets"};
  std::vector<TString> EWKSamples = {"Diboson","SingleTop"};
  std::vector<TString> TTSamples = {"TTbar"};
  std::vector<TString> HiggsSamples = {"GluGluHToTauTau","VBFHToTauTau","WHToTauTau","ZHToTauTau"};
  std::vector<TString> bbHSamples = {"BBHToTauTau_YT2","BBHToTauTau_YB2","BBHToTauTau_YBYT"};
  std::vector<TString> bbHSamples_noBB = {"BBHToTauTau_YB2","BBHToTauTau_YBYT"};

  std::vector<TString> names = {"Data","VVL","TTL","W","ZTT","ZL","VVT","TTT","Higgs","bbH","bbH_bb","bbH_nobb"};
  
  std::map<TString, std::vector<TString>> nameSamples = {
    {"Data",DataSamples},
    {"VVL",EWKSamples},
    {"TTL",TTSamples},
    {"W",WJetsSamples},
    {"ZTT",DYSamples},
    {"ZL",DYSamples},
    {"VVT",EWKSamples},
    {"TTT",TTSamples},
    {"Higgs",HiggsSamples},
    {"bbH",bbHSamples},
    {"bbH_bb",bbHSamples},
    {"bbH_nobb",bbHSamples_noBB}
  };
  
  std::map<TString, std::vector<TString> > nameCuts = {
    {"Data",    {CutsSR,      CutsSB,     CutsSR}},
    {"VVL",     {genCutsSR_L, genCutsSB,  genCutsSingleFake}},
    {"TTL",     {genCutsSR_L, genCutsSB,  genCutsSingleFake}},
    {"W",       {genCutsSR_L, genCutsSB,  genCutsSingleFake}},
    {"ZTT",     {genCutsSR_TT,genCutsSB,  genCutsSingleFake}},
    {"ZL",      {genCutsSR_L, genCutsSB_L,genCutsSingleFake_L}},
    {"VVT",     {genCutsSR_TT,genCutsSB,  genCutsSingleFake}},
    {"TTT",     {genCutsSR_TT,genCutsSB,  genCutsSingleFake}},
    {"Higgs",   {genCutsSR_TT,genCutsSB,  genCutsSingleFake}},
    {"bbH",     {CutsSR,      genCutsSB,  genCutsSingleFake}},
    {"bbH_bb",  {genCutsSR_B, genCutsSB,  genCutsSingleFake}},
    {"bbH_nobb",{genCutsSR_noB, genCutsSB,  genCutsSingleFake}},
  };

  std::map<TString, SampleAttributes> nameAttributes;
  for (auto name : names) {
    std::vector<TString> nSamples = nameSamples[name];
    std::vector<TString> nCuts = nameCuts[name];
    SampleAttributes attr = CreateSampleAttributes(name,
						   nSamples,
						   nCuts[0],
						   nCuts[1],
						   nCuts[2],
						   Weight,
						   WeightQCD,
						   Weight,
						   nbins,
						   xmin,
						   xmax);
    nameAttributes[name] = attr;
  }

  TCanvas * dummy = new TCanvas("dummy","",400,400);

  // filling histograms
  for (auto name : names) {

    SampleAttributes sampleAttr = nameAttributes[name];
    std::vector<TString> Samples = sampleAttr.sampleNames;
    TString WeightSample = sampleAttr.weight;
    TString WeightSampleSB = sampleAttr.weightSB;
    TString WeightSampleSingleFake = sampleAttr.weightSingleFake;

    for (unsigned int j=0; j<Samples.size(); ++j) {

      TString sampleName = Samples.at(j);

      TFile * file = new TFile(dir+"/tt-NOMINAL_ntuple_"+sampleName+"_"+era+".root");
      if (file==0||file->IsZombie()) {
	std::cout << "file " << dir << "/" << sampleName << ".root does not exist" << std::endl;
	std::cout << "quitting..." << std::endl;
	exit(-1);
      }
      TTree * tree = (TTree*)file->Get("TauCheck");
      TH1D * histWeightsH = (TH1D*)file->Get("nWeightedEvents");

      TH1D * histSample   = new TH1D("hist","",nbins,xmin,xmax);
      TH1D * histSampleSB = new TH1D("histSB","",nbins,xmin,xmax);
      TH1D * histSampleSingleFake = new TH1D("histSingleFake","",nbins,xmin,xmax);

      TString CutsSample   = sampleAttr.cuts;
      TString CutsSampleSB = sampleAttr.cutsSB;
      TString CutsSampleSingleFake = sampleAttr.cutsSingleFake;
      
      tree->Draw(Variable+">>hist",WeightSample+"("+CutsSample+")");
      tree->Draw(Variable+">>histSB",WeightSampleSB+"("+CutsSampleSB+")");
      tree->Draw(Variable+">>histSingleFake",WeightSampleSingleFake+"("+CutsSampleSingleFake+")");
      double yield = histSample->GetSumOfWeights();
      std::cout << setw(5) << name << setw(30) << sampleName << " : " << setw(6) << yield << std::endl; 
      sampleAttr.hist->Add(sampleAttr.hist,histSample,1.,1.);
      sampleAttr.histSB->Add(sampleAttr.histSB,histSampleSB,1.,1.);
      sampleAttr.histSingleFake->Add(sampleAttr.histSingleFake,histSampleSingleFake,1.,1.);
      delete histSample;
      delete histSampleSB;
      delete histSampleSingleFake;
      delete file;
    }
  }  
  delete dummy;
 
  // *******************
  // adding data samples 
  // *******************
  TH1D * histData = nameAttributes["Data"].hist;
  TH1D * Fakes = nameAttributes["Data"].histSB;
  TH1D * SingleFake = nameAttributes["TTL"].histSingleFake;

  Fakes->Add(Fakes,nameAttributes["ZTT"].histSB,1.,-1.);
  Fakes->Add(Fakes,nameAttributes["TTL"].histSB,1.,-1.);
  Fakes->Add(Fakes,nameAttributes["VVL"].histSB,1.,-1.);
  Fakes->Add(Fakes,nameAttributes["W"].histSB,1.,-1.);
  double fakes0 = Fakes->GetSumOfWeights();


  SingleFake->Add(SingleFake,nameAttributes["ZTT"].histSingleFake,1.,1.);
  SingleFake->Add(SingleFake,nameAttributes["VVL"].histSingleFake,1.,1.);
  SingleFake->Add(SingleFake,nameAttributes["W"].histSingleFake,1.,1.);
  double fakes1 = SingleFake->GetSumOfWeights();

  Fakes->Add(Fakes,SingleFake,1.,1.);
  double fakes2 = Fakes->GetSumOfWeights();  

  std::cout << "Fakes : " << fakes0 << "(QCD) + " << fakes1 << "(WJets) = " << fakes2 << std::endl;

  double scaleFF = histData->GetSumOfWeights()/Fakes->GetSumOfWeights();
  Fakes->Scale(scaleFF);

  TH1D * TT  = nameAttributes["TTL"].hist;
  TH1D * EWK = nameAttributes["VVL"].hist;
  TH1D * ZTT = nameAttributes["ZTT"].hist;
  TH1D * Higgs = nameAttributes["Higgs"].hist;
  TH1D * bbH = nameAttributes["bbH"].hist;
  TH1D * bbH_bb = nameAttributes["bbH_bb"].hist;
  TH1D * bbH_nobb = nameAttributes["bbH_nobb"].hist;

  //  ZTT->Scale(1./1.27); // 2016
  //  ZTT->Scale(1./1.22); // 2017
  //  ZTT->Scale(1./1.13); // 2018

  TT->Add(TT,nameAttributes["TTT"].hist,1.,1.);
  EWK->Add(EWK,nameAttributes["VVT"].hist,1.,1.);
  EWK->Add(EWK,nameAttributes["ZL"].hist,1.,1.);

  std::cout << std::endl;
  std::cout << "Variable -> " << Variable << std::endl;
  std::cout << "Top   : " << TT->GetSumOfWeights()  << std::endl;
  std::cout << "EWK   : " << EWK->GetSumOfWeights() << std::endl;
  std::cout << "ZTT   : " << ZTT->GetSumOfWeights() << std::endl;
  std::cout << "Fakes : " << Fakes->GetSumOfWeights() << std::endl;
  std::cout << "Higgs : " << Higgs->GetSumOfWeights() << std::endl;
  double total = TT->GetSumOfWeights() + EWK->GetSumOfWeights() + ZTT->GetSumOfWeights() + Fakes->GetSumOfWeights() + Higgs->GetSumOfWeights();
  std::cout << "Total : " << total << std::endl;
  std::cout << "Data  : " << histData->GetSumOfWeights() << std::endl;
  std::cout << std::endl;
  std::cout << "bbH       : " << bbH->GetSumOfWeights() << std::endl;
  std::cout << std::endl;
  double bbH_total =  bbH_bb->GetSumOfWeights() + bbH_nobb->GetSumOfWeights();
  std::cout << "bbH_bb    : " << bbH_bb->GetSumOfWeights() << std::endl;
  std::cout << "bbH_nobb  : " << bbH_nobb->GetSumOfWeights() << std::endl;
  std::cout << "bbH_total : " << bbH_total << std::endl;

  //  adding normalization systematics
  double ZTT_norm   = 0.05; //  normalization ZTT   :  5%
  double QCD_norm   = 0.08; //  normalization Fakes :  7%
  double TT_norm    = 0.06; //  normalization TT    :  6%
  double EWK_norm   = 0.05; //  normalization EWK   :  5%
  double eff_MC  = 0.04; // efficiency MC

  bool applyNormSys = cfg.get<bool>("ApplySystematics");
  if (applyNormSys) {
    for (int iB=1; iB<=nbins; ++iB) {

      float ztt  = ZTT->GetBinContent(iB);
      float ztte = ZTT->GetBinError(iB);
      ztte = TMath::Sqrt(ztte*ztte+ztt*ztt*(ZTT_norm*ZTT_norm+eff_MC*eff_MC));
      ZTT->SetBinError(iB,ztte);
      
      float ewk  = EWK->GetBinContent(iB);
      float ewke = EWK->GetBinError(iB);
      ewke = TMath::Sqrt(ewke*ewke+ewk*ewk*(EWK_norm*EWK_norm+eff_MC*eff_MC));
      EWK->SetBinError(iB,ewke);
      
      float qcd  = Fakes->GetBinContent(iB);
      float qcde = Fakes->GetBinError(iB);
      qcde = TMath::Sqrt(qcde*qcde+qcd*qcd*QCD_norm*QCD_norm);
      Fakes->SetBinError(iB,qcde);

      float tt  = TT->GetBinContent(iB);
      float tte = TT->GetBinError(iB);
      tte = TMath::Sqrt(tte*tte+tt*tt*(TT_norm*TT_norm+eff_MC*eff_MC));
      TT->SetBinError(iB,tte);
      float total = tt+ewk+ztt+qcd;
      //      if (total>0)
      //	std::cout << iB << " : " << ztte/total << std::endl;
    }
  }
  /*
  if (Variable=="bpt_1") {
    if (era=="2016") {
      Fakes->SetBinContent(8,0.8*Fakes->GetBinContent(8));
      ZTT->SetBinContent(8,0.8*ZTT->GetBinContent(8));
    }
    if (era=="2017") {
      Fakes->SetBinContent(6,0.9*Fakes->GetBinContent(6));
      ZTT->SetBinContent(6,0.9*ZTT->GetBinContent(6));
      Fakes->SetBinContent(8,0.9*Fakes->GetBinContent(8));
      ZTT->SetBinContent(8,0.9*ZTT->GetBinContent(8));
    }
    if (era=="2018") {
      Fakes->SetBinContent(8,1.11*Fakes->GetBinContent(8));
      ZTT->SetBinContent(8,1.11*ZTT->GetBinContent(8));
    }
  }

  if (Variable=="njets") {
    if (era=="2016") {
      Fakes->SetBinContent(5,1.15*Fakes->GetBinContent(5));
      Fakes->SetBinContent(6,1.27*Fakes->GetBinContent(6));
      Fakes->SetBinContent(7,1.23*Fakes->GetBinContent(7));
      Fakes->SetBinContent(8,1.40*Fakes->GetBinContent(8));
      ZTT->SetBinContent(5,1.15*ZTT->GetBinContent(5));
      ZTT->SetBinContent(6,1.27*ZTT->GetBinContent(6));
      ZTT->SetBinContent(7,1.23*ZTT->GetBinContent(7));
      ZTT->SetBinContent(8,1.40*ZTT->GetBinContent(8));
    }
    if (era=="2017") {
      Fakes->SetBinContent(5,1.15*Fakes->GetBinContent(5));
      Fakes->SetBinContent(7,1.15*Fakes->GetBinContent(7));
      ZTT->SetBinContent(5,1.15*ZTT->GetBinContent(5));
      ZTT->SetBinContent(7,1.15*ZTT->GetBinContent(7));
    }
    if (era=="2018") {
      Fakes->SetBinContent(6,1.1*Fakes->GetBinContent(6));
      Fakes->SetBinContent(7,1.2*Fakes->GetBinContent(7));
      ZTT->SetBinContent(6,1.1*ZTT->GetBinContent(6));
      ZTT->SetBinContent(7,1.2*ZTT->GetBinContent(7));
    }
  }
  */
  if (Variable=="njets") {
    if (era=="2016") {
      Fakes->SetBinContent(3,0.95*Fakes->GetBinContent(3));
      Fakes->SetBinContent(4,0.90*Fakes->GetBinContent(4));
      Fakes->SetBinContent(5,0.95*Fakes->GetBinContent(5));
      Fakes->SetBinContent(6,0.80*Fakes->GetBinContent(6));
    }
    if (era=="2017") {
      Fakes->SetBinContent(2,0.98*Fakes->GetBinContent(2));
      Fakes->SetBinContent(5,0.91*Fakes->GetBinContent(5));
    }
    if (era=="2018") {
      Fakes->SetBinContent(3,0.95*Fakes->GetBinContent(3));
      Fakes->SetBinContent(4,0.95*Fakes->GetBinContent(4));
      Fakes->SetBinContent(6,0.87*Fakes->GetBinContent(6));
    }
  }

  if (Variable=="nbtag") {
    if (era=="2016") {
      Fakes->SetBinContent(2,0.90*Fakes->GetBinContent(2));
      Fakes->SetBinContent(4,0.70*Fakes->GetBinContent(4));
    }
    if (era=="2018") {
      Fakes->SetBinContent(2,0.95*Fakes->GetBinContent(2));
      Fakes->SetBinContent(3,0.85*Fakes->GetBinContent(3));
    }
  }

  EWK->Add(EWK,TT);
  ZTT->Add(ZTT,EWK);
  Fakes->Add(Fakes,ZTT);
  //  ZTT->Add(ZTT,Fakes);
  //  Higgs->Add(Higgs,ZTT);

  TH1D * bkgdErr = (TH1D*)Fakes->Clone("bkgdErr");
  bkgdErr->SetFillStyle(3013);
  bkgdErr->SetFillColor(1);
  bkgdErr->SetMarkerStyle(21);
  bkgdErr->SetMarkerSize(0);
  
  for (int iB=1; iB<=nbins; ++iB) {
    TT->SetBinError(iB,0);
    EWK->SetBinError(iB,0);
    Fakes->SetBinError(iB,0);
    ZTT->SetBinError(iB,0);
    Higgs->SetBinError(iB,0);
  }
  InitData(histData);

  InitHist(Higgs,"","",TColor::GetColor("#FFCCFF"),1001);
  InitHist(Fakes,"","",TColor::GetColor("#c6f74a"),1001);
  InitHist(TT,"","",TColor::GetColor("#9999CC"),1001);
  InitHist(EWK,"","",TColor::GetColor("#DE5A6A"),1001);
  InitHist(ZTT,"","",TColor::GetColor("#FFCC66"),1001);
  InitSignal(bbH);
  bbH->SetLineColor(4);
  bbH->SetLineStyle(1);
  bbH->SetLineWidth(2);
  bbH->SetMarkerStyle(0);
  bbH->SetMarkerSize(0);
  bbH->Scale(signalScale);

  histData->GetXaxis()->SetTitle(xtitle);
  histData->GetYaxis()->SetTitle(ytitle);
  histData->GetYaxis()->SetTitleOffset(1.3);
  histData->GetYaxis()->SetTitleSize(0.06);
  float yUpper = histData->GetMaximum();
  if (ZTT->GetMaximum()>yUpper)
    yUpper = ZTT->GetMaximum();
  histData->GetYaxis()->SetRangeUser(0,1.2*yUpper);
  ZTT->GetYaxis()->SetRangeUser(0,1.2*ZTT->GetMaximum());
  if (logY) {
    histData->GetYaxis()->SetRangeUser(yLower,scaleYUpper*yUpper);
    ZTT->GetYaxis()->SetRangeUser(yLower,scaleYUpper*yUpper);
  }

  histData->SetMarkerSize(1.4);
  histData->GetXaxis()->SetLabelSize(0);
  histData->GetYaxis()->SetLabelSize(0.06);

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

  if (blindData) {
    for (int iB=1; iB<=nbins; ++iB) {
      float xcenter = histData->GetXaxis()->GetBinCenter(iB);
      if (xcenter>xmin_blind&&xcenter<xmax_blind) {
	histData->SetBinContent(iB,1e+7);
	histData->SetBinError(iB,0.);
      }
    }
  }

  histData->Draw("e1");
  //  Higgs->Draw("sameh");
  Fakes->Draw("sameh");
  ZTT->Draw("sameh");
  EWK->Draw("sameh");
  TT->Draw("sameh");
  histData->Draw("e1same");
  bkgdErr->Draw("e2same");
  //  bbH->Draw("sameh");
  histData->Draw("e1same");
  float chi2 = 0;
  for (int iB=1; iB<=nbins; ++iB) {
    float xData = histData->GetBinContent(iB);
    float xMC = bkgdErr->GetBinContent(iB);
    float eMC = bkgdErr->GetBinError(iB);
    if (xMC>1e-1) {
      float diff2 = (xData-xMC)*(xData-xMC);
      chi2 += diff2/(xMC+eMC*eMC);
    }
  }
  double ndof = nbins - 1;
  double prob = TMath::Prob(chi2,ndof); 
  std::cout << std::endl;
  std::cout << "Chi2/ndof = " << chi2 << "/" << ndof << " -> p-value = " << prob << std::endl;
  std::cout << std::endl;

  TLegend * leg;
  if (legRight) leg = new TLegend(0.61,0.47,0.90,0.77);
  else leg = new TLegend(0.20,0.60,0.50,0.90);
  SetLegendStyle(leg);
  leg->SetTextSize(0.044);
  leg->AddEntry(histData,"Data","lp");
  leg->AddEntry(Fakes,"Fakes","f");
  //  leg->AddEntry(Higgs,"H(125)","f");
  leg->AddEntry(ZTT,"Z#rightarrow#tau#tau","f");
  leg->AddEntry(EWK,"electroweak","f");
  leg->AddEntry(TT,"t#bar{t}","f");
  //  leg->AddEntry(bbH,"Hbb","l");
  if (plotLegend) leg->Draw();
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
  ratioH->GetYaxis()->SetRangeUser(ymin_ratio,ymax_ratio);
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

  for (int iB=1; iB<=nbins; ++iB) {
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

  if (blindData) {
    for (int iB=1; iB<=nbins; ++iB) {
      float xcenter = ratioH->GetXaxis()->GetBinCenter(iB);
      if (xcenter>xmin_blind&&xcenter<xmax_blind) {
	ratioH->SetBinContent(iB,1e+7);
	ratioH->SetBinError(iB,0.);
      }
    }
  }
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
  TString suffixLOGY("");
  if (logY) suffixLOGY = "_logY";
  canv1->Print(outputGraphics+"/"+Variable+"_"+era+"_"+sel_suffix+suffixLOGY+".png");

}
