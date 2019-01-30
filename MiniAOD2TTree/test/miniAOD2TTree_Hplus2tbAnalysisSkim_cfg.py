'''
For miniAOD instructions see: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2015 
'''
#================================================================================================  
# Import Modules
#================================================================================================  
import FWCore.ParameterSet.Config as cms
import HiggsAnalysis.MiniAOD2TTree.tools.git as git
from HiggsAnalysis.MiniAOD2TTree.tools.HChOptions import getOptionsDataVersion


#================================================================================================  
# Options
#================================================================================================  
maxEvents    = 500
maxWarnings  = 100
reportEvery  = 100
testWithData = False
if testWithData:
    dataVersion  = "94Xdata"
    datasetFiles = [
        "/store/data/Run2017D/JetHT/MINIAOD/31Mar2018-v1/90000/DA9E7A45-4439-E811-AAA9-0025905A60B2.root",
        "/store/data/Run2017D/JetHT/MINIAOD/31Mar2018-v1/90000/D62DA569-5139-E811-84D7-0CC47A7452D0.root",
        "/store/data/Run2017D/JetHT/MINIAOD/31Mar2018-v1/90000/D064F63B-3939-E811-A73C-0CC47A4C8E96.root",
        ]
else:
    dataVersion  = "94Xmc" 
    datasetFiles = [
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/FE3E8889-9342-E811-898F-008CFAF724BE.root',
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/F819F9EE-5142-E811-BC28-7845C4FC3C7D.root',
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/F4DCCD39-A542-E811-9E16-008CFAF225DC.root',
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/F4C04DD1-9042-E811-A933-008CFAF747AA.root',
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/F445F408-C442-E811-88B5-7CD30AD0A15C.root',
        ]
    
# For debugging purposes
debug       = False
RunNum_1    = 1
LumiBlock_1 = 2
EvtNum_1    = 240
RunNum_2    = 1
LumiBlock_2 = 2
EvtNum_2    = 260


#================================================================================================  
# Setup the Process
#================================================================================================  
process = cms.Process("TTreeDump")
process.options = cms.untracked.PSet(
    #SkipEvent         = cms.untracked.vstring('ProductNotFound'),
    wantSummary       = cms.untracked.bool(debug),
    printDependencies = cms.untracked.bool(debug),
)
process.maxEvents = cms.untracked.PSet(
    input         = cms.untracked.int32(maxEvents)
    )


#================================================================================================  
# Tracer service is for debugging purposes (Tells user what cmsRun is accessing)
#================================================================================================  
if debug:
    process.Tracer = cms.Service("Tracer")


#================================================================================================  
# Setup the Process
#================================================================================================  
process.load("FWCore/MessageService/MessageLogger_cfi")
process.MessageLogger.categories.append("TriggerBitCounter")
process.MessageLogger.cerr.FwkReport.reportEvery = reportEvery # print the event number for every 100th event
process.MessageLogger.cerr.TriggerBitCounter = cms.untracked.PSet(limit = cms.untracked.int32(maxWarnings)) # print max 100 warnings

#================================================================================================  
# Set the process options -- Display summary at the end, enable unscheduled execution
#================================================================================================  
process.options = cms.untracked.PSet(
    allowUnscheduled = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
    )

#================================================================================================  
# Define the input files 
#================================================================================================  
process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring('/store/data/Run2016B/JetHT/MINIAOD/PromptReco-v2/000/273/150/00000/66051AAF-D819-E611-BD3D-02163E011D55.root',)
                            fileNames = cms.untracked.vstring(datasetFiles)
                            #eventsToProcess = cms.untracked.VEventRange('%s:%s:%s-%s:%s:%s' % (RunNum_1, LumiBlock_1, EvtNum_1, RunNum_2, LumiBlock_2, EvtNum_2) ), 
                            )


#================================================================================================  
# Get Dataset version and Global tag
#================================================================================================  
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
options, dataVersion = getOptionsDataVersion(dataVersion)
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, str(dataVersion.getGlobalTag()), '')


#================================================================================================  
# Print Settings
#================================================================================================  
msgAlign = "{:<10} {:<55} {:<25} {:<25}"
title    =  msgAlign.format("Data", "Global Tag", "Trigger Source", "Trigger Tag")
print "="*len(title)
print title
print "="*len(title)
print msgAlign.format(dataVersion.version, dataVersion.getGlobalTag(), dataVersion.getMETFilteringProcess(), dataVersion.getTriggerProcess())
print 


#================================================================================================
# Load processes
#================================================================================================
process.load("HiggsAnalysis/MiniAOD2TTree/PUInfo_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/TopPt_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Tau_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Electron_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Muon_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Jet_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/FatJet_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/SecondaryVertex_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Top_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/MET_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/METNoiseFilter_cfi")

