#!/bin/bash
era=$1
cat > plotter_tautau_UL.cfg <<EOF
Embedded = false
Era = $1
isUL = true
InputDir = /nfs/dust/cms/user/rasp/Run/tautau_UL/$1
OutputDir = /nfs/dust/cms/user/rasp/Run/tautau_UL/figures/$1
YMin = 0.601
YMax = 1.399
logX = false
logY = false
AdditionalCut = &&os>0.5
PlotLegend = true
InclusiveDY = false
DY_LO = false
DropZPtWeight = false
DropTrigWeight = false
DropIdWeight = false
DropEffWeight = false
ComputeZttNorm = true
FileSuffix = DY_NLO_incl_os
ApplySystematics = true
EOF
cat > plotter_tautau_UL_btg.cfg <<EOF
Embedded = false
Era = $1
isUL = true
InputDir = /nfs/dust/cms/user/rasp/Run/tautau_UL/$1
OutputDir = /nfs/dust/cms/user/rasp/Run/tautau_UL/figures/$1
YMin = 0.501
YMax = 1.499
logX = false
logY = false
AdditionalCut = &&os>0.5&&nbtag>=1
PlotLegend = true
InclusiveDY = false
DY_LO = false
DropZPtWeight = false
DropTrigWeight = false
DropIdWeight = false
DropEffWeight = false
ComputeZttNorm = true
FileSuffix = btag_os
ApplySystematics = true
EOF
PlotTauTau plotter_tautau_UL.cfg pt_1     30    0 150
PlotTauTau plotter_tautau_UL.cfg pt_2     30    0 150
PlotTauTau plotter_tautau_UL.cfg dr_tt    30    0 6
PlotTauTau plotter_tautau_UL.cfg m_vis    25    0 250
PlotTauTau plotter_tautau_UL.cfg mt_tot   30    0 300 
PlotTauTau plotter_tautau_UL.cfg m_sv     30    0 300
PlotTauTau plotter_tautau_UL.cfg puppimet 40    0 200
PlotTauTau plotter_tautau_UL.cfg nbtag     5 -0.5 4.5
PlotTauTau plotter_tautau_UL.cfg njets     8 -0.5 7.5
PlotTauTau plotter_tautau_UL.cfg mjj      40    0 400
PlotTauTau plotter_tautau_UL.cfg jdeta    25    0 5.0  
PlotTauTau plotter_tautau_UL.cfg jpt_1    20    0 200
PlotTauTau plotter_tautau_UL.cfg jpt_2    20    0 200
PlotTauTau plotter_tautau_UL.cfg bpt_1    20    0 200
PlotTauTau plotter_tautau_UL.cfg bpt_2    20    0 200
PlotTauTau plotter_tautau_UL.cfg bcsv_1   16  0.2 1.0
PlotTauTau plotter_tautau_UL.cfg bcsv_2    8  0.2 1.0
PlotTauTau plotter_tautau_UL.cfg mbb      10    0 200
PlotTauTau plotter_tautau_UL.cfg dRbb     12    0 6
# ----------
PlotTauTau plotter_tautau_UL_btg.cfg pt_1     30    0 150
PlotTauTau plotter_tautau_UL_btg.cfg pt_2     30    0 150
PlotTauTau plotter_tautau_UL_btg.cfg m_vis    25    0 250
PlotTauTau plotter_tautau_UL_btg.cfg m_sv     30    0 300
PlotTauTau plotter_tautau_UL_btg.cfg mt_tot   30    0 300
PlotTauTau plotter_tautau_UL_btg.cfg puppimet 30    0 300
PlotTauTau plotter_tautau_UL_btg.cfg dr_tt    30    0 6
PlotTauTau plotter_tautau_UL_btg.cfg pt_tt    30    0 300

