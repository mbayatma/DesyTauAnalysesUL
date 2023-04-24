#ifndef SETTINGS_FOR_ERAS_H
#define SETTINGS_FOR_ERAS_H

using namespace std;
// **************************************************************************************************
// Define the subsamples that belong to a certain process
// **********************************************************
const vector<TString> MuonEG_2018 = { 
  "MuonEG_Run2018A",
  "MuonEG_Run2018B", 
  "MuonEG_Run2018C",
  "MuonEG_Run2018D" 
};

const vector<TString> Tau_2018 = { 
  "Tau_Run2018A",
  "Tau_Run2018B", 
  "Tau_Run2018C",
  "Tau_Run2018D" 
};

const vector<TString> EmbeddedEMu_2018 = { 
  "EmbeddedElMu_Run2018A" ,
  "EmbeddedElMu_Run2018B" ,
  "EmbeddedElMu_Run2018C" , 
  "EmbeddedElMu_Run2018D" 
};

const vector<TString> EmbeddedTauTau_2018 = { 
  "EmbeddedTauTau_Run2018A",
  "EmbeddedTauTau_Run2018B",
  "EmbeddedTauTau_Run2018C", 
  "EmbeddedTauTau_Run2018D" 
};

const vector<TString> MuonEG_2017 = {
  "MuonEG_Run2017B",
  "MuonEG_Run2017C",
  "MuonEG_Run2017D",
  "MuonEG_Run2017E",
  "MuonEG_Run2017F" 
};

const vector<TString> Tau_2017 = {
  "Tau_Run2017B",
  "Tau_Run2017C",
  "Tau_Run2017D",
  "Tau_Run2017E",
  "Tau_Run2017F" 
};

const vector<TString> EmbeddedEMu_2017 = { 
  "EmbeddedElMu_Run2017B",
  "EmbeddedElMu_Run2017C",
  "EmbeddedElMu_Run2017D",
  "EmbeddedElMu_Run2017E",
  "EmbeddedElMu_Run2017F" 
};

const vector<TString> EmbeddedTauTau_2017 = { 
  "EmbeddedTauTau_Run2017B",
  "EmbeddedTauTau_Run2017C",
  "EmbeddedTauTau_Run2017D",
  "EmbeddedTauTau_Run2017E",
  "EmbeddedTauTau_Run2017F" 
};

const vector<TString> MuonEG_2016_pre = {
  "MuonEG_Run2016B", 
  "MuonEG_Run2016C", 
  "MuonEG_Run2016D", 
  "MuonEG_Run2016E", 
  "MuonEG_Run2016F"
};

const vector<TString> MuonEG_2016_post = {
  "MuonEG_Run2016F",
  "MuonEG_Run2016G",
  "MuonEG_Run2016H"
};

const vector<TString> Tau_2016_pre = {
  "Tau_Run2016B", 
  "Tau_Run2016C", 
  "Tau_Run2016D", 
  "Tau_Run2016E", 
  "Tau_Run2016F"
};

const vector<TString> Tau_2016_post = {
  "Tau_Run2016F",
  "Tau_Run2016G",
  "Tau_Run2016H"
};


const vector<TString> EmbeddedEMu_2016_pre = { 
  "EmbeddedElMu_Run2016B",
  "EmbeddedElMu_Run2016C",
  "EmbeddedElMu_Run2016D",
  "EmbeddedElMu_Run2016E",
  "EmbeddedElMu_Run2016F"
};

const vector<TString> EmbeddedEMu_2016_post = { 
  "EmbeddedElMu_Run2016F",
  "EmbeddedElMu_Run2016G",
  "EmbeddedElMu_Run2016H"
};

const vector<TString> EmbeddedTauTau_2016_pre = { 
  "EmbeddedTauTau_Run2016B",
  "EmbeddedTauTau_Run2016C",
  "EmbeddedTauTau_Run2016D",
  "EmbeddedTauTau_Run2016E",
  "EmbeddedTauTau_Run2016F"
};

const vector<TString> EmbeddedTauTau_2016_post = { 
  "EmbeddedTauTau_Run2016F",
  "EmbeddedTauTau_Run2016G",
  "EmbeddedTauTau_Run2016H"
};

