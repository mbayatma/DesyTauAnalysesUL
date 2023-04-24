#!/bin/bash
conf=datacards_em.conf
confCoarse=datacards_em_coarse.conf
for era in 2016 2017 2018
do
    for sample in Data DYToTT DYToLL TT ST EWK TTVJets HTT HWW bbHTT bbHTT_nobb bbHWW bbHWW_nobb
    do
	./Datacards_submit.sh ${sample} cat0_NbtagGe1 ${era} em datacards_em_cat0.conf
	./Datacards_submit.sh ${sample} cat1_NbtagGe1 ${era} em datacards_em_cat1.conf
	./Datacards_submit.sh ${sample} cat2_NbtagGe1 ${era} em datacards_em_cat2.conf
	./Datacards_submit.sh ${sample} cat3_NbtagGe1 ${era} em datacards_em_cat3.conf
	./Datacards_submit.sh ${sample} cat4_NbtagGe1 ${era} em datacards_em_cat4.conf
	./Datacards_submit.sh ${sample} cat5_NbtagGe1 ${era} em datacards_em_cat5.conf
    done 
done
