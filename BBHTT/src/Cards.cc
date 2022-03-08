#ifndef Cards_ccx
#define Cards_ccx

#include "DesyTauAnalyses/BBHTT/interface/Cards.h"

Cards::Cards(TString Sample,
	     TString Era,
	     TString Category,
	     TString Channel,
	     TString InputDir,
	     TString PredDir,
	     TString OutputDir,
	     TString Variable,
	     int nbins,
	     double xmin,
	     double xmax,
	     bool RunWithSystematics,
	     bool RunOnEmbedded) {

  era = Era;
  channel = Channel;
  input_dir = InputDir;
  /*
  input_friend_dir = "/nfs/dust/cms/user/filatovo/ML/ml-framework/mlruns/2/5cb31f2f24b84f27bf28ae05b44b2793/artifacts/pred/";
  if (era=="2017")
    input_friend_dir = "/nfs/dust/cms/user/filatovo/ML/ml-framework/mlruns/2/cafd0046bd7f4dc0a2ba4e37cd3aa0e3/artifacts/pred/";
  if (era=="2018")
    input_friend_dir = "/nfs/dust/cms/user/filatovo/ML/ml-framework/mlruns/2/1f14e963a7d14425909831c02fd49617/artifacts/pred/";
  */
  input_friend_dir = PredDir;
  runWithShapeSystematics = false;
  output_filename = OutputDir+"/"+Sample+"_"+Category+".root";
  sampleToProcess = Sample;
  category = channel+"_"+Category;
  variable = Variable;
  runWithSystematics = RunWithSystematics;
  runOnEmbedded = RunOnEmbedded;

  _usefriend=true;
  if(PredDir=="")_usefriend=false;

  if(era=="2016"){
    lumi = 59740;
    sampleXSecMap = xsecs_2016;
  }else if(era=="2017"){
    lumi = 41500;
    sampleXSecMap = xsecs_2017;
  }else{
    lumi = 35890;
    sampleXSecMap = xsecs_2018;
  }

  if(channel=="em"){
    commonCuts=baselineEM;
    mcNotTauTau=mcNotTauTau_EM;
    mcTauTau=mcTauTau_EM;
    if(era=="2016"){
      Embedded=EmbeddedElMu_2016;
      Data = DataElMu_2016;
    }else if(era=="2017"){
      Embedded=EmbeddedElMu_2017;
      Data = DataElMu_2017;
    }else{
      Embedded=EmbeddedElMu_2018;
      Data = DataElMu_2018;
    }
  }else{
    commonCuts=baselineTT;
    mcNotTauTau=mcNotTauTau_TT;
    mcTauTau=mcTauTau_TT;
    if(era=="2016"){
      Embedded=EmbeddedTauTau_2016;
      Data = DataTauTau_2016;
    }else if(era=="2017"){
      Embedded=EmbeddedTauTau_2017;
      Data = DataTauTau_2017;
    }else{
      Embedded=EmbeddedTauTau_2018;
      Data = DataTauTau_2018;
    }
  }


  block = false;

  if (xmin>xmax) {
    std::cout << "warning -> xmin for histogram  : " << xmin << " is greater than xmax : " << xmax << std::endl;
    std::cout << "nothing will be done..." << std::endl;
    block = true;
    return;
  }

  nBins = nbins;
  double binWidth = (xmax-xmin)/double(nBins);
  for (int iB=0; iB<=nBins; ++iB)
    Bins[iB] = xmin + double(iB)*binWidth;


  if (sampleToProcess!="Data"&&
      sampleToProcess!="EWK"&&
      sampleToProcess!="TTbar"&&
      sampleToProcess!="TTbarToTT"&&
      sampleToProcess!="EWKToTT"&&
      sampleToProcess!="WJets"&&
      sampleToProcess!="DYJets"&&
      sampleToProcess!="EMB"&&
      sampleToProcess!="ggH"&&
      sampleToProcess!="ggHbb"&&
      sampleToProcess!="qqH"&&
      sampleToProcess!="VH"&&
      sampleToProcess!="bbHybyt"&&
      sampleToProcess!="bbH") {
    std::cout << "Unknown sample specified : " << sampleToProcess << std::endl;
    std::cout << "Nothing will be done" << std::endl;
    block = true;
    return;
  }  

  if (category!=channel+"_inclusive"&&
      category!=channel+"_Nbtag0"&&
      category!=channel+"_Nbtag1"&&
      category!=channel+"_Nbtag2"&&
      category!=channel+"_NbtagGe2"&&
      category!=channel+"_NbtagGe1"&&
      category!=channel+"_cat0"&&
      category!=channel+"_cat1"&&
      category!=channel+"_cat2"&&
      category!=channel+"_cat3"&& 
      category!=channel+"_cat0_NbtagGt1"&&
      category!=channel+"_cat1_NbtagGt1"&&
      category!=channel+"_cat2_NbtagGt1"&&
      category!=channel+"_cat3_NbtagGt1") {
    std::cout << "Unknown category specified : " << category << std::endl;
    std::cout << "nothing will be done" << std::endl;
    block = true;
    return;
  }

  std::map<TString,TString> categoryCuts = {
    {channel+"_inclusive",""},
    {channel+"_Nbtag0",   "&&nbtag==0"},
    {channel+"_Nbtag1",   "&&nbtag==1"},
    {channel+"_Nbtag2",   "&&nbtag==2"},
    {channel+"_NbtagGe1", "&&nbtag>=1"},
    {channel+"_NbtagGe2", "&&nbtag>=2"},
    {channel+"_cat0", "&&pred_class==0"},
    {channel+"_cat1", "&&pred_class==1"},
    {channel+"_cat2", "&&pred_class==2"},
    {channel+"_cat3", "&&pred_class==3"},
    {channel+"_cat0_NbtagGt1", "&&pred_class==0&&nbtag>0"},
    {channel+"_cat1_NbtagGt1", "&&pred_class==1&&nbtag>0"},
    {channel+"_cat2_NbtagGt1", "&&pred_class==2&&nbtag>0"},
    {channel+"_cat3_NbtagGt1", "&&pred_class==3&&nbtag>0"},
  };

  TH1::SetDefaultSumw2(true);
  TH2::SetDefaultSumw2(true);
  isEquidistantBinning = true;
  if (variable=="mt_tot")
    isEquidistantBinning = false;

  isBTag = false;
  if (Category.Contains("_Nbtag1")||Category.Contains("_Nbtag2")||Category.Contains("_NbtagGe1")||Category.Contains("_NbtagGe2"))
    isBTag = true;

  outputFile = new TFile(output_filename,"recreate");
  if (outputFile->IsZombie()) {
    std::cout << "Cannot open file" << output_filename << std::endl;
    std::cout << "Nothing will be done" << std::endl;
    block = true;
    return;
  }
  outputFile->mkdir(category);


  commonCuts += categoryCuts[category];

  // btagCorrection
  //  btagCorr["2016"][channel+"_Nbtag0"] = 1.0;
  //  btagCorr_Cat["2016"][channel+"_Nbtag1"] = 0.9;
  //  btagCorr_Cat["2016"][channel+"_Nbtag2"] = 0.8;

  regionCut.clear();
  if(channel=="tt"){
    regionCut.push_back(commonCuts+signalRegion); // SR
    regionCut.push_back(commonCuts+fakesSideBand); // Fake AR
    regionCut.push_back(commonCuts+signalRegion); // Single Fake region
  }else{
    regionCut.push_back(commonCuts+oppositeSignRegion); // opposite sign
    regionCut.push_back(commonCuts+sameSignRegion); // same sign
  }

  globalWeight = "weightEMu*";
  regionWeight.clear();
  regionWeight.push_back(globalWeight);

  TString QCDFFWeight = "";
  if(channel=="em")
    QCDFFWeight=qcdWeight;
  else
    QCDFFWeight = FFWeight + FF_pt2_era[era] + FF_btg_era[era];
 
  regionWeight.push_back(globalWeight+QCDFFWeight);
  if(channel=="tt") regionWeight.push_back(globalWeight);


  nameSampleMap["Data"] = Data; nameHistoMap["Data"] = "data_obs";
  nameSampleMap["DYJetsToLL"] = DYJetsToLL; nameHistoMap["DYJetsToLL"] = "ZL"; 
  nameSampleMap["DYJetsToTT"] = DYJetsToTT; nameHistoMap["DYJetsToTT"] = "ZTT";
  nameSampleMap["DYJetsLowToLL"] = DYJets_Low; nameHistoMap["DYJetsLowToLL"] = "ZL"; 
  nameSampleMap["DYJetsLowToTT"] = DYJets_Low; nameHistoMap["DYJetsLowToTT"] = "ZTT";
  nameSampleMap["WJets"] = WJets; nameHistoMap["WJets"] = "W";
  nameSampleMap["TTbar"] = TT; nameHistoMap["TTbar"] = "TTL";
  nameSampleMap["TTbarToTT"] = TTToTT; nameHistoMap["TTbarToTT"] = "TTT";
  nameSampleMap["EWK"] = EWK; nameHistoMap["EWK"] = "VVL";
  nameSampleMap["EWKToTT"] = EWKToTT; nameHistoMap["EWKToTT"] = "VVT";
  nameSampleMap["EMB"] = Embedded; nameHistoMap["EMB"] = "EMB";
  nameSampleMap["ggHWW125"] = GluGluHToWW; nameHistoMap["ggHWW125"] = "ggHWW125";
  nameSampleMap["qqHWW125"] = VBFHToWW; nameHistoMap["qqHWW125"] = "qqHWW125";
  nameSampleMap["WHWW125"] = WHToWW; nameHistoMap["WHWW125"] = "WHWW125";
  nameSampleMap["ZHWW125"] = ZHToWW; nameHistoMap["ZHWW125"] = "ZHWW125";
  nameSampleMap["ggHTT125"] = GluGluHToTauTau; nameHistoMap["ggHTT125"] = "ggH125";
  nameSampleMap["ggHbbTT125"] = GluGluHToTauTau; nameHistoMap["ggHbbTT125"] = "ggHbb125";
  nameSampleMap["qqHTT125"] = VBFHToTauTau; nameHistoMap["qqHTT125"] = "qqH125";
  nameSampleMap["WHTT125"] = WHToTauTau; nameHistoMap["WHTT125"] = "WH125";
  nameSampleMap["ZHTT125"] = ZHToTauTau; nameHistoMap["ZHTT125"] = "ZH125";
  nameSampleMap["bbHTTybyt125"] = bbHybytToTauTau; nameHistoMap["bbHybytTT125"] = "bbHybyt125";
  nameSampleMap["bbHTT125"] = bbHToTauTau; nameHistoMap["bbHTT125"] = "bbH125";

  samplesContainer.clear();
  if (sampleToProcess=="Data") {
    InitializeSample("Data");
    if (runOnEmbedded) {
      samplesContainer.push_back("EMB");
    }
    else{ 
      samplesContainer.push_back("EWKToTT");
      samplesContainer.push_back("DYJetsToTT");
      samplesContainer.push_back("TTbarToTT");
    }
    samplesContainer.push_back("WJets");
    samplesContainer.push_back("EWK");
    samplesContainer.push_back("TTbar");
    samplesContainer.push_back("DYJetsToLL");
  }
  if (sampleToProcess=="TTbar") {
    samplesContainer.push_back("TTbar");
  }
  if (sampleToProcess=="TTbarToTT") {
    samplesContainer.push_back("TTbarToTT");
  }
  if (sampleToProcess=="EMB") {
    samplesContainer.push_back("EMB");
    InitializeSample("TTbarToTT");
  }
  if (sampleToProcess=="DYJets") {
    samplesContainer.push_back("DYJetsToLL");
    if (!runOnEmbedded) 
      samplesContainer.push_back("DYJetsToTT");
  }
  if (sampleToProcess=="EWK") {
    samplesContainer.push_back("EWK");
  }
  if (sampleToProcess=="EWKToTT") {
    samplesContainer.push_back("EWKToTT");
  }
  if (sampleToProcess=="WJets") {
    samplesContainer.push_back("WJets");    
  }
  if (sampleToProcess=="ggH") {
    samplesContainer.push_back("ggHTT125");
  }
  if (sampleToProcess=="ggHbb") {
    samplesContainer.push_back("ggHbbTT125");
  }
  if (sampleToProcess=="qqH") {
    samplesContainer.push_back("qqHTT125");
  }
  if (sampleToProcess=="VH") {
    samplesContainer.push_back("WHTT125");
    samplesContainer.push_back("ZHTT125");
  }
  if (sampleToProcess=="bbH") {
    samplesContainer.push_back("bbHTT125");
  }
  if (sampleToProcess=="bbHybyt") {
    samplesContainer.push_back("bbHTTybyt125");
  }

  InitializeSamples();

  numberOfShapeSystematics = CreateShapeSystematicsMap();
  numberOfWeightSystematics = CreateWeightSystematicsMap();
  
}

