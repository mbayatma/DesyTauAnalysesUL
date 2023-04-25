#!/bin/bash
cat > tt_cards.log <<EOF
Starting --->

EOF

for era in 2016 2017 2018 
do 
    PlotDatacards ${era} tt_cat0_NbtagGe1 tt plot_cards_tt_blind.conf >> tt_cards.log
    PlotDatacards ${era} tt_cat2_NbtagGe1 tt plot_cards_tt.conf >> tt_cards.log
    PlotDatacards ${era} tt_cat3_NbtagGe1 tt plot_cards_tt.conf >> tt_cards.log
    PlotDatacards ${era} tt_cat4_NbtagGe1 tt plot_cards_tt.conf >> tt_cards.log
done
