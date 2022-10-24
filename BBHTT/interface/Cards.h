#ifndef DataCards_h
#define DataCards_h

#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TFile.h"
#include "TList.h"
#include "TString.h"
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

  TString mcNotTauTau;
  TString mcTauTau;
  const TString BaseTreeName = "TauCheck"; 
  TString baselineTT="trg_doubletau>0.5&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.5&&pt_1>40.&&pt_2>40.&&byVVLooseDeepTau2017v2p1VSe_1>0.5&&byVLooseDeepTau2017v2p1VSmu_1>0.5&&byVVLooseDeepTau2017v2p1VSe_2>0.5&&byVLooseDeepTau2017v2p1VSmu_2>0.5&&os>0.5";
  TString baselineEM="((trg_muhigh_elow >0.5 && pt_2 > 24) || (trg_ehigh_mulow >0.5&& pt_1 > 24))&&iso_1<0.15&&iso_2<0.2&&dr_tt>0.5&&pt_1>15.&&pt_2>15.&&extraelec_veto < 0.5&&extramuon_veto<0.5";
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

  const map<TString,TString> WeightSystematicsTT = {
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

  const map<TString,TString> QCDSystematics = {
    {"CMS_htt_em_qcd_0jet_rate","qcdweight_deltaR_0jet_Par0"},
    {"CMS_htt_em_qcd_0jet_shape","qcdweight_deltaR_0jet_Par1"},
    {"CMS_htt_em_qcd_0jet_shape2","qcdweight_deltaR_0jet_Par2"},
    {"CMS_htt_em_qcd_1jet_rate","qcdweight_deltaR_1jet_Par0"},
    {"CMS_htt_em_qcd_1jet_shape","qcdweight_deltaR_1jet_Par1"},
    {"CMS_htt_em_qcd_1jet_shape2","qcdweight_deltaR_1jet_Par2"},
    {"CMS_htt_em_qcd_2jet_rate","qcdweight_deltaR_2jet_Par0"},
    {"CMS_htt_em_qcd_2jet_shape","qcdweight_deltaR_2jet_Par1"},
    {"CMS_htt_em)qcd_2jet_shape2","qcdweight_deltaR_0jet_Par2"},
  };

  const map<TString,TString> FakeFactorSystematics = {
    {"CMS_htt_tt_qcd_stat_dR_unc1","ff_qcd_stat_dR_unc1"},
    {"CMS_htt_tt_qcd_stat_dR_unc2","ff_qcd_stat_dR_unc2"},    
    {"CMS_htt_tt_qcd_stat_pt_unc1","ff_qcd_stat_pt_unc1"},
    {"CMS_htt_tt_qcd_stat_pt_unc2","ff_qcd_stat_pt_unc2"},
    {"CMS_htt_tt_qcd_syst","ff_qcd_syst"},
    {"CMS_htt_tt_qcd_syst_dr_closure","ff_qcd_syst_dr_closure"},
    {"CMS_htt_tt_qcd_syst_pt_2_closure","ff_qcd_syst_pt_2_closure"},
    {"CMS_htt_tt_qcd_syst_met_closur","ff_qcd_syst_met_closure"},
  };

  const map<TString,TString> QCDIsoSystematics = {
    {"CMS_htt_em_qcd_iso","qcdweight_isolationcorrection"},
    {"CMS_htt_em_qcd_nonClosure","qcdweight_nonclosure"},
  };

  const map<TString,TString> SignalSystematics = {
    {"CMS_QCDscale","weight_CMS_scale_gg_13TeV"},
    //    {"CMS_PS_ISR","weight_CMS_PS_ISR_ggH_13TeV"},
    //    {"CMS_PS_FSR","weight_CMS_PS_FSR_ggH_13TeV"},
  };

  // ******************************************************* 
  // ************* CLASS VARIABLES *************************
  // *******************************************************

  map<TString, TString> weightSystematicsMap;
  map<TString, TString> shapeSystematicsMap;
  map<TString, TFile*> sampleFileMap; // sample-file map
  map<TString, TFile*> samplePredFileMap; // sample-friend map
  //  map<TString, TString> baseNameMap; // sample-baseName map
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

  TString sampleToProcess;
  TString input_dir; // includes era
  TString input_friend_dir; // input friend 
  TString output_filename; // outputdir + era / sampleToProcess + Category;
  TFile * outputFile; 

  const std::vector<TString> Tau = {"Tau"};
  const std::vector<TString> MuonEG = {"MuonEG"};
  const std::vector<TString> DYJets = {"DYJets_amcatnlo"};
  const std::vector<TString> WJets  = {"WJets"};
  const std::vector<TString> VV = {"Diboson"};
  const std::vector<TString> ST = {"SingleTop"};
  const std::vector<TString> TTbar = {"TTbar"};
  const std::vector<TString> ggH = {"GluGluHToTauTau"};
  const std::vector<TString> qqH = {"VBFHToTauTau"};
  const std::vector<TString> WH = {"WHToTauTau"};
  const std::vector<TString> ZH = {"ZHToTauTau"};
  const std::vector<TString> ggHWW = {"GluGluHToWW"};
  const std::vector<TString> qqHWW = {"VBFHToToWW"};
  const std::vector<TString> WHWW  = {"WHToWW"};
  const std::vector<TString> ZHWW  = {"ZHToWW"};
  const std::vector<TString> bbH_yt2 = {"BBHToTauTau_YT2"};
  const std::vector<TString> bbH_yb2 = {"BBHToTauTau_YB2"};
  const std::vector<TString> bbH_ybyt = {"BBHToTauTau_YBYT"};
  const std::vector<TString> bbH = {"BBHToTauTau_YT2","BBHToTauTau_YB2","BBHToTauTau_YBYT"};

  const std::vector<TString> availableSamplesToProcess = 
    {"Data","DYJets","EWK","Top","HTT","HWW","bbHTT","bbHTT_nobb"};

  map<TString,TString> mapAvailableSamples = 
    {
      {"Data","data and QCD (fakes) background templates"},
      {"EWK","diboson and WJets MC templates"},
      {"Top","ttbar and single-top templates"},
      {"DYJets","ZTT and ZL templates"},
      {"HTT","ggHTT, qqHTT, WHTT and ZHTT templates"},
      {"HWW","ggHWW, qqHWW, WHWW and ZHWW templates"},
      {"bbHTT","bbHTT_yb2, bbHTT_yt2, bbHTT_ybyt and sum"},
      {"bbHTT_nobb","bbHTT_yb2, bbHTT_ybyt with no b-quarks"},
    };

  const std::vector<TString> availableCategories = {
    "inclusive","Nbtag0","NbtagGe1",
    "cat0"       ,  "cat1",         "cat2",         "cat3",
    "cat0_Nbtag0",  "cat1_Nbtag0",  "cat2_Nbtag0",  "cat3_Nbtag0",
    "cat0_NBtagGe1","cat1_NbtagGe1","cat2_NbtagGe1","cat3_NbtagGe1"
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


};

#endif
