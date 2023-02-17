#!/bin/bash
config=plot_cards_em.conf
configSignal=plot_cards_em_signal.conf
cat > em_cards.log <<EOF
Starting --->

EOF

for era in 2016 2017 2018
do 
    PlotDatacards ${era} em_cat0_NbtagGe1 em ${config} >> em_cards.log
    PlotDatacards ${era} em_cat2_NbtagGe1 em ${configSignal} >> em_cards.log
    PlotDatacards ${era} em_cat3_NbtagGe1 em ${configSignal} >> em_cards.log

done
