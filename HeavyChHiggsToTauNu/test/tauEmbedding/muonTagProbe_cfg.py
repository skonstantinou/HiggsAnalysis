# https://twiki.cern.ch/twiki/bin/view/CMS/TagAndProbe
# https://twiki.cern.ch/twiki/bin/view/CMS/MuonTagAndProbe
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonAnalysisMuonAssociators#Configuration_file_to_produce_PA
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideTagProbeFitTreeProducer

import FWCore.ParameterSet.Config as cms
from HiggsAnalysis.HeavyChHiggsToTauNu.HChOptions import getOptionsDataVersion

################################################################################
# Configuration

dataVersion = "39Xredigi"

################################################################################

# Command line arguments (options) and DataVersion object
options, dataVersion = getOptionsDataVersion(dataVersion)
options.doPat=1

trigger = options.trigger
if len(trigger) == 0:
    trigger = "HLT_Mu9"

#mu9filter = "hltSingleL3MuonPre9"
#mu15filter = "hltSingleL3MuonPre15"
mu9filter = "hltSingleMu9L3Filtered9"
mu15filter = "hltSingleM159L3Filtered15"

triggerFilter = ""
if "HLT_Mu9" in trigger:
    triggerFilter = mu9filter
elif "HLT_Mu15" in trigger:
    triggerFilter = mu15filter
else:
    raise Exception("Trigger '%s' not recognized" % trigger)


################################################################################
# Define the process
process = cms.Process("TagProbe")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string(dataVersion.getGlobalTag())

process.source = cms.Source('PoolSource',
    fileNames = cms.untracked.vstring(
        #dataVersion.getPatDefaultFileMadhatter()
        "file:/mnt/flustre/mkortela/data/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Winter10-E7TeV_ProbDist_2010Data_BX156_START39_V8-v1/AODSIM/E28BCD86-B311-E011-A953-E0CB4E19F95B.root"
    )
)

################################################################################

process.load("HiggsAnalysis.HeavyChHiggsToTauNu.HChCommon_cfi")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

################################################################################

# PAT
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('dummy.root'),
    outputCommands = cms.untracked.vstring()
)

from HiggsAnalysis.HeavyChHiggsToTauNu.HChPatTuple import addPatOnTheFly
patArgs = {
    "doPatTaus": False,
    "doPatMET": False,
    "doPatElectronID": False,
    "doPatCalo": False,
    "doBTagging": False,
    "doPatMuonPFIsolation": True,
    "doTauHLTMatching": False,
    }
process.commonSequence, counters = addPatOnTheFly(process, options, dataVersion, patArgs=patArgs)
del process.out

# Triggering
process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")
process.triggerResultsFilter.hltResults = cms.InputTag("TriggerResults", "", dataVersion.getTriggerProcess())
process.triggerResultsFilter.l1tResults = cms.InputTag("") # dummy
process.triggerResultsFilter.throw = cms.bool(True)
process.triggerResultsFilter.triggerConditions = cms.vstring(trigger)
process.commonSequence *= process.triggerResultsFilter

process.triggeredCount = cms.EDProducer("EventCountProducer")
process.commonSequence *= process.triggeredCount
counters.append("triggeredCount")

# HLT matching and embedding
import MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff as muonTrigger
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
muonTrigger.useExistingPATMuons(process, "patMuons")
process.patTrigger.onlyStandAlone = False
process.commonSequence *= process.patMuonsWithTriggerSequence

# Preselection by tracks
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.goodTracks = cms.EDFilter("TrackSelector",
    src = cms.InputTag("generalTracks"), # or cms.InputTag("standAloneMuons","UpdatedAtVtx"), 
#    cut = cms.string("pt > 25 && abs(eta) < 2.1 && numberOfValidHits >= 12"),
    cut = cms.string("pt > 25 && abs(eta) < 2.1"),
    filter = cms.bool(True)
)
process.goodTracksCount = cms.EDProducer("EventCountProducer")
counters.append("goodTracksCount")
process.trackCands = cms.EDProducer("ConcreteChargedCandidateProducer",
    src = cms.InputTag("goodTracks"),
    particleType = cms.string("mu+")
)
process.commonSequence *= (process.goodTracks * process.goodTracksCount * process.trackCands)

# Preselection by track invariant mass
process.zCands = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("trackCands@+ trackCands@-"),
    cut   = cms.string("60 < mass < 120")
)
process.zCandsFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("zCands"),
    minNumber = cms.uint32(1)
)
process.zCandsCount = cms.EDProducer("EventCountProducer")
counters.append("zCandsCount")
process.commonSequence *= (process.zCands * process.zCandsFilter * process.zCandsCount)

