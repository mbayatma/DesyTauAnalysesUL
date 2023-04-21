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
  if (argc!=6) {
    std::cout << "usage of the script : CreateCards [sample] [category] [era] [channel] [config]" << std::endl;
    exit(EXIT_FAILURE);
  }

  TString sample(argv[1]);
  TString category(argv[2]);
  TString era(argv[3]);
  TString channel(argv[4]); 
  string config(argv[5]);

  string cmsswBase = (getenv("CMSSW_BASE"));
  string config_file = cmsswBase + "/src/DesyTauAnalyses/BBHTT/test/datacards/"+string(argv[5]);

  Config cfg(config_file.c_str());

  TString inputDir(cfg.get<string>("InputDir"));
  TString outputDir(cfg.get<string>("OutputDir"));
  TString predDir(cfg.get<string>("PredictionDir"));
  TString variable(cfg.get<string>("Variable"));
  bool equidistant = cfg.get<bool>("Equidistant");
  int nbins = cfg.get<int>("Nbins");
  double xmin = cfg.get<double>("Xmin");
  double xmax = cfg.get<double>("Xmax");
  vector<double> xbins = cfg.get<vector<double> >("Bins");
  int minSmooth = cfg.get<int>("MinSmooth");
  int maxSmooth = cfg.get<int>("MaxSmooth");
  int rangeSmooth = cfg.get<int>("RangeSmooth");
  bool runWithSystematics = cfg.get<bool>("Systematics");
  bool useLooseShape = cfg.get<bool>("UseLooseShape");
  bool rebin = cfg.get<bool>("Rebin");
  bool testCards = cfg.get<bool>("TestCards");
  bool runOnEmbedded = false;

  Cards * cards = new Cards(sample,
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
 
  cards->PrintSamples();
  cards->PrintShapeSystematics();
  cards->PrintWeightSystematics(); 

  if (equidistant)
    cards->SetVariableToPlot(variable,nbins,xmin,xmax);
  else {
    nbins = xbins.size() - 1;
    cards->SetVariableToPlot(variable,nbins,xbins);
    std::cout << "nbins = " << nbins << std::endl;
    for (int i=0; i<=nbins; ++i)
      std::cout << xbins[i] << std::endl;
    //    exit(-1);
  }
  cards->SetSmoothing(minSmooth,maxSmooth,rangeSmooth);
  if (useLooseShape) cards->SetLooseShape(useLooseShape);
  if (rebin) cards->Rebin(rebin,xbins);
  if (!testCards) cards->Run();
  cards->CloseFile();
  cout << endl;
  cout << endl << endl<<" >>>>> DONE >>>>>>" <<endl;
  delete cards;

}
