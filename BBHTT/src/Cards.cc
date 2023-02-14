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
  input_dir = InputDir + "/" + era;
  input_friend_dir = PredDir + "/" + era;
  runWithShapeSystematics = true;
  output_filename = OutputDir+"/"+era+"/"+Sample+"_"+Category+".root";
  sampleToProcess = Sample;
  category = channel+"_"+Category;
  variable = Variable;
  runWithSystematics = RunWithSystematics;
  runOnEmbedded = RunOnEmbedded;

  _usefriend=true;
  if(PredDir==""||PredDir=="None"||PredDir=="NONE"||PredDir=="none") _usefriend=false;

  if(channel=="em"){
    commonCuts=baselineEM;
    mcNotTauTau=mcNotTauTau_EM;
    mcTauTau=mcTauTau_EM;
  }else{
    commonCuts=baselineTT;
    mcNotTauTau=mcNotTauTau_TT;
    mcTauTau=mcTauTau_TT;
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

  bool sampleExist = false;
  for (auto availSample : availableSamplesToProcess) {
    if (sampleToProcess==availSample) {
      sampleExist = true;
      break;
    }
  }
  if (!sampleExist) {
    std::cout << "Unknown sample specified : " << sampleToProcess << std::endl;
    std::cout << "Available samples -> " << std::endl;
    for (auto availSample : availableSamplesToProcess) {
      std::cout << availSample << " -> " << mapAvailableSamples[availSample] << std::endl;
    }
    std::cout << "Nothing will be done" << std::endl;
    block = true;
    return;
  }  

  bool catExist = false;
  for (auto availCat : availableCategories) {
    if (Category == availCat) {
      catExist = true;
      break;
    }
  }
  if (!catExist) {
    std::cout << "Unknown category specified : " << Category << std::endl;
    std::cout << "Available categories -> " << std::endl;
    for (auto availCat : availableCategories ) {
      std::cout << availCat << std::endl;
    }
    std::cout << "nothing will be done" << std::endl;
    block = true;
    return;
  }

  std::map<TString,TString> categoryCuts = {
    {channel+"_inclusive",""},
    {channel+"_Nbtag0",   "&&nbtag==0"},
    {channel+"_NbtagGe1",   "&&nbtag>0"},

    {channel+"_Nbtag0_lowPzeta", "&&nbtag==0&&pzeta<-35"},
    {channel+"_NbtagGe1_lowPzeta", "&&nbtag>0&&pzeta<-35"},

    {channel+"_Nbtag0_highPzeta", "&&nbtag==0&&pzeta>-35"},
    {channel+"_NbtagGe1_highPzeta", "&&nbtag>0&&pzeta>-35"},

    {channel+"_Nbtag0_Pzeta1", "&&nbtag==0&&pzeta>-35&&pzeta<-10"},
    {channel+"_NbtagGe1_Pzeta1", "&&nbtag>0&&pzeta>-35&&pzeta<-10"},

    {channel+"_Nbtag0_Pzeta2", "&&nbtag==0&&pzeta>-10&&pzeta<20"},
    {channel+"_NbtagGe1_Pzeta2", "&&nbtag>0&&pzeta>-10&&pzeta<20"},

    {channel+"_cat0", "&&pred_class==0"},
    {channel+"_cat1", "&&pred_class==1"},
    {channel+"_cat2", "&&pred_class==2"},
    {channel+"_cat3", "&&pred_class==3"},
    {channel+"_cat4", "&&pred_class==4"},

    {channel+"_cat0_Nbtag0", "&&pred_class==0&&nbtag==0"},
    {channel+"_cat1_Nbtag0", "&&pred_class==1&&nbtag==0"},
    {channel+"_cat2_Nbtag0", "&&pred_class==2&&nbtag==0"},
    {channel+"_cat3_Nbtag0", "&&pred_class==3&&nbtag==0"},
    {channel+"_cat4_Nbtag0", "&&pred_class==4&&nbtag==0"},

    {channel+"_cat0_Nbtag1", "&&pred_class==0&&nbtag==1"},
    {channel+"_cat1_Nbtag1", "&&pred_class==1&&nbtag==1"},
    {channel+"_cat2_Nbtag1", "&&pred_class==2&&nbtag==1"},
    {channel+"_cat3_Nbtag1", "&&pred_class==3&&nbtag==1"},
    {channel+"_cat4_Nbtag1", "&&pred_class==4&&nbtag==1"},

    {channel+"_cat0_Nbtag2", "&&pred_class==0&&nbtag==2"},
    {channel+"_cat1_Nbtag2", "&&pred_class==1&&nbtag==2"},
    {channel+"_cat2_Nbtag2", "&&pred_class==2&&nbtag==2"},
    {channel+"_cat3_Nbtag2", "&&pred_class==3&&nbtag==2"},
    {channel+"_cat4_Nbtag2", "&&pred_class==4&&nbtag==2"},

    {channel+"_cat0_NbtagGe1", "&&pred_class==0&&nbtag>0"},
    {channel+"_cat1_NbtagGe1", "&&pred_class==1&&nbtag>0"},
    {channel+"_cat2_NbtagGe1", "&&pred_class==2&&nbtag>0"},
    {channel+"_cat3_NbtagGe1", "&&pred_class==3&&nbtag>0"},
    {channel+"_cat4_NbtagGe1", "&&pred_class==4&&nbtag>0"},
  };    

  TH1::SetDefaultSumw2(true);
  TH2::SetDefaultSumw2(true);

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

  if (channel=="em") {
    commonCuts += "&&pzeta<20.0&&nbtag<3";
    if (category=="em_cat3_NbtagGe1")
      commonCuts += "&&puppimet>20.&&mt_tot>40.0";
  }

  regionCut.clear();
  if(channel=="tt"){
    regionCut.push_back(commonCuts+signalRegion); // SR
    regionCut.push_back(commonCuts+fakesSideBand); // Fake AR
    regionCut.push_back(commonCuts+signalRegion); // Single Fake region
  }else{
    regionCut.push_back(commonCuts+oppositeSignRegion); // opposite sign
    regionCut.push_back(commonCuts+sameSignRegion); // same sign
  }

  regionWeight.clear();
  regionWeight.push_back(globalWeight);

  TString QCDFFWeight = "";
  if(channel=="em")
    QCDFFWeight=qcdWeight;  
  else
    QCDFFWeight = FFWeight;
 
  map<TString, TString> btag_scale = 
    {
      {"2016_post","0.67*"},
      {"2016_pre","0.67*"},
      {"2016","0.67*"},
      {"2017","0.69*"},
      {"2018","0.71*"}
    };
  
  
  if (channel=="em"&&isBTag) {
    QCDFFWeight += btag_scale[era];
  }

  regionWeight.push_back(globalWeight+QCDFFWeight);
  if(channel=="tt") regionWeight.push_back(globalWeight);

  if (channel=="tt") {
    nameSampleMap["Data"] = Tau; nameHistoMap["Data"] = "data_obs";
  }
  else {
    nameSampleMap["Data"] = MuonEG; nameHistoMap["Data"] = "data_obs";
  }
  nameSampleMap["DY"] = DYJets; nameHistoMap["DY"] = "DYJets";
  nameSampleMap["DYToLL"] = DYJets; nameHistoMap["DYToLL"] = "ZL"; 
  nameSampleMap["DYToTT"] = DYJets; nameHistoMap["DYToTT"] = "ZTT";
  nameSampleMap["W"] = WJets; nameHistoMap["W"] = "W";
  nameSampleMap["TT"] = TTbar; nameHistoMap["TT"] = "TT";
  nameSampleMap["TTToL"] = TTbar; nameHistoMap["TTToL"] = "TTL";
  nameSampleMap["TTToTT"] = TTbar; nameHistoMap["TTToTT"] = "TTT";
  nameSampleMap["VV"] = VV; nameHistoMap["VV"] = "VV";
  nameSampleMap["VVToL"] = VV; nameHistoMap["VVToL"] = "VVL"; 
  nameSampleMap["VVToTT"] = VV; nameHistoMap["VVToTT"] = "VVT";
  nameSampleMap["ST"] = ST; nameHistoMap["ST"] = "ST";
  nameSampleMap["STToL"] = ST; nameHistoMap["STToL"] = "STL"; 
  nameSampleMap["STToTT"] = ST; nameHistoMap["STToTT"] = "STT";
  nameSampleMap["TTVJets"] = TTVJets; nameHistoMap["TTVJets"] = "TTVJets";

  nameSampleMap["ggHWW"] = ggHWW; nameHistoMap["ggHWW"] = "ggH_hww";
  nameSampleMap["qqHWW"] = qqHWW; nameHistoMap["qqHWW"] = "qqHWW125";
  nameSampleMap["WHWW"] = WHWW; nameHistoMap["WHWW"] = "WHWW125";
  nameSampleMap["ZHWW"] = ZHWW; nameHistoMap["ZHWW"] = "ZHWW125";
  nameSampleMap["TTHWW"] = TTHWW; nameHistoMap["TTHWW"] = "TTHWW125";

  nameSampleMap["ggHTT"] = ggH; nameHistoMap["ggHTT"] = "ggH_htt";
  nameSampleMap["qqHTT"] = qqH; nameHistoMap["qqHTT"] = "qqH125";
  nameSampleMap["WHTT"] = WH; nameHistoMap["WHTT"] = "WH125";
  nameSampleMap["ZHTT"] = ZH; nameHistoMap["ZHTT"] = "ZH125";
  nameSampleMap["TTHTT"] = TTH; nameHistoMap["TTHTT"] = "TTH125";

  nameSampleMap["bbHTTybyt"] = bbH_ybyt; nameHistoMap["bbHTTybyt"] = "intH_bb_htt";
  nameSampleMap["bbHTTyt2"] = bbH_yt2; nameHistoMap["bbHTTyt2"] = "ggH_bb_htt";
  nameSampleMap["bbHTTyb2"] = bbH_yb2; nameHistoMap["bbHTTyb2"] = "bbH_htt";
  nameSampleMap["bbHTTybyt_nobb"] = bbH_ybyt; nameHistoMap["bbHTTybyt_nobb"] = "intH_htt";
  nameSampleMap["bbHTTyb2_nobb"] = bbH_yb2; nameHistoMap["bbHTTyb2_nobb"] = "bbH_nobb_htt";

  nameSampleMap["bbHWWybyt"] = bbHWW_ybyt; nameHistoMap["bbHWWybyt"] = "intH_bb_hww";
  nameSampleMap["bbHWWyt2"] = bbHWW_yt2; nameHistoMap["bbHWWyt2"] = "ggH_bb_hww";
  nameSampleMap["bbHWWyb2"] = bbHWW_yb2; nameHistoMap["bbHWWyb2"] = "bbH_hww";
  nameSampleMap["bbHWWybyt_nobb"] = bbHWW_ybyt; nameHistoMap["bbHWWybyt_nobb"] = "intH_hww";
  nameSampleMap["bbHWWyb2_nobb"] = bbHWW_yb2; nameHistoMap["bbHWWyb2_nobb"] = "bbH_nobb_hww";

  samplesContainer.clear();
  if (sampleToProcess=="Data") {
    InitializeSample("Data");
    samplesContainer.push_back("W");
    samplesContainer.push_back("VV");
    samplesContainer.push_back("ST");
    samplesContainer.push_back("TT");
    samplesContainer.push_back("DY");
  }
  else if (sampleToProcess=="DYToTT") {
    samplesContainer.push_back("DYToTT");
  }
  else if (sampleToProcess=="DYToLL") {
    samplesContainer.push_back("DYToLL");
  }
  else if (sampleToProcess=="EWK") {
    samplesContainer.push_back("W");
    samplesContainer.push_back("VV");
  }
  else if (sampleToProcess=="ST") {
    samplesContainer.push_back("ST");
  }
  else if (sampleToProcess=="TT") {
    samplesContainer.push_back("TT");
  }
  else if (sampleToProcess=="TTVJets") {
    samplesContainer.push_back("TTVJets");
  }
  else if (sampleToProcess=="HTT") {
    samplesContainer.push_back("ggHTT");
    samplesContainer.push_back("qqHTT");
    samplesContainer.push_back("WHTT");
    samplesContainer.push_back("ZHTT");
    samplesContainer.push_back("TTHTT");
  }
  else if (sampleToProcess=="HWW") {
    samplesContainer.push_back("ggHWW");
    samplesContainer.push_back("qqHWW");
    samplesContainer.push_back("WHWW");
    samplesContainer.push_back("ZHWW");
    samplesContainer.push_back("TTHWW");
  }
  else if (sampleToProcess=="bbHTT_nobb") {
    samplesContainer.push_back("bbHTTybyt_nobb");
    samplesContainer.push_back("bbHTTyb2_nobb");
  }
  else if (sampleToProcess=="bbHTT") {
    samplesContainer.push_back("bbHTTybyt");
    samplesContainer.push_back("bbHTTyb2");
    samplesContainer.push_back("bbHTTyt2");
  }
  else if (sampleToProcess=="bbHWW") {
    samplesContainer.push_back("bbHWWybyt");
    samplesContainer.push_back("bbHWWyb2");
    samplesContainer.push_back("bbHWWyt2");
  }
  else if (sampleToProcess=="bbHWW_nobb") {
    samplesContainer.push_back("bbHWWybyt_nobb");
    samplesContainer.push_back("bbHWWyb2_nobb");    
  }
  else {
    std::cout << "Unknown sample specified : " << sampleToProcess << std::endl;
    std::cout << "Available samples -> " << std::endl;
    for (auto availSample : availableSamplesToProcess) {
      std::cout << availSample << " -> " << mapAvailableSamples[availSample] << std::endl;
    }
    std::cout << "Nothing will be done" << std::endl;
    block = true;
    return;
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
  
  if (name=="ggHTT"||name=="ggHWW") {
    ngenPartonsCut = "&&gen_nbjets_cut==0";
  }
  
  if (name=="bbHTTybyt_nobb"||name=="bbHTTyb2_nobb") {
    ngenPartonsCut = "&&gen_nbjets_cut==0";
  }

  if (name=="bbHTTybyt"||name=="bbHTTyt2"||name=="bbHTTyb2") {
    ngenPartonsCut = "&&gen_nbjets_cut>0";
  }

  if (name=="bbHWWybyt_nobb"||name=="bbHWWyb2_nobb") {
    ngenPartonsCut = "&&gen_nbjets_cut==0";
  }

  if (name=="bbHWWybyt"||name=="bbHWWyt2"||name=="bbHWWyb2") {
    ngenPartonsCut = "&&gen_nbjets_cut>0";
  }
  
  if (name=="EMB") {
    mcSR = mcTauTau;
    mcSB = mcSideBand;
    mcSF = mcSingleFake;
  }

  if ((name=="TT"||name=="VV"||name=="W"||name=="ST"||name=="DY")) {
    mcSR = mcNotFakes;
    mcSB = mcSideBand;
    mcSF = mcSingleFake;
  }
  if (name=="TTToTT"||name=="VVToTT"||name=="STToTT"||name=="DYToTT") {
    mcSR = mcTauTau;
    mcSB = mcSideBand;
    mcSF = mcSingleFake;
  }
  if (name=="DYToLL"||name=="VVToL"||name=="STToL"||name=="TTToL") {
    mcSR = mcNotTauTau + mcNotFakes;
    mcSB = mcSideBand + mcNotTauTau;
    mcSF = mcSingleFake + mcNotTauTau;
  }


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

  if (name=="ggHTT"||name=="ggHWW") {
    ngenPartonsCut = "&&gen_nbjets_cut==0&&weightEMu<30.";
  }
  
  if (name=="bbHTTybyt_nobb"||name=="bbHTTyb2_nobb") {
    ngenPartonsCut = "&&gen_nbjets_cut==0";
  }

  if (name=="bbHTTybyt"||name=="bbHTTyt2"||name=="bbHTTyb2") {
    ngenPartonsCut = "&&gen_nbjets_cut>0";
  }

  if (name=="bbHWWybyt_nobb"||name=="bbHWWyb2_nobb") {
    ngenPartonsCut = "&&gen_nbjets_cut==0&&weightEMu<30.";
  }

  if (name=="bbHWWybyt"||name=="bbHWWyt2"||name=="bbHWWyb2") {
    ngenPartonsCut = "&&gen_nbjets_cut>0&&weightEMu<30.";
  }

  if (name=="TTToL"||name=="VVToL"||name=="STToLL"||name=="DYToLL") {
    mcOS = mcNotTauTau;
    mcSS = mcNotTauTau;
  }
  if (name=="TTToTT"||name=="VVToTT"||name=="STToTT"||name=="DYToTT") {
    mcOS = mcTauTau;
    mcSS = mcTauTau;
  }

  std::vector<TString> Cuts; Cuts.clear();
  Cuts.push_back(mcOS+ngenPartonsCut);
  Cuts.push_back(mcSS+ngenPartonsCut);

  return Cuts;

}

void Cards::InitializeSample(TString name) {

  //  std::cout << "Name = " << name << std::endl;

  std::vector<TString> sampleNames = nameSampleMap[name];
  for (auto sampleName : sampleNames) {
    TString baseFileName = channel + "-NOMINAL_ntuple_" + sampleName + "_" + era;

    TString fullPathName = input_dir + "/" + baseFileName +".root";//+ "_"+era+".root";
    std::cout << "file " << fullPathName << std::endl;
    TFile * file = new TFile(fullPathName);

    if (file->IsZombie()||file==NULL) {
      std::cout << "cannot open file " << fullPathName << std::endl;
      std::cout << "nothing will be done " << std::endl;
      block = true;
      return;
    }

    //    TTree * tree = (TTree*)file->Get("TauCheck");
    TFile * filePred=NULL;
    //    TTree * treeF=NULL;
    TString friendName = "";
    if(_usefriend){
      if(channel=="tt")
	friendName=input_friend_dir+"/"+baseFileName+"_pred.root";
      else
	friendName=input_friend_dir+"/"+baseFileName+"_pred.root";
      //friendName=input_friend_dir+channel+"-"+baseFileName+".root";
      filePred = new TFile(friendName);
      if (filePred->IsZombie()||filePred==NULL) {
	std::cout << "cannot open friend file " << friendName << std::endl;
	std::cout << "nothing will be done " << std::endl;
	block = true;
	return;
      }
      //      treeF=(TTree*)filePred->Get("TauCheck");
      //      treeF->SetTreeIndex(0);
      //      tree->AddFriend(treeF);
    }

    sampleFileMap[sampleName] = file;
    samplePredFileMap[sampleName] = filePred;
    if(channel=="em") sampleSpecificCutMap[sampleName] = SampleSpecificCutEM(name,sampleName);
    else sampleSpecificCutMap[sampleName] = SampleSpecificCutTT(name,sampleName);

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
  //  std::cout << std::endl;
  TString weight = regionWeight[region];
  

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
  TH1D * hist = NULL;
  TH2D * hist2D = NULL;
  std::cout << "creating histo " << histName << std::endl; 
  if (is2D) hist2D = create2DHisto(histName);
  else hist = createHisto(histName);

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
    std::cout << sampleName << "  :  entries in tree = " << tree->GetEntries() << std::endl;

    TTree * treeF = NULL;
    if (_usefriend) {
      TFile * fileF = sampleFileMap[sampleName];
      treeF = (TTree*)fileF->Get(treeName);
      treeF->SetTreeIndex(0);
      tree->AddFriend(treeF);
    }

    //    tree->AddFriend(treeName,friendName);
    TString cut = regionCut[region] + sampleSpecificCutMap[sampleName].at(region);
    TString HistName = sampleName+suffix;
    if(sysName!="")
      HistName+="_"+sysName;

    TH1D * histSample=NULL;
    TH2D * hist2DSample=NULL; 

    //    std::cout << "   creating histo " << HistName << std::endl; 
    if (is2D) 
      hist2DSample = create2DHisto(HistName);
    else
      histSample = createHisto(HistName);
    TString Cuts = weight + "(" + cut + ")";
    std::cout << "histo name " << HistName << " :  cuts = " << Cuts << std::endl;
    tree->Draw(variable+">>"+HistName,Cuts);
    if (is2D)
      hist2D->Add(hist2D,hist2DSample,1.,1.);
    else    
      hist->Add(hist,histSample,1.,1.);
    //    if (is2D) std::cout << "    ENTRIES = " << hist2DSample->GetEntries() << std::endl;
    //    else std::cout << "    ENTRIES = " << histSample->GetEntries() << std::endl;

    if (is2D) delete hist2DSample;
    else delete histSample;
  }

  if (is2D) {
    hist = unroll(hist2D,histName);
    delete hist2D;
  }
  if (name.Contains("ybyt"))
    hist->Scale(-1.0);
  else 
    zeroBins(hist);

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

  if (channel=="tt") {
    for (auto mapIter : ShapeSystematicsTT) {
      TString sysName = mapIter.first;
      TString treeName = mapIter.second;
      shapeSystematicsMap[sysName+era+"Up"] = treeName+"Up";
      shapeSystematicsMap[sysName+era+"Down"] = treeName+"Down";
      numberOfShapeSystematics += 2;
    }
  }

  if (channel=="em") {
    for (auto mapIter : ShapeSystematicsEM) {
      TString sysName = mapIter.first;
      TString treeName = mapIter.second;
      shapeSystematicsMap[sysName+era+"Up"] = treeName+"Up";
      shapeSystematicsMap[sysName+era+"Down"] = treeName+"Down";
      numberOfShapeSystematics += 2;
    }
  }

  /*
       
  if (sampleToProcess=="EMB") {
    for (auto mapIter : EmbeddedShapeSystematics) {
      TString sysName = mapIter.first;
      TString treeName = mapIter.second;
      shapeSystematicsMap[sysName+"_"+era+"Up"] = treeName+"Up";
      shapeSystematicsMap[sysName+"_"+era+"Down"] = treeName+"Down";
      numberOfShapeSystematics += 2;
    }
    for (auto mapIter : EmbeddedMetShapeSystematics) {
      TString sysName = mapIter.first;
      TString treeName = mapIter.second;
      shapeSystematicsMap[sysName] = treeName;
      numberOfShapeSystematics += 1;
    }
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
*/
  return numberOfShapeSystematics;

}

int Cards::CreateWeightSystematicsMap() {
   
  int numberOfWeightSystematics = 0; 
  /*
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
  */
  // Data ---->
  if (sampleToProcess=="Data") {

    if (channel=="em") {
      for (auto mapIter : QCDSystematics) {
	TString sysName = mapIter.first + "_" + era;
	TString weightName = mapIter.second;
	TString weightNameUp = weightName + "_up*";
	TString weightNameDown = weightName + "_down*";
	TString sysNameUp = sysName + "Up";
	TString sysNameDown = sysName + "Down";
	weightSystematicsMap[sysNameUp] = weightNameUp;
	weightSystematicsMap[sysNameDown] = weightNameDown;
      }
      for (auto mapIter : QCDIsoSystematics) {
	TString sysName = mapIter.first + "_" + era;
        TString weightName = mapIter.second;
        TString weightNameUp = weightName + "*";
        TString weightNameDown = "(1.0/"+weightName + ")*";
	TString sysNameUp = sysName + "Up";
        TString sysNameDown = sysName + "Down";
	weightSystematicsMap[sysNameUp] = weightNameUp;
        weightSystematicsMap[sysNameDown] = weightNameDown;
	numberOfWeightSystematics += 2;
      }
    }

    if (channel=="tt") {
      for (auto mapIter : FakeFactorSystematics) {
	TString sysName = mapIter.first + "_" + era;
	TString weightName = mapIter.second;
	TString weightNameUp = weightName + "*";
	TString weightNameDown = "(1.0/"+weightName+")*";
	TString sysNameUp = sysName + "Up";
	TString sysNameDown = sysName + "Down";
	weightSystematicsMap[sysNameUp] = weightNameUp;
	weightSystematicsMap[sysNameDown] = weightNameDown;    
	numberOfWeightSystematics += 2;
      }
    }
    
    return numberOfWeightSystematics;

  }

  for (auto mapIter : BTagSystematics) {
    TString sysName = "btag" + era + "_" + mapIter.first + "Up";
    TString weightName = mapIter.second;
    weightSystematicsMap[sysName] = weightName+"*";

    sysName = "btag" + era + "_" + mapIter.first + "Down";
    weightSystematicsMap[sysName] = "TMath::Max(0.1,2.0-"+weightName+")*";
    numberOfWeightSystematics += 2;
  }
  
  // Prefiring weight;
  for (auto mapIter : PrefiringSystematics) {
    TString sysName = mapIter.first;
    TString weightName = mapIter.second;
    weightSystematicsMap[sysName] = weightName+"*";      
    numberOfWeightSystematics++;
  }

  if (channel=="tt") {
    // tau id and trigger and l->tau fakes
    for (auto mapIter : WeightSystematicsTT) {
      TString sysName = mapIter.first;
      TString weightName = mapIter.second;
      weightSystematicsMap[sysName+"_"+era+"Up"] = weightName + "Up*";
      weightSystematicsMap[sysName+"_"+era+"Down"] = weightName + "Down*";
      numberOfWeightSystematics += 2;
    }
  }

  if (sampleToProcess=="HTT"||
      sampleToProcess=="HWW"||
      sampleToProcess=="bbHTT"||
      sampleToProcess=="bbHTT_nobb"||
      sampleToProcess=="bbHWW"||
      sampleToProcess=="bbHWW_nobb") {
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
  if (sampleToProcess=="EWK"||sampleToProcess=="ST")
    return numberOfWeightSystematics;
  
  // TTbar ---->
  if (sampleToProcess=="TT") {
    for (auto mapIter : TopShapeSystematics) {
      TString sysName = mapIter.first + "Up";
      TString weightName = mapIter.second;
      weightSystematicsMap[sysName] = weightName+"*";
      
      sysName = mapIter.first + "Down";
      weightSystematicsMap[sysName] = "TMath::Max(0.1,2.0-"+weightName+")*";
      numberOfWeightSystematics += 2;
      
   }      
    return numberOfWeightSystematics;
  }

  // DYJets ---->
  if (sampleToProcess=="DY"||sampleToProcess=="DYToTT"||sampleToProcess=="DYToLL") {
    for (auto mapIter : DYShapeSystematics) {
      TString sysName = mapIter.first + "Up";
      TString weightName = mapIter.second;
      weightSystematicsMap[sysName] = weightName+"*";

      sysName = mapIter.first + "Down";
      weightSystematicsMap[sysName] = "TMath::Max(0.1,2.0-"+weightName+")*";
      numberOfWeightSystematics += 2;
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
    //    cout << ">>> processing sample " << name << endl;
    TH1D * hist = ProcessSample(name,"",1,false);
    QCD->Add(QCD,hist,1.,-1.);
    QCD_Up->Add(QCD_Up,hist,1.,-0.8);
    QCD_Down->Add(QCD_Down,hist,1.,-1.2);
    delete hist;
  }
  
  if(channel=="em"){
    nameTH1DMap["QCD"] = QCD;
    nameTH1DMap["QCD_CMS_qcd_subtr_syst_em_"+era+"Up"] = QCD_Up;
    nameTH1DMap["QCD_CMS_qcd_subtr_syst_em_"+era+"Down"] = QCD_Down;
  }else{
    nameTH1DMap["jetFakes"] = QCD;
    nameTH1DMap["jetFakes_CMS_fakes_subtr_syst_tt_"+era+"Up"] = QCD_Up;
    nameTH1DMap["jetFakes_CMS_fakes_subtr_syst_tt_"+era+"Down"] = QCD_Down;
  }

  bool first = true;
  TH1D * histSingleFake;
  if(channel=="tt"){
    //    cout<<"Side band region for tt channel"<<endl;
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
    if(channel=="em") nameTH1DMap["QCD_"+sysName] = QCD_sys;
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
    TH1D * hist = ProcessSample("TTToTT","",0,false);
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
      std::cout << "hist : " << sampleHistName << "   entries = " << hist->GetEntries() << "   sumOfW = " << hist->GetSumOfWeights() << std::endl;
    }
    if (runWithShapeSystematics) {
      for (auto shapeSys : shapeSystematicsMap) {
	TString sysName = shapeSys.first;
	TH1D * hist = ProcessSample(name,sysName,0,false);
	TString sampleHistName = nameHistoMap[name] + "_" + sysName;
	// Systematics may not exist, be careful
	if (hist!=NULL) { 
	  nameTH1DMap[sampleHistName] = hist;
	  std::cout << "hist : " << sampleHistName << "   entries = " << hist->GetEntries() << "   sumOfW = " << hist->GetSumOfWeights() << std::endl;
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
  std::cout << "printing sampleSpecificCut" << std::endl;

  if (sampleToProcess=="Data") {
    vector<TString> sampleNames = nameSampleMap["Data"];
    std::cout << "Data -> " << nameHistoMap["Data"] << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << std::endl;
    for (auto sampleName : sampleNames) {
      std::cout << "      cut(SR/OS) : " << sampleSpecificCutMap[sampleName].at(0) << std::endl;
      std::cout << "      cut(SB/SS) : " << sampleSpecificCutMap[sampleName].at(1) << std::endl;
      if(channel=="tt")std::cout << "      cut(SF) : " << sampleSpecificCutMap[sampleName].at(2) << std::endl;
      
    }
  }

  for (auto name : samplesContainer) {
    std::cout << name << " -> " << nameHistoMap[name] << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << std::endl;
    vector<TString> sampleNames = nameSampleMap[name];
    for (auto sampleName : sampleNames) {
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
