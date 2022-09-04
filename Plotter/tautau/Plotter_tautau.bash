#!/bin/bash
config=$1
PlotTauTau $1 pt_1     30    0 150
PlotTauTau $1 pt_2     30    0 150
PlotTauTau $1 eta_1    24 -2.4 2.4
PlotTauTau $1 eta_2    25 -2.5 2.5
PlotTauTau $1 m_vis    25    0 250
PlotTauTau $1 m_sv     30    0 300
PlotTauTau $1 puppimet 30    0 300
PlotTauTau $1 nbtag     5 -0.5 4.5
PlotTauTau $1 njets     8 -0.5 7.5
PlotTauTau $1 mjj      40    0 400
PlotTauTau $1 jdeta    25    0 5.0  
PlotTauTau $1 jpt_1    20    0 200
PlotTauTau $1 jpt_2    20    0 200
PlotTauTau $1 bpt_1    20    0 200
PlotTauTau $1 bpt_2    20    0 200
PlotTauTau $1 bcsv_1   15 0.25 1.0
PlotTauTau $1 bcsv_2   15 0.25 1.0
