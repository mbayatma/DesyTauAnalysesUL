#!/bin/bash
era=$1
cat > plotter_tautau.cfg <<EOF
Era = $1
InputDir = /nfs/dust/cms/user/rasp/Run/tautau_dnn_UL/$1
OutputDir = /nfs/dust/cms/user/rasp/Run/tautau_dnn_UL/figures/$1
YMin = 0.601
YMax = 1.399
logX = false
logY = false
AdditionalCut = &&os>0.5
PlotLegend = true
FileSuffix = incl_os
ApplySystematics = true
EOF
cat > plotter_tautau_btg.cfg <<EOF
Embedded = false
Era = $1
isUL = true
InputDir = /nfs/dust/cms/user/rasp/Run/tautau_dnn_UL/$1
OutputDir = /nfs/dust/cms/user/rasp/Run/tautau_dnn_UL/figures/$1
YMin = 0.301
YMax = 1.699
logX = false
logY = false
AdditionalCut = &&os>0.5&&nbtag>=1
PlotLegend = true
FileSuffix = btag_os
ApplySystematics = true
EOF
PlotTauTau_dnn plotter_tautau.cfg pt_1     30    0 150
PlotTauTau_dnn plotter_tautau.cfg pt_2     30    0 150
PlotTauTau_dnn plotter_tautau.cfg dr_tt    30    0 6
PlotTauTau_dnn plotter_tautau.cfg m_vis    25    0 250
PlotTauTau_dnn plotter_tautau.cfg mt_tot   30    0 300 
PlotTauTau_dnn plotter_tautau.cfg m_sv     30    0 300
PlotTauTau_dnn plotter_tautau.cfg puppimet 40    0 200
PlotTauTau_dnn plotter_tautau.cfg nbtag     5 -0.5 4.5
PlotTauTau_dnn plotter_tautau.cfg njets     8 -0.5 7.5
PlotTauTau_dnn plotter_tautau.cfg mjj      40    0 400
PlotTauTau_dnn plotter_tautau.cfg jdeta    25    0 5.0  
PlotTauTau_dnn plotter_tautau.cfg jpt_1    20    0 200
PlotTauTau_dnn plotter_tautau.cfg jpt_2    20    0 200
PlotTauTau_dnn plotter_tautau.cfg bpt_1    10    0 200
PlotTauTau_dnn plotter_tautau.cfg bpt_2    10    0 200
PlotTauTau_dnn plotter_tautau.cfg bcsv_1   15 0.25 1.0
PlotTauTau_dnn plotter_tautau.cfg bcsv_2   15 0.25 1.0
PlotTauTau_dnn plotter_tautau.cfg mbb      20    0 200
PlotTauTau_dnn plotter_tautau.cfg dRbb     30    0 6
PlotTauTau_dnn plotter_tautau.cfg pt_tt    30    0 300
# ----------
PlotTauTau_dnn plotter_tautau_btg.cfg pt_1     30    0 150
PlotTauTau_dnn plotter_tautau_btg.cfg pt_2     30    0 150
PlotTauTau_dnn plotter_tautau_btg.cfg m_vis    25    0 250
PlotTauTau_dnn plotter_tautau_btg.cfg m_sv     30    0 300
PlotTauTau_dnn plotter_tautau_btg.cfg mt_tot   30    0 300
PlotTauTau_dnn plotter_tautau_btg.cfg puppimet 30    0 300
PlotTauTau_dnn plotter_tautau_btg.cfg dr_tt    30    0 6
PlotTauTau_dnn plotter_tautau_btg.cfg pt_tt    30    0 300
