#!/bin/bash

CHANNEL=$1
YEAR=$2
echo "CONFIGFILE,FILELIST" > parameters.txt

if [[ $CHANNEL == "mm" ]]; then

    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WJetsToLNu_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf DYJetsToLL_M-50_amcatnlo 10

else 

    # DYJets_amcatnlo
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf DYJetsToLL_M-50_amcatnlo 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf DYJetsToLL_0J_amcatnlo 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf DYJetsToLL_1J_amcatnlo 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf DYJetsToLL_2J_amcatnlo 10

    # WJets_amcatnlo
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WJetsToLNu_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WJetsToLNu_0J_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WJetsToLNu_1J_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WJetsToLNu_2J_amcatnlo 20

    # H->tautau
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf GluGluHToTauTau_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf VBFHToTauTau_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WplusHToTauTau_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WminusHToTauTau_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ZHToTauTau_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ttHToTauTau_M125 5
    
    # BBH
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf bbHToTauTau_yb2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf bbHToTauTau_yt2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf bbHToTauTau_ybyt_M125 5

fi

# Exclusive VV
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WWTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ZZTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WZTo2L2Q 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WZTo3LNu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ZZTo2L2Q 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ZZTo4L 10

# TT
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf TTTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf TTToHadronic 20
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf TTToSemiLeptonic 20

# Single Top
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ST_t-channel_antitop_4f 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ST_t-channel_top_4f 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ST_tW_antitop_5f 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ST_tW_top_5f 10

if [[ $CHANNEL = "em" ]]; then
    # H->WW
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf GluGluHToWWTo2L2Nu_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf VBFHToWWTo2L2Nu_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WplusHToWWTo2L2Nu_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WminusHToWWTo2L2Nu_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ZHToWWTo2L2Nu_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ttHJetToNonbb_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ttZJets 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf ttWJets 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf WGToLNuG 5
    # BBHToWW
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf bbHToWWTo2L2Nu_yt2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf bbHToWWTo2L2Nu_yb2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_${YEAR}_MC.conf bbHToWWTo2L2Nu_ybyt_M125 5
fi

