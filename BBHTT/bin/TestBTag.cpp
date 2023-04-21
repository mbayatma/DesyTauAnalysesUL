#include "DesyTauAnalyses/Common/interface/Config.h"
#include "TFile.h"
#include "TH3.h"
#include "TH2.h"
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
  variations.push_back("up");
  variations.push_back("down");
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
  std::cout << inputFileName << std::endl;
  BTagCalibration calib("deepFlavour", inputFileName);
  BTagCalibrationReader * reader_B  = new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up","down"});   BTagCalibrationReader * reader_C  = new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up","down"});   BTagCalibrationReader * reader_Light  = new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central", {"up","down"});  
  reader_B->load(calib, BTagEntry::FLAV_B, "comb");
  reader_C->load(calib, BTagEntry::FLAV_C, "comb");
  reader_Light->load(calib, BTagEntry::FLAV_UDSG, "incl");
  map<string,BTagCalibrationReader*> mapReader = {
    {"light",reader_Light},
    {"c",reader_C},
    {"b",reader_B}
  };


  int nBinsEta = 3;
  float binsEta[4] = {0.,0.8,1.6,2.5};

  int nBinsPt = 7;
  float binsPt[8] = {20.,30.,40.,50.,60.,70.,100.,200.};

  TFile * file = new TFile("btag_wpDeepJet_"+Era+".root","recreate");
  file->cd("");

  for (auto flavour : flavours) {
    BTagCalibrationReader * reader = mapReader[flavour];    
    TString histName = TString(flavour) + "_" + TString(central);
    TH2D * hist = new TH2D(histName,"",
			   nBinsEta,binsEta,
			   nBinsPt,binsPt);      
    BTagEntry::JetFlavor entryPoint = map_flavour[flavour];    
    std::cout << std::endl;
    std::cout << "Filling histogram : " << histName << std::endl;
    for (int iEta=0; iEta<nBinsEta; ++iEta) {
      float eta = 0.5*(binsEta[iEta]+binsEta[iEta+1]);
      for (int iPt=0; iPt<nBinsPt; ++iPt) {
	float pt = 0.5*(binsPt[iPt]+binsPt[iPt+1]);
	float weight = reader->eval_auto_bounds(central,entryPoint,-eta,pt);
	std::cout << "pt = " << pt << "  eta = " << eta << " : " << weight << std::endl;
	hist->SetBinContent(iEta+1,iPt+1,weight);
      }
    }
    file->cd("");
    hist->Write(histName);
  }
  std::cout << std::endl;
  for (auto flavour : flavours) {
    BTagCalibrationReader * reader = mapReader[flavour];    
    for (auto name : variations) {
      TString histName = TString(flavour) + "_" + TString(name);
      TH2D * hist = new TH2D(histName,"",
			     nBinsEta,binsEta,
			     nBinsPt,binsPt);
      BTagEntry::JetFlavor entryPoint = map_flavour[flavour];    
      std::cout << "Filling histogram : " << histName << std::endl;
      for (int iEta=0; iEta<nBinsEta; ++iEta) {
	float eta = 0.5*(binsEta[iEta]+binsEta[iEta+1]);
	for (int iPt=0; iPt<nBinsPt; ++iPt) {
	  float pt = 0.5*(binsPt[iPt]+binsPt[iPt+1]);
	  float weight = reader->eval_auto_bounds(name,entryPoint,-eta,pt);
	  hist->SetBinContent(iEta+1,iPt+1,weight);
	}
      }
      file->cd("");
      hist->Write(histName);
    }
  }
  file->Write();
  file->Close();
  delete file;
  delete reader_B;
  delete reader_C;
  delete reader_Light;
}
