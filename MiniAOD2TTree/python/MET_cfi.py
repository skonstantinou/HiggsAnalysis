import FWCore.ParameterSet.Config as cms

METs = cms.VPSet(
    cms.PSet(
        branchname = cms.untracked.string("MET_Type1"),
        src = cms.InputTag("slimmedMETsModifiedMET")
    ),
#    cms.PSet(
#        branchname = cms.untracked.string("MET_Type1_NoHF"),
#        src = cms.InputTag("slimmedMETsNoHF")
#    ),
#    cms.PSet(
#        branchname = cms.untracked.string("MET_Puppi"),
#        src = cms.InputTag("slimmedMETsPuppi")
#    ),
    cms.PSet(
        branchname = cms.untracked.string("MET_Type1_UnclusteredEnDown"),
        src = cms.InputTag("patPFMetT1UnclusteredEnDownModifiedMET")
    ),
    cms.PSet(
        branchname = cms.untracked.string("MET_Type1_UnclusteredEnUp"),
        src = cms.InputTag("patPFMetT1UnclusteredEnUpModifiedMET")
    ),
    cms.PSet(
        branchname = cms.untracked.string("MET_Type1_JetEnDown"),
        src = cms.InputTag("patPFMetT1JetEnDownModifiedMET")
    ),
    cms.PSet(
        branchname = cms.untracked.string("MET_Type1_JetEnUp"),
        src = cms.InputTag("patPFMetT1JetEnUpModifiedMET")
    ),
    cms.PSet(
        branchname = cms.untracked.string("MET_Type1_JetResDown"),
        src = cms.InputTag("patPFMetT1JetResDownModifiedMET")   
    ),
    cms.PSet(
        branchname = cms.untracked.string("MET_Type1_JetResUp"),
        src = cms.InputTag("patPFMetT1JetResUpModifiedMET")
    ),
    cms.PSet(
        branchname = cms.untracked.string("MET_Type1_TauEnDown"),
        src = cms.InputTag("patPFMetT1TauEnDownModifiedMET")   
    ),
    cms.PSet(
        branchname = cms.untracked.string("MET_Type1_TauEnUp"),
        src = cms.InputTag("patPFMetT1TauEnUpModifiedMET")
    ),
)

METsNoSysVariations = cms.VPSet()
METsNoSysVariations.append(METs[0])
