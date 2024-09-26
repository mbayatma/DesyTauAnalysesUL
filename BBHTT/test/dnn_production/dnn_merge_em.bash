#!/bin/bash
# modify properly the parameter below (location of DNN tuples)
dir=/nfs/dust/cms/user/rasp/Run/emu_dnn_sysJES_fixed

# merging TTbar tuples with central tree and different systematic trees ->
for era in 2016_pre 2016_post 2017 2018
do
    rm ${dir}/${era}/em-NOMINAL_ntuple_TTbar_${era}.root
    hadd ${dir}/${era}/em-NOMINAL_ntuple_TTbar_${era}.root ${dir}/${era}/em-NOMINAL_ntuple_TTbar_${era}_*.root
done

# merging 2016_pre and 2016_post samples
for sample in MuonEG DYJets_amcatnlo WJets_amcatnlo TTbar SingleTop Diboson TTVJets   GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau TTHToTauTau   GluGluHToWW VBFHToWW WHToWW ZHToWW TTHToWW   BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT   BBHToWW_YT2 BBHToWW_YB2 BBHToWW_YBYT
do
    rm ${dir}/2016/em-NOMINAL_ntuple_${sample}_2016.root
    hadd ${dir}/2016/em-NOMINAL_ntuple_${sample}_2016.root ${dir}/2016_pre/em-NOMINAL_ntuple_${sample}_2016_pre.root ${dir}/2016_post/em-NOMINAL_ntuple_${sample}_2016_post.root
done
