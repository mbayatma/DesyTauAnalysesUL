#!/bin/bash
# submits sequence of dnn producers 
for era in 2016_post
do
    for sample in Tau DYJets_amcatnlo DrellYanJets WJets TTbar SingleTop Diboson GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT 
    do
	./dnn_producer.bash ${sample} ${era} tt
    done
done 
