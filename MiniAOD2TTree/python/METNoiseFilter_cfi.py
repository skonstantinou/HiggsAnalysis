import FWCore.ParameterSet.Config as cms

METNoiseFilter = cms.PSet(
#    triggerResults = cms.InputTag("TriggerResults::"+str(dataVersion.getMETFilteringProcess())),   
    triggerResults = cms.InputTag("TriggerResults::HLT"),
    printTriggerResultsList = cms.untracked.bool(False),
    filtersFromTriggerResults = cms.vstring(
        "Flag_HBHENoiseFilter",
        "Flag_HBHENoiseIsoFilter",
        "Flag_CSCTightHaloFilter",
        "Flag_EcalDeadCellTriggerPrimitiveFilter",
        "Flag_goodVertices",
        "Flag_eeBadScFilter",
        "Flag_globalSuperTightHalo2016Filter",
        "Flag_BadPFMuonFilter",
        "Flag_BadChargedCandidateFilter",
        ),
    hbheNoiseTokenRun2LooseSource   = cms.InputTag('HBHENoiseFilterResultProducer','HBHENoiseFilterResultRun2Loose'),
    hbheNoiseTokenRun2TightSource   = cms.InputTag('HBHENoiseFilterResultProducer','HBHENoiseFilterResultRun2Tight'),
    hbheIsoNoiseTokenSource         = cms.InputTag('HBHENoiseFilterResultProducer','HBHEIsoNoiseFilterResult'),
    ecalBadCalibReducedFilterSource = cms.InputTag('ecalBadCalibReducedMINIAODFilter'),
)

