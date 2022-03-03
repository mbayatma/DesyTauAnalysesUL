#!/bin/sh 
# $1 - era
# $2 - sample 
# $3 - category

cat > jobs/$1_$2_$3.sh <<EOF1
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -
CreateCards_emu $1 $2 $3 0
EOF1

chmod u+x jobs/$1_$2_$3.sh
nohup ./jobs/$1_$2_$3.sh > nohup_$1_$2_$3.out &
