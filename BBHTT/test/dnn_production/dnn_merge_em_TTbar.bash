#!/bin/bash
# merged 2016_pre and 2016_post for em channel
dir=/nfs/dust/cms/user/rasp/Run/emu_dnn_sys_UL
for sample in TTHToTauTau
#for sample in MuonEG DYJets_amcatnlo WJets TTbar SingleTop Diboson GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau GluGluHToWW VBFHToWW WHToWW ZHToWW BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT BBHToWW_YB2 BBHToWW_YBYT
do
    rm ${dir}/2016/em-NOMINAL_ntuple_${sample}_2016.root
    hadd ${dir}/2016/em-NOMINAL_ntuple_${sample}_2016.root ${dir}/2016_pre/em-NOMINAL_ntuple_${sample}_2016_pre.root ${dir}/2016_post/em-NOMINAL_ntuple_${sample}_2016_post.root
done
