#!/bin/bash

cat > em.log <<EOF
Starting --->

EOF

for era in 2016 2017 2018 
do 
    PlotMLFit ${era} bbhtt_em_1_13TeV em plot_mlfit_em_cat1.conf >> em.log
    PlotMLFit ${era} bbhtt_em_2_13TeV em plot_mlfit_em.conf >> em.log
    PlotMLFit ${era} bbhtt_em_3_13TeV em plot_mlfit_em.conf >> em.log
done