std::vector<TString> Cards::SampleSpecificCutTT(TString name, TString sampleName) {
  TString mcSR("");
  TString mcSB("");
  TString mcSF("");
  TString ngenPartonsCut("");

  if (name=="ggHbbTT125") {
    ngenPartonsCut = "&&gen_nbjets>=1";
  }
  
  if (name=="ggHTT125") {
    ngenPartonsCut = "&&gen_nbjets==0";
  }


  if (name=="EMB") {
    mcSR = mcTauTau;
    mcSB = mcSideBand;
    mcSF = mcSingleFake;
  }

  if ((name=="TTbar"||name=="EWK"||name=="WJets")) {
    mcSR = mcNotTauTau + mcNotFakes;
    mcSB = mcSideBand;
    mcSF = mcSingleFake;
  }
  if (name=="TTbarToTT"||name=="EWKToTT"||name=="DYJetsToTT") {
    mcSR = mcTauTau;
    mcSB = mcSideBand;
    mcSF = mcSingleFake;
  }
  if (name=="DYJetsToLL") {
    mcSR = mcNotTauTau + mcNotFakes;
    mcSB = mcSideBand + mcNotTauTau;
    mcSF = mcSingleFake + mcNotTauTau;
  }

  if (sampleName.Contains("WJetsToLNu_0")||
      sampleName.Contains("DYJetsToLL_M-50_0")||
      sampleName.Contains("DYJetsToTT_M-50_0"))
    ngenPartonsCut = "&&(gen_noutgoing==0||gen_noutgoing>4)";

  if (sampleName.Contains("WJetsToLNu_1")||
      sampleName.Contains("DYJetsToLL_M-50_1")||
      sampleName.Contains("DYJetsToTT_M-50_1"))
    ngenPartonsCut = "&&gen_noutgoing==1";

  if (sampleName.Contains("WJetsToLNu_2")||
      sampleName.Contains("DYJetsToLL_M-50_2")||
      sampleName.Contains("DYJetsToTT_M-50_2"))
    ngenPartonsCut = "&&gen_noutgoing==2";

  if (sampleName.Contains("WJetsToLNu_3")||
      sampleName.Contains("DYJetsToLL_M-50_3")||
      sampleName.Contains("DYJetsToTT_M-50_3"))
    ngenPartonsCut = "&&gen_noutgoing==3";

  if (sampleName.Contains("WJetsToLNu_4")||
      sampleName.Contains("DYJetsToLL_M-50_4")||
      sampleName.Contains("DYJetsToTT_M-50_4"))
    ngenPartonsCut = "&&gen_noutgoing==4";


  std::vector<TString> Cuts; Cuts.clear();
  Cuts.push_back(mcSR+ngenPartonsCut);
  Cuts.push_back(mcSB+ngenPartonsCut);
  Cuts.push_back(mcSF+ngenPartonsCut);

  return Cuts;
}


