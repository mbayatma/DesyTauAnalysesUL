#!/bin/sh 
channel=$1
era=$2
label=$3

dir=datacardsEMu_${era}

echo "base directory" $dir

echo "merging file in dir " ${dir}
cd ${dir}
rm htt_${channel}_bbh.root
hadd htt_${channel}_bbh.root *${label}.root
cd -
