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
SignalScale = 1000
logY = false
logX = false
BlindData = false
xmin_blind = 0.
xmax_blind = 1000.
ApplyBTagQCDScale = false
AdditionalCut = &&nbtag>=0
FileSuffix = incl
ApplySystematics = true
EOF

cat > plot_dnn_pzeta_${1}.conf<<EOF
Era = $1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.501
YMax = 1.499
PlotLegend = true
PlotSignal = true
SignalScale = 1000
logY = false
logX = false
BlindData = false
xmin_blind = 0.
xmax_blind = 1000.
ApplyBTagQCDScale = false
AdditionalCut = &&pzeta<20.
FileSuffix = incl
ApplySystematics = true
EOF

cat > plot_dnn_mvis_pzeta_${1}.conf<<EOF
Era = $1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.501
YMax = 1.499
PlotLegend = true
PlotSignal = true
SignalScale = 1000
logY = false
logX = false
BlindData = true
xmin_blind = 0.
xmax_blind = 100.
ApplyBTagQCDScale = false
AdditionalCut = &&pzeta<20.
FileSuffix = incl
ApplySystematics = true
EOF

cat > plot_dnn_mttot_pzeta_${1}.conf<<EOF
Era = $1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.501
YMax = 1.499
PlotLegend = true
PlotSignal = true
SignalScale = 1000
logY = false
logX = false
BlindData = true
xmin_blind = 50.
xmax_blind = 150.
ApplyBTagQCDScale = false
AdditionalCut = &&pzeta<20.
FileSuffix = incl
ApplySystematics = true
EOF

cat > plot_dnn_btag_${1}.conf<<EOF
Era = $1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.501
YMax = 1.499
PlotLegend = true
PlotSignal = true
SignalScale = 1000
logY = false
logX = false
BlindData = false
xmin_blind = 0.
xmax_blind = 1000.
ApplyBTagQCDScale = true
AdditionalCut = &&nbtag>=1&&pzeta<20.
FileSuffix = btag
ApplySystematics = true
EOF

cat > plot_dnn_njetsGe1_${1}.conf<<EOF
Era = $1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.501
YMax = 1.499
PlotLegend = true
PlotSignal = true
SignalScale = 1000
logY = false
logX = false
BlindData = false
xmin_blind = 0.
xmax_blind = 1000.
ApplyBTagQCDScale = true
AdditionalCut = &&njets>=1&&nbtag>=1&&pzeta<20.
FileSuffix = btag
ApplySystematics = true
EOF

cat > plot_dnn_njetsGe2_${1}.conf<<EOF
Era = $1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.501
YMax = 1.499
PlotLegend = true
PlotSignal = true
SignalScale = 1000
logY = false
logX = false
BlindData = false
xmin_blind = 0.
xmax_blind = 1000.
ApplyBTagQCDScale = true
AdditionalCut = &&njets>=2&&nbtag>=1&&pzeta<20.
FileSuffix = btag
ApplySystematics = true
EOF

cat > plot_dnn_mvis_btag_${1}.conf<<EOF
Era = $1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.501
YMax = 1.499
PlotLegend = true
PlotSignal = true
SignalScale = 1000
logY = false
logX = false
BlindData = true
xmin_blind = 0.
xmax_blind = 100.
ApplyBTagQCDScale = true
AdditionalCut = &&nbtag>=1&&pzeta<20.
FileSuffix = btag
ApplySystematics = true
EOF

cat > plot_dnn_mttot_btag_${1}.conf<<EOF
Era = $1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.501
YMax = 1.499
PlotLegend = true
PlotSignal = true
SignalScale = 1000
logY = false
logX = false
BlindData = true
xmin_blind = 50.
xmax_blind = 150.
ApplyBTagQCDScale = true
AdditionalCut = &&nbtag>=1&&pzeta<20.
FileSuffix = btag
ApplySystematics = true
EOF

PlotEMu_dnn plot_dnn_pzeta_${1}.conf           pt_1      30     0   150
PlotEMu_dnn plot_dnn_pzeta_${1}.conf           pt_2      30     0   150
PlotEMu_dnn plot_dnn_pzeta_${1}.conf          m_vis      30     0   300
PlotEMu_dnn plot_dnn_pzeta_${1}.conf         mt_tot      40     0   400
PlotEMu_dnn plot_dnn_pzeta_${1}.conf       puppimet      20     0   200
PlotEMu_dnn plot_dnn_pzeta_${1}.conf          nbtag       5   -0.5  4.5
PlotEMu_dnn plot_dnn_pzeta_${1}.conf          njets       7   -0.5  6.5
PlotEMu_dnn plot_dnn_${1}.conf                pzeta      30   -200  100

PlotEMu_dnn plot_dnn_btag_${1}.conf           pt_1       30     0   150
PlotEMu_dnn plot_dnn_btag_${1}.conf           pt_2       30     0   150
PlotEMu_dnn plot_dnn_mvis_btag_${1}.conf     m_vis       30     0   300
PlotEMu_dnn plot_dnn_mttot_btag_${1}.conf   mt_tot       40     0   400
PlotEMu_dnn plot_dnn_btag_${1}.conf          pt_tt       20     0   200
PlotEMu_dnn plot_dnn_btag_${1}.conf       puppimet       30     0   300
PlotEMu_dnn plot_dnn_btag_${1}.conf          bpt_1       30     0   300
PlotEMu_dnn plot_dnn_btag_${1}.conf          pzeta       27  -250    20
PlotEMu_dnn plot_dnn_btag_${1}.conf          njets        7  -0.5   6.5

PlotEMu_dnn plot_dnn_njetsGe1_${1}.conf jpt_1       30     0   300
PlotEMu_dnn plot_dnn_njetsGe2_${1}.conf jpt_2       30     0   300  
PlotEMu_dnn plot_dnn_njetsGe2_${1}.conf jdeta       24     0   6.0
