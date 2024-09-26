#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"

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

TString SpecificCut(TString sample) {
  TString cut("");
  if (sample.Contains("WJetsToLNu")||sample.Contains("DYJetsToLL_M-50"))
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

// triggerOption = 0 (e+mu), 1 (single-lep), 2 (comb)
// selection = 0 (inclusive), 1 (signal region), 2 (ttbar control region)
void Plot_variables( bool embedded = false,
		     TString era = "2018",
		     int selection = 0) {

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  SetStyle();

  // ******************* directory **********
  TString dir = "/nfs/dust/cms/user/rasp/Run/tautau_dnn_UL/"+era;

  // ****************************************
  // ****** Variable to plot ****************
  // ****** and plot settings ***************
  // ****************************************
  TString Variable = "jdeta";
  TString xtitle = "#Delta#eta_{jj}";
  TString ytitle = "normalized";
  int nbins  =                   14;
  float xmin =                    0;
  float xmax =                    7;
  float yLower =                 0;
  float scaleYUpper =           50;

  bool plotLegend = true;
  bool legRight = true;
  bool logY = false;
  bool logX = false;
  bool applyNormSys = true;

  TString Selection("trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5&&os>0.5");

  if (selection==1) {
    Selection += "&&nbtag>=1";    
  }
  if (selection==2) {
    Selection += "&&nbtag>=2";
  }
  if (selection==3) {
    Selection += "&&njets>=1";
  }
  if (selection==4) {
    Selection += "&&njets>=2";
  }

  // ******** end of settings *********

  std::cout << dir << std::endl;

  lumi_13TeV = "2018, 60 fb^{-1}";
  if (era=="2017")
    lumi_13TeV = "2017, 41 fb^{-1}";
  if (era=="2016")
    lumi_13TeV = "2016, 36 fb^{-1}";

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

  TString mcCutsGenB("&&gen_nbjets>0");
  TString mcCutsNonB("&&gen_nbjets==0");
  TString mcCutsSB("&&gen_match_1!=6");
  TString mcCutsSingleFake("&&gen_match_1!=6&&gen_match_2==6");

  TString genCutsSR = CutsSR + mcCutsNotJetFakes; 
  TString genCutsSB = CutsSB + mcCutsSB;
  TString genCutsSingleFake = CutsSR + mcCutsSingleFake;

  std::vector<TString> DataSamples = {"Tau"};
  std::vector<TString> DYSamples = {"DYJets_amcatnlo"};
  std::vector<TString> TTSamples = {"TTbar"};
  std::vector<TString> EWKSamples = {"Diboson","WJets","SingleTop"};
  std::vector<TString> bbHSamples = {"BBHToTauTau_YB2","BBHToTauTau_YT2"};
  std::vector<TString> H125Samples = {"GluGluHToTauTau","VBFHToTauTau"};

  std::vector<TString> names = {"Data","DY","TT","EWK","bbH","Higgs"};

  std::map<TString, std::vector<TString>> nameSamples = {
    {"Data",DataSamples},
    {"DY",DYSamples},
    {"TT",TTSamples},
    {"EWK",EWKSamples},
    {"bbH",bbHSamples},
    {"Higgs",H125Samples},
  };

  std::map<TString, std::vector<TString> > nameCuts = {
    {"Data",  {CutsSR,    CutsSB,     CutsSR}},
    {"DY",    {genCutsSR, genCutsSB,  genCutsSingleFake}},
    {"TT",    {genCutsSR, genCutsSB,  genCutsSingleFake}},
    {"EWK",   {genCutsSR, genCutsSB,  genCutsSingleFake}},
    {"bbH",   {genCutsSR, genCutsSB,  genCutsSingleFake}},
    {"Higgs", {genCutsSR, genCutsSB,  genCutsSingleFake}},
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
      if (file==NULL||file->IsZombie()) {
	std::cout << "file " << dir << "/tt-NOMINAL_ntuple_" << sampleName << "_" << era << ".root not found " << std::endl;
	return;
      }
      TTree * tree = (TTree*)file->Get("TauCheck");

      TH1D * histSample   = new TH1D("hist","",nbins,xmin,xmax);
      TH1D * histSampleSB = new TH1D("histSB","",nbins,xmin,xmax);
      TH1D * histSampleSingleFake = new TH1D("histSingleFake","",nbins,xmin,xmax);

      TString CutsSample   = sampleAttr.cuts   + SpecificCut(sampleName);
      TString CutsSampleSB = sampleAttr.cutsSB + SpecificCut(sampleName);
      TString CutsSampleSingleFake = sampleAttr.cutsSingleFake + SpecificCut(sampleName);
      
      tree->Draw(Variable+">>hist",WeightSample+"("+CutsSample+")");
      tree->Draw(Variable+">>histSB",WeightSampleSB+"("+CutsSampleSB+")");
      tree->Draw(Variable+">>histSingleFake",WeightSampleSingleFake+"("+CutsSampleSingleFake+")");
      std::cout << "   " << sampleName << "  " << "   yield = " << histSample->GetSumOfWeights() << std::endl;
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
  TH1D * SingleFake = nameAttributes["TT"].histSingleFake;

  Fakes->Add(Fakes,nameAttributes["TT"].histSB,1.,-1.);
  Fakes->Add(Fakes,nameAttributes["DY"].histSB,1.,-1.);
  Fakes->Add(Fakes,nameAttributes["EWK"].histSB,1.,-1.);

  SingleFake->Add(SingleFake,nameAttributes["DY"].histSingleFake,1.,1.);
  SingleFake->Add(SingleFake,nameAttributes["EWK"].histSingleFake,1.,1.);


  TH1D * TT = nameAttributes["TT"].hist;
  TH1D * ZTT = nameAttributes["DY"].hist;  
  TH1D * bbH_hist = nameAttributes["bbH"].hist;
  TH1D * H125_hist = nameAttributes["Higgs"].hist;

  InitSignal(Fakes);
  InitSignal(ZTT);
  InitSignal(TT);
  InitSignal(bbH_hist);
  InitSignal(H125_hist);

  Fakes->SetLineColor(kGreen+2);
  ZTT->SetLineColor(kBlack);
  TT->SetLineColor(kMagenta);
  bbH_hist->SetLineColor(kBlue);
  H125_hist->SetLineColor(kRed);

  Fakes->Scale(1./Fakes->GetSumOfWeights());
  ZTT->Scale(1./ZTT->GetSumOfWeights());
  bbH_hist->Scale(1./bbH_hist->GetSumOfWeights());
  H125_hist->Scale(1./H125_hist->GetSumOfWeights());
  TT->Scale(1./TT->GetSumOfWeights());
  
  Fakes->SetLineStyle(1);
  ZTT->SetLineStyle(1);
  TT->SetLineStyle(1);
  bbH_hist->SetLineStyle(1);
  H125_hist->SetLineStyle(1);

  Fakes->SetLineWidth(3);
  ZTT->SetLineWidth(3);
  TT->SetLineWidth(3);
  bbH_hist->SetLineWidth(3);
  H125_hist->SetLineWidth(3);

  int nBins = Fakes->GetNbinsX();
  for (int iB=1; iB<=nBins; ++iB) {
    Fakes->SetBinError(iB,0);
    ZTT->SetBinError(iB,0);
    TT->SetBinError(iB,0);
    bbH_hist->SetBinError(iB,0);
    H125_hist->SetBinError(iB,0);
  }

  float yMax = Fakes->GetMaximum();
  if (ZTT->GetMaximum()>yMax) yMax = ZTT->GetMaximum();
  if (TT->GetMaximum()>yMax) yMax = TT->GetMaximum();
  if (bbH_hist->GetMaximum()>yMax) yMax = bbH_hist->GetMaximum();
  if (H125_hist->GetMaximum()>yMax) yMax = H125_hist->GetMaximum();

  Fakes->GetYaxis()->SetRangeUser(0.,1.2*yMax);
  if (logY) Fakes->GetYaxis()->SetRangeUser(yLower,scaleYUpper*yMax);
  Fakes->GetXaxis()->SetTitle(xtitle);
  Fakes->GetYaxis()->SetTitle(ytitle);
  Fakes->GetYaxis()->SetTitleOffset(1.5);
  Fakes->GetXaxis()->SetTitleOffset(1.2);

  TCanvas * canv1 = MakeCanvas("canv1", "", 600, 600);
  TLegend * leg;

  Fakes->Draw("h");
  ZTT->Draw("hsames");
  //  TT->Draw("hsame");
  bbH_hist->Draw("hsame");
  H125_hist->Draw("hsame");

  if (legRight) leg = new TLegend(0.61,0.60,0.90,0.77);
  else leg = new TLegend(0.20,0.60,0.50,0.77);
  SetLegendStyle(leg);
  leg->SetTextSize(0.04);
  leg->AddEntry(Fakes,"Fakes","l");
  leg->AddEntry(ZTT,"Z#rightarrow #tau#tau","l");
  //  leg->AddEntry(TT,"t#bar{t}","l");
  leg->AddEntry(H125_hist,"H125","l");
  leg->AddEntry(bbH_hist,"bbH","l");
  writeExtraText = true;
  extraText = "Simulation";
  CMS_lumi(canv1,4,33); 

  if (plotLegend) leg->Draw();

  canv1->SetLogy(logY);
  canv1->Update();
  canv1->Print("figures/"+Variable+"_"+era+"_var.png");

}
