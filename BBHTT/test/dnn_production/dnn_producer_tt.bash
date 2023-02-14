#!/bin/bash
# submits sequence of dnn producers 
dir=/nfs/dust/cms/user/rasp/Run/jobs
for era in 2016_pre 2016_post 2017 2018
do
    for sample in Tau DYJets_amcatnlo WJets_amcatnlo TTbar SingleTop Diboson GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau TTHToTauTau BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT
    do
	./dnn_producer.bash ${sample} ${era} tt ${dir}
    done
done 
