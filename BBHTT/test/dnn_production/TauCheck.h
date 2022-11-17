//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 17 12:48:40 2022 by ROOT version 6.14/09
// from TTree TauCheck/TauCheck
// found on file: /nfs/dust/cms/user/rasp/Run/tautau_UL/2016_post/Tau_Run2016F.root
//////////////////////////////////////////////////////////

#ifndef TauCheck_h
#define TauCheck_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TauCheck {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          lumi;
   ULong64_t       evt;
   Int_t           npv;
   Float_t         npu;
   Float_t         rho;
   Float_t         weight_CMS_eff_tauidUp;
   Float_t         weight_CMS_eff_tauidDown;
   Float_t         weight_CMS_eff_tauid_DM0Up;
   Float_t         weight_CMS_eff_tauid_DM0Down;
   Float_t         weight_CMS_eff_tauid_DM1Up;
   Float_t         weight_CMS_eff_tauid_DM1Down;
   Float_t         weight_CMS_eff_tauid_DM10Up;
   Float_t         weight_CMS_eff_tauid_DM10Down;
   Float_t         weight_CMS_eff_tauid_DM11Up;
   Float_t         weight_CMS_eff_tauid_DM11Down;
   Float_t         weight_CMS_eff_tau_trigUp;
   Float_t         weight_CMS_eff_tau_trigDown;
   Float_t         weight_CMS_eff_tau_trig_DM0Up;
   Float_t         weight_CMS_eff_tau_trig_DM0Down;
   Float_t         weight_CMS_eff_tau_trig_DM1Up;
   Float_t         weight_CMS_eff_tau_trig_DM1Down;
   Float_t         weight_CMS_eff_tau_trig_DM10Up;
   Float_t         weight_CMS_eff_tau_trig_DM10Down;
   Float_t         weight_CMS_eff_tau_trig_DM11Up;
   Float_t         weight_CMS_eff_tau_trig_DM11Down;
   Float_t         weight_CMS_mutaufakeUp;
   Float_t         weight_CMS_mutaufakeDown;
   Float_t         ff_qcd_stat_unc1_njet0_dm0;
   Float_t         ff_qcd_stat_unc1_njet0_dm1;
   Float_t         ff_qcd_stat_unc1_njet0_dm10;
   Float_t         ff_qcd_stat_unc1_njet0_dm11;
   Float_t         ff_qcd_stat_unc1_njet1_dm0;
   Float_t         ff_qcd_stat_unc1_njet1_dm1;
   Float_t         ff_qcd_stat_unc1_njet1_dm10;
   Float_t         ff_qcd_stat_unc1_njet1_dm11;
   Float_t         ff_qcd_stat_unc1_njet2_dm0;
   Float_t         ff_qcd_stat_unc1_njet2_dm1;
   Float_t         ff_qcd_stat_unc1_njet2_dm10;
   Float_t         ff_qcd_stat_unc1_njet2_dm11;
   Float_t         ff_qcd_stat_unc2_njet0_dm0;
   Float_t         ff_qcd_stat_unc2_njet0_dm1;
   Float_t         ff_qcd_stat_unc2_njet0_dm10;
   Float_t         ff_qcd_stat_unc2_njet0_dm11;
   Float_t         ff_qcd_stat_unc2_njet1_dm0;
   Float_t         ff_qcd_stat_unc2_njet1_dm1;
   Float_t         ff_qcd_stat_unc2_njet1_dm10;
   Float_t         ff_qcd_stat_unc2_njet1_dm11;
   Float_t         ff_qcd_stat_unc2_njet2_dm0;
   Float_t         ff_qcd_stat_unc2_njet2_dm1;
   Float_t         ff_qcd_stat_unc2_njet2_dm10;
   Float_t         ff_qcd_stat_unc2_njet2_dm11;
   Float_t         ff_qcd_met;
   Float_t         ff_qcd_syst;
   Float_t         ff_qcd_pt2;
   Float_t         jleppt_1;
   Float_t         jlepeta_1;
   Float_t         jlepphi_1;
   Float_t         jleppt_2;
   Float_t         jlepeta_2;
   Float_t         jlepphi_2;
   Bool_t          passedAllMetFilters;
   Float_t         pt_1;
   Float_t         phi_1;
   Float_t         eta_1;
   Float_t         m_1;
   Int_t           gen_match_1;
   Int_t           q_1;
   Float_t         iso_1;
   Float_t         d0_1;
   Float_t         dZ_1;
   Float_t         pt_uncorr_1;
   Float_t         mt_1;
   Float_t         puppimt_1;
   Int_t           tau_decay_mode_1;
   Float_t         dm_1;
   Float_t         dmMVA_1;
   Float_t         pt_2;
   Float_t         phi_2;
   Float_t         eta_2;
   Float_t         m_2;
   Int_t           gen_match_2;
   Int_t           q_2;
   Float_t         iso_2;
   Float_t         pt_uncorr_2;
   Float_t         d0_2;
   Float_t         dZ_2;
   Float_t         mt_2;
   Float_t         puppimt_2;
   Int_t           tau_decay_mode_2;
   Float_t         dm_2;
   Float_t         dmMVA_2;
   Float_t         deepTauVsEleRaw_1;
   Float_t         deepTauVsJetRaw_1;
   Float_t         deepTauVsMuRaw_1;
   Float_t         byLooseDeepTau2017v2p1VSe_1;
   Float_t         byLooseDeepTau2017v2p1VSjet_1;
   Float_t         byLooseDeepTau2017v2p1VSmu_1;
   Float_t         byMediumDeepTau2017v2p1VSe_1;
   Float_t         byMediumDeepTau2017v2p1VSjet_1;
   Float_t         byMediumDeepTau2017v2p1VSmu_1;
   Float_t         byTightDeepTau2017v2p1VSe_1;
   Float_t         byTightDeepTau2017v2p1VSjet_1;
   Float_t         byTightDeepTau2017v2p1VSmu_1;
   Float_t         byVLooseDeepTau2017v2p1VSe_1;
   Float_t         byVLooseDeepTau2017v2p1VSjet_1;
   Float_t         byVLooseDeepTau2017v2p1VSmu_1;
   Float_t         byVTightDeepTau2017v2p1VSe_1;
   Float_t         byVTightDeepTau2017v2p1VSjet_1;
   Float_t         byVVLooseDeepTau2017v2p1VSe_1;
   Float_t         byVVLooseDeepTau2017v2p1VSjet_1;
   Float_t         byVVTightDeepTau2017v2p1VSe_1;
   Float_t         byVVTightDeepTau2017v2p1VSjet_1;
   Float_t         byVVVLooseDeepTau2017v2p1VSe_1;
   Float_t         byVVVLooseDeepTau2017v2p1VSjet_1;
   Float_t         deepTauVsEleRaw_2;
   Float_t         deepTauVsJetRaw_2;
   Float_t         deepTauVsMuRaw_2;
   Float_t         byLooseDeepTau2017v2p1VSe_2;
   Float_t         byLooseDeepTau2017v2p1VSjet_2;
   Float_t         byLooseDeepTau2017v2p1VSmu_2;
   Float_t         byMediumDeepTau2017v2p1VSe_2;
   Float_t         byMediumDeepTau2017v2p1VSjet_2;
   Float_t         byMediumDeepTau2017v2p1VSmu_2;
   Float_t         byTightDeepTau2017v2p1VSe_2;
   Float_t         byTightDeepTau2017v2p1VSjet_2;
   Float_t         byTightDeepTau2017v2p1VSmu_2;
   Float_t         byVLooseDeepTau2017v2p1VSe_2;
   Float_t         byVLooseDeepTau2017v2p1VSjet_2;
   Float_t         byVLooseDeepTau2017v2p1VSmu_2;
   Float_t         byVTightDeepTau2017v2p1VSe_2;
   Float_t         byVTightDeepTau2017v2p1VSjet_2;
   Float_t         byVVLooseDeepTau2017v2p1VSe_2;
   Float_t         byVVLooseDeepTau2017v2p1VSjet_2;
   Float_t         byVVTightDeepTau2017v2p1VSe_2;
   Float_t         byVVTightDeepTau2017v2p1VSjet_2;
   Float_t         byVVVLooseDeepTau2017v2p1VSe_2;
   Float_t         byVVVLooseDeepTau2017v2p1VSjet_2;
   Float_t         embweight;
   Float_t         idisoweight_1;
   Float_t         trkeffweight_1;
   Float_t         idisoweight_2;
   Float_t         trkeffweight_2;
   Float_t         trigweight_1;
   Float_t         trigweight_antiiso_1;
   Float_t         idisoweight_antiiso_1;
   Float_t         trigweight_2;
   Float_t         trigweight_2_Up;
   Float_t         trigweight_2_Down;
   Float_t         trigweight_l_lt;
   Float_t         trigweight_t_lt;
   Float_t         trigweight_antiiso_2;
   Float_t         idisoweight_antiiso_2;
   Float_t         weight_CMS_scale_gg_13TeVUp;
   Float_t         weight_CMS_scale_gg_13TeVDown;
   Float_t         weight_CMS_PS_ISR_ggH_13TeVUp;
   Float_t         weight_CMS_PS_ISR_ggH_13TeVDown;
   Float_t         weight_CMS_PS_FSR_ggH_13TeVUp;
   Float_t         weight_CMS_PS_FSR_ggH_13TeVDown;
   Float_t         weight;
   Float_t         mcweight;
   Float_t         puweight;
   Float_t         trigweight;
   Float_t         prefiringweight;
   Float_t         prefiringweightUp;
   Float_t         prefiringweightDown;
   Float_t         topptweight;
   Double_t        zptweight;
   Double_t        zptembweight;
   Float_t         effweight;
   Float_t         btagweight;
   Float_t         ff_nom;
   Float_t         ff_nom_sys;
   Bool_t          trg_singlemuon;
   Bool_t          trg_singleelectron;
   Bool_t          trg_doubletau;
   Float_t         met;
   Float_t         metphi;
   Float_t         metcov00;
   Float_t         metcov01;
   Float_t         metcov10;
   Float_t         metcov11;
   Float_t         pzetavis;
   Float_t         pzetamiss;
   Float_t         pzeta;
   Float_t         puppimet;
   Float_t         puppimetphi;
   Float_t         puppimetcov00;
   Float_t         puppimetcov01;
   Float_t         puppimetcov10;
   Float_t         puppimetcov11;
   Float_t         pt_tt;
   Float_t         dr_tt;
   Float_t         m_vis;
   Float_t         mt_tot;
   Float_t         m_sv;
   Float_t         pt_sv;
   Float_t         eta_sv;
   Float_t         phi_sv;
   Float_t         met_sv;
   Float_t         mt_sv;
   Int_t           njets;
   Int_t           nbtag;
   Int_t           gen_nbjets_cut;
   Int_t           gen_nbjets;
   Float_t         jpt_1;
   Float_t         jeta_1;
   Float_t         jphi_1;
   Float_t         jpt_2;
   Float_t         jeta_2;
   Float_t         jphi_2;
   Float_t         mjj;
   Float_t         jdeta;
   Float_t         dijetpt;
   Float_t         dijeteta;
   Float_t         dijetphi;
   Float_t         jdphi;
   Float_t         bpt_1;
   Float_t         beta_1;
   Float_t         bpt_2;
   Float_t         beta_2;
   Float_t         jcsv_1;
   Float_t         jcsv_2;
   Float_t         bphi_1;
   Float_t         bcsv_1;
   Float_t         bphi_2;
   Float_t         bcsv_2;
   Float_t         mbb;
   Float_t         dRbb;
   Int_t           gen_noutgoing;
   Int_t           os;
   Int_t           dilepton_veto;
   Int_t           extraelec_veto;
   Int_t           extramuon_veto;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_weight_CMS_eff_tauidUp;   //!
   TBranch        *b_weight_CMS_eff_tauidDown;   //!
   TBranch        *b_weight_CMS_eff_tauid_DM0Up;   //!
   TBranch        *b_weight_CMS_eff_tauid_DM0Down;   //!
   TBranch        *b_weight_CMS_eff_tauid_DM1Up;   //!
   TBranch        *b_weight_CMS_eff_tauid_DM1Down;   //!
   TBranch        *b_weight_CMS_eff_tauid_DM10Up;   //!
   TBranch        *b_weight_CMS_eff_tauid_DM10Down;   //!
   TBranch        *b_weight_CMS_eff_tauid_DM11Up;   //!
   TBranch        *b_weight_CMS_eff_tauid_DM11Down;   //!
   TBranch        *b_weight_CMS_eff_tau_trigUp;   //!
   TBranch        *b_weight_CMS_eff_tau_trigDown;   //!
   TBranch        *b_weight_CMS_eff_tau_trig_DM0Up;   //!
   TBranch        *b_weight_CMS_eff_tau_trig_DM0Down;   //!
   TBranch        *b_weight_CMS_eff_tau_trig_DM1Up;   //!
   TBranch        *b_weight_CMS_eff_tau_trig_DM1Down;   //!
   TBranch        *b_weight_CMS_eff_tau_trig_DM10Up;   //!
   TBranch        *b_weight_CMS_eff_tau_trig_DM10Down;   //!
   TBranch        *b_weight_CMS_eff_tau_trig_DM11Up;   //!
   TBranch        *b_weight_CMS_eff_tau_trig_DM11Down;   //!
   TBranch        *b_weight_CMS_mutaufakeUp;   //!
   TBranch        *b_weight_CMS_mutaufakeDown;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet0_dm0;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet0_dm1;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet0_dm10;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet0_dm11;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet1_dm0;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet1_dm1;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet1_dm10;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet1_dm11;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet2_dm0;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet2_dm1;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet2_dm10;   //!
   TBranch        *b_ff_qcd_stat_unc1_njet2_dm11;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet0_dm0;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet0_dm1;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet0_dm10;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet0_dm11;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet1_dm0;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet1_dm1;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet1_dm10;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet1_dm11;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet2_dm0;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet2_dm1;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet2_dm10;   //!
   TBranch        *b_ff_qcd_stat_unc2_njet2_dm11;   //!
   TBranch        *b_ff_qcd_met;   //!
   TBranch        *b_ff_qcd_syst;   //!
   TBranch        *b_ff_qcd_pt2;   //!
   TBranch        *b_jleppt_1;   //!
   TBranch        *b_jlepeta_1;   //!
   TBranch        *b_jlepphi_1;   //!
   TBranch        *b_jleppt_2;   //!
   TBranch        *b_jlepeta_2;   //!
   TBranch        *b_jlepphi_2;   //!
   TBranch        *b_passedAllMetFilters;   //!
   TBranch        *b_pt_1;   //!
   TBranch        *b_phi_1;   //!
   TBranch        *b_eta_1;   //!
   TBranch        *b_m_1;   //!
   TBranch        *b_gen_match_1;   //!
   TBranch        *b_q_1;   //!
   TBranch        *b_iso_1;   //!
   TBranch        *b_d0_1;   //!
   TBranch        *b_dZ_1;   //!
   TBranch        *b_pt_uncorr_1;   //!
   TBranch        *b_mt_1;   //!
   TBranch        *b_puppimt_1;   //!
   TBranch        *b_tau_decay_mode_1;   //!
   TBranch        *b_dm_1;   //!
   TBranch        *b_dmMVA_1;   //!
   TBranch        *b_pt_2;   //!
   TBranch        *b_phi_2;   //!
   TBranch        *b_eta_2;   //!
   TBranch        *b_m_2;   //!
   TBranch        *b_gen_match_2;   //!
   TBranch        *b_q_2;   //!
   TBranch        *b_iso_2;   //!
   TBranch        *b_pt_uncorr_2;   //!
   TBranch        *b_d0_2;   //!
   TBranch        *b_dZ_2;   //!
   TBranch        *b_mt_2;   //!
   TBranch        *b_puppimt_2;   //!
   TBranch        *b_tau_decay_mode_2;   //!
   TBranch        *b_dm_2;   //!
   TBranch        *b_dmMVA_2;   //!
   TBranch        *b_deepTauVsEleRaw_1;   //!
   TBranch        *b_deepTauVsJetRaw_1;   //!
   TBranch        *b_deepTauVsMuRaw_1;   //!
   TBranch        *b_byLooseDeepTau2017v2p1VSe_1;   //!
   TBranch        *b_byLooseDeepTau2017v2p1VSjet_1;   //!
   TBranch        *b_byLooseDeepTau2017v2p1VSmu_1;   //!
   TBranch        *b_byMediumDeepTau2017v2p1VSe_1;   //!
   TBranch        *b_byMediumDeepTau2017v2p1VSjet_1;   //!
   TBranch        *b_byMediumDeepTau2017v2p1VSmu_1;   //!
   TBranch        *b_byTightDeepTau2017v2p1VSe_1;   //!
   TBranch        *b_byTightDeepTau2017v2p1VSjet_1;   //!
   TBranch        *b_byTightDeepTau2017v2p1VSmu_1;   //!
   TBranch        *b_byVLooseDeepTau2017v2p1VSe_1;   //!
   TBranch        *b_byVLooseDeepTau2017v2p1VSjet_1;   //!
   TBranch        *b_byVLooseDeepTau2017v2p1VSmu_1;   //!
   TBranch        *b_byVTightDeepTau2017v2p1VSe_1;   //!
   TBranch        *b_byVTightDeepTau2017v2p1VSjet_1;   //!
   TBranch        *b_byVVLooseDeepTau2017v2p1VSe_1;   //!
   TBranch        *b_byVVLooseDeepTau2017v2p1VSjet_1;   //!
   TBranch        *b_byVVTightDeepTau2017v2p1VSe_1;   //!
   TBranch        *b_byVVTightDeepTau2017v2p1VSjet_1;   //!
   TBranch        *b_byVVVLooseDeepTau2017v2p1VSe_1;   //!
   TBranch        *b_byVVVLooseDeepTau2017v2p1VSjet_1;   //!
   TBranch        *b_deepTauVsEleRaw_2;   //!
   TBranch        *b_deepTauVsJetRaw_2;   //!
   TBranch        *b_deepTauVsMuRaw_2;   //!
   TBranch        *b_byLooseDeepTau2017v2p1VSe_2;   //!
   TBranch        *b_byLooseDeepTau2017v2p1VSjet_2;   //!
   TBranch        *b_byLooseDeepTau2017v2p1VSmu_2;   //!
   TBranch        *b_byMediumDeepTau2017v2p1VSe_2;   //!
   TBranch        *b_byMediumDeepTau2017v2p1VSjet_2;   //!
   TBranch        *b_byMediumDeepTau2017v2p1VSmu_2;   //!
   TBranch        *b_byTightDeepTau2017v2p1VSe_2;   //!
   TBranch        *b_byTightDeepTau2017v2p1VSjet_2;   //!
   TBranch        *b_byTightDeepTau2017v2p1VSmu_2;   //!
   TBranch        *b_byVLooseDeepTau2017v2p1VSe_2;   //!
   TBranch        *b_byVLooseDeepTau2017v2p1VSjet_2;   //!
   TBranch        *b_byVLooseDeepTau2017v2p1VSmu_2;   //!
   TBranch        *b_byVTightDeepTau2017v2p1VSe_2;   //!
   TBranch        *b_byVTightDeepTau2017v2p1VSjet_2;   //!
   TBranch        *b_byVVLooseDeepTau2017v2p1VSe_2;   //!
   TBranch        *b_byVVLooseDeepTau2017v2p1VSjet_2;   //!
   TBranch        *b_byVVTightDeepTau2017v2p1VSe_2;   //!
   TBranch        *b_byVVTightDeepTau2017v2p1VSjet_2;   //!
   TBranch        *b_byVVVLooseDeepTau2017v2p1VSe_2;   //!
   TBranch        *b_byVVVLooseDeepTau2017v2p1VSjet_2;   //!
   TBranch        *b_embweight;   //!
   TBranch        *b_idisoweight_1;   //!
   TBranch        *b_trkeffweight_1;   //!
   TBranch        *b_idisoweight_2;   //!
   TBranch        *b_trkeffweight_2;   //!
   TBranch        *b_trigweight_1;   //!
   TBranch        *b_trigweight_antiiso_1;   //!
   TBranch        *b_idisoweight_antiiso_1;   //!
   TBranch        *b_trigweight_2;   //!
   TBranch        *b_trigweight_2_Up;   //!
   TBranch        *b_trigweight_2_Down;   //!
   TBranch        *b_trigweight_l_lt;   //!
   TBranch        *b_trigweight_t_lt;   //!
   TBranch        *b_trigweight_antiiso_2;   //!
   TBranch        *b_idisoweight_antiiso_2;   //!
   TBranch        *b_weight_CMS_scale_gg_13TeVUp;   //!
   TBranch        *b_weight_CMS_scale_gg_13TeVDown;   //!
   TBranch        *b_weight_CMS_PS_ISR_ggH_13TeVUp;   //!
   TBranch        *b_weight_CMS_PS_ISR_ggH_13TeVDown;   //!
   TBranch        *b_weight_CMS_PS_FSR_ggH_13TeVUp;   //!
   TBranch        *b_weight_CMS_PS_FSR_ggH_13TeVDown;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_mcweight;   //!
   TBranch        *b_puweight;   //!
   TBranch        *b_trigweight;   //!
   TBranch        *b_prefiringweight;   //!
   TBranch        *b_prefiringweightUp;   //!
   TBranch        *b_prefiringweightDown;   //!
   TBranch        *b_topptweight;   //!
   TBranch        *b_zptweight;   //!
   TBranch        *b_zptembweight;   //!
   TBranch        *b_effweight;   //!
   TBranch        *b_btagweight;   //!
   TBranch        *b_ff_nom;   //!
   TBranch        *b_ff_nom_sys;   //!
   TBranch        *b_trg_singlemuon;   //!
   TBranch        *b_trg_singleelectron;   //!
   TBranch        *b_trg_doubletau;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_metcov00;   //!
   TBranch        *b_metcov01;   //!
   TBranch        *b_metcov10;   //!
   TBranch        *b_metcov11;   //!
   TBranch        *b_pzetavis;   //!
   TBranch        *b_pzetamiss;   //!
   TBranch        *b_pzeta;   //!
   TBranch        *b_puppimet;   //!
   TBranch        *b_puppimetphi;   //!
   TBranch        *b_puppimetcov00;   //!
   TBranch        *b_puppimetcov01;   //!
   TBranch        *b_puppimetcov10;   //!
   TBranch        *b_puppimetcov11;   //!
   TBranch        *b_pt_tt;   //!
   TBranch        *b_dr_tt;   //!
   TBranch        *b_m_vis;   //!
   TBranch        *b_mt_tot;   //!
   TBranch        *b_m_sv;   //!
   TBranch        *b_pt_sv;   //!
   TBranch        *b_eta_sv;   //!
   TBranch        *b_phi_sv;   //!
   TBranch        *b_met_sv;   //!
   TBranch        *b_mt_sv;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_nbtag;   //!
   TBranch        *b_gen_nbjets_cut;   //!
   TBranch        *b_gen_nbjets;   //!
   TBranch        *b_jpt_1;   //!
   TBranch        *b_jeta_1;   //!
   TBranch        *b_jphi_1;   //!
   TBranch        *b_jpt_2;   //!
   TBranch        *b_jeta_2;   //!
   TBranch        *b_jphi_2;   //!
   TBranch        *b_mjj;   //!
   TBranch        *b_jdeta;   //!
   TBranch        *b_dijetpt;   //!
   TBranch        *b_dijeteta;   //!
   TBranch        *b_dijetphi;   //!
   TBranch        *b_jdphi;   //!
   TBranch        *b_bpt_1;   //!
   TBranch        *b_beta_1;   //!
   TBranch        *b_bpt_2;   //!
   TBranch        *b_beta_2;   //!
   TBranch        *b_jcsv_1;   //!
   TBranch        *b_jcsv_2;   //!
   TBranch        *b_bphi_1;   //!
   TBranch        *b_bcsv_1;   //!
   TBranch        *b_bphi_2;   //!
   TBranch        *b_bcsv_2;   //!
   TBranch        *b_mbb;   //!
   TBranch        *b_dRbb;   //!
   TBranch        *b_gen_noutgoing;   //!
   TBranch        *b_os;   //!
   TBranch        *b_dilepton_veto;   //!
   TBranch        *b_extraelec_veto;   //!
   TBranch        *b_extramuon_veto;   //!

   TauCheck(TTree *tree=0);
   virtual ~TauCheck();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TauCheck_cxx
