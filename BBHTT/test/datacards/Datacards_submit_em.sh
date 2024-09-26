#!/bin/bash
# Category scheme: 0 - TTbar, 1 - DY+Jets, 2 - HTT, 3 - HWW
outputdir=/nfs/dust/cms/user/rasp/Run/log/datacards/
#for era in 2016 2017 2018
for era in 2016
do
    for sample in DYToTT DYToLL TT ST EWK TTVJets HTT HWW bbHTT bbHTT_nobb bbHWW bbHWW_nobb
    do
	./Datacards_submit.sh ${sample} cat0_NbtagGe1 ${era} em datacards_em_cat0.conf ${outputdir}
	./Datacards_submit.sh ${sample} cat1_NbtagGe1 ${era} em datacards_em_cat1.conf ${outputdir}
	./Datacards_submit.sh ${sample} cat2_NbtagGe1 ${era} em datacards_em_cat2.conf ${outputdir}
	./Datacards_submit.sh ${sample} cat3_NbtagGe1 ${era} em datacards_em_cat3.conf ${outputdir}
    done 
done
