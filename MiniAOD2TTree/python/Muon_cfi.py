import FWCore.ParameterSet.Config as cms

Muons = cms.VPSet(
    cms.PSet(
        branchname = cms.untracked.string("Muons"),
        src = cms.InputTag("slimmedMuons"),
        
        rhoSource = cms.InputTag("fixedGridRhoFastjetAll"), # For MiniIsolation
        
        discriminators = cms.vstring(),
        
        pfcands = cms.InputTag("packedPFCandidates"),
    )
)
