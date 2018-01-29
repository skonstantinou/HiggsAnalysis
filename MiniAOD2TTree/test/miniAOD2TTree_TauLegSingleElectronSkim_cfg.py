import FWCore.ParameterSet.Config as cms
import HiggsAnalysis.MiniAOD2TTree.tools.git as git #HiggsAnalysis.HeavyChHiggsToTauNu.tools.git as git
from HiggsAnalysis.MiniAOD2TTree.tools.HChOptions import getOptionsDataVersion

process = cms.Process("TTreeDump")

#dataVersion = "92Xmc"
dataVersion = "92Xdata"

options, dataVersion = getOptionsDataVersion(dataVersion)
print dataVersion

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.load("FWCore/MessageService/MessageLogger_cfi")
process.MessageLogger.categories.append("TriggerBitCounter")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000 # print the event number for every 100th event
process.MessageLogger.cerr.TriggerBitCounter = cms.untracked.PSet(limit = cms.untracked.int32(10)) # print max 100 warnings

# Set the process options -- Display summary at the end, enable unscheduled execution
process.options = cms.untracked.PSet(
    allowUnscheduled = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'/store/data/Run2017D/SingleElectron/MINIAOD/PromptReco-v1/000/302/031/00000/105643A1-328F-E711-943D-02163E014641.root',
    ),
    secondaryFileNames = cms.untracked.vstring(
    )
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, str(dataVersion.getGlobalTag()), '')
print "GlobalTag="+dataVersion.getGlobalTag()

# Set up electron ID (VID framework)
# https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
# define which IDs we want to produce and add them to the VID producer
for idmod in ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_PHYS14_PU20bx25_nonTrig_V1_cff']:
    setupAllVIDIdsInModule(process, idmod, setupVIDElectronSelection)

# Set up HBHE noise filter
# https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2
print "Setting up HBHE noise filter"   
process.load('CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi')
process.HBHENoiseFilterResultProducer.minZeros = cms.int32(99999)
process.HBHENoiseFilterResultProducer.IgnoreTS4TS5ifJetInLowBVRegion=cms.bool(False)
process.HBHENoiseFilterResultProducer.defaultDecision = cms.string("HBHENoiseFilterResultRun2Loose")
# Do not apply EDfilters for HBHE noise, the discriminators for them are saved into the ttree

process.load("HiggsAnalysis/MiniAOD2TTree/PUInfo_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/TopPt_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Tau_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Electron_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Muon_cfi")
process.load("HiggsAnalysis/MiniAOD2TTree/Jet_cfi")    
process.load("HiggsAnalysis/MiniAOD2TTree/MET_cfi")    
process.load("HiggsAnalysis/MiniAOD2TTree/METNoiseFilter_cfi")
process.METNoiseFilter.triggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getMETFilteringProcess())) 

process.dump = cms.EDFilter('MiniAOD2TTreeFilter',
    OutputFileName = cms.string("miniaod2tree.root"),
    PUInfoInputFileName = process.PUInfo.OutputFileName,
    TopPtInputFileName = process.TopPtProducer.OutputFileName,
    CodeVersion = cms.string(git.getCommitId()),
    DataVersion = cms.string(str(dataVersion.version)),
    CMEnergy = cms.int32(13),
    Skim = cms.PSet(
	Counters = cms.VInputTag(
	    "skimCounterAll",
            "skimCounterPassed"
        ),
    ),
    EventInfo = cms.PSet(
	PileupSummaryInfoSrc = process.PUInfo.PileupSummaryInfoSrc,
#	LumiScalersSrc = cms.InputTag("scalersRawToDigi"),
	OfflinePrimaryVertexSrc = cms.InputTag("offlineSlimmedPrimaryVertices"),
        TopPtProducer = cms.InputTag("TopPtProducer"),
    ),
    Trigger = cms.PSet(
	TriggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getTriggerProcess())),
#        TriggerResults = cms.InputTag("TriggerResults::HLT25NSV4L1V5"),
#        TriggerResults = cms.InputTag("TriggerResults::TauHLT"),
	TriggerBits = cms.vstring(
            "HLT_Ele24_eta2p1_WPTight_Gsf_v",
            "HLT_Ele35_WPTight_Gsf_v",
            "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1_v",
            "HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTau30_eta2p1_CrossL1_v",
            "HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTau30_eta2p1_CrossL1_v",
            "HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1_v",
            "HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTau30_eta2p1_TightID_CrossL1_v",
            "HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTau30_eta2p1_TightID_CrossL1_v"
        ),
	L1Extra = cms.InputTag("l1extraParticles:MET"),
#        L1Extra = cms.InputTag("l1extraParticles:MET:HLT25NSV4L1V5"),
#	L1Extra = cms.InputTag("l1extraParticles:MET:TauHLT"),
	TriggerObjects = cms.InputTag("selectedPatTrigger"),
        L1TauObjects = cms.InputTag("caloStage2Digis:Tau"),
        L1EtSumObjects = cms.InputTag("caloStage2Digis:EtSum"),
	TriggerMatch = cms.untracked.vstring(
	    "MediumChargedIsoPFTau50_Trk30_eta2p1_1pr",
	    "LooseIsoPFTau20",
            "MediumIsoPFTau32_Trk1_eta2p1_Reg",
            "IsoMu24_eta2p1",
	),
	filter = cms.untracked.bool(False)
    ),
    METNoiseFilter = process.METNoiseFilter,
    Taus      = process.TausNoSysVariations,
    Electrons = process.Electrons,
    Muons     = process.Muons,
    Jets      = process.JetsNoSysVariations,
    METs      = process.METsNoSysVariations,
    GenWeights = cms.VPSet(
        cms.PSet(
            branchname = cms.untracked.string("GenWeights"),
            src = cms.InputTag("generator"),
            filter = cms.untracked.bool(False)
        )
    ),
)

process.load("HiggsAnalysis.MiniAOD2TTree.TauLegSingleElectronSkim_cfi")
process.skim.GenWeights = process.dump.GenWeights

process.skimCounterAll        = cms.EDProducer("HplusEventCountProducer")
process.skimCounterMETFilters = cms.EDProducer("HplusEventCountProducer")
process.skimCounterPassed     = cms.EDProducer("HplusEventCountProducer")
process.skim.TriggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getTriggerProcess()))

# === Setup customizations
from HiggsAnalysis.MiniAOD2TTree.CommonFragments import produceCustomisations
produceCustomisations(process,dataVersion.isData()) # This produces process.CustomisationsSequence which needs to be included to path

# module execution
process.runEDFilter = cms.Path(process.PUInfo*
                               process.skimCounterAll*
                               process.skim*
                               process.skimCounterPassed*
                               process.CustomisationsSequence*
                               process.dump)

#process.output = cms.OutputModule("PoolOutputModule",
#    outputCommands = cms.untracked.vstring(
#        "keep *",
#    ),
#    fileName = cms.untracked.string("CMSSW.root")
#)
#process.out_step = cms.EndPath(process.output)