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

* [DesyTauAnalyses/BBHTT/bin/SynchNTupleProducer_em_UL.cpp](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/bin/SynchNTupleProducer_em_UL.cpp)
* [DesyTauAnalyses/BBHTT/bin/SynchNTupleProducer_tt_UL.cpp](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/bin/SynchNTupleProducer_tt_UL.cpp)

Template configuration files to create synchtuples are

* [DesyTauAnalyses/BBHTT/test/analysisMacroSynch_em_template.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/analysisMacroSynch_em_template.conf)
* [DesyTauAnalyses/BBHTT/test/analysisMacroSynch_tt_template.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/analysisMacroSynch_tt_template.conf)


## DNN tuple production

Production of DNN tuples follows the BDT training in tt and em channels. The code requires as inputs synchtuples and BDT prediction tuples with friend trees containing information on predicted classes and BDT scores for each class as well as BDT score for the predicted class (highest BDT score). The source code for this step of the analysis is 

* [DesyTauAnalyses/BBHTT/bin/create_dnn_ntuples.cpp](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/bin/create_dnn_ntuples.cpp)

The code requires three or four input parameters:
```
> create_dnn $sample $era $channel $systematic
```     
where $sample is the name of the sample to be processed, $era={2016_pre,2016_post,2017,2018}, $channel={em,tt}. The fourth parameter ($systematic) is optional and stands for the name of systematic uncertainty (or central tree). When this parameter is specified the code will produce DNN tree only for the systematic uncertainty specified or for central tree. Otherwise the code will create DNN trees for central tree and all systematic variations. Available options for parameter $systematic are:

* Central : nominal tree TauCheck;
* JES{Up,Down} : TauCheck_CMS_scale_j_13TeV{Up,Down} (total JES uncertainty);
* JER{Up,Down} : TauCheck_CMS_res_j_13TeV{Up};
* Uncl{Up,Down} : TauCheck_CMS_scale_met_unclustered_13TeV{Up,Down};
* EScale{Up,Down} : TauCheck_CMS_scale_e_13TeV{Up,Down}.

The names of the samples to be processed are listed in bash scripts that submit jobs to the condor system: 
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_producer_em.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_em.bash)
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_producer_tt.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_tt.bash)

The code loads configuration files depending on the channel specified: 
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_production_em.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_production_em.conf)
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_production_tt.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_production_tt.conf)

In configuration files you have to specify
* the name of the directory where synchtuples are located (parameter ```InputDir```), 
* the name of the directory were the BDT predictions (friend trees) are located (parameter ```FriendDir```),
* and the name of the directory where DNN tuples will be stored (parameter ```OutputDir```)

Make sure that the directory where DNN tuples will be stored, exists (you should create it) and contains subfolders for each era: ```2016_pre```, ```2016_post```, ```2017``` and ```2018```. You should also create one more subfolder ```2016``` where merged DNN tuples of eras ```2016_pre``` and ```2016_post``` will be stored. How to merge tuples of eras ```2016_pre``` and ```2016_post``` is explained later in this instruction.  

The script [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_producer.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer.bash) submits one single job to the condor system for specified sample, channel and era. With this script all trees (central and systematic variations) will be filled and output into single RooT file. 

The script [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_producer_Syst.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_Syst.bash) submits one single job to the condor system for specified sample, channel, era and tree (central tree or systematic variation).

To submit jobs to condor system for multiple eras and samples use the following scripts:
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_producer_em.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_em.bash)
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_producer_tt.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_tt.bash)
  
Change to the directory:
```
cd $CMSSW_BASE/src/DesyTauAnalyses/test/dnn_production
```

Before running DNN tuple production modify the following scripts: 
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_producer_em.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_em.bash) 
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_producer_tt.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_producer_tt.bash).

You have to specify directory where log files of jobs submitted to condor, will be stored 
(parameter ```dir```) as well list of eras and samples you would like to run on. 
By default, scripts will submit jobs for all eras and samples. Aforementioned scripts will submit one job per sample and per era, and the DNN tuples will be saved in the folder specified by parameter ```OutputDir``` of configuration files 
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_production_em.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_production_em.conf)
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_production_tt.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_production_tt.conf)

For extremely large TTbar sample of em channel, jobs are split by sample, era and systematic tree. This is done in order to accelerate production of DNN tuples for this extremely large sample. Once all jobs submitted to condor have finished you have to merge RooT files of TTbar sample in em channel (central tree and different systematic trees). You have to merge also DNN tuples of eras 2016_pre and 2016_post. This is done with the following scripts: 

* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_merge_em.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_merge_em.bash) 
* [DesyTauAnalyses/BBHTT/test/dnn_production/dnn_merge_tt.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/dnn_production/dnn_merge_tt.bash)
  
In these bash scripts you have to specify properly the name of the directory where DNN tuples are stored (parameter ```dir```). 

## Running datacards production

The datacard production is run with the script [DesyTauAnalyses/BBHTT/bin/CreateCards.cpp](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/bin/CreateCards.cpp). This executable uses helper class: 
* [DesyTauAnalyses/BBHTT/src/Cards.cc](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/src/Cards.cc)
* [DesyTauAnalyses/BBHTT/interface/Cards.h](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/interface/Cards.h) 

The script [DesyTauAnalyses/BBHTT/bin/CreateCards.cpp](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/bin/CreateCards.cpp) expects five input parameters:
```
CreateCards $sample $category $era $channel $config
```

where 
* ```$sample``` is the name of sample (group of samples) to be prcessed;
* ```$category``` is the name of the event category, 
* ```$era``` is era (2016, 2017 or 2018); 
* ```$channel``` is channel (em or tt); 
* ```$config``` is the name of config file. 

Available options for parameter ```$sample```:
* Data : data distributions and QCD (Fakes) templates;
* DYToTT : DY templates for genuine Z->tautau decays;
* DYToLL : DY templates for Z->ee/mumu decays;
* EWK : VV and WJets templates;
* TT : TTbar templates;
* ST : single-top templates;
* HTT : standard model H->tautau backgrounds (ggH, VBF, VH and ttH);
* bbHTT : H->tautau signal templates (yt2, yb2, ybyt) (at least one generator b-jet with pT > 10 GeV is required)
* bbHTT_nobb : yt2, yb2, ybyt H->tautau templates without generator b-jets with pT > 10 GeV; 
* HWW : standard model H->WW backgrounds (ggH, VBF, VH, ttH) in em channel;
* TTVJets : ttW/ttZ templates in em channel;
* bbHWW : H->WW signal templates (yt2, yb2, ybyt) in em channel (at least one generator b-jet with pT > 10 GeV is required);
* bbHWW_nobb : yt2, yb2, ybyt H->WW templates without generator b-jets with pT > 10 GeV;

Available options for parameter ```$category```:
* cat0_NbtagGe1 : TTbar (bbH signal) category in em (tt) channel;
* cat1_NbtagGe1 : DY (Higgs bkg) category in em (tt) channel
* cat2_NbtagGe1 : HTT (Fakes) category in em (tt) channel;
* cat3_NbtagGe1 : HWW (DY) category in em (tt) channel;
* cat4_NbtagGe1 : Single-top (TTbar) category in em (tt) channel;
* cat5_NbtagGe1 : merged ST+TTbar (DY+Higgs bkg) category in em (tt) channel;  

