#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"

Double_t pol2(Double_t * x, Double_t * par) {

  double r = 
    par[0]+
    par[1]*x[0]+
    par[2]*x[0]*x[0]+
    par[3]*x[0]*x[0]*x[0];
    par[4]*x[0]*x[0]*x[0]*x[0];

  return r;

}


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
					std::vector<double> bins) {
  int nbins = bins.size()-1;
  double xbins[100];
  for (unsigned int i=0; i<bins.size(); ++i) {
    xbins[i] = bins[i];
  }
  SampleAttributes attr;
  attr.name = name;
  attr.sampleNames = sampleNames;
  attr.cuts = cuts;
  attr.cutsSB = cutsSB;
  attr.cutsSingleFake = cutsSingleFake;
  attr.weight = weight;
  attr.weightSB = weightSB;
  attr.weightSingleFake = weightSingleFake;
  attr.hist = new TH1D(name,"",nbins,xbins);
  attr.histSB = new TH1D(name+"_SB","",nbins,xbins);
  attr.histSingleFake = new TH1D(name+"_SingleFake","",nbins,xbins);
  return attr;
    
}

// selection = 0 (inclusive), 1 (signal region), 2 (ttbar control region)
void Plot_FR_met( bool embedded = true,
		  TString era = "2016",
		  bool OS = false,
		  bool iso2 = true,
		  TString njets = "1",
		  TString nbtags = "",
		  TString dm = "") {

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  double mult = 1.0/0.139855;
  //  double mult = 1/0.19;
  //  double mult = 1.0/0.174616;
  //  double mult = 1.0/0.191154;

  SetStyle();

  //  std::vector<double> bins = {40,50,60,70,80,90,100,125,150,200};
  //  std::vector<double> bins = {0.5,0.7,0.9,1.1,1.3,
  //			      1.5,1.7,1.9,2.1,2.3,
  //			      2.5,2.7,2.9,3.1,3.3,
  //
  std::vector<double> bins;
  for (unsigned int i = 0; i<15; ++i) 
    bins.push_back(-1.5+0.2*double(i));

  double xbins[100];
  int nbins = bins.size()-1;
  for (unsigned int i=0; i<bins.size();++i)
    xbins[i]=bins[i];

  std::map<TString,double> xsecs = xsecs_2016;
  if (era=="2017")
    xsecs = xsecs_2017;
  if (era=="2018")
    xsecs = xsecs_2018;

  // ******************* directory **********
  TString dir = "/nfs/dust/cms/user/rasp/Run/tautau/"+era;

  // ****************************************
  // ****** Variable to plot ****************
  // ****** and plot settings ***************
  // ****************************************
  TString Variable = "puppimet*(TMath::Cos(puppimetphi)*TMath::Cos(phi_1)+TMath::Sin(puppimetphi)*TMath::Sin(phi_1))/pt_1";
  TString var_to_save = "met_qcd";
  TString xtitle = "MET_{QCD}";
  TString ytitle = "Events";
  float xmin =                 1.5;
  float xmax =                -1.5;
  float yLower =                10;
  float scaleYUpper =           10;

  bool plotLegend = true;
  bool legRight = true;
  bool logY = false;
  bool logX = false;
  bool applyNormSys = true;

  TString Selection("trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5");
  if (OS) Selection += "&&os>0.5";
  else Selection += "&&os<0.5";

  // njets ->
  if (njets=="0"||njets=="1")
    Selection += "&&njets=="+njets;
  if (njets=="2")
    Selection += "&&njets>="+njets;

  // ddecay mode ->
  if (dm=="0"||dm=="1"||dm=="10"||dm=="11")
    Selection += "&&tau_decay_mode_1=="+dm;

  // nbtags ->
  if (nbtags=="0")
    Selection += "&&nbtag=="+nbtags;
  if (nbtags=="1")
    Selection += "&&nbtag=="+nbtags;
  if (nbtags=="2")
    Selection += "&&nbtag>="+nbtags;

  TString suffix = "_mc";
  if (embedded) suffix = "_embedded";

  // ******** end of settings *********
  TString outputGraphics("figures");

  std::cout << dir << std::endl;

  lumi_13TeV = "2018, 60 fb^{-1}";
  if (era=="2017")
    lumi_13TeV = "2017, 41 fb^{-1}";
  if (era=="2016")
    lumi_13TeV = "2016, 36 fb^{-1}";

  TString Weight("weight*");
  TString FFWeight("1.0*");

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

  double lumi = 59740;
  if (era=="2017")
    lumi = 41500;
  if (era=="2016")
    lumi = 35890;

  std::vector<TString> DataSamples = Tau_2018;
  std::vector<TString> EmbedSamples = EmbeddedTauTau_2018;
  std::vector<TString> DYSamples = DYJets;
  std::vector<TString> WJetsSamples = WJets;
  std::vector<TString> EWKSamples = EWK;
  std::vector<TString> TTSamples = TT;
  std::vector<TString> bbHSamples = ggH125;

  if (era=="2017") {
    DataSamples = Tau_2017;
    EmbedSamples = EmbeddedTauTau_2017;
  }
  if (era=="2016") {
    DataSamples = Tau_2016;
    EmbedSamples = EmbeddedTauTau_2016;
  }

  std::vector<TString> names = {"Data","EMB","VVL","TTL","W","ZTT","ZL"};

  std::map<TString, std::vector<TString>> nameSamples = {
    {"Data",DataSamples},
    {"EMB",EmbedSamples},
    {"VVL",EWKSamples},
    {"TTL",TTSamples},
    {"W",WJetsSamples},
    {"ZTT",DYSamples},
    {"ZL",DYSamples},
  };

  std::map<TString, std::vector<TString> > nameCuts = {
    {"Data",{CutsSR,         CutsSB,     CutsSR}},
    {"EMB", {genCutsSB,   genCutsSB,  genCutsSingleFake}},
    {"VVL", {genCutsSB,   genCutsSB,  genCutsSingleFake}},
    {"TTL", {genCutsSB,   genCutsSB,  genCutsSingleFake}},
    {"W",   {genCutsSB,   genCutsSB,  genCutsSingleFake}},
    {"ZTT", {genCutsSB,   genCutsSB,  genCutsSingleFake}},
    {"ZL",  {genCutsSB_L, genCutsSB_L,genCutsSingleFake_L}},
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
						   bins);
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

      TFile * file = new TFile(dir+"/"+sampleName+".root");
      TTree * tree = (TTree*)file->Get("TauCheck");
      TH1D * histWeightsH = (TH1D*)file->Get("nWeightedEvents");

      TH1D * histSample   = new TH1D("hist","",nbins,xbins);
      TH1D * histSampleSB = new TH1D("histSB","",nbins,xbins);
      TH1D * histSampleSingleFake = new TH1D("histSingleFake","",nbins,xbins);

      TString CutsSample   = sampleAttr.cuts   + SpecificCut(sampleName);
      TString CutsSampleSB = sampleAttr.cutsSB + SpecificCut(sampleName);
      TString CutsSampleSingleFake = sampleAttr.cutsSingleFake + SpecificCut(sampleName);
      
      tree->Draw(Variable+">>hist",WeightSample+"("+CutsSample+")");
      tree->Draw(Variable+">>histSB",WeightSampleSB+"("+CutsSampleSB+")");
      tree->Draw(Variable+">>histSingleFake",WeightSampleSingleFake+"("+CutsSampleSingleFake+")");

      double norm = 1.0;
      double nevents = 1.0;
      double xsec = 1.0;
      if (name.Contains("Data")||name.Contains("EMB")) {
	norm = 1.;
      }
      else { 
	xsec = xsecs[sampleName];
	nevents = histWeightsH->GetSumOfWeights();
	norm = xsec*lumi/nevents;
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
  
  InitData(histData);

  if (embedded) {
    histData->Add(histData,nameAttributes["EMB"].hist,1.,-1.);
    histData->Add(histData,nameAttributes["ZL"].hist,1.,-1.);
    Fakes->Add(Fakes,nameAttributes["EMB"].histSB,1.,-1.);
    Fakes->Add(Fakes,nameAttributes["ZL"].histSB,1.,-1.);
    SingleFake->Add(SingleFake,nameAttributes["EMB"].histSingleFake,1.,1.);
    SingleFake->Add(SingleFake,nameAttributes["ZL"].histSingleFake,1.,1.);
  }
  else {
    histData->Add(histData,nameAttributes["ZTT"].hist,1.,-1.);
    Fakes->Add(Fakes,nameAttributes["ZTT"].histSB,1.,-1.);
    SingleFake->Add(SingleFake,nameAttributes["ZTT"].histSingleFake,1.,1.);
  }

  Fakes->Add(Fakes,nameAttributes["TTL"].histSB,1.,-1.);
  Fakes->Add(Fakes,nameAttributes["VVL"].histSB,1.,-1.);
  Fakes->Add(Fakes,nameAttributes["W"].histSB,1.,-1.);

  histData->Add(histData,nameAttributes["TTL"].hist,1.,-1.);
  histData->Add(histData,nameAttributes["VVL"].hist,1.,-1.);
  histData->Add(histData,nameAttributes["W"].hist,1.,-1.);

  SingleFake->Add(SingleFake,nameAttributes["VVL"].histSingleFake,1.,1.);
  SingleFake->Add(SingleFake,nameAttributes["W"].histSingleFake,1.,1.);

  TH1D * ratioH = (TH1D*)histData->Clone("ratioH");
  ratioH->GetYaxis()->SetTitle("Correction");
  ratioH->GetXaxis()->SetTitle(xtitle);

  double average = 0;
  for (int iB=1; iB<=nbins; ++iB) {
    double x1 = histData->GetBinContent(iB);
    double x2 = Fakes->GetBinContent(iB);
    double e1 = histData->GetBinError(iB);
    double e2 = Fakes->GetBinError(iB);
    double r1 = e1/x1;
    double r2 = e2/x2;
    double r = TMath::Sqrt(r1*r1+r2*r2);
    double rat  = x1/x2;
    double erat = rat*r;
    average += rat;
    ratioH->SetBinContent(iB,mult*rat);
    ratioH->SetBinError(iB,mult*erat);
  }
  average = average/double(nbins);
  std::cout << "average = " << average << std::endl;

  ratioH->GetYaxis()->SetRangeUser(0,2*ratioH->GetMaximum());
  TCanvas * dummy1 = new TCanvas("dummy","",400,400);

  TF1 * fitFunc = new TF1("fitFunc",pol2,-1.5,1.5,5);
  fitFunc->SetLineColor(2);
  fitFunc->SetParameter(0,1.);
  fitFunc->SetParameter(1,0.);
  fitFunc->SetParameter(2,0.);
  fitFunc->SetParameter(3,0.);
  fitFunc->SetParameter(4,0.);
  
  ratioH->Fit("fitFunc","Q");
  delete dummy1;
    
  TH1D * hint = new TH1D("ff_"+era,"",150,-1.5,1.5);   
  TH1D * hint_68 = new TH1D("ff_"+era+"_68","",150,-1.5,1.5);   
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint_68,0.68);
  TH1D * hint_central = (TH1D*)hint->Clone("hint_central");
  for (int iB=1; iB<=160; ++iB)
    hint_central->SetBinError(iB,0.);
  InitHist(hint,"","",kCyan,1001);
  InitHist(hint_68,"","",kYellow,1001);
  hint_central->SetLineColor(2);
  hint_central->SetLineWidth(2);

  double update = ratioH->GetBinContent(nbins) + 0.5*(hint->GetBinContent(158)-ratioH->GetBinContent(nbins)) ;

  //  for (int i=0; i<3; ++i) 
  //    std::cout << "a" << i << " = " << fitFunc->GetParameter(i) << std::endl;
  //  std::cout << "pt_2 > 100. : " << fitFunc->Eval(160.) << std::endl;

  //  TFile * fileOutput = new TFile("ff_nbtags_"+nbtags+"_os_"+era+".root","recreate");
  //  fileOutput->cd("");
  //  ratioH->Write("ratioH");
  //  fileOutput->Close();


  TCanvas * canv = MakeCanvas("canv1", "", 500, 500);

  ratioH->Draw("e1");
  hint->Draw("e2same");
  hint_68->Draw("e2same");
  hint_central->Draw("hsame");
  ratioH->Draw("e1same");

  TLegend * leg= new TLegend(0.20,0.85,0.50,0.90);
  SetLegendStyle(leg);
  leg->SetTextSize(0.044);
  leg->SetHeader("njets"+njets);
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

  canv->Print(var_to_save+suffix+"_njets"+njets+"_dm"+dm+"_ss_iso2_"+era+".png");

}
