#!/bin/bash
config=datacards_tt.conf
for era in 2016 2017 2018
do
    for sample in Data DYToTT DYToLL TT ST EWK HTT bbHTT bbHTT_nobb
    do
	for category in cat0_Nbtag0 cat1_Nbtag0 cat2_Nbtag0 cat3_Nbtag0
	do 
	    echo submitting job ${sample} ${category} ${era} tt ${config}
	    ./Datacards_submit.sh ${sample} ${category} ${era} tt ${config}
	done
    done 
done