Example configuration files (files with extension conf) are found in folder
[DesyTauAnalyses/BBHTT/test/datacards](https://github.com/DesyTau/DesyTauAnalysesUL/tree/bbHTT/BBHTT/test/datacards). Configuration parameters and their meaning are explained below:
* ```InputDir``` - folder where input DNN tuples are located;
* ```OutputDir``` - folder where output datacards will be stored; 
* ```PredictionDir``` - should be always set to ```none```;
* ```Variable``` - variable used for statistical inference, should be always set to ```pred_class_proba```;
* ```Equidistant``` - if true equidistant binning is used, otherwise non-equdistant binning is used for distribution of ```pred_class_proba```;
* ```Nbins``` - number of bins in case of equdistant binning (this parameter is ignored if non-equidistant binning is specified);
* ```Xmin``` - lower boundary in the distribution of ```pred_class_proba``` in case of equdistant binning (this parameter is ignored if non-equidistant binning is specified);
* ```Xmax``` - upper boundary in the distribution of ```pred_class_proba``` in case of equdistant binning (this parameter is ignored if non-equidistant binning is specified);
* ```Bins``` - vector of bin boundaries in case of non-equidistant binning (this parameter is ignored if equidistant binning is specified);
* ```Systematics``` - if true templates with systematic variations are produced (always set to true)
* ```TestCards``` - if true quick test run is performed with detailed output (cuts applied, systematic uncertainties activated, sample weights, etc) (set to false by default)

The following parameters have been introduced to implement smoothing of templates with large statistical fluctuations. Currently, the smoothing procedure is disabled. Don't change settings of these parameters:
* ```MinSmooth = 1```
* ```MaxSmooth = -1```
* ```RangeSmooth = 1```
* ```UseLooseShape = false```
* ```Rebin = false```
 
IMPORTANT! Before running datacards production specify properly parameter ```OutputDir``` which points to the directory where datacards (RooT files with templates) will be stored. Make sure that the directory exists (you have to create it). Inside this directory subfolders have to be created for each era : 2016, 2017, 2018. For a given $era datacards will be saved in the directory ```$OutputDir/$era```. 

Presently the following DNN tuples are available:
* ```/nfs/dust/cms/user/rasp/Run/tautau_dnn_newTauID_UL``` : tt channel, "nominal" training with 5 categories (bbH signal, Higgs background, Fakes, DY, TTbar);
* ```/nfs/dust/cms/user/rasp/Run/emu_dnn_sys_UL``` : em channel, "nominal training" with 4 categories (TTbar, DY, HTT, HWW) using inclusive sample for training (no mass cuts, nbtag<3)
* ```/nfs/dust/cms/user/rasp/Run/emu_dnn_ST_UL``` : em channel, training with 5 categories (TTbar, DY, HTT, HWW, ST4f), cuts applied for training : 10<m_vis<100&&mt_tot<200&&nbtag>0&&nbtag<3; 

The script 
* [DesyTauAnalyses/BBHTT/test/datacards/Datacards_submit.sh](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/Datacards_submit.sh) 

ssubmit one job to condor system for specified sample name, era and event category and channel. 
It takes five input parameters:
```
> Datacards_submit.sh $sample $category $era $channel $config
```

IMPORTANT! Before running datacard production modify in the script [DesyTauAnalyses/BBHTT/test/datacards/Datacards_submit.sh](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/Datacards_submit.sh) parameter ```outdir``` which points to the folder where outputs of condor jobs (log, output and error files) will be saved.

Datacard production on multiple samples, eras and categories is run with the following scripts:
* [DesyTauAnalyses/BBHTT/test/datacards/Datacards_submit_em.sh](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/Datacards_submit_em.sh) - to submit jobs for em channel;
* [DesyTauAnalyses/BBHTT/test/datacards/Datacards_submit_tt.sh](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/Datacards_submit_tt.sh) - to submit jobs for tt channel.

In the current version scripts produce datacards for all eras, samples and categories. However, you can edit these scripts to specify for which eras and categories you would like datacards to be created. 

These scripts make use of configuration files with category dependent non-equidistant binnings: 
* [DesyTauAnalyses/BBHTT/test/datacards/datacards_em_cat0.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/datacards_em_cat0.conf) : to produce datacards for category cat0_NbtagGe1 (TTbar category) of em channel;
* [DesyTauAnalyses/BBHTT/test/datacards/datacards_em_cat1.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/datacards_em_cat1.conf) : to produce datacards for category cat1_NbtagGe1 (DY category) of em channel;
* [DesyTauAnalyses/BBHTT/test/datacards/datacards_em_cat2.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/datacards_em_cat2.conf) : to produce datacards for category cat2_NbtagGe1 (HTT category) of em channel;
* [DesyTauAnalyses/BBHTT/test/datacards/datacards_em_cat3.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/datacards_em_cat3.conf) : to produce datacards for category cat3_NbtagGe1 (HWW category) of em channel;
* [DesyTauAnalyses/BBHTT/test/datacards/datacards_em_cat4.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/datacards_em_cat4.conf) : to produce datacards for category cat4_NbtagGe1 (Single-top category) of em channel;
* [DesyTauAnalyses/BBHTT/test/datacards/datacards_em_cat5.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/datacards_em_cat4.conf) : to produce datacards for category cat5_NbtagGe1 (merged TTbar + single-top category) of em channel;
* [DesyTauAnalyses/BBHTT/test/datacards/datacards_tt.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/datacards_tt.conf) : to produce datacards for categories cat2_NbtagGe1 (Fakes) and cat4_NbtagGe1 (TTbar) of tt channel;
* [DesyTauAnalyses/BBHTT/test/datacards/datacards_tt_DY.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/datacards_tt_DY.conf) : to produce datacards for category cat3_NbtagGe1 (DY) of tt channel;
* [DesyTauAnalyses/BBHTT/test/datacards/datacards_tt_bbH.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/datacards_tt_bbH.conf) : to produce datacards for category cat0_NbtagGe1 (bbH signal) of tt channel;

You can edit these configuration files and define binning of your choice. You can also create your own configuration files and use them in bash scripts: 
* [DesyTauAnalyses/BBHTT/test/datacards/Datacards_submit_em.sh](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/Datacards_submit_em.sh);
* [DesyTauAnalyses/BBHTT/test/datacards/Datacards_submit_tt.sh](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/Datacards_submit_tt.sh).


Once all jobs have finished, you have to merge datacards RooT files with the script 
* [DesyTauAnalyses/BBHTT/test/datacards/Merge_datacards.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/BBHTT/test/datacards/Merge_datacards.bash). 

The script expects two input parameters:
```
> Merge_datacards.bash $channel $datacards_folder
```

where ```$channel``` is the channel and ```$datacards_folder``` is the name of the directory where datacards are saved. The latter is defined via parameter ```OutputDir``` of configuration files.
This script merges datacard RooT files for each era and saves merged RooT files under names ```bbH_$channel_$era.root``` in the folder ```$datacards_folder```. 

## Plotting datacards

Plotting of datacards is done with macro 
* [DesyTauAnalyses/Plotter/bin/PlotDatacards.cpp](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/Plotter/bin/PlotDatacards.cpp) 

It is run with 4 input parameters:
```
> PlotDatacards $era $category $channel $config
```

The example configuration files to create datacards are:
* [DesyTauAnalyses/Plotter/datacards/plot_cards_tt.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/Plotter/datacards/plot_cards_tt.conf) : to plot unblinded distributions in tt channel (recommended for background categories)
* [DesyTauAnalysis/Plotter/datacards/plot_cards_tt_blind.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/Plotter/datacards/plot_cards_tt_blind.conf) : to plot blinded distributions in tt channel (recommended for signal category before unblinding data)
* [DesyTauAnalyses/Plotter/datacards/plot_cards_em.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/Plotter/datacards/plot_cards_em.conf) : to plot unblinded distributions in em channel (recommended for background categories)
* [DesyTauAnalysis/Plotter/datacards/plot_cards_em_blind.conf](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/Plotter/datacards/plot_cards_em_blind.conf) : to plot blinded distributions in em channel (recommended for signal categories before unblinding data)

Parameters specified in config files are: 
* ```InputDir``` - directory with datacards (code assumes that this directory contains datacard RooT files named ```bbH_$channel_$era.root```);
* ```BlindData``` - if true, the plotted distribution is blinded, otherwise unblinded distribution is plotted;
* ```XminBlind``` - lower boundary of the blinded region (parameter is ignored if ```BlindData = false```);
* ```XmaxBlind``` - upper boundary of the blinded region (parameter is ignored if ```BlindData = false```);
* ```ApplySystematics``` - if true systematic error band is shown for normalization uncertainties;
* ```Xtitle``` - title of x-axis;
* ```YMin``` - lower edge of y-axis (if y-axis is set to log scale);
* ```YMax``` - logarithmic factor for y-axis (recommended value 100);
* ```YRatioMin``` - lower edge of the y-axis in the ratio plot;
* ```YRatioMax``` - upper edge of the y-axis in the ratio plot;
* ```PlotDir``` - directory where plots (png files) will be saved;
* ```logY``` - if true, y-axis is set to log scale;
* ```PlotLegend``` - if true, legend is put on the plot;
* ```LegendRight``` - if true, legend is drawn in the upper-right corner of the plot (in the upper-left corner otherwise).


Bash scripts: 

* [DesyTauAnalyses/Plotter/datacards/Plot_em.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/Plotter/datacards/Plot_em.bash)
* [DesyTauAnalyses/Plotter/datacards/Plot_tt.bash](https://github.com/DesyTau/DesyTauAnalysesUL/blob/bbHTT/Plotter/datacards/Plot_tt.bash)

plot datacards sequentially for all eras and categories in em and tt channels, respectively.
Output of these scripts is saved in files ```em_cards.log``` and ```tt_cards.log```

Available datacards:
* ```/nfs/dust/cms/user/rasp/Run/tautau_datacards_newTauID_UL/BDT_coarse``` : tt datacards, "nominal" with 5 categories (bbH signal, Higgs background, Fakes, DY, TTbar). Higgs background category is excluded from statistical inference;
* ```/nfs/dust/cms/user/rasp/Run/emu_datacards_sys_UL/BDT_coarse``` : em datacards, "nominal" training with 4 categories (TTbar, DY, HTT, HWW), no mass cuts, nbtag<3, DY category is excluded from statistical inference;
* ```/nfs/dust/cms/user/rasp/Run/emu_datacards_ST_UL/BDT_coarse``` : em datacards, training with 5 categories (TTbar, DY, HTT, HWW, ST); cuts applied: m_vis<100&&m_vis>10&&mt_tot>200&&nbtag>0&&nbtag<3.
