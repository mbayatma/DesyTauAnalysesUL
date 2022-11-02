#!/bin/bash
# submits sequence of dnn producers  
# please change this directory appropriately
# this is directory where output of condor jobs will be put 
dir=/nfs/dust/cms/user/rasp/Run/jobs
for era in 2016_pre 2016_post
do
    for sample in MuonEG DYJets_amcatnlo WJets TTbar SingleTop Diboson GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau GluGluHToWW VBFHToWW WHToWW ZHToWW BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT BBHToWW_YBYT BBHToWW_YB2
    do
	./dnn_producer.bash ${sample} ${era} em ${dir}
    done
done 
