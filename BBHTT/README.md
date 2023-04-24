# DesyTauAnalysesUL - BBHTT analysis
bbHTT analysis FW for UL campaign

## Install
In order to install framework with required CMSSW dependencies:
```sh
wget https://raw.githubusercontent.com/DesyTau/DesyTauAnalysesUL/bbHTT/BBHTT/setup.sh
source setup.sh
```

## Running synchtuples

Before running synch tuples update the code from git repository. 
```
cd $CMSSW_BASE/src/DesyTauAnalyses
git pull
```

Recompile the code.
```
scramv1 b -j 8
```

IMPORTANT! Update the folder with correction/uncertainty workspaces
```
rm -rf $CMSSW_BASE/src/DesyTauAnalyses/Common/data
cp -r /nfs/dust/cms/user/rasp/CMSSW/Update/CMSSW_10_6_26/src/DesyTauAnalyses/Common/data $CMSSW_BASE/src/DesyTauAnalyses/Common/
```

Set up working directory preferably outside your CMSSW project area
```
mkdir /nfs/dust/cms/user/$username/$working_dir
cd /nfs/dust/cms/user/$username/$working_dir
cp $CMSSW_BASE/src/DesyTauAnalyses/BBHTT/test/* ./
```
Ignore warning messages
```
cp: omitting directory '/nfs/dust/cms/user/rasp/CMSSW/Update/CMSSW_10_6_26/src/DesyTauAnalyses/BBHTT/test/datacards'
cp: omitting directory '/nfs/dust/cms/user/rasp/CMSSW/Update/CMSSW_10_6_26/src/DesyTauAnalyses/BBHTT/test/dnn_production'
```

Set up grid-control to run synchtuple production for a given era
```
./gridcontrol_setup_Run2.sh $era $channel
```
where $era={16_pre,16_post,17,18} and $channel={em,tt}. 
IMPORTANT! Eras should be specified as 16_pre, 16_post, 17 or 18 without preceeding "20".

Don't forget to edit gc_synch.conf file. In particular these parameters need to be adapted accordingly
```
[storage]
; please modify according to your working directory ->
se path = /nfs/dust/cms/user/rasp/Run/emu_sysJES
```
```
[CMSSW]
epilog executable = run_synchntuples.sh
subst files       = run_synchntuples.sh
input files       = analysisMacroSynch*em_*.conf
; please modify acoording to your CMSSW project area ->
project area      = /nfs/dust/cms/user/rasp/CMSSW/Update/CMSSW_10_6_26
```

Run synchntuple production for each era using grid-control tool. 
It is suggested to run grid-control in screen session.
```
screen
cd $CMSSW_BASE/src
source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc7_amd64_gcc700
cmsenv
setenv X509_USER_PROXY /afs/desy.de/user/r/rasp/public/k5-ca-proxy.pem
voms-proxy-init -voms cms:/cms/dcms -valid 96:00
cd /nfs/dust/cms/user/$username/$working_dir/$era
$grid_control_folder/go.py gc_synch.conf -iGc
```

Once all jobs have finished, merge RooT files for each processed sample
```
cd /nfs/dust/cms/user/$username/$working_dir/$era
./add_samples.sh
```

For the current synchtuple production campaign we only reproduce MC samples with
extended model of systematic uncertainties and updated btag reshaping scale factors
and uncertainties. There is no need to reproduce synchtuples 
for data. Moreover, recent glitches of dCache system has caused loss of data.
The big data tuples (MuonEG and Tau) have been affected. Thus at the moment 
it makes no sense to run synchtuple production for data.   

Already existing synchtuples for data should be copied to corresponding folders:
For tt channel:
```
cp /nfs/dust/cms/user/rasp/Run/tautau_sys_UL/$era/Tau*root /nfs/dust/cms/user/$username/$working_dir/$era
```
For em channel:
```
cp /nfs/dust/cms/user/rasp/Run/emu_sys_UL/$era/MuonEG*root /nfs/dust/cms/user/$username/$working_dir/$era
```

### Systematic trees in em channel.

