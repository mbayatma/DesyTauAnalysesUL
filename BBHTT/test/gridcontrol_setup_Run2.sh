#!/bin/bash

YEAR=20${1}
CHANNEL=$2
if [[ $CHANNEL == "em" ]]; then
    OUTDIR=./$YEAR
else  
    if [[ $CHANNEL == "tt" ]]; then
	OUTDIR=./$YEAR
    else
	if [[ $CHANNEL == "mm" ]]; then
	    OUTDIR=./$YEAR
	else
	    echo "ERROR: please run the script with ./gridcontrol_setup_Run2.sh <year={16_pre,16_post,17,18}> <channel={tt,em,mm}>"
	    exit
	fi
    fi
fi
echo $OUTDIR

if [ ! -d "$OUTDIR" ]; then
  mkdir ${OUTDIR}
fi
cp ./run_${CHANNEL}_synchntuples.sh $OUTDIR/run_synchntuples.sh
cp ./split_filelist.sh $OUTDIR/.
cp ./gc_synch_${CHANNEL}.conf $OUTDIR/gc_synch.conf 
cp ./make_parameter_file.sh $OUTDIR/.
cp ./add_samples.sh $OUTDIR/.


./make_config_Run2.sh $1 MC $CHANNEL
./make_config_Run2.sh $1 data $CHANNEL
./make_lists_${YEAR}.sh $CHANNEL

cd ./$OUTDIR
rm parameters.txt
./make_parameter_file.sh $CHANNEL $YEAR
cd -

echo "-----------------------------------------"
echo "DONT FORGET TO EDIT gc_synch.conf file!!!"
echo "-----------------------------------------"
