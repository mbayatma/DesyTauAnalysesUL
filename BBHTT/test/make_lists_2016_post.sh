#!/bin/sh

CHANNEL=$1

dirMC2=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2016/mc_2
dirMC=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2016/mc
dirMC_UL=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2016_postVFP/mc
dirSignal_UL=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2016_postVFP/mc
dirData=/pnfs/desy.de/cms/tier2/store/user/acardini/ntuples/Oktoberfest21/2016_postVFP/data
dirEmbedded=/pnfs/desy.de/cms/tier2/store/user/rasp/ntuples_Dec2020/2016/emb

OUTDIR=./2016_post

if [ ! -d "$OUTDIR" ]; then
  echo "Path does not exist: ${OUTDIR}"
  echo "Please create it"
  exit
fi

if [[ $CHANNEL == "mm" ]]; then

#    ls $dirMC_UL/WJetsToLNu/*root > $OUTDIR/WJetsToLNu
    ls $dirMC_UL/WJetsToLNu_amcatnlo/*root > $OUTDIR/WJetsToLNu_amcatnlo

else 

#    ls $dirMC_UL/WJetsToLNu/*root > $OUTDIR/WJetsToLNu
#    ls $dirMC_UL/W1JetsToLNu/*root > $OUTDIR/W1JetsToLNu
#    ls $dirMC_UL/W2JetsToLNu/*root > $OUTDIR/W2JetsToLNu
#    ls $dirMC_UL/W3JetsToLNu/*root > $OUTDIR/W3JetsToLNu
#    ls $dirMC_UL/W4JetsToLNu/*root > $OUTDIR/W4JetsToLNu

    ls $dirMC_UL/WJetsToLNu_amcatnlo/*root > $OUTDIR/WJetsToLNu_amcatnlo
    ls $dirMC_UL/WJetsToLNu_0J_amcatnlo/*root > $OUTDIR/WJetsToLNu_0J_amcatnlo
    ls $dirMC_UL/WJetsToLNu_1J_amcatnlo/*root > $OUTDIR/WJetsToLNu_1J_amcatnlo
    ls $dirMC_UL/WJetsToLNu_2J_amcatnlo/*root > $OUTDIR/WJetsToLNu_2J_amcatnlo

    ls $dirMC_UL/GluGluHToTauTau_amcatnlo_M125_UL16MiniAODv2/*.root > $OUTDIR/GluGluHToTauTau_M125
    ls $dirMC_UL/VBFHToTauTau_M125/*.root > $OUTDIR/VBFHToTauTau_M125
    ls $dirMC_UL/WplusHToTauTau_M125/*.root > $OUTDIR/WplusHToTauTau_M125
    ls $dirMC_UL/WminusHToTauTau_M125/*.root > $OUTDIR/WminusHToTauTau_M125
    ls $dirMC_UL/ZHToTauTau_M125/*root > $OUTDIR/ZHToTauTau_M125
    ls $dirMC_UL/ttHToTauTau_M125/*root > $OUTDIR/ttHToTauTau_M125

    ls $dirSignal_UL/bbHToTauTau_yb2_M125_UL16MiniAODv2/*.root > $OUTDIR/bbHToTauTau_yb2_M125
    ls $dirSignal_UL/bbHToTauTau_yt2_M125_UL16MiniAODv2/*.root > $OUTDIR/bbHToTauTau_yt2_M125
    ls $dirSignal_UL/bbHToTauTau_M125_ybyt_UL16MiniAODv2/*.root > $OUTDIR/bbHToTauTau_ybyt_M125
    
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

ls $dirMC_UL/ST_t-channel_antitop_4f_InclusiveDecays/*root > $OUTDIR/ST_t-channel_antitop_4f
ls $dirMC_UL/ST_t-channel_top_4f_InclusiveDecays/*root > $OUTDIR/ST_t-channel_top_4f
ls $dirMC_UL/ST_tW_top_5f_inclusiveDecays/*root > $OUTDIR/ST_tW_top_5f
ls $dirMC_UL/ST_tW_antitop_5f_inclusiveDecays/*root > $OUTDIR/ST_tW_antitop_5f

ls $dirMC_UL/WWTo2L2Nu/*root > $OUTDIR/WWTo2L2Nu
ls $dirMC_UL/ZZTo2L2Nu/*root > $OUTDIR/ZZTo2L2Nu 
ls $dirMC_UL/WZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/*root > $OUTDIR/WZTo2L2Q
ls $dirMC_UL/WZTo3LNu/*root > $OUTDIR/WZTo3LNu
ls $dirMC_UL/ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX-pythia8/*root > $OUTDIR/ZZTo2L2Q
ls $dirMC_UL/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/*root > $OUTDIR/ZZTo4L

if [[ $CHANNEL == "em" ]]; then

    ls $dirData/MuonEG_Run2016F/*.root > $OUTDIR/MuonEG_Run2016F
    ls $dirData/MuonEG_Run2016G/*.root > $OUTDIR/MuonEG_Run2016G
    ls $dirData/MuonEG_Run2016H/*.root > $OUTDIR/MuonEG_Run2016H

#    ls $dirEmbedded/EmbeddingRun2016F_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2016F
#    ls $dirEmbedded/EmbeddingRun2016G_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2016G
#    ls $dirEmbedded/EmbeddingRun2016H_ElMu/*root > $OUTDIR/EmbeddedElMu_Run2016H

    ls $dirMC_UL/GluGluHToWWTo2L2Nu/*root > $OUTDIR/GluGluHToWWTo2L2Nu_M125
    ls $dirMC_UL/VBFHToWWTo2L2Nu/*root > $OUTDIR/VBFHToWWTo2L2Nu_M125
    ls $dirMC/HWminusJ_HToWW_M125_13TeV_powheg_pythia8/*root > $OUTDIR/WminusHToWWTo2L2Nu_M125
    ls $dirMC/HWplusJ_HToWW_M125_13TeV_powheg_pythia8/*root > $OUTDIR/WplusHToWWTo2L2Nu_M125
    ls $dirMC/HZJ_HToWW_M125_13TeV_powheg_pythia8/*root > $OUTDIR/ZHToWWTo2L2Nu_M125

    ls $dirMC2/bbHToWWTo2L2Nu_M-125_yb2/*.root > $OUTDIR/bbHToWWTo2L2Nu_yb2_M125
    ls $dirMC2/bbHToWWTo2L2Nu_M-125_ybyt/*.root > $OUTDIR/bbHToWWTo2L2Nu_ybyt_M125

elif [[ $CHANNEL == "tt" ]]; then

    ls $dirData/Tau_Run2016F/*.root > $OUTDIR/Tau_Run2016F
    ls $dirData/Tau_Run2016G/*.root > $OUTDIR/Tau_Run2016G
    ls $dirData/Tau_Run2016H/*.root > $OUTDIR/Tau_Run2016H

#    ls $dirEmbedded/EmbeddingRun2016F_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2016F
#    ls $dirEmbedded/EmbeddingRun2016G_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2016G
#    ls $dirEmbedded/EmbeddingRun2016H_TauTau/*root > $OUTDIR/EmbeddedTauTau_Run2016H

elif [[ $CHANNEL == "mm" ]]; then

    ls $dirData/SingleMuon_Run2016F/*.root > $OUTDIR/SingleMuon_Run2016F
    ls $dirData/SingleMuon_Run2016G/*.root > $OUTDIR/SingleMuon_Run2016G
    ls $dirData/SingleMuon_Run2016H/*.root > $OUTDIR/SingleMuon_Run2016H

fi