std::vector<TString> Cards::SampleSpecificCutEM(TString name, TString sampleName) {
  TString mcOS("");
  TString mcSS("");
  TString ngenPartonsCut("");

  if (name=="ggHbbTT125") {
    ngenPartonsCut = "&&gen_nbjets>=1";
  }
  
  if (name=="ggHTT125") {
    ngenPartonsCut = "&&gen_nbjets==0";
  }


  if (name=="EMB") {
    mcOS = mcTauTau;
    mcSS = mcTauTau;
  }

  if ((name=="TTbar"||name=="EWK"||name=="WJets")) {
    mcOS = mcNotTauTau;
    mcSS = mcNotTauTau;
  }
  if (name=="TTbarToTT"||name=="EWKToTT"||name=="DYJetsToTT") {
    mcOS = mcTauTau;
    mcSS = mcTauTau;
  }
  if (name=="DYJetsToLL") {
    mcOS = mcNotTauTau;
    mcSS = mcNotTauTau;
  }

  if (sampleName.Contains("WJetsToLNu_0")||
      sampleName.Contains("DYJetsToLL_M-50_0")||
      sampleName.Contains("DYJetsToTT_M-50_0"))
    ngenPartonsCut = "&&(gen_noutgoing==0||gen_noutgoing>4)";

  if (sampleName.Contains("WJetsToLNu_1")||
      sampleName.Contains("DYJetsToLL_M-50_1")||
      sampleName.Contains("DYJetsToTT_M-50_1"))
    ngenPartonsCut = "&&gen_noutgoing==1";

  if (sampleName.Contains("WJetsToLNu_2")||
      sampleName.Contains("DYJetsToLL_M-50_2")||
      sampleName.Contains("DYJetsToTT_M-50_2"))
    ngenPartonsCut = "&&gen_noutgoing==2";

  if (sampleName.Contains("WJetsToLNu_3")||
      sampleName.Contains("DYJetsToLL_M-50_3")||
      sampleName.Contains("DYJetsToTT_M-50_3"))
    ngenPartonsCut = "&&gen_noutgoing==3";

  if (sampleName.Contains("WJetsToLNu_4")||
      sampleName.Contains("DYJetsToLL_M-50_4")||
      sampleName.Contains("DYJetsToTT_M-50_4"))
    ngenPartonsCut = "&&gen_noutgoing==4";


  std::vector<TString> Cuts; Cuts.clear();
  Cuts.push_back(mcOS+ngenPartonsCut);
  Cuts.push_back(mcSS+ngenPartonsCut);

  return Cuts;
}

