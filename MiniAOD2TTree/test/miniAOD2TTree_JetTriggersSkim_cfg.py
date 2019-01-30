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
DataSet = "SingleMu" # Options = ["SingleMu", "JetHT"]

maxEvents    = 1000
maxWarnings  = 100
reportEvery  = 100
testWithData = False
if testWithData:
    dataVersion  = "94Xdata"
    datasetFiles = [
        # SingleMuon
        "/store/data/Run2017C/SingleMuon/MINIAOD/31Mar2018-v1/00000/7AF7AD3D-2237-E811-9D8E-FA163E7CF739.root",
        "/store/data/Run2017C/SingleMuon/MINIAOD/31Mar2018-v1/00000/80183154-F336-E811-B0F5-FA163EF3C3CB.root",
        "/store/data/Run2017C/SingleMuon/MINIAOD/31Mar2018-v1/00000/86502CAF-F036-E811-9E24-FA163E095B0B.root",
        "/store/data/Run2017C/SingleMuon/MINIAOD/31Mar2018-v1/00000/9409C24A-1B37-E811-9D6C-02163E01A048.root",
        "/store/data/Run2017C/SingleMuon/MINIAOD/31Mar2018-v1/00000/9CA5B1B5-FE36-E811-B598-FA163E6F47B2.root",
        # JetHT
        #'/store/data/Run2017B/JetHT/MINIAOD/31Mar2018-v1/00000/0205C4D3-463A-E811-86BD-0CC47A4C8E2A.root',
        #'/store/data/Run2017B/JetHT/MINIAOD/31Mar2018-v1/00000/082B8E3A-B23A-E811-B9B6-0CC47A4D760A.root',
        #'/store/data/Run2017B/JetHT/MINIAOD/31Mar2018-v1/00000/0E6724B9-013A-E811-962C-0025905B8606.root',
        #'/store/data/Run2017B/JetHT/MINIAOD/31Mar2018-v1/00000/12479445-673A-E811-89D8-0CC47A4C8E82.root',
        #'/store/data/Run2017E/JetHT/MINIAOD/31Mar2018-v1/90001/EE28F64A-9F37-E811-AE35-008CFAC91B70.root',
        #'/store/data/Run2017E/JetHT/MINIAOD/31Mar2018-v1/90001/EC952E5C-7237-E811-BFB8-008CFAC9405C.root',
        #'/store/data/Run2017E/JetHT/MINIAOD/31Mar2018-v1/90001/E6F15B74-7237-E811-B46D-008CFAC94068.root',
        #'/store/data/Run2017E/JetHT/MINIAOD/31Mar2018-v1/90001/DEFCBB4C-6E37-E811-B2EF-008CFAC91C58.root',
        ]
else:
    dataVersion  = "94Xmc"
    datasetFiles = [
        # TTToHadronic
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/FE3E8889-9342-E811-898F-008CFAF724BE.root',
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/F819F9EE-5142-E811-BC28-7845C4FC3C7D.root',
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/F4DCCD39-A542-E811-9E16-008CFAF225DC.root',
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/F4C04DD1-9042-E811-A933-008CFAF747AA.root',
        '/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/F445F408-C442-E811-88B5-7CD30AD0A15C.root',
        # HPlusToTB
        '/store/mc/RunIISummer17MiniAOD/ChargedHiggs_HplusTB_HplusToTB_M-500_13TeV_amcatnlo_pythia8/MINIAODSIM/NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/150000/FA3778BB-1BAE-E711-86C7-0025905B85CC.root',
        '/store/mc/RunIISummer17MiniAOD/ChargedHiggs_HplusTB_HplusToTB_M-500_13TeV_amcatnlo_pythia8/MINIAODSIM/NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/150000/C6B567EC-29B3-E711-8B60-002590DE6E78.root',
        '/store/mc/RunIISummer17MiniAOD/ChargedHiggs_HplusTB_HplusToTB_M-500_13TeV_amcatnlo_pythia8/MINIAODSIM/NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/150000/B4FB980E-2AB3-E711-8F79-FA163E1B2305.root',
        '/store/mc/RunIISummer17MiniAOD/ChargedHiggs_HplusTB_HplusToTB_M-500_13TeV_amcatnlo_pythia8/MINIAODSIM/NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/150000/B2EFA52E-C3B4-E711-8B38-3417EBE70003.root',
        '/store/mc/RunIISummer17MiniAOD/ChargedHiggs_HplusTB_HplusToTB_M-500_13TeV_amcatnlo_pythia8/MINIAODSIM/NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/150000/9846934D-50AC-E711-AC34-003048FFD7A4.root',
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
                            fileNames = cms.untracked.vstring(datasetFiles)
                            )


