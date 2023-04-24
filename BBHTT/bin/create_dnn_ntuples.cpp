#include <iostream>
#include <map>
#include "TString.h"
#include "TFile.h"
#include "TF1.h"
#include "TH2F.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1.h"
#include "TList.h"
#include "TSystem.h"
#include "DesyTauAnalyses/BBHTT/interface/settings_for_eras.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "DesyTauAnalyses/Common/interface/Config.h"

// Updated tau ID SF -> 

double TauSFv1_UL(TString era,
		  int tauDM,
		  int genMatch,
		  float tauPT) {

  float sf = 1.0;
  if (genMatch!=5) return sf;
  float minPT = TMath::Min(tauPT,float(140.)); 
  if (era=="2016_pre") 
    sf = 
      (tauDM==0)*((0.95606+0.00165764*minPT))+
      (tauDM>=1&&tauDM<=2)*((0.947464+0.000494337*minPT))+
      (tauDM==10)*((0.857375+0.00132127*minPT))+
      (tauDM==11)*((0.704867+0.00198543*minPT));
  if (era=="2016_post") 
    sf = 
      (tauDM==0)*((0.924781+0.000788052*minPT))+
      (tauDM>=1&&tauDM<=2)*((0.858842+0.00248185*minPT))+
      (tauDM==10)*((0.823274+0.00132487*minPT))+
      (tauDM==11)*((0.681992+0.000256323*minPT));
  if (era=="2017")
    sf =
      (tauDM==0)*((0.940199+0.000243024*minPT))+
      (tauDM>=1&&tauDM<=2)*((0.864785+0.00109546*minPT))+
      (tauDM==10)*((0.862916+0.000676206*minPT))+
      (tauDM==11)*((0.707493+0.00173345*minPT));
  if (era=="2018")
    sf = 
      (tauDM==0)*((0.866109+0.00187025*minPT))+
      (tauDM>=1&&tauDM<=2)*((0.845787+0.00123494*minPT))+
      (tauDM==10)*((0.808835+0.00134081*minPT))+
      (tauDM==11)*((0.636465+0.002494*minPT));

  return sf;


}

double TauSF_UL(TString era, 
		int tauDM,
		int genMatch,
		float tauPT) {

  float sf = 1.0;
  if (genMatch!=5) return sf;
  float minPT = TMath::Min(tauPT,float(125.)); 
  if (era=="2016_pre") 
    sf = 
      (tauDM==0)*((1.03397+0.000407969*minPT))+
      (tauDM>=1&&tauDM<=2)*((1.15107-0.00211504*minPT))+
      (tauDM==10)*((1.03783-0.0011254*minPT))+
      (tauDM==11)*((0.975761-0.00305113*minPT));
  if (era=="2016_post") 
    sf = 
      (tauDM==0)*((0.978417+5.72368e-05*minPT))+
      (tauDM>=1&&tauDM<=2)*(1.04437*TMath::Erf((minPT+10.8845)/46.7379))+
      (tauDM==10)*((0.927759-0.000719045*minPT))+
      (tauDM==11)*(0.766739*TMath::Erf((minPT-16.5928)/11.2111));
  if (era=="2017")
    sf =
      (tauDM==0)*((1.04266-0.00158397*minPT))+
      (tauDM>=1&&tauDM<=2)*(1.01061*TMath::Erf((minPT+13.518)/48.5772))+
      (tauDM==10)*(0.934699*TMath::Erf((minPT-6.19958)/14.8044))+
      (tauDM==11)*(0.939418*TMath::Erf((minPT+2.64469)/40.9824));
  if (era=="2018")
    sf = 
      (tauDM==0)*((1.00465-8.36161e-05*minPT))+
      (tauDM>=1&&tauDM<=2)*(0.93569*TMath::Erf((minPT-1.11787)/28.7657))+
      (tauDM==10)*(0.932986*TMath::Erf((minPT+13.0774)/36.7303))+
      (tauDM==11)*((0.72108+0.00110556*minPT));

  return sf;

}

double tauIDWeight(TString era, 
		   int dm_1,
		   int genmatch_1,
		   float pt_1,  
		   int dm_2,
		   int genmatch_2,
		   float pt_2,
		   float effweight,
		   float trigweight) {


  float sf_1 = TauSF_UL(era,dm_1,genmatch_1,pt_1);
  float sf_2 = TauSF_UL(era,dm_2,genmatch_2,pt_2);
  float sf = sf_1 * sf_2;
  
  float refEff = effweight/TMath::Max(float(0.1),trigweight);

  float weight = sf/refEff;

  return weight;

}


// define the main function to make this code executable. 
// argc gives the number of arguments and argv contains those arguments. 

