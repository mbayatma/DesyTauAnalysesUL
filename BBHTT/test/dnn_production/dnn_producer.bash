#!/bin/bash
# $1 - era (2016_pre, 2016_post, 2017, 2018)
# $2 - sample (MuonEG or Tau, DYJets_amcatnlo, WJets, TTbar, 
#              SingleTop, Diboson, GluGluHToTauTau, VBFHToTauTau,
#              WHToTauTau, ZHToTauTau, TTHToTauTau, BBHToTauTau_YT2, BBHToTauTau_YB2, BBHToTauTau_YBYT
#              em only : GluGluHToWW, VBFHToWW, WHToWW, ZHToWW, BBHToWW_YB2, BBHToWW_YBYT
# $3 - channel (em,tt)
# $4 - directory where output of condor jobs are stored 
#      : example /nfs/dust/cms/user/rasp/jobs 
#        PLEASE SPECIFY YOUR OWN DIRECTORY ->
dir=${4}

jobname=dnntuple_producer_${1}_${2}_${3}
cat > ${dir}/${jobname}.sh <<EOF1
#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -
create_dnn $1 $2 $3
EOF1

cat > ${dir}/${jobname}.submit <<EOF
+RequestRuntime=4000

RequestMemory = 4000

executable = ${dir}/${jobname}.sh

transfer_executable = True
universe            = vanilla
getenv              = True
Requirements        = OpSysAndVer == "CentOS7"

output              = ${dir}/${jobname}.out
error               = ${dir}/${jobname}.error
log                 = ${dir}/${jobname}.log

queue

EOF
chmod u+x ${dir}/${jobname}.sh
chmod u+x ${dir}/${jobname}.submit
condor_submit ${dir}/${jobname}.submit