TauCheck::TauCheck(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/nfs/dust/cms/user/rasp/Run/tautau_UL/2016_post/Tau_Run2016F.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/nfs/dust/cms/user/rasp/Run/tautau_UL/2016_post/Tau_Run2016F.root");
      }
      f->GetObject("TauCheck",tree);

   }
   Init(tree);
}

TauCheck::~TauCheck()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TauCheck::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TauCheck::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TauCheck::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("weight_CMS_eff_tauidUp", &weight_CMS_eff_tauidUp, &b_weight_CMS_eff_tauidUp);
   fChain->SetBranchAddress("weight_CMS_eff_tauidDown", &weight_CMS_eff_tauidDown, &b_weight_CMS_eff_tauidDown);
   fChain->SetBranchAddress("weight_CMS_eff_tauid_DM0Up", &weight_CMS_eff_tauid_DM0Up, &b_weight_CMS_eff_tauid_DM0Up);
   fChain->SetBranchAddress("weight_CMS_eff_tauid_DM0Down", &weight_CMS_eff_tauid_DM0Down, &b_weight_CMS_eff_tauid_DM0Down);
   fChain->SetBranchAddress("weight_CMS_eff_tauid_DM1Up", &weight_CMS_eff_tauid_DM1Up, &b_weight_CMS_eff_tauid_DM1Up);
   fChain->SetBranchAddress("weight_CMS_eff_tauid_DM1Down", &weight_CMS_eff_tauid_DM1Down, &b_weight_CMS_eff_tauid_DM1Down);
   fChain->SetBranchAddress("weight_CMS_eff_tauid_DM10Up", &weight_CMS_eff_tauid_DM10Up, &b_weight_CMS_eff_tauid_DM10Up);
   fChain->SetBranchAddress("weight_CMS_eff_tauid_DM10Down", &weight_CMS_eff_tauid_DM10Down, &b_weight_CMS_eff_tauid_DM10Down);
   fChain->SetBranchAddress("weight_CMS_eff_tauid_DM11Up", &weight_CMS_eff_tauid_DM11Up, &b_weight_CMS_eff_tauid_DM11Up);
   fChain->SetBranchAddress("weight_CMS_eff_tauid_DM11Down", &weight_CMS_eff_tauid_DM11Down, &b_weight_CMS_eff_tauid_DM11Down);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trigUp", &weight_CMS_eff_tau_trigUp, &b_weight_CMS_eff_tau_trigUp);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trigDown", &weight_CMS_eff_tau_trigDown, &b_weight_CMS_eff_tau_trigDown);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trig_DM0Up", &weight_CMS_eff_tau_trig_DM0Up, &b_weight_CMS_eff_tau_trig_DM0Up);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trig_DM0Down", &weight_CMS_eff_tau_trig_DM0Down, &b_weight_CMS_eff_tau_trig_DM0Down);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trig_DM1Up", &weight_CMS_eff_tau_trig_DM1Up, &b_weight_CMS_eff_tau_trig_DM1Up);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trig_DM1Down", &weight_CMS_eff_tau_trig_DM1Down, &b_weight_CMS_eff_tau_trig_DM1Down);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trig_DM10Up", &weight_CMS_eff_tau_trig_DM10Up, &b_weight_CMS_eff_tau_trig_DM10Up);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trig_DM10Down", &weight_CMS_eff_tau_trig_DM10Down, &b_weight_CMS_eff_tau_trig_DM10Down);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trig_DM11Up", &weight_CMS_eff_tau_trig_DM11Up, &b_weight_CMS_eff_tau_trig_DM11Up);
   fChain->SetBranchAddress("weight_CMS_eff_tau_trig_DM11Down", &weight_CMS_eff_tau_trig_DM11Down, &b_weight_CMS_eff_tau_trig_DM11Down);
   fChain->SetBranchAddress("weight_CMS_mutaufakeUp", &weight_CMS_mutaufakeUp, &b_weight_CMS_mutaufakeUp);
   fChain->SetBranchAddress("weight_CMS_mutaufakeDown", &weight_CMS_mutaufakeDown, &b_weight_CMS_mutaufakeDown);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet0_dm0", &ff_qcd_stat_unc1_njet0_dm0, &b_ff_qcd_stat_unc1_njet0_dm0);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet0_dm1", &ff_qcd_stat_unc1_njet0_dm1, &b_ff_qcd_stat_unc1_njet0_dm1);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet0_dm10", &ff_qcd_stat_unc1_njet0_dm10, &b_ff_qcd_stat_unc1_njet0_dm10);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet0_dm11", &ff_qcd_stat_unc1_njet0_dm11, &b_ff_qcd_stat_unc1_njet0_dm11);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet1_dm0", &ff_qcd_stat_unc1_njet1_dm0, &b_ff_qcd_stat_unc1_njet1_dm0);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet1_dm1", &ff_qcd_stat_unc1_njet1_dm1, &b_ff_qcd_stat_unc1_njet1_dm1);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet1_dm10", &ff_qcd_stat_unc1_njet1_dm10, &b_ff_qcd_stat_unc1_njet1_dm10);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet1_dm11", &ff_qcd_stat_unc1_njet1_dm11, &b_ff_qcd_stat_unc1_njet1_dm11);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet2_dm0", &ff_qcd_stat_unc1_njet2_dm0, &b_ff_qcd_stat_unc1_njet2_dm0);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet2_dm1", &ff_qcd_stat_unc1_njet2_dm1, &b_ff_qcd_stat_unc1_njet2_dm1);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet2_dm10", &ff_qcd_stat_unc1_njet2_dm10, &b_ff_qcd_stat_unc1_njet2_dm10);
   fChain->SetBranchAddress("ff_qcd_stat_unc1_njet2_dm11", &ff_qcd_stat_unc1_njet2_dm11, &b_ff_qcd_stat_unc1_njet2_dm11);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet0_dm0", &ff_qcd_stat_unc2_njet0_dm0, &b_ff_qcd_stat_unc2_njet0_dm0);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet0_dm1", &ff_qcd_stat_unc2_njet0_dm1, &b_ff_qcd_stat_unc2_njet0_dm1);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet0_dm10", &ff_qcd_stat_unc2_njet0_dm10, &b_ff_qcd_stat_unc2_njet0_dm10);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet0_dm11", &ff_qcd_stat_unc2_njet0_dm11, &b_ff_qcd_stat_unc2_njet0_dm11);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet1_dm0", &ff_qcd_stat_unc2_njet1_dm0, &b_ff_qcd_stat_unc2_njet1_dm0);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet1_dm1", &ff_qcd_stat_unc2_njet1_dm1, &b_ff_qcd_stat_unc2_njet1_dm1);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet1_dm10", &ff_qcd_stat_unc2_njet1_dm10, &b_ff_qcd_stat_unc2_njet1_dm10);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet1_dm11", &ff_qcd_stat_unc2_njet1_dm11, &b_ff_qcd_stat_unc2_njet1_dm11);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet2_dm0", &ff_qcd_stat_unc2_njet2_dm0, &b_ff_qcd_stat_unc2_njet2_dm0);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet2_dm1", &ff_qcd_stat_unc2_njet2_dm1, &b_ff_qcd_stat_unc2_njet2_dm1);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet2_dm10", &ff_qcd_stat_unc2_njet2_dm10, &b_ff_qcd_stat_unc2_njet2_dm10);
   fChain->SetBranchAddress("ff_qcd_stat_unc2_njet2_dm11", &ff_qcd_stat_unc2_njet2_dm11, &b_ff_qcd_stat_unc2_njet2_dm11);
   fChain->SetBranchAddress("ff_qcd_met", &ff_qcd_met, &b_ff_qcd_met);
   fChain->SetBranchAddress("ff_qcd_syst", &ff_qcd_syst, &b_ff_qcd_syst);
   fChain->SetBranchAddress("ff_qcd_pt2", &ff_qcd_pt2, &b_ff_qcd_pt2);
   fChain->SetBranchAddress("jleppt_1", &jleppt_1, &b_jleppt_1);
   fChain->SetBranchAddress("jlepeta_1", &jlepeta_1, &b_jlepeta_1);
   fChain->SetBranchAddress("jlepphi_1", &jlepphi_1, &b_jlepphi_1);
   fChain->SetBranchAddress("jleppt_2", &jleppt_2, &b_jleppt_2);
   fChain->SetBranchAddress("jlepeta_2", &jlepeta_2, &b_jlepeta_2);
   fChain->SetBranchAddress("jlepphi_2", &jlepphi_2, &b_jlepphi_2);
   fChain->SetBranchAddress("passedAllMetFilters", &passedAllMetFilters, &b_passedAllMetFilters);
   fChain->SetBranchAddress("pt_1", &pt_1, &b_pt_1);
   fChain->SetBranchAddress("phi_1", &phi_1, &b_phi_1);
   fChain->SetBranchAddress("eta_1", &eta_1, &b_eta_1);
   fChain->SetBranchAddress("m_1", &m_1, &b_m_1);
   fChain->SetBranchAddress("gen_match_1", &gen_match_1, &b_gen_match_1);
   fChain->SetBranchAddress("q_1", &q_1, &b_q_1);
   fChain->SetBranchAddress("iso_1", &iso_1, &b_iso_1);
   fChain->SetBranchAddress("d0_1", &d0_1, &b_d0_1);
   fChain->SetBranchAddress("dZ_1", &dZ_1, &b_dZ_1);
   fChain->SetBranchAddress("pt_uncorr_1", &pt_uncorr_1, &b_pt_uncorr_1);
   fChain->SetBranchAddress("mt_1", &mt_1, &b_mt_1);
   fChain->SetBranchAddress("puppimt_1", &puppimt_1, &b_puppimt_1);
   fChain->SetBranchAddress("tau_decay_mode_1", &tau_decay_mode_1, &b_tau_decay_mode_1);
   fChain->SetBranchAddress("dm_1", &dm_1, &b_dm_1);
   fChain->SetBranchAddress("dmMVA_1", &dmMVA_1, &b_dmMVA_1);
   fChain->SetBranchAddress("pt_2", &pt_2, &b_pt_2);
   fChain->SetBranchAddress("phi_2", &phi_2, &b_phi_2);
   fChain->SetBranchAddress("eta_2", &eta_2, &b_eta_2);
   fChain->SetBranchAddress("m_2", &m_2, &b_m_2);
   fChain->SetBranchAddress("gen_match_2", &gen_match_2, &b_gen_match_2);
   fChain->SetBranchAddress("q_2", &q_2, &b_q_2);
   fChain->SetBranchAddress("iso_2", &iso_2, &b_iso_2);
   fChain->SetBranchAddress("pt_uncorr_2", &pt_uncorr_2, &b_pt_uncorr_2);
   fChain->SetBranchAddress("d0_2", &d0_2, &b_d0_2);
   fChain->SetBranchAddress("dZ_2", &dZ_2, &b_dZ_2);
   fChain->SetBranchAddress("mt_2", &mt_2, &b_mt_2);
   fChain->SetBranchAddress("puppimt_2", &puppimt_2, &b_puppimt_2);
   fChain->SetBranchAddress("tau_decay_mode_2", &tau_decay_mode_2, &b_tau_decay_mode_2);
   fChain->SetBranchAddress("dm_2", &dm_2, &b_dm_2);
   fChain->SetBranchAddress("dmMVA_2", &dmMVA_2, &b_dmMVA_2);
   fChain->SetBranchAddress("deepTauVsEleRaw_1", &deepTauVsEleRaw_1, &b_deepTauVsEleRaw_1);
   fChain->SetBranchAddress("deepTauVsJetRaw_1", &deepTauVsJetRaw_1, &b_deepTauVsJetRaw_1);
   fChain->SetBranchAddress("deepTauVsMuRaw_1", &deepTauVsMuRaw_1, &b_deepTauVsMuRaw_1);
   fChain->SetBranchAddress("byLooseDeepTau2017v2p1VSe_1", &byLooseDeepTau2017v2p1VSe_1, &b_byLooseDeepTau2017v2p1VSe_1);
   fChain->SetBranchAddress("byLooseDeepTau2017v2p1VSjet_1", &byLooseDeepTau2017v2p1VSjet_1, &b_byLooseDeepTau2017v2p1VSjet_1);
   fChain->SetBranchAddress("byLooseDeepTau2017v2p1VSmu_1", &byLooseDeepTau2017v2p1VSmu_1, &b_byLooseDeepTau2017v2p1VSmu_1);
   fChain->SetBranchAddress("byMediumDeepTau2017v2p1VSe_1", &byMediumDeepTau2017v2p1VSe_1, &b_byMediumDeepTau2017v2p1VSe_1);
   fChain->SetBranchAddress("byMediumDeepTau2017v2p1VSjet_1", &byMediumDeepTau2017v2p1VSjet_1, &b_byMediumDeepTau2017v2p1VSjet_1);
   fChain->SetBranchAddress("byMediumDeepTau2017v2p1VSmu_1", &byMediumDeepTau2017v2p1VSmu_1, &b_byMediumDeepTau2017v2p1VSmu_1);
   fChain->SetBranchAddress("byTightDeepTau2017v2p1VSe_1", &byTightDeepTau2017v2p1VSe_1, &b_byTightDeepTau2017v2p1VSe_1);
   fChain->SetBranchAddress("byTightDeepTau2017v2p1VSjet_1", &byTightDeepTau2017v2p1VSjet_1, &b_byTightDeepTau2017v2p1VSjet_1);
   fChain->SetBranchAddress("byTightDeepTau2017v2p1VSmu_1", &byTightDeepTau2017v2p1VSmu_1, &b_byTightDeepTau2017v2p1VSmu_1);
   fChain->SetBranchAddress("byVLooseDeepTau2017v2p1VSe_1", &byVLooseDeepTau2017v2p1VSe_1, &b_byVLooseDeepTau2017v2p1VSe_1);
   fChain->SetBranchAddress("byVLooseDeepTau2017v2p1VSjet_1", &byVLooseDeepTau2017v2p1VSjet_1, &b_byVLooseDeepTau2017v2p1VSjet_1);
   fChain->SetBranchAddress("byVLooseDeepTau2017v2p1VSmu_1", &byVLooseDeepTau2017v2p1VSmu_1, &b_byVLooseDeepTau2017v2p1VSmu_1);
   fChain->SetBranchAddress("byVTightDeepTau2017v2p1VSe_1", &byVTightDeepTau2017v2p1VSe_1, &b_byVTightDeepTau2017v2p1VSe_1);
   fChain->SetBranchAddress("byVTightDeepTau2017v2p1VSjet_1", &byVTightDeepTau2017v2p1VSjet_1, &b_byVTightDeepTau2017v2p1VSjet_1);
   fChain->SetBranchAddress("byVVLooseDeepTau2017v2p1VSe_1", &byVVLooseDeepTau2017v2p1VSe_1, &b_byVVLooseDeepTau2017v2p1VSe_1);
   fChain->SetBranchAddress("byVVLooseDeepTau2017v2p1VSjet_1", &byVVLooseDeepTau2017v2p1VSjet_1, &b_byVVLooseDeepTau2017v2p1VSjet_1);
   fChain->SetBranchAddress("byVVTightDeepTau2017v2p1VSe_1", &byVVTightDeepTau2017v2p1VSe_1, &b_byVVTightDeepTau2017v2p1VSe_1);
   fChain->SetBranchAddress("byVVTightDeepTau2017v2p1VSjet_1", &byVVTightDeepTau2017v2p1VSjet_1, &b_byVVTightDeepTau2017v2p1VSjet_1);
   fChain->SetBranchAddress("byVVVLooseDeepTau2017v2p1VSe_1", &byVVVLooseDeepTau2017v2p1VSe_1, &b_byVVVLooseDeepTau2017v2p1VSe_1);
   fChain->SetBranchAddress("byVVVLooseDeepTau2017v2p1VSjet_1", &byVVVLooseDeepTau2017v2p1VSjet_1, &b_byVVVLooseDeepTau2017v2p1VSjet_1);
   fChain->SetBranchAddress("deepTauVsEleRaw_2", &deepTauVsEleRaw_2, &b_deepTauVsEleRaw_2);
   fChain->SetBranchAddress("deepTauVsJetRaw_2", &deepTauVsJetRaw_2, &b_deepTauVsJetRaw_2);
   fChain->SetBranchAddress("deepTauVsMuRaw_2", &deepTauVsMuRaw_2, &b_deepTauVsMuRaw_2);
   fChain->SetBranchAddress("byLooseDeepTau2017v2p1VSe_2", &byLooseDeepTau2017v2p1VSe_2, &b_byLooseDeepTau2017v2p1VSe_2);
   fChain->SetBranchAddress("byLooseDeepTau2017v2p1VSjet_2", &byLooseDeepTau2017v2p1VSjet_2, &b_byLooseDeepTau2017v2p1VSjet_2);
   fChain->SetBranchAddress("byLooseDeepTau2017v2p1VSmu_2", &byLooseDeepTau2017v2p1VSmu_2, &b_byLooseDeepTau2017v2p1VSmu_2);
   fChain->SetBranchAddress("byMediumDeepTau2017v2p1VSe_2", &byMediumDeepTau2017v2p1VSe_2, &b_byMediumDeepTau2017v2p1VSe_2);
   fChain->SetBranchAddress("byMediumDeepTau2017v2p1VSjet_2", &byMediumDeepTau2017v2p1VSjet_2, &b_byMediumDeepTau2017v2p1VSjet_2);
   fChain->SetBranchAddress("byMediumDeepTau2017v2p1VSmu_2", &byMediumDeepTau2017v2p1VSmu_2, &b_byMediumDeepTau2017v2p1VSmu_2);
   fChain->SetBranchAddress("byTightDeepTau2017v2p1VSe_2", &byTightDeepTau2017v2p1VSe_2, &b_byTightDeepTau2017v2p1VSe_2);
   fChain->SetBranchAddress("byTightDeepTau2017v2p1VSjet_2", &byTightDeepTau2017v2p1VSjet_2, &b_byTightDeepTau2017v2p1VSjet_2);
   fChain->SetBranchAddress("byTightDeepTau2017v2p1VSmu_2", &byTightDeepTau2017v2p1VSmu_2, &b_byTightDeepTau2017v2p1VSmu_2);
   fChain->SetBranchAddress("byVLooseDeepTau2017v2p1VSe_2", &byVLooseDeepTau2017v2p1VSe_2, &b_byVLooseDeepTau2017v2p1VSe_2);
   fChain->SetBranchAddress("byVLooseDeepTau2017v2p1VSjet_2", &byVLooseDeepTau2017v2p1VSjet_2, &b_byVLooseDeepTau2017v2p1VSjet_2);
   fChain->SetBranchAddress("byVLooseDeepTau2017v2p1VSmu_2", &byVLooseDeepTau2017v2p1VSmu_2, &b_byVLooseDeepTau2017v2p1VSmu_2);
   fChain->SetBranchAddress("byVTightDeepTau2017v2p1VSe_2", &byVTightDeepTau2017v2p1VSe_2, &b_byVTightDeepTau2017v2p1VSe_2);
   fChain->SetBranchAddress("byVTightDeepTau2017v2p1VSjet_2", &byVTightDeepTau2017v2p1VSjet_2, &b_byVTightDeepTau2017v2p1VSjet_2);
   fChain->SetBranchAddress("byVVLooseDeepTau2017v2p1VSe_2", &byVVLooseDeepTau2017v2p1VSe_2, &b_byVVLooseDeepTau2017v2p1VSe_2);
   fChain->SetBranchAddress("byVVLooseDeepTau2017v2p1VSjet_2", &byVVLooseDeepTau2017v2p1VSjet_2, &b_byVVLooseDeepTau2017v2p1VSjet_2);
   fChain->SetBranchAddress("byVVTightDeepTau2017v2p1VSe_2", &byVVTightDeepTau2017v2p1VSe_2, &b_byVVTightDeepTau2017v2p1VSe_2);
   fChain->SetBranchAddress("byVVTightDeepTau2017v2p1VSjet_2", &byVVTightDeepTau2017v2p1VSjet_2, &b_byVVTightDeepTau2017v2p1VSjet_2);
   fChain->SetBranchAddress("byVVVLooseDeepTau2017v2p1VSe_2", &byVVVLooseDeepTau2017v2p1VSe_2, &b_byVVVLooseDeepTau2017v2p1VSe_2);
   fChain->SetBranchAddress("byVVVLooseDeepTau2017v2p1VSjet_2", &byVVVLooseDeepTau2017v2p1VSjet_2, &b_byVVVLooseDeepTau2017v2p1VSjet_2);
   fChain->SetBranchAddress("embweight", &embweight, &b_embweight);
   fChain->SetBranchAddress("idisoweight_1", &idisoweight_1, &b_idisoweight_1);
   fChain->SetBranchAddress("trkeffweight_1", &trkeffweight_1, &b_trkeffweight_1);
   fChain->SetBranchAddress("idisoweight_2", &idisoweight_2, &b_idisoweight_2);
   fChain->SetBranchAddress("trkeffweight_2", &trkeffweight_2, &b_trkeffweight_2);
   fChain->SetBranchAddress("trigweight_1", &trigweight_1, &b_trigweight_1);
   fChain->SetBranchAddress("trigweight_antiiso_1", &trigweight_antiiso_1, &b_trigweight_antiiso_1);
   fChain->SetBranchAddress("idisoweight_antiiso_1", &idisoweight_antiiso_1, &b_idisoweight_antiiso_1);
   fChain->SetBranchAddress("trigweight_2", &trigweight_2, &b_trigweight_2);
   fChain->SetBranchAddress("trigweight_2_Up", &trigweight_2_Up, &b_trigweight_2_Up);
   fChain->SetBranchAddress("trigweight_2_Down", &trigweight_2_Down, &b_trigweight_2_Down);
   fChain->SetBranchAddress("trigweight_l_lt", &trigweight_l_lt, &b_trigweight_l_lt);
   fChain->SetBranchAddress("trigweight_t_lt", &trigweight_t_lt, &b_trigweight_t_lt);
   fChain->SetBranchAddress("trigweight_antiiso_2", &trigweight_antiiso_2, &b_trigweight_antiiso_2);
   fChain->SetBranchAddress("idisoweight_antiiso_2", &idisoweight_antiiso_2, &b_idisoweight_antiiso_2);
   fChain->SetBranchAddress("weight_CMS_scale_gg_13TeVUp", &weight_CMS_scale_gg_13TeVUp, &b_weight_CMS_scale_gg_13TeVUp);
   fChain->SetBranchAddress("weight_CMS_scale_gg_13TeVDown", &weight_CMS_scale_gg_13TeVDown, &b_weight_CMS_scale_gg_13TeVDown);
   fChain->SetBranchAddress("weight_CMS_PS_ISR_ggH_13TeVUp", &weight_CMS_PS_ISR_ggH_13TeVUp, &b_weight_CMS_PS_ISR_ggH_13TeVUp);
   fChain->SetBranchAddress("weight_CMS_PS_ISR_ggH_13TeVDown", &weight_CMS_PS_ISR_ggH_13TeVDown, &b_weight_CMS_PS_ISR_ggH_13TeVDown);
   fChain->SetBranchAddress("weight_CMS_PS_FSR_ggH_13TeVUp", &weight_CMS_PS_FSR_ggH_13TeVUp, &b_weight_CMS_PS_FSR_ggH_13TeVUp);
   fChain->SetBranchAddress("weight_CMS_PS_FSR_ggH_13TeVDown", &weight_CMS_PS_FSR_ggH_13TeVDown, &b_weight_CMS_PS_FSR_ggH_13TeVDown);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("mcweight", &mcweight, &b_mcweight);
   fChain->SetBranchAddress("puweight", &puweight, &b_puweight);
   fChain->SetBranchAddress("trigweight", &trigweight, &b_trigweight);
   fChain->SetBranchAddress("prefiringweight", &prefiringweight, &b_prefiringweight);
   fChain->SetBranchAddress("prefiringweightUp", &prefiringweightUp, &b_prefiringweightUp);
   fChain->SetBranchAddress("prefiringweightDown", &prefiringweightDown, &b_prefiringweightDown);
   fChain->SetBranchAddress("topptweight", &topptweight, &b_topptweight);
   fChain->SetBranchAddress("zptweight", &zptweight, &b_zptweight);
   fChain->SetBranchAddress("zptembweight", &zptembweight, &b_zptembweight);
   fChain->SetBranchAddress("effweight", &effweight, &b_effweight);
   fChain->SetBranchAddress("btagweight", &btagweight, &b_btagweight);
   fChain->SetBranchAddress("ff_nom", &ff_nom, &b_ff_nom);
   fChain->SetBranchAddress("ff_nom_sys", &ff_nom_sys, &b_ff_nom_sys);
   fChain->SetBranchAddress("trg_singlemuon", &trg_singlemuon, &b_trg_singlemuon);
   fChain->SetBranchAddress("trg_singleelectron", &trg_singleelectron, &b_trg_singleelectron);
   fChain->SetBranchAddress("trg_doubletau", &trg_doubletau, &b_trg_doubletau);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("metphi", &metphi, &b_metphi);
   fChain->SetBranchAddress("metcov00", &metcov00, &b_metcov00);
   fChain->SetBranchAddress("metcov01", &metcov01, &b_metcov01);
   fChain->SetBranchAddress("metcov10", &metcov10, &b_metcov10);
   fChain->SetBranchAddress("metcov11", &metcov11, &b_metcov11);
   fChain->SetBranchAddress("pzetavis", &pzetavis, &b_pzetavis);
   fChain->SetBranchAddress("pzetamiss", &pzetamiss, &b_pzetamiss);
   fChain->SetBranchAddress("pzeta", &pzeta, &b_pzeta);
   fChain->SetBranchAddress("puppimet", &puppimet, &b_puppimet);
   fChain->SetBranchAddress("puppimetphi", &puppimetphi, &b_puppimetphi);
   fChain->SetBranchAddress("puppimetcov00", &puppimetcov00, &b_puppimetcov00);
   fChain->SetBranchAddress("puppimetcov01", &puppimetcov01, &b_puppimetcov01);
   fChain->SetBranchAddress("puppimetcov10", &puppimetcov10, &b_puppimetcov10);
   fChain->SetBranchAddress("puppimetcov11", &puppimetcov11, &b_puppimetcov11);
   fChain->SetBranchAddress("pt_tt", &pt_tt, &b_pt_tt);
   fChain->SetBranchAddress("dr_tt", &dr_tt, &b_dr_tt);
   fChain->SetBranchAddress("m_vis", &m_vis, &b_m_vis);
   fChain->SetBranchAddress("mt_tot", &mt_tot, &b_mt_tot);
   fChain->SetBranchAddress("m_sv", &m_sv, &b_m_sv);
   fChain->SetBranchAddress("pt_sv", &pt_sv, &b_pt_sv);
   fChain->SetBranchAddress("eta_sv", &eta_sv, &b_eta_sv);
   fChain->SetBranchAddress("phi_sv", &phi_sv, &b_phi_sv);
   fChain->SetBranchAddress("met_sv", &met_sv, &b_met_sv);
   fChain->SetBranchAddress("mt_sv", &mt_sv, &b_mt_sv);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("nbtag", &nbtag, &b_nbtag);
   fChain->SetBranchAddress("gen_nbjets_cut", &gen_nbjets_cut, &b_gen_nbjets_cut);
   fChain->SetBranchAddress("gen_nbjets", &gen_nbjets, &b_gen_nbjets);
   fChain->SetBranchAddress("jpt_1", &jpt_1, &b_jpt_1);
   fChain->SetBranchAddress("jeta_1", &jeta_1, &b_jeta_1);
   fChain->SetBranchAddress("jphi_1", &jphi_1, &b_jphi_1);
   fChain->SetBranchAddress("jpt_2", &jpt_2, &b_jpt_2);
   fChain->SetBranchAddress("jeta_2", &jeta_2, &b_jeta_2);
   fChain->SetBranchAddress("jphi_2", &jphi_2, &b_jphi_2);
   fChain->SetBranchAddress("mjj", &mjj, &b_mjj);
   fChain->SetBranchAddress("jdeta", &jdeta, &b_jdeta);
   fChain->SetBranchAddress("dijetpt", &dijetpt, &b_dijetpt);
   fChain->SetBranchAddress("dijeteta", &dijeteta, &b_dijeteta);
   fChain->SetBranchAddress("dijetphi", &dijetphi, &b_dijetphi);
   fChain->SetBranchAddress("jdphi", &jdphi, &b_jdphi);
   fChain->SetBranchAddress("bpt_1", &bpt_1, &b_bpt_1);
   fChain->SetBranchAddress("beta_1", &beta_1, &b_beta_1);
   fChain->SetBranchAddress("bpt_2", &bpt_2, &b_bpt_2);
   fChain->SetBranchAddress("beta_2", &beta_2, &b_beta_2);
   fChain->SetBranchAddress("jcsv_1", &jcsv_1, &b_jcsv_1);
   fChain->SetBranchAddress("jcsv_2", &jcsv_2, &b_jcsv_2);
   fChain->SetBranchAddress("bphi_1", &bphi_1, &b_bphi_1);
   fChain->SetBranchAddress("bcsv_1", &bcsv_1, &b_bcsv_1);
   fChain->SetBranchAddress("bphi_2", &bphi_2, &b_bphi_2);
   fChain->SetBranchAddress("bcsv_2", &bcsv_2, &b_bcsv_2);
   fChain->SetBranchAddress("mbb", &mbb, &b_mbb);
   fChain->SetBranchAddress("dRbb", &dRbb, &b_dRbb);
   fChain->SetBranchAddress("gen_noutgoing", &gen_noutgoing, &b_gen_noutgoing);
   fChain->SetBranchAddress("os", &os, &b_os);
   fChain->SetBranchAddress("dilepton_veto", &dilepton_veto, &b_dilepton_veto);
   fChain->SetBranchAddress("extraelec_veto", &extraelec_veto, &b_extraelec_veto);
   fChain->SetBranchAddress("extramuon_veto", &extramuon_veto, &b_extramuon_veto);
   Notify();
}

Bool_t TauCheck::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TauCheck::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TauCheck::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TauCheck_cxx
