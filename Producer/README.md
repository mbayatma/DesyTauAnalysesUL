# NTuple Producer

This setup runs on miniAOD ntuples and uses [grid-control](https://github.com/grid-control/grid-control) for job handling.

## Current Campaing

For practical purposes please add here the link to the google doc with the datasets being produced when a new campaign is called:
Oktoberfest2021 campaign: [google doc](https://docs.google.com/spreadsheets/d/1MVDy3fOna8GEaYnzBEowtchffwRxakT-ilgZ25H1eRQ/edit?usp=sharing)


## Setup

Please make sure you first run the setup of the DesyTauAnalyses repository following the instructions in the [main directory](https://github.com/DesyTau/DesyTauAnalysesUL#desytauanalysesul).

To run the NTupleMaker on the batch system we recommend the use of [grid-control](https://github.com/grid-control/grid-control).
Please set up grid-control outside your CMSSW area.
```bash
git clone https://github.com/grid-control/grid-control.git -b testing
```

You will also have to setup [Rucio]() to access the miniAODs and run the NTuple production.
Please add you CERN username in `Producer/test/setupRucio.sh` and then execute it with `source setupRucio.sh`.
NOTE: do NOT set up your CMS environment before running `source setupRucio.sh`, the default python libraries of CMSSW are in conflict with the one used by Rucio.


## Running NTuple Production

The main script you will use is `/path/to/grid-control/go.py`.

First you need to check that the datasets are correctly stored in T2_DE_DESY with Rucio.
NOTE: You need to NOT have set up your CMSSW environment for this or there will be conflicts with the python library used by Rucio.
The script `Producer/test/rucio_transfer.sh` can be used for transfering one dataset at a time, it can be executed with:
```bash
./rucio_transfer.sh <nickname of dataset> </DATASET-NAME/CAMPAIGN/MINIAODSIM(MINIAOD/USER)>
```
The script can easily be edited in order to attach multiple datasets to the same Rucio container and request the transfer of multiple datasets at once:
```bash
#!/bin/bash
NICK=$1
DATASET=$2
#Uncomment the following lines to add multiple datasets to the same container and request only one transfer
#DATASET_2=$3
#DATASET_3=$4

rucio add-container user.${RUCIO_ACCOUNT}:/Analyses/$NICK/USER 
rucio attach user.${RUCIO_ACCOUNT}:/Analyses/$NICK/USER cms:$DATASET
#rucio attach user.${RUCIO_ACCOUNT}:/Analyses/$NICK/USER cms:$DATASET_2
#rucio attach user.${RUCIO_ACCOUNT}:/Analyses/$NICK/USER cms:$DATASET_3
rucio add-rule --ask-approval user.${RUCIO_ACCOUNT}:/Analyses/$NICK/USER 1 T2_DE_DESY --lifetime 2592000 --asynchronous

```
The `attach user` instruction can be executed again for different datasets, in order to attach them to the same container.



Second: create a list of files from cms-das on which grid-control will act.
This can be done using the script `Producer/test/read_filelist_from_das.py`, to run it use (requires python libraries in CMSSW):
```bash
cd $CMSSW_BASE
cmsenv
cd $CMSSW_BASE/src/Producer/test
python read_filelist_from_das.py --nick <nickname of dataset> --query </DATASET-NAME/CAMPAIGN/MINIAODSIM(MINIAOD/USER)> --outputfile <my_list>
```

Then copy the grid-control config files stored in `Producer/test` to the area where you want to run the NTuple production, we recommend to choose an area outside of CMSSW for this purpose.

The config files are named `gc_DATA.cfg` and `gc_MC.cfg`, the areas to be edited before running are:
* `se path`: Path to storage area, simply put the full path to store on nfs or `srm://dcache-se-cms.desy.de:8443/srm/managerv2?SFN=/pnfs/desy.de/cms/tier2/store/user/<username>/<path to storage area>`
* `dbs instance`: (Needed only for embedded and private signal samples) The default location is `prod/global` (most MC/data are here), to switch to phys03 or other production instances uncomment this option and specify the type of instance used for the desired datasets
* `project area`: Input full path to your CMSSW area
* `dataset`: to use a file list provided with Rucio use `<nickname of dataset>: list:<full path to file list>`
* `nickname config`: python config file (`TreeProducer.py`) to be used for production.
* `nickname lumi filter`: Json lumi file turned into txt format, to be used when running on DATA.
* `events per job`: number of events stored in output tree. Recommended values
  * Signal samples: 10000-20000
  * Data/MC: 20000-50000 



Copy the python config file to the area where you plan to run grid-control (again, please choose an area outside CMSSW), and edit the following variables:
* `isData`: enter True for data and leave false for MC (for Embedded it is automatically set to True
* `isEmbedded`: enter True only for Embedded samples, and not for real data
* `year`: actual year of data-taking, a number is expected (2016,2017 or 2018, for now)
* `period`: a string which marks the year and the data-processing iteration (UL2016APV, UL2016, UL2017 or UL2018). NOTE: the current setup does NOT work for ReReco and Legacy2016 campaigns.

Other variables are introduced for dedicated analyses, e.g. `isHiggsSignal` for STXS and `RunTauSpinnerProducer` for Higgs CP.

Suggestions: please rename python and grid-control config files before starting the ntuple production as it helps keeping track of what was used for a specific NTuple campaign.

