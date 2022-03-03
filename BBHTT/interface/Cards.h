#ifndef DataCards_h
#define DataCards_h

#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

// Samples :
// Data - data_obs
// DYJetsToLL - ZL
// WJets - W
// TTbar - TTL
// EWK - VVL
// EMB - EMB 
// ggHWW125, 
// qqHWW125, 
// WHWW125,
// ZHWW125,
// ggH125, 
// qqH125 
// WH125,
// ZH125,  
// bbH125
// ttH125 

// sampleToProcess = Data (Data and QCD)
//                 = DYJetsToLL
//                 = EMB 
//                 = MC (EWK WJets)
//                 = SMggH (gg->H H->tautau and H->WW)
//                 = SMothers (qqH, WH, ZH, bbH)

using namespace std;

template<class T1, class T2>
  vector<T1> extract_first(const map<T1, T2>& v) {
  vector<T1> vFirst;
  for (auto element : v) {
    vFirst.push_back(element.first);
  }
  return vFirst;
};

template<class T1, class T2>
  vector<T2> extract_second(const vector<pair<T1, T2> >& v) {
  vector<T2> vSecond;
  for (auto element : v) {
    vSecond.push_back(element.second);
  }
  return vSecond;
};

class Cards {

 public:

  Cards(TString Sample,
	TString Era,
	TString Category,
	TString channel,
	TString InputDir,
	TString PredDir,
	TString OutputDir,
	TString Variable,
	int nbins,
	double xmin,
	double xmax,
	bool RunWithSystematics,
	bool RunOnEmbedded); 

  void SetVariableToPlot(TString var, int nbins, double xmin, double xmax);
  void SetVariableToPlot(TString var, int nbins, double * bins);
  void SetVariableToPlot(TString var, int nbins, vector<double> bins);
  void SetVariableToPlot(TString var, vector<double> bins, vector<double> bins2);

  bool Run();
  bool CloseFile();
  void PrintSamples();
  void PrintShapeSystematics();
  void PrintWeightSystematics();
  ~Cards();

 private:

  const map<TString, double> xsecs_2016 = {
    {"WJetsToLNu"  , 61526.7}, // NNLO (1)
    {"W1JetsToLNu" , 9370.5}, // NNLO (2)
    {"W2JetsToLNu" , 3170.9}, // NNLO (3)
    {"W3JetsToLNu" , 1132.5}, // NNLO (4)
    {"W4JetsToLNu" , 631.5 }, // NNLO (5)
    {"DYJetsToLL_M-10to50",  21658.0}, // NNLO 
    {"DYJetsToLL_M-50"       , 6077.22},  // NNLO (20)
    {"DY1JetsToLL_M-50"      , 1253.1}, // NNLO (20a)
    {"DY2JetsToLL_M-50"      , 409.4}, // NNLO (20b)
    {"DY3JetsToLL_M-50"      , 124.8}, // NNLO (20c)
    {"DY4JetsToLL_M-50"      , 67.33}, // NNLO (20d)
    {"TTTo2L2Nu"        , 88.29},  // NNLO (21)
    {"TTToHadronic"     , 377.96}, // NNLO (22)
    {"TTToSemiLeptonic" , 365.35}, // NNLO (23)
    {"ST_t-channel_top_4f"      , 136.02}, 
    {"ST_t-channel_antitop_4f"  , 80.95}, 
    {"ST_tW_top_5f"             , 35.85}, 
    {"ST_tW_antitop_5f"         , 35.85}, 
    {"VVTo2L2Nu"                , 13.84},
    {"WWToLNuQQ"                , 49.997},
    {"WZTo2L2Q"                 , 5.52},
    {"WZTo1L1Nu2Q"              , 10.71},
    {"WZTo1L3Nu"                , 3.05},
    {"WZJToLLLNu"               , 4.708},
    {"WZTo3LNu"                 , 4.43},
    {"ZZTo4L"                   , 1.26},
    {"ZZTo2L2Q"                 , 3.38},
    {"TTTo2L2Nu_corrMET"        , 88.29},  // NNLO (21)
    {"TTToHadronic_corrMET"     , 377.96}, // NNLO (22)
    {"TTToSemiLeptonic_corrMET" , 365.35}, // NNLO (23)
    {"ST_t-channel_top_4f_corrMET"      , 136.02}, 
    {"ST_t-channel_antitop_4f_corrMET"  , 80.95}, 
    {"ST_tW_top_5f_corrMET"             , 35.85}, 
    {"ST_tW_antitop_5f_corrMET"         , 35.85}, 
    {"VVTo2L2Nu_corrMET"                , 13.84},
    {"WWToLNuQQ_corrMET"                , 49.997},
    {"WZTo2L2Q_corrMET"                 , 5.52},
    {"WZTo1L1Nu2Q_corrMET"              , 10.71},
    {"WZTo1L3Nu_corrMET"                , 3.05},
    {"WZJToLLLNu_corrMET"               , 4.708},
    {"WZTo3LNu_corrMET"                 , 4.43},
    {"ZZTo4L_corrMET"                   , 1.26},
    {"ZZTo2L2Q_corrMET"                 , 3.38},
    {"GluGluHToTauTau_M125"     , 3.00},
    {"VBFHToTauTau_M125"        , 0.237},
    {"VBFHToTauTau_M95"         , 1.00},
    {"WplusHToTauTau_M125"      , 0.0527},
    {"WminusHToTauTau_M125"     , 0.0334},
    {"ZHToTauTau_M125_13TeV"    , 0.0477},
    {"GluGluHToWWTo2L2Nu_M125"  , 1.09},
    {"VBFHToWWTo2L2Nu_M125"     , 0.0850},
    {"HWminusJ_HToWW_M125"      , 0.114},
    {"HWplusJ_HToWW_M125"       , 0.18},
    {"ZHJ_HToWW_M125"           , 0.163},
    {"SUSYGluGluToBBHToTauTau_powheg_M125", 0.405*6.208E-02}    
  };

