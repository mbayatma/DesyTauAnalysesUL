#!/bin/bash

CHANNEL=$1
echo "CONFIGFILE,FILELIST" > parameters.txt

if [[ $CHANNEL == "mm" ]]; then

    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WJetsToLNu_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf DYJetsToLL_M-50_amcatnlo 10

else 

    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf DYJetsToLL_M-50_amcatnlo 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf DYJetsToLL_0J_amcatnlo 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf DYJetsToLL_1J_amcatnlo 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf DYJetsToLL_2J_amcatnlo 10

    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WJetsToLNu_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WJetsToLNu_0J_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WJetsToLNu_1J_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WJetsToLNu_2J_amcatnlo 20

    # H->tautau
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf GluGluHToTauTau_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf VBFHToTauTau_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WplusHToTauTau_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WminusHToTauTau_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ZHToTauTau_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ttHToTauTau_M125 10
    
    # BBH
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf bbHToTauTau_yb2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf bbHToTauTau_yt2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf bbHToTauTau_ybyt_M125 5

fi

# Exclusive VV
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WWTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ZZTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WZTo2L2Q 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WZTo3LNu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ZZTo2L2Q 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ZZTo4L 10

# TT
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf TTTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf TTToHadronic 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf TTToSemiLeptonic 10

# Single Top
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ST_t-channel_antitop_4f 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ST_t-channel_top_4f 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ST_tW_antitop_5f 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ST_tW_top_5f 10

if [[ $CHANNEL = "em" ]]; then
    # H->WW
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf GluGluHToWWTo2L2Nu_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf VBFHToWWTo2L2Nu_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WplusHToWWTo2L2Nu_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf WminusHToWWTo2L2Nu_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf ZHToWWTo2L2Nu_M125 10
    # BBHToWW
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf bbHToWWTo2L2Nu_yb2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_18_MC.conf bbHToWWTo2L2Nu_ybyt_M125 5
fi