const vector<TString> DYJets = { 
  "DY1JetsToLL_M-50",
  "DY2JetsToLL_M-50",
  "DY3JetsToLL_M-50",
  "DY4JetsToLL_M-50",
  "DYJetsToLL_M-50"
  //"EWKZ2Jets_ZToNuNu_TuneCP5_PSweights_13TeV-madgraph-pythia8" ,
  //"EWKZ2Jets_ZToLL_M-50_TuneCP5_PSweights_13TeV-madgraph-pythia8" , 
  //"DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8"
};

const vector<TString> DYJets_amcatnlo = { 
  "DYJetsToLL_M-50_amcatnlo",
  "DYJetsToLL_0J_amcatnlo",
  "DYJetsToLL_1J_amcatnlo",
  "DYJetsToLL_2J_amcatnlo"
};

const vector<TString> WJets_amcatnlo = { 
  //  "WJetsToLNu_amcatnlo",
  "WJetsToLNu_0J_amcatnlo",
  "WJetsToLNu_1J_amcatnlo",
  "WJetsToLNu_2J_amcatnlo"
};

const vector<TString> DYJets_amcatnlo_incl = { 
  "DYJetsToLL_M-50_amcatnlo"
};

const vector<TString> WJets = { 
  "W1JetsToLNu" ,
  "W2JetsToLNu" ,
  "W3JetsToLNu" ,
  "W4JetsToLNu" ,
  "WJetsToLNu" ,
};

const vector<TString> TTbar = { 
  "TTTo2L2Nu" ,
  "TTToHadronic" ,
  "TTToSemiLeptonic"
};

const vector<TString> SingleTop = { 
  "ST_t-channel_antitop_4f" ,
  "ST_t-channel_top_4f" ,
  "ST_tW_antitop_5f" ,
  "ST_tW_top_5f"
};

const vector<TString> Diboson  = { 
  "WZTo2L2Q" ,
  "WZTo3LNu" ,
  "ZZTo2L2Q" ,
  "ZZTo4L"   ,
  "ZZTo2L2Nu",
  "WWTo2L2Nu"                                                 
};

const vector<TString> BBHToTauTau =  {
   "bbHToTauTau_yb2_M125",
   "bbHToTauTau_yt2_M125", 
   "bbHToTauTau_ybyt_M125"
};

const vector<TString> BBHToTauTau_YB2 =  {
  "bbHToTauTau_yb2_M125"
};

const vector<TString> BBHToTauTau_YT2 =  {
  "bbHToTauTau_yt2_M125"
};

const vector<TString> BBHToTauTau_YBYT =  {
  "bbHToTauTau_ybyt_M125"
};

const vector<TString> VBFHToTauTau = { 
  "VBFHToTauTau_M125"
};

const vector<TString> ZHToTauTau = { 
  "ZHToTauTau_M125" 
};

const vector<TString> WHToTauTau = { 
  "WplusHToTauTau_M125", 
  "WminusHToTauTau_M125" 
};

const vector<TString> TTHToTauTau = {
  "ttHToTauTau_M125"
};

const vector<TString> GluGluHToTauTau = {
  "GluGluHToTauTau_M125" 
};

const vector<TString> GluGluHToWW = { 
  "GluGluHToWWTo2L2Nu_M125",
};

const vector<TString> VBFHToWW = { 
  "VBFHToWWTo2L2Nu_M125"
};

const vector<TString> ZHToWW = {
  "ZHToWWTo2L2Nu_M125"
};

const vector<TString> WHToWW = {
  "WminusHToWWTo2L2Nu_M125",
  "WplusHToWWTo2L2Nu_M125"
};

const vector<TString> BBHToWW_YB2 = {
  "bbHToWWTo2L2Nu_yb2_M125"
};

const vector<TString> BBHToWW_YBYT = {
  "bbHToWWTo2L2Nu_ybyt_M125"
};

const vector<TString> BBHToWW_YT2 = {
  "bbHToWWTo2L2Nu_yt2_M125"
};

const vector<TString> TTVJets = {
  "ttWJets",
  "ttZJets"
};

const vector<TString> TTHToWW = {
  "ttHJetToNonbb_M125"
};