2016:
```
TauCheck_CMS_scale_j_FlavorQCD_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeBal_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_2016_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_2016_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_2016_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeSample_2016_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_2016_13TeV{Up,Down}
TauCheck_CMS_res_j_13TeV{Up,Down}
TauCheck_CMS_scale_e_13TeV{Up,Down}
TauCheck_CMS_scale_met_unclustered_13TeV{Up,Down}
```

2017:
```
TauCheck_CMS_scale_j_FlavorQCD_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeBal_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_2017_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_2017_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_2017_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeSample_2017_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_2017_13TeV{Up,Down}
TauCheck_CMS_res_j_13TeV{Up,Down}
TauCheck_CMS_scale_e_13TeV{Up,Down}
TauCheck_CMS_scale_met_unclustered_13TeV{Up,Down}
```

2018:
```
TauCheck_CMS_scale_j_FlavorQCD_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeBal_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_2018_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_2018_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_2018_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeSample_2018_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_2018_13TeV{Up,Down}
TauCheck_CMS_res_j_13TeV{Up,Down}
TauCheck_CMS_scale_e_13TeV{Up,Down}
TauCheck_CMS_scale_met_unclustered_13TeV{Up,Down}
```

### Systematic trees in tt channel

2016:
```
TauCheck_CMS_scale_j_FlavorQCD_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeBal_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_2016_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_2016_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_2016_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeSample_2016_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_2016_13TeV{Up,Down}
TauCheck_CMS_res_j_13TeV{Up,Down}
TauCheck_CMS_scale_met_unclustered_13TeV{Up,Down}
TauCheck_CMS_scale_t_1prong_13TeV{Up,Down}
TauCheck_CMS_scale_t_1prong1pizero_13TeV{Up,Down}
TauCheck_CMS_scale_t_3prong_13TeV{Up,Down}
TauCheck_CMS_scale_t_3prong1pizero_13TeV{Up,Down}
```

2017:
```
TauCheck_CMS_scale_j_FlavorQCD_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeBal_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_2017_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_2017_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_2017_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeSample_2017_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_2017_13TeV{Up,Down}
TauCheck_CMS_res_j_13TeV{Up,Down}
TauCheck_CMS_scale_met_unclustered_13TeV{Up,Down}
TauCheck_CMS_scale_t_1prong_13TeV{Up,Down}
TauCheck_CMS_scale_t_1prong1pizero_13TeV{Up,Down}
TauCheck_CMS_scale_t_3prong_13TeV{Up,Down}
TauCheck_CMS_scale_t_3prong1pizero_13TeV{Up,Down}
```

2018:
```
TauCheck_CMS_scale_j_FlavorQCD_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeBal_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_13TeV{Up,Down}
TauCheck_CMS_scale_j_Absolute_2018_13TeV{Up,Down}
TauCheck_CMS_scale_j_HF_2018_13TeV{Up,Down}
TauCheck_CMS_scale_j_EC2_2018_13TeV{Up,Down}
TauCheck_CMS_scale_j_RelativeSample_2018_13TeV{Up,Down}
TauCheck_CMS_scale_j_BBEC1_2018_13TeV{Up,Down}
TauCheck_CMS_res_j_13TeV{Up,Down}
TauCheck_CMS_scale_met_unclustered_13TeV{Up,Down}
TauCheck_CMS_scale_t_1prong_13TeV{Up,Down}
TauCheck_CMS_scale_t_1prong1pizero_13TeV{Up,Down}
TauCheck_CMS_scale_t_3prong_13TeV{Up,Down}
TauCheck_CMS_scale_t_3prong1pizero_13TeV{Up,Down}
```

The source codes for synchtuple production are

* [SynchNTupleProducer_em_UL.cpp](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/bin/SynchNTupleProducer_em_UL.cpp)
* [SynchNTupleProducer_tt_UL.cpp](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/bin/SynchNTupleProducer_tt_UL.cpp)

Template configuration files to create synchtuples are

* [analysisMacroSynch_em_template.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/analysisMacroSynch_em_template.conf)
* [analysisMacroSynch_tt_template.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/analysisMacroSynch_tt_template.conf)


## DNN tuple production

