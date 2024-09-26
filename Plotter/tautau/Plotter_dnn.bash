#!/bin/bash
era=$1
dir=/nfs/dust/cms/user/rasp/Run/tautau_dnn_sys_UL
cat > plotter_tautau_${1}.cfg <<EOF
Era = $1
BlindData = false
xmin_blind = 0
xmax_blind = 1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.401
YMax = 1.599
logX = false
logY = false
AdditionalCut = &&os>0.5&&m_sv>20.&&m_vis>20.
PlotSignal = false
PlotLegend = true
FileSuffix = incl_os
SignalScale = 1000
ApplySystematics = true
EOF

cat > plotter_tautau_btag_${1}.cfg <<EOF
Era = $1
BlindData = false
xmin_blind = 0
xmax_blind = 1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.401
YMax = 1.599
logX = false
logY = false
AdditionalCut = &&os>0.5&&m_sv>20.&&m_vis>20.&&nbtag>=1
PlotSignal = false
PlotLegend = true
FileSuffix = btag_os
SignalScale = 1000
ApplySystematics = true
EOF

cat > plotter_tautau_njets1_${1}.cfg <<EOF
Era = $1
BlindData = false
xmin_blind = 0
xmax_blind = 1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.401
YMax = 1.599
logX = false
logY = false
AdditionalCut = &&os>0.5&&m_sv>20.&&m_vis>20.&&nbtag>=1&&njets>=1
PlotSignal = false
PlotLegend = true
FileSuffix = btag_os
SignalScale = 1000
ApplySystematics = true
EOF

cat > plotter_tautau_njets2_${1}.cfg <<EOF
Era = $1
BlindData = false
xmin_blind = 0
xmax_blind = 1
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.401
YMax = 1.599
logX = false
logY = false
AdditionalCut = &&os>0.5&&m_sv>20.&&m_vis>20.&&nbtag>=1&&njets>=2
PlotSignal = false
PlotLegend = true
FileSuffix = btag_os
SignalScale = 1000
ApplySystematics = true
EOF

cat > plotter_tautau_msv_${1}.cfg <<EOF
Era = $1
BlindData = true
xmin_blind = 100
xmax_blind = 150
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.401
YMax = 1.599
logX = false
logY = false
AdditionalCut = &&os>0.5&&m_sv>20.&&m_vis>20.&&nbtag>=1
PlotSignal = false
PlotLegend = true
FileSuffix = btag_os
SignalScale = 1000
ApplySystematics = true
EOF

cat > plotter_tautau_mvis_${1}.cfg <<EOF
Era = $1
BlindData = true
xmin_blind = 70
xmax_blind = 130
InputDir = ${dir}/$1
OutputDir = ${dir}/figures
YMin = 0.401
YMax = 1.599
logX = false
logY = false
AdditionalCut = &&os>0.5&&m_sv>20.&&m_vis>20.&&nbtag>=1
PlotSignal = false
PlotLegend = true
FileSuffix = btag_os
SignalScale = 1000
ApplySystematics = true
EOF

#PlotTauTau_dnn plotter_tautau_${1}.cfg pt_1     40    0 200
#PlotTauTau_dnn plotter_tautau_${1}.cfg pt_2     40    0 200
PlotTauTau_dnn plotter_tautau_${1}.cfg m_sv     30    0 300
PlotTauTau_dnn plotter_tautau_${1}.cfg m_vis    30    0 300
#PlotTauTau_dnn plotter_tautau_${1}.cfg puppimet 20    0 200
#PlotTauTau_dnn plotter_tautau_${1}.cfg pt_tt    30    0 300
#PlotTauTau_dnn plotter_tautau_${1}.cfg njets     6 -0.5 5.5
#PlotTauTau_dnn plotter_tautau_${1}.cfg nbtag     5 -0.5 4.5

PlotTauTau_dnn plotter_tautau_btag_${1}.cfg m_sv      30  0  300
PlotTauTau_dnn plotter_tautau_btag_${1}.cfg m_vis     30  0  300

#PlotTauTau_dnn plotter_tautau_btag_${1}.cfg pt_1      40  0  200
#PlotTauTau_dnn plotter_tautau_btag_${1}.cfg pt_2      40  0  200
#PlotTauTau_dnn plotter_tautau_msv_${1}.cfg  m_sv      30  0  300
#PlotTauTau_dnn plotter_tautau_mvis_${1}.cfg m_vis     25  0  250
#PlotTauTau_dnn plotter_tautau_btag_${1}.cfg puppimet  20  0  200
#PlotTauTau_dnn plotter_tautau_btag_${1}.cfg pt_tt     30  0  300
#PlotTauTau_dnn plotter_tautau_njets1_${1}.cfg jpt_1   20  0  200
#PlotTauTau_dnn plotter_tautau_njets2_${1}.cfg jpt_2   20  0  200
#PlotTauTau_dnn plotter_tautau_njets2_${1}.cfg mjj     20  0  500
#PlotTauTau_dnn plotter_tautau_njets2_${1}.cfg jdeta   12  0  6.0


