#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"

Double_t pol2(Double_t * x, Double_t * par) {

  double t = 100.;
  double r = par[0]+par[1]*x[0]+par[2]*x[0]*x[0];
  if (x[0]>t)
    r = par[0]+par[1]*t+par[2]*t*t;

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
  for (unsigned int i=0; i<bins.size(); ++i)
    xbins[i] = bins[i];
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
void Plot_pt_Closure( bool embedded = true,
		      TString era = "2017",
		      bool OS = false,
		      bool iso2 = true,
		      int selection = 0) {

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  SetStyle();

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
  TString Variable = "pt_2";
  TString xtitle = "pt_2";
  TString ytitle = "Events";
  float yLower =                10;
  float scaleYUpper =           10;

  std::vector<double> bins = {40,45,50,55,60,65,70,75,80,90,100,125,150,200};
  int nbins = bins.size()-1;
  double xbins[100];
  for (unsigned int i=0; i<bins.size(); ++i)
    xbins[i] = bins[i];


  bool plotLegend = true;
  bool legRight = true;
  bool logY = false;
  bool logX = false;
  bool applyNormSys = true;

  TString Selection("trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5");
  if (OS) Selection += "&&os>0.5";
  else Selection += "&&os<0.5";
  TString sel_suffix("_incl");

  if (selection==1) {
    Selection += "&&nbtag==0";    
    sel_suffix = "_btag0";
  }

  if (selection==2) {
    Selection += "&&nbtag==1";
    sel_suffix = "_btag1";
  }

  if (selection==3) {
    Selection += "&&nbtag==2";
    sel_suffix = "_btag2";
  }

  if (selection==4) {
    Selection += "&&nbtag>=1";
    sel_suffix = "_btagGe1";
  }

  if (selection==5) {
    Selection += "&&nbtag>=2";
    sel_suffix = "_btagGe2";
  }

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
  TString FFWeight("ff_nom*");

  TString FF_pt2_2016("((1.40443-0.01440030*pt_2+9.79065e-05*pt_2*pt_2)*(pt_2<=100.)+0.943459*(pt_2>100.))*");
  TString FF_pt2_2017("((1.28039-0.00939058*pt_2+4.91952e-05*pt_2*pt_2)*(pt_2<=100.)+0.833286*(pt_2>100.))*");
  TString FF_pt2_2018("0.94*");
    
  if (era=="2016")
    FFWeight += FF_pt2_2016;
  if (era=="2017")
    FFWeight += FF_pt2_2017;
  if (era=="2018")
    FFWeight += FF_pt2_2018;
  
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

  //  Fakes->Add(Fakes,SingleFake,1.,1.);
  double fakes2 = Fakes->GetSumOfWeights();

  std::cout << "Fakes : " << fakes0 << " vs. " << fakes1 << " vs. " << fakes2 << std::endl;

  TH1D * TT  = nameAttributes["TTL"].hist;
  TH1D * EWK = nameAttributes["VVL"].hist;
  TH1D * ZTT = nameAttributes["ZTT"].hist;
  
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
  std::cout << "ratio : " << histData->GetSumOfWeights()/total << std::endl;

  //  adding normalization systematics
  double ZTT_norm   = 0.04; //  normalization ZTT :  4% (EMBEDDED)
  double EWK_norm   = 0.05; //  normalization EWK :  5%
  double QCD_norm   = 0.12; //  normalization Fakes : 10%
  double TT_norm    = 0.06; //  normalization TT  :  7%

  double eff_Emb = 0.04;
  double eff_MC  = 0.03;

  if (applyNormSys) {
    for (int iB=1; iB<=nbins; ++iB) {

      float ztt  = ZTT->GetBinContent(iB);
      float ztte = ZTT->GetBinError(iB);
      ztte = TMath::Sqrt(ztte*ztte+ztt*ztt*(ZTT_norm*ZTT_norm+eff_Emb*eff_Emb));
      ZTT->SetBinError(iB,ztte);
      
      float ewk  = EWK->GetBinContent(iB);
      float ewke = EWK->GetBinError(iB);
      ewke = TMath::Sqrt(ewke*ewke+ewk*ewk*(EWK_norm*EWK_norm+eff_MC*eff_MC));
      EWK->SetBinError(iB,ewke);
      
      float qcd  = Fakes->GetBinContent(iB);
      float qcde = Fakes->GetBinError(iB);
      qcde = TMath::Sqrt(qcde*qcde+qcd*qcd*QCD_norm*QCD_norm);
      Fakes->SetBinError(iB,qcde);
      //    std::cout << "bin : " << iB << " : " << QCD->GetBinContent(iB) << std::endl;

      float tt  = TT->GetBinContent(iB);
      float tte = TT->GetBinError(iB);
      tte = TMath::Sqrt(tte*tte+tt*tt*(TT_norm*TT_norm+eff_MC*eff_MC));
      //    tte = TMath::Sqrt(tte*tte+tt*tt*TT_norm*TT_norm);
      //      std::cout << iB << "  " << ttweight/tt << std::endl;
      TT->SetBinError(iB,tte);

      /*
	std::cout << iB << " : " 
	<< "qcd = " << qcd << " +/- " << qcde 
	<< "  w = " << w << " +/- " << we 
	<< "  ztt = " << ztt << " +/- " << ztte
	<< "  zll = " << zll << " +/- " << zlle 
	<< "  ewk = " << ewk << " +/- " << ewke << std::endl;
      */
    }
  }

  EWK->Add(EWK,TT);
  ZTT->Add(ZTT,EWK);
  Fakes->Add(Fakes,ZTT);


  TH1D * bkgdErr = (TH1D*)Fakes->Clone("bkgdErr");
  //  TH1
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


  TH1D * ratioH = (TH1D*)histData->Clone("ratioH");
  ratioH->GetYaxis()->SetTitle("Non-closure correction");
  ratioH->GetXaxis()->SetTitle("p_{T}^{#tau2} (GeV)");

  for (int iB=1; iB<=nbins; ++iB) {
    double x1 = histData->GetBinContent(iB);
    double x2 = bkgdErr->GetBinContent(iB);
    double e1 = histData->GetBinError(iB);
    double e2 = bkgdErr->GetBinError(iB);
    double r1 = e1/x1;
    double r2 = e2/x2;
    double ratio = x1/x2;
    double r = TMath::Sqrt(r1*r1+r2*r2);
    double eratio = e1/x2;
    ratioH->SetBinContent(iB,ratio);
    ratioH->SetBinError(iB,eratio);
  }
  ratioH->GetYaxis()->SetRangeUser(0.601,1.399);


  TF1 * fitFunc = new TF1("fitFunc",pol2,40.,200.,3);
  fitFunc->SetLineColor(2);
  fitFunc->SetParameter(0,1.);
  fitFunc->SetParameter(1,0.);
  fitFunc->SetParameter(2,0.);

  for (int iB=1; iB<=nbins; ++iB) {
    double bin_center = ratioH->GetXaxis()->GetBinCenter(iB);
    if (bin_center>80.)
      ratioH->SetBinContent(iB,0.95*ratioH->GetBinContent(iB));
    else if (bin_center>100.&&bin_center<150.)
      ratioH->SetBinContent(iB,0.90*ratioH->GetBinContent(iB));
    else if (bin_center>150.)
      ratioH->SetBinContent(iB,0.68*ratioH->GetBinContent(iB));
  }

  TCanvas * dummy1 = new TCanvas("dummy1","",600,600);
  ratioH->Fit("fitFunc","Q");
  delete dummy1;
  
  TH1D * hint = new TH1D("pt2_"+era,"",160,40.,200.);
  TH1D * hint68 = new TH1D("pt2_"+era+"68","",160,40.,200.);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint68,0.68);
  TH1D * hint_central = (TH1D*)hint->Clone("hint_central");
  for (int iB=1; iB<=160; ++iB)
    hint_central->SetBinError(iB,0.);
  InitHist(hint,"","",kCyan,1001);
  InitHist(hint68,"","",kYellow,1001);
  hint_central->SetLineColor(2);
  hint_central->SetLineWidth(2);
  
  for (int i=0; i<3; ++i) 
    std::cout << "a" << i << " = " << fitFunc->GetParameter(i) << std::endl;
  std::cout << "pt_2 > 100. : " << fitFunc->Eval(120.) << std::endl;

  TCanvas * canv = MakeCanvas("canv1", "", 500, 500);

  ratioH->Draw("e1");
  hint->Draw("e2same");
  hint68->Draw("e2same");
  hint_central->Draw("hsame");
  ratioH->Draw("e1same");

  TLegend * leg= new TLegend(0.20,0.85,0.50,0.90);
  SetLegendStyle(leg);
  leg->SetTextSize(0.044);
  leg->SetHeader("p_{T}^{#tau2} Non-closure");
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
  canv->Print(Variable+suffix+"_nonclosure_"+era+".png");


}