void Cards::InitializeSample(TString name) {

  std::vector<TString> sampleNames = nameSampleMap[name];
  for (auto sampleName : sampleNames) {
    TString baseFileName = sampleName;
    cout << name << " ----" << baseFileName << endl;
    if (name=="DYJetsToLL") 
      baseFileName = "DYJetsToLL_M-50";
      //baseFileName = DYJetsLLFiles[sampleName];
    if (name=="DYJetsToTT") 
      baseFileName = "DYJetsToLL_M-50";
      //baseFileName = DYJetsTTFiles[sampleName];
    if (name=="EWKToTT") 
      baseFileName.ReplaceAll("ToTT","");
    if (name=="TTbarToTT") 
      baseFileName.ReplaceAll("ToTT","");
    if (name=="WJets") 
      baseFileName = WJetsFiles[sampleName];
    TString fullPathName = input_dir + "/" + baseFileName + "_"+era+".root";
    std::cout << "file " << fullPathName << std::endl;
    TFile * file = new TFile(fullPathName);

    if (file->IsZombie()) {
      std::cout << "cannot open file " << fullPathName << std::endl;
      std::cout << "nothing will be done " << std::endl;
      block = true;
      return;
    }

    TTree * tree = (TTree*)file->Get("TauCheck");
    TString friendName = "";
    if(_usefriend){
      if(channel=="tt")
	friendName=input_friend_dir+baseFileName+"_pred.root";
      else
	friendName=input_friend_dir+channel+"-"+baseFileName+".root";
      tree->AddFriend("TauCheck",friendName);
    }

    sampleFileMap[sampleName] = file;
    TH1D * histEvents = (TH1D*)file->Get("nWeightedEvents");
    sampleNeventsMap[sampleName] = histEvents->GetSumOfWeights();
    if(channel=="em")sampleSpecificCutMap[sampleName] = SampleSpecificCutEM(name,sampleName);
    else sampleSpecificCutMap[sampleName] = SampleSpecificCutTT(name,sampleName);


    if(!(name.Contains("DYJets")||name.Contains("WJets"))){
 
       if (name=="Data"||name=="EMB")
	 sampleNormMap[sampleName] = 1.0;
       else {
	 cout << "lumi-" << lumi << "    sampleXSecMap[sampleName]-" << sampleXSecMap[sampleName]  << "    sampleNeventsMap[sampleName]-" << sampleNeventsMap[sampleName] << endl;
	 sampleNormMap[sampleName] = lumi*sampleXSecMap[baseFileName]/sampleNeventsMap[sampleName];
	 if(sampleToProcess=="ggHbb") sampleNormMap[sampleName] *= ggHbb_scale;
       }
    }
  }


  
  if (name.Contains("DYJetsToLL")) {

    // float nIncl = sampleNeventsMap["DYJetsToLL_M-50_0"];
    float nIncl = sampleNeventsMap["DYJetsToLL_M-50"];
    float xsecIncl = sampleXSecMap["DYJetsToLL_M-50"];

    float n1Jet = sampleNeventsMap["DY1JetsToLL_M-50"];
    float xsec1Jet = sampleXSecMap["DY1JetsToLL_M-50"];

    float n2Jet = sampleNeventsMap["DY2JetsToLL_M-50"];
    float xsec2Jet = sampleXSecMap["DY2JetsToLL_M-50"];

    float n3Jet = sampleNeventsMap["DY3JetsToLL_M-50"];
    float xsec3Jet = sampleXSecMap["DY3JetsToLL_M-50"];

    float n4Jet = sampleNeventsMap["DY4JetsToLL_M-50"];
    float xsec4Jet = sampleXSecMap["DY4JetsToLL_M-50"];

    sampleNormMap["DYJetsToLL_M-50"] = lumi*xsecIncl/nIncl;
    sampleNormMap["DYJetsToLL_M-50_0"] = lumi*xsecIncl/nIncl;
    sampleNormMap["DYJetsToLL_M-50_1"] = lumi/(nIncl/xsecIncl+n1Jet/xsec1Jet);
    sampleNormMap["DYJetsToLL_M-50_2"] = lumi/(nIncl/xsecIncl+n2Jet/xsec2Jet);
    sampleNormMap["DYJetsToLL_M-50_3"] = lumi/(nIncl/xsecIncl+n3Jet/xsec3Jet);
    sampleNormMap["DYJetsToLL_M-50_4"] = lumi/(nIncl/xsecIncl+n4Jet/xsec4Jet);

    sampleNormMap["DY1JetsToLL_M-50"] = lumi/(nIncl/xsecIncl+n1Jet/xsec1Jet);
    sampleNormMap["DY2JetsToLL_M-50"] = lumi/(nIncl/xsecIncl+n2Jet/xsec2Jet);
    sampleNormMap["DY3JetsToLL_M-50"] = lumi/(nIncl/xsecIncl+n3Jet/xsec3Jet);
    sampleNormMap["DY4JetsToLL_M-50"] = lumi/(nIncl/xsecIncl+n4Jet/xsec4Jet);

  }
  else if (name.Contains("DYJetsToTT")) {

    //float nIncl = sampleNeventsMap["DYJetsToTT_M-50_0"];
    float nIncl = sampleNeventsMap["DYJetsToTT_M-50"];
    float xsecIncl = sampleXSecMap["DYJetsToLL_M-50"];

    float n1Jet = sampleNeventsMap["DY1JetsToTT_M-50"];
    float xsec1Jet = sampleXSecMap["DY1JetsToLL_M-50"];

    float n2Jet = sampleNeventsMap["DY2JetsToTT_M-50"];
    float xsec2Jet = sampleXSecMap["DY2JetsToLL_M-50"];

    float n3Jet = sampleNeventsMap["DY3JetsToTT_M-50"];
    float xsec3Jet = sampleXSecMap["DY3JetsToLL_M-50"];

    float n4Jet = sampleNeventsMap["DY4JetsToTT_M-50"];
    float xsec4Jet = sampleXSecMap["DY4JetsToLL_M-50"];

    std::cout << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "nIncl = " << nIncl << "   xsecIncl = " << xsecIncl << std::endl;
    std::cout << "n1Jet = " << n1Jet << "   xsec1Jet = " << xsec1Jet << std::endl;
    std::cout << "n2Jet = " << n2Jet << "   xsec2Jet = " << xsec2Jet << std::endl;
    std::cout << "n3Jet = " << n3Jet << "   xsec3Jet = " << xsec3Jet << std::endl;
    std::cout << "n4Jet = " << n4Jet << "   xsec4Jet = " << xsec4Jet << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl; 
    std::cout << std::endl;

    sampleNormMap["DYJetsToTT_M-50"] = lumi*xsecIncl/nIncl;
    sampleNormMap["DYJetsToTT_M-50_0"] = lumi*xsecIncl/nIncl;
    sampleNormMap["DYJetsToTT_M-50_1"] = lumi/(nIncl/xsecIncl+n1Jet/xsec1Jet);
    sampleNormMap["DYJetsToTT_M-50_2"] = lumi/(nIncl/xsecIncl+n2Jet/xsec2Jet);
    sampleNormMap["DYJetsToTT_M-50_3"] = lumi/(nIncl/xsecIncl+n3Jet/xsec3Jet);
    sampleNormMap["DYJetsToTT_M-50_4"] = lumi/(nIncl/xsecIncl+n4Jet/xsec4Jet);

    sampleNormMap["DY1JetsToTT_M-50"] = lumi/(nIncl/xsecIncl+n1Jet/xsec1Jet);
    sampleNormMap["DY2JetsToTT_M-50"] = lumi/(nIncl/xsecIncl+n2Jet/xsec2Jet);
    sampleNormMap["DY3JetsToTT_M-50"] = lumi/(nIncl/xsecIncl+n3Jet/xsec3Jet);
    sampleNormMap["DY4JetsToTT_M-50"] = lumi/(nIncl/xsecIncl+n4Jet/xsec4Jet);

  }
  else if (name.Contains("WJets")) {

    //float nIncl = sampleNeventsMap["WJetsToLNu_0"];
    float nIncl = sampleNeventsMap["WJetsToLNu"];
    float xsecIncl = sampleXSecMap["WJetsToLNu"];

    float n1Jet = sampleNeventsMap["W1JetsToLNu"];
    float xsec1Jet = sampleXSecMap["W1JetsToLNu"];

    float n2Jet = sampleNeventsMap["W2JetsToLNu"];
    float xsec2Jet = sampleXSecMap["W2JetsToLNu"];

    float n3Jet = sampleNeventsMap["W3JetsToLNu"];
    float xsec3Jet = sampleXSecMap["W3JetsToLNu"];

    float n4Jet = sampleNeventsMap["W4JetsToLNu"];
    float xsec4Jet = sampleXSecMap["W4JetsToLNu"];

    std::cout << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "nIncl = " << nIncl << "   xsecIncl = " << xsecIncl << std::endl;
    std::cout << "n1Jet = " << n1Jet << "   xsec1Jet = " << xsec1Jet << std::endl;
    std::cout << "n2Jet = " << n2Jet << "   xsec2Jet = " << xsec2Jet << std::endl;
    std::cout << "n3Jet = " << n3Jet << "   xsec3Jet = " << xsec3Jet << std::endl;
    std::cout << "n4Jet = " << n4Jet << "   xsec4Jet = " << xsec4Jet << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl; 

    sampleNormMap["WJetsToLNu"] = lumi*xsecIncl/nIncl;
    sampleNormMap["WJetsToLNu_0"] = lumi*xsecIncl/nIncl;
    sampleNormMap["WJetsToLNu_1"] = lumi/(nIncl/xsecIncl+n1Jet/xsec1Jet);
    sampleNormMap["WJetsToLNu_2"] = lumi/(nIncl/xsecIncl+n2Jet/xsec2Jet);
    sampleNormMap["WJetsToLNu_3"] = lumi/(nIncl/xsecIncl+n3Jet/xsec3Jet);
    sampleNormMap["WJetsToLNu_4"] = lumi/(nIncl/xsecIncl+n4Jet/xsec4Jet);

    sampleNormMap["W1JetsToLNu"] = lumi/(nIncl/xsecIncl+n1Jet/xsec1Jet);
    sampleNormMap["W2JetsToLNu"] = lumi/(nIncl/xsecIncl+n2Jet/xsec2Jet);
    sampleNormMap["W3JetsToLNu"] = lumi/(nIncl/xsecIncl+n3Jet/xsec3Jet);
    sampleNormMap["W4JetsToLNu"] = lumi/(nIncl/xsecIncl+n4Jet/xsec4Jet);

  }

}
void Cards::InitializeSamples() {
  for (auto sample : samplesContainer) {
    cout << "Initialize " << sample << endl;
    InitializeSample(sample);
  }
}

