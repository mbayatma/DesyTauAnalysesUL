#include "DesyTauAnalyses/Common/interface/Config.h"
#include "TFile.h"
#include "TH3.h"
#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include "TMath.h"
#include <iostream>
#include <string>
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"

using namespace std;

int main(int argc, char ** argv) {

  string cmsswBase = (getenv("CMSSW_BASE"));
  vector<string> flavours = {"light","c","b"};
  vector<string> variations; variations.clear();
  vector<string> systematics = 
    {"jes","lf","hf","hfstats1","hfstats2","lfstats1","lfstats2","cferr1","cferr2"};
  for (auto sys : systematics) {
    string sys_up = "up_"+sys;
    variations.push_back(sys_up);
    string sys_down = "down_"+sys;
    variations.push_back(sys_down);
  }
  map<TString, TH3D*> map_histo;
  map<string, BTagEntry::JetFlavor> map_flavour = {
    {"light",BTagEntry::FLAV_UDSG},
    {"c",BTagEntry::FLAV_C},
    {"b",BTagEntry::FLAV_B}
  };

  Config cfg(argv[1]);

  string era = cfg.get<string>("Era");
  string btagFileName = cfg.get<string>("BTagReshapeFileName");
  TString Era(era);
  string inputFileName = cmsswBase+"/src/"+btagFileName; 

  const std::string algo = "deepFlavour";
  const std::string measType = "iterativefit";
  std::string central = "central";
  BTagCalibration calib("deepFlavour", inputFileName);
  BTagCalibrationReader * reader  = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, central, variations);  
  reader->load(calib, BTagEntry::FLAV_B, measType);
  reader->load(calib, BTagEntry::FLAV_C, measType);
  reader->load(calib, BTagEntry::FLAV_UDSG, measType);

  int nBinsEta = 3;
  float binsEta[4] = {0.,0.8,1.6,2.5};

  int nBinsPt = 7;
  float binsPt[8] = {20.,30.,40.,50.,60.,70.,100.,200.};

  int nBinsD = 100;
  float binsD[101];
  for (int iD=0; iD<=100; ++iD) {
    binsD[iD] = 0.01*float(iD);
  }

  TFile * file = new TFile("btag_reshape_"+Era+".root","recreate");
  file->cd("");

  for (auto flavour : flavours) {
    TString histName = TString(flavour) + "_" + TString(central);
    TH3D * hist = new TH3D(histName,"",
			   nBinsEta,binsEta,
			   nBinsPt,binsPt,
			   nBinsD,binsD);      
    BTagEntry::JetFlavor entryPoint = map_flavour[flavour];    
    std::cout << std::endl;
    std::cout << "Filling histogram : " << histName << std::endl;
    for (int iEta=0; iEta<nBinsEta; ++iEta) {
      float eta = 0.5*(binsEta[iEta]+binsEta[iEta+1]);
      for (int iPt=0; iPt<nBinsPt; ++iPt) {
	float pt = 0.5*(binsPt[iPt]+binsPt[iPt+1]);
	for (int iD=0; iD<nBinsD; ++iD) {
	  float d = 0.5*(binsD[iD]+binsD[iD+1]);
	  float weight = reader->eval_auto_bounds(central,entryPoint,eta,pt,d);
	  std::cout << "pt = " << pt << "  eta = " << eta << "  d = " << d << " : " << weight << std::endl;
	  hist->SetBinContent(iEta+1,iPt+1,iD+1,weight);
	}
      }
    }
    file->cd("");
    hist->Write(histName);
  }
  std::cout << std::endl;
  for (auto flavour : flavours) {
    for (auto name : variations) {
      TString histName = TString(flavour) + "_" + TString(name);
      TH3D * hist = new TH3D(histName,"",
			   nBinsEta,binsEta,
			   nBinsPt,binsPt,
			   nBinsD,binsD);      
      BTagEntry::JetFlavor entryPoint = map_flavour[flavour];    
      std::cout << "Filling histogram : " << histName << std::endl;
      for (int iEta=0; iEta<nBinsEta; ++iEta) {
	float eta = 0.5*(binsEta[iEta]+binsEta[iEta+1]);
	for (int iPt=0; iPt<nBinsPt; ++iPt) {
	  float pt = 0.5*(binsPt[iPt]+binsPt[iPt+1]);
	  for (int iD=0; iD<nBinsD; ++iD) {
	    float d = 0.5*(binsD[iD]+binsD[iD+1]);
	    const string nameSys = name; 
	    float weight = reader->eval_auto_bounds(nameSys,entryPoint,eta,pt,d);
	    hist->SetBinContent(iEta+1,iPt+1,iD+1,weight);
	  }
	}
      }
      file->cd("");
      hist->Write(histName);
    }
  }
  file->Write();
  file->Close();
  delete file;
  delete reader;
}
