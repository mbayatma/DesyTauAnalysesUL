#include "DesyTauAnalyses/BBHTT/interface/BTagReshape.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"


BTagReshape::BTagReshape(const std::string inputFileName) {
  
  const std::string algo = "deepFlavour";
  const std::string measType = "iterativefit";
  const std::string sysType = "central";
  
  BTagCalibration calib("deepFlavour", inputFileName, true);
  reader =  new BTagCalibrationReader(BTagEntry::OP_RESHAPING, sysType) ;
  
  reader->load(calib, BTagEntry::FLAV_B, measType);
  reader->load(calib, BTagEntry::FLAV_C, measType);
  reader->load(calib, BTagEntry::FLAV_UDSG, measType);
 
  std::vector<float> ptV = {25., 50., 120.};
  std::vector<float> etaV = {0.1, 1.6, 2.1};
  std::vector<float> discrV = {0.1, 0.6, 0.8};

  std::cout << "testing btag reshaping ->" << std::endl;
  for (auto pt : ptV) {
    for (auto eta : etaV) {
      for (auto discr : discrV ) {
	std::cout << "b    : pt = " << pt 
		  << "   eta = " << eta 
		  << "   disr = " << discr 
		  << "   weight = " << reader->eval(BTagEntry::FLAV_B,eta,pt,discr) << std::endl;
	std::cout << "udsg : pt = " << pt 
		  << "   eta = " << eta 
		  << "   disr = " << discr 
		  << "   weight = " << reader->eval(BTagEntry::FLAV_UDSG,eta,pt,discr) << std::endl;
      }
    }
  }
  std::cout << std::endl;

}

double BTagReshape::getWeight(double jetPt,
			      double jetEta,
			      double jetDiscr,
			      int jetFlavor) const {

  int absJetFlavor = TMath::Abs(jetFlavor);  
  double absJetEta = TMath::Abs(jetEta);

  double wght = 1.0;
  if (absJetFlavor==5)
    wght = reader->eval(BTagEntry::FLAV_B, absJetEta, jetPt, jetDiscr);
  else if (absJetFlavor==4)
    wght = reader->eval(BTagEntry::FLAV_C, absJetEta, jetPt, jetDiscr);
  else
    wght = reader->eval(BTagEntry::FLAV_UDSG, absJetEta, jetPt, jetDiscr);

  return wght;

}

BTagReshape::~BTagReshape() {
  delete reader;
}


