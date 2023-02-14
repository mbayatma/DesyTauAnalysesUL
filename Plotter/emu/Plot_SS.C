#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"
TString SpecificCut(TString sample) {
  TString cut("");
  if (sample.Contains("WJetsToLNu")||sample.Contains("DYJetsToLL_M-50"))
    cut = "&&gen_noutgoing==0";
  return cut;

}

// triggerOption = 0 (e+mu), 1 (single-lep), 2 (comb)
// selection = 0 (inclusive), 1 (signal region), 2 (ttbar control region)
void Plot_SS( bool embedded = false,
	      int triggerOption = 0,
	      TString era = "2018",
	      int selection = 2) {

  SetStyle();

  // ******************* directory **********
  TString dir = "/nfs/dust/cms/user/rasp/Run/emu_MSSM/Oct2021/"+era;

  // ****************************************
  // ****** Variable to plot ****************
  // ****** and plot settings ***************
  // ****************************************
  TString Variable = "nbtag";
  TString xtitle = "nbtag";
  TString ytitle = "Events";
  int nBins  =                  5;
  float xmin =               -0.5;
  float xmax =                4.5;
  float yLower =                1;
  float scaleYUpper =          10;

  bool plotLegend = true;
  bool legRight = true;
  bool logY = false;
  bool logX = false;
  bool applyNormSys = true;

  TString Selection("&&iso_1<0.15&&iso_2>0.05&&iso_2<0.40&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.3&&pt_1>15.&&pt_2>15.");
  
  TString trigger_suffix("_emuTrig");
  TString sel_suffix("_incl");
  if (triggerOption==1)
    trigger_suffix = "_singleLepTrig";
  if (triggerOption==2)
    trigger_suffix = "_combTrig";

  if (selection==1) {
    Selection += "&&pzeta>-35";    
    sel_suffix = "_sig";
  }
  if (selection==2) {
    Selection += "&&pzeta<-60&&nbtag>=1";    
    sel_suffix = "_ttbar";
  }
  if (selection==3) {
    Selection += "&&pzeta<-50";    
    sel_suffix = "_noQCD";
  }

  std::map<TString,double> xsecs = xsecs_2016;
  if (era=="2017")
    xsecs = xsecs_2017;
  if (era=="2018")
    xsecs = xsecs_2018;


  TString suffix = "_mc";
  if (embedded) suffix = "_embedded";

  // ******** end of settings *********
  TString outputGraphics("figures");

  std::cout << dir << std::endl;

  lumi_13TeV = "2018, 59.7 fb^{-1}";
  if (era=="2017")
    lumi_13TeV = "2017, 41.5 fb^{-1}";
  if (era=="2016")
    lumi_13TeV = "2016, 35.9 fb^{-1}";

  TString Weight("weightEMu*");
  TString QCDW("qcdweight*");

  TString CutsEMu("((trg_muhigh_elow>0.5&&pt_2>24.0)||(trg_ehigh_mulow>0.5&&pt_1>24.0))");

  TString CutsSingleE = "trg_singleelectron>0.5&&pt_1>33.";
  TString CutsSingleMu = "trg_singlemuon>0.5&&pt_2>25.";

  if (era=="2017") {
    CutsSingleE = "trg_singleelectron>0.5&&pt_1>28.";
    CutsSingleMu = "trg_singlemuon>0.5&&pt_2>25.";
  }
  if (era=="2016") {
    CutsSingleE = "trg_singleelectron>0.5&&pt_1>26.";
    CutsSingleMu = "trg_singlemuon>0.5&&pt_2>23.";
  }

  TString CutsMC = CutsEMu;
  if (triggerOption==1) {
    CutsMC = "(("+CutsSingleMu+")||("+CutsSingleE+"))";
    Weight = "weightSingle*";
  }
  if (triggerOption==2) {
    CutsMC = "((("+CutsSingleMu+")||("+CutsSingleE+"))||"+CutsEMu+")";
    Weight = "weight*";
  }

  CutsMC += Selection;

  TString CutsDataSingleMu = CutsSingleMu + Selection;

  TString CutsDataSingleE = "("+CutsSingleE+")&&!("+CutsSingleMu+")";
  CutsDataSingleE += Selection;

  TString CutsDataEMu = CutsEMu;
  if (triggerOption==2)
    CutsDataEMu = CutsEMu + "&&!("+CutsSingleE+")&&!("+CutsSingleMu+")";
  CutsDataEMu += Selection;

  TString WeightQCD = Weight + QCDW;
  
  TString OS("&&os<0.5");
  TString SS("&&os<0.5&&(gen_match_1==1||gen_match_2==1)");

  TString CutsDataSingleE_OS = CutsDataSingleE + OS;
  TString CutsDataSingleE_SS = CutsDataSingleE + SS;

  TString CutsDataSingleMu_OS = CutsDataSingleMu + OS;
  TString CutsDataSingleMu_SS = CutsDataSingleMu + SS;

  TString CutsDataEMu_OS = CutsDataEMu + OS;
  TString CutsDataEMu_SS = CutsDataEMu + SS;

  TString CutsOS = CutsMC + OS;
  TString CutsSS = CutsMC + SS;
  TString CutsZTT_OS  = CutsOS + TString("&&gen_match_1==3&&gen_match_2==4");
  TString CutsZLL_OS  = CutsOS + TString("&&!(gen_match_1==3&&gen_match_2==4)");
  TString CutsZTT_SS  = CutsSS + TString("&&gen_match_1==3&&gen_match_2==4");
  TString CutsZLL_SS  = CutsSS + TString("&&!(gen_match_1==3&&gen_match_2==4)");

  double lumi = 59740;
  if (era=="2017")
    lumi = 41500;
  if (era=="2016")
    lumi = 35890;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  std::vector<TString> SingleElectron = SingleElectron_2018;
  std::vector<TString> SingleMuon = SingleMuon_2018;
  std::vector<TString> MuonEG = MuonEG_2018;

  std::vector<TString> EmbedSamples = EmbeddedElMu_2018;
  std::vector<TString> DYSamples = DYJets;
  std::vector<TString> WJetsSamples = WJets;
  std::vector<TString> EWKSamples = EWK;
  std::vector<TString> TTSamples = TT_EXCL;

  if (era=="2017") {
    SingleElectron = SingleElectron_2017;
    SingleMuon = SingleMuon_2017;
    MuonEG = MuonEG_2017;
    EmbedSamples = EmbeddedElMu_2017;
  }
  if (era=="2016") {
    SingleElectron = SingleElectron_2016;
    SingleMuon = SingleMuon_2016;
    MuonEG = MuonEG_2016;
    EmbedSamples = EmbeddedElMu_2016;
  }

  struct SampleAttributes {
    TString name;
    std::vector<TString> sampleNames;
    TString cuts;
    TString cutsSS;
    TH1D * hist;
    TH1D * histSS;
  };

  TH1D * dataSingleMuH   = new TH1D("dataSingleMu_os_Hist","",nBins,xmin,xmax);
  TH1D * dataSingleMuSSH = new TH1D("dataSingleMu_ss_Hist","",nBins,xmin,xmax);

  TH1D * dataSingleEH   = new TH1D("dataSingleE_os_Hist","",nBins,xmin,xmax);
  TH1D * dataSingleESSH = new TH1D("dataSingleE_ss_Hist","",nBins,xmin,xmax);

  TH1D * dataEMuH   = new TH1D("dataEMu_os_Hist","",nBins,xmin,xmax);
  TH1D * dataEMuSSH = new TH1D("dataEMu_ss_Hist","",nBins,xmin,xmax);

  TH1D * zttH   = new TH1D("ztt_os_Hist","",nBins,xmin,xmax);
  TH1D * zttSSH = new TH1D("ztt_ss_Hist","",nBins,xmin,xmax);

  TH1D * zllH   = new TH1D("zll_os_Hist","",nBins,xmin,xmax);
  TH1D * zllSSH = new TH1D("zll_ss_Hist","",nBins,xmin,xmax);

  TH1D * wH   = new TH1D("w_os_Hist","",nBins,xmin,xmax);
  TH1D * wSSH = new TH1D("w_ss_Hist","",nBins,xmin,xmax);

  TH1D * ewkH   = new TH1D("ewk_os_Hist","",nBins,xmin,xmax);
  TH1D * ewkSSH = new TH1D("ewk_ss_Hist","",nBins,xmin,xmax);

  TH1D * ttH   = new TH1D("tt_os_Hist","",nBins,xmin,xmax);
  TH1D * ttSSH = new TH1D("tt_ss_Hist","",nBins,xmin,xmax);

  TH1D * ttSysH   = new TH1D("tt_sys_os_Hist","",nBins,xmin,xmax);
  TH1D * ttSysSSH = new TH1D("tt_sys_ss_Hist","",nBins,xmin,xmax);

  // data
  SampleAttributes DataSingleMuAttr;
  DataSingleMuAttr.name = "Data_SingleMu";
  DataSingleMuAttr.sampleNames = SingleMuon;
  DataSingleMuAttr.cuts = CutsDataSingleMu_OS;
  DataSingleMuAttr.cutsSS = CutsDataSingleMu_SS;
  DataSingleMuAttr.hist = dataSingleMuH;
  DataSingleMuAttr.histSS = dataSingleMuSSH;

  SampleAttributes DataSingleEAttr;
  DataSingleEAttr.name = "Data_SingleE";
  DataSingleEAttr.sampleNames = SingleElectron;
  DataSingleEAttr.cuts = CutsDataSingleE_OS;
  DataSingleEAttr.cutsSS = CutsDataSingleE_SS;
  DataSingleEAttr.hist = dataSingleEH;
  DataSingleEAttr.histSS = dataSingleESSH;

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
  if (embedded) {
    ZttAttr.name = "EmbeddedZTT";
    ZttAttr.sampleNames = EmbedSamples;
    ZttAttr.cuts = CutsOS;
    ZttAttr.cutsSS = CutsSS;
  }
  else {
    ZttAttr.name = "ZTT";
    ZttAttr.sampleNames = DYSamples;
    ZttAttr.cuts = CutsZTT_OS;
    ZttAttr.cutsSS = CutsZTT_SS;
  }
  ZttAttr.hist = zttH;
  ZttAttr.histSS = zttSSH;

  // ZLL
  SampleAttributes ZllAttr;
  ZllAttr.name = "ZLL";
  ZllAttr.sampleNames = DYSamples;
  ZllAttr.cuts = CutsZLL_OS;
  ZllAttr.cutsSS = CutsZLL_SS;
  ZllAttr.hist = zllH;
  ZllAttr.histSS = zllSSH;

  // WJets
  SampleAttributes WJetsAttr;
  WJetsAttr.name = "WJets";
  WJetsAttr.sampleNames = WJetsSamples;
  if (embedded) {
    WJetsAttr.cuts = CutsZLL_OS;
    WJetsAttr.cutsSS = CutsZLL_SS;
  }
  else {
    WJetsAttr.cuts = CutsOS;
    WJetsAttr.cutsSS = CutsSS;
  }
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

  // TTBarSys
  SampleAttributes TTSysAttr = TTAttr;
  TTSysAttr.name = "TTBarSys";
  TTSysAttr.sampleNames = TTSamples;
  TTSysAttr.hist = ttSysH;
  TTSysAttr.histSS = ttSysSSH;  

  std::vector<SampleAttributes> AllSamples;  
  AllSamples.push_back(ZttAttr);
  AllSamples.push_back(ZllAttr);
  AllSamples.push_back(WJetsAttr);
  AllSamples.push_back(EWKAttr);
  AllSamples.push_back(TTAttr);
  AllSamples.push_back(DataEMuAttr);
  
  //  Weight = "puweight*mcweight*prefiringweight*zptweight*effweightEMu*";
  //  Weight = "puweight*mcweight*prefiringweight*topptweight*effweightEMu*";
  //  Weight = "trigweightEMu*";
  //  Weight = "weightEMu*";

  TCanvas * dummy = new TCanvas("dummy","",400,400);

  // filling histograms
  for (unsigned int i=0; i<AllSamples.size(); ++i) {
  //  for (unsigned int i=0; i<1; ++i) {
    SampleAttributes sampleAttr = AllSamples.at(i);
    TString name = sampleAttr.name; 
    std::vector<TString> Samples = sampleAttr.sampleNames;
    TString WeightSample = Weight;
    TString WeightSampleQCD = WeightQCD;
    for (unsigned int j=0; j<Samples.size(); ++j) {
      TString sampleName = Samples.at(j);
      TFile * file = new TFile(dir+"/"+sampleName+".root");
      TTree * tree = (TTree*)file->Get("TauCheck");
      //      std::cout << "Processing sample : " 
      //		<< sampleName << "  number of entries in tree : " 
      //		<< tree->GetEntries() << std::endl;      
      TH1D * histWeightsH = (TH1D*)file->Get("nWeightedEvents");
      TString histName = sampleName + "_os";
      TString histNameSS = sampleName + "_ss";
      TH1D * histSample = new TH1D(histName,"",nBins,xmin,xmax);
      TH1D * histSampleSS = new TH1D(histNameSS,"",nBins,xmin,xmax);
      histSample->Sumw2();
      histSampleSS->Sumw2();
      TString CutsSample = sampleAttr.cuts + SpecificCut(sampleName);
      TString CutsSampleSS = sampleAttr.cutsSS + SpecificCut(sampleName);
      tree->Draw(Variable+">>"+histName,WeightSample+"("+CutsSample+")");
      tree->Draw(Variable+">>"+histNameSS,WeightSample+"("+CutsSampleSS+")");
      //      tree->Draw(Variable+">>"+histName,  CutsSample);
      //      tree->Draw(Variable+">>"+histNameSS,CutsSampleSS);
      double norm = 1.0;
      double nevents = 1.0;
      double xsec = 1.0;
      if (name.Contains("Data")||name.Contains("Embed")) {
	norm = 1.;
      }
      else { 
	xsec = xsecs[sampleName];
	nevents = histWeightsH->GetSumOfWeights();
	norm = xsec*lumi/nevents;
      }
            std::cout << "   " << sampleName << "   nEvents = " << nevents << "   xsec = " << xsec << "  entries = " << histSample->GetEntries() << "   yield =" << histSample->GetSumOfWeights() << std::endl;
      sampleAttr.hist->Add(sampleAttr.hist,histSample,1.,norm);
      sampleAttr.histSS->Add(sampleAttr.histSS,histSampleSS,1.,norm);
      //      delete file;
      //      delete histSample;
      //      delete histSampleSS;
      
    }
  }  
  
  TH1D * QCD_SS = new TH1D("QCD_SS","",nBins,xmin,xmax);
  TH1D * QCD    = new TH1D("QCD",   "",nBins,xmin,xmax);

  QCD_SS->Add(QCD_SS,ZttAttr.histSS,1,1);
  QCD_SS->Add(QCD_SS,ZllAttr.histSS,1,1);
  QCD_SS->Add(QCD_SS,WJetsAttr.histSS,1,1);
  QCD_SS->Add(QCD_SS,EWKAttr.histSS,1,1);
  QCD_SS->Add(QCD_SS,TTAttr.histSS,1,1);
  
  QCD->Add(QCD,ZttAttr.hist,1,1);
  QCD->Add(QCD,ZllAttr.hist,1,1);
  QCD->Add(QCD,WJetsAttr.hist,1,1);
  QCD->Add(QCD,EWKAttr.hist,1,1);
  QCD->Add(QCD,TTAttr.hist,1,1);
  
  std::cout << "All    : " << QCD->GetSumOfWeights() << std::endl;
  std::cout << "Only e : " << QCD_SS->GetSumOfWeights() << std::endl;

  std::cout << "W   : " << WJetsAttr.hist->GetSumOfWeights() << std::endl;
  std::cout << "W e : " << WJetsAttr.histSS->GetSumOfWeights() << std::endl;

  std::cout << "Data : " << DataEMuAttr.hist->GetSumOfWeights() << std::endl;

}
