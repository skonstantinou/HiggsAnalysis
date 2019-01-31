import FWCore.ParameterSet.Config as cms

Electrons = cms.VPSet(
    cms.PSet(
        branchname = cms.untracked.string("Electrons"),
        src = cms.InputTag("slimmedElectrons"),
        rhoSource = cms.InputTag("fixedGridRhoFastjetAll"), # for PU mitigation in isolation
#        IDprefix = cms.string("egmGsfElectronIDs"),
	discriminators = cms.vstring(
            "cutBasedElectronID-Fall17-94X-V2-veto",
            "cutBasedElectronID-Fall17-94X-V2-loose",
            "cutBasedElectronID-Fall17-94X-V2-medium",
            "cutBasedElectronID-Fall17-94X-V2-tight",
            
            'mvaEleID-Fall17-iso-V2-wp80', 
            'mvaEleID-Fall17-iso-V2-wp90',
            'mvaEleID-Fall17-iso-V2-wpHZZ', 
            'mvaEleID-Fall17-iso-V2-wpLoose',
            'mvaEleID-Fall17-noIso-V2-wp80', 
            'mvaEleID-Fall17-noIso-V2-wp90',
            'mvaEleID-Fall17-noIso-V2-wpLoose',
            ),
        pfcands     = cms.InputTag("packedPFCandidates"),
        ElectronMVA = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values"),
        #"electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17NoIsoV2Values",
        #"electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17NoIsoV2RawValues",
        #"electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17IsoV2Values",
        #"electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17IsoV2RawValues",
        #"electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17IsoV1Values",
        #"electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17NoIsoV1Values",
        rhoSourceMiniIso = cms.InputTag("fixedGridRhoFastjetAll"),
    )
)

# 8X
# egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-veto
# egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose
# egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium
# egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight
#
# heepElectronID-HEEPV60 
# mvaEleID-Spring15-25ns-nonTrig-V1-wp80 
# mvaEleID-Spring15-25ns-nonTrig-V1-wp90 
# cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-loose 
# cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-medium 
# cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-tight 
# cutBasedElectronID-PHYS14-PU20bx25-V2-standalone-veto 
# cutBasedElectronID-Spring15-25ns-V1-standalone-loose 
# cutBasedElectronID-Spring15-25ns-V1-standalone-medium 
# cutBasedElectronID-Spring15-25ns-V1-standalone-tight 
# cutBasedElectronID-Spring15-25ns-V1-standalone-veto 
# cutBasedElectronID-Spring15-50ns-V1-standalone-loose 
# cutBasedElectronID-Spring15-50ns-V1-standalone-medium 
# cutBasedElectronID-Spring15-50ns-V1-standalone-tight 
# cutBasedElectronID-Spring15-50ns-V1-standalone-veto 
# eidLoose 
# eidRobustHighEnergy 
# eidRobustLoose 
# eidRobustTight 
# eidTight