Production of DNN tuples follows the BDT training in tt and em channels. The code requires as inputs synchtuples and BDT prediction tuples with friend trees containing information on predicted classes and BDT scores for each class as well as BDT score for the predicted class (highest BDT score). The source code for this step of the analysis is 

* [create_dnn_ntuples.cpp](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/bin/create_dnn_ntuples.cpp)

The code requires three or four input parameters:
```
> create_dnn $sample $era $channel [$systematic]
```     
where $sample is the name of the sample to be processed, $era={2016_pre,2016_post,2017,2018}, $channel={em,tt}. The fourth parameter ($systematic) is optional and stands for the name of systematic uncertainty (or central tree). When this parameter is specified the code will produce DNN tree only for the systematic uncertainty specified or for central tree. Otherwise the code will create DNN trees for central tree and all systematic variations. Available options for parameter $systematic are:

* Central : nominal tree TauCheck
* JES{Up,Down} : TauCheck_CMS_scale_j_13TeV{Up,Down}
* JER{Up,Down} : TauCheck_CMS_res_j_13TeV{Up}
* Uncl{Up,Down} : TauCheck_CMS_scale_met_unclustered_13TeV{Up,Down}
* EScale{Up,Down} : TauCheck_

More options will be added for the extended uncertainty model which implements splitting .

The names of the samples to be processed are listed in bash scripts that submit jobs to the condor system: 
* [dnn_producer_em.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_em.bash)
* [dnn_producer_tt.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_tt.bash)

The code loads configuration files depending on the channel specified: 
* [dnn_production_em.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_production_em.conf)
* [dnn_production_tt.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_production_tt.conf)

In configuration files you have to specify
* the name of the directory where synchtuples are located (parameter ```InputDir```), 
* the name of the directory were the BDT predictions (friend trees) are located (parameter ```FriendDir```),
* and the name of the directory where DNN tuples will be stored (parameter ```OutputDir```)

Make sure that the directory where DNN tuples will be stored, exists (you should create it) and contains subfolders for each era: ```2016_pre```, ```2016_post```, ```2017``` and ```2018```. You should also create one more subfolder ```2016``` where merged DNN tuples of eras ```2016_pre``` and ```2016_post``` will be stored. How to merge tuples of eras ```2016_pre``` and ```2016_post``` is explained later in this instruction.  

The script [dnn_producer.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer.bash) submits one single job to the condor system for specified sample, channel and era. With this script all trees (central and systematic variations) will be filled and output into single RooT file. 

The script [dnn_producer_Syst.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_Syst.bash) submits one single job to the condor system for specified sample, channel, era and tree (central tree or systematic variation).

To submit jobs to condor system for multiple eras and samples use the following scripts:
* [dnn_producer_em.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_em.bash)
* [dnn_producer_tt.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_tt.bash)
  
Change to the directory:
```
cd $CMSSW_BASE/src/DesyTauAnalyses/test/dnn_production
```

Before running DNN tuple production modify the following scripts: 
* [dnn_producer_em.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_em.bash) 
* [dnn_producer_tt.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_tt.bash).

You have to specify directory where log files of jobs submitted to condor, will be stored 
(parameter ```dir```) as well list of eras and samples you would like to run on. 
By default, scripts will submit jobs for all eras and samples. Aforementioned scripts will submit one job per sample and per era, and the DNN tuples will be saved in the folder specified by parameter ```OutputDir``` of configuration files 
* [dnn_production_em.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_production_em.conf)
* [dnn_production_tt.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_production_tt.conf)

For extremely large TTbar sample of em channel, jobs are split by sample, era and systematic tree. This is done in order to accelerate production of DNN tuples for this extremely large sample. Once all jobs submitted to condor have finished you have to merge RooT files of TTbar sample in em channel (central tree and different systematic trees). You have to merge also DNN tuples of eras 2016_pre and 2016_post. This is done with the following scripts: 

* [dnn_merge_em.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_merge_em.bash) 
* [dnn_merge_tt.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_merge_tt.bash)
  
In these bash scripts you have to specify properly the name of the directory where DNN tuples are stored (parameter ```dir```). 

  