int main(int argc, char * argv[]) {

  //  bool TEST = false;
  if (argc<4||argc>5) {
    cout << "Usage of the program : create_dnn sample era channel [systematics]" << endl;
    exit(EXIT_FAILURE);
  }
  
  TString process(argv[1]);
  TString era(argv[2]);
  TString channel(argv[3]);
  TString SysName("Central");

  TString Era("2018");
  if (era=="2017") Era="2017";
  if (era=="2016_pre") Era="2016";
  if (era=="2016_post") Era="2016";

  std::map<TString,TString> systematicsNameMap = {
    {"JES","_CMS_scale_j_JES_13TeV"},
    {"JER","_CMS_res_j_13TeV"},
    {"EScale","_CMS_scale_e_13TeV"},
    {"Uncl","_CMS_scale_met_unclustered_13TeV"},
    {"FlavorQCD","_CMS_scale_j_FlavorQCD_13TeV"},
    {"RelativeBal","_CMS_scale_j_RelativeBal_13TeV"},
    {"HF","_CMS_scale_j_HF_13TeV"},
    {"BBEC1","_CMS_scale_j_BBEC1_13TeV"},
    {"EC2","_CMS_scale_j_EC2_13TeV"},
    {"Absolute","_CMS_scale_j_Absolute_13TeV"},
    {"Absolute_Era","_CMS_scale_j_Absolute_"+Era+"_13TeV"},
    {"HF_Era","_CMS_scale_j_HF_"+Era+"_13TeV"},
    {"EC2_Era","_CMS_scale_j_EC2_"+Era+"_13TeV"},
    {"RelativeSample_Era","_CMS_scale_j_RelativeSample_"+Era+"_13TeV"},
    {"BBEC1_Era","_CMS_scale_j_BBEC1_"+Era+"_13TeV"}
  };

  if (argc==5) { 
    SysName = TString(argv[4]);
    bool isSysExist = false;

    if (SysName=="Central") isSysExist = true;
    if (!isSysExist) {
      for (auto sysmap : systematicsNameMap) {
	TString sysLabelUp = sysmap.first + "Up";
	TString sysLabelDown = sysmap.first + "Down";
	if (SysName==sysLabelUp||SysName==sysLabelDown) {
	  isSysExist = true;
	  break;
	}
      }
    }
    if (!isSysExist) {
      std::cout << "Unknown systematics specified : " << SysName << std::endl;
      std::cout << "Available options ->" << std::endl;
      std::cout << "  Central" << std::endl;
      for (auto sysmap : systematicsNameMap) 
	std::cout << "  " << sysmap.first << "{Up,Down}" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  std::map<TString,TString> systematicsMap;
  systematicsMap["Central"] = "";
  for (auto sysmap : systematicsNameMap) {
    TString label = sysmap.first;
    TString sysname = sysmap.second;
    systematicsMap[label+"Up"] = sysname + "Up";
    systematicsMap[label+"Down"] = sysname + "Down";
  }
  
  TString Sample = process + "_" + era ;

  string cmsswBase = (getenv("CMSSW_BASE"));
  string config_file = cmsswBase + "/src/DesyTauAnalyses/BBHTT/test/dnn_production/dnn_production_"+string(argv[3])+".conf"; 
  Config cfg(config_file.c_str());

  if (era!="2018"&&era!="2017"&&era!="2016_post"&&era!="2016_pre") {
    cout << "ERROR : specified era " << era << " is unknown " << endl;
    exit(EXIT_FAILURE);
  }
  bool sampleFound = false;
  for (auto name_sample : map_sample) {
    if (name_sample.first==Sample) {
      sampleFound = true;
      break;
    }
  }
  if (!sampleFound) {
    cout << "ERROR : specified sample " << Sample << " is unknown " << endl;
    cout << "Available samples ===> " << endl;
    for (auto name_sample : map_sample) {
      cout << "     " << name_sample.first << endl;
    }
    exit(EXIT_FAILURE);
  }
  if (channel!="em"&&channel!="tt") {
    cout << "ERROR : specified channel " << channel << " is unknown " << endl;
    cout << "Available samples ===> {em,tt}" << endl;
    exit(EXIT_FAILURE);
  }

  double luminosity = LUMI[era];

  // Mapping of subsamples to output root-file
  map< TString , vector<TString> > samples_map;
  const map<TString, double>  *xsec_map    = 0;
  const map<TString, TString> *process_map = 0;

  RooWorkspace * w_fakefactors;
  TFile * ff_file;

  float scaleDY = 1.0;
  float scaleDY_btag = 1.0;

  float scaleFake = 1.0;
  float scaleFake_btag = 1.0;
  //TString output_dir = "";
  samples_map[channel + "-NOMINAL_ntuple_"+Sample     ] = map_sample.at(Sample);
  bool useFriend = cfg.get<bool>("UseFriend");
  bool applyPreselection = cfg.get<bool>("ApplyPreselection");
  bool recomputeTauID = cfg.get<bool>("RecomputeTauID");
  bool splitJES = cfg.get<bool>("SplitJES");
  TString input_dir  = TString(cfg.get<string>("InputDir"))+"/"+era; 
  TString friend_dir = TString(cfg.get<string>("FriendDir"))+"/"+era;
  TString output_dir = TString(cfg.get<string>("OutputDir"))+"/"+ era;
  if (channel=="em") {
    cout << "Running dnn for em channel " << endl;
  }
  else if (channel=="tt") {
    cout << "Running dnn for tt channel " << endl;
    TString ff_filename = TString(cmsswBase)+"/src/DesyTauAnalyses/Common/data/fakefactors_ws_tt_mssm_"+Era+"_v3.root";
    ff_file = new TFile(ff_filename);
    w_fakefactors = (RooWorkspace*)ff_file->Get("w");

    // scaling for the NLO DY sample and Fake Factors (from closure tests) ->
    if (era=="2018") {
      scaleDY = 1.13;
      scaleDY_btag = 1.13;
      scaleFake = 1.01;
      scaleFake_btag = 1.1;
    }
    else if (era=="2017") {
      scaleDY = 1.27;
      scaleDY_btag = 1.30;
      //      scaleDY_btag = 1.05;
      scaleFake = 0.97;
      scaleFake_btag = 1.0;
    }
    else if (era=="2016_post") {
      scaleDY = 1.30;
      scaleDY_btag = 1.30;
      //      scaleDY_btag = 1.10;
      scaleFake = 1.13;
      scaleFake_btag = 1.33;
    }
    else if (era=="2016_pre") {
      scaleDY = 1.30;
      scaleDY_btag = 1.50;
      //      scaleDY_btag = 1.30;
      scaleFake = 1.15;
      scaleFake_btag = 1.33;
    }
  }
  else {
    std::cout << "Unknown channel specified : " << channel << std::endl;
    exit(-1);
  }
  std::cout << std::endl;
  std::cout << "Era : " << era << std::endl;
  std::cout << std::endl;
  if (channel=="tt") {
    std::cout << "scaling DY    by " << scaleDY <<   " (incl) and " << scaleDY_btag <<   " (btag)" << std::endl;
    std::cout << "scaling fakes by " << scaleFake << " (incl) and " << scaleFake_btag << " (btag)" << std::endl;
  }

  std::vector<TString> systematicsJES_era = systematicsJES_2018;
  if (Era=="2017") systematicsJES_era = systematicsJES_2017;
  if (Era=="2016") systematicsJES_era = systematicsJES_2016;

  std::vector<TString> sysTreeNames;
  if (argc==4) {
    sysTreeNames.push_back("");

    bool isData = process=="Tau"||process=="MuonEG";

    if (!isData) {
      for (auto sysname : systematics) {
	TString NameSys = "_" + sysname + "Up";
	sysTreeNames.push_back(NameSys);
	NameSys = "_" + sysname +"Down";
	sysTreeNames.push_back(NameSys);
      }
      if (splitJES) {
	for (auto sysname : systematicsJES) {
	  TString NameSys = "_" + sysname + "Up";
	  sysTreeNames.push_back(NameSys);
	  NameSys = "_" + sysname +"Down";
	  sysTreeNames.push_back(NameSys);
	}
	for (auto sysname : systematicsJES_era) {
	  TString NameSys = "_" + sysname + "Up";
	  sysTreeNames.push_back(NameSys);
	  NameSys = "_" + sysname +"Down";
	  sysTreeNames.push_back(NameSys);
	}
      }
      else {
	for (auto sysname : systematicsTotalJES) {
	  TString NameSys = "_" + sysname + "Up";
	  sysTreeNames.push_back(NameSys);
	  NameSys = "_" + sysname +"Down";
	  sysTreeNames.push_back(NameSys);
	}
      }
      if (channel == "tt") {
	for (auto sysname : systematics_tt) {
	  TString NameSys = "_" + sysname + "Up";
	  sysTreeNames.push_back(NameSys);
	  NameSys = "_" + sysname +"Down";
	  sysTreeNames.push_back(NameSys);
	}
      }
      if (channel == "em") {
	for (auto sysname : systematics_em) {
	  TString NameSys = "_" + sysname + "Up";
	  sysTreeNames.push_back(NameSys);
	  NameSys = "_" + sysname +"Down";
	  sysTreeNames.push_back(NameSys);
	}
      }
    }
  }
  else if (argc==5) {
    TString systName = systematicsMap[SysName];
    sysTreeNames.push_back(systName);
  }

  if (era == "2018"){
     xsec_map    = &xsec_map_2018;
     process_map = &process_map_2018;

  }
  else if(era == "2017"){
    xsec_map    = &xsec_map_2017;
    process_map = &process_map_2017;
  }
  else if(era == "2016_pre"){
    xsec_map    = &xsec_map_2016;
    process_map = &process_map_2016;
  }
  else if(era == "2016_post"){
    xsec_map    = &xsec_map_2016;
    process_map = &process_map_2016;
  }

  std::cout << std::endl;

  // Needed for stitching
  double xsecWIncl = 0;
  double xsecW0Jets = 0;
  double xsecW1Jets = 0;
  double xsecW2Jets = 0;
  double xsecW3Jets = 0;
  double xsecW4Jets = 0;

  double xsecDYIncl  = 0;
  double xsecDY0Jets = 0;
  double xsecDY1Jets = 0;
  double xsecDY2Jets = 0;

  double neventsWIncl = 0;
  double neventsW0Jets  = 0;
  double neventsW1Jets  = 0;
  double neventsW2Jets  = 0;
  double neventsW3Jets  = 0;
  double neventsW4Jets  = 0;

  double neventsDYIncl  = 0;
  double neventsDY0Jets = 0;
  double neventsDY1Jets = 0;
  double neventsDY2Jets = 0;

  if (Sample.Contains("WJets")){
    /*
    neventsWIncl   = getNEventsProcessed(input_dir+"/"+process_map->at("WJets")+".root");
    neventsW0Jets  = getNEventsProcessed(input_dir+"/"+process_map->at("W0Jets")+".root");
    neventsW1Jets  = getNEventsProcessed(input_dir+"/"+process_map->at("W1Jets")+".root");
    neventsW2Jets  = getNEventsProcessed(input_dir+"/"+process_map->at("W2Jets")+".root");
    xsecWIncl      = xsec_map->at(process_map->at("WJets"));
    xsecW0Jets     = xsec_map->at(process_map->at("W0Jets"));
    xsecW1Jets     = xsec_map->at(process_map->at("W1Jets"));
    xsecW2Jets     = xsec_map->at(process_map->at("W2Jets"));
    */

    neventsWIncl   = getNEventsProcessed(input_dir+"/"+process_map->at("WJets")+".root");
    neventsW1Jets  = getNEventsProcessed(input_dir+"/"+process_map->at("W1Jets")+".root");
    neventsW2Jets  = getNEventsProcessed(input_dir+"/"+process_map->at("W2Jets")+".root");
    neventsW3Jets  = getNEventsProcessed(input_dir+"/"+process_map->at("W3Jets")+".root");
    neventsW4Jets  = getNEventsProcessed(input_dir+"/"+process_map->at("W4Jets")+".root");
    xsecWIncl      = xsec_map->at(process_map->at("WJets"));
    xsecW1Jets     = xsec_map->at(process_map->at("W1Jets"));
    xsecW2Jets     = xsec_map->at(process_map->at("W2Jets"));
    xsecW3Jets     = xsec_map->at(process_map->at("W3Jets"));
    xsecW4Jets     = xsec_map->at(process_map->at("W4Jets"));
  }
  if (Sample.Contains("DYJets")){
     neventsDYIncl  = getNEventsProcessed(input_dir+"/"+process_map->at("DYJets")+".root");
     neventsDY0Jets = getNEventsProcessed(input_dir+"/"+process_map->at("DY0Jets")+".root");
     neventsDY1Jets = getNEventsProcessed(input_dir+"/"+process_map->at("DY1Jets")+".root");
     neventsDY2Jets = getNEventsProcessed(input_dir+"/"+process_map->at("DY2Jets")+".root");
     xsecDYIncl     = xsec_map->at(process_map->at("DYJets"));
     xsecDY0Jets    = xsec_map->at(process_map->at("DY0Jets"));
     xsecDY1Jets    = xsec_map->at(process_map->at("DY1Jets"));
     xsecDY2Jets    = xsec_map->at(process_map->at("DY2Jets"));
  }

  // Loop over all samples
  //  cout <<"loop start " << endl;
  for (auto const& sample : samples_map){
    //    cout <<"loop start " << endl;
    cout << sample.first << "  :  " << endl ;
    // creating file -->
    TFile *outFile = NULL; 
    if (argc==4) outFile = new TFile(output_dir + "/" + sample.first + ".root","RECREATE");
    else if (argc==5) outFile = new TFile(output_dir + "/" + sample.first + "_" + SysName + ".root","RECREATE");
    // reading files -->
    std::map<TString,TFile*> files_sample; 
    std::map<TString,TFile*> files_friend;
    std::vector<TString> subsamples;
    subsamples.clear();
    for(TString const& subsample: sample.second) {
      bool FoundSampleInMap=false;
      //      cout << "  - " << subsample << " -> ";
      TString subSample = subsample;

      subsamples.push_back(subSample);

      TFile *inFile = NULL;
      inFile  = new TFile( input_dir + "/" + subsample + ".root" ,"READ");
      if (inFile->IsZombie()||inFile==NULL) {
	std::cout << "unable to open file " << input_dir << "/" << subsample << ".root" << std::endl;
	exit(-1);
      }

      TFile *friendFile =NULL;      
      if(useFriend){
	if (channel=="em")
	  friendFile = new TFile(friend_dir + "/" + subsample + ".root","READ" );
	else 
	  friendFile = new TFile(friend_dir + "/" + subsample + "_pred.root","READ" );
	if (friendFile->IsZombie()||friendFile==NULL) {
	  std::cout << "unable to open file " << friend_dir << "/" << subsample << "_pred.root" << std::endl;
	  std::cout << "quitting..." << std::endl;
	  exit(-1);
	}
      }
      files_sample[subSample] = inFile;
      files_friend[subSample] = friendFile;
    }

    for (auto sysTreeName : sysTreeNames) {
      TString TreeName = "TauCheck" + sysTreeName;
      outFile->cd();
      TTree * outTree = new TTree(TreeName, "tree created as DNN input");
      bool firstTree = true;
      TList* treeList = new TList();
      
      for(auto subsample : subsamples) {
	cout << "  - " << subsample << "   " << TreeName << " -> " << std::endl;
	TFile * inFile = files_sample[subsample];

	TTree *inTree  = NULL;
	inTree = (TTree*)inFile->Get(TreeName);
	if (inTree==NULL) continue;

	TTree *friendTree= NULL;	
	if(useFriend){
	  TFile * friendFile = files_friend[subsample];
	  friendTree=(TTree*)friendFile->Get(TreeName);
	  if (friendTree==NULL) continue;
	  friendTree->SetTreeIndex(0);
	  inTree->AddFriend(friendTree);
	}
	//	std::cout << "InTree : " << inTree << "  FriendTree : " << friendTree << std::endl;
	//	friendTree->Print();

	if( xsec_map->find(subsample) == xsec_map->end() && !subsample.Contains("MuonEG_Run")  && !subsample.Contains("Embedded") && !subsample.Contains("Tau_Run") && !subsample.Contains("")){
	  cout << endl << endl << "Sample " << subsample << " is missing in xsec_map. Exit code." << endl << endl ;
	exit(-1);
	}
	float xsec = 1;
	if(!subsample.Contains("MuonEG_Run") && !subsample.Contains("Embedded") && !subsample.Contains("Tau_Run")) xsec = xsec_map->at(subsample);
	double nevents = getNEventsProcessed( input_dir + "/" + subsample + ".root" );
	
	if(subsample.Contains("MuonEG_Run")||subsample.Contains("Tau_Run"))
	  std::cout << "  nevents = " << nevents << std::endl;
	else
	  std::cout << "  xsec = " << xsec << " ; nevents = " << nevents << " ; lumi = " << luminosity << " -> norm = " << xsec*luminosity/nevents << std::endl;
	
	// SetBranchAddress for variables that need are needed for preselection or stitching
	int gen_noutgoing;
	float iso_1;
	float iso_2;
	int extraelec_veto;
	int extramuon_veto;
	float pt_1;
	float pt_2;
	int tau_decay_mode_1;
	int tau_decay_mode_2;
	int gen_match_1;
	int gen_match_2;
	float trigweight;
	float effweight;
	float pzeta;
	//float mTdileptonMET;
	bool passedAllMetFilters;
	bool trg_muonelectron;
	bool trg_muhigh_elow;
	bool trg_ehigh_mulow;
	unsigned int run;
	int njets;
	float mjj;
	float jdeta;
	float pt_tt;
	/* float pt_ttjj;
	   float dijetpt;*/
	float jpt_1;
	float jpt_2;
	float jeta_1;
	float jeta_2;
	float weightEMu;
	float qcdweight;
	float dr_tt;
	int os;
	float mbb;
	float dRbb;
	int nbtag;
	int pred_class;
	float prob_0,prob_1,prob_2,prob_3,prob_4;
	double prob_tt_0, prob_tt_1, prob_tt_2, prob_tt_3, prob_tt_4;
	float pred_proba;
	float weight;
	bool trg_doubletau;
	int njetspt20_central;
	float puppimet;
	float jleppt_1;
	float byVVLooseDeepTau2017v2p1VSe_1;
	float byVVLooseDeepTau2017v2p1VSe_2;
	float byVLooseDeepTau2017v2p1VSmu_1;
	float byVLooseDeepTau2017v2p1VSmu_2;
	float byVVVLooseDeepTau2017v2p1VSjet_1;
	float byVVVLooseDeepTau2017v2p1VSjet_2;
	float ff_nom;
	// weights ->
	float weight_CMS_QCDScale4;
	float weight_CMS_QCDScale2;
	float weight_CMS_scale_gg_13TeVUp;
	float weight_CMS_scale_gg_13TeVDown;

	inTree->SetBranchAddress("gen_noutgoing",&gen_noutgoing);
	inTree->SetBranchAddress("iso_1",&iso_1);
	inTree->SetBranchAddress("iso_2",&iso_2);
	inTree->SetBranchAddress("extraelec_veto",&extraelec_veto);
	inTree->SetBranchAddress("extramuon_veto",&extramuon_veto);
	inTree->SetBranchAddress("pt_1",&pt_1);
	inTree->SetBranchAddress("pt_2",&pt_2);
	inTree->SetBranchAddress("pzeta",&pzeta);
	//inTree->SetBranchAddress("mTdileptonMET",&mTdileptonMET);
	inTree->SetBranchAddress("passedAllMetFilters",&passedAllMetFilters);
	inTree->SetBranchAddress("run",&run);
	inTree->SetBranchAddress("njets",&njets);
	inTree->SetBranchAddress("mjj",&mjj);
	inTree->SetBranchAddress("jdeta",&jdeta);
	inTree->SetBranchAddress("pt_tt",&pt_tt);
	inTree->SetBranchAddress("jpt_1",&jpt_1);
	inTree->SetBranchAddress("jpt_2",&jpt_2);
	inTree->SetBranchAddress("jeta_1",&jeta_1);
	inTree->SetBranchAddress("jeta_2",&jeta_2);
	inTree->SetBranchAddress("dr_tt",&dr_tt);
	inTree->SetBranchAddress("os",&os);
	inTree->SetBranchAddress("mbb", &mbb);
	inTree->SetBranchAddress("dRbb",&dRbb);
	inTree->SetBranchAddress("nbtag",&nbtag);
	inTree->SetBranchAddress("trg_doubletau",&trg_doubletau);
	inTree->SetBranchAddress("weight",&weight);
	inTree->SetBranchAddress("weight_CMS_QCDScale4",&weight_CMS_QCDScale4);
	inTree->SetBranchAddress("weight_CMS_QCDScale2",&weight_CMS_QCDScale2);
	inTree->SetBranchAddress("weight_CMS_scale_gg_13TeVUp",&weight_CMS_scale_gg_13TeVUp);
	inTree->SetBranchAddress("weight_CMS_scale_gg_13TeVDown",&weight_CMS_scale_gg_13TeVDown);

	// em specific variables
	if (channel=="em") {
	  inTree->SetBranchAddress("trg_muhigh_elow",&trg_muhigh_elow);
	  inTree->SetBranchAddress("trg_ehigh_mulow", &trg_ehigh_mulow);
	  inTree->SetBranchAddress("weightEMu",&weightEMu);
	  inTree->SetBranchAddress("qcdweight",&qcdweight);
	}
	
	// tt specific variables
	if (channel=="tt") {
	  inTree->SetBranchAddress("byVVLooseDeepTau2017v2p1VSe_1",&byVVLooseDeepTau2017v2p1VSe_1);
	  inTree->SetBranchAddress("byVVLooseDeepTau2017v2p1VSe_2",&byVVLooseDeepTau2017v2p1VSe_2);
	  inTree->SetBranchAddress("byVLooseDeepTau2017v2p1VSmu_1",&byVLooseDeepTau2017v2p1VSmu_1);
	  inTree->SetBranchAddress("byVLooseDeepTau2017v2p1VSmu_2",&byVLooseDeepTau2017v2p1VSmu_2);
	  inTree->SetBranchAddress("byVVVLooseDeepTau2017v2p1VSjet_1",&byVVVLooseDeepTau2017v2p1VSjet_1);
	  inTree->SetBranchAddress("byVVVLooseDeepTau2017v2p1VSjet_2",&byVVVLooseDeepTau2017v2p1VSjet_2);
	  inTree->SetBranchAddress("njetspt20_central",&njetspt20_central);
	  inTree->SetBranchAddress("jleppt_1",&jleppt_1);
	  inTree->SetBranchAddress("puppimet",&puppimet);
	  inTree->SetBranchAddress("ff_nom",&ff_nom);
	  inTree->SetBranchAddress("tau_decay_mode_1",&tau_decay_mode_1);
	  inTree->SetBranchAddress("tau_decay_mode_2",&tau_decay_mode_2);
	  inTree->SetBranchAddress("gen_match_1",&gen_match_1);
	  inTree->SetBranchAddress("gen_match_2",&gen_match_2);
	  inTree->SetBranchAddress("trigweight",&trigweight);
	  inTree->SetBranchAddress("effweight",&effweight);
	}
	
	// Check for tt channel !!!
	if(useFriend){
	  if (channel=="em") { // em	
	    inTree->SetBranchAddress("pred_class",&pred_class);
	    inTree->SetBranchAddress("pred_proba",&pred_proba);
	    inTree->SetBranchAddress("prob_0",&prob_0);
	    inTree->SetBranchAddress("prob_1",&prob_1);
	    inTree->SetBranchAddress("prob_2",&prob_2);
	    inTree->SetBranchAddress("prob_3",&prob_3);
	    inTree->SetBranchAddress("prob_4",&prob_4);
	  }
	  else { // tt
	    inTree->SetBranchAddress("pred_class",&pred_class);
	    inTree->SetBranchAddress("pred_class_proba",&pred_proba);
	    inTree->SetBranchAddress("pred_class_0_proba",&prob_tt_0);
	    inTree->SetBranchAddress("pred_class_1_proba",&prob_tt_1);
	    inTree->SetBranchAddress("pred_class_2_proba",&prob_tt_2);
	    inTree->SetBranchAddress("pred_class_3_proba",&prob_tt_3);
	    inTree->SetBranchAddress("pred_class_4_proba",&prob_tt_4);
	  }
	}

	outFile->cd();
      
	TTree *currentTree = new TTree(subsample,"temporary tree");

	// Create a branch for xsec_lumi_weight
	float xsec_lumi_weight;
	float ff_tt;
	float ff_sys[20];
	std::vector<std::string> ff_sysnames = {
	  "qcd_stat_dR_unc1",
	  "qcd_stat_dR_unc2",
	  "qcd_stat_pt_unc1",
	  "qcd_stat_pt_unc2",
	  "qcd_syst",
	  "qcd_syst_dr_closure",
	  "qcd_syst_pt_2_closure",
	  "qcd_syst_met_closure",
	  "syst_alt_func"
	};
	
	if(firstTree){
	  outTree    = inTree->CloneTree(0);
	  outTree->Branch("xsec_lumi_weight", &xsec_lumi_weight, "xsec_lumi_weight/F");
	  if (channel=="tt") {
	    outTree->Branch("ff_total",&ff_tt,"ff_total/F");
	    for (unsigned int i=0; i<ff_sysnames.size(); ++i) {
	      outTree->Branch("ff_"+TString(ff_sysnames[i]),&ff_sys[i],"ff_"+TString(ff_sysnames[i])+"/F");
	    }
	  }
	  if(useFriend){
	    outTree->Branch("pred_class",&pred_class,"pred_class/I");
	    outTree->Branch("pred_class_proba",&pred_proba,"pred_class_proba/F");
	    outTree->Branch("pred_class_0_proba",&prob_0,"pred_class_0_proba/F");
	    outTree->Branch("pred_class_1_proba",&prob_1,"pred_class_1_proba/F");
	    outTree->Branch("pred_class_2_proba",&prob_2,"pred_class_2_proba/F");
	    outTree->Branch("pred_class_3_proba",&prob_3,"pred_class_3_proba/F");
	    outTree->Branch("pred_class_4_proba",&prob_4,"pred_class_4_proba/F");
	  }
	  firstTree  = false;
	}
	currentTree = inTree->CloneTree(0);
	currentTree->Branch("xsec_lumi_weight", &xsec_lumi_weight, "xsec_lumi_weight/F");
	if (channel=="tt") {
	  currentTree->Branch("ff_total",&ff_tt,"ff_total/F");
	  for (unsigned int i=0; i<ff_sysnames.size(); ++i) {
	    currentTree->Branch("ff_"+TString(ff_sysnames[i]),&ff_sys[i],"ff_"+TString(ff_sysnames[i])+"/F");
	  }
	}
	if(useFriend){
	  currentTree->Branch("pred_class",&pred_class,"pred_class/I");
	  currentTree->Branch("pred_class_proba",&pred_proba,"pred_class_proba/F");
	  currentTree->Branch("pred_class_0_proba",&prob_0,"pred_class_0_proba/F");
	  currentTree->Branch("pred_class_1_proba",&prob_1,"pred_class_1_proba/F");
	  currentTree->Branch("pred_class_2_proba",&prob_2,"pred_class_2_proba/F");
	  currentTree->Branch("pred_class_3_proba",&prob_3,"pred_class_3_proba/F");
	  currentTree->Branch("pred_class_4_proba",&prob_4,"pred_class_4_proba/F");
	}
	// lumi-xsec-weight added

	for (int i=0; i<inTree->GetEntries(); i++) {
	  inTree->GetEntry(i);
	  trg_muonelectron = (trg_muhigh_elow && pt_2 > 24) || (trg_ehigh_mulow && pt_1 > 24);
	  // Add here preselection if necessary
	  weight_CMS_scale_gg_13TeVUp = TMath::Max(float(0.01),TMath::Min(float(5.0),weight_CMS_QCDScale4));
	  weight_CMS_scale_gg_13TeVDown = 1.0/weight_CMS_scale_gg_13TeVUp;
	  // use different QCD scale
	  if (process.Contains("_YB2")||process.Contains("_YBY2")) {
	    weight_CMS_scale_gg_13TeVUp = TMath::Max(float(0.01),TMath::Min(float(5.0),weight_CMS_QCDScale2));
	    weight_CMS_scale_gg_13TeVDown = 1.0/weight_CMS_scale_gg_13TeVUp;
	  }
	  if(applyPreselection){
	    if (channel=="em") {
	      if( iso_1 > 0.5 )                continue;
	      if( iso_2 > 0.5 )                continue;
	      if( extraelec_veto > 0.5 )       continue;
	      if( extramuon_veto > 0.5 )       continue;
	      if( dr_tt < 0.3)                 continue;
	      if( pt_1 < 15 )                  continue;
	      if( pt_2 < 15 )                  continue;
	      //	    if( TMath::Max(pt_1,pt_2) < 24 ) continue;
	      //if( pzeta< -50 )                 continue;
	      //if( mTdileptonMET > 90 )         continue;
	      //if( passedAllMetFilters < 0.5 )           continue;
	      if( trg_muonelectron < 0.5 )     continue;
	    }
	    else if (channel=="tt") {
	      /*
		std::cout << "pt_1 = " << pt_1 << std::endl;
		std::cout << "pt_2 = " << pt_2 << std::endl;
		std::cout << "extraelec_veto = " << extraelec_veto << std::endl;
		std::cout << "extramuon_veto = " << extramuon_veto << std::endl;
		std::cout << "trg_doubletau  = " << trg_doubletau << std::endl;
		std::cout << "dr_tt = " << dr_tt << std::endl;
		std::cout << "byVVLooseDeepTau2017v2p1VSe_1 = " << byVVLooseDeepTau2017v2p1VSe_1 << std::endl;
		std::cout << "byVVLooseDeepTau2017v2p1VSe_2 = " << byVVLooseDeepTau2017v2p1VSe_2 << std::endl;
		std::cout << "byVLooseDeepTau2017v2p1VSmu_1 = " << byVLooseDeepTau2017v2p1VSmu_1 << std::endl;
		std::cout << "byVLooseDeepTau2017v2p1VSmu_2 = " << byVLooseDeepTau2017v2p1VSmu_2 << std::endl;
		std::cout << "byVVVLooseDeepTau2017v2p1VSjet_1 = " << byVVVLooseDeepTau2017v2p1VSjet_1 << std::endl;
		std::cout << "byVVVLooseDeepTau2017v2p1VSjet_2 = " << byVVVLooseDeepTau2017v2p1VSjet_2 << std::endl;
		std::cout << std::endl;
	      */
	      if ( pt_1 < 35 ) continue;
	      if ( pt_2 < 35 ) continue;
	      if ( extraelec_veto > 0.5 ) continue;
	      if ( extramuon_veto > 0.5 ) continue;
	      if ( trg_doubletau < 0.5) continue;
	      if ( dr_tt < 0.5 ) continue;
	      if ( byVVLooseDeepTau2017v2p1VSe_1 < 0.5 ) continue;
	      if ( byVVLooseDeepTau2017v2p1VSe_2 < 0.5 ) continue;
	      if ( byVLooseDeepTau2017v2p1VSmu_1 < 0.5 ) continue;
	      if ( byVLooseDeepTau2017v2p1VSmu_2 < 0.5 ) continue;
	      if ( byVVVLooseDeepTau2017v2p1VSjet_1 < 0.5 ) continue;
	      if ( byVVVLooseDeepTau2017v2p1VSjet_2 < 0.5 ) continue;
	      /*
		std::cout << "pt     = " << pt_1 << std::endl;
		std::cout << "njets  = " << njetspt20_central << std::endl;
		std::cout << "nbjets = " << nbtag << std::endl;
		std::cout << "os     = " << os << std::endl;
		std::cout << "dR     = " << dr_tt << std::endl;
		std::cout << "pt_2   = " << pt_2 << std::endl;
		std::cout << "met    = " << puppimet << std::endl;
		std::cout << "jetpt  = " << jleppt_1 << std::endl;
	      */
	    }
	  }
	  // Fake background tt channel
	  if (channel=="tt") {
	    w_fakefactors->var("pt")->setVal(pt_1);
	    int njets_for_ff = njetspt20_central;
	    if (process=="Tau") njets_for_ff = njets;
	    w_fakefactors->var("njets")->setVal(njets_for_ff);
	    w_fakefactors->var("nbjets")->setVal(nbtag);
	    w_fakefactors->var("os")->setVal(os);
	    w_fakefactors->var("dR")->setVal(dr_tt);
	    w_fakefactors->var("pt_2")->setVal(pt_2);
	    w_fakefactors->var("met")->setVal(puppimet);
	    w_fakefactors->var("jetpt")->setVal(jleppt_1);
	    double ff_central = w_fakefactors->function("ff_total")->getVal();
	    double ff_base = ff_central;
	    if (process=="Tau") ff_base = ff_nom;
	    prob_0 = float(prob_tt_0);
	    prob_1 = float(prob_tt_1);
	    prob_2 = float(prob_tt_2);
	    prob_3 = float(prob_tt_3);
	    prob_4 = float(prob_tt_4);
	    if (nbtag>=1) {
	      ff_tt =  ff_base * scaleFake_btag;
	    }
	    else {
	      ff_tt =  ff_base * scaleFake;
	    }
	    //	    std::cout << "ff_total = " << ff_tt << std::endl;
	    for (unsigned int isys = 0; isys < ff_sysnames.size(); ++isys) {
	      ff_sys[isys] = w_fakefactors->function(("ff_total_"+ff_sysnames[isys]+"_up").c_str())->getVal()/ff_central;
	      //	      std::cout << ff_sysnames[isys] << " : " << ff_sys[isys] << std::endl;
	    }
	    //	    std::cout << std::endl;
	  }

	  // Replace jet variables to have an effectie cut of jetpt > 30 GeV
	  if(njets < 2){
	    jdeta   = -10;
	    mjj     = -10;
	    //dijetpt = -10;
	    //pt_ttjj = -10;
	    jpt_2   = -10;
	    jeta_2  = -10;
	 
	    if(njets < 1){
	      jpt_1 = -10;
	      jeta_1= -10;
	    }
	  }
	  if(nbtag < 2){
	    mbb     = -10;
	    dRbb    = -10;
	  }
	  
	  xsec_lumi_weight = xsec*luminosity/nevents;
	  
	  // Stitching only for wjets MC in n-jet binned samples in npartons
	  //	  if( subsample.Contains("W") && subsample.Contains("JetsToLNu") ){
	  //	    if(gen_noutgoing== 1)      xsec_lumi_weight = luminosity / ( neventsW1Jets/xsecW1Jets + neventsWIncl/xsecWIncl );
	  //	    else if(gen_noutgoing== 2) xsec_lumi_weight = luminosity / ( neventsW2Jets/xsecW2Jets + neventsWIncl/xsecWIncl );
	  //	    else if(gen_noutgoing== 3) xsec_lumi_weight = luminosity / ( neventsW3Jets/xsecW3Jets + neventsWIncl/xsecWIncl );
	  //	    else if(gen_noutgoing== 4) xsec_lumi_weight = luminosity / ( neventsW4Jets/xsecW4Jets + neventsWIncl/xsecWIncl );
	  //	    else                       xsec_lumi_weight = luminosity / ( neventsWIncl/xsecWIncl );
	  //	    if(gen_noutgoing==0)      xsec_lumi_weight = luminosity / ( neventsW0Jets/xsecW0Jets + neventsWIncl/xsecWIncl );
	  //	    else if(gen_noutgoing==1) xsec_lumi_weight = luminosity / ( neventsW1Jets/xsecW1Jets + neventsWIncl/xsecWIncl );
	  //	    else if(gen_noutgoing==2) xsec_lumi_weight = luminosity / ( neventsW2Jets/xsecW2Jets + neventsWIncl/xsecWIncl );
	  //	    else                      xsec_lumi_weight = luminosity / ( neventsWIncl/xsecWIncl );
	  //
	  //	  } //changed the DYJETS for amcatnlo
	  if( subsample.Contains("DY") && subsample.Contains("amcatnlo") ){
	    if(gen_noutgoing==0)      xsec_lumi_weight = luminosity / ( neventsDY0Jets/xsecDY0Jets + neventsDYIncl/xsecDYIncl );
	    else if(gen_noutgoing==1) xsec_lumi_weight = luminosity / ( neventsDY1Jets/xsecDY1Jets + neventsDYIncl/xsecDYIncl );
	    else if(gen_noutgoing==2) xsec_lumi_weight = luminosity / ( neventsDY2Jets/xsecDY2Jets + neventsDYIncl/xsecDYIncl );
	    else                      xsec_lumi_weight = luminosity / ( neventsDYIncl/xsecDYIncl );
	  }
	  
	  if (subsample.Contains("MuonEG_Run")||
	      subsample.Contains("Tau_Run")||
	      subsample.Contains("Embedded")) xsec_lumi_weight = 1.0;
	  
	  //	std::cout << "xsec_lumi_weight = " << xsec_lumi_weight << std::endl;
	  
	  if (channel=="em")
	    xsec_lumi_weight = xsec_lumi_weight * weightEMu;
	  else if (channel=="tt") {
	    xsec_lumi_weight = xsec_lumi_weight * weight;
	  
	    if (recomputeTauID) {
	      float tauIdWeight = tauIDWeight(era,
					      tau_decay_mode_1,
					      gen_match_1,
					      pt_1,
					      tau_decay_mode_2,
					      gen_match_2,
					      pt_2,
					      effweight,
					      trigweight);
	      xsec_lumi_weight *= tauIdWeight;
	    }
	    else { // ad-hoc corrections to DY
	      if (channel=="tt"&&subsample.Contains("DY") && subsample.Contains("amcatnlo")) {
		if (nbtag>=1) xsec_lumi_weight *= scaleDY_btag;
		else xsec_lumi_weight *= scaleDY;
	      }
	    }
	  }
	  
	  currentTree->Fill();
	}
	//	cout<< " Entries (current tree) = " << currentTree->GetEntries() << endl;
	treeList->Add(currentTree);
      }
      outTree = TTree::MergeTrees(treeList);
      cout << endl;
      cout << " Entries (all trees) = " << outTree->GetEntries() << endl;
      cout << endl;
      outTree  -> Write( "" , TObject::kOverwrite );
      treeList -> Delete();
    
    }
    //    for (auto subSample : subsamples) {
    //      TFile * inFile = files_sample[subSample];
    //      inFile->Delete();
    //    }
    outFile  -> Close();
  }
  cout << endl; 
}
