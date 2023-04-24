#!/bin/bash
# submits sequence of dnn producers for em channel 
# the parameter dir (below) sets the name of directory where output of condor jobs will be stored (please change this directory appropriately)
dir=/nfs/dust/cms/user/rasp/Run/log/dnn
for era in 2016_pre 2016_post 2017 2018
do
    for sample in MuonEG DYJets_amcatnlo WJets_amcatnlo SingleTop Diboson TTVJets    GluGluHToTauTau VBFHToTauTau WHToTauTau ZHToTauTau TTHToTauTau   GluGluHToWW VBFHToWW WHToWW ZHToWW TTHToWW   BBHToTauTau_YT2 BBHToTauTau_YB2 BBHToTauTau_YBYT    BBHToWW_YT2 BBHToWW_YBYT BBHToWW_YB2
    do
	./dnn_producer.bash ${sample} ${era} em ${dir}
    done
    ./dnn_producer_Syst.bash TTbar ${era} em Central ${dir}
    #    for sys in JER JES Uncl # <- uncomment for old tuples
    for sys in EScale JER Uncl FlavorQCD RelativeBal HF BBEC1 EC2 Absolute Absolute_Era HF_Era EC2_Era RelativeSample_Era BBEC1_Era 
    do 
	for variation in Up Down
	do 
	    ./dnn_producer_Syst.bash TTbar ${era} em ${sys}${variation} ${dir}
	done
    done
done 