// **************************************************************************************************
// **************************************************************************************************
// Cross-section map
// 2018 (checked with AN-19-177)
const map<TString, double> xsec_map_2018 = {
  {"WJetsToLNu_amcatnlo", 61526.7},
  {"WJetsToLNu_0J_amcatnlo", 50002.6},
  {"WJetsToLNu_1J_amcatnlo", 8395.38},
  {"WJetsToLNu_2J_amcatnlo", 3128.68},
  {"WJetsToLNu"  , 61526.7}, // NNLO (1)
  {"W1JetsToLNu" , 9370.5}, // NNLO (2)
  {"W2JetsToLNu" , 3170.9}, // NNLO (3)
  {"W3JetsToLNu" , 1132.5}, // NNLO (4)
  {"W4JetsToLNu" , 631.5 }, // NNLO (5)
  {"DYJetsToLL_M-50_amcatnlo", 6077.2}, // NNLO
  {"DYJetsToLL_0J_amcatnlo"  , 4840.0}, // NNLO
  {"DYJetsToLL_1J_amcatnlo"  , 898.5},  // NNLO
  {"DYJetsToLL_2J_amcatnlo"  , 338.7},  // NNLO
  {"DYJetsToLL_M-50"       , 6077.22},  // NNLO (20)
  {"DY1JetsToLL_M-50"      , 977.1}, // NNLO (20a)
  {"DY2JetsToLL_M-50"      , 347.3}, // NNLO (20b)
  {"DY3JetsToLL_M-50"      , 126.1}, // NNLO (20c)
  {"DY4JetsToLL_M-50"      , 71.67}, // NNLO (20d)
  {"TTTo2L2Nu"             , 88.29},  // NNLO (21)
  {"TTToHadronic"          , 377.96}, // NNLO (22)
  {"TTToSemiLeptonic"      , 365.35}, // NNLO (23)
  {"ST_t-channel_top_4f"      , 136.02}, // ? (24) -> could be improved
  {"ST_t-channel_antitop_4f"  , 80.95}, // ? (25) -> could be improved
  {"ST_tW_top_5f"             , 35.85}, // ? (26) -> could be improved
  {"ST_tW_antitop_5f"         , 35.85}, // ? (27) -> could be improved
  {"VVTo2L2Nu"                , 13.84},
  {"WWTo2L2Nu"                , 11.59},
  {"WWToLNuQQ"                , 49.997},
  {"WZTo2L2Q"                 , 5.52},
  {"WZTo1L1Nu2Q"              , 10.71},
  {"WZTo1L3Nu"                , 3.05},
  {"WZJToLLLNu"               , 4.708},
  {"WZTo3LNu"                 , 4.43},
  {"ZZTo2L2Nu"                , 2.01},
  {"ZZTo4L"                   , 1.26},
  {"ZZTo2L2Q"                 , 3.38},
  {"GluGluHToTauTau_M125"     , 3.00},
  {"VBFHToTauTau_M125"        , 0.234},
  {"WplusHToTauTau_M125"      , 0.0527},
  {"WminusHToTauTau_M125"     , 0.0334},
  {"ZHToTauTau_M125"          , 0.0477},
  {"ttHToTauTau_M125"         , 0.5033*0.06208},
  {"GluGluHToWWTo2L2Nu_M125"  , 3.11},
  {"VBFHToWWTo2L2Nu_M125"     , 0.087},
  {"WminusHToWWTo2L2Nu_M125"  , 0.114},
  {"WplusHToWWTo2L2Nu_M125"   , 0.18},
  {"ZHToWWTo2L2Nu_M125"       , 0.163},
  {"ttHJetToNonbb_M125"       , 0.212},
  // from AN-21-090
  // yb2: 0.4822*0.06208, yt2: 1.040*0.06208, ytyb: -0.033*0.06208
  {"bbHToTauTau_yb2_M125"     , 0.4822*0.06208},
  {"bbHToTauTau_yt2_M125"     , 1.040*0.06208},
  {"bbHToTauTau_ybyt_M125"    , -0.033*0.06208},
  // cross sections for the H->WW
  {"bbHToWWTo2L2Nu_yb2_M125"  , 0.4822*0.0281},
  {"bbHToWWTo2L2Nu_yt2_M125"  , 1.040*0.0281},
  {"bbHToWWTo2L2Nu_ybyt_M125" , -0.033*0.0281},
  {"ttWJets",0.205},
  {"ttZJets",0.920},
};