  const map<TString, double> xsecs_2017 = {
    {"WJetsToLNu"  , 61526.7}, // NNLO (1)
    {"W1JetsToLNu" , 9370.5}, // NNLO (2)
    {"W2JetsToLNu" , 3170.9}, // NNLO (3)
    {"W3JetsToLNu" , 1132.5}, // NNLO (4)
    {"W4JetsToLNu" , 631.5 }, // NNLO (5)
    {"DYJetsToLL_M-10to50",  21658.0}, // NNLO 
    {"DYJetsToLL_M-50"       , 6077.22},  // NNLO (20)
    {"DY1JetsToLL_M-50"      , 977.1}, // NNLO (20a)
    {"DY2JetsToLL_M-50"      , 347.3}, // NNLO (20b)
    {"DY3JetsToLL_M-50"      , 126.1}, // NNLO (20c)
    {"DY4JetsToLL_M-50"      , 71.67}, // NNLO (20d)
    {"TTTo2L2Nu"        , 88.29},  // NNLO (21)
    {"TTToHadronic"     , 377.96}, // NNLO (22)
    {"TTToSemiLeptonic" , 365.35}, // NNLO (23)
    {"ST_t-channel_top_4f"      , 136.02}, 
    {"ST_t-channel_antitop_4f"  , 80.95}, 
    {"ST_tW_top_5f"             , 35.85}, 
    {"ST_tW_antitop_5f"         , 35.85}, 
    {"VVTo2L2Nu"                , 13.84},
    {"WWToLNuQQ"                , 49.997},
    {"WZTo2L2Q"                 , 5.52},
    {"WZTo1L1Nu2Q"              , 10.71},
    {"WZTo1L3Nu"                , 3.05},
    {"WZJToLLLNu"               , 4.708},
    {"WZTo3LNu"                 , 4.43},
    {"ZZTo4L"                   , 1.26},
    {"ZZTo2L2Q"                 , 3.38},
    {"TTTo2L2Nu_corrMET"        , 88.29},  // NNLO (21)
    {"TTToHadronic_corrMET"     , 377.96}, // NNLO (22)
    {"TTToSemiLeptonic_corrMET" , 365.35}, // NNLO (23)
    {"ST_t-channel_top_4f_corrMET"      , 136.02}, 
    {"ST_t-channel_antitop_4f_corrMET"  , 80.95}, 
    {"ST_tW_top_5f_corrMET"             , 35.85}, 
    {"ST_tW_antitop_5f_corrMET"         , 35.85}, 
    {"VVTo2L2Nu_corrMET"                , 13.84},
    {"WWToLNuQQ_corrMET"                , 49.997},
    {"WZTo2L2Q_corrMET"                 , 5.52},
    {"WZTo1L1Nu2Q_corrMET"              , 10.71},
    {"WZTo1L3Nu_corrMET"                , 3.05},
    {"WZJToLLLNu_corrMET"               , 4.708},
    {"WZTo3LNu_corrMET"                 , 4.43},
    {"ZZTo4L_corrMET"                   , 1.26},
    {"ZZTo2L2Q_corrMET"                 , 3.38},
    {"GluGluHToTauTau_M125"     , 3.00},
    {"VBFHToTauTau_M125"        , 0.237},
    {"VBFHToTauTau_M95"         , 1.00},
    {"WplusHToTauTau_M125"      , 0.0527},
    {"WminusHToTauTau_M125"     , 0.0334},
    {"ZHToTauTau_M125_13TeV"    , 0.0477},
    {"GluGluHToWWTo2L2Nu_M125"  , 1.09},
    {"VBFHToWWTo2L2Nu_M125"     , 0.0850},
    {"HWminusJ_HToWW_M125"      , 0.114},
    {"HWplusJ_HToWW_M125"       , 0.18},
    {"ZHJ_HToWW_M125"           , 0.163},
    {"SUSYGluGluToBBHToTauTau_powheg_M125", 0.405*6.208E-02}
  };

