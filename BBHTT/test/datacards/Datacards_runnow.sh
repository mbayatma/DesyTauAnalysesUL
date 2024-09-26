#!/bin/bash
#for era in 2016 2017 2018
for era in 2018
do
    for dataset in Data EMB DYJets TTbar EWK ggH qqH ggHbb bbH TTbarToTT EWKToTT bbHybyt
#    for dataset in ggHbb
    do
#	for category in Nbtag0 Nbtag1 Nbtag2 NbtagGe1
	for category in cat0_NbtagGt1 cat1_NbtagGt1 cat2_NbtagGt1 cat3_NbtagGt1
	do 
	    ./NohupParserCards.sh ${era} ${dataset} ${category} 
	done
    done 
done
