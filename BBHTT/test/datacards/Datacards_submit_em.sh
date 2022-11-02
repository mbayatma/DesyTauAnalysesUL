#!/bin/bash
config=datacards_em.conf 
for era in 2016 2017 2018
do
    for sample in Data DYToTT DYToLL TT ST EWK HTT HWW bbHTT bbHTT_nobb bbHWW bbHWW_nobb
    do
	for category in Nbtag0_Pzeta1 NbtagGe1_Pzeta1 Nbtag0_Pzeta2 NbtagGe1_Pzeta2
	do 
	    echo submitting job for ${sample} ${category} ${era} em ${config} 
	    ./Datacards_submit.sh ${sample} ${category} ${era} em ${config} 
	done
    done 
done