  const map<TString, double> xsecs_2018 = {
    {"WJetsToLNu"  , 61526.7}, // NNLO (1)
    {"W1JetsToLNu" , 9370.5}, // NNLO (2)
    {"W2JetsToLNu" , 3170.9}, // NNLO (3)
    {"W3JetsToLNu" , 1132.5}, // NNLO (4)
    {"W4JetsToLNu" , 631.5 }, // NNLO (5)
    {"DYJetsToLL_M-10to50",  21658.0}, // NNLO 
    {"DYJetsToLL_M-50"       , 6077.22},  // NNLO (20)
    {"DY1JetsToLL_M-50"      , 1007.6}, // NNLO (20a)
    {"DY2JetsToLL_M-50"      , 344.3}, // NNLO (20b)
    {"DY3JetsToLL_M-50"      , 125.3}, // NNLO (20c)
    {"DY4JetsToLL_M-50"      , 71.20}, // NNLO (20d)
    {"TTTo2L2Nu"        , 88.29},  // NNLO (21)
    {"TTToHadronic"     , 377.96}, // NNLO (22)
    {"TTToSemiLeptonic" , 365.35}, // NNLO (23)
    {"ST_t-channel_top_4f"      , 136.02}, 
    {"ST_t-channel_antitop_4f"  , 80.95}, 
    {"ST_tW_top_5f"             , 35.85}, 
    {"ST_tW_antitop_5f"         , 35.85}, 
    {"VVTo2L2Nu"                , 13.84},
    {"WWToLNuQQ"                , 49.997},
    {"WZTo2L2Q"                 , 5.52},
    {"WZTo1L1Nu2Q"              , 10.71},
    {"WZTo1L3Nu"                , 3.05},
    {"WZJToLLLNu"               , 4.708},
    {"WZTo3LNu"                 , 4.43},
    {"ZZTo4L"                   , 1.26},
    {"ZZTo2L2Q"                 , 3.38},
    {"TTTo2L2Nu_corrMET"        , 88.29},  // NNLO (21)
    {"TTToHadronic_corrMET"     , 377.96}, // NNLO (22)
    {"TTToSemiLeptonic_corrMET" , 365.35}, // NNLO (23)
    {"ST_t-channel_top_4f_corrMET"      , 136.02}, 
    {"ST_t-channel_antitop_4f_corrMET"  , 80.95}, 
    {"ST_tW_top_5f_corrMET"             , 35.85}, 
    {"ST_tW_antitop_5f_corrMET"         , 35.85}, 
    {"VVTo2L2Nu_corrMET"                , 13.84},
    {"WWToLNuQQ_corrMET"                , 49.997},
    {"WZTo2L2Q_corrMET"                 , 5.52},
    {"WZTo1L1Nu2Q_corrMET"              , 10.71},
    {"WZTo1L3Nu_corrMET"                , 3.05},
    {"WZJToLLLNu_corrMET"               , 4.708},
    {"WZTo3LNu_corrMET"                 , 4.43},
    {"ZZTo4L_corrMET"                   , 1.26},
    {"ZZTo2L2Q_corrMET"                 , 3.38},
    {"GluGluHToTauTau_M125"     , 3.00},
    {"VBFHToTauTau_M125"        , 0.237},
    {"VBFHToTauTau_M95"         , 1.00},
    {"WplusHToTauTau_M125"      , 0.0527},
    {"WminusHToTauTau_M125"     , 0.0334},
    {"ZHToTauTau_M125_13TeV"    , 0.0477},
    {"GluGluHToWWTo2L2Nu_M125"  , 1.09},
    {"VBFHToWWTo2L2Nu_M125"     , 0.0850},
    {"HWminusJ_HToWW_M125"      , 0.114},
    {"HWplusJ_HToWW_M125"       , 0.18},
    {"ZHJ_HToWW_M125"           , 0.163},
    {"SUSYGluGluToBBHToTauTau_powheg_M125", 0.405*6.208E-02}
  };

  const double ggHbb_scale = 0.54;

  map<TString,double> xsecs;

  vector<TString> Embedded;
  vector<TString> Data;


  // Data TauTau
  // ******* 2018 ******

  const vector<TString> DataTauTau_2018 = {
    "Tau_Run2018A",
    "Tau_Run2018B",
    "Tau_Run2018C",
    "Tau_Run2018D"
  };
    // ******* 2017 ******

  const vector<TString> DataTauTau_2017 = {
    "Tau_Run2017B",
    "Tau_Run2017C",
    "Tau_Run2017D",
    "Tau_Run2017E",
    "Tau_Run2017F"
  };
  
  // ******* 2016 ******

  const vector<TString> DataTauTau_2016 = {
    "Tau_Run2016B",
    "Tau_Run2016C",
    "Tau_Run2016D",
    "Tau_Run2016E",
    "Tau_Run2016F",
    "Tau_Run2016G",
    "Tau_Run2016H"
  };
    // Data ElMu