// 2017 (checked again - AN-19-177 -> DY xsec updated )
const map<TString, double> xsec_map_2017 = {
  {"WJetsToLNu_amcatnlo", 61526.7},
  {"WJetsToLNu_0J_amcatnlo", 50002.6},
  {"WJetsToLNu_1J_amcatnlo", 8395.38},
  {"WJetsToLNu_2J_amcatnlo", 3128.68},
  {"WJetsToLNu"  , 61526.7}, // NNLO (1)
  {"W1JetsToLNu" , 9370.5}, // NNLO (2)
  {"W2JetsToLNu" , 3170.9}, // NNLO (3)
  {"W3JetsToLNu" , 1132.5}, // NNLO (4)
  {"W4JetsToLNu" , 631.5 }, // NNLO (5)
  {"DYJetsToLL_M-50_amcatnlo", 6077.2}, // NNLO
  {"DYJetsToLL_0J_amcatnlo"  , 4840.0}, // NNLO
  {"DYJetsToLL_1J_amcatnlo"  , 898.5},  // NNLO
  {"DYJetsToLL_2J_amcatnlo"  , 338.7},  // NNLO
  {"DYJetsToLL_M-50"       , 6077.22},  // NNLO (20)
  {"DY1JetsToLL_M-50"      , 977.1}, // NNLO (20a)
  {"DY2JetsToLL_M-50"      , 347.3}, // NNLO (20b)
  {"DY3JetsToLL_M-50"      , 126.1}, // NNLO (20c)
  {"DY4JetsToLL_M-50"      , 71.67}, // NNLO (20d)
  {"TTTo2L2Nu"             , 88.29},  // NNLO (21)
  {"TTToHadronic"          , 377.96}, // NNLO (22)
  {"TTToSemiLeptonic"      , 365.35}, // NNLO (23)
  {"ST_t-channel_top_4f"      , 136.02}, // ? (24) -> could be improved
  {"ST_t-channel_antitop_4f"  , 80.95}, // ? (25) -> could be improved
  {"ST_tW_top_5f"             , 35.85*0.543}, // ? (26) -> could be improved
  {"ST_tW_antitop_5f"         , 35.85*0.543}, // ? (27) -> could be improved
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
  {"ZZTo2L2Nu"                , 2.01},
  {"GluGluHToTauTau_M125"     , 3.00},
  {"VBFHToTauTau_M125"        , 0.234},
  {"WplusHToTauTau_M125"      , 0.0527},
  {"WminusHToTauTau_M125"     , 0.0334},
  {"ZHToTauTau_M125"          , 0.0477},
  {"ttHToTauTau_M125"         , 0.5033*0.06208},
  {"GluGluHToWWTo2L2Nu_M125"  , 3.11},
  {"VBFHToWWTo2L2Nu_M125"     , 0.0850},
  {"WminusHToWWTo2L2Nu_M125"  , 0.114},
  {"WplusHToWWTo2L2Nu_M125"   , 0.18},
  {"ZHToWWTo2L2Nu_M125"       , 0.163},
  {"ttHJetToNonbb_M125"       , 0.212},
  // from AN-21-090
  // yb2: 0.4822*0.06208, yt2: 1.040*0.06208, ytyb: -0.033*0.06208
  {"bbHToTauTau_yb2_M125"     , 0.4822*0.06208},
  {"bbHToTauTau_yt2_M125"     , 1.040*0.06208},
  {"bbHToTauTau_ybyt_M125"    , -0.033*0.06208},
  // cross sections for the H->WW
  {"bbHToWWTo2L2Nu_yb2_M125"  , 0.4822*0.0281},
  {"bbHToWWTo2L2Nu_yt2_M125"  , 1.040*0.0281},
  {"bbHToWWTo2L2Nu_ybyt_M125" , -0.033*0.0281},
  {"ttWJets",0.205},
  {"ttZJets",0.920},
};

