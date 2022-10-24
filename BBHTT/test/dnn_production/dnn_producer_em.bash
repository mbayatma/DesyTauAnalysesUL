#!/bin/bash
# submits sequence of dnn producers 
for era in 2017 2018
do
    for sample in MuonEG DYJets_amcatnlo DrellYanJets WJets TTbar SingleTop Diboson GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau GluGluHToWW VBFHToWW WHToWW ZHToWW BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToWW_YBYT BBHToWW_YB2
    do
	./dnn_producer.bash ${sample} ${era} em
    done
done 
