#!/bin/bash
config=datacards_em.conf 
for era in 2016
do
    for sample in Data DYToTT DYToLL TT ST EWK HTT HWW bbHTT bbHTT_nobb bbHWW bbHWW_nobb
    do
	for category in Nbtag0_lowPzeta NbtagGe1_lowPzeta Nbtag0_Pzeta1 NbtagGe1_Pzeta1 Nbtag0_Pzeta2 NbtagGe1_Pzeta2
#	for category in cat0 cat1 cat2 cat3 cat2_Nbtag0 cat3_Nbtag0 cat2_NbtagGe1 cat3_NbtagGe1
	do 
	    echo submitting job for ${sample} ${category} ${era} em ${config} 
	    ./Datacards_submit.sh ${sample} ${category} ${era} em ${config} 
	done
    done 
done