# Tag and Probe definitions
process.tagMuons = cms.EDFilter("PATMuonRefSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(
        "isGlobalMuon() && isTrackerMuon()"
        "&& pt() > 30 && abs(eta()) < 2.1"
        "&& muonID('GlobalMuonPromptTight')"
        "&& innerTrack().numberOfValidHits() > 10"
        "&& innerTrack().hitPattern.pixelLayersWithMeasurement() >= 1"
        "&& numberOfMatches() > 1"
        "&& abs(dB()) < 0.02"
        "&& (isolationR03().emEt+isolationR03().hadEt+isolationR03().sumPt)/pt() < 0.1"
        "&& !triggerObjectMatchesByFilter('%s').empty()" % triggerFilter
    ),
)

#process.trkProbes  = cms.EDProducer("ConcreteChargedCandidateProducer", 
#    src  = cms.InputTag("goodTracks"),      
#    particleType = cms.string("mu+"),     # this is needed to define a mass
#)
process.probeMuons = cms.EDFilter("PATMuonRefSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(
        "isTrackerMuon()"
        "&& pt() > 30"
    )
)

process.tagProbes = cms.EDProducer("CandViewShallowCloneCombiner",
#    decay = cms.string("tagMuons@+ trkProbes@-"),
    decay = cms.string("tagMuons@+ probeMuons@-"),
#    cut   = cms.string("2.5 < mass < 3.8"),
    cut   = cms.string("60 < mass < 120"),
)

process.tagAndProbeSequence = cms.Sequence(
    process.tagMuons *
#    process.trkProbes *
    process.probeMuons *
    process.tagProbes
)


# Tag and Probe tree
process.tnpTree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tagProbes"),
    arbitration   = cms.string("OneProbe"), ## that is, use only tags associated to a single probe.
    # probe variables
    variables = cms.PSet(
        pt     = cms.string("pt"),
        abseta = cms.string("abs(eta)"),
    ),
    # choice of what defines a 'passing' probe
    flags = cms.PSet(
        isGlobalMuon = cms.string("isGlobalMuon"),
        #isHLTMu9     = cms.string("!triggerObjectMatchesByFilter('hltSingleL3MuonPre9').empty()"),  
        #isHLTMu15    = cms.string("!triggerObjectMatchesByFilter('hltSingleL3MuonPre15').empty()"),  
        isHLTMu9     = cms.string("!triggerObjectMatchesByFilter('%s').empty()" % mu9filter),
        isHLTMu15    = cms.string("!triggerObjectMatchesByFilter('%s').empty()" % mu15filter),
        isID         = cms.string("muonID('GlobalMuonPromptTight')"),
        hitQuality   = cms.string("innerTrack().numberOfValidHits() > 10 && innerTrack().hitPattern.pixelLayersWithMeasurement() >= 1 && numberOfMatches() > 1"),
        isClose      = cms.string("abs(dB()) < 0.02"),
        isIsolated   = cms.string("(isolationR03().emEt+isolationR03().hadEt+isolationR03().sumPt)/pt() < 0.1"),
        fullSelection = cms.string(
            "isGlobalMuon() && isTrackerMuon()"
            "&& pt() > 30 && abs(eta()) < 2.1"
            "&& muonID('GlobalMuonPromptTight')"
            "&& innerTrack().numberOfValidHits() > 10"
            "&& innerTrack().hitPattern.pixelLayersWithMeasurement() >= 1"
            "&& numberOfMatches() > 1"
            "&& abs(dB()) < 0.02"
            "&& (isolationR03().emEt+isolationR03().hadEt+isolationR03().sumPt)/pt() < 0.1"
            "&& !triggerObjectMatchesByFilter('%s').empty()" % triggerFilter
        )
    ),
    ## DATA-related info
    addRunLumiInfo = cms.bool(True),
    ## MC-related info
    isMC = cms.bool(False), ## on MC you can set this to true, add some parameters and get extra info in the tree.
#    isMC = cms.bool(dataVersion.isMC()), ## on MC you can set this to true, add some parameters and get extra info in the tree.
)

# Count analyzer
process.tnpCounters = cms.EDAnalyzer("HPlusEventCountAnalyzer",
    counters = cms.untracked.VInputTag([cms.InputTag(c) for c in counters])
)

# Path
process.tagAndProbeSequence *= (process.tnpTree * process.tnpCounters)

process.path = cms.Path(
    process.commonSequence *
    process.tagAndProbeSequence
)
