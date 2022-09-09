#ifndef Settings_h
#define Settings_h

#include "TString.h"
#include <map>
#include <vector>

using namespace std;

  const map<TString, double> xsecs_2016 = {
    {"WJetsToLNu"  , 61526.7}, // NNLO (1)
    {"W1JetsToLNu" , 9370.5}, // NNLO (2)
    {"W2JetsToLNu" , 3170.9}, // NNLO (3)
    {"W3JetsToLNu" , 1132.5}, // NNLO (4)
    {"W4JetsToLNu" , 631.5 }, // NNLO (5)
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
    {"WWTo2L2Nu"                , 11.59},
    {"VVTo2L2Nu"                , 13.84},
    {"WWToLNuQQ"                , 49.997},
    {"WZTo2L2Q"                 , 5.52},
    {"WZTo1L1Nu2Q"              , 10.71},
    {"WZTo1L3Nu"                , 3.05},
    {"WZJToLLLNu"               , 4.708},
    {"WZTo3LNu"                 , 4.43},
    {"ZZTo4L"                   , 1.26},
    {"ZZTo2L2Q"                 , 3.38},
    {"ZZTo2L2Nu"                , 2.00},
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
    {"SUSYGluGluToBBHToTauTau_powheg_M125", 0.405*6.208E-02},
  };

  const map<TString, double> xsecs_2017 = {
    {"WJetsToLNu"  , 61526.7}, // NNLO (1)
    {"W1JetsToLNu" , 9370.5}, // NNLO (2)
    {"W2JetsToLNu" , 3170.9}, // NNLO (3)
    {"W3JetsToLNu" , 1132.5}, // NNLO (4)
    {"W4JetsToLNu" , 631.5 }, // NNLO (5)
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
    {"WWTo2L2Nu"                , 11.59},
    {"WWToLNuQQ"                , 49.997},
    {"WZTo2L2Q"                 , 5.52},
    {"WZTo1L1Nu2Q"              , 10.71},
    {"WZTo1L3Nu"                , 3.05},
    {"WZJToLLLNu"               , 4.708},
    {"WZTo3LNu"                 , 4.43},
    {"ZZTo4L"                   , 1.26},
    {"ZZTo2L2Q"                 , 3.38},
    {"ZZTo2L2Nu"                , 2.00},
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
    {"SUSYGluGluToBBHToTauTau_powheg_M125", 0.405*6.208E-02},
  };

  const map<TString, double> xsecs_2018 = {
    {"WJetsToLNu"  , 61526.7}, // NNLO (1)
    {"W1JetsToLNu" , 9370.5}, // NNLO (2)
    {"W2JetsToLNu" , 3170.9}, // NNLO (3)
    {"W3JetsToLNu" , 1132.5}, // NNLO (4)
    {"W4JetsToLNu" , 631.5 }, // NNLO (5)
      
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
    {"WWTo2L2Nu"                , 11.59},
    {"WWToLNuQQ"                , 49.997},
    {"WZTo2L2Q"                 , 5.52},
    {"WZTo1L1Nu2Q"              , 10.71},
    {"WZTo1L3Nu"                , 3.05},
    {"WZJToLLLNu"               , 4.708},
    {"WZTo3LNu"                 , 4.43},
    {"ZZTo4L"                   , 1.26},
    {"ZZTo2L2Q"                 , 3.38},
    {"ZZTo2L2Nu"                , 2.00},
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
    {"SUSYGluGluToBBHToTauTau_powheg_M125", 0.405*6.208E-02},
  };


std::vector<TString> SingleMuon_2018 = {
  "SingleMuon_Run2018A",
  "SingleMuon_Run2018B",
  "SingleMuon_Run2018C",
  "SingleMuon_Run2018D"
};

std::vector<TString> SingleElectron_2018 = {
  "EGamma_Run2018A",
  "EGamma_Run2018B",
  "EGamma_Run2018C",
  "EGamma_Run2018D"
};

std::vector<TString> MuonEG_2018 = {
  "MuonEG_Run2018A",
  "MuonEG_Run2018B",
  "MuonEG_Run2018C",
  "MuonEG_Run2018D"
};

std::vector<TString> Tau_2018 = {
  "Tau_Run2018A",
  "Tau_Run2018B",
  "Tau_Run2018C",
  "Tau_Run2018D"
};

std::vector<TString> EmbeddedElMu_2018 = {
  "EmbeddedElMu_Run2018A",
  "EmbeddedElMu_Run2018B",
  "EmbeddedElMu_Run2018C",
  "EmbeddedElMu_Run2018D"
};

std::vector<TString> EmbeddedTauTau_2018 = {
  "EmbeddedTauTau_Run2018A",
  "EmbeddedTauTau_Run2018B",
  "EmbeddedTauTau_Run2018C",
  "EmbeddedTauTau_Run2018D"
};

// ****** 2017 ********

std::vector<TString> SingleMuon_2017 = {
  "SingleMuon_Run2017B",
  "SingleMuon_Run2017C",
  "SingleMuon_Run2017D",
  "SingleMuon_Run2017E",
  "SingleMuon_Run2017F"
};

