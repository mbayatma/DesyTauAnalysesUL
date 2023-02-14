#!/bin/bash
# submits sequence of dnn producers split into systematics 
# please change this directory appropriately
# this is directory where output of condor jobs will be put 
dir=/nfs/dust/cms/user/rasp/Run/jobs
for era in 2018
do
    for sys in Central JESUp JESDown JERUp JERDown UnclEnUp UnclEnDown
    do
	./dnn_producer_TTbar.bash TTbar ${era} em ${sys} ${dir}
    done
done 
