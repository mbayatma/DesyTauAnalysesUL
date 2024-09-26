#ifndef DataCards_h
#define DataCards_h

#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TFile.h"
#include "TList.h"
#include "TString.h"
#include "TMath.h"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

// Samples :
// Data - data_obs (Tau or MuonEG)
// DYJetsToLL - ZL
// DYJetsToTT - ZTT
// WJets    - W
// TTbarToL - TTL
// TTbar    - TT
// EWKToL   - VVL
// EWK      - VV
// ggHWW - ggHWW125 
// qqHWW - qqHWW125 
// WHWW  - WHWW125
// ZHWW  - ZHWW125
// ggH   - ggH125
// qqH   - 
// WH125,
// ZH125,  
// bbHyt2
// bbHyb2
//  

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
	bool split,
	bool RunOnEmbedded,
	int sym,
	bool MassCuts); 

  void SetVariableToPlot(TString var, int nbins, double xmin, double xmax);
  void SetVariableToPlot(TString var, int nbins, double * bins);
  void SetVariableToPlot(TString var, int nbins, vector<double> bins);
  void SetVariableToPlot(TString var, vector<double> bins, vector<double> bins2);

  bool Run();
  bool CloseFile();
  void PrintSamples();
  void PrintShapeSystematics();
  void PrintWeightSystematics();
  void SetSmoothing(int min, int max, int range);
  void SetLooseShape(bool shape);
  void SetSplitJES(bool split);
  void Rebin(bool rebinHisto, vector<double> bins);
  ~Cards();

 private:

  int min_smooth;
  int max_smooth;
  int range_smooth;
  bool massCuts;

  std::vector<TString> shapeList;

  bool useLooseShape;
  bool rebin;
  bool splitJES;
  int symmetrize;

  TString mcNotTauTau;
  TString mcTauTau;
  const TString BaseTreeName = "TauCheck"; 
  TString baselineTT="trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5&&os>0.5";
  TString baselineEM="((trg_muhigh_elow >0.5 && pt_2 > 24) || (trg_ehigh_mulow >0.5&& pt_1 > 24))&&dr_tt>0.5&&pt_1>15.&&pt_2>15.&&extraelec_veto<0.5&&extramuon_veto<0.5&&nbtag<3&&pzeta<20.";

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

  const TString sameSignRegion = "&&os<0.5&&iso_1<0.15&&iso_2<0.2";
  const TString oppositeSignRegion = "&&os>0.5&&iso_1<0.15&&iso_2<0.2";
  const TString sameSignAntiIsoRegion = "&&os<0.5&&iso_1>0.05&&iso_1<0.25&&iso_2>0.05&&iso_2<0.25";
  const TString sameSignLooseIsoRegion = "&&os<0.5&&iso_1<0.3&&iso_2<0.3";

  vector<TString> regionCut;    // three regions defined (SR, fake AR, single fake region)
  vector<TString> regionWeight; // three regions defined 

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

  const map<TString,TString> ShapeSystematicsJESCommon = {
    {"jesFlavorQCD","CMS_scale_j_FlavorQCD_13TeV"},
    {"jesRelativeBal","CMS_scale_j_RelativeBal_13TeV"},
    {"jesHF","CMS_scale_j_HF_13TeV"},
    {"jesBBEC1","CMS_scale_j_BBEC1_13TeV"},
    {"jesEC2","CMS_scale_j_EC2_13TeV"},
    {"jesAbsolute","CMS_scale_j_Absolute_13TeV"},    
  };

  const map<TString,TString> ShapeSystematicsJES2016 = {
    {"jesAbsolute_2016","CMS_scale_j_Absolute_2016_13TeV"},
    {"jesHF_2016","CMS_scale_j_HF_2016_13TeV"},
    {"jesEC2_2016","CMS_scale_j_EC2_2016_13TeV"},
    {"jesRelativeSample_2016","CMS_scale_j_RelativeSample_2016_13TeV"},
    {"jesBBEC1_2016","CMS_scale_j_BBEC1_2016_13TeV"}
  };  

  const map<TString,TString> ShapeSystematicsJES2017 = {
    {"jesAbsolute_2017","CMS_scale_j_Absolute_2017_13TeV"},
    {"jesHF_2017","CMS_scale_j_HF_2017_13TeV"},
    {"jesEC2_2017","CMS_scale_j_EC2_2017_13TeV"},
    {"jesRelativeSample_2017","CMS_scale_j_RelativeSample_2017_13TeV"},
    {"jesBBEC1_2017","CMS_scale_j_BBEC1_2017_13TeV"},
  };  

  const map<TString,TString> ShapeSystematicsJES2018 = {
    {"jesAbsolute_2018","CMS_scale_j_Absolute_2018_13TeV"},
    {"jesHF_2018","CMS_scale_j_HF_2018_13TeV"},
    {"jesEC2_2018","CMS_scale_j_EC2_2018_13TeV"},
    {"jesRelativeSample_2018","CMS_scale_j_RelativeSample_2018_13TeV"},
    {"jesBBEC1_2018","CMS_scale_j_BBEC1_2018_13TeV"},
  };  

  const map<TString,TString> ShapeSystematicsJES_TT2018 = {
    {"jesAbsolute_2018","CMS_scale_j_BBEC1_2018_13TeV"},
    {"jesHF_2018","CMS_scale_j_HF_2018_13TeV"},
    {"jesEC2_2018","CMS_scale_j_EC2_2018_13TeV"},
    {"jesRelativeSample_2018","CMS_scale_j_HF_2018_13TeV"},
    {"jesBBEC1_2018","CMS_scale_j_Absolute_2018_13TeV"},
  };

  const map<TString,TString> ShapeSystematicsTT = {
    {"scale_t_1prong","CMS_scale_t_1prong_13TeV"},
    {"scale_t_1prong1pi","CMS_scale_t_1prong1pizero_13TeV"},
    {"scale_t_3prong","CMS_scale_t_3prong_13TeV"},
    {"scale_t_3prong1pi","CMS_scale_t_3prong1pizero_13TeV"},
    {"met_unclustered","CMS_scale_met_unclustered_13TeV"},
    {"jer","CMS_res_j_13TeV"},
  };

  const map<TString,TString> ShapeSystematicsJESTotal = {
    {"jesTotal","CMS_scale_j_JES_13TeV"}
  };

  const map<TString,TString> ShapeSystematicsEM = {
    {"met_unclustered","CMS_scale_met_unclustered_13TeV"},
    {"jer","CMS_res_j_13TeV"},
  };

  // ******************************
  // *** Weight systematics *******
  // ******************************

  const map<TString,TString> PrefiringSystematics = {
    {"prefiringUp","(prefiringweightUp/prefiringweight)"},
    {"prefiringDown","(prefiringweightDown/prefiringweight)"},    
  };

  const map<TString,TString> DYShapeSystematics = {
    {"dyShape","zptweight"},
    {"dyShape1b","zptweight_1btag"},
    {"dyShape2b","zptweight_2btag"},
    {"dyxsec1b","zptweight_tt_1btag"},
    {"dyxsec2b","zptweight_tt_2btag"}
  };

  const map<TString,TString> TopShapeSystematics = {
    {"ttbarShape","topptweight"},
  };

  const map<TString,TString> WeightSystematicsTT = {
    {"CMS_eff_xtrigger_t_tt_dm0","weight_CMS_eff_tau_trig_DM0"},
    {"CMS_eff_xtrigger_t_tt_dm1","weight_CMS_eff_tau_trig_DM1"},
    {"CMS_eff_xtrigger_t_tt_dm10","weight_CMS_eff_tau_trig_DM10"},
    {"CMS_eff_xtrigger_t_tt_dm11","weight_CMS_eff_tau_trig_DM11"},
    {"CMS_eff_t_1prong","weight_CMS_eff_tauid_DM0"},
    {"CMS_eff_t_1prong1pi","weight_CMS_eff_tauid_DM1"},
    {"CMS_eff_t_3prong","weight_CMS_eff_tauid_DM10"},
    //    {"CMS_eff_t_dm11","weight_CMS_eff_tauid_DM11"},
    {"fake_e_tt","weight_CMS_etaufake"},
    {"fake_m_tt","weight_CMS_mutaufake"}
  };

  const map<TString,TString> EmbeddedWeightSystematicsTT = {
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

  const map<TString,TString> BTagSystematics = {
    //    {"jes","btagweight_jes"},
    {"lf","btagweight_lf"},
    {"hf","btagweight_hf"},
    {"hfstats1","btagweight_hfstats1"},
    {"hfstats2","btagweight_hfstats2"},
    {"lfstats1","btagweight_lfstats1"},
    {"lfstats2","btagweight_lfstats2"},
    {"cferr1","btagweight_cferr1"},
    {"cferr2","btagweight_cferr2"}
  };

  const map<TString,TString> BTagSystematics2016 = {
    {"2016_preVFP_hfstats1","btagweight_hfstats1_2016pre"},
    {"2016_preVFP_hfstats2","btagweight_hfstats2_2016pre"},
    {"2016_preVFP_lfstats1","btagweight_lfstats1_2016pre"},
    {"2016_preVFP_lfstats2","btagweight_lfstats2_2016pre"},
    {"2016_postVFP_hfstats1","btagweight_hfstats1_2016post"},
    {"2016_postVFP_hfstats2","btagweight_hfstats2_2016post"},
    {"2016_postVFP_lfstats1","btagweight_lfstats1_2016post"},
    {"2016_postVFP_lfstats2","btagweight_lfstats2_2016post"}
  };


  const map<TString,TString> LeptonFakeSystematics = {
    {"CMS_htt_em_JetToElecFakes","jfakeE"},
    {"CMS_htt_em_JetToMuonFakes","jfakeMu"},
    {"CMS_htt_em_BJetToElecFakes","bfakeE"},
    {"CMS_htt_em_BJetToMuonFakes","bfakeMu"},
  };

  const map<TString,TString> QCDSystematics = {
    {"CMS_htt_em_qcd_0jet_rate","qcdweight_deltaR_0jet_Par0"},
    {"CMS_htt_em_qcd_0jet_shape1","qcdweight_deltaR_0jet_Par1"},
    {"CMS_htt_em_qcd_0jet_shape2","qcdweight_deltaR_0jet_Par2"},
    {"CMS_htt_em_qcd_1jet_rate","qcdweight_deltaR_1jet_Par0"},
    {"CMS_htt_em_qcd_1jet_shape1","qcdweight_deltaR_1jet_Par1"},
    {"CMS_htt_em_qcd_1jet_shape2","qcdweight_deltaR_1jet_Par2"},
    {"CMS_htt_em_qcd_2jet_rate","qcdweight_deltaR_2jet_Par0"},
    {"CMS_htt_em_qcd_2jet_shape1","qcdweight_deltaR_2jet_Par1"},
    {"CMS_htt_em_qcd_2jet_shape2","qcdweight_deltaR_0jet_Par2"},
  };

  const map<TString,TString> FakeFactorSystematics = {
    {"CMS_htt_tt_qcd_syst_dR_nbtag1","qcd_syst_DR_nbtag1"},
    {"CMS_htt_tt_qcd_syst_dR_nbtag2","qcd_syst_DR_nbtag2"},    

    {"CMS_htt_tt_qcd_stat_dR_nbtag1","ff_qcd_extrap_stat_nbtag1"},
    {"CMS_htt_tt_qcd_stat_dR_nbtag2","ff_qcd_extrap_stat_nbtag2"},    

    {"CMS_htt_tt_qcd_syst_pt_2_closure","ff_qcd_syst_pt_2_closure"},

    {"CMS_htt_tt_qcd_syst_met_njet0_closure","qcd_syst_met_njet0_closure"},
    {"CMS_htt_tt_qcd_syst_met_njet1_closure","qcd_syst_met_njet1_closure"},
    {"CMS_htt_tt_qcd_syst_met_njet2_closure","qcd_syst_met_njet2_closure"},

    {"CMS_htt_tt_qcd_stat_njet0_dm0","ff_qcd_stat_njet0_dm0"},
    {"CMS_htt_tt_qcd_stat_njet0_dm1","ff_qcd_stat_njet0_dm1"},
    {"CMS_htt_tt_qcd_stat_njet0_dm10","ff_qcd_stat_njet0_dm10"},
    {"CMS_htt_tt_qcd_stat_njet0_dm11","ff_qcd_stat_njet0_dm11"},

    {"CMS_htt_tt_qcd_stat_njet1_dm0","ff_qcd_stat_njet1_dm0"},
    {"CMS_htt_tt_qcd_stat_njet1_dm1","ff_qcd_stat_njet1_dm1"},
    {"CMS_htt_tt_qcd_stat_njet1_dm10","ff_qcd_stat_njet1_dm10"},
    {"CMS_htt_tt_qcd_stat_njet1_dm11","ff_qcd_stat_njet1_dm11"},

    {"CMS_htt_tt_qcd_stat_njet2_dm0","ff_qcd_stat_njet2_dm0"},
    {"CMS_htt_tt_qcd_stat_njet2_dm1","ff_qcd_stat_njet2_dm1"},
    {"CMS_htt_tt_qcd_stat_njet2_dm10","ff_qcd_stat_njet2_dm10"},
    {"CMS_htt_tt_qcd_stat_njet2_dm11","ff_qcd_stat_njet2_dm11"},

  };

  const map<TString,TString> QCDIsoSystematics = {
    {"CMS_htt_em_qcd_iso","qcdweight_isolationcorrection"},
    {"CMS_htt_em_qcd_nonClosure","qcdweight_nonclosure"},
  };

  const map<TString,TString> SignalScaleSystematics = {
    {"QCDscaleMURSig","weight_CMS_scale_muR_13TeV"},
    {"QCDscaleMUFSig","weight_CMS_scale_muF_13TeV"},
    {"PS_ISRSig","weight_CMS_PS_ISR_ggH_13TeV"},
    {"PS_FSRSig","weight_CMS_PS_FSR_ggH_13TeV"},
  };

  const map<TString,TString> TTscaleSystematics = {
    {"QCDscaleMURTT","weight_CMS_scale_muR_13TeV"},
    {"QCDscaleMUFTT","weight_CMS_scale_muF_13TeV"},
    {"PS_ISRTT","weight_CMS_PS_ISR_ggH_13TeV"},
    {"PS_FSRTT","weight_CMS_PS_FSR_ggH_13TeV"}
  };

  const map<TString,TString> DYscaleSystematics = {
    {"QCDscaleMURDY","weight_CMS_scale_muR_13TeV"},
    {"QCDscaleMUFDY","weight_CMS_scale_muF_13TeV"},
    {"PS_ISRDY","weight_CMS_PS_ISR_ggH_13TeV"},
    {"PS_FSRDY","weight_CMS_PS_FSR_ggH_13TeV"}
  };


  // ******************************************************* 
  // ************* CLASS VARIABLES *************************
  // *******************************************************

  map<TString, TString> weightSystematicsMap;
  map<TString, TString> shapeSystematicsMap;
  map<TString, TFile*> sampleFileMap; // sample-file map
  map<TString, TFile*> samplePredFileMap; // sample-friend map
  map<TString, vector<TString> > nameSampleMap; // sample map
  map<TString, vector<TString> > sampleSpecificCutMap; // sample-specific-cut map
  map<TString, TString> nameHistoMap;
  map<TString, TH1D*> nameTH1DMap;
  vector<TString> samplesContainer;

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
  // for the rebinned histograms
  int nBins_rebinned;
  double Bins_rebinned[100];

  TString sampleToProcess;
  TString input_dir; // includes era
  TString input_friend_dir; // input friend 
  TString output_filename; // outputdir + era / sampleToProcess + Category;
  TFile * outputFile; 

  const std::vector<TString> Tau = {"Tau"};
  const std::vector<TString> MuonEG = {"MuonEG"};
  const std::vector<TString> DYJets = {"DYJets_amcatnlo"};
  const std::vector<TString> WJets  = {"WJets_amcatnlo"};
  const std::vector<TString> VV = {"Diboson"};
  const std::vector<TString> ST = {"SingleTop"};
  const std::vector<TString> TTbar = {"TTbar"};
  const std::vector<TString> ggH = {"GluGluHToTauTau"};
  const std::vector<TString> qqH = {"VBFHToTauTau"};
  const std::vector<TString> WH = {"WHToTauTau"};
  const std::vector<TString> ZH = {"ZHToTauTau"};
  const std::vector<TString> TTH = {"TTHToTauTau"};
  const std::vector<TString> ggHWW = {"GluGluHToWW"};
  const std::vector<TString> qqHWW = {"VBFHToWW"};
  const std::vector<TString> WHWW  = {"WHToWW"};
  const std::vector<TString> ZHWW  = {"ZHToWW"};
  const std::vector<TString> TTHWW = {"TTHToWW"};
  const std::vector<TString> TTVJets = {"TTVJets"};
  const std::vector<TString> bbH_yt2 =  {"BBHToTauTau_YT2"};
  const std::vector<TString> bbH_yb2 =  {"BBHToTauTau_YB2"};
  const std::vector<TString> bbH_ybyt = {"BBHToTauTau_YBYT"};
  const std::vector<TString> bbHWW_yt2 =  {"BBHToWW_YT2"};
  const std::vector<TString> bbHWW_yb2 =  {"BBHToWW_YB2"};
  const std::vector<TString> bbHWW_ybyt = {"BBHToWW_YBYT"};

  const std::vector<TString> availableSamplesToProcess = 
    {"Data",
     "DYToTT",
     "DYToLL",
     "EWK",
     "TT",
     "ST",
     "HTT",
     "HWW",
     "TTVJets",
     "bbHTT",
     "bbHTT_nobb",
     "bbHWW",
     "bbHWW_nobb"};

  map<TString,TString> mapAvailableSamples = 
    {
      {"Data","data and QCD (fakes) background templates"},
      {"EWK","diboson and WJets MC templates"},
      {"TT","ttbar template"},
      {"ST","single-top template"},
      {"DYToTT","ZTT template"},
      {"DYToLL","ZL template"},
      {"TTVJets","TTZ and TTW templates"},
      {"HTT","ggHTT, qqHTT, WHTT, ZHTT and ttbarHTT templates"},
      {"HWW","ggHWW, qqHWW, WHWW, ZHWW and ttbarHWW templates"},
      {"bbHTT","bbHTT_yb2, bbHTT_yt2, bbHTT_ybyt templates"},
      {"bbHTT_nobb","bbHTT_yb2, bbHTT_ybyt without b-quarks"},
      {"bbHWW","bbHWW_yb2, bbHWW_yt2, bbHWW_ybyt templates"},
      {"bbHWW_nobb","bbHWW_yb2, bbHWW_ybyt without b-quarks"},
    };

  const std::vector<TString> availableCategories = {
    "inclusive","Nbtag0","NbtagGe1",
    "Nbtag0_lowPzeta","NbtagGe1_lowPzeta",
    "Nbtag0_highPzeta","NbtagGe1_highPzeta",
    "Nbtag0_Pzeta1","NbtagGe1_Pzeta1",
    "Nbtag0_Pzeta2","NbtagGe1_Pzeta2",
    "Nbtag0_Pzeta3","NbtagGe1_Pzeta3",
    "cat0"       ,  "cat1",         "cat2",         "cat3",          "cat4",
    "cat0_Nbtag0",  "cat1_Nbtag0",  "cat2_Nbtag0",  "cat3_Nbtag0",   "cat4_Nbtag0",
    "cat0_Nbtag1",  "cat1_Nbtag1",  "cat2_Nbtag1",  "cat3_Nbtag1",   "cat4_Nbtag1",
    "cat0_Nbtag2",  "cat1_Nbtag2",  "cat2_Nbtag2",  "cat3_Nbtag2",   "cat4_Nbtag2",
    "cat0_NbtagGe1","cat1_NbtagGe1","cat2_NbtagGe1","cat3_NbtagGe1", "cat4_NbtagGe1",
    "cat5_NbtagGe1","cat6_NbtagGe1"
  };

  TString globalWeight="xsec_lumi_weight*";
  TString qcdWeight="qcdweight*";
  TString FFWeight="ff_total*";
  TString commonCuts;
  TString era;
  TString channel;

  bool block;
  bool isBTag;
  bool isEquidistantBinning;
  bool runWithSystematics;
  bool runWithShapeSystematics;
  bool runOnEmbedded;
  bool _usefriend;

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
  void smooth(TH1D * hist);

};

#endif
