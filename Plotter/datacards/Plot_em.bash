#!/bin/bash
cat > em_cards.log <<EOF
Starting --->

EOF

for era in 2016 2017 2018
do 
    PlotDatacards ${era} em_cat0_NbtagGe1 em plot_cards_em.conf >> em_cards.log
    PlotDatacards ${era} em_cat1_NbtagGe1 em plot_cards_em.conf >> em_cards.log
    PlotDatacards ${era} em_cat2_NbtagGe1 em plot_cards_em_blind.conf >> em_cards.log
    PlotDatacards ${era} em_cat3_NbtagGe1 em plot_cards_em_blind.conf >> em_cards.log
    PlotDatacards ${era} em_cat4_NbtagGe1 em plot_cards_em.conf >> em_cards.log
done
