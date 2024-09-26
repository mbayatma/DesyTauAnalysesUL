#!/bin/sh
dirData=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/data
dirMC_UL=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/mc
dirMC_UL_v2=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples/UL/2018/mc
dirMC=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2018/mc

CHANNEL=$1

OUTDIR=./2018
if [ ! -d "$OUTDIR" ]; then
  echo "Path does not exist: ${OUTDIR}"
  echo "Please create it"
  exit
fi

if [[ $CHANNEL == "mm" ]]; then

    ls $dirMC_UL/WJetsToLNu_amcatnlo/*root > $OUTDIR/WJetsToLNu
else

    ls $dirMC_UL/WJetsToLNu_amcatnlo/*root > $OUTDIR/WJetsToLNu_amcatnlo
    ls $dirMC_UL/WJetsToLNu_0J_amcatnlo/*root > $OUTDIR/WJetsToLNu_0J_amcatnlo
    ls $dirMC_UL/WJetsToLNu_1J_amcatnlo/*root > $OUTDIR/WJetsToLNu_1J_amcatnlo
    ls $dirMC_UL/WJetsToLNu_2J_amcatnlo/*root > $OUTDIR/WJetsToLNu_2J_amcatnlo

    ls $dirMC_UL_v2/GluGluHToTauTau_M125/*root > $OUTDIR/GluGluHToTauTau_M125
    ls $dirMC_UL_v2/VBFHToTauTau_M125/*.root > $OUTDIR/VBFHToTauTau_M125
    ls $dirMC_UL_v2/WplusHToTauTau_M125/*.root > $OUTDIR/WplusHToTauTau_M125
    ls $dirMC_UL_v2/WminusHToTauTau_M125/*.root > $OUTDIR/WminusHToTauTau_M125
    ls $dirMC_UL_v2/ZHToTauTau_M125/*root > $OUTDIR/ZHToTauTau_M125
    ls $dirMC_UL/ttHToTauTau_M125/*root > $OUTDIR/ttHToTauTau_M125

    ls $dirMC_UL/bbHToTauTau_yb2_M125_MiniAODv2/*.root > $OUTDIR/bbHToTauTau_yb2_M125
    ls $dirMC_UL/bbHToTauTau_yt2_M125_MiniAODv2/*.root > $OUTDIR/bbHToTauTau_yt2_M125
    ls $dirMC_UL/bbHToTauTau_M125_ybyt_UL18MiniAODv2/*.root > $OUTDIR/bbHToTauTau_ybyt_M125

fi

# Huge files -> split them
ls $dirMC_UL_v2/TTToSemiLeptonic/*0.root > $OUTDIR/TTToSemiLeptonic
ls $dirMC_UL_v2/DYJetsToLL_M-50_amcatnlo/*0.root > $OUTDIR/DYJetsToLL_M-50_amcatnlo
ls $dirMC_UL_v2/DYJetsToLL_0J_amcatnlo/*0.root > $OUTDIR/DYJetsToLL_0J_amcatnlo
ls $dirMC_UL_v2/DYJetsToLL_1J_amcatnlo/*0.root > $OUTDIR/DYJetsToLL_1J_amcatnlo
ls $dirMC_UL_v2/DYJetsToLL_2J_amcatnlo/*0.root > $OUTDIR/DYJetsToLL_2J_amcatnlo
for index in {1..9}
do
    ls $dirMC_UL_v2/TTToSemiLeptonic/*${index}.root >> $OUTDIR/TTToSemiLeptonic
    ls $dirMC_UL_v2/DYJetsToLL_M-50_amcatnlo/*${index}.root >> $OUTDIR/DYJetsToLL_M-50_amcatnlo
    ls $dirMC_UL_v2/DYJetsToLL_0J_amcatnlo/*${index}.root >> $OUTDIR/DYJetsToLL_0J_amcatnlo
    ls $dirMC_UL_v2/DYJetsToLL_1J_amcatnlo/*${index}.root >> $OUTDIR/DYJetsToLL_1J_amcatnlo
    ls $dirMC_UL_v2/DYJetsToLL_2J_amcatnlo/*${index}.root >> $OUTDIR/DYJetsToLL_2J_amcatnlo
done

ls $dirMC_UL_v2/TTTo2L2Nu/*root > $OUTDIR/TTTo2L2Nu
ls $dirMC_UL_v2/TTToHadronic/*root > $OUTDIR/TTToHadronic

ls $dirMC_UL_v2/ST_t-channel_antitop_4f/*root > $OUTDIR/ST_t-channel_antitop_4f
ls $dirMC_UL_v2/ST_t-channel_top_4f/*root > $OUTDIR/ST_t-channel_top_4f
ls $dirMC_UL/ST_tW_antitop_5f_inclusiveDecays/*root > $OUTDIR/ST_tW_antitop_5f
ls $dirMC_UL/ST_tW_top_5f_inclusiveDecays/*root > $OUTDIR/ST_tW_top_5f

ls $dirMC_UL_v2/WWTo2L2Nu/*root > $OUTDIR/WWTo2L2Nu
ls $dirMC_UL_v2/ZZTo2L2Nu/*root > $OUTDIR/ZZTo2L2Nu
ls $dirMC_UL_v2/WZTo2Q2L/*root > $OUTDIR/WZTo2L2Q
ls $dirMC_UL_v2/WZTo3LNu/*root > $OUTDIR/WZTo3LNu
ls $dirMC_UL_v2/ZZTo2Q2L/*root > $OUTDIR/ZZTo2L2Q
ls $dirMC_UL_v2/ZZTo4L/*root > $OUTDIR/ZZTo4L

if [[ $CHANNEL == "em" ]]; then

    ls $dirMC_UL/GluGluHToWWTo2L2Nu/*root > $OUTDIR/GluGluHToWWTo2L2Nu_M125
    ls $dirMC_UL/VBFHToWWTo2L2Nu/*root > $OUTDIR/VBFHToWWTo2L2Nu_M125
    ls $dirMC/HWminusJ_HToWW_M125_13TeV_powheg_jhugen724_pythia8_TuneCP5/*root > $OUTDIR/WplusHToWWTo2L2Nu_M125
    ls $dirMC/HWplusJ_HToWW_M125_13TeV_powheg_jhugen724_pythia8_TuneCP5/*root > $OUTDIR/WminusHToWWTo2L2Nu_M125
    ls $dirMC/HZJ_HToWW_M125_13TeV_powheg_jhugen714_pythia8_TuneCP5/*root > $OUTDIR/ZHToWWTo2L2Nu_M125
    ls $dirMC_UL/ttHJetToNonbb_M125/*root > $OUTDIR/ttHJetToNonbb_M125
    ls $dirMC_UL/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/*root > $OUTDIR/ttWJets
    ls $dirMC_UL/ttZJets_TuneCP5_13TeV_madgraphMLM_pythia8/*root > $OUTDIR/ttZJets
    ls $dirMC_UL/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/*root > $OUTDIR/WGToLNuG

    ls $dirMC_UL/bbHWWTo2L2Nu_M-125_4FS_yb2/*root > $OUTDIR/bbHToWWTo2L2Nu_yb2_M125
    ls $dirMC_UL/bbHWWTo2L2Nu_M-125_4FS_ybyt/*root > $OUTDIR/bbHToWWTo2L2Nu_ybyt_M125
    ls $dirMC_UL/bbHWWTo2L2Nu_M-125_4FS_yt2/*root > $OUTDIR/bbHToWWTo2L2Nu_yt2_M125

    ls $dirData/MuonEG-Run2018A-UL2018/*.root > $OUTDIR/MuonEG_Run2018A
    ls $dirData/MuonEG-Run2018B-UL2018/*.root > $OUTDIR/MuonEG_Run2018B
    ls $dirData/MuonEG-Run2018C-UL2018/*.root > $OUTDIR/MuonEG_Run2018C
    ls $dirData/MuonEG-Run2018D-UL2018/*.root > $OUTDIR/MuonEG_Run2018D

elif [[ $CHANNEL == "tt" ]]; then

    ls $dirData/Tau-Run2018A-UL2018/*.root > $OUTDIR/Tau_Run2018A
    ls $dirData/Tau-Run2018B-UL2018/*.root > $OUTDIR/Tau_Run2018B
    ls $dirData/Tau-Run2018C-UL2018/*.root > $OUTDIR/Tau_Run2018C
    ls $dirData/Tau-Run2018D-UL2018/*.root > $OUTDIR/Tau_Run2018D

elif [[ $CHANNEL == "mm" ]]; then

    ls $dirData/SingleMuon-Run2018A-UL2018/*.root > $OUTDIR/SingleMuon_Run2018A
    ls $dirData/SingleMuon-Run2018B-UL2018/*.root > $OUTDIR/SingleMuon_Run2018B
    ls $dirData/SingleMuon-Run2018C-UL2018/*.root > $OUTDIR/SingleMuon_Run2018C
    ls $dirData/SingleMuon-Run2018D-UL2018/*0.root > $OUTDIR/SingleMuon_Run2018D
    for index in {1..9}
    do
	ls $dirData/SingleMuon-Run2018D-UL2018/*${index}.root >> $OUTDIR/SingleMuon_Run2018D
    done
    
fi
