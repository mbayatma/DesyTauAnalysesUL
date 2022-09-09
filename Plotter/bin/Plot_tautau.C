#include "DesyTauAnalyses/Plotter/bin/HttStylesNew.cc"
#include "DesyTauAnalyses/Plotter/bin/CMS_lumi.C"
#include "DesyTauAnalyses/Plotter/interface/settings.h"
#include "DesyTauAnalyses/Common/interface/Config.h"

#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1.h"

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

TString SpecificCut(TString era, TString sample) {
  TString cut("");
  if (era=="2016_pre"&&sample.Contains("Embed"))
    cut = "&&run<278769";
  if (era=="2016_post"&&sample.Contains("Embed"))
    cut = "&&run>=278769";  
  if (sample.Contains("WJetsToLNu")||sample.Contains("DYJetsToLL_M-50"))
    //  if (sample.Contains("WJetsToLNu"))
    cut = "&&gen_noutgoing==0";
  return cut;

}

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
  {"pt_2","trailing #tau [GeV]"},
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
  {"dr_tt","#DeltaR(#tau_1,#tau_2)"}
};
int main(int argc, char * argv[]) { 

  if (argc<6) {
    std::cout << "Code should be run with 5 arguments" << std::endl;
    std::cout << "PlotEMu [config_file] [var] [nbins] [xmin] [xmax]" << std::endl;
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

  bool embedded = cfg.get<bool>("Embedded");
  bool isUL = cfg.get<bool>("isUL");
  string era_string = cfg.get<string>("Era");
  TString era(era_string);
  string input_dir = cfg.get<string>("InputDir");
  TString dir(input_dir);
  string output_dir = cfg.get<string>("OutputDir");
  TString outputGraphics(output_dir);
    
  SetStyle();

  std::map<TString,double> xsecs = xsecs_2016;
  if (era=="2017")
    xsecs = xsecs_2017;
  if (era=="2018")
    xsecs = xsecs_2018;

  std::map<TString,double> normScale = {
    {"2016",1.16},
    {"2017",0.94},
    {"2018",1.27}
  };

  float yLower =                10;
  float scaleYUpper =           10;

  float ymin_ratio = cfg.get<float>("YMin");
  float ymax_ratio = cfg.get<float>("YMax");
  bool plotLegend = cfg.get<bool>("PlotLegend");
  bool legRight = true;
  if (Variable=="bcsv_1"||Variable=="bcsv_2") legRight = false;
  bool logY = cfg.get<bool>("logY");
  bool logX = cfg.get<bool>("logX");
  string additional_cut = cfg.get<string>("AdditionalCut");
  TString AdditionalCut(additional_cut);
  bool applyDYScale = cfg.get<bool>("ApplyDYScale");
  string FileSuffix = cfg.get<string>("FileSuffix");
  TString sel_suffix(FileSuffix);
  TString Selection("trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5&&os>0.5&&TMath::Abs(eta_1)<2.1&&TMath::Abs(eta_2)<2.1");

  Selection += AdditionalCut;

  TString suffix = "mc";
  if (embedded) suffix = "embedded";

  lumi_13TeV = "2018, 60 fb^{-1}";
  if (era=="2017")
    lumi_13TeV = "2017, 41 fb^{-1}";
  if (era=="2016")
    lumi_13TeV = "2016, 36 fb^{-1}";

  TString Weight("weight*");
  TString FFWeight("ff_nom*");

  /*
  TString FF_pt2_2016("1.05*(1.0*(pt_2<=120.)+0.80*(pt_2>120.))*");
  TString FF_pt2_2017("1.06*(1.0*(pt_2<=80.)+0.90*(pt_2>80.))*");
  TString FF_pt2_2018("1.06*(1.0*(pt_2<=80.)+0.85*(pt_2>80.&&pt_2<=95.)+0.6*(pt_2>95.))*");

  TString FF_btg_2016("(1.0*(nbtag==0)+0.93*(nbtag==1)+1.00*(nbtag>=2))*");
  TString FF_btg_2017("(1.0*(nbtag<=1)+0.60*(nbtag==2)+0.50*(nbtag>=3))*");
  TString FF_btg_2018("(1.0*(nbtag==0)+0.93*(nbtag==1)+0.52*(nbtag>=2))*");
  */

  /*
  if (embedded) {
    if (era=="2016")
      FFWeight += FF_pt2_2016+FF_btg_2016;
    if (era=="2017")
      FFWeight += FF_pt2_2017+FF_btg_2017;    
    if (era=="2018")
      FFWeight += FF_pt2_2018+FF_btg_2018;    
  }
  */  

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

  TString genCutsSR_L  = CutsSR + mcCutsNotTauTau + mcCutsNotJetFakes;
  TString genCutsSR_TT = CutsSR + mcCutsTauTau;
  TString genCutsSB = CutsSB + mcCutsSB;
  TString genCutsSB_L = CutsSB + mcCutsSB + mcCutsNotTauTau; 
  TString genCutsSingleFake = CutsSR + mcCutsSingleFake;
  TString genCutsSingleFake_L = CutsSR + mcCutsSingleFake + mcCutsNotTauTau;

  double lumi = LUMI[era];

  std::vector<TString> DataSamples = Tau_2018;
  std::vector<TString> EmbedSamples = EmbeddedTauTau_2018;
  std::vector<TString> DYSamples = DYJets;
  std::vector<TString> WJetsSamples = WJets;
  std::vector<TString> EWKSamples = EWK;
  if (isUL) EWKSamples = EWK_UL;
  std::vector<TString> TTSamples = TT_EXCL;
  std::vector<TString> bbHSamples = bbH125;

  if (era=="2017") {
    DataSamples = Tau_2017;
    EmbedSamples = EmbeddedTauTau_2017;
  }
  if (era=="2016") {
    DataSamples = Tau_2016;
    EmbedSamples = EmbeddedTauTau_2016;
  }
  if (era=="2016_pre") {
    DataSamples = Tau_2016_pre;
    EmbedSamples = EmbeddedTauTau_2016_pre;
  }
  if (era=="2016_post") {
    DataSamples = Tau_2016_post;
    EmbedSamples = EmbeddedTauTau_2016_post;
  }

  std::vector<TString> names = {"Data","EMB","VVL","TTL","W","ZTT","ZL","VVT","TTT"};

  std::map<TString, std::vector<TString>> nameSamples = {
    {"Data",DataSamples},
    {"EMB",EmbedSamples},
    {"VVL",EWKSamples},
    {"TTL",TTSamples},
    {"W",WJetsSamples},
    {"ZTT",DYSamples},
    {"ZL",DYSamples},
    {"VVT",EWKSamples},
    {"TTT",TTSamples},
  };

  std::map<TString, std::vector<TString> > nameCuts = {
    {"Data",{CutsSR,      CutsSB,     CutsSR}},
    {"EMB", {genCutsSR_TT,genCutsSB,  genCutsSingleFake}},
    {"VVL", {genCutsSR_L, genCutsSB,  genCutsSingleFake}},
    {"TTL", {genCutsSR_L, genCutsSB,  genCutsSingleFake}},
    {"W",   {genCutsSR_L, genCutsSB,  genCutsSingleFake}},
    {"ZTT", {genCutsSR_TT,genCutsSB,  genCutsSingleFake}},
    {"ZL",  {genCutsSR_L, genCutsSB_L,genCutsSingleFake_L}},
    {"VVT", {genCutsSR_TT,genCutsSB,  genCutsSingleFake}},
    {"TTT", {genCutsSR_TT,genCutsSB,  genCutsSingleFake}},
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

    double kfactor = 1.0;
    for (unsigned int j=0; j<Samples.size(); ++j) {

      TString sampleName = Samples.at(j);

      TFile * file = new TFile(dir+"/"+sampleName+".root");
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

      TString CutsSample   = sampleAttr.cuts   + SpecificCut(era,sampleName);
      TString CutsSampleSB = sampleAttr.cutsSB + SpecificCut(era,sampleName);
      TString CutsSampleSingleFake = sampleAttr.cutsSingleFake + SpecificCut(era,sampleName);
      
      tree->Draw(Variable+">>hist",WeightSample+"("+CutsSample+")");
      tree->Draw(Variable+">>histSB",WeightSampleSB+"("+CutsSampleSB+")");
      tree->Draw(Variable+">>histSingleFake",WeightSampleSingleFake+"("+CutsSampleSingleFake+")");

      double norm = 1.0;
      double nevents = 1.0;
      double xsec = 1.0;
      if (name.Contains("Data")) {
	norm = 1.;
      }
      else if (name.Contains("EMB")) {
	norm = 1.;
      }
      else { 
	xsec = xsecs[sampleName];
	nevents = histWeightsH->GetSumOfWeights();
	norm = xsec*lumi*kfactor/nevents;

      }
      std::cout << "   " << sampleName << "   nEvents = " << nevents << "   xsec = " << xsec << "  entries = " << histSample->GetEntries() << "   yield = " << histSample->GetSumOfWeights() << std::endl;
      sampleAttr.hist->Add(sampleAttr.hist,histSample,1.,norm);
      sampleAttr.histSB->Add(sampleAttr.histSB,histSampleSB,1.,norm);
      sampleAttr.histSingleFake->Add(sampleAttr.histSingleFake,histSampleSingleFake,1.,norm);
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

  double fakes0 = Fakes->GetSumOfWeights();

  if (embedded) {
    Fakes->Add(Fakes,nameAttributes["EMB"].histSB,1.,-1.);
    Fakes->Add(Fakes,nameAttributes["ZL"].histSB,1.,-1.);
    SingleFake->Add(SingleFake,nameAttributes["EMB"].histSingleFake,1.,1.);
    SingleFake->Add(SingleFake,nameAttributes["ZL"].histSingleFake,1.,1.);
  }
  else {
    Fakes->Add(Fakes,nameAttributes["ZTT"].histSB,1.,-1.);
    SingleFake->Add(SingleFake,nameAttributes["ZTT"].histSingleFake,1.,1.);
  }

  Fakes->Add(Fakes,nameAttributes["TTL"].histSB,1.,-1.);
  Fakes->Add(Fakes,nameAttributes["VVL"].histSB,1.,-1.);
  Fakes->Add(Fakes,nameAttributes["W"].histSB,1.,-1.);

  double fakes1 = Fakes->GetSumOfWeights();

  SingleFake->Add(SingleFake,nameAttributes["VVL"].histSingleFake,1.,1.);
  SingleFake->Add(SingleFake,nameAttributes["W"].histSingleFake,1.,1.);

  Fakes->Add(Fakes,SingleFake,1.,1.);
  double fakes2 = Fakes->GetSumOfWeights();

  std::cout << "Fakes : " << fakes0 << " vs. " << fakes1 << " vs. " << fakes2 << std::endl;

  TH1D * TT  = nameAttributes["TTL"].hist;
  TH1D * EWK = nameAttributes["VVL"].hist;
  TH1D * ZTT = nameAttributes["ZTT"].hist;

  TH1D * Ztt = (TH1D*)ZTT->Clone("Ztt");

  TH1D * EMB = nameAttributes["EMB"].hist;
  TH1D * TTT  = nameAttributes["TTT"].hist;
  TH1D * EWKT = nameAttributes["VVT"].hist;
  
  double embNorm = EMB->GetSumOfWeights()-TTT->GetSumOfWeights()-EWKT->GetSumOfWeights();
  double zttNorm = ZTT->GetSumOfWeights();
  double normScaleX = embNorm/zttNorm;
  
  if (applyDYScale)
    //    ZTT->Scale(normScale[era]);
    ZTT->Scale(normScaleX);

  if (embedded) {
    ZTT = nameAttributes["EMB"].hist;
    //    ZTT->Add(ZTT,nameAttributes["ZL"].hist,1.,1.);
  }
  else {
    TT->Add(TT,nameAttributes["TTT"].hist,1.,1.);
    EWK->Add(EWK,nameAttributes["VVT"].hist,1.,1.);
  }
  EWK->Add(EWK,nameAttributes["ZL"].hist,1.,1.);

  std::cout << "Top   : " << TT->GetSumOfWeights()  << std::endl;
  std::cout << "EWK   : " << EWK->GetSumOfWeights() << std::endl;
  std::cout << "ZTT   : " << ZTT->GetSumOfWeights() << std::endl;
  std::cout << "Fakes : " << Fakes->GetSumOfWeights() << std::endl;
  double total = TT->GetSumOfWeights() + EWK->GetSumOfWeights() + ZTT->GetSumOfWeights() + Fakes->GetSumOfWeights();
  std::cout << "Total : " << total << std::endl;
  std::cout << "Data  : " << histData->GetSumOfWeights() << std::endl;

  //  adding normalization systematics
  double ZTT_norm   = 0.03; //  normalization ZTT :  4% (EMBEDDED)
  double EWK_norm   = 0.05; //  normalization EWK :  5%
  double QCD_norm   = 0.07; //  normalization Fakes : 10%
  double TT_norm    = 0.00; //  normalization TT  :  7%

  double eff_Emb = 0.03;
  double eff_MC  = 0.03;

  bool applyNormSys = cfg.get<bool>("ApplySystematics");
  if (applyNormSys) {
    for (int iB=1; iB<=nbins; ++iB) {

      float ztt  = ZTT->GetBinContent(iB);
      float ztte = ZTT->GetBinError(iB);
      ztte = TMath::Sqrt(ztte*ztte+ztt*ztt*(ZTT_norm*ZTT_norm+eff_Emb*eff_Emb));
      if (!embedded) ZTT->SetBinError(iB,0.5*ztte);
      
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


    }
  }

  //  for (int i=1; i<=6; ++i) 
  //    Fakes->SetBinContent(i,0.9*Fakes->GetBinContent(i));

  std::cout << std::endl;
  std::cout << "normZTT = " << normScaleX << std::endl;
  std::cout << std::endl;

  EWK->Add(EWK,TT);
  ZTT->Add(ZTT,EWK);
  Fakes->Add(Fakes,ZTT);

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
  }
  InitData(histData);

  InitHist(Fakes,"","",TColor::GetColor("#c6f74a"),1001);
  InitHist(TT,"","",TColor::GetColor("#9999CC"),1001);
  InitHist(EWK,"","",TColor::GetColor("#DE5A6A"),1001);
  InitHist(ZTT,"","",TColor::GetColor("#FFCC66"),1001);

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

  histData->Draw("e1");
  Fakes->Draw("sameh");
  ZTT->Draw("sameh");
  EWK->Draw("sameh");
  //  TT->Draw("sameh");
  histData->Draw("e1same");
  bkgdErr->Draw("e2same");
  histData->Draw("e1same");
  float chi2 = 0;
  for (int iB=1; iB<=nbins; ++iB) {
    float xData = histData->GetBinContent(iB);
    float xMC = ZTT->GetBinContent(iB);
    if (xMC>1e-1) {
      float diff2 = (xData-xMC)*(xData-xMC);
      chi2 += diff2/xMC;
    }
  }
  std::cout << std::endl;
  std::cout << "Chi2 = " << chi2 << std::endl;
  std::cout << std::endl;

  TLegend * leg;
  if (legRight) leg = new TLegend(0.61,0.47,0.90,0.77);
  else leg = new TLegend(0.20,0.60,0.50,0.90);
  SetLegendStyle(leg);
  leg->SetTextSize(0.044);
  leg->AddEntry(histData,"Data","lp");
  leg->AddEntry(Fakes,"Fakes","f");
  //  if (embedded) 
  leg->AddEntry(ZTT,"genuine #tau#tau","f");
    //  else 
    //    leg->AddEntry(ZTT,"Z#rightarrow#tau#tau","f");
  leg->AddEntry(EWK,"rest","f");
  //  leg->AddEntry(TT,"t#bar{t}","f");
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
  canv1->Print(outputGraphics+"/"+Variable+"_"+era+"_"+suffix+"_"+sel_suffix+suffixLOGY+".png");

}