// 2016 (taken from AN-19-177)
const map<TString, double> xsec_map_2016 = {
  {"WJetsToLNu_amcatnlo", 61526.7},
  {"WJetsToLNu_0J_amcatnlo", 50002.6},
  {"WJetsToLNu_1J_amcatnlo", 8395.38},
  {"WJetsToLNu_2J_amcatnlo", 3128.68},
  {"WJetsToLNu"  , 61526.7}, // NNLO (1)
  {"W1JetsToLNu" , 9370.5}, // NNLO (2)
  {"W2JetsToLNu" , 3170.9}, // NNLO (3)
  {"W3JetsToLNu" , 1132.5}, // NNLO (4)
  {"W4JetsToLNu" , 631.5 }, // NNLO (5)
  {"DYJetsToLL_M-50_amcatnlo", 6077.2}, // NNLO 
  {"DYJetsToLL_0J_amcatnlo"  , 4840.0}, // NNLO
  {"DYJetsToLL_1J_amcatnlo"  , 898.5},  // NNLO
  {"DYJetsToLL_2J_amcatnlo"  , 338.7},  // NNLO
  {"DYJetsToLL_M-50"       , 6077.22},  // NNLO
  {"DY1JetsToLL_M-50"      , 977.1}, // NNLO (20a)
  {"DY2JetsToLL_M-50"      , 347.3}, // NNLO (20b)
  {"DY3JetsToLL_M-50"      , 126.1}, // NNLO (20c)
  {"DY4JetsToLL_M-50"      , 71.67}, // NNLO (20d)
  {"TTTo2L2Nu"             , 88.29},  // NNLO (21)
  {"TTToHadronic"          , 377.96}, // NNLO (22)
  {"TTToSemiLeptonic"      , 365.35}, // NNLO (23)
  {"ST_t-channel_top_4f"      , 136.02}, // ? (24) -> could be improved
  {"ST_t-channel_antitop_4f"  , 80.95}, // ? (25) -> could be improved
  {"ST_tW_top_5f"             , 35.85}, // ? (26) -> could be improved
  {"ST_tW_antitop_5f"         , 35.85}, // ? (27) -> could be improved
  {"VVTo2L2Nu"                , 13.84},
  {"WWTo2L2Nu"                , 11.59},
  {"WWToLNuQQ"                , 49.997},
  {"WZTo2L2Q"                 , 5.52},
  {"WZTo1L1Nu2Q"              , 10.71},
  {"WZTo1L3Nu"                , 3.05},
  {"WZJToLLLNu"               , 4.708},
  {"WZTo3LNu"                 , 4.43},
  {"ZZTo2L2Nu"                , 2.01},
  {"ZZTo4L"                   , 1.26},
  {"ZZTo2L2Q"                 , 3.38},
  {"GluGluHToTauTau_M125"     , 3.00},
  {"VBFHToTauTau_M125"        , 0.234},
  {"WplusHToTauTau_M125"      , 0.0527},
  {"WminusHToTauTau_M125"     , 0.0334},
  {"ZHToTauTau_M125"          , 0.0477},
  {"ttHToTauTau_M125"         , 0.5033*0.06208},
  {"GluGluHToWWTo2L2Nu_M125"  , 3.11},
  {"VBFHToWWTo2L2Nu_M125"     , 0.0850},
  {"WminusHToWWTo2L2Nu_M125"  , 0.114},
  {"WplusHToWWTo2L2Nu_M125"   , 0.18},
  {"ZHToWWTo2L2Nu_M125"       , 0.163},
  {"ttHJetToNonbb_M125"       , 0.212},
  // from AN-21-090
  // yb2: 0.4822*0.06208, yt2: 1.040*0.06208, ytyb: -0.033*0.06208
  {"bbHToTauTau_yb2_M125"     , 0.4822*0.06208},
  {"bbHToTauTau_yt2_M125"     , 1.040*0.06208},
  {"bbHToTauTau_ybyt_M125"    , -0.033*0.06208},
  // cross sections for the H->WW
  {"bbHToWWTo2L2Nu_yb2_M125"  , 0.4822*0.0281},
  {"bbHToWWTo2L2Nu_yt2_M125"  , 1.040*0.0281},
  {"bbHToWWTo2L2Nu_ybyt_M125" , -0.033*0.0281},
  {"ttWJets",0.205},
  {"ttZJets",0.920},
};

