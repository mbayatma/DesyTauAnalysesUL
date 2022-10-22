#!/bin/bash
# $1 - era (2016_pre, 2016_post, 2017, 2018)
# $2 - sample (MuonEG or Tau, DYJets_amcatnlo, WJets, TTbar, 
#              SingleTop, Diboson, GluGluHToTauTau, VBFHToTauTau,
#              WHToTauTau, ZHToTauTau, TTHToTauTau, BBHToTauTau_YT2, BBHToTauTau_YB2, BBHToTauTau_YBYT
# $3 - channel (em,tt)
# please specify your directory ->
#dir=/nfs/dust/cms/user/makou/jobs or whatever
dir=/nfs/dust/cms/user/rasp/Run/tautau_dnn_UL

jobname=dnntuple_producer_${1}_${2}_${3}
cat > ${dir}/jobs/${jobname}.sh <<EOF1
#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -
create_dnn $1 $2 $3
EOF1

cat > ${dir}/jobs/${jobname}.submit <<EOF
+RequestRuntime=2000

RequestMemory = 2000

executable = ${dir}/jobs/${jobname}.sh

transfer_executable = True
universe            = vanilla
getenv              = True
Requirements        = OpSysAndVer == "CentOS7"

output              = ${dir}/jobs/${jobname}.out
error               = ${dir}/jobs/${jobname}.error
log                 = ${dir}/jobs/${jobname}.log

queue

EOF
chmod u+x ${dir}/jobs/${jobname}.sh
chmod u+x ${dir}/jobs/${jobname}.submit
condor_submit ${dir}/jobs/${jobname}.submit