TH1D * Cards::ProcessSample(TString name,
				  TString sysName,
				  unsigned int region,
				  bool weightSys) {

  bool is2D = variable.Contains(":");


  std::cout << std::endl;
  std::cout << "processing " << name;
  if (sysName!="") 
    std::cout << " with systematics " << sysName;
  TString suffix = "_SR";
  if(channel=="em") suffix="_OS";
  if (region==0) std::cout << "  signal region / opposite sign" << std::endl; 
  else if (region==1) { 
    std::cout << "  fake factor application region / same sign region" << std::endl; 
    suffix = "_SB";
    if(channel=="em") suffix="_SS";
  }
  else if (region==2&&channel=="tt") { 
    std::cout << "  single fake region" << std::endl;
    suffix = "_SF";
  }
  else { 
    std::cout << "  unknown region is defined : " << region << std::endl; 
    return NULL;
  }
  std::cout << std::endl;
  TString weight = regionWeight[region];
  

  TList * list = new TList;


  TString treeName = BaseTreeName;
  if (sysName=="") {
    treeName = BaseTreeName;
  }
  else {
    if (weightSys) {
      treeName = BaseTreeName;
      weight += weightSystematicsMap[sysName];
    }
    else {
      treeName = BaseTreeName + "_" + shapeSystematicsMap[sysName];
    }
  }


  TString histName = name + suffix + "_" + sysName;
  if (sysName=="") histName = name + suffix;


  vector<TString> sampleNames = nameSampleMap[name];
  for (auto sampleName : sampleNames) {
    TFile * file = sampleFileMap[sampleName];

    //    std::cout << "  weight = " << weight << "  " << treeName << std::endl;
    TTree * tree = (TTree*)file->Get(treeName);
    if (tree==NULL) {
      std::cout << "Tree named " << treeName << " does not exist for sample " << sampleName << std::endl;
      std::cout << "returning null pointer" << std::endl;

      return NULL;
    }
    std::cout << "      " << sampleName << "  :  entries in tree = " << tree->GetEntries() << std::endl;
    
    //    tree->AddFriend(treeName,friendName);
    TString cut = regionCut[region] + sampleSpecificCutMap[sampleName].at(region);
    double norm = sampleNormMap[sampleName];
    TString HistName = sampleName+suffix;
    if(sysName!="")
      HistName+="_"+sysName;


    TH1D * histSample=NULL;
    TH2D * hist2DSample=NULL; 

    std::cout << "   creating histo " << HistName << std::endl; 
    std::cout << "   creating histo " << histName << std::endl; 
    if (is2D) 
      hist2DSample = create2DHisto(HistName);
    else
      histSample = createHisto(HistName);
    TString Cuts = weight + norm+"*(" + cut + ")";
    std::cout << HistName << "       cuts = " << Cuts << std::endl;
    tree->Draw(variable+">>"+HistName,Cuts);
    //cout<< histSample->GetEntries() << "  integral " << histSample->Integral() << endl;
    if (is2D)
      list->Add((TH2D*)hist2DSample->Clone());
    else    
      list->Add((TH1D*)histSample->Clone());
    std::cout << "    ENTRIES = " << histSample->GetEntries() << std::endl;

    delete hist2DSample;
    delete histSample;
  }

  TH1D * hist= NULL;
  TH2D * hist2D= NULL;

  if(is2D){
    hist2D = (TH2D*)(list->First())->Clone(histName+"_2d");
    hist2D->Reset();
    hist2D->Merge(list);
  }else{
    hist = (TH1D*)(list->First())->Clone(histName);
    hist->Reset();
    hist->Merge(list);
  }
  list->Clear();
  delete list;

  if (is2D) {
    hist = unroll(hist2D,histName);
    delete hist2D;
  }
  //  zeroBins(hist);

  cout << "Integral " << hist->Integral() << endl;
  return hist;


}

void Cards::SetVariableToPlot(TString var, int nbins, double xmin, double xmax) {
  if (xmin>xmax) {
    std::cout << "Cards::SetVariableToPlot() -> " << std::endl; 
    std::cout << "warning ->  xmin : " << xmin << " is greater than xmax : " << xmax << std::endl;
    std::cout << "nothing will be done..." << std::endl;
    block = true;
    return;
  }

  variable = var;
  nBins = nbins;
  double binWidth = (xmax-xmin)/double(nBins);
  for (int iB=0; iB<=nBins; ++iB)
    Bins[iB] = xmin + double(iB)*binWidth;

}