  // ******* 2018 ******

  const vector<TString> DataElMu_2018 = {
    "MuonEG_Run2018A",
    "MuonEG_Run2018B",
    "MuonEG_Run2018C",
    "MuonEG_Run2018D"
  };
  // ******* 2017 ******

  const vector<TString> DataElMu_2017 = {
    "MuonEG_Run2017B",
    "MuonEG_Run2017C",
    "MuonEG_Run2017D",
    "MuonEG_Run2017E",
    "MuonEG_Run2017F"
  };
  
  // ******* 2016 ******

  const vector<TString> DataElMu_2016 = {
    "MuonEG_Run2016B",
    "MuonEG_Run2016C",
    "MuonEG_Run2016D",
    "MuonEG_Run2016E",
    "MuonEG_Run2016F",
    "MuonEG_Run2016G",
    "MuonEG_Run2016H"
  };
  
  // ****** embedded samples *************


  const vector<TString> EmbeddedTauTau_2016 = {
    "EmbeddedTauTau_Run2016B",
    "EmbeddedTauTau_Run2016C",
    "EmbeddedTauTau_Run2016D",
    "EmbeddedTauTau_Run2016E",
    "EmbeddedTauTau_Run2016F",
    "EmbeddedTauTau_Run2016G",
    "EmbeddedTauTau_Run2016H"
  };
  
  const vector<TString> EmbeddedTauTau_2017 = {
    "EmbeddedTauTau_Run2017B",
    "EmbeddedTauTau_Run2017C",
    "EmbeddedTauTau_Run2017D",
    "EmbeddedTauTau_Run2017E",
    "EmbeddedTauTau_Run2017F",
  };

  const vector<TString> EmbeddedTauTau_2018 = {
    "EmbeddedTauTau_Run2018A",
    "EmbeddedTauTau_Run2018B",
    "EmbeddedTauTau_Run2018C",
    "EmbeddedTauTau_Run2018D"
  };

  const vector<TString> EmbeddedElMu_2016 = {
    "EmbeddedElMu_Run2016B",
    "EmbeddedElMu_Run2016C",
    "EmbeddedElMu_Run2016D",
    "EmbeddedElMu_Run2016E",
    "EmbeddedElMu_Run2016F",
    "EmbeddedElMu_Run2016G",
    "EmbeddedElMu_Run2016H"
  };
  
  const vector<TString> EmbeddedElMu_2017 = {
    "EmbeddedElMu_Run2017B",
    "EmbeddedElMu_Run2017C",
    "EmbeddedElMu_Run2017D",
    "EmbeddedElMu_Run2017E",
    "EmbeddedElMu_Run2017F",
  };

  const vector<TString> EmbeddedElMu_2018 = {
    "EmbeddedElMu_Run2018A",
    "EmbeddedElMu_Run2018B",
    "EmbeddedElMu_Run2018C",
    "EmbeddedElMu_Run2018D"
  };

  // ******** MC samples *************

  const vector<TString> WJets = {
    "WJetsToLNu_0",
    "WJetsToLNu_1",
    "WJetsToLNu_2",
    "WJetsToLNu_3",
    "WJetsToLNu_4",
    "W1JetsToLNu",
    "W2JetsToLNu",
    "W3JetsToLNu",
    "W4JetsToLNu"
  };
  
  vector<TString> DYJetsToLL = {
    "DYJetsToLL_M-50_0",
    "DYJetsToLL_M-50_1",
    "DYJetsToLL_M-50_2",
    "DYJetsToLL_M-50_3",
    "DYJetsToLL_M-50_4",
    "DY1JetsToLL_M-50",
    "DY2JetsToLL_M-50",
    "DY3JetsToLL_M-50",
    "DY4JetsToLL_M-50"  
  };

  vector<TString> DYJetsToTT = {
    "DYJetsToTT_M-50_0",
    "DYJetsToTT_M-50_1",
    "DYJetsToTT_M-50_2",
    "DYJetsToTT_M-50_3",
    "DYJetsToTT_M-50_4",
    "DY1JetsToTT_M-50",
    "DY2JetsToTT_M-50",
    "DY3JetsToTT_M-50",
    "DY4JetsToTT_M-50"  
  };
  
  /*
    vector<TString> DYJets = {
    "DYJetsToLL_M-50",
    "DY1JetsToLL_M-50",
    "DY2JetsToLL_M-50",
    "DY3JetsToLL_M-50",
    "DY4JetsToLL_M-50"  
    };
  */
  
  // needed for stitching 
  map<TString,TString> WJetsFiles = {
    {"WJetsToLNu_0","WJetsToLNu"},
    {"WJetsToLNu_1","WJetsToLNu"},
    {"WJetsToLNu_2","WJetsToLNu"},
    {"WJetsToLNu_3","WJetsToLNu"},
    {"WJetsToLNu_4","WJetsToLNu"},
    {"W1JetsToLNu","W1JetsToLNu"},
    {"W2JetsToLNu","W2JetsToLNu"},
    {"W3JetsToLNu","W3JetsToLNu"},
    {"W4JetsToLNu","W4JetsToLNu"}
  };