const map<TString, vector<TString> > map_sample = {
  {"MuonEG_2018", MuonEG_2018},
  {"MuonEG_2017", MuonEG_2017},
  {"MuonEG_2016_pre", MuonEG_2016_pre},
  {"MuonEG_2016_post", MuonEG_2016_post},

  {"Tau_2018", Tau_2018},
  {"Tau_2017", Tau_2017},
  {"Tau_2016_pre", Tau_2016_pre},
  {"Tau_2016_post", Tau_2016_post},
  
  {"EmbeddedEMu_2018", EmbeddedEMu_2018},
  {"EmbeddedEMu_2017", EmbeddedEMu_2017},
  {"EmbeddedEMu_2016_pre", EmbeddedEMu_2016_pre},
  {"EmbeddedEMu_2016_post", EmbeddedEMu_2016_post},

  {"EmbeddedTauTau_2018", EmbeddedTauTau_2018},
  {"EmbeddedTauTau_2017", EmbeddedTauTau_2017},
  {"EmbeddedTauTau_2016_pre", EmbeddedTauTau_2016_pre},
  {"EmbeddedTauTau_2016_post", EmbeddedTauTau_2016_post},

  {"DrellYanJets_2018",DYJets_amcatnlo_incl},
  {"DrellYanJets_2017",DYJets_amcatnlo_incl},
  {"DrellYanJets_2016_pre",DYJets_amcatnlo_incl},
  {"DrellYanJets_2016_post",DYJets_amcatnlo_incl},
  
  {"DYJets_2018",DYJets},
  {"DYJets_2017",DYJets},
  {"DYJets_2016_pre",DYJets},
  {"DYJets_2016_post",DYJets},

  {"DYJets_amcatnlo_2018",DYJets_amcatnlo},
  {"DYJets_amcatnlo_2017",DYJets_amcatnlo},
  {"DYJets_amcatnlo_2016_pre",DYJets_amcatnlo},
  {"DYJets_amcatnlo_2016_post",DYJets_amcatnlo},

  {"WJets_amcatnlo_2018",WJets_amcatnlo},
  {"WJets_amcatnlo_2017",WJets_amcatnlo},
  {"WJets_amcatnlo_2016_pre",WJets_amcatnlo},
  {"WJets_amcatnlo_2016_post",WJets_amcatnlo},

  //  {"WJets_nnlo_2018",WJets_nnlo},
  //  {"WJets_nnlo_2017",WJets_nnlo},
  //  {"WJets_nnlo_2016_pre",WJets_nnlo},
  //  {"WJets_nnlo_2016_post",WJets_nnlo},

  {"WJets_2018",WJets},
  {"WJets_2017",WJets},
  {"WJets_2016_pre",WJets},
  {"WJets_2016_post",WJets},

  {"TTbar_2018",TTbar},
  {"TTbar_2017",TTbar},
  {"TTbar_2016_pre",TTbar},
  {"TTbar_2016_post",TTbar},

  {"SingleTop_2018",SingleTop},
  {"SingleTop_2017",SingleTop},
  {"SingleTop_2016_pre",SingleTop},
  {"SingleTop_2016_post",SingleTop},

  {"Diboson_2018",Diboson},
  {"Diboson_2017",Diboson},
  {"Diboson_2016_pre",Diboson},
  {"Diboson_2016_post",Diboson},

  {"GluGluHToTauTau_2018",GluGluHToTauTau},
  {"GluGluHToTauTau_2017",GluGluHToTauTau},
  {"GluGluHToTauTau_2016_pre",GluGluHToTauTau},
  {"GluGluHToTauTau_2016_post",GluGluHToTauTau},

  {"VBFHToTauTau_2018",VBFHToTauTau},
  {"VBFHToTauTau_2017",VBFHToTauTau},
  {"VBFHToTauTau_2016_pre",VBFHToTauTau},
  {"VBFHToTauTau_2016_post",VBFHToTauTau},

  {"WHToTauTau_2018", WHToTauTau},
  {"WHToTauTau_2017", WHToTauTau},
  {"WHToTauTau_2016_pre", WHToTauTau},
  {"WHToTauTau_2016_post", WHToTauTau},
   
  {"ZHToTauTau_2018",ZHToTauTau},
  {"ZHToTauTau_2017",ZHToTauTau},
  {"ZHToTauTau_2016_pre",ZHToTauTau},
  {"ZHToTauTau_2016_post",ZHToTauTau},
  
  {"TTHToTauTau_2018",TTHToTauTau},
  {"TTHToTauTau_2017",TTHToTauTau},
  {"TTHToTauTau_2016_pre",TTHToTauTau},
  {"TTHToTauTau_2016_post",TTHToTauTau},
  
  {"BBHToTauTau_2018",BBHToTauTau},
  {"BBHToTauTau_2017",BBHToTauTau},
  {"BBHToTauTau_2016_pre",BBHToTauTau},
  {"BBHToTauTau_2016_post",BBHToTauTau},

  {"BBHToTauTau_YT2_2018",BBHToTauTau_YT2},
  {"BBHToTauTau_YT2_2017",BBHToTauTau_YT2},
  {"BBHToTauTau_YT2_2016_pre",BBHToTauTau_YT2},
  {"BBHToTauTau_YT2_2016_post",BBHToTauTau_YT2},

  {"BBHToTauTau_YB2_2018",BBHToTauTau_YB2},
  {"BBHToTauTau_YB2_2017",BBHToTauTau_YB2},
  {"BBHToTauTau_YB2_2016_pre",BBHToTauTau_YB2},
  {"BBHToTauTau_YB2_2016_post",BBHToTauTau_YB2},

  {"BBHToTauTau_YBYT_2018",BBHToTauTau_YBYT},
  {"BBHToTauTau_YBYT_2017",BBHToTauTau_YBYT},
  {"BBHToTauTau_YBYT_2016_pre",BBHToTauTau_YBYT},
  {"BBHToTauTau_YBYT_2016_post",BBHToTauTau_YBYT},

  {"GluGluHToWW_2018",GluGluHToWW},
  {"GluGluHToWW_2017",GluGluHToWW},
  {"GluGluHToWW_2016_pre",GluGluHToWW},
  {"GluGluHToWW_2016_post",GluGluHToWW},

  {"VBFHToWW_2018",VBFHToWW},
  {"VBFHToWW_2017",VBFHToWW},
  {"VBFHToWW_2016_pre",VBFHToWW},
  {"VBFHToWW_2016_post",VBFHToWW},

  {"WHToWW_2018",WHToWW},
  {"WHToWW_2017",WHToWW},
  {"WHToWW_2016_pre",WHToWW},
  {"WHToWW_2016_post",WHToWW},

  {"ZHToWW_2018",ZHToWW},
  {"ZHToWW_2017",ZHToWW},
  {"ZHToWW_2016_pre",ZHToWW},
  {"ZHToWW_2016_post",ZHToWW},

  {"BBHToWW_YB2_2018",BBHToWW_YB2},
  {"BBHToWW_YB2_2017",BBHToWW_YB2},
  {"BBHToWW_YB2_2016_pre",BBHToWW_YB2},
  {"BBHToWW_YB2_2016_post",BBHToWW_YB2},

  {"BBHToWW_YT2_2018",BBHToWW_YT2},
  {"BBHToWW_YT2_2017",BBHToWW_YT2},
  {"BBHToWW_YT2_2016_pre",BBHToWW_YT2},
  {"BBHToWW_YT2_2016_post",BBHToWW_YT2},

  {"BBHToWW_YBYT_2018",BBHToWW_YBYT},
  {"BBHToWW_YBYT_2017",BBHToWW_YBYT},
  {"BBHToWW_YBYT_2016_pre",BBHToWW_YBYT},
  {"BBHToWW_YBYT_2016_post",BBHToWW_YBYT},

  {"TTVJets_2018",TTVJets},
  {"TTVJets_2017",TTVJets},
  {"TTVJets_2016_pre",TTVJets},
  {"TTVJets_2016_post",TTVJets},
  
  {"TTHToWW_2018",TTHToWW},
  {"TTHToWW_2017",TTHToWW},
  {"TTHToWW_2016_pre",TTHToWW},
  {"TTHToWW_2016_post",TTHToWW},


};

