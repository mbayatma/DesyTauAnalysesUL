#include "DesyTauAnalyses/Plotter/bin/HttStylesNew.cc"
#include "DesyTauAnalyses/Plotter/bin/CMS_lumi.C"
#include "DesyTauAnalyses/Plotter/interface/settings.h"
#include "DesyTauAnalyses/Common/interface/Config.h"

#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1.h"

#include <map>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

map<TString, TString> xtitles = {
  {"pzeta","D_{#zeta} [GeV]"},
  {"pt_1","electron p_{T} [GeV]"},
  {"pt_2","muon p_{T} [GeV]"},
  {"eta_1","electron #eta"},
  {"eta_2","muon #eta"},
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
  {"dr_tt","#DeltaR(e,#mu)"},
  {"pt_tt","p_{T}(#tau#tau) [GeV]"}
};

// triggerOption = 0 (e+mu), 1 (single-lep), 2 (comb)
// selection = 0 (inclusive), 1 (signal region), 2 (high dzeta), 3 (medium dzeta), 4 (low dzeta)
int main(int argc, char * argv[]) { 

  if (argc<6) {
    std::cout << "Code should be run with 5 arguments" << std::endl;
    std::cout << "PlotEMu [config_file] [var] [nbins] [xmin] [xmax]" << std::endl;
    exit(-1);
  }

  Config cfg(argv[1]);
  TString Variable(argv[2]);
  TString xtitle("");
  if (xtitles.find(Variable)!=xtitles.end())
    xtitle = xtitles[Variable];
  else
    xtitle = Variable;
  TString ytitle = "Events";
  int nBins  = atoi(argv[3]);
  float xmin = atof(argv[4]);
  float xmax = atof(argv[5]);
  float yLower = 0;

  bool embedded = cfg.get<bool>("Embedded");
  string era_string = cfg.get<string>("Era");
  TString era(era_string);
  string input_dir = cfg.get<string>("InputDir");
  TString dir(input_dir);
  string output_dir = cfg.get<string>("OutputDir");
  TString outputGraphics(output_dir);
    
  std::cout << std::endl;
  std::cout << "dir    = " << dir << std::endl;
  std::cout << std::endl;
  std::cout << "output = " << outputGraphics << std::endl;
  std::cout << std::endl;

  SetStyle();

  // ****************************************
  // ****** Variable to plot ****************
  // ****** and plot settings ***************
  // ****************************************
  float scaleYUpper = 10;
  float ymin_ratio = cfg.get<float>("YMin");
  float ymax_ratio = cfg.get<float>("YMax");

  bool plotLegend = cfg.get<bool>("PlotLegend");
  bool legRight = true;
  if (Variable=="pzeta"||Variable=="bcsv_1"||Variable=="bcsv_2") 
    legRight = false;
  bool logY = cfg.get<bool>("logY");
  bool logX = cfg.get<bool>("logX");
  string additional_cut = cfg.get<string>("AdditionalCut");
  TString AdditionalCut(additional_cut);
  bool isBTag = cfg.get<bool>("ApplyBTagQCDScale");
  bool isDYamcatnlo = cfg.get<bool>("IsDYamcatnlo");
  TString Selection("&&iso_1<0.15&&iso_2<0.20&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.3&&pt_1>15.&&pt_2>15.");
  Selection += AdditionalCut; // additional cut, for example nbtag>=1
  string SelSuffix = cfg.get<string>("FileSuffix");
  TString sel_suffix(SelSuffix);
  double scaleQCD = 1.0;  
  std::map<TString,double> scaleQCD_btag = 
    {
      {"2016",0.71},
      {"2016_pre",0.71},
      {"2016_post",0.71},
      {"2017",0.69},
      {"2018",0.67},
    };
  if (isBTag) 
    scaleQCD = scaleQCD_btag[era];
 
  TString suffix = "mc";
  if (embedded) suffix = "embedded";

  // ******** end of settings *********

  //  std::cout << dir << std::endl;

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
  TString QCDW("qcdweight*");
  TString WeightQCD = Weight + QCDW;

  TString CutsEMu("((trg_muhigh_elow>0.5&&pt_2>24.0)||(trg_ehigh_mulow>0.5&&pt_1>24.0))");
  TString CutsMC = CutsEMu;
  TString CutsDataEMu = CutsEMu;
  CutsMC += Selection;
  CutsDataEMu += Selection;
  
  TString OS("&&os>0.5");
  TString SS("&&os<0.5");

  TString CutsDataEMu_OS = CutsDataEMu + OS;
  TString CutsDataEMu_SS = CutsDataEMu + SS;

  TString CutsOS = CutsMC + OS;
  TString CutsSS = CutsMC + SS;
  TString CutsZTT_OS  = CutsOS + TString("&&gen_match_1==3&&gen_match_2==4");
  TString CutsZLL_OS  = CutsOS + TString("&&!(gen_match_1==3&&gen_match_2==4)");
  TString CutsZTT_SS  = CutsSS + TString("&&gen_match_1==3&&gen_match_2==4");
  TString CutsZLL_SS  = CutsSS + TString("&&!(gen_match_1==3&&gen_match_2==4)");

  double lumi = LUMI[era];

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  TString dnn_prefix("em-NOMINAL_ntuple_");

  std::vector<TString> MuonEG = {"MuonEG"};
  std::vector<TString> EmbedSamples = {"EmbeddedElMu"};
  std::vector<TString> DYSamples = {"DYJets"};
  std::vector<TString> WJetsSamples = {"WJets"};
  std::vector<TString> EWKSamples = {"Diboson","SingleTop"};
  std::vector<TString> TTSamples = {"TTbar"};
  std::vector<TString> HiggsSamples = {"GluGluHToTauTau","VBFHToTauTau"};

  struct SampleAttributes {
    TString name;
    std::vector<TString> sampleNames;
    TString Weight;
    TString WeightQCD;
    TString cuts;
    TString cutsSS;
    TH1D * hist;
    TH1D * histSS;
  };

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

  TH1D * higgsH   = new TH1D("higgs_os_Hist","",nBins,xmin,xmax);
  TH1D * higgsSSH = new TH1D("higgs_ss_Hist","",nBins,xmin,xmax);

  TH1D * ttH   = new TH1D("tt_os_Hist","",nBins,xmin,xmax);
  TH1D * ttSSH = new TH1D("tt_ss_Hist","",nBins,xmin,xmax);

  TH1D * ttSysH   = new TH1D("tt_sys_os_Hist","",nBins,xmin,xmax);
  TH1D * ttSysSSH = new TH1D("tt_sys_ss_Hist","",nBins,xmin,xmax);

  // data
  SampleAttributes DataEMuAttr;
  DataEMuAttr.name = "Data_EMu";
  DataEMuAttr.Weight = "1.0*";
  DataEMuAttr.WeightQCD = "qcdweight*";
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
    ZttAttr.Weight = Weight;
    ZttAttr.WeightQCD = WeightQCD;
    ZttAttr.sampleNames = EmbedSamples;
    ZttAttr.cuts = CutsOS;
    ZttAttr.cutsSS = CutsSS;
  }
  else {
    ZttAttr.name = "ZTT";
    ZttAttr.sampleNames = DYSamples;
    ZttAttr.Weight = Weight;
    ZttAttr.WeightQCD = WeightQCD;
    ZttAttr.cuts = CutsZTT_OS;
    ZttAttr.cutsSS = CutsZTT_SS;
  }
  ZttAttr.hist = zttH;
  ZttAttr.histSS = zttSSH;

  // ZLL
  SampleAttributes ZllAttr;
  ZllAttr.name = "ZLL";
  ZllAttr.sampleNames = DYSamples;
  ZllAttr.Weight = Weight;
  ZllAttr.WeightQCD = WeightQCD;
  ZllAttr.cuts = CutsZLL_OS;
  ZllAttr.cutsSS = CutsZLL_SS;
  ZllAttr.hist = zllH;
  ZllAttr.histSS = zllSSH;

  // H125
  SampleAttributes HiggsAttr;
  HiggsAttr.sampleNames = HiggsSamples;
  HiggsAttr.cuts = CutsOS;
  HiggsAttr.Weight = Weight;
  HiggsAttr.WeightQCD = WeightQCD;
  HiggsAttr.cutsSS = CutsSS;
  HiggsAttr.hist = higgsH;
  HiggsAttr.histSS = higgsSSH;

  // WJets
  SampleAttributes WJetsAttr;
  WJetsAttr.name = "WJets";
  WJetsAttr.sampleNames = WJetsSamples; 
  WJetsAttr.Weight = Weight;
  WJetsAttr.WeightQCD = WeightQCD;
  WJetsAttr.cuts = CutsOS;
  WJetsAttr.cutsSS = CutsSS;
  WJetsAttr.hist = wH;
  WJetsAttr.histSS = wSSH;

  // EWK
  SampleAttributes EWKAttr;
  EWKAttr.name = "EWK";
  EWKAttr.sampleNames = EWKSamples;
  if (embedded) {
    EWKAttr.cuts = CutsZLL_OS;
    EWKAttr.cutsSS = CutsZLL_SS;
  }
  else {
    EWKAttr.cuts = CutsOS;
    EWKAttr.cutsSS = CutsSS;
  }
  EWKAttr.Weight = Weight;
  EWKAttr.WeightQCD = WeightQCD;
  EWKAttr.hist = ewkH;
  EWKAttr.histSS = ewkSSH;

  // TTBar
  SampleAttributes TTAttr = EWKAttr;
  TTAttr.name = "TTBar";
  TTAttr.sampleNames = TTSamples;
  TTAttr.Weight = Weight;
  TTAttr.WeightQCD = WeightQCD;
  TTAttr.hist = ttH;
  TTAttr.histSS = ttSSH;  

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
    SampleAttributes sampleAttr = AllSamples.at(i);
    TString name = sampleAttr.name; 
    std::vector<TString> Samples = sampleAttr.sampleNames;
    TString WeightSample = sampleAttr.Weight;
    TString WeightSampleQCD = sampleAttr.WeightQCD;
    for (unsigned int j=0; j<Samples.size(); ++j) {
      TString sampleName = Samples.at(j);
      TFile * file = new TFile(dir+"/"+dnn_prefix+sampleName+"_"+era+".root");
      if (file==0||file->IsZombie()) {
	std::cout << "file " << dir << "/" << sampleName << ".root does not exist" << std::endl;
	std::cout << "quitting..." << std::endl;
	exit(-1);
      }
      TTree * tree = (TTree*)file->Get("TauCheck");
      //      std::cout << "Processing sample : " 
      //		<< sampleName << "  number of entries in tree : " 
      //		<< tree->GetEntries() << std::endl;      
      //      TH1D * histWeightsH = (TH1D*)file->Get("nWeightedEvents");
      TString histName = sampleName + "_os";
      TString histNameSS = sampleName + "_ss";
      TH1D * histSample = new TH1D(histName,"",nBins,xmin,xmax);
      TH1D * histSampleSS = new TH1D(histNameSS,"",nBins,xmin,xmax);
      histSample->Sumw2();
      histSampleSS->Sumw2();
      TString CutsSample = sampleAttr.cuts;// + SpecificCut(era,sampleName);
      TString CutsSampleSS = sampleAttr.cutsSS;// + SpecificCut(era,sampleName);
      tree->Draw(Variable+">>"+histName,WeightSample+"("+CutsSample+")");
      tree->Draw(Variable+">>"+histNameSS,WeightSampleQCD+"("+CutsSampleSS+")");
      //      double norm = 1.0;
      //      double nevents = 1.0;
      //      double xsec = 1.0;
      //      if (name.Contains("Data")||name.Contains("Embed")) {
      //	norm = 1.;
      //	nevents = histWeightsH->GetSumOfWeights();
      //      }
      //      else { 
      //	xsec = xsecs[sampleName];
      //	nevents = histWeightsH->GetSumOfWeights();
      //	norm = xsec*lumi/nevents;
      //      }
      double yield = histSample->GetSumOfWeights();
      std::cout << setw(30) << sampleName << " : " << setw(6) << int(yield) << std::endl;
      sampleAttr.hist->Add(sampleAttr.hist,histSample,1.,1.);
      sampleAttr.histSS->Add(sampleAttr.histSS,histSampleSS,1.,1.);
      //      delete file;
      //      delete histSample;
      //      delete histSampleSS;
      
    }
  }  

  delete dummy;
  
  // *******************
  // adding data samples 
  // *******************
  TH1D * histData = NULL;
  TH1D * QCD = NULL;
  histData = DataEMuAttr.hist;
  QCD = DataEMuAttr.histSS;

  TH1D * data_SS = (TH1D*)QCD->Clone("data_SS");
  TH1D * data_OS = (TH1D*)histData->Clone("data_OS");

  //  if (!embedded) {
  //    ZttAttr.hist->Add(ZttAttr.hist,EWKAttr.hist,1.,1.);
  //    ZttAttr.hist->Add(ZttAttr.hist,TTAttr.hist,1.,1.);
  //  }

  QCD->Add(QCD,ZttAttr.histSS,1,-1);
  QCD->Add(QCD,ZllAttr.histSS,1,-1);
  QCD->Add(QCD,WJetsAttr.histSS,1,-1);
  QCD->Add(QCD,EWKAttr.histSS,1,-1);
  QCD->Add(QCD,TTAttr.histSS,1,-1);

  QCD->Scale(scaleQCD);
      
  TH1D * W        = WJetsAttr.hist;
  TH1D * TT       = TTAttr.hist;
  TH1D * EWK      = EWKAttr.hist;
  TH1D * ZLL      = ZllAttr.hist;
  TH1D * ZTT      = ZttAttr.hist;
  TH1D * Higgs    = HiggsAttr.hist;

  TH1D * W_SS        = WJetsAttr.histSS;
  TH1D * TT_SS       = TTAttr.histSS;
  TH1D * EWK_SS      = EWKAttr.histSS;
  TH1D * ZLL_SS      = ZllAttr.histSS;
  TH1D * ZTT_SS      = ZttAttr.histSS;
  TH1D * Higgs_SS    = HiggsAttr.histSS;

  std::cout << std::endl;
  std::cout << "Variable : " << Variable << std::endl;
  std::cout << "---------------------------" << std::endl;
  std::cout << "Same-sign - > " << std::endl;
  std::cout << "TTL  : " << TT_SS->GetSumOfWeights() << endl;
  std::cout << "VVL  : " << EWK_SS->GetSumOfWeights() << endl;
  std::cout << "W    : " << W_SS->GetSumOfWeights() << endl;
  std::cout << "ZLL  : " << ZLL_SS->GetSumOfWeights() << endl;
  std::cout << "ZTT  : " << ZTT_SS->GetSumOfWeights() << endl;
  std::cout << "Data : " << data_SS->GetSumOfWeights() << std::endl;
  std::cout << std::endl;
  std::cout << "Opposite-sign -> " << std::endl;
  std::cout << "TTL  : " << TT->GetSumOfWeights() << endl;
  std::cout << "VVL  : " << EWK->GetSumOfWeights() << endl;
  std::cout << "W    : " << W->GetSumOfWeights() << endl;
  std::cout << "QCD  : " << QCD->GetSumOfWeights() << endl;
  std::cout << "ZLL  : " << ZLL->GetSumOfWeights() << endl;
  std::cout << "ZTT  : " << ZTT->GetSumOfWeights() << endl;
  std::cout << std::endl;

  //  return;

  // zero bins in the QCD background
  for (int iB=1; iB<=nBins; ++iB) {
    double qcd = QCD->GetBinContent(iB);
    if (qcd<0) {
      QCD->SetBinContent(iB,0.);
      QCD->SetBinError(iB,0.);
    }
  }

  //  adding normalization systematics
  double ZTT_norm = 0.04; //  normalization ZTT     :   4% (EMBEDDED)
  double EWK_norm = 0.05; //  normalization EWK     :   5%
  double QCD_norm = 0.12; //  normalization Fakes   :  12%
  double ZLL_mtau = 0.07; //  mu->tau fake rate ZLL :   7%
  double TT_norm  = 0.06; //  normalization TT      :   6%
  double W_norm   = 0.07; //  normalization W       :   7%

  double eff_Emb = 0.04;
  double eff_MC  = 0.04;
  
  bool applyNormSys = cfg.get<bool>("ApplySystematics");
  if (applyNormSys) {
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
      //    std::cout << "bin : " << iB << " : " << QCD->GetBinContent(iB) << std::endl;

      float w = W->GetBinContent(iB);
      float we = W->GetBinError(iB);
      we = TMath::Sqrt(we*we+w*w*(W_norm*W_norm+eff_MC*eff_MC));
      W->SetBinError(iB,we);

      float tt  = TT->GetBinContent(iB);
      float tte = TT->GetBinError(iB);
      tte = TMath::Sqrt(tte*tte+tt*tt*(TT_norm*TT_norm+eff_MC*eff_MC));
      TT->SetBinError(iB,tte);

      float zll  = ZLL->GetBinContent(iB);
      float zlle = ZLL->GetBinError(iB);
      zlle = TMath::Sqrt(zlle*zlle+zll*zll*eff_MC*eff_MC);
      ZLL->SetBinError(iB,zlle);
      
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

  TT->Add(TT,Higgs);
  EWK->Add(EWK,TT);
  EWK->Add(EWK,W);
  EWK->Add(EWK,ZLL);
  QCD->Add(QCD,EWK);
  ZTT->Add(ZTT,QCD);

  std::cout << "Model : " << ZTT->GetSumOfWeights() << std::endl;
  std::cout << "Data  : " << histData->GetSumOfWeights() << std::endl;
  std::cout << "ratio = " << histData->GetSumOfWeights()/ZTT->GetSumOfWeights() << std::endl;

  TH1D * bkgdErr = (TH1D*)ZTT->Clone("bkgdErr");
  //  TH1
  bkgdErr->SetFillStyle(3013);
  bkgdErr->SetFillColor(1);
  bkgdErr->SetMarkerStyle(21);
  bkgdErr->SetMarkerSize(0);
  
  for (int iB=1; iB<=nBins; ++iB) {
    TT->SetBinError(iB,0);
    EWK->SetBinError(iB,0);
    W->SetBinError(iB,0);
    ZLL->SetBinError(iB,0);
    ZTT->SetBinError(iB,0);
    QCD->SetBinError(iB,0);
    Higgs->SetBinError(iB,0);
  }
  InitData(histData);

  InitHist(QCD,"","",TColor::GetColor("#FFCCFF"),1001);
  InitHist(TT,"","",TColor::GetColor("#9999CC"),1001);
  InitHist(EWK,"","",TColor::GetColor("#DE5A6A"),1001);
  InitHist(Higgs,"","",kCyan,1001);
  InitHist(ZLL,"","",TColor::GetColor("#4496C8"),1001);
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

  ZTT->Draw("h");
  QCD->Draw("sameh");
  EWK->Draw("sameh");
  TT->Draw("sameh");
  Higgs->Draw("sameh");
  bkgdErr->Draw("e2same");
  histData->Draw("e1same");
  float chi2 = 0;
  for (int iB=1; iB<=nBins; ++iB) {
    float xData = histData->GetBinContent(iB);
    float xMC = bkgdErr->GetBinContent(iB);
    float eMC = bkgdErr->GetBinError(iB);
    if (xMC>1e-1) {
      float diff2 = (xData-xMC)*(xData-xMC);
      chi2 += diff2/(xMC+eMC*eMC);
    }
  }
  std::cout << std::endl;
  double ndof = nBins - 1;
  double prob = TMath::Prob(chi2,ndof);
  std::cout << "Chi2/ndof = " << chi2 << "/" << ndof << "  p-value = " << prob << std::endl;
  std::cout << std::endl;

  TLegend * leg;
  if (legRight) leg = new TLegend(0.61,0.47,0.90,0.77);
  else leg = new TLegend(0.20,0.47,0.50,0.77);
  SetLegendStyle(leg);
  leg->SetTextSize(0.044);
  leg->AddEntry(histData,"Data","lp");
  if (embedded) 
    leg->AddEntry(ZTT,"embedded #tau#tau","f");
  else 
    leg->AddEntry(ZTT,"Z#rightarrow#tau#tau","f");
  leg->AddEntry(QCD,"QCD","f");
  leg->AddEntry(EWK,"electroweak","f");
  leg->AddEntry(TT,"t#bar{t}","f");
  //  leg->AddEntry(Higgs,"H(125)","f");
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

  for (int iB=1; iB<=nBins; ++iB) {
    float x1 = histData->GetBinContent(iB);
    float x2 = ZTT->GetBinContent(iB);
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
  lower->Modified();
  lower->RedrawAxis();
  if (logX) lower->SetLogx(true);
  canv1->cd();
  canv1->Modified();
  canv1->cd();
  canv1->SetSelected(canv1);
  canv1->Update();
  TString suffixLOGY("");
  TString suffixDY("");
  if (isDYamcatnlo) suffixDY = "_DYamcatnlo";
  if (logY) suffixLOGY = "_logY";
  canv1->Print(outputGraphics+"/"+Variable+"_"+era+"_"+suffix+"_"+sel_suffix+suffixDY+suffixLOGY+".png");

}