process.METNoiseFilter.triggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getMETFilteringProcess())) 
print "check tau", process.Taus_TauPOGRecommendation[0]#.src.moduleLabel

process.dump = cms.EDFilter('MiniAOD2TTreeFilter',
    OutputFileName      = cms.string("miniaod2tree.root"),
    PUInfoInputFileName = process.PUInfo.OutputFileName,
    TopPtInputFileName  = process.TopPtProducer.OutputFileName,
    CodeVersion         = cms.string(git.getCommitId()),
    DataVersion         = cms.string(str(dataVersion.version)),
    CMEnergy            = cms.int32(13),
    Skim = cms.PSet(
	Counters = cms.VInputTag(
            cms.InputTag("skimCounterAll","Counter"),
            cms.InputTag("skimCounterPassed","Counter")
        ),
    ),
    EventInfo = cms.PSet(
        PileupSummaryInfoSrc        = process.PUInfo.PileupSummaryInfoSrc, 
	LHESrc                      = cms.untracked.InputTag("externalLHEProducer"),
	OfflinePrimaryVertexSrc     = cms.InputTag("offlineSlimmedPrimaryVertices"),
	TopPtProducer               = cms.InputTag("TopPtProducer"),
    ),
    Trigger = cms.PSet(
	TriggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getTriggerProcess())),
	TriggerBits    = cms.vstring(
            # Triggers in 2017: https://fwyzard.web.cern.ch/fwyzard/hlt/2017/summary.html            
            # Triggers in 2018: https://ndaci.web.cern.ch/ndaci/hlt/2018/summary
            "HLT_PFHT300PT30_QuadPFJet_75_60_45_40_v",
            "HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0_v",
            "HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_v",
            "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_v",
            "HLT_PFHT380_SixPFJet32_v",
            "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_v",
            "HLT_PFHT430_SixPFJet40_v",
            "HLT_PFHT350_v",
            "HLT_HT300PT30_QuadJet_75_60_45_40_v",
            "HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07_v",
            "HLT_PFHT380_SixJet32_DoubleBTagCSV_p075_v",
            "HLT_PFHT430_SixJet40_BTagCSV_p080_v",
            "HLT_PFJet320_v",
            "HLT_PFJet400_v",
            "HLT_PFJet450_v",
            "HLT_PFJet500_v",
            "HLT_PFJet550_v",
            "HLT_PFHT250_v",
            "HLT_PFHT370_v",
            "HLT_PFHT430_v",
            "HLT_PFHT510_v",
            "HLT_PFHT590_v",
            "HLT_PFHT680_v",
            "HLT_PFHT780_v",
            "HLT_PFHT890_v",
            "HLT_PFHT1050_v",
            "HLT_PFHT380_SixJet32_v",
            "HLT_PFHT430_SixJet40_v",
            "HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1_v",
            "HLT_QuadPFJet103_88_75_15_v",
            "HLT_QuadPFJet105_88_76_15_v",
            "HLT_QuadPFJet111_90_80_15_v",
            # AK8 Paths
            "HLT_AK8PFHT750_TrimMass50_v",
            "HLT_AK8PFHT800_TrimMass50_v",
            "HLT_AK8PFHT850_TrimMass50_v",
            "HLT_AK8PFHT900_TrimMass50_v",
            "HLT_AK8PFJet330_PFAK8BTagCSV_p1_v",
            "HLT_AK8PFJet330_PFAK8BTagCSV_p17_v",
            "HLT_AK8PFJet360_TrimMass30_v",
            "HLT_AK8PFJet380_TrimMass30_v",
            "HLT_AK8PFJet400_v",
            "HLT_AK8PFJet400_TrimMass30_v",
            "HLT_AK8PFJet420_TrimMass30_v",
            "HLT_AK8PFJet450_v",
            "HLT_AK8PFJet500_v",
            "HLT_AK8PFJet550_v",
            "HLT_DoublePFJets100_CaloBTagCSV_p33_v",
            "HLT_DoublePFJets200_CaloBTagCSV_p33_v",
            "HLT_DoublePFJets350_CaloBTagCSV_p33_v",
            "HLT_DoublePFJets40_CaloBTagCSV_p33_v",
            ),
	L1Extra        = cms.InputTag("l1extraParticles:MET"),
	TriggerObjects = cms.InputTag("selectedPatTrigger"),
        TriggerMatch   = cms.untracked.vstring(
            ),
	filter = cms.untracked.bool(False)
    ),
    METNoiseFilter = process.METNoiseFilter,
    Taus      = process.Taus_TauPOGRecommendation,
    Electrons = process.Electrons,
    Muons     = process.Muons,
    Jets      = process.Jets,
    FatJets   = process.FatJets,
    #SoftBTag  = process.SoftBTag,
    Top       = process.Top,
    METs      = process.METs,
    GenWeights = cms.VPSet(
        cms.PSet(
            branchname = cms.untracked.string("GenWeights"),
            src        = cms.InputTag("generator"),
            filter     = cms.untracked.bool(False)
        )
    ),
    GenMETs = cms.VPSet(
        cms.PSet(
            branchname = cms.untracked.string("GenMET"),
            src        = cms.InputTag("genMetTrue"),
            filter     = cms.untracked.bool(False)
        )
    ),
    GenJets = cms.VPSet(      
        cms.PSet(
            branchname = cms.untracked.string("GenJets"),
            src        = cms.InputTag("slimmedGenJets"), # ak4
        )
    ),
    GenParticles = cms.VPSet(      
        cms.PSet(
            branchname          = cms.untracked.string("genParticles"),
            src                 = cms.InputTag("prunedGenParticles"),
            saveAllGenParticles = cms.untracked.bool(True),
            saveGenBooleans     = cms.untracked.bool(True),
            saveGenStatusFlags  = cms.untracked.bool(True),
            saveGenElectrons    = cms.untracked.bool(False),
            saveGenMuons        = cms.untracked.bool(False),
            saveGenTaus         = cms.untracked.bool(False),
            saveGenNeutrinos    = cms.untracked.bool(False),
            saveTopInfo         = cms.untracked.bool(False),
            saveWInfo           = cms.untracked.bool(False),
            saveHplusInfo       = cms.untracked.bool(False),
        )
    ),

)

