#!/bin/sh
# $1 - executable
# $2 - filelist


cat > $2.sh <<EOF
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
cd ${CMSSW_BASE}/src
cmsenv
cd -
$1 $2
EOF

chmod u+x $2.sh
./HTC_submit.sh $2.sh $2
