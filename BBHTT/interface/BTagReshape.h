#ifndef BTagReshape_h
#define BTagReshape_h

#include "TH1D.h"
#include "TH3.h"
#include "TFile.h"
#include "TString.h"
#include "TMath.h"
#include <iostream>
#include <string>
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"

using namespace std;

class BTagReshape {

 private:
  BTagCalibrationReader * reader;
  bool isCSV;
  bool isHistogram;
  TFile * file;

 public:
  BTagReshape(const std::string inputFileName);
  void SetCSV(const std::string inputFileName);
  ~BTagReshape();

  double getWeight(double jetPt,
		   double jetEta,
		   double jetDiscr,
		   int jetFlavor);

  double getWeightSys(double jetPt,
		      double jetEta,
		      double jetDiscr,
		      int jetFlavor,
		      string sysName,
		      bool dir);


  
  double getWeightCSV(double jetPt, 
		      double jetEta, 
		      double jetDiscr,
		      int jetFlavor) const;

  const std::vector<TString> systematics = 
    { "central",
      "up_jes","down_jes",
      "up_lf","down_lf",
      "up_hf","down_hf",
      "up_hfstats1","down_hfstats1",
      "up_hfstats2","down_hfstats2",
      "up_lfstats1","down_lfstats1",
      "up_lfstats2","down_lfstats2",
      "up_cferr1","down_cferr1",
      "up_cferr2","down_cferr2"
    };
  
  const std::vector<TString> flavors = 
    {
      "light","c","b"
    };

  std::map<TString, TH3D*> map_histo;

};

#endif

