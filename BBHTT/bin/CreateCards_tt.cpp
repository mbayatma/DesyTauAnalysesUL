//#include "DesyTauAnalyses/BBHTT/interface/settings.h"
#include "TFile.h"
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
  if (argc!=6) {
    std::cout << "usage of the script : CreateCards_emu [era=2016,2017,2018] [channel=em,tt] [Sample=Data,EWK,DYJets,EMB,TTbar,ggH,qqH,VH,bbH] [category] [Systematics=0,1]" << std::endl;
    exit(-1);
  }

  TString era(argv[1]);
  TString channel(argv[2]);
  TString sample(argv[2]);
  TString category(argv[3]);
  int systematics = atoi(argv[4]);
  int triggerOption = 0;

  TString inputDir("/nfs/dust/cms/user/rasp/Run/tautau/Aug21/");
  TString outputDir("/nfs/dust/cms/user/rasp/Run/tautau/Aug21/datacards_ml_btag");
  //  TString variable("m_sv");
  //  TString variable("m_vis");
  TString variable("pred_class_proba");
  //  TString variable("pt_tt:m_sv");
  int nbins   =   15;
  double xmin = 0.25;
  double xmax = 1.00;
  bool runWithSystematics = true;
  if (systematics==0) runWithSystematics = false;
  bool runOnEmbedded = true;

  Cards * cardsTauTau = new Cards(sample,
					      era,
					      category,
					      inputDir,
					      outputDir,
					      variable,
					      nbins,
					      xmin,
					      xmax,
					      runWithSystematics,
					      runOnEmbedded
					      );
 
  cardsTauTau->PrintSamples();
  cardsTauTau->PrintShapeSystematics();
  cardsTauTau->PrintWeightSystematics(); 

  cardsTauTau->SetVariableToPlot(variable,nbins,xmin,xmax);

  cardsTauTau->Run();
  cardsTauTau->CloseFile();
  delete cardsTauTau;

}
