#!/bin/bash
config=plot_cards_tt.conf
configDY=plot_cards_tt_DY.conf
configSignal=plot_cards_tt_signal.conf
cat > tt_cards.log <<EOF
Starting --->

EOF

for era in 2016 2017 2018 
do 
    for category in tt_cat2_NbtagGe1 tt_cat4_NbtagGe1
    do 
	PlotDatacards ${era} ${category} tt ${config} >> tt_cards.log
    done
    PlotDatacards ${era} tt_cat3_NbtagGe1 tt ${configDY} >> tt_cards.log
    PlotDatacards ${era} tt_cat0_NbtagGe1 tt ${configSignal} >> tt_cards.log
done
