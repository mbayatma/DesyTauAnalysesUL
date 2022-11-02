#!/bin/bash
# submits sequence of dnn producers 
dir=/nfs/dust/cms/user/rasp/Run/tautau_dnn_UL/jobs
for era in 2017 2018
do
    for sample in Tau DYJets_amcatnlo WJets TTbar SingleTop Diboson GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT 
    do
	./dnn_producer.bash ${sample} ${era} tt ${dir}
    done
done 
