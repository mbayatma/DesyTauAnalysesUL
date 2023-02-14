#!/bin/bash

cat > tt.log <<EOF
Starting --->

EOF

for era in 2016 2017 2018 
do 
    for category in bbhtt_tt_2_13TeV bbhtt_tt_3_13TeV bbhtt_tt_4_13TeV
    do 
	PlotMLFit ${era} ${category} tt >> tt.log
    done
done
