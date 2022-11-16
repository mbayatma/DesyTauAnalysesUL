#!/bin/sh

CHANNEL=$1

dirMC2=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2017/mc_2
dirMC=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2017/mc
dirMC_UL=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2017/mc
dirSignal_UL=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2017/mc
dirData=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2017/data
dirEmbedded=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2017/emb

OUTDIR=./2017

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

    ls $dirMC_UL/GluGluHToTauTau/*root > $OUTDIR/GluGluHToTauTau_M125
    ls $dirMC_UL/VBFHToTauTau/*.root > $OUTDIR/VBFHToTauTau_M125
    ls $dirMC_UL/WplusHToTauTau/*.root > $OUTDIR/WplusHToTauTau_M125
    ls $dirMC_UL/WminusHToTauTau/*.root > $OUTDIR/WminusHToTauTau_M125
    ls $dirMC_UL/ZHToTauTau_M125_CP5_13TeV-powheg-pythia8_ext1/*root > $OUTDIR/ZHToTauTau_M125
    ls $dirMC_UL/ttHToTauTau/*root > $OUTDIR/ttHToTauTau_M125

    ls $dirSignal_UL/BBHToTauTau/*.root > $OUTDIR/bbHToTauTau_yb2_M125
    ls $dirSignal_UL/bbHToTauTau_yt2_M125_MiniAODv2/*.root > $OUTDIR/bbHToTauTau_yt2_M125
    ls $dirSignal_UL/bbHToTauTau_M125_ybyt_UL17MiniAODv2/*.root > $OUTDIR/bbHToTauTau_ybyt_M125

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

ls $dirMC_UL/TTToHadronic/*root > $OUTDIR/TTToHadronic
ls $dirMC_UL/TTTo2L2Nu/*root > $OUTDIR/TTTo2L2Nu

ls $dirMC_UL/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/*root > $OUTDIR/ST_t-channel_antitop_4f
ls $dirMC_UL/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/*root > $OUTDIR/ST_t-channel_top_4f
ls $dirMC_UL/ST_tW_top_5f/*root > $OUTDIR/ST_tW_top_5f
ls $dirMC_UL/ST_tW_antitop_5f/*root > $OUTDIR/ST_tW_antitop_5f

ls $dirMC_UL/WWTo2L2Nu/*root > $OUTDIR/WWTo2L2Nu
ls $dirMC_UL/ZZTo2L2Nu/*root > $OUTDIR/ZZTo2L2Nu 
ls $dirMC_UL/WZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/*root > $OUTDIR/WZTo2L2Q
ls $dirMC_UL/WZTo3LNu/*root > $OUTDIR/WZTo3LNu
ls $dirMC_UL/ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/*root > $OUTDIR/ZZTo2L2Q
ls $dirMC_UL/ZZTo4L/*root > $OUTDIR/ZZTo4L

if [[ $CHANNEL == "em" ]]; then

    ls $dirMC_UL/GluGluHToWWTo2L2Nu/*root > $OUTDIR/GluGluHToWWTo2L2Nu_M125
    ls $dirMC_UL/VBFHToWWTo2L2Nu/*root > $OUTDIR/VBFHToWWTo2L2Nu_M125
    ls $dirMC/HWminusJ_HToWW_M125_13TeV_powheg_jhugen724_pythia8_TuneCP5/*root > $OUTDIR/WminusHToWWTo2L2Nu_M125
    ls $dirMC/HWplusJ_HToWW_M125_13TeV_powheg_jhugen724_pythia8_TuneCP5/*root > $OUTDIR/WplusHToWWTo2L2Nu_M125
    ls $dirMC/HZJ_HToWW_M125_13TeV_powheg_jhugen714_pythia8_TuneCP5/*root > $OUTDIR/ZHToWWTo2L2Nu_M125

    ls $dirMC2/bbHToWWTo2L2Nu_M-125_yb2/*.root > $OUTDIR/bbHToWWTo2L2Nu_yb2_M125
    ls $dirMC2/bbHToWWTo2L2Nu_M-125_ybyt/*.root > $OUTDIR/bbHToWWTo2L2Nu_ybyt_M125

    ls $dirData/MuonEG_Run2017B/*.root > $OUTDIR/MuonEG_Run2017B
    ls $dirData/MuonEG_Run2017C/*.root > $OUTDIR/MuonEG_Run2017C
    ls $dirData/MuonEG_Run2017D/*.root > $OUTDIR/MuonEG_Run2017D
    ls $dirData/MuonEG_Run2017E/*.root > $OUTDIR/MuonEG_Run2017E
    ls $dirData/MuonEG_Run2017F/*.root > $OUTDIR/MuonEG_Run2017F

#    ls $dirEmbedded/EmbeddingRun2017B_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2017B
#    ls $dirEmbedded/EmbeddingRun2017C_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2017C
#    ls $dirEmbedded/EmbeddingRun2017D_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2017D
#    ls $dirEmbedded/EmbeddingRun2017E_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2017E
#    ls $dirEmbedded/EmbeddingRun2017F_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2017F

elif [[ $CHANNEL == "tt" ]]; then

    ls $dirData/Tau_Run2017B/*.root > $OUTDIR/Tau_Run2017B
    ls $dirData/Tau_Run2017C/*.root > $OUTDIR/Tau_Run2017C
    ls $dirData/Tau_Run2017D/*.root > $OUTDIR/Tau_Run2017D
    ls $dirData/Tau_Run2017E/*.root > $OUTDIR/Tau_Run2017E
    ls $dirData/Tau_Run2017F/*.root > $OUTDIR/Tau_Run2017F

#    ls $dirEmbedded/EmbeddingRun2017B_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2017B
#    ls $dirEmbedded/EmbeddingRun2017C_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2017C
#    ls $dirEmbedded/EmbeddingRun2017D_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2017D
#    ls $dirEmbedded/EmbeddingRun2017E_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2017E
#    ls $dirEmbedded/EmbeddingRun2017F_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2017F

elif [[ $CHANNEL == "mm" ]]; then

    ls $dirData/SingleMuon_Run2017B/*.root > $OUTDIR/SingleMuon_Run2017B
    ls $dirData/SingleMuon_Run2017C/*.root > $OUTDIR/SingleMuon_Run2017C
    ls $dirData/SingleMuon_Run2017D/*.root > $OUTDIR/SingleMuon_Run2017D
    ls $dirData/SingleMuon_Run2017E/*.root > $OUTDIR/SingleMuon_Run2017E
    ls $dirData/SingleMuon_Run2017F/*.root > $OUTDIR/SingleMuon_Run2017F

fi
