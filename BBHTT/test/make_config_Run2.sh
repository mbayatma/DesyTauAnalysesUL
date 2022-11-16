#!/bin/bash

### the script is to be run with "./make_config_Run2.sh <year={16_pre,16_post,17,18}> <type={data, MC, embedded}> <channel={em,tt}> "

YEARS="16_pre 16_post 17 18"
YEAR=$1
DATA_TYPE=$2
CHANNEL=$3

if [[ $YEAR == "16_pre" ]]; then
    NOT_YEAR=(16_post 17 18)
elif [[ $YEAR == "16_post" ]]; then
    NOT_YEAR=(16_pre 17 18)
elif [[ $YEAR == "17" ]]; then
    NOT_YEAR=(16_pre 16_post 18)
elif [[ $YEAR == "18" ]]; then
    NOT_YEAR=(16_pre 16_post 17)
else 
    echo
    echo "To produce the scripts for a specific year and either data or MC this script is to be run with a command:"
    echo
    echo "  ./make_config_Run2.sh <year={16_pre,16_post,17,18}> <data_type={data, MC, embedded}> <channel={em,tt,mm}>"
    echo
    echo "year is not 16_pre,16_post, 17 or 18 - exiting"
    exit
fi

# define parameters which are different between MC and data configs
KEY_LIST=(isData ApplyPUweight ApplyLepSF ApplyBTagScaling ApplyBTagReshape)
VALUE_LIST_MC=(false true true true true)
VALUE_LIST_DATA=(true false false false false)
VALUE_LIST_EMBEDDED=(true false true false false)

if [[ $DATA_TYPE == "data" ]]; then
    VALUE_LIST=("${VALUE_LIST_DATA[@]}")
    NOT_DATA_TYPE=("MC" "embedded")
elif [[ $DATA_TYPE == "MC" ]]; then
    VALUE_LIST=("${VALUE_LIST_MC[@]}")
    NOT_DATA_TYPE=("data" "embedded")
elif [[ $DATA_TYPE == "embedded" ]]; then          
    VALUE_LIST=("${VALUE_LIST_EMBEDDED[@]}")
    NOT_DATA_TYPE=("MC" "data")
else
    echo
    echo "To produce the scripts for a specific year and either data or MC this script is to be run with a command:"
    echo
    echo "  ./make_config_Run2.sh <year={16_pre,16_post,17,18}> <data_type={data, MC, embedded}> <channel={em,tt,mm}>"
    echo
    echo "data_type is neither data nor MC - exiting"
    exit
fi  


if [[ $CHANNEL == "em" ]]; then
    OUTDIR=./20$YEAR
elif [[ $CHANNEL == "tt" ]]; then
    OUTDIR=./20$YEAR
elif [[ $CHANNEL == "mm" ]]; then
    OUTDIR=./20$YEAR
fi


if [ ! -d "$OUTDIR" ]; then
  mkdir $OUTDIR
fi

TEMPLATE_CFG_PREFIX="analysisMacroSynch"
TEMPLATE_CFG_NAME=${TEMPLATE_CFG_PREFIX}_${CHANNEL}_${YEAR}_${DATA_TYPE}
cp ${TEMPLATE_CFG_PREFIX}_${CHANNEL}_template.conf ${TEMPLATE_CFG_NAME}_tmp.conf

# remove all the lines for years which is not the one specified 
NOT_YEAR_LEN=${#NOT_YEAR[@]}
for (( i = 0; i < NOT_YEAR_LEN; i++ )); do
  sed -i "/${NOT_YEAR[i]}: /d" ${TEMPLATE_CFG_NAME}_tmp.conf
done

# remove just the strings "YEAR: " leaving the rest of the line intact 
sed -i "s/${YEAR}: //" ${TEMPLATE_CFG_NAME}_tmp.conf

# these parameters are year dependant for MC, so leave them as they are in the config and set to 0 only if it is data config
# also redefine list of the parameters according to the input data type

# add the parameters to the config
KEY_LEN=${#KEY_LIST[@]}
for (( i = 0; i < $KEY_LEN; i++ )); do
        printf '/%s/c\%s\n' "${KEY_LIST[i]} =*" "${KEY_LIST[i]} = ${VALUE_LIST[i]}"
done | sed -r -i -f- ${TEMPLATE_CFG_NAME}_tmp.conf

# add year
sed -i "s/era = /era = 20$YEAR/" ${TEMPLATE_CFG_NAME}_tmp.conf

# remove all the lines which starts with "NOT_DATA_TYPE: " 
NOT_DATA_TYPE_LEN=${#NOT_DATA_TYPE[@]}
for (( i = 0; i < NOT_DATA_TYPE_LEN; i++ )); do
  sed -i "/${NOT_DATA_TYPE[i]}: /d" ${TEMPLATE_CFG_NAME}_tmp.conf
done

# remove just the strings "DATA_TYPE: " leaving the rest of the line intact 
sed -i "s/${DATA_TYPE}: //" ${TEMPLATE_CFG_NAME}_tmp.conf

if [[ $DATA_TYPE == "MC" ]]; then
    sed "s/pileUpforMC =/pileUpforMC = pileup/" ${TEMPLATE_CFG_NAME}_tmp.conf > $OUTDIR/${TEMPLATE_CFG_NAME}.conf
    # path in the root file to PU histograms for 16 and 18 data; 
else
    cp  ${TEMPLATE_CFG_NAME}_tmp.conf $OUTDIR/${TEMPLATE_CFG_NAME}.conf
fi
rm ${TEMPLATE_CFG_NAME}_tmp.conf

if [[ $DATA_TYPE == "data" ]]; then
    if [[ $CHANNEL == "em" ]]; then
	if [[ $YEAR == "16_post" ]]; then
	    sed "s/ApplyDzFilterMatch = false/ApplyDzFilterMatch = true/" $OUTDIR/${TEMPLATE_CFG_NAME}.conf > $OUTDIR/${TEMPLATE_CFG_NAME}GH.conf
	fi
	if [[ $YEAR = "17" ]]; then
	    sed "s/LowPtLegMuon =  hltMu8TrkIsoVVLEle23CaloIdLTrackIdLIsoVLMuonlegL3IsoFiltered8/LowPtLegMuon =  hltL3fL1sMu7EG23f0Filtered8/" $OUTDIR/${TEMPLATE_CFG_NAME}.conf > $OUTDIR/${TEMPLATE_CFG_NAME}B.conf
	fi
    fi
fi
