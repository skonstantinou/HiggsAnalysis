#!/usr/bin/env python

from HiggsAnalysis.HeavyChHiggsToTauNu.tools.multicrab import *

multicrab = Multicrab("../crab_analysis.cfg", "muonAnalysis_cfg.py", lumiMaskDir="..")

aodDatasets = [
    # Data
    "Mu_136035-144114_Dec22",
    "Mu_146428-147116_Dec22",
    "Mu_147196-149294_Dec22"
    # Signal MC
    # Background MC
    "QCD_Pt20_MuEnriched_TuneZ2_Winter10",
    "DYJetsToLL_TuneZ2_Winter10",
    "TToBLNu_s-channel_TuneZ2_Winter10",
    "TToBLNu_t-channel_TuneZ2_Winter10",
    "TToBLNu_tW-channel_TuneZ2_Winter10",
    ]
patDatasets = [
    # Signal MC
    "WJets_TuneZ2_Winter10",
    "WJets_TuneD6T_Winter10",
    "TTJets_TuneZ2_Winter10",
    "TTJets_TuneD6T_Winter10",
]

usePatTuples = True
#usePatTuples = False

#aodDatasets = []
#patDatasets = []

if not usePatTuples:
    aodDatasets.extend(patDatasets)
if len(aodDatasets) > 0:
    multicrab.extendDatasets("AOD", aodDatasets)
if usePatTuples and len(patDatasets) > 0:
    multicrab.extendDatasets("pattuple_v9", patDatasets)
multicrab.appendLineAll("GRID.maxtarballsize = 15")
multicrab.appendLineAll("CMSSW.output_file = histograms.root")

decaySeparate = [
#    "WJets_TuneZ2_Winter10",
#    "WJets_TuneD6T_Winter10",
#    "TTJets_TuneZ2_Winter10",
#    "TTJets_TuneD6T_Winter10",
#    "TToBLNu_s-channel_TuneZ2_Winter10",
#    "TToBLNu_t-channel_TuneZ2_Winter10",
#    "TToBLNu_tW-channel_TuneZ2_Winter10",
]
numberOfJobs = {}
#if usePatTuples:
#    numberOfJobs.update({
#            "WJets": 30
#    })
#else:
#    numberOfJobs.update({
#            "TTJets": 40
#    })
    

def modify(dataset):
    if dataset.getName() in aodDatasets:
        dataset.appendArg("doPat=1")
    if dataset.getName() in decaySeparate:
        dataset.addArg("WDecaySeparate=1")

    try:
        njobs = numberOfJobs[dataset.getName()]
        dataset.setNumberOfJobs(njobs)
    except KeyError:
        pass

multicrab.forEachDataset(modify)

#multicrab.modifyLumisPerJobAll(lambda nlumis: nlumis*0.5)
#multicrab.modifyNumberOfJobsAll(lambda njobs: njobs*2)

multicrab.createTasks()
#multicrab.createTasks(configOnly=True)
