#include <map>
#include <string>
#include <vector>
void TestFilters(int numberOfEvents = 10) {

  // 2018 MC ->
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/mc/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_ext/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_ext_10000.root");
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples/UL/2018/mc/DYJetsToLL_M-50/DYJetsToLL_M-50_243.root");

  //  2017 MC ->
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2017/mc/TTTo2L2Nu/TTTo2L2Nu_2534.root");

  // 2016 MC ->
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2016_preVFP/mc/TTTo2L2Nu/TTTo2L2Nu_191.root");
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2016_postVFP/mc/TTTo2L2Nu/TTTo2L2Nu_1625.root");
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples/UL/2018/mc/WJetsToLNu/WJetsToLNu_19447.root");
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/mc/bbHToTauTau_M125_ybyt_UL18MiniAODv2/bbHToTauTau_M125_ybyt_UL18MiniAODv2_99.root");
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/mc/bbHToTauTau_yb2_M125_MiniAODv2/bbHToTauTau_yb2_M125_MiniAODv2_98.root");
  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/mc/bbHToTauTau_yt2_M125_MiniAODv2/bbHToTauTau_yt2_M125_MiniAODv2_2059.root");

  // 2018 data ->
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/data/Tau-Run2018B-UL2018/Tau-Run2018B-UL2018_5479.root");
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/data/Tau-Run2018D-UL2018/Tau-Run2018D-UL2018_10599.root");

  // 2017 data ->
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2017/data/Tau_Run2017F/Tau_Run2017F_8765.root");

  // 2016 data ->
  //TFile * file =  new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2016_postVFP/data/Tau_Run2016H/Tau_Run2016H_6160.root");
  //  TFile * file = new TFile("/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2016_preVFP/data/Tau_Run2016E/Tau_Run2016E_11459.root");

  TTree * tree = (TTree*)file->Get("makeroottree/AC1B");

  vector<string> * hltfilters = new vector<string>();
  ULong64_t event_nr;

  vector<TString> filterList = {
    //    "hltL3fL1sMu7EG23f0Filtered8",
    "hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8",
    "hltHpsDoublePFTau35TrackPt1MediumChargedIsolationDz02Reg",
    "hltDoublePFTau40TrackPt1MediumChargedIsolationAndTightOOSCPhotonsDz02Reg",
    "hltDoublePFTau40TrackPt1TightChargedIsolationDz02Reg",
    "hltDoublePFTau35TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg",
    "hltDoublePFTau35TrackPt1MediumIsolationDz02Reg",
    "hltDoublePFTau35TrackPt1MediumCombinedIsolationDz02Reg",
    /*
    "hltL3fL1sDoubleMu114L1f0L2f10OneMuL3Filtered17",
    "hltL3pfL1sDoubleMu114L1f0L2pf0L3PreFiltered8",
    "hltL3pfL1sDoubleMu114ORDoubleMu125L1f0L2pf0L3PreFiltered8",
    "hltDiMuonGlb17Glb8DzFiltered0p2",
    "hltDiMuonGlb17Glb8DzFiltered0p2SameSign"
    "hltEle35noerWPTightGsfTrackIsoFilter",
    "hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p07", // IsoMu27
    "hltL3crIsoL1sMu22Or25L1f0L2f10QL3f27QL3trkIsoFiltered0p09",
    "hltPFTau180TrackPt50LooseAbsOrRelMediumHighPtRelaxedIsoIso",
    "hltSelectedPFTau180MediumChargedIsolationL1HLTMatched",
    "hltSingleL2Tau80eta2p2",
    "hltPFTau180TrackPt50LooseAbsOrRelMediumHighPtRelaxedIso1Prong",
    "hltSelectedPFTau180MediumChargedIsolationL1HLTMatched1Prong",
    "hltDoublePFTau40TrackPt1TightChargedIsolationDz02Reg",
    "hltDoublePFTau35TrackPt1TightChargedIsolationAndTightOOSCPhotonsDz02Reg",
    "hltDoublePFTau40TrackPt1MediumChargedIsolationAndTightOOSCPhotonsDz02Reg",
    "hltHpsDoublePFTau35TrackPt1MediumChargedIsolationDz02Reg",
    "hltDoubleL2IsoTau26eta2p2",
    "hltOverlapFilterIsoMu24TightChargedIsoAndTightOOSCPhotonsPFTau35MonitoringReg",
    "hltOverlapFilterIsoMu24MediumChargedIsoAndTightOOSCPhotonsPFTau40MonitoringReg",
    "hltOverlapFilterIsoMu24TightChargedIsoPFTau40MonitoringReg",
    "hltHpsOverlapFilterIsoMu24MediumChargedIsoPFTau35MonitoringReg",
    "hltSingleL2IsoTau26eta2p2",
    */
  }; 

  tree->SetBranchAddress("event_nr",&event_nr);
  tree->SetBranchAddress("run_hltfilters",&hltfilters);

  int nEntries = tree->GetEntries();

  std::cout << "Entries = " << nEntries << std::endl;

  int nEvents = 0;
  for (int iE=0; iE<numberOfEvents; ++iE) {

    nEvents++;

    tree->GetEntry(iE);

    std::cout << std::endl;
    std::cout << "event number = " << nEvents << std::endl;
    std::cout << std::endl;

    unsigned int nfilters = hltfilters->size();
    std::cout << "nfiltres = " << nfilters << std::endl;
    for (unsigned int ifilter=0; ifilter<filterList.size(); ++ifilter) {
      bool found = false;
      for (unsigned int i=0; i<nfilters; ++i) {
	//      std::cout << "HLT Filter : " << hltfilters->at(i) << " i: " << i << std::endl;
	TString Filter(hltfilters->at(i));
	if (Filter==filterList[ifilter]) {
	  std::cout << i << "  " << Filter << std::endl;
	  found = true;
	  break;
	}
      }
      if (!found) 
	std::cout << "Filter : " << filterList.at(ifilter) << " not found" << std::endl;
    }
    
    std::cout << "++++++++++++++++++++++++++++++++++++" << std::endl;
    
  }


}
