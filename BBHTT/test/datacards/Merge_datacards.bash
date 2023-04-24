#!/bin/bash
channel=$1
folder=$2
# em : /nfs/dust/cms/user/rasp/Run/emu_datacards_sys_UL/BDT_coarse/nonneg_v2
#    : /nfs/dust/cms/user/rasp/Run/emu_datacards_sys_UL/BDT_fine/nonneg_v2
#    : /nfs/dust/cms/user/rasp/Run/emu_datacards_ST_UL/BDT_coarse
#    : /nfs/dust/cms/user/rasp/Run/emu_datacards_ST_UL/BDT_fine
# tt : /nfs/dust/cms/user/rasp/Run/tautau_datacards_newTauID_UL/BDT_coarse
cd $folder
for era in 2016 2017 2018
do
    rm bbH_${1}_${era}.root
    hadd bbH_${1}_${era}.root ${era}/*.root
done
cd -