  map<TString,TString> DYJetsLLFiles = {
    {"DYJetsToLL_M-50_0","DYJetsToLL_M-50"},
    {"DYJetsToLL_M-50_1","DYJetsToLL_M-50"},
    {"DYJetsToLL_M-50_2","DYJetsToLL_M-50"},
    {"DYJetsToLL_M-50_3","DYJetsToLL_M-50"},
    {"DYJetsToLL_M-50_4","DYJetsToLL_M-50"},
    {"DY1JetsToLL_M-50","DY1JetsToLL_M-50"},
    {"DY2JetsToLL_M-50","DY2JetsToLL_M-50"},
    {"DY3JetsToLL_M-50","DY3JetsToLL_M-50"},
    {"DY4JetsToLL_M-50","DY4JetsToLL_M-50"},
  };

  map<TString,TString> DYJetsTTFiles = {
    {"DYJetsToTT_M-50_0","DYJetsToLL_M-50"},
    {"DYJetsToTT_M-50_1","DYJetsToLL_M-50"},
    {"DYJetsToTT_M-50_2","DYJetsToLL_M-50"},
    {"DYJetsToTT_M-50_3","DYJetsToLL_M-50"},
    {"DYJetsToTT_M-50_4","DYJetsToLL_M-50"},
    {"DY1JetsToTT_M-50","DY1JetsToLL_M-50"},
    {"DY2JetsToTT_M-50","DY2JetsToLL_M-50"},
    {"DY3JetsToTT_M-50","DY3JetsToLL_M-50"},
    {"DY4JetsToTT_M-50","DY4JetsToLL_M-50"},
  };
  
  vector<TString> EWK = {
    "ST_t-channel_top_4f",
    "ST_t-channel_antitop_4f",
    "ST_tW_top_5f",
    "ST_tW_antitop_5f",
    "VVTo2L2Nu",
    "WZTo2L2Q",
    "WZTo3LNu",
    "ZZTo2L2Q",
    "ZZTo4L",
  };

  vector<TString> TT = {
    "TTTo2L2Nu",
    "TTToHadronic",
    "TTToSemiLeptonic"
  };

  vector<TString> DYJets_Low = {
    "DYJetsToLL_M-10to50"
  };
  
  vector<TString> GluGluHToTauTau = {
    "GluGluHToTauTau_M125" 
  };
  
  vector<TString> VBFHToTauTau = {
    "VBFHToTauTau_M125"
  };

  vector<TString> WHToTauTau = {
    "WplusHToTauTau_M125",
    "WminusHToTauTau_M125"
  };

  vector<TString> ZHToTauTau = {
    "ZHToTauTau_M125_13TeV"
  };

  vector<TString> bbHToTauTau = {
    "BBHToTauTau_M125_13TeV","BBHToTauTauYbYt_M125_13TeV","GluGluToBBHToTauTau_M125_13TeV"
  };

  vector<TString> GluGluHToWW = {
    "GluGluHToWWTo2L2Nu_M125"
  };
  
  vector<TString> VBFHToWW = {
    "VBFHToWWTo2L2Nu_M125"
  };

  vector<TString> WHToWW = {
    "HWminusJ_HToWW_M125",
    "HWplusJ_HToWW_M125"
  };

  vector<TString> ZHToWW = {
    "ZHJ_HToWW_M125"
  };
  
  TString mcNotTauTau;
  TString mcTauTau;
  const TString BaseTreeName = "TauCheck"; 
  TString baselineTT="trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5&&os>0.5";
  TString baselineEM="(trg_muhigh_elow && pt_2 > 24) || (trg_ehigh_mulow && pt_1 > 24)&&iso_1<0.15&&iso_2<0.2&&dr_tt>0.5&&pt_1>10.&&pt_2>10.&&extraelec_veto < 0.5&&extramuon_veto<0.5&&TMath::Max(pt_1,pt_2)>20";
  TString category;
  const TString mcNotTauTau_TT = "&&!(gen_match_1==5&&gen_match_2==5)";
  const TString mcTauTau_TT = "&&(gen_match_1==5&&gen_match_2==5)";
  const TString mcNotTauTau_EM = "&&!(gen_match_1==3&&gen_match_2==4)";
  const TString mcTauTau_EM = "&&(gen_match_1==3&&gen_match_2==4)";
  const TString mcNotFakes = "&&(gen_match_1<=5&&gen_match_2<=5)";
  const TString signalRegion = "&&byMediumDeepTau2017v2p1VSjet_1>0.5&&byMediumDeepTau2017v2p1VSjet_2>0.5";
  const TString fakesSideBand = "&&byMediumDeepTau2017v2p1VSjet_1<0.5&&byVVVLooseDeepTau2017v2p1VSjet_1>0.5&&byMediumDeepTau2017v2p1VSjet_2>0.5";
  const TString mcSideBand = "&&gen_match_1!=6" ;
  const TString mcSingleFake = "&&gen_match_1!=6&&gen_match_2==6";

