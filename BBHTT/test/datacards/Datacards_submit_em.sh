#!/bin/bash
config=datacards_em.conf 
for era in 2016 2017 2018
do
    for sample in Data DYToTT DYToLL TT ST EWK TTVJets HTT HWW bbHTT bbHTT_nobb bbHWW bbHWW_nobb
    do
	for category in cat3_NbtagGe1
#	for category in cat0 cat1 cat0_NbtagGe1 cat1_NbtagGe1 cat2_NbtagGe1 cat3_NbtagGe1
	do 
	    echo submitting job for ${sample} ${category} ${era} em ${config} 
	    ./Datacards_submit.sh ${sample} ${category} ${era} em ${config} 
	done
    done 
done
