#!/bin/bash
# merges 2016_pre and 2016_post samples
dir=/nfs/dust/cms/user/rasp/Run/tautau_dnn_sysJES_5Cat
#for sample in WJets_amcatnlo
for sample in Tau DYJets_amcatnlo WJets_amcatnlo TTbar SingleTop Diboson GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau TTHToTauTau BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT 
do
    rm ${dir}/2016/tt-NOMINAL_ntuple_${sample}_2016.root
    hadd ${dir}/2016/tt-NOMINAL_ntuple_${sample}_2016.root ${dir}/2016_pre/tt-NOMINAL_ntuple_${sample}_2016_pre.root ${dir}/2016_post/tt-NOMINAL_ntuple_${sample}_2016_post.root
done
