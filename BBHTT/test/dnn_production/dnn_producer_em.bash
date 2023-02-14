#!/bin/bash
# submits sequence of dnn producers  
# this is directory where output of condor jobs will be put 
# (please change this directory appropriately)
dir=/nfs/dust/cms/user/rasp/Run/jobs
for era in 2016_pre 2016_post 2017 2018
do
    for sample in GluGluHToWW
#    for sample in MuonEG DYJets_amcatnlo WJets_amcatnlo SingleTop Diboson GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau TTHToTauTau TTHToWW GluGluHToWW VBFHToWW WHToWW ZHToWW BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT BBHToWW_YT2 BBHToWW_YBYT BBHToWW_YB2 TTVJets 
    do
	./dnn_producer.bash ${sample} ${era} em ${dir}
    done
done 
