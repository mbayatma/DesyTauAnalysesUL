#!/bin/sh
dirMC=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2018/mc
dirMC_2=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2018/mc_2
dirData=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/data
dirEmbedded=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2018/emb
dirMC_UL=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2018/mc

CHANNEL=$1

OUTDIR=./2018
if [ ! -d "$OUTDIR" ]; then
  echo "Path does not exist: ${OUTDIR}"
  echo "Please create it"
  exit
fi

if [[ $CHANNEL == "mm" ]]; then

    ls $dirMC_UL/WJetsToLNu/*root > $OUTDIR/WJetsToLNu
else

    ls $dirMC_UL/WJetsToLNu/*root > $OUTDIR/WJetsToLNu
    ls $dirMC_UL/W1JetsToLNu/*root > $OUTDIR/W1JetsToLNu
    ls $dirMC_UL/W2JetsToLNu/*root > $OUTDIR/W2JetsToLNu
    ls $dirMC_UL/W3JetsToLNu/*root > $OUTDIR/W3JetsToLNu
    ls $dirMC_UL/W4JetsToLNu/*root > $OUTDIR/W4JetsToLNu

    ls $dirMC_UL/GluGluHToTauTau_amcatnlo_M125_MiniAOD/*root > $OUTDIR/GluGluHToTauTau_M125
    ls $dirMC_UL/VBFHToTauTau_M125/*.root > $OUTDIR/VBFHToTauTau_M125
    ls $dirMC_UL/WplusHToTauTau_M125/*.root > $OUTDIR/WplusHToTauTau_M125
    ls $dirMC_UL/WminusHToTauTau_M125/*.root > $OUTDIR/WminusHToTauTau_M125
    ls $dirMC_UL/ZHToTauTau_M125/*.root > $OUTDIR/ZHToTauTau_M125
    ls $dirMC_UL/ttHToTauTau_M125/*.root $OUTDIR/ttHToTauTau_M125
    
    ls $dirMC_UL/bbHToTauTau_yb2_M125_MiniAODv2/*.root > $OUTDIR/bbHToTauTau_yb2_M125
    ls $dirMC_UL/bbHToTauTau_yt2_M125_MiniAODv2/*.root > $OUTDIR/bbHToTauTau_yt2_M125
    ls $dirMC_UL/bbHToTauTau_ybyt_M125_MiniAODv2/*.root > $OUTDIR/bbHToTauTau_ybyt_M125

fi

# Huge files -> split them
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

ls $dirMC_UL/TTTo2L2Nu/*root > $OUTDIR/TTTo2L2Nu
ls $dirMC_UL/TTToHadronic/*root > $OUTDIR/TTToHadronic

ls $dirMC_UL/ST_t-channel_antitop_4f/*root > $OUTDIR/ST_t-channel_antitop_4f
ls $dirMC_UL/ST_t-channel_top_4f/*root > $OUTDIR/ST_t-channel_top_4f
ls $dirMC_UL/ST_tW_antitop_5f_inclusiveDecays/*root > $OUTDIR/ST_tW_antitop_5f
ls $dirMC_UL/ST_tW_top_5f_inclusiveDecays/*root > $OUTDIR/ST_tW_top_5f

ls $dirMC_UL/WWTo2L2Nu/*root > $OUTDIR/WWTo2L2Nu
ls $dirMC_UL/ZZTo2L2Nu/*root > $OUTDIR/ZZTo2L2Nu
ls $dirMC_UL/WZTo2Q2L/*root > $OUTDIR/WZTo2L2Q
ls $dirMC_UL/WZTo3LNu/*root > $OUTDIR/WZTo3LNu
ls $dirMC_UL/ZZTo2Q2L/*root > $OUTDIR/ZZTo2L2Q
ls $dirMC_UL/ZZTo4L/*root > $OUTDIR/ZZTo4L

if [[ $CHANNEL == "em" ]]; then

    ls $dirMC_UL/GluGluHToWWTo2L2Nu/*root > $OUTDIR/GluGluHToWWTo2L2Nu_M125
    ls $dirMC_UL/VBFHToWWTo2L2Nu/*root > $OUTDIR/VBFHToWWTo2L2Nu_M125
    ls $dirMC/HWminusJ_HToWW_M125_13TeV_powheg_jhugen724_pythia8_TuneCP5/*root > $OUTDIR/WplusHToWWTo2L2Nu_M125
    ls $dirMC/HWplusJ_HToWW_M125_13TeV_powheg_jhugen724_pythia8_TuneCP5/*root > $OUTDIR/WminusHToWWTo2L2Nu_M125
    ls $dirMC/HZJ_HToWW_M125_13TeV_powheg_jhugen714_pythia8_TuneCP5/*root > $OUTDIR/ZHToWWTo2L2Nu_M125

    ls $dirMC2/bbHToWWTo2L2Nu_M-125_yb2/*.root > $OUTDIR/bbHToWWTo2L2Nu_yb2_M125
    ls $dirMC2/bbHToWWTo2L2Nu_M-125_ybyt/*.root > $OUTDIR/bbHToWWTo2L2Nu_ybyt_M125

    ls $dirData/MuonEG-Run2018A-UL2018/*.root > $OUTDIR/MuonEG_Run2018A
    ls $dirData/MuonEG-Run2018B-UL2018/*.root > $OUTDIR/MuonEG_Run2018B
    ls $dirData/MuonEG-Run2018C-UL2018/*.root > $OUTDIR/MuonEG_Run2018C
    ls $dirData/MuonEG-Run2018D-UL2018/*.root > $OUTDIR/MuonEG_Run2018D

#    ls $dirEmbedded/EmbeddingRun2018A_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2018A
#    ls $dirEmbedded/EmbeddingRun2018B_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2018B
#    ls $dirEmbedded/EmbeddingRun2018C_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2018C
#    ls $dirEmbedded/EmbeddingRun2018D_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2018D

elif [[ $CHANNEL == "tt" ]]; then

    ls $dirData/Tau-Run2018A-UL2018/*.root > $OUTDIR/Tau_Run2018A
    ls $dirData/Tau-Run2018B-UL2018/*.root > $OUTDIR/Tau_Run2018B
    ls $dirData/Tau-Run2018C-UL2018/*.root > $OUTDIR/Tau_Run2018C
    ls $dirData/Tau-Run2018D-UL2018/*.root > $OUTDIR/Tau_Run2018D

#    ls $dirEmbedded/EmbeddingRun2018A_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2018A
#    ls $dirEmbedded/EmbeddingRun2018B_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2018B
#    ls $dirEmbedded/EmbeddingRun2018C_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2018C
#    ls $dirEmbedded/EmbeddingRun2018D_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2018D

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