std::vector<TString> systematics_tt = {
  "CMS_scale_t_1prong_13TeV",
  "CMS_scale_t_1prong1pizero_13TeV",
  "CMS_scale_t_3prong_13TeV",
  "CMS_scale_t_3prong1pizero_13TeV"
};

std::vector<TString> systematicsJES_2016 = {
  "CMS_scale_j_Absolute_2016_13TeV",
  "CMS_scale_j_HF_2016_13TeV",
  "CMS_scale_j_EC2_2016_13TeV",
  "CMS_scale_j_RelativeSample_2016_13TeV",
  "CMS_scale_j_BBEC1_2016_13TeV"
};

std::vector<TString> systematicsJES_2017 = {
  "CMS_scale_j_Absolute_2017_13TeV",
  "CMS_scale_j_HF_2017_13TeV",
  "CMS_scale_j_EC2_2017_13TeV",
  "CMS_scale_j_RelativeSample_2017_13TeV",
  "CMS_scale_j_BBEC1_2017_13TeV"
};

std::vector<TString> systematicsJES_2018 = {
  "CMS_scale_j_Absolute_2018_13TeV",
  "CMS_scale_j_HF_2018_13TeV",
  "CMS_scale_j_EC2_2018_13TeV",
  "CMS_scale_j_RelativeSample_2018_13TeV",
  "CMS_scale_j_BBEC1_2018_13TeV"
};

std::vector<TString> systematicsTotalJES = {
  "CMS_scale_j_JES_13TeV"
};

