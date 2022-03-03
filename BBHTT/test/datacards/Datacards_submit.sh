#!/bin/sh 
# $1 - era (2016, 2017, 2018)
# $2 - sample (Data,EMB,DYJets,TTbar,EWK,ggH,qqH,VH,bbH,ggHbb
# $3 - category (Nbtag0, Nbtag1, Nbtag2, NbtagGe1, NbtagGe2)

jobname=Datacards_${1}_${2}_${3}
cat > jobs/${jobname}.sh <<EOF1
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -
CreateCards_emu $1 $2 $3 1
EOF1

cat > jobs/${jobname}.submit <<EOF
+RequestRuntime=5000

RequestMemory = 2000

executable = jobs/${jobname}.sh

transfer_executable = True
universe            = vanilla
getenv              = True
Requirements        = OpSysAndVer == "CentOS7"

output              = jobs/${jobname}.out
error               = jobs/${jobname}.error
log                 = jobs/${jobname}.log

queue

EOF
chmod u+x jobs/${jobname}.sh
chmod u+x jobs/${jobname}.submit
condor_submit jobs/${jobname}.submit
