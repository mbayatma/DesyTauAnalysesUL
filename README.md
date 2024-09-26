# DesyTauAnalysesUL
DesyTauAnalyses FW for Run2 UL campaign

## BBHTT analysis

For the bbH(tau tau) analysis the setup script is located in the [subdirectory BBHTT](https://github.com/DesyTau/DesyTauAnalysesUL/tree/bbHTT/BBHTT#desytauanalysesul---bbhtt-analysis)


### Install BBHTT version
In order to install framework for bbH(tau tau) with required CMSSW dependencies:
```sh
wget https://raw.githubusercontent.com/DesyTau/DesyTauAnalysesUL/bbHTT/BBHTT/setup.sh
source setup.sh
```



## General remarks on main branch

Corresponding framework is an updated and refactored version of the DESY Tau analysis framework: https://github.com/DesyTau/DesyTauAnalysesRun2_25ns
(as of commit: https://github.com/DesyTau/DesyTauAnalysesRun2_25ns/commit/fdcc47df731580e5bc78b09d2b90602307897bc9)

### Install main branch
In order to install framework with required CMSSW dependencies:
```sh
wget https://raw.githubusercontent.com/DesyTau/DesyTauAnalysesUL/main/setup.sh
chmod 755 setup.sh
./setup.sh
```
