#!/bin/bash
# Category scheme: 0 - signal, 1 - Higgs bkg, 2 - Fakes, 3 - DY (+Higgs),  4 - TT
outputdir=/nfs/dust/cms/user/rasp/Run/log/datacards/
for era in 2016 2017 2018
do
    for sample in Data EWK DYToTT DYToLL TT ST HTT bbHTT bbHTT_nobb
    do
	./Datacards_submit.sh ${sample} cat0_NbtagGe1 ${era} tt datacards_tt_bbH.conf ${outputdir}
#	./Datacards_submit.sh ${sample} cat1_NbtagGe1 ${era} tt datacards_tt.conf ${outputdir}
	./Datacards_submit.sh ${sample} cat2_NbtagGe1 ${era} tt datacards_tt.conf ${outputdir}
	./Datacards_submit.sh ${sample} cat3_NbtagGe1 ${era} tt datacards_tt_DY.conf ${outputdir}
	./Datacards_submit.sh ${sample} cat4_NbtagGe1 ${era} tt datacards_tt.conf ${outputdir}
    done
done
