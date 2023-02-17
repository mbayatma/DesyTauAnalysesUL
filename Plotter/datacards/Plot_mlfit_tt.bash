#!/bin/bash

cat > tt_mlfit.log <<EOF
Starting --->

EOF

for era in 2016  
do 
    PlotMLFit ${era} bbhtt_tt_1_13TeV tt plot_mlfit_tt_cat1.conf >> tt_mlfit.log
#    PlotMLFit ${era} bbhtt_tt_2_13TeV tt plot_mlfit_tt.conf >> tt_mlfit.log
#    PlotMLFit ${era} bbhtt_tt_3_13TeV tt plot_mlfit_tt_cat3.conf >> tt_mlfit.log
#    PlotMLFit ${era} bbhtt_tt_4_13TeV tt plot_mlfit_tt.conf >> tt_mlfit.log
done