  const TString sameSignRegion = "&&os<0.5";
  const TString oppositeSignRegion = "&&os>0.5";

  vector<TString> regionCut;    // three regions defined (SR, fake AR, single fake region)
  vector<TString> regionWeight; // three regions defined 



  // ************************
  // ***** Fake Factors *****
  // ************************


  std::map<TString,TString> FF_pt2_era = {
    {"2016","1.05*(1.0*(pt_2<=120.)+0.80*(pt_2>120.))*"},
    {"2017","1.06*(1.0*(pt_2<=80.)+0.90*(pt_2>80.))*"},
    {"2018","1.06*(1.0*(pt_2<=80.)+0.85*(pt_2>80.&&pt_2<=95.)+0.6*(pt_2>95.))*"},
  }; 
  std::map<TString,TString> FF_btg_era = {
    {"2016","(1.0*(nbtag==0)+0.93*(nbtag==1)+1.00*(nbtag>=2))*"},
    {"2017","(1.0*(nbtag<=1)+0.60*(nbtag==2)+0.50*(nbtag>=3))*"},
    {"2018","(1.0*(nbtag==0)+0.93*(nbtag==1)+0.52*(nbtag>=2))*"},
  };




  // *****************************
  // ***** Shape systematics *****
  // *****************************

  const map<TString,TString> EmbeddedShapeSystematics = {
    {"CMS_scale_t_emb_1prong","CMS_scale_t_1prong_13TeV"},
    {"CMS_scale_t_emb_1prong1pizero","CMS_scale_t_1prong1pizero_13TeV"},
    {"CMS_scale_t_emb_3prong","CMS_scale_t_3prong_13TeV"},
    {"CMS_scale_t_emb_3prong1pizero","CMS_scale_t_3prong1pizero_13TeV"},
    {"CMS_scale_t_1prong","CMS_scale_t_1prong_13TeV"},
    {"CMS_scale_t_1prong1pizero","CMS_scale_t_1prong1pizero_13TeV"},
    {"CMS_scale_t_3prong","CMS_scale_t_3prong_13TeV"},
    {"CMS_scale_t_3prong1pizero","CMS_scale_t_3prong1pizero_13TeV"}
  };

  const map<TString,TString> ShapeSystematics_Common = {
    {"CMS_scale_j_FlavorQCD","CMS_scale_j_FlavorQCD_13TeV"},
    {"CMS_scale_j_RelativeBal","CMS_scale_j_RelativeBal_13TeV"},
    {"CMS_scale_j_HF","CMS_scale_j_HF_13TeV"},
    {"CMS_scale_j_BBEC1","CMS_scale_j_BBEC1_13TeV"},
    {"CMS_scale_j_EC2","CMS_scale_j_EC2_13TeV"},
    {"CMS_scale_j_Absolute","CMS_scale_j_Absolute_13TeV"},    
  };

  const map<TString,TString> ShapeSystematics_2016 = {
    {"CMS_scale_t_1prong_2016","CMS_scale_t_1prong_13TeV"},
    {"CMS_scale_t_1prong1pizero_2016","CMS_scale_t_1prong1pizero_13TeV"},
    {"CMS_scale_t_3prong_2016","CMS_scale_t_3prong_13TeV"},
    {"CMS_scale_t_3prong1pizero_2016","CMS_scale_t_3prong1pizero_13TeV"},
    {"CMS_scale_met_unclustered_2016","CMS_scale_met_unclustered_13TeV"},
    {"CMS_htt_boson_res_met_2016","CMS_htt_boson_reso_met_13TeV"},
    {"CMS_htt_boson_scale_met_2016","CMS_htt_boson_scale_met_13TeV"},
    {"CMS_htt_eff_b_2016","CMS_eff_b_13TeV"},
    {"CMS_htt_mistag_b_2016","CMS_mistag_b_13TeV"},
    {"CMS_scale_j_Absolute_2016","CMS_scale_j_Absolute_2016_13TeV"},
    {"CMS_scale_j_HF_2016","CMS_scale_j_HF_2016_13TeV"},
    {"CMS_scale_j_EC2_2016","CMS_scale_j_EC2_2016_13TeV"},
    {"CMS_scale_j_RelativeSample_2016","CMS_scale_j_RelativeSample_2016_13TeV"},
    {"CMS_scale_j_BBEC1_2016","CMS_scale_j_BBEC1_2016_13TeV"},
    {"CMS_res_j_2016","CMS_res_j_13TeV"},
  };  

