#!/bin/bash
cat > plot_em.cfg <<EOF
Embedded = false
isUL = true
InputDir = /nfs/dust/cms/user/rasp/Run/emu_UL/$1
Era = $1
OutputDir = /nfs/dust/cms/user/rasp/Run/emu_UL/figures/$1
YMin = 0.7
YMax = 1.3
PlotLegend = true
logY = false
logX = false
AdditionalCut = &&pzeta>-35.0
InclusiveDY = true
ApplyBTagQCDScale = false
FileSuffix = incl
ApplySystematics = true
EOF
PlotEMu plot_em.cfg pt_1     30    0 150
PlotEMu plot_em.cfg pt_2     30    0 150
PlotEMu plot_em.cfg m_vis    25    0 250
PlotEMu plot_em.cfg m_sv     30    0 300
#PlotEMu plot_em.cfg puppimet 30    0 300
#PlotEMu plot_em.cfg nbtag     5 -0.5 4.5
#PlotEMu plot_em.cfg njets     8 -0.5 7.5
#PlotEMu plot_em.cfg mjj      40    0 400
#PlotEMu plot_em.cfg jdeta    25    0 5.0  
#PlotEMu plot_em.cfg jpt_1    20    0 200
#PlotEMu plot_em.cfg jpt_2    20    0 200
#PlotEMu plot_em.cfg bpt_1    20    0 200
#PlotEMu plot_em.cfg bpt_2    20    0 200
#PlotEMu plot_em.cfg bcsv_1   15 0.25 1.0
#PlotEMu plot_em.cfg bcsv_2   15 0.25 1.0
