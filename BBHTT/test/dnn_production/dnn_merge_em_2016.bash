#!/bin/bash
# submits sequence of dnn producers 
# change base directory for 
dir=/nfs/dust/cms/user/rasp/Run/emu_dnn_UL
for sample in Tau DYJets_amcatnlo WJets TTbar SingleTop Diboson GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau GluGluHToWW VBFHToWW WHToWW ZHToWW BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT BBHToWW_YB2 BBHToWW_YBYT
do
    rm ${dir}/2016/tt-NOMINAL_ntuple_${sample}_2016.root
    hadd ${dir}/2016/tt-NOMINAL_ntuple_${sample}_2016.root ${dir}/2016_pre/tt-NOMINAL_ntuple_${sample}_2016_pre.root ${dir}/2016_post/tt-NOMINAL_ntuple_${sample}_2016_post.root
done