void Cards::SetVariableToPlot(TString var, int nbins, double * bins) {

  bool notOrdered = false;
  for (int iB=0; iB<nbins; ++iB) {
    if (bins[iB]>bins[iB+1]) {
      std::cout << iB << " : " << bins[iB] << " vs. " << bins[iB+1] << std::endl;
      notOrdered = true;
      break;
    }
  }

  if (notOrdered) {
    std::cout << "Cards::SetVariableToPlot() -> " << std::endl; 
    std::cout << "warning -> bins are not in increasing order  : " << std::endl;
    std::cout << "nothing will be done..." << std::endl;
    block = true;
    return;
  }

  variable = var;
  nBins = nbins;
  for (int iB=0; iB<=nBins; ++iB)
    Bins[iB] = bins[iB];

}

void Cards::SetVariableToPlot(TString var, int nbins, vector<double> bins) {

  bool notOrdered = false;
  for (int iB=0; iB<nbins; ++iB) {
    if (bins[iB]>bins[iB+1]) {
      notOrdered = true;
      break;
    }
  }

  if (notOrdered) {
    std::cout << "Cards::SetVariableToPlot() -> " << std::endl; 
    std::cout << "warning -> bins are not in increasing order  : " << std::endl;
    std::cout << "nothing will be done..." << std::endl;
    block = true;
    return;
  }

  variable = var;
  nBins = nbins;
  for (int iB=0; iB<=nBins; ++iB)
    Bins[iB] = bins[iB];

}

void Cards::SetVariableToPlot(TString var, vector<double> bins, vector<double> bins2) {

  bool notOrdered = false;
  int nbins = bins.size()-1;
  for (int iB=0; iB<nbins; ++iB) {
    if (bins[iB]>bins[iB+1]) {
      notOrdered = true;
      break;
    }
  }

  if (notOrdered) {
    std::cout << "Cards::SetVariableToPlot() -> " << std::endl; 
    std::cout << "warning -> bins are not in increasing order  : " << std::endl;
    std::cout << "nothing will be done..." << std::endl;
    block = true;
    return;
  }

  notOrdered = false;
  int nbins2 = bins2.size()-1;
  for (int iB=0; iB<nbins2; ++iB) {
    if (bins2[iB]>bins2[iB+1]) {
      notOrdered = true;
      break;
    }
  }

  if (notOrdered) {
    std::cout << "Cards::SetVariableToPlot() -> " << std::endl; 
    std::cout << "warning -> bins are not in increasing order for the second variable : " << std::endl;
    std::cout << "nothing will be done..." << std::endl;
    block = true;
    return;
  }

  variable = var;
  nBins = nbins;
  nBins2 = nbins2;
  for (int iB=0; iB<=nBins; ++iB)
    Bins[iB] = bins[iB];
  for (int iB=0; iB<=nBins2; ++iB)
    Bins2[iB] = bins2[iB];

}

TH1D * Cards::createHisto(TString histName) {
  TH1D * hist = new TH1D(histName,"",nBins,Bins);
  return hist;
}

TH2D * Cards::create2DHisto(TString histName) {
  TH2D * hist = new TH2D(histName,"",nBins,Bins,nBins2,Bins2);
  return hist;
}

TH1D * Cards::unroll(TH2D * hist2D, TString histName) {
  int nBinsX = hist2D->GetNbinsX();
  int nBinsY = hist2D->GetNbinsY();
  int nBins1D = nBinsX*nBinsY;
  TH1D * hist = new TH1D(histName,"",nBins1D,0.,double(nBins1D));
  for (int iy=1; iy<=nBinsY; ++iy) {
    for (int ix=1; ix<=nBinsX; ++ix) {
      int binId = ix + (iy-1)*nBinsX;
      double xBin = hist2D->GetBinContent(ix,iy);
      double eBin = hist2D->GetBinError(ix,iy);
      hist->SetBinContent(binId,xBin);
      hist->SetBinError(binId,eBin);
    }
  }
  return hist;

}

int Cards::CreateShapeSystematicsMap() {

  int numberOfShapeSystematics = 0;

  if (sampleToProcess=="Data")
    return numberOfShapeSystematics;

  if (sampleToProcess=="EMB") {
    for (auto mapIter : EmbeddedShapeSystematics) {
      TString sysName = mapIter.first;
      TString treeName = mapIter.second;
      shapeSystematicsMap[sysName+"_"+era+"Up"] = treeName+"Up";
      shapeSystematicsMap[sysName+"_"+era+"Down"] = treeName+"Down";
      numberOfShapeSystematics += 2;
    }
    /*
    for (auto mapIter : EmbeddedMetShapeSystematics) {
      TString sysName = mapIter.first;
      TString treeName = mapIter.second;
      shapeSystematicsMap[sysName] = treeName;
      numberOfShapeSystematics += 1;
    }
    */
    return numberOfShapeSystematics;
  }
  
  std::map<TString, TString> yearSysMap = ShapeSystematics_2016;
  if (era=="2016")
    yearSysMap = ShapeSystematics_2016;
  if (era=="2017")
    yearSysMap = ShapeSystematics_2017;
  if (era=="2018")
    yearSysMap = ShapeSystematics_2018;
  
  for (auto mapIter : yearSysMap) {
    TString sysName = mapIter.first;
    TString treeName = mapIter.second;
    shapeSystematicsMap[sysName+"Up"] = treeName+"Up";
    shapeSystematicsMap[sysName+"Down"] = treeName+"Down";
    numberOfShapeSystematics += 2;
  }

  for (auto mapIter : ShapeSystematics_Common) {
    TString sysName = mapIter.first;
    TString treeName = mapIter.second;
    shapeSystematicsMap[sysName+"Up"] = treeName+"Up";
    shapeSystematicsMap[sysName+"Down"] = treeName+"Down";
    numberOfShapeSystematics += 2;
  }

  return numberOfShapeSystematics;

}

