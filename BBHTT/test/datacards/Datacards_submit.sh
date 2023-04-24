#!/bin/sh 
# $1 - sample : Data,DYToTT,DYToLL,ST,TT,EWK,HTT,bbHTT,bbHTT_nobb [HWW, bbHWW, bbHWW_nobb]
# $2 - category inclusive, Nbtag0, NbtagGe1, 
#               cat0,          cat1,          cat2,          cat3
#               cat0_Nbtag0,   cat1_Nbtag0  , cat2_Nbtag0  , cat3_Nbtag0
#               cat0_NbtagGe1, cat1_NbtagGe1, cat2_NbtagGe1, cat3_NbtagGe1
# $3 - era (2016, 2017, 2018)
# $4 - channel (em, tt)
# $5 - configuration file
outdir=/nfs/dust/cms/user/rasp/Run/log/datacards

jobname=Datacards_${1}_${2}_${3}_${4}_${5}
cat > ${outdir}/${jobname}.bash <<EOF1
#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -
CreateCards $1 $2 $3 $4 $5
EOF1

cat > ${outdir}/${jobname}.submit <<EOF
+RequestRuntime=5000

RequestMemory = 2000

executable = ${outdir}/${jobname}.bash

transfer_executable = True
universe            = vanilla
getenv              = True
Requirements        = OpSysAndVer == "CentOS7"

output              = ${outdir}/${jobname}.out
error               = ${outdir}/${jobname}.error
log                 = ${outdir}/${jobname}.log

queue

EOF
chmod u+x ${outdir}/${jobname}.bash
chmod u+x ${outdir}/${jobname}.submit
condor_submit ${outdir}/${jobname}.submit
