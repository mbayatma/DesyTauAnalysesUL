#!/bin/bash

cat > em.log <<EOF
Starting --->

EOF

for era in 2018
do 
#    for category in em_Nbtag0_lowPzeta em_Nbtag0_Pzeta1 em_Nbtag0_Pzeta2 em_NbtagGe1_lowPzeta em_NbtagGe1_Pzeta1 em_NbtagGe1_Pzeta2
#    for category in em_Nbtag0_Pzeta1 em_Nbtag0_Pzeta2 em_NbtagGe1_Pzeta1 em_NbtagGe1_Pzeta2
#    for category in em_cat0 em_cat1
    for category in em_cat2 em_cat3 em_cat2_Nbtag0 em_cat2_NbtagGe1 em_cat3_Nbtag0 em_cat3_NbtagGe1 
    do 
	PlotDatacards ${era} ${category} em >> em.log
    done
done
