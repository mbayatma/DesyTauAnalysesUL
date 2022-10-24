#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include <iostream>
#include "DesyTauAnalyses/Common/interface/Config.h"
#include "DesyTauAnalyses/BBHTT/interface/Cards.h"

using namespace std;

int main(int argc, char * argv[]) {
  
  // arguments - config file, sample, category
  if (argc!=5) {
    std::cout << "usage of the script : CreateCards [sample] [category] [era] [channel]" << std::endl;
    exit(EXIT_FAILURE);
  }

  TString sample(argv[1]);
  TString category(argv[2]);
  TString era(argv[3]);
  TString channel(argv[4]); 

  string cmsswBase = (getenv("CMSSW_BASE"));
  string config_file = cmsswBase + "/src/DesyTauAnalyses/BBHTT/test/datacards/datacards_"+string(argv[4])+".conf";

  Config cfg(config_file.c_str());

  TString inputDir(cfg.get<string>("InputDir"));
  TString outputDir(cfg.get<string>("OutputDir"));
  TString predDir(cfg.get<string>("PredictionDir"));
  TString variable(cfg.get<string>("Variable"));
  int nbins = cfg.get<int>("Nbins");
  double xmin = cfg.get<double>("Xmin");
  double xmax = cfg.get<double>("Xmax");
  bool runWithSystematics = cfg.get<bool>("Systematics");

  bool runOnEmbedded = false;

  Cards * cardsEMu = new Cards(sample,
			       era,
			       category,
			       channel,
			       inputDir,
			       predDir,
			       outputDir,
			       variable,
			       nbins,
			       xmin,
			       xmax,
			       runWithSystematics,
			       runOnEmbedded
			       );
 
  cardsEMu->PrintSamples();
  cardsEMu->PrintShapeSystematics();
  cardsEMu->PrintWeightSystematics(); 

  cardsEMu->SetVariableToPlot(variable,nbins,xmin,xmax);

  //  cardsEMu->Run();
  cardsEMu->CloseFile();

  cout << endl << endl<<" >>>>> DONE >>>>>>" <<endl;
  delete cardsEMu;

}
