#!/bin/sh

CHANNEL=$1

dirMC=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2016/mc
dirMC_UL=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2016_preVFP/mc
dirData=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2016_preVFP/data

OUTDIR=./2016_pre

if [ ! -d "$OUTDIR" ]; then
  echo "Path does not exist: ${OUTDIR}"
  echo "Please create it"
  exit
fi

if [[ $CHANNEL == "mm" ]]; then

    ls $dirMC_UL/WJetsToLNu_amcatnlo/*root > $OUTDIR/WJetsToLNu_amcatnlo

else

    ls $dirMC_UL/WJetsToLNu_amcatnlo/*root > $OUTDIR/WJetsToLNu_amcatnlo
    ls $dirMC_UL/WJetsToLNu_0J_amcatnlo/*root > $OUTDIR/WJetsToLNu_0J_amcatnlo
    ls $dirMC_UL/WJetsToLNu_1J_amcatnlo/*root > $OUTDIR/WJetsToLNu_1J_amcatnlo
    ls $dirMC_UL/WJetsToLNu_2J_amcatnlo/*root > $OUTDIR/WJetsToLNu_2J_amcatnlo

    ls $dirMC_UL/GluGluHToTauTau_M-125_amcatnlo/*.root > $OUTDIR/GluGluHToTauTau_M125
    ls $dirMC_UL/VBFHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/*.root > $OUTDIR/VBFHToTauTau_M125
    ls $dirMC_UL/WplusHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/*.root > $OUTDIR/WplusHToTauTau_M125
    ls $dirMC_UL/WminusHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/*.root > $OUTDIR/WminusHToTauTau_M125
    ls $dirMC_UL/ZHToTauTau_M125_CP5_13TeV-powheg-pythia8_ext1/*root > $OUTDIR/ZHToTauTau_M125
    ls $dirMC_UL/ttHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/*root > $OUTDIR/ttHToTauTau_M125

    ls $dirMC_UL/bbHToTauTau_yb2_M125_MiniAODv2/*root > $OUTDIR/bbHToTauTau_yb2_M125
    ls $dirMC_UL/bbHToTauTau_yt2_M125_MiniAODv2/*root > $OUTDIR/bbHToTauTau_yt2_M125
    ls $dirMC_UL/bbHToTauTau_ybyt_M125_MiniAODv2/*root > $OUTDIR/bbHToTauTau_ybyt_M125

fi

# Huge filelists -> split them
ls $dirMC_UL/TTToSemiLeptonic/*0.root > $OUTDIR/TTToSemiLeptonic
ls $dirMC_UL/DYJetsToLL_M-50_amcatnlo/*0.root > $OUTDIR/DYJetsToLL_M-50_amcatnlo
ls $dirMC_UL/DYJetsToLL_0J_amcatnlo/*0.root > $OUTDIR/DYJetsToLL_0J_amcatnlo
ls $dirMC_UL/DYJetsToLL_1J_amcatnlo/*0.root > $OUTDIR/DYJetsToLL_1J_amcatnlo
ls $dirMC_UL/DYJetsToLL_2J_amcatnlo/*0.root > $OUTDIR/DYJetsToLL_2J_amcatnlo
for index in {1..9}
do
    ls $dirMC_UL/TTToSemiLeptonic/*${index}.root >> $OUTDIR/TTToSemiLeptonic
    ls $dirMC_UL/DYJetsToLL_M-50_amcatnlo/*${index}.root >> $OUTDIR/DYJetsToLL_M-50_amcatnlo
    ls $dirMC_UL/DYJetsToLL_0J_amcatnlo/*${index}.root >> $OUTDIR/DYJetsToLL_0J_amcatnlo
    ls $dirMC_UL/DYJetsToLL_1J_amcatnlo/*${index}.root >> $OUTDIR/DYJetsToLL_1J_amcatnlo
    ls $dirMC_UL/DYJetsToLL_2J_amcatnlo/*${index}.root >> $OUTDIR/DYJetsToLL_2J_amcatnlo
done

ls $dirMC_UL/TTToHadronic/*root > $OUTDIR/TTToHadronic
ls $dirMC_UL/TTTo2L2Nu/*root > $OUTDIR/TTTo2L2Nu

ls $dirMC_UL/ST_t-channel_antitop_4f/*root > $OUTDIR/ST_t-channel_antitop_4f
ls $dirMC_UL/ST_t-channel_top_4f/*root > $OUTDIR/ST_t-channel_top_4f
ls $dirMC_UL/ST_tW_top_5f_inclusiveDecays/*root > $OUTDIR/ST_tW_top_5f
ls $dirMC_UL/ST_tW_antitop_5f_inclusiveDecays/*root > $OUTDIR/ST_tW_antitop_5f

ls $dirMC_UL/WWTo2L2Nu/*root > $OUTDIR/WWTo2L2Nu
ls $dirMC_UL/ZZTo2L2Nu/*root > $OUTDIR/ZZTo2L2Nu 
ls $dirMC_UL/WZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/*root > $OUTDIR/WZTo2L2Q
ls $dirMC_UL/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/*root > $OUTDIR/WZTo3LNu
ls $dirMC_UL/ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/*root > $OUTDIR/ZZTo2L2Q
ls $dirMC_UL/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/*root > $OUTDIR/ZZTo4L

if [[ $CHANNEL == "em" ]]; then

    ls $dirMC_UL/GluGluHToWWTo2L2Nu/*root > $OUTDIR/GluGluHToWWTo2L2Nu_M125
    ls $dirMC_UL/VBFHToWWTo2L2Nu/*root > $OUTDIR/VBFHToWWTo2L2Nu_M125
    ls $dirMC/HWminusJ_HToWW_M125_13TeV_powheg_pythia8/*root > $OUTDIR/WminusHToWWTo2L2Nu_M125
    ls $dirMC/HWplusJ_HToWW_M125_13TeV_powheg_pythia8/*root > $OUTDIR/WplusHToWWTo2L2Nu_M125
    ls $dirMC/HZJ_HToWW_M125_13TeV_powheg_pythia8/*root > $OUTDIR/ZHToWWTo2L2Nu_M125
    ls $dirMC_UL/ttHJetToNonbb_M125/*root > $OUTDIR/ttHJetToNonbb_M125
    ls $dirMC_UL/TTWJetsToLNu/*root > $OUTDIR/ttWJets
    ls $dirMC_UL/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/*root > $OUTDIR/ttZJets
    ls $dirMC_UL/WGToLNuG/*root > $OUTDIR/WGToLNuG

    ls $dirMC_UL/bbHWWTo2L2Nu_M-125_4FS_yt2/*root > $OUTDIR/bbHToWWTo2L2Nu_yt2_M125
    ls $dirMC_UL/bbHWWTo2L2Nu_M-125_4FS_yb2/*root > $OUTDIR/bbHToWWTo2L2Nu_yb2_M125
    ls $dirMC_UL/bbHWWTo2L2Nu_M-125_4FS_ybyt/*root > $OUTDIR/bbHToWWTo2L2Nu_ybyt_M125

    ls $dirData/MuonEG_Run2016B-ver2/*.root > $OUTDIR/MuonEG_Run2016B
    ls $dirData/MuonEG_Run2016C/*.root > $OUTDIR/MuonEG_Run2016C
    ls $dirData/MuonEG_Run2016D/*.root > $OUTDIR/MuonEG_Run2016D
    ls $dirData/MuonEG_Run2016E/*.root > $OUTDIR/MuonEG_Run2016E
    ls $dirData/MuonEG_Run2016F/*.root > $OUTDIR/MuonEG_Run2016F

elif [[ $CHANNEL == "tt" ]]; then

    ls $dirData/Tau_Run2016B-ver2/*.root > $OUTDIR/Tau_Run2016B
    ls $dirData/Tau_Run2016C/*.root > $OUTDIR/Tau_Run2016C
    ls $dirData/Tau_Run2016D/*.root > $OUTDIR/Tau_Run2016D
    ls $dirData/Tau_Run2016E/*.root > $OUTDIR/Tau_Run2016E
    ls $dirData/Tau_Run2016F/*.root > $OUTDIR/Tau_Run2016F

elif [[ $CHANNEL == "mm" ]]; then

    ls $dirData/SingleMuon_Run2016B-ver2/*.root > $OUTDIR/SingleMuon_Run2016B
    ls $dirData/SingleMuon_Run2016C/*.root > $OUTDIR/SingleMuon_Run2016C
    ls $dirData/SingleMuon_Run2016D/*.root > $OUTDIR/SingleMuon_Run2016D
    ls $dirData/SingleMuon_Run2016E/*.root > $OUTDIR/SingleMuon_Run2016E
    ls $dirData/SingleMuon_Run2016F_preVFP/*.root > $OUTDIR/SingleMuon_Run2016F
    
fi
