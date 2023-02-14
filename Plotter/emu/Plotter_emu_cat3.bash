#!/bin/bash
# $1 - era
dir=/nfs/dust/cms/user/rasp/Run/emu_dnn_sys_UL
cat > plot_dnn_${1}.conf<<EOF
Era = $1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.501
YMax = 1.499
PlotLegend = true
PlotSignal = true
SignalScale = 20
logY = false
logX = false
BlindData = false
xmin_blind = 0.
xmax_blind = 1000.
ApplyBTagQCDScale = true
AdditionalCut = &&nbtag>0&&nbtag<3&&pred_class==3&&pzeta<20.&&pred_class_proba>0.8
FileSuffix = btag_cat3_prob0p8
ApplySystematics = true
EOF

#PlotEMu_dnn plot_dnn_${1}.conf           pt_1       30     0   150
#PlotEMu_dnn plot_dnn_${1}.conf           pt_2       30     0   150
PlotEMu_dnn plot_dnn_${1}.conf          m_vis       20     0   100
PlotEMu_dnn plot_dnn_${1}.conf         mt_tot       20     0   200
#PlotEMu_dnn plot_dnn_${1}.conf          pt_tt       20     0   200
#PlotEMu_dnn plot_dnn_${1}.conf       puppimet       30     0   300
#PlotEMu_dnn plot_dnn_${1}.conf          bpt_1       30     0   300
#PlotEMu_dnn plot_dnn_${1}.conf          pzeta       27  -250    20
#PlotEMu_dnn plot_dnn_${1}.conf          njets        7  -0.5   6.5

