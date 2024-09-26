#!/bin/bash

CHANNEL=$1
echo "CONFIGFILE,FILELIST" > parameters.txt

#if [[ $CHANNEL = "em" ]]; then
# data
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_dataB.conf MuonEG_Run2017B 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf MuonEG_Run2017C 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf MuonEG_Run2017D 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf MuonEG_Run2017E 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf MuonEG_Run2017F 10
    
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedElMu_Run2017B 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedElMu_Run2017C 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedElMu_Run2017D 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedElMu_Run2017E 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedElMu_Run2017F 4
#elif [[ $CHANNEL == "tt" ]]; then
#
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf Tau_Run2017B 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf Tau_Run2017C 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf Tau_Run2017D 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf Tau_Run2017E 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf Tau_Run2017F 10
    
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedTauTau_Run2017B 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedTauTau_Run2017C 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedTauTau_Run2017D 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedTauTau_Run2017E 4
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_embedded.conf EmbeddedTauTau_Run2017F 4
#elif [[ $CHANNEL == "mm" ]]; then
#
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf SingleMuon_Run2017B 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf SingleMuon_Run2017C 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf SingleMuon_Run2017D 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf SingleMuon_Run2017E 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_data.conf SingleMuon_Run2017F 10
#    
#fi 


# DY and W+jets
if [[ $CHANNEL == "mm" ]]; then

    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf DYJetsToLL_M-50_amcatnlo 10
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WJetsToLNu 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WJetsToLNu_amcatnlo 20

else 

    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf DYJetsToLL_M-50_amcatnlo 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf DYJetsToLL_0J_amcatnlo 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf DYJetsToLL_1J_amcatnlo 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf DYJetsToLL_2J_amcatnlo 10

#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WJetsToLNu 20
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf W1JetsToLNu 20
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf W2JetsToLNu 20
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf W3JetsToLNu 20
#    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf W4JetsToLNu 20

    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WJetsToLNu_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WJetsToLNu_0J_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WJetsToLNu_1J_amcatnlo 20
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WJetsToLNu_2J_amcatnlo 20

    # H->tautau
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf GluGluHToTauTau_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf VBFHToTauTau_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WplusHToTauTau_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WminusHToTauTau_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ZHToTauTau_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ttHToTauTau_M125 4

    # BBH
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf bbHToTauTau_yb2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf bbHToTauTau_yt2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf bbHToTauTau_ybyt_M125 5

fi


# Exclusive VV
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WWTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ZZTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WZTo2L2Q 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WZTo3LNu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ZZTo2L2Q 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ZZTo4L 10

# TT
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf TTTo2L2Nu 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf TTToHadronic 10
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf TTToSemiLeptonic 10

# Single Top
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ST_t-channel_antitop_4f 20
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ST_t-channel_top_4f 20
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ST_tW_antitop_5f 20
./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ST_tW_top_5f 20

if [[ $CHANNEL = "em" ]]; then
# H->WW
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf GluGluHToWWTo2L2Nu_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf VBFHToWWTo2L2Nu_M125 4
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WplusHToWWTo2L2Nu_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf WminusHToWWTo2L2Nu_M125 10
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf ZHToWWTo2L2Nu_M125 10
# BBHToWW
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf bbHToWWTo2L2Nu_yb2_M125 5
    ./split_filelist.sh analysisMacroSynch_${CHANNEL}_17_MC.conf bbHToWWTo2L2Nu_ybyt_M125 5
fi
