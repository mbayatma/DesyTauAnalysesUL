void Check(TString sample = "WJets",
	   TString era = "2016_pre") {


  TString fileName = "/nfs/dust/cms/user/makou/bbh_analysis_NTuples/HTauTau_emu/Inputs/DNN_Ntuples/NTuples_"+era+"/em-NOMINAL_ntuple_"+sample+"_"+era+".root" ; 

  TFile * file = new TFile(fileName);
  TTree * tree = (TTree*)file->Get("TauCheck");
  TString cuts("&&iso_1<0.15&&iso_2<0.20&&extraelec_veto<0.5&&extramuon_veto<0.5&&dr_tt>0.3&&pt_1>15.&&pt_2>15.&&((trg_muhigh_elow>0.5&&pt_2>24.0)||(trg_ehigh_mulow>0.5&&pt_1>24.0))");
  tree->Draw("mcweight",cuts);


}
