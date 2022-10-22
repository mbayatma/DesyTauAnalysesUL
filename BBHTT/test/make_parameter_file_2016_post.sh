#!/bin/bash

CHANNEL=$1
echo "CONFIGFILE,FILELIST" > parameters.txt


if [[ $CHANNEL == "em" ]]; then
    # data
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_data.conf MuonEG_Run2016F 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_dataGH.conf MuonEG_Run2016G 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_dataGH.conf MuonEG_Run2016H 10
    
    # Embedded
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_embedded.conf EmbeddedElMu_Run2016F 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_embedded.conf EmbeddedElMu_Run2016G 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_embedded.conf EmbeddedElMu_Run2016H 4
elif [[ $CHANNEL == "tt" ]]; then
    # data
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_data.conf Tau_Run2016F 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_data.conf Tau_Run2016G 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_data.conf Tau_Run2016H 10
    
    # Embedded
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_embedded.conf EmbeddedTauTau_Run2016F 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_embedded.conf EmbeddedTauTau_Run2016G 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_embedded.conf EmbeddedTauTau_Run2016H 4

elif [[ $CHANNEL == "mm" ]]; then

    # data
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_data.conf SingleMuon_Run2016F 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_data.conf SingleMuon_Run2016G 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_data.conf SingleMuon_Run2016H 10

fi


if [[ $CHANNEL == "mm" ]]; then
    # W+jets
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WJetsToLNu 20
else   

    # W+jets
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WJetsToLNu 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf W1JetsToLNu 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf W2JetsToLNu 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf W3JetsToLNu 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf W4JetsToLNu 20

    # H->tautau
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf GluGluHToTauTau_M125_amcatnlo 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf GluGluHToTauTau_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf VBFHToTauTau_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WplusHToTauTau_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WminusHToTauTau_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf ZHToTauTau_M125 4

    # H->tautau+b's
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf bbHToTauTau_yb2_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf bbHToTauTau_yt2_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf bbHToTauTau_ybyt_M125 4

fi

# DY
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf DYJetsToLL_M-50_amcatnlo 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf DYJetsToLL_0J_amcatnlo 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf DYJetsToLL_1J_amcatnlo 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf DYJetsToLL_2J_amcatnlo 10

# Exclusive VV
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WWTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf ZZTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WZTo2L2Q 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WZTo3LNu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf ZZTo2L2Q 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf ZZTo4L 10

# TT
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf TTTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf TTToSemiLeptonic 20
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf TTToHadronic 20

# Single Top
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf ST_t-channel_antitop_4f 20
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf ST_t-channel_top_4f 20
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf ST_tW_antitop_5f 20
./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf ST_tW_top_5f 20

# H->WW
if [[ $CHANNEL == "em" ]]; then
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf GluGluHToWWTo2L2Nu_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf VBFHToWWTo2L2Nu_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WminusHToWWTo2L2Nu_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WplusHToWWTo2L2Nu_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf ZHToWWTo2L2Nu_M125 4
    # WGamma
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf WGToLNuG 10
    # H->WW+b's
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf bbHToWWTo2L2Nu_yb2_M125 4 
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_16_post_MC.conf bbHToWWTo2L2Nu_ybyt_M125 4
fi