  const map<TString,TString> ShapeSystematics_2017 = {
    {"CMS_scale_t_1prong_2017","CMS_scale_t_1prong_13TeV"},
    {"CMS_scale_t_1prong1pizero_2017","CMS_scale_t_1prong1pizero_13TeV"},
    {"CMS_scale_t_3prong_2017","CMS_scale_t_3prong_13TeV"},
    {"CMS_scale_t_3prong1pizero_2017","CMS_scale_t_3prong1pizero_13TeV"},
    {"CMS_scale_met_unclustered_2017","CMS_scale_met_unclustered_13TeV"},
    {"CMS_htt_boson_res_met_2017","CMS_htt_boson_reso_met_13TeV"},
    {"CMS_htt_boson_scale_met_2017","CMS_htt_boson_scale_met_13TeV"},
    {"CMS_htt_eff_b_2017","CMS_eff_b_13TeV"},
    {"CMS_htt_mistag_b_2017","CMS_mistag_b_13TeV"},
    {"CMS_scale_j_Absolute_2017","CMS_scale_j_Absolute_2017_13TeV"},
    {"CMS_scale_j_HF_2017","CMS_scale_j_HF_2017_13TeV"},
    {"CMS_scale_j_EC2_2017","CMS_scale_j_EC2_2017_13TeV"},
    {"CMS_scale_j_RelativeSample_2017","CMS_scale_j_RelativeSample_2017_13TeV"},
    {"CMS_scale_j_BBEC1_2017","CMS_scale_j_BBEC1_2017_13TeV"},
    {"CMS_res_j_2017","CMS_res_j_13TeV"},
  };  

  const map<TString,TString> ShapeSystematics_2018 = {
    {"CMS_scale_t_1prong_2018","CMS_scale_t_1prong_13TeV"},
    {"CMS_scale_t_1prong1pizero_2018","CMS_scale_t_1prong1pizero_13TeV"},
    {"CMS_scale_t_3prong_2018","CMS_scale_t_3prong_13TeV"},
    {"CMS_scale_t_3prong1pizero_2018","CMS_scale_t_3prong1pizero_13TeV"},
    {"CMS_scale_met_unclustered_2018","CMS_scale_met_unclustered_13TeV"},
    {"CMS_htt_boson_res_met_2018","CMS_htt_boson_reso_met_13TeV"},
    {"CMS_htt_boson_scale_met_2018","CMS_htt_boson_scale_met_13TeV"},
    {"CMS_htt_eff_b_2018","CMS_eff_b_13TeV"},
    {"CMS_htt_mistag_b_2018","CMS_mistag_b_13TeV"},
    {"CMS_scale_j_Absolute_2018","CMS_scale_j_Absolute_2018_13TeV"},
    {"CMS_scale_j_HF_2018","CMS_scale_j_HF_2018_13TeV"},
    {"CMS_scale_j_EC2_2018","CMS_scale_j_EC2_2018_13TeV"},
    {"CMS_scale_j_RelativeSample_2018","CMS_scale_j_RelativeSample_2018_13TeV"},
    {"CMS_scale_j_BBEC1_2018","CMS_scale_j_BBEC1_2018_13TeV"},
    {"CMS_res_j_2018","CMS_res_j_13TeV"},
  };  

  // ******************************
  // *** Weight systematics *******
  // ******************************

  const map<TString,TString> PrefiringSystematics = {
    {"CMS_prefiringUp","(prefiringweightUp/prefiringweight)"},
    {"CMS_prefiringDown","(prefiringweightDown/prefiringweight)"},    
  };

  const map<TString,TString> DYShapeSystematics_2016 = {
    {"CMS_htt_dyShape_2016Up","zptweight"},
    {"CMS_htt_dyShape_2016Down","(1/zptweight)"},
  };

  const map<TString,TString> DYShapeSystematics = {
    {"CMS_htt_dyShapeUp","zptweight"},
    {"CMS_htt_dyShapeDown","(1/zptweight)"},
  };

  const map<TString,TString> TopShapeSystematics = {
    {"CMS_htt_ttbarShapeUp","topptweight"},
    {"CMS_htt_ttbarShapeDown","(1/topptweight)"},
  };

  const map<TString,TString> WeightSystematics = {
    {"CMS_eff_xtrigger_t_tt_dm0","weight_CMS_eff_tau_trig_DM0"},
    {"CMS_eff_xtrigger_t_tt_dm1","weight_CMS_eff_tau_trig_DM1"},
    {"CMS_eff_xtrigger_t_tt_dm10","weight_CMS_eff_tau_trig_DM10"},
    {"CMS_eff_xtrigger_t_tt_dm11","weight_CMS_eff_tau_trig_DM11"},
    {"CMS_eff_t_dm0","weight_CMS_eff_tauid_DM0"},
    {"CMS_eff_t_dm1","weight_CMS_eff_tauid_DM1"},
    {"CMS_eff_t_dm10","weight_CMS_eff_tauid_DM10"},
    {"CMS_eff_t_dm11","weight_CMS_eff_tauid_DM11"},
    {"CMS_htt_fake_e_tt","weight_CMS_etaufake"},
    {"CMS_htt_fake_m_tt","weight_CMS_mutaufake"}
  };

