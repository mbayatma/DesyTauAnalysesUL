#ifndef DataCardsEMu_h
#define DataCardsEMu_h

#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include "TMath.h"
#include <iostream>
#include <string>
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"


class BTagReshape {

 private:
  BTagCalibrationReader * reader;

 public:
  BTagReshape(const std::string inputFileName);
  ~BTagReshape();

  double getWeight(double jetPt, 
		   double jetEta, 
		   double jetDiscr,
		   int jetFlavor) const;
  


};

#endif