std::vector<TString> SingleElectron_2017 = {
  "SingleElectron_Run2017B",
  "SingleElectron_Run2017C",
  "SingleElectron_Run2017D",
  "SingleElectron_Run2017E",
  "SingleElectron_Run2017F",
};

std::vector<TString> MuonEG_2017 = {
  "MuonEG_Run2017B",
  "MuonEG_Run2017C",
  "MuonEG_Run2017D",
  "MuonEG_Run2017E",
  "MuonEG_Run2017F"
};

std::vector<TString> Tau_2017 = {
  "Tau_Run2017B",
  "Tau_Run2017C",
  "Tau_Run2017D",
  "Tau_Run2017E",
  "Tau_Run2017F"
};

std::vector<TString> EmbeddedElMu_2017 = {
  "EmbeddedElMu_Run2017B",
  "EmbeddedElMu_Run2017C",
  "EmbeddedElMu_Run2017D",
  "EmbeddedElMu_Run2017E",
  "EmbeddedElMu_Run2017F",
};

std::vector<TString> EmbeddedTauTau_2017 = {
  "EmbeddedTauTau_Run2017B",
  "EmbeddedTauTau_Run2017C",
  "EmbeddedTauTau_Run2017D",
  "EmbeddedTauTau_Run2017E",
  "EmbeddedTauTau_Run2017F",
};

// ******* 2016 ******

std::vector<TString> SingleMuon_2016 = {
  "SingleMuon_Run2016B",
  "SingleMuon_Run2016C",
  "SingleMuon_Run2016D",
  "SingleMuon_Run2016E",
  "SingleMuon_Run2016F",
  "SingleMuon_Run2016G",
  "SingleMuon_Run2016H"
};

std::vector<TString> SingleElectron_2016 = {
  "SingleElectron_Run2016B",
  "SingleElectron_Run2016C",
  "SingleElectron_Run2016D",
  "SingleElectron_Run2016E",
  "SingleElectron_Run2016F",
  "SingleElectron_Run2016G",
  "SingleElectron_Run2016H"
};

std::vector<TString> MuonEG_2016 = {
  "MuonEG_Run2016B",
  "MuonEG_Run2016C",
  "MuonEG_Run2016D",
  "MuonEG_Run2016E",
  "MuonEG_Run2016F",
  "MuonEG_Run2016G",
  "MuonEG_Run2016H"
};

std::vector<TString> Tau_2016 = {
  "Tau_Run2016B",
  "Tau_Run2016C",
  "Tau_Run2016D",
  "Tau_Run2016E",
  "Tau_Run2016F",
  "Tau_Run2016G",
  "Tau_Run2016H"
};

std::vector<TString> EmbeddedElMu_2016 = {
  "EmbeddedElMu_Run2016B",
  "EmbeddedElMu_Run2016C",
  "EmbeddedElMu_Run2016D",
  "EmbeddedElMu_Run2016E",
  "EmbeddedElMu_Run2016F",
  "EmbeddedElMu_Run2016G",
  "EmbeddedElMu_Run2016H"
};

std::vector<TString> EmbeddedTauTau_2016 = {
  "EmbeddedTauTau_Run2016B",
  "EmbeddedTauTau_Run2016C",
  "EmbeddedTauTau_Run2016D",
  "EmbeddedTauTau_Run2016E",
  "EmbeddedTauTau_Run2016F",
  "EmbeddedTauTau_Run2016G",
  "EmbeddedTauTau_Run2016H"
};

std::vector<TString> WJets = {
  "WJetsToLNu",
  "W1JetsToLNu",
  "W2JetsToLNu",
  "W3JetsToLNu",
  "W4JetsToLNu"
};
 
std::vector<TString> DYJets = {
  "DYJetsToLL_M-50",
  "DY1JetsToLL_M-50",
  "DY2JetsToLL_M-50",
  "DY3JetsToLL_M-50",
  "DY4JetsToLL_M-50"  
};

std::vector<TString> EWK_UL = {
  "ST_t-channel_top_4f",
  "ST_t-channel_antitop_4f",
  "ST_tW_top_5f",
  "ST_tW_antitop_5f",
  //  "VVTo2L2Nu",
  "WWTo2L2Nu",
  "ZZTo2L2Nu",
  "WZTo2L2Q",
  "WZTo3LNu",
  "ZZTo2L2Q",
  "ZZTo4L",
};

std::vector<TString> EWK = {
  "ST_t-channel_top_4f",
  "ST_t-channel_antitop_4f",
  "ST_tW_top_5f",
  "ST_tW_antitop_5f",
  "VVTo2L2Nu",
  //  "WWTo2L2Nu",
  //  "ZZTo2L2Nu",
  "WZTo2L2Q",
  "WZTo3LNu",
  "ZZTo2L2Q",
  "ZZTo4L",
};

std::vector<TString> TT_EXCL = {
  "TTTo2L2Nu",
  "TTToHadronic",
  "TTToSemiLeptonic"
};

std::vector<TString> TT_INCL = {
  "TT_INCL"
};

std::vector<TString> bbH125 = {
  "SUSYGluGluToBBHToTauTau_powheg_M125"
};