  const map<TString,TString> EmbeddedWeightSystematics = {
    {"CMS_eff_xtrigger_t_emb_tt_dm0","weight_CMS_eff_tau_trig_DM0"},
    {"CMS_eff_xtrigger_t_emb_tt_dm1","weight_CMS_eff_tau_trig_DM1"},
    {"CMS_eff_xtrigger_t_emb_tt_dm10","weight_CMS_eff_tau_trig_DM10"},
    {"CMS_eff_xtrigger_t_emb_tt_dm11","weight_CMS_eff_tau_trig_DM11"},
    {"CMS_eff_t_emb_dm0","weight_CMS_eff_tauid_DM0"},
    {"CMS_eff_t_emb_dm1","weight_CMS_eff_tauid_DM1"},
    {"CMS_eff_t_emb_dm10","weight_CMS_eff_tauid_DM10"},
    {"CMS_eff_t_emb_dm11","weight_CMS_eff_tauid_DM11"},
    {"CMS_eff_xtrigger_t_tt_dm0","weight_CMS_eff_tau_trig_DM0"},
    {"CMS_eff_xtrigger_t_tt_dm1","weight_CMS_eff_tau_trig_DM1"},
    {"CMS_eff_xtrigger_t_tt_dm10","weight_CMS_eff_tau_trig_DM10"},
    {"CMS_eff_xtrigger_t_tt_dm11","weight_CMS_eff_tau_trig_DM11"},
    {"CMS_eff_t_dm0","weight_CMS_eff_tauid_DM0"},
    {"CMS_eff_t_dm1","weight_CMS_eff_tauid_DM1"},
    {"CMS_eff_t_dm10","weight_CMS_eff_tauid_DM10"},
    {"CMS_eff_t_dm11","weight_CMS_eff_tauid_DM11"},
  };

  const map<TString,TString> FakeFactorSystematics = {
    {"CMS_ff_total_qcd_met_closure_syst_tt","ff_qcd_met"},
    {"CMS_ff_total_qcd_pt2_closure_syst_tt","ff_qcd_pt2"},
    {"CMS_ff_total_qcd_osss_extrap_syst_tt","ff_qcd_syst"}
  };

  const map<TString,TString> SignalSystematics = {
    {"CMS_QCDscale","weight_CMS_scale_gg_13TeV"},
    {"CMS_PS_ISR","weight_CMS_PS_ISR_ggH_13TeV"},
    {"CMS_PS_FSR","weight_CMS_PS_FSR_ggH_13TeV"},
  };

  // ******************************************************* 
  // ************* CLASS VARIABLES *************************
  // *******************************************************

  map<TString, TString> weightSystematicsMap;
  map<TString, TString> shapeSystematicsMap;
  map<TString, double> sampleNormMap; // sample-norm map
  map<TString, TFile*> sampleFileMap; // sample-file map
  map<TString, TString> baseNameMap; // sample-baseName map
  map<TString, vector<TString> > nameSampleMap; // sample map
  map<TString, vector<TString> > sampleSpecificCutMap; // sample-specific-cut map
  map<TString, double> sampleXSecMap;
  map<TString, double> sampleNeventsMap;
  map<TString, TString> nameHistoMap;
  map<TString, TH1D*> nameTH1DMap;
  vector<TString> samplesContainer;

  map<TString, map<TString,double> > btagCorr_Cat;

  int numberOfShapeSystematics;
  int numberOfWeightSystematics;

  // for variables which are different from mt_tot; 
  int nBins;
  double Bins[500];
  double xMin;
  double xMax;
  // for the second variable 
  int nBins2;
  double Bins2[10];

  TString sampleToProcess;
  TString input_dir; // includes era
  TString input_friend_dir; // input friend 
  TString output_filename; // outputdir + era / sampleToProcess + Category;
  TFile * outputFile; 

  TString globalWeight="weight*";
  TString qcdWeight="qcdweight*";
  TString FFWeight="ff_nom*ff_qcd_pt2*";
  TString commonCuts;
  TString era;
  TString channel;

  bool block;
  bool isBTag;
  bool isEquidistantBinning;
  bool runWithSystematics;
  bool runWithShapeSystematics;
  bool runOnEmbedded;

  TString variable;
  double lumi;

  // **************************************************
  // ************* Internal member functions **********
  // **************************************************

  vector<TString> SampleSpecificCutEM(TString name, 
				      TString sampleName);
  vector<TString> SampleSpecificCutTT(TString name, 
				      TString sampleName);

  void InitializeSample(TString name);

  void InitializeSamples();

  TH1D * ProcessSample(TString name,
		       TString sysName,
		       unsigned int region,
		       bool weightSys);

  TH1D * createHisto(TString histName);
  TH2D * create2DHisto(TString histName);
  TH1D * unroll(TH2D * hist2D, TString histName);

  int CreateShapeSystematicsMap();
  int CreateWeightSystematicsMap();
  bool RunData();
  bool RunModel();
  void zeroBins(TH1D * hist);


};

#endif
