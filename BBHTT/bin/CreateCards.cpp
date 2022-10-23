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
    std::cout << "usage of the script : CreateCards [config_file] [sample] [category]" << std::endl;
    exit(EXIT_FAILURE);
  }

  Config cfg(argv[1]);
  TString sample(argv[2]);
  TString category(argv[3]);

  TString inputDir(cfg.get<string>("InputDir"));
  TString outputDir(cfg.get<string>("OutputDir"));
  TString predDir(cfg.get<string>("PredDir"));
  TString era(cfg.get<string>("Era"));
  TString channel(cfg.get<string>("Channel"));
  TString variable(cfg.get<string>("Variable"));
  int nbins = cfg.get<int>("Nbins");
  double xmin = cfg.get<double>("Xmin");
  double xmax = cfg.get<double>("Xmax");
  bool runWithSystematics = cfg.get<bool>("Systematics");

  //  TString inputDir("/nfs/dust/cms/user/cardinia/Maryam/SynchNTuples_UL_v2/");
  //TString predDir("/nfs/dust/cms/user/makou/predict_synchNTuples/");
  //  TString predDir("/nfs/dust/cms/user/filatovo/ML/ml-framework/mlruns/4/2e465ee969674198839ed7c981ecf8fd/artifacts/pred/");
  //TString inputDir("/nfs/dust/cms/user/makou/predict_synchTuples_nonfriend/");
  //TString predDir("");
  //  string cmsswBase = (getenv("CMSSW_BASE"));
  //  gSystem -> Exec("mkdir " + outputDir);
  //  TString variable("m_sv");
  //  TString variable("m_vis");
  //  TString variable("pred_class_proba");
  //  TString variable("pt_tt:m_sv");
  //  int nbins   =   15;
  //  double xmin = 0.25;
  //  double xmax = 1.00;

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