#================================================================================================ 
# Setup skim counters
#================================================================================================ 
process.load("HiggsAnalysis.MiniAOD2TTree.Hplus2tbAnalysisSkim_cfi")
process.skimCounterAll        = cms.EDProducer("HplusEventCountProducer")
process.skimCounterPassed     = cms.EDProducer("HplusEventCountProducer")
process.skim.TriggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getTriggerProcess()))

#================================================================================================ 
# Setup customizations
#================================================================================================ 
from HiggsAnalysis.MiniAOD2TTree.CommonFragments import produceCustomisations
produceCustomisations(process, dataVersion.isData()) # This produces process.CustomisationsSequence which needs to be included to path

from HiggsAnalysis.MiniAOD2TTree.CommonFragments import produceAK8Customisations
produceAK8Customisations(process, dataVersion.isData())   # This produces process.AK8CustomisationsSequence which needs to be included to path


#===== EGamma IDs
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")

setupEgammaPostRecoSeq(process,
                       runVID=True,
                       era='2017-Nov17ReReco')

switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_id_modules = [
    'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V1_cff',
    'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V1_cff',
    'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff',
    'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
    'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V1_cff',
    'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
    ]

for idmod in my_id_modules:
    setupAllVIDIdsInModule(process, idmod, setupVIDElectronSelection)


#===== Setup tau ID
print "\n=== Rerunning Tau MVA ID (2017v2) \n" 
from HiggsAnalysis.MiniAOD2TTree.runTauIdMVA import *
na = TauIDEmbedder(process, cms, # pass tour process object
    debug=True,
    toKeep = ["newDM2017v2", "2017v2", "dR0p32017v2"] # pick the one you need: ["2017v1", "2017v2", "newDM2017v2", "dR0p32017v2", "2016v1", "newDM2016v1"]
)
na.runTauID()



#================================================================================================ 
# Module execution
#================================================================================================ 
process.runEDFilter = cms.Path(process.PUInfo*
                               process.TopPtProducer*
                               
                               # Produce Tau MVA ID prior skimming
                               process.rerunMvaIsolationSequence*
                               process.NewTauIDsEmbedded*
                               
                               # Produce Electron IDs prior skimming
                               #process.egammaPostRecoSeq*
                               #process.electronMVAVariableHelper*
                               #process.electronMVAValueMapProducer*
                               #process.egmGsfElectronIDSequence*
                               
                               # Apply the skimming
                               process.skimCounterAll*
                               process.skim*
                               process.skimCounterPassed*
                               
                               
                               process.CustomisationsSequence*
                               process.AK8CustomisationsSequence*
                               process.dump)


#process.output = cms.OutputModule("PoolOutputModule",
#   outputCommands = cms.untracked.vstring(
#       "keep *_*AK8*_*_*",
#       "keep *_*AK4*_*_*",
#       "keep *_selected*_*_*",
#       "keep *_updated*_*_*",
##      "keep *",
#   ),
#   fileName = cms.untracked.string("CMSSW.root")
#)
#process.out_step = cms.EndPath(process.output)
