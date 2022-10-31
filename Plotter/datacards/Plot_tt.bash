#!/bin/bash

cat > em.log <<EOF
Starting --->

EOF

for era in 2016 2017 2018
do 
    for category in em_Nbtag0_lowPzeta em_Nbtag0_Pzeta1 em_Nbtag0_Pzeta2 em_Nbtag0_Pzeta3 em_NbtagGe1_lowPzeta em_NbtagGe1_Pzeta1 em_NbtagGe1_Pzeta2 em_NbtagGe1_Pzeta3
    do 
	PlotDatacards ${era} ${category} em
    done
done
