#!/bin/bash
configDY=datacards_tt_DY.conf
configSignal=datacards_tt_bbH.conf
config=datacards_tt.conf
for era in 2016 2017 2018
do
    for sample in Data EWK DYToTT DYToLL TT ST HTT bbHTT bbHTT_nobb
    do
	for category in cat3_NbtagGe1
	do 
	    echo submitting job ${sample} ${category} ${era} tt ${configDY}
	    ./Datacards_submit.sh ${sample} ${category} ${era} tt ${configDY}
	done
	for category in cat0_NbtagGe1
	do 
	    echo submitting job ${sample} ${category} ${era} tt ${configSignal}
	    ./Datacards_submit.sh ${sample} ${category} ${era} tt ${configSignal}
	done
	for category in cat2_NbtagGe1 cat4_NbtagGe1
	do 
	    echo submitting job ${sample} ${category} ${era} tt ${config}
	    ./Datacards_submit.sh ${sample} ${category} ${era} tt ${config}
	done
    done 
done