int Cards::CreateWeightSystematicsMap() {
   
  int numberOfWeightSystematics = 0; 
  if (sampleToProcess=="EMB") {
    for (auto mapIter : EmbeddedWeightSystematics) {
      TString sysName = mapIter.first;
      TString weightName = mapIter.second;
      weightSystematicsMap[sysName+"_"+era+"Up"] = weightName + "Up*";
      weightSystematicsMap[sysName+"_"+era+"Down"] = weightName + "Down*";
      numberOfWeightSystematics += 2;
    }
    return numberOfWeightSystematics;
  }

  // Data ---->
  if (sampleToProcess=="Data") {
        
    std::vector<TString> jetBins = {"0","1","2"};
    std::vector<TString> dmBins = {"0","1","10"};
    std::vector<TString> uncs = {"1","2"};
    for (auto jetBin : jetBins) {
      for (auto dmBin : dmBins) {
	for (auto unc : uncs) {
	  TString weightName = "ff_qcd_stat_unc"+unc+"_njet"+jetBin+"_dm"+dmBin;
	  TString weightNameUp = weightName + "*";
	  TString weightNameDown = "(1/"+weightName+")*";
	  TString sysName = "CMS_ff_total_qcd_stat_unc"+unc+"_njets"+jetBin+"_dm"+dmBin+"_tt_"+era;
	  TString sysNameUp = sysName + "Up";
	  TString sysNameDown = sysName + "Down";
	  weightSystematicsMap[sysNameUp] = weightNameUp;
	  weightSystematicsMap[sysNameDown] = weightNameDown;
	  numberOfWeightSystematics += 2;
	}
      }
    }

    for (auto mapIter : FakeFactorSystematics) {
      TString sysName = mapIter.first + "_" + era;
      TString weightName = mapIter.second;
      TString weightNameUp = weightName + "*";
      TString weightNameDown = "(1/"+weightName+")*";
      TString sysNameUp = sysName + "Up";
      TString sysNameDown = sysName + "Down";
      weightSystematicsMap[sysNameUp] = weightNameUp;
      weightSystematicsMap[sysNameDown] = weightNameDown;    
      numberOfWeightSystematics += 2;
    }

    return numberOfWeightSystematics;

  }
  
  // Prefiring weight;
  for (auto mapIter : PrefiringSystematics) {
    TString sysName = mapIter.first;
    TString weightName = mapIter.second;
    weightSystematicsMap[sysName] = weightName+"*";      
    numberOfWeightSystematics++;
  }

  // tau id and trigger and l->tau fakes
  for (auto mapIter : WeightSystematics) {
    TString sysName = mapIter.first;
    TString weightName = mapIter.second;
    weightSystematicsMap[sysName+"_"+era+"Up"] = weightName + "Up*";
    weightSystematicsMap[sysName+"_"+era+"Down"] = weightName + "Down*";
    numberOfWeightSystematics += 2;
  }

  if (sampleToProcess=="ggH") {
    for (auto mapIter : SignalSystematics) {
      TString sysName = mapIter.first;
      TString weightName = mapIter.second;
      weightSystematicsMap[sysName+"Up"] = weightName + "Up*";
      weightSystematicsMap[sysName+"Down"] = weightName + "Down*";
      numberOfWeightSystematics += 2;
    }
    return numberOfWeightSystematics;
  }

  // MC ---->
  if (sampleToProcess=="EWK"||sampleToProcess=="EWKToTT"||sampleToProcess=="WJets")
    return numberOfWeightSystematics;
  
  // TTbar ---->
  if (sampleToProcess=="TTbar"||sampleToProcess=="TTbarToTT") {
    for (auto mapIter : TopShapeSystematics) {
      TString sysName = mapIter.first;
      TString weightName = mapIter.second;
      weightSystematicsMap[sysName] = weightName+"*";
      numberOfWeightSystematics++;
    }      
    return numberOfWeightSystematics;
  }

  // DYJets ---->
  if (sampleToProcess=="DYJets") {
    map<TString,TString> DYSys = DYShapeSystematics;
    if (era=="2016") DYSys = DYShapeSystematics_2016;
    for (auto mapIter : DYSys) {
      TString sysName = mapIter.first;
      TString weightName = mapIter.second;
      weightSystematicsMap[sysName] = weightName+"*";
      numberOfWeightSystematics++;
    }
    return numberOfWeightSystematics;
  }

  return numberOfWeightSystematics;

}

bool Cards::RunData() {

  bool status = true;

  TH1D * histData = ProcessSample("Data","",0,false);
  nameTH1DMap["data_obs"] = histData;
  
  TH1D * QCD = ProcessSample("Data","",1,false);
  TH1D * QCD_Up = (TH1D*)QCD->Clone("QCDsubtrUp");
  TH1D * QCD_Down = (TH1D*)QCD->Clone("QCDsubtrDown");
  for (auto name : samplesContainer) {
    cout << ">>> processing sample " << name << endl;
    TH1D * hist = ProcessSample(name,"",1,false);
    QCD->Add(QCD,hist,1.,-1.);
    QCD_Up->Add(QCD_Up,hist,1.,-0.9);
    QCD_Down->Add(QCD_Down,hist,1.,-1.1);
    delete hist;
  }
  
  if(channel=="em"){
    nameTH1DMap["QCD"] = QCD;
    nameTH1DMap["QCD_CMS_total_subtr_syst_tt_"+era+"Up"] = QCD_Up;
    nameTH1DMap["QCD_CMS_total_subtr_syst_tt_"+era+"Down"] = QCD_Down;
  }else{
    nameTH1DMap["jetFakes"] = QCD;
    nameTH1DMap["jetFakes_CMS_ff_total_subtr_syst_tt_"+era+"Up"] = QCD_Up;
    nameTH1DMap["jetFakes_CMS_ff_total_subtr_syst_tt_"+era+"Down"] = QCD_Down;
  }

  bool first = true;
  TH1D * histSingleFake;
  if(channel=="tt"){
    cout<<"Side band region for tt channel"<<endl;
    for (auto name : samplesContainer) {
      TH1D * hist = ProcessSample(name,"",2,false);
      if (first) {
	histSingleFake = hist;
	first = false;
      }
      else {
	histSingleFake->Add(histSingleFake,hist,1.,1.);
	delete hist;
      }
    }
    nameTH1DMap["wFakes"] = histSingleFake;
  }

  if (!runWithSystematics) { 
    status = false;
    return status;
  }

  for (auto weightSys : weightSystematicsMap) {
    TString sysName = weightSys.first;
    TH1D * QCD_sys = ProcessSample("Data",sysName,1,true);
    for (auto name : samplesContainer) {
      TH1D * hist = ProcessSample(name,sysName,1,true);
      QCD_sys->Add(QCD_sys,hist,1.,-1.);
      delete hist;
    }
    if(channel=="em")
      nameTH1DMap["QCD_"+sysName] = QCD_sys;
    else nameTH1DMap["jetFakes_"+sysName] = QCD_sys;
  }

  return status;

}