std::vector<TString> systematicsJES = {
  "CMS_scale_j_FlavorQCD_13TeV",
  "CMS_scale_j_RelativeBal_13TeV",
  "CMS_scale_j_HF_13TeV",
  "CMS_scale_j_BBEC1_13TeV",
  "CMS_scale_j_EC2_13TeV",
  "CMS_scale_j_Absolute_13TeV"  
};

std::vector<TString> systematics = {
  "CMS_res_j_13TeV",
  "CMS_scale_met_unclustered_13TeV"
};

std::vector<TString> systematics_em = {
  "CMS_scale_e_13TeV"
};

const map<TString , TString> process_map_2018 = {
  //  { "WJets"   , "WJetsToLNu_amcatnlo"},
  //  { "W0Jets"  , "WJetsToLNu_0J_amcatnlo"},
  //  { "W1Jets"  , "WJetsToLNu_1J_amcatnlo"},
  //  { "W2Jets"  , "WJetsToLNu_2J_amcatnlo"},

  { "WJets"   , "WJetsToLNu"},
  { "W1Jets"  , "W1JetsToLNu"},
  { "W2Jets"  , "W2JetsToLNu"},
  { "W3Jets"  , "W3JetsToLNu"},
  { "W4Jets"  , "W4JetsToLNu"},

  { "DYJets"  , "DYJetsToLL_M-50_amcatnlo"},
  { "DY0Jets" , "DYJetsToLL_0J_amcatnlo"},
  { "DY1Jets" , "DYJetsToLL_1J_amcatnlo"},
  { "DY2Jets" , "DYJetsToLL_2J_amcatnlo"}
};

const map<TString , TString> process_map_2017 = {
  //  { "WJets"   , "WJetsToLNu_amcatnlo"},
  //  { "W0Jets"  , "WJetsToLNu_0J_amcatnlo"},
  //  { "W1Jets"  , "WJetsToLNu_1J_amcatnlo"},
  //  { "W2Jets"  , "WJetsToLNu_2J_amcatnlo"},

  { "WJets"   , "WJetsToLNu"},
  { "W1Jets"  , "W1JetsToLNu"},
  { "W2Jets"  , "W2JetsToLNu"},
  { "W3Jets"  , "W3JetsToLNu"},
  { "W4Jets"  , "W4JetsToLNu"},

  { "DYJets"  , "DYJetsToLL_M-50_amcatnlo"},
  { "DY0Jets" , "DYJetsToLL_0J_amcatnlo"},
  { "DY1Jets" , "DYJetsToLL_1J_amcatnlo"},
  { "DY2Jets" , "DYJetsToLL_2J_amcatnlo"}
};

const map<TString , TString> process_map_2016 = {
  //  { "WJets"   , "WJetsToLNu_amcatnlo"},
  //  { "W0Jets"  , "WJetsToLNu_0J_amcatnlo"},
  //  { "W1Jets"  , "WJetsToLNu_1J_amcatnlo"},
  //  { "W2Jets"  , "WJetsToLNu_2J_amcatnlo"},

  { "WJets"   , "WJetsToLNu"},
  { "W1Jets"  , "W1JetsToLNu"},
  { "W2Jets"  , "W2JetsToLNu"},
  { "W3Jets"  , "W3JetsToLNu"},
  { "W4Jets"  , "W4JetsToLNu"},

  { "DYJets"  , "DYJetsToLL_M-50_amcatnlo"},
  { "DY0Jets" , "DYJetsToLL_0J_amcatnlo"},
  { "DY1Jets" , "DYJetsToLL_1J_amcatnlo"},
  { "DY2Jets" , "DYJetsToLL_2J_amcatnlo"}
};

std::map<TString,double> LUMI = {
  {"2016",     36330},
  {"2016_pre", 19520},
  {"2016_post",16810},
  {"2017",     41480},
  {"2018",     59830}
};

double getNEventsProcessed(TString filename)
{
  TFile * file = new TFile(filename);
  TH1D * nWeightedEvents = (TH1D*)file->Get("nWeightedEvents");
  if(!nWeightedEvents){
    cout << endl << endl << "Histogram nWeightedEvents doesn't exist in the file "<< filename <<". Quit program." << endl << endl;
    exit(-1);
  }
  double nevents = nWeightedEvents->GetSumOfWeights();
  file -> Close();
  delete file;
  return nevents;
}


#endif
