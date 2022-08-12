export CMSSW_GIT_REFERENCE=/nfs/dust/cms/user/${USER}/.cmsgit-cache
source /cvmfs/cms.cern.ch/cmsset_default.sh

export SCRAM_ARCH=slc7_amd64_gcc700

cmsrel CMSSW_12_1_1
cd CMSSW_12_1_1/src
cmsenv

git cms-init

cd ${CMSSW_BASE}/src
git clone https://github.com/CMS-HTT/HiggsCPinTauDecays.git

scram b -j 8

cd ${CMSSW_BASE}/src

git clone https://github.com/svfit/ClassicSVfit TauAnalysis/ClassicSVfit -b fastMTT_19_02_2019
git clone https://github.com/svfit/SVfitTF TauAnalysis/SVfitTF

cd ${CMSSW_BASE}/src
git clone https://github.com/CMS-HTT/RecoilCorrections.git HTT-utilities/RecoilCorrections

cd ${CMSSW_BASE}/src
git clone https://github.com/marmeyer/RecoilCorrections.git HTT-utilities/RecoilCorrections_KIT

cd ${CMSSW_BASE}/src
git clone https://github.com/CMS-HTT/CorrectionsWorkspace HTT-utilities/CorrectionsWorkspace
cd ${CMSSW_BASE}/src/HTT-utilities/CorrectionsWorkspace
root -l -q CrystalBallEfficiency.cxx++
cd ${CMSSW_BASE}/src

git clone https://github.com/veelken/SVfit_standalone.git ${CMSSW_BASE}/src/TauAnalysis/SVfitStandalone
cd ${CMSSW_BASE}/src/TauAnalysis/SVfitStandalone
git checkout HIG-16-006
cd ${CMSSW_BASE}/src/


cd ${CMSSW_BASE}/src
git clone https://github.com/DesyTau/DesyTauAnalysesUL.git DesyTauAnalyses -b bbHTT


cp ${CMSSW_BASE}/src/DesyTauAnalyses/patch/SVFit/SVfitStandaloneAlgorithm.h TauAnalysis/SVfitStandalone/interface/
cp ${CMSSW_BASE}/src/DesyTauAnalyses/patch/SVFit/SVfitStandaloneAlgorithm.cc TauAnalysis/SVfitStandalone/src
cp ${CMSSW_BASE}/src/DesyTauAnalyses/patch/SVFit/testSVfitStandalone.cc TauAnalysis/SVfitStandalone/bin
rm TauAnalysis/SVfitStandalone/interface/SVfitStandaloneQuantities.h
rm TauAnalysis/SVfitStandalone/src/SVfitStandaloneQuantities.cc

cd ${CMSSW_BASE}/src

cp -r /nfs/dust/cms/user/cardinia/public/DesyTau_data/data ${CMSSW_BASE}/src/DesyTauAnalyses/Common/.

git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools
cd PhysicsTools/NanoAODTools

python3 -c 'import correctionlib._core; import correctionlib.schemav2'
cd ${CMSSW_BASE}/src



scram b -j 16
scram b -j 16


