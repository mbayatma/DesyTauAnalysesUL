#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "/nfs/dust/cms/user/rasp/CMSSW/Update/CMSSW_10_2_22/src/DesyTauAnalyses/NTupleMaker/test/emu_MSSM/settings.h"

Double_t FitFunc(Double_t * x, Double_t * par) {

  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];

}

TString SpecificCut(TString sample) {
  TString cut("");
  if (sample.Contains("WJetsToLNu")||sample.Contains("DYJetsToLL_M-50"))
    cut = "&&gen_noutgoing==0";
  return cut;

}

// triggerOption = 0 (e+mu), 1 (single-lep), 2 (comb)
// selection = 0 (njets=0), 1 (nobtag), 2 (btag)
void Fit_QCD( bool embedded = false,
	      int triggerOption = 0,
	      TString era = "2016",
	      double Ymin = 0.5,
	      double Ymax = 3.5,
	      bool correctTTBar = false,
	      int selection = 2) {

  SetStyle();

  TString dir = "/nfs/dust/cms/user/rasp/Run/emu_dnn_UL/"+era;

  bool plotLegend = true;
  bool legRight = true;
  bool logY = false;
  bool logX = false;
  bool applyNormSys = true;

  // ****************************************
  // ****** Variable to plot ****************
  // ****************************************
  TString Variable = "dr_tt";
  TString xtitle = "#DeltaR(e,#mu)";
  TString ytitle = "OS/SS";
  float yLower =               1;
  float scaleYUpper =         10;
  int nBins = 10;
  double binWidth = 0.5;
  double xbins[100];
  for (int i=0; i<=nBins; ++i)
    xbins[i] = 0.5 + double(i)*binWidth;
  double xmin = 0.5;
  double xmax = 5.5;
  //  xbins[11]=250.;
  //  xbins[12]=300.;

  TString Selection("&&m_sv>1.0&&iso_1<0.15&&iso_2>0.2&&iso_2<0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>15.&&pt_2>15.&&pzeta>-35.&&pzeta<20.");
  
  TString trigger_suffix("_emuTrig");
  TString sel_suffix("_njets0");
  if (triggerOption==1)
    trigger_suffix = "_singleLepTrig";
  if (triggerOption==2)
    trigger_suffix = "_combTrig";

  TString NJets("N_{jets}=0");
  if (selection==1) {
    Selection += "&&njets==1";    
    sel_suffix = "_njets1";
    NJets = "N_{jets}=1";
  }
  if (selection==2) {
    Selection += "&&njets>=2";    
    sel_suffix = "_njets2";
    NJets = "N_{jets}>1";
  }

  // ******** end of settings *********

  lumi_13TeV = "2018, 59.7 fb^{-1}";
  if (era=="2017")
    lumi_13TeV = "2017, 41.9 fb^{-1}";
  if (era=="2016")
    lumi_13TeV = "2016, 35.9 fb^{-1}";

  TString Weight("xsec_lumi_weight*");
  TString QCDW("1.0*");

  TString CutsEMu("((trg_muhigh_elow>0.5&&pt_2>24.0)||(trg_ehigh_mulow>0.5&&pt_1>24.0))");
  TString CutsDataEMu = CutsEMu;
  CutsDataEMu += Selection;

  TString WeightQCD = Weight + QCDW;
  
  TString OS("&&os>0.5");
  TString SS("&&os<0.5");

  TString CutsDataEMu_OS = CutsDataEMu + OS;
  TString CutsDataEMu_SS = CutsDataEMu + SS;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  std::vector<TString> MuonEG = {"MuonEG"};
  std::vector<TString> DYSamples = {"DYJets_amcatnlo"};
  std::vector<TString> WJetsSamples = {"WJets"};
  std::vector<TString> EWKSamples = {"SingleTop","Diboson"};
  std::vector<TString> TTSamples = {"TTbar"};

  struct SampleAttributes {
    TString name;
    std::vector<TString> sampleNames;
    TString cuts;
    TString cutsSS;
    TH1D * hist;
    TH1D * histSS;
  };

  TH1D * dataEMuH   = new TH1D("dataEMu_os_Hist","",nBins,xbins);
  TH1D * dataEMuSSH = new TH1D("dataEMu_ss_Hist","",nBins,xbins);

  TH1D * zttH   = new TH1D("ztt_os_Hist","",nBins,xbins);
  TH1D * zttSSH = new TH1D("ztt_ss_Hist","",nBins,xbins);

  TH1D * wH   = new TH1D("w_os_Hist","",nBins,xbins);
  TH1D * wSSH = new TH1D("w_ss_Hist","",nBins,xbins);

  TH1D * ewkH   = new TH1D("ewk_os_Hist","",nBins,xbins);
  TH1D * ewkSSH = new TH1D("ewk_ss_Hist","",nBins,xbins);

  TH1D * ttH   = new TH1D("tt_os_Hist","",nBins,xbins);
  TH1D * ttSSH = new TH1D("tt_ss_Hist","",nBins,xbins);

  SampleAttributes DataEMuAttr;
  DataEMuAttr.name = "Data_EMu";
  DataEMuAttr.sampleNames = MuonEG;
  DataEMuAttr.cuts = CutsDataEMu_OS;
  DataEMuAttr.cutsSS = CutsDataEMu_SS;
  DataEMuAttr.hist = dataEMuH;
  DataEMuAttr.histSS = dataEMuSSH;

  // ZTT
  SampleAttributes ZttAttr;
  ZttAttr.name = "ZTT";
  ZttAttr.sampleNames = DYSamples;
  ZttAttr.cuts = CutsDataEMu_OS;
  ZttAttr.cutsSS = CutsDataEMu_SS;
  ZttAttr.hist = zttH;
  ZttAttr.histSS = zttSSH;

  // WJets
  SampleAttributes WJetsAttr;
  WJetsAttr.name = "WJets";
  WJetsAttr.sampleNames = WJetsSamples;
  WJetsAttr.cuts = CutsDataEMu_OS;
  WJetsAttr.cutsSS = CutsDataEMu_SS;
  WJetsAttr.hist = wH;
  WJetsAttr.histSS = wSSH;

  // EWK
  SampleAttributes EWKAttr = WJetsAttr;
  EWKAttr.name = "EWK";
  EWKAttr.sampleNames = EWKSamples;
  EWKAttr.hist = ewkH;
  EWKAttr.histSS = ewkSSH;

  // TTBar
  SampleAttributes TTAttr = WJetsAttr;
  TTAttr.name = "TTBar";
  TTAttr.sampleNames = TTSamples;
  TTAttr.hist = ttH;
  TTAttr.histSS = ttSSH;  

  std::vector<SampleAttributes> AllSamples;  
  AllSamples.push_back(ZttAttr);
  AllSamples.push_back(WJetsAttr);
  AllSamples.push_back(EWKAttr);
  AllSamples.push_back(TTAttr);
  AllSamples.push_back(DataEMuAttr);

  TCanvas * dummy = new TCanvas("dummy","",400,400);

  // filling histograms
  for (unsigned int i=0; i<AllSamples.size(); ++i) {
    SampleAttributes sampleAttr = AllSamples.at(i);
    TString name = sampleAttr.name; 
    std::vector<TString> Samples = sampleAttr.sampleNames;
    TString WeightSample = Weight;
    TString WeightSampleQCD = WeightQCD;
    for (unsigned int j=0; j<Samples.size(); ++j) {
      TString sampleName = Samples.at(j);
      TFile * file = new TFile(dir+"/em-NOMINAL_ntuple_"+sampleName+"_"+era+".root");
      TTree * tree = (TTree*)file->Get("TauCheck");
      std::cout << "Processing sample : " 
		<< sampleName << "  number of entries in tree : " 
		<< tree->GetEntries() << std::endl;      
      TH1D * histWeightsH = (TH1D*)file->Get("nWeightedEvents");
      TString histName = sampleName + "_os";
      TString histNameSS = sampleName + "_ss";
      TH1D * histSample = new TH1D(histName,"",nBins,xbins);
      TH1D * histSampleSS = new TH1D(histNameSS,"",nBins,xbins);
      histSample->Sumw2();
      histSampleSS->Sumw2();
      TString CutsSample = sampleAttr.cuts + SpecificCut(sampleName);
      TString CutsSampleSS = sampleAttr.cutsSS + SpecificCut(sampleName);
      tree->Draw(Variable+">>"+histName,WeightSample+"("+CutsSample+")");
      tree->Draw(Variable+">>"+histNameSS,WeightSampleQCD+"("+CutsSampleSS+")");
      sampleAttr.hist->Add(sampleAttr.hist,histSample,1.,1.);
      sampleAttr.histSS->Add(sampleAttr.histSS,histSampleSS,1.,1.);
      //      delete file;
      //      delete histSample;
      //      delete histSampleSS;
      
    }
  }  
  
  // *******************
  // adding data samples 
  // *******************
  TH1D * histData = NULL;
  TH1D * QCD_OS = DataEMuAttr.hist;
  TH1D * QCD_SS = DataEMuAttr.histSS;

  QCD_OS->Add(QCD_OS,ZttAttr.hist,1,-1);
  QCD_OS->Add(QCD_OS,WJetsAttr.hist,1,-1);
  QCD_OS->Add(QCD_OS,EWKAttr.hist,1,-1);
  QCD_OS->Add(QCD_OS,TTAttr.hist,1,-1);

  QCD_SS->Add(QCD_SS,ZttAttr.histSS,1,-1);
  QCD_SS->Add(QCD_SS,WJetsAttr.histSS,1,-1);
  QCD_SS->Add(QCD_SS,EWKAttr.histSS,1,-1);
  QCD_SS->Add(QCD_SS,TTAttr.histSS,1,-1);

  delete dummy;
  
  std::cout << std::endl;
  std::cout << "OS    : " << QCD_OS->GetSumOfWeights() << std::endl;
  std::cout << "SS    : " << QCD_SS->GetSumOfWeights() << std::endl;
  std::cout << "ratio = " << QCD_OS->GetSumOfWeights()/QCD_SS->GetSumOfWeights() << std::endl;

  InitSignal(QCD_OS);
  InitSignal(QCD_SS);

  QCD_OS->SetLineStyle(1);
  QCD_OS->SetLineColor(2);
  QCD_OS->SetMarkerSize(0);
  QCD_OS->SetMarkerStyle(0);
  QCD_SS->SetLineStyle(1);
  QCD_SS->SetLineColor(4);
  QCD_SS->SetMarkerSize(0);
  QCD_SS->SetMarkerStyle(0);
  
  QCD_OS->GetXaxis()->SetTitle(xtitle);
  QCD_OS->GetYaxis()->SetTitle(ytitle);
  //  QCD_OS->GetYaxis()->SetTitleOffset(1.3);
  //  QCD_OS->GetYaxis()->SetTitleSize(0.06);

  TH1D * ratioH = new TH1D("ratioH","",nBins,xbins);
  ratioH->GetXaxis()->SetTitle(xtitle);
  ratioH->GetYaxis()->SetTitle(ytitle);
  ratioH->SetMarkerSize(1.3);

  for (int iB=1; iB<=nBins; ++iB) {
    double num = QCD_OS->GetBinContent(iB);
    double numE = QCD_OS->GetBinError(iB);
    double den = QCD_SS->GetBinContent(iB);
    double denE = QCD_SS->GetBinError(iB);
    double ratio = 1.0;
    double ratioE = 1.0;
    if (den>0&&num>0) {
      ratio = num/den;
      ratioE = ratio*TMath::Sqrt((numE/num)*(numE/num)+(denE/den)*(denE/den));
    } 
    ratioH->SetBinContent(iB,ratio);
    ratioH->SetBinError(iB,ratioE);
  }
  //  ratioH->SetBinContent(4,2.33); // 2018 njets=0
  //  ratioH->SetBinContent(4,2.43); // 2017 njets=0

  //  ratioH->SetBinContent(2,2.55); // 2016 njets=1

  //  ratioH->SetBinContent(9,1.33); // 2017 njets=1
  //  ratioH->SetBinError(9,0.33); // 2017 njets=1
  
  //  ratioH->SetBinContent(4,2.01); // 2018 njets=2
  //  ratioH->SetBinContent(6,1.52); // 2018 njets=2
  
  //  ratioH->SetBinContent(9,1.11); // 2017 njets=2
  //  ratioH->SetBinError(9,0.27); // 2017 njets=2
  
  TF1 * fitFunc = new TF1("fitFunc",FitFunc,xmin,xmax,3);
  fitFunc->SetParameter(0,1.);
  fitFunc->SetParameter(1,0.);
  fitFunc->SetParameter(2,0.);

  TCanvas * dummy1 = new TCanvas("dummy1","",500,500);
  ratioH->Fit("fitFunc","Q");
  delete dummy1;

  TH1D * hint = new TH1D("hist95","",150,xmin,xmax);
  TH1D * hint68 = new TH1D("hist68","",150,xmin,xmax);
  hint->SetMarkerSize(0.0);
  hint68->SetMarkerSize(0.0);
  hint->SetMarkerStyle(0);
  hint68->SetMarkerStyle(0);

  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint);
  (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint68,0.68);
  TH1D * hint_central = (TH1D*)hint->Clone("hint_central");
  for (int iB=1; iB<=120; ++iB)
    hint_central->SetBinError(iB,0.);
  InitHist(hint,"","",kCyan,1001);
  InitHist(hint68,"","",kYellow,1001);
  hint_central->SetLineColor(2);
  hint_central->SetLineWidth(2);

  ratioH->GetYaxis()->SetRangeUser(Ymin,Ymax);

  TCanvas * ratioCanv = MakeCanvas("ratioCanv","",600,600);
  ratioH->Draw("e1");
  hint->Draw("e2same");
  hint68->Draw("e2same");
  //  hint_central->Draw("hsame");
  ratioH->Draw("e1same");
  TLegend * leg = new TLegend(0.25,0.15,0.50,0.35);
  SetLegendStyle(leg);
  leg->SetTextSize(0.055);
  leg->SetHeader(NJets);
  writeExtraText = true;
  extraText = "Preliminary";
  CMS_lumi(ratioCanv,4,33); 
  leg->Draw();


  ratioCanv->RedrawAxis();
  ratioCanv->Update();
  ratioCanv->Print("dR_"+era+sel_suffix+".png");

  
}
