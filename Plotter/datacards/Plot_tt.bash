#!/bin/bash

cat > tt.log <<EOF
Starting --->

EOF

for era in 2016 2017 2018
do 
    for category in tt_cat0
    do 
	PlotDatacards ${era} ${category} tt >> tt.log
    done
done