bool Cards::RunModel() {

  bool status = true;
  
  // central templates ---->
  for (auto name : samplesContainer) {
    TH1D * hist = ProcessSample(name,"",0,false);
    TString sampleHistName = nameHistoMap[name];
    nameTH1DMap[sampleHistName] = hist;
    std::cout << "hist : " << sampleHistName << "   entries = " << hist->GetEntries() << "   sumOfW = " << hist->GetSumOfWeights() << std::endl;
  }

  if (!runWithSystematics) {
    status = false;
    return status;
  }

  // ttbar contamination --->
  if (sampleToProcess=="EMB") {
    TH1D * hist = ProcessSample("TTbarToTT","",0,false);
    TH1D * emb = nameTH1DMap["EMB"];
    TString nameUp = sampleToProcess + "_CMS_htt_emb_ttbar_"+era+"Up";
    TString nameDown = sampleToProcess + "_CMS_htt_emb_ttbar_"+era+"Down";
    TH1D * histDown = (TH1D*)emb->Clone(nameDown);
    TH1D * histUp = (TH1D*)emb->Clone(nameUp);
    histDown->Add(histDown,hist,1.,-0.1);
    histUp->Add(histUp,hist,1.,0.1);
    nameTH1DMap[nameUp] = histUp;
    nameTH1DMap[nameDown] = histDown;
    std::cout << "EMB_CMS_htt_emb_ttbar   lnN " << histDown->GetSum()/emb->GetSum() << "/" << histUp->GetSum()/emb->GetSum() << std::endl;
    std::cout << std::endl;
  }

  // systematics ----->
  for (auto name : samplesContainer) {
    for (auto weightSys : weightSystematicsMap) {
      TString sysName = weightSys.first;
      TString sampleHistName = nameHistoMap[name] + "_" + sysName;
      TH1D * hist = ProcessSample(name,sysName,0,true);
      nameTH1DMap[sampleHistName] = hist;
    }
    if (runWithShapeSystematics) {
      for (auto shapeSys : shapeSystematicsMap) {
	TString sysName = shapeSys.first;
	TH1D * hist = ProcessSample(name,sysName,0,false);
	TString sampleHistName = nameHistoMap[name] + "_" + sysName;
	// Systematics may not exist, be careful
	if (hist!=NULL) { 
	  nameTH1DMap[sampleHistName] = hist;
	}
      }
    }
  }
  
  return status;

}

void Cards::PrintWeightSystematics() {
  if (block) return;

  std::cout << std::endl;
  std::cout << "Cards::PrintWeightSysMap() " << std::endl;
  std::cout << "Number of weight systematics : " << numberOfWeightSystematics << std::endl;
  for (auto weightSys : weightSystematicsMap) {
    TString sysName = weightSys.first;
    TString treeName = weightSys.second;
    std::cout << sysName << " : " << treeName << std::endl;
  }
  std::cout << std::endl;

}

void Cards::PrintShapeSystematics() {
  if (block) return;

  std::cout << std::endl;
  std::cout << "Cards::PrintShapeSysMap() " << std::endl;
  std::cout << "Number of shape systematics : " << numberOfShapeSystematics << std::endl;
  for (auto shapeSys : shapeSystematicsMap) {
    TString sysName = shapeSys.first;
    TString treeName = shapeSys.second;
    std::cout << sysName << " : " << treeName << std::endl;
  }
  std::cout << std::endl;

}

void Cards::PrintSamples() {
  if (block) return;

  std::cout << std::endl;
  std::cout << "Cards::PrintNameSampleMap() " << std::endl;
  std::cout << "printing sampleName : sampleNorm : sampleSpecificCut" << std::endl;

  if (sampleToProcess=="Data") {
    vector<TString> sampleNames = nameSampleMap["Data"];
    std::cout << "Data -> " << nameHistoMap["Data"] << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << std::endl;
    for (auto sampleName : sampleNames) {
      std::cout << "    " << sampleName << " : norm = " << sampleNormMap[sampleName] << std::endl;
      std::cout << "      cut(SR/OS) : " << sampleSpecificCutMap[sampleName].at(0) << std::endl;
      std::cout << "      cut(SB/SS) : " << sampleSpecificCutMap[sampleName].at(1) << std::endl;
      if(channel=="tt")std::cout << "      cut(SF) : " << sampleSpecificCutMap[sampleName].at(2) << std::endl;
      
    }
  }

  for (auto name : samplesContainer) {
    std::cout << name << " -> " << nameHistoMap[name] << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << std::endl;
    vector<TString> sampleNames = nameSampleMap[name];
    for (auto sampleName : sampleNames) {
      std::cout << "    " << sampleName << " : norm = " << sampleNormMap[sampleName] << std::endl;
      std::cout << "      cut(SR/OS) : " << sampleSpecificCutMap[sampleName].at(0) << std::endl;
      std::cout << "      cut(SB/SS) : " << sampleSpecificCutMap[sampleName].at(1) << std::endl;
      if(channel=="tt")std::cout << "      cut(SF) : " << sampleSpecificCutMap[sampleName].at(2) << std::endl;
      
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Variable to be plotted : " << variable << std::endl;
  std::cout << std::endl;
  std::cout << "Cuts to be applied for category " << category << std::endl;
  std::cout << "  -> " << commonCuts << std::endl;
  std::cout << std::endl;
  std::cout << "Global weight = " << globalWeight << std::endl;
  std::cout << std::endl;
  std::cout << "Region cuts : " << std::endl;
  std::cout << "       SR/OS = " << regionCut[0] << std::endl;
  std::cout << "       SB/SS = " << regionCut[1] << std::endl;
  if(channel=="tt")std::cout << "       SF = " << regionCut[2] << std::endl;
  std::cout << std::endl;
  std::cout << "Region weights : " << std::endl;
  std::cout << "       SR/OS = " << regionWeight[0] << std::endl;
  std::cout << "       SB/SS = " << regionWeight[1] << std::endl;
  if(channel=="tt")std::cout << "       SF = " << regionWeight[2] << std::endl;
  std::cout << std::endl;

}

bool Cards::Run() {
  if (block) return false;

  bool status = true;

  if (sampleToProcess=="Data")
    status = RunData();
  else 
    status = RunModel();

  // save histograms ---->
  outputFile->cd(category);
  for (auto histogram : nameTH1DMap) {
    TString histoName = histogram.first;
    TH1D * histo = histogram.second;
    histo->Write(histoName);
  }
  return status;
};

bool Cards::CloseFile() {

  bool result = false;
  if (block) return result;

  if (outputFile!=NULL) {
    outputFile->Close();
    delete outputFile;
    result = true;
  }
  return result;

}
void Cards::zeroBins(TH1D * hist) {

  int nbins = hist->GetNbinsX();
  for (int iB=1; iB<=nbins; ++iB) {
    double x = hist->GetBinContent(iB);
    if (x<0.0) {
      hist->SetBinContent(iB,0.);
      hist->SetBinError(iB,0.);
    }
  }

}

Cards::~Cards() {

}

#endif
