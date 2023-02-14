#!/bin/bash

cat > em.log <<EOF
Starting --->

EOF

for era in 2018
do 
#    for category in em_cat0_NbtagGe1 em_cat1_NbtagGe1 em_cat2_NbtagGe1 em_cat3_NbtagGe1 em_cat4_NbtagGe1
    for category in em_cat2_NbtagGe1 em_cat3_NbtagGe1
    do 
	PlotDatacards ${era} ${category} em >> em.log
    done
done