std::vector<TString> ggH125bb = {
  "GluGluHToTauTau_M125"
};

std::vector<TString> ggH125 = {
  "GluGluHToTauTau_M125",
};

std::vector<TString> H125 = {
  "GluGluHToTauTau_M125",
  "VBFHToTauTau_M125"
};

std::vector<TString> qqH125 = {
  "VBFHToTauTau_M125",
  //  "WplusHToTauTau_M125",
  //  "WminusHToTauTau_M125",
  //  "ZHToTauTau_M125_13TeV"
};

std::map<TString,double> LUMI = {
  {"2016_pre",19500},
  {"2016_post",16800},
  {"2017",41500},
  {"2018",59800}
};

const TString BaseTreeName = "TauCheck"; 
vector<TString> SystematicsNames = {"",  
				    "CMS_scale_met_unclustered_13TeVUp",
				    "CMS_scale_met_unclustered_13TeVDown",
				    "CMS_scale_met_boson_resolution_13TeVUp",
				    "CMS_scale_met_boson_resolution_13TeVDown",
				    "CMS_scale_met_boson_response_13TeVUp",
				    "CMS_scale_met_boson_response_13TeVDown",
				    "CMS_htt_boson_reso_met_13TeVUp",
				    "CMS_htt_boson_reso_met_13TeVDown",
				    "CMS_htt_boson_scale_met_13TeVUp",
				    "CMS_htt_boson_scale_met_13TeVDown",
				    "CMS_eff_b_13TeVUp",
				    "CMS_eff_b_13TeVDown",
				    "CMS_eff_mistag_13TeVUp",
				    "CMS_eff_mistag_13TeVDown",
				    "CMS_scale_j_FlavorQCD_13TeVUp",
				    "CMS_scale_j_FlavorQCD_13TeVDown",
				    "CMS_scale_j_RelativeBal_13TeVUp",
				    "CMS_scale_j_RelativeBal_13TeVDown",
				    "CMS_scale_j_HF_13TeVUp",
				    "CMS_scale_j_HF_13TeVDown",
				    "CMS_scale_j_BBEC1_13TeVUp",
				    "CMS_scale_j_BBEC1_13TeVDown",
				    "CMS_scale_j_EC2_13TeVUp",
				    "CMS_scale_j_EC2_13TeVDown",
				    "CMS_scale_j_Absolute_13TeVUp",
				    "CMS_scale_j_Absolute_13TeVDown",
				    "CMS_scale_j_Absolute_2016_13TeVUp",
				    "CMS_scale_j_Absolute_2016_13TeVDown",
				    "CMS_scale_j_HF_2016_13TeVUp",
				    "CMS_scale_j_HF_2016_13TeVDown",
				    "CMS_scale_j_EC2_2016_13TeVUp",
				    "CMS_scale_j_EC2_2016_13TeVDown",
				    "CMS_scale_j_RelativeSample_2016_13TeVUp",
				    "CMS_scale_j_RelativeSample_2016_13TeVDown",
				    "CMS_scale_j_BBEC1_2016_13TeVUp",
				    "CMS_scale_j_BBEC1_2016_13TeVDown",
				    "CMS_scale_j_Absolute_2017_13TeVUp",
				    "CMS_scale_j_Absolute_2017_13TeVDown",
				    "CMS_scale_j_HF_2017_13TeVUp",
				    "CMS_scale_j_HF_2017_13TeVDown",
				    "CMS_scale_j_EC2_2017_13TeVUp",
				    "CMS_scale_j_EC2_2017_13TeVDown",
				    "CMS_scale_j_RelativeSample_2017_13TeVUp",
				    "CMS_scale_j_RelativeSample_2017_13TeVDown",
				    "CMS_scale_j_BBEC1_2017_13TeVUp",
				    "CMS_scale_j_BBEC1_2017_13TeVDown",
				    "CMS_scale_j_Absolute_2018_13TeVUp",
				    "CMS_scale_j_Absolute_2018_13TeVDown",
				    "CMS_scale_j_HF_2018_13TeVUp",
				    "CMS_scale_j_HF_2018_13TeVDown",
				    "CMS_scale_j_EC2_2018_13TeVUp",
				    "CMS_scale_j_EC2_2018_13TeVDown",
				    "CMS_scale_j_RelativeSample_2018_13TeVUp",
				    "CMS_scale_j_RelativeSample_2018_13TeVDown",
				    "CMS_scale_j_BBEC1_2018_13TeVUp",
				    "CMS_scale_j_BBEC1_2018_13TeVDown",
				    "CMS_scale_mu_13TeVUp",
				    "CMS_scale_mu_13TeVDown",
				    "CMS_scale_e_13TeVUp",
				    "CMS_scale_e_13TeVDown",
				    "CMS_res_j_13TeVUp",
				    "CMS_res_j_13TeVDown"
};

int nBinsNoBTag = 31;
float binsNoBTag[32] = 
  {20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,225,250,275,300,325,350,400,500,700,900,4000};

int nBinsBTag = 17;
float binsBTag[18] =
  {20,40,60,80,100,120,140,160,180,200,250,300,350,400,500,700,4000};

#endif
