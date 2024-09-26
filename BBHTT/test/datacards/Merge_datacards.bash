#!/bin/bash
channel=$1
folder=$2
# em : /nfs/dust/cms/user/rasp/Run/emu_datacards_sysv1_UL/BDT_coarse
#    : /nfs/dust/cms/user/rasp/Run/emu_datacards_sysJES/BDT_coarse
# tt : /nfs/dust/cms/user/rasp/Run/tautau_datacards_newTauID_UL/BDT_coarse
#    : /nfs/dust/cms/user/rasp/Run/tautau_datacards_sysJES_5Cat/BDT_coarse
cd $folder
for era in 2016 2017 2018
do
    rm bbH_${1}_${era}.root
    hadd bbH_${1}_${era}.root ${era}/*.root
done
cd -
