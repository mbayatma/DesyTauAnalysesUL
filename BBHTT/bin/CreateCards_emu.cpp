//#include "DesyTauAnalyses/BBHTT/interface/settings.h"
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
  
  // argument - config file
  if (argc!=5) {
    std::cout << "usage of the script : CreateCards_emu [era=2016,2017,2018] [Sample=Data,EWK,DYJets,EMB,TTbar,ggH,qqH,VH,bbH] [category] [Systematics=0,1]" << std::endl;
    exit(EXIT_FAILURE);
  }

  TString era(argv[1]);
  era="2018";
  TString sample(argv[2]);
  TString category(argv[3]);
  int systematics = atoi(argv[4]);
  int triggerOption = 0;

  TString inputDir("/nfs/dust/cms/user/cardinia/Maryam/SynchNTuples_UL_v2/");
  TString predDir("/nfs/dust/cms/user/makou/predict_synchNTuples/");
  string cmsswBase = (getenv("CMSSW_BASE"));

  TString outputDir = (TString) cmsswBase + "/src/DesyTauAnalyses/BBHTT/test/datacards/datacardsEMu_"+era;
  gSystem -> Exec("mkdir " + outputDir);

  //  TString variable("m_sv");
  //  TString variable("m_vis");
  TString variable("pred_proba");
  //  TString variable("pt_tt:m_sv");
  int nbins   =   15;
  double xmin = 0.25;
  double xmax = 1.00;
  bool runWithSystematics = true;
  if (systematics==0) runWithSystematics = false;
  bool runOnEmbedded = false;

  Cards * cardsEMu = new Cards(sample,
			       era,
			       category,
			       "em",
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

  cardsEMu->Run();
  cardsEMu->CloseFile();

  cout << endl << endl<<" >>>>> DONE >>>>>>" <<endl;
  delete cardsEMu;

}