#================================================================================================  
# Get Dataset version andGlobal tag
#================================================================================================  
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
options, dataVersion = getOptionsDataVersion(dataVersion)
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, str(dataVersion.getGlobalTag()), '')


#================================================================================================  
# Set up tree dumper
#================================================================================================  

####
msgAlign = "{:<10} {:<55} {:<25} {:<25}"
title    =  msgAlign.format("Data", "Global Tag", "Trigger Source", "Trigger Tag")
print "="*len(title)
print title
print "="*len(title)
print msgAlign.format(dataVersion.version, dataVersion.getGlobalTag(), dataVersion.getMETFilteringProcess(), dataVersion.getTriggerProcess())
print 
####

process.load("HiggsAnalysis/MiniAOD2TTree/PUInfo_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/TopPt_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Tau_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Electron_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Muon_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Jet_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/FatJet_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Top_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/MET_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/METNoiseFilter_cfi")

process.METNoiseFilter.triggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getMETFilteringProcess())) 
print "check tau",process.Taus_TauPOGRecommendation[0]
process.dump = cms.EDFilter('MiniAOD2TTreeFilter',
    OutputFileName      = cms.string("miniaod2tree.root"),
    PUInfoInputFileName = process.PUInfo.OutputFileName,
    TopPtInputFileName  = process.TopPtProducer.OutputFileName,
    CodeVersion         = cms.string(git.getCommitId()),
    DataVersion         = cms.string(str(dataVersion.version)),
    CMEnergy            = cms.int32(13),
    Skim = cms.PSet(
	Counters = cms.VInputTag(
	    "skimCounterAll",
            "skimCounterPassed"
        ),
    ),
    EventInfo = cms.PSet(
        PileupSummaryInfoSrc    = process.PUInfo.PileupSummaryInfoSrc, 
	LHESrc                  = cms.untracked.InputTag("externalLHEProducer"),
	OfflinePrimaryVertexSrc = cms.InputTag("offlineSlimmedPrimaryVertices"),
	TopPtProducer           = cms.InputTag("TopPtProducer"),
    ),
    Trigger = cms.PSet(
	TriggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getTriggerProcess())),
	TriggerBits    = cms.vstring(
            "HLT_IsoMu24_v",
            "HLT_IsoMu24_eta2p1_v",
            "HLT_IsoMu27_v",
            "HLT_IsoMu30_v",
            # Signal Triggers
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
            "HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1_v",
            "HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1_v",
            "HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1_v",
            "HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2_v",
            "HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2_v",
            "HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2_v",
            "HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2_v",
            "HLT_QuadPFJet98_83_71_15_v",
            "HLT_QuadPFJet103_88_75_15_v",
            "HLT_QuadPFJet105_88_76_15_v",
            "HLT_QuadPFJet111_90_80_15_v",
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
if DataSet == "SingleMu":
    process.load("HiggsAnalysis.MiniAOD2TTree.JetTriggersSkim_SingleMu_cfi")
if DataSet == "JetHT":
    process.load("HiggsAnalysis.MiniAOD2TTree.JetTriggersSkim_JetHT_cfi")

process.skimCounterAll        = cms.EDProducer("HplusEventCountProducer")
process.skimCounterPassed     = cms.EDProducer("HplusEventCountProducer")
process.skim.TriggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getTriggerProcess()))

#================================================================================================ 
# Setup customizations
#================================================================================================ 
from HiggsAnalysis.MiniAOD2TTree.CommonFragments import produceCustomisations
produceCustomisations(process,dataVersion.isData()) # This produces process.CustomisationsSequence which needs to be included to path

from HiggsAnalysis.MiniAOD2TTree.CommonFragments import produceAK8Customisations
produceAK8Customisations(process, dataVersion.isData())   # This produces process.AK8CustomisationsSequence which needs to be included to path   

# Set up electron MVA ID for Skimming
# https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

print "=== Adding Electron MVA: ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values"
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)

for idmod in ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff']:
    setupAllVIDIdsInModule(process, idmod, setupVIDElectronSelection)


#================================================================================================ 
# Module execution
#================================================================================================ 
process.runEDFilter = cms.Path(process.PUInfo*
                               process.TopPtProducer*
                               process.egmGsfElectronIDSequence*
                               process.skimCounterAll*
                               process.skim*
                               process.skimCounterPassed*
                               process.CustomisationsSequence*
                               process.AK8CustomisationsSequence*
                               process.dump)


#process.output = cms.OutputModule("PoolOutputModule",
#   outputCommands = cms.untracked.vstring(
#       "keep *",
#   ),
#   fileName = cms.untracked.string("CMSSW.root")
#)
#process.out_step = cms.EndPath(process.output)
