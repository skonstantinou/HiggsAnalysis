import FWCore.ParameterSet.Config as cms

Electrons = cms.VPSet(
    cms.PSet(
        branchname = cms.untracked.string("Electrons"),
        src = cms.InputTag("slimmedElectrons"),
        rhoSource = cms.InputTag("fixedGridRhoFastjetAll"), # for PU mitigation in isolation
#        IDprefix = cms.string("egmGsfElectronIDs"),
#        discriminators = cms.vstring()
	discriminators = cms.vstring(

            # V1
            'cutBasedElectronID-Fall17-94X-V1-loose',
            'cutBasedElectronID-Fall17-94X-V1-medium',
            'cutBasedElectronID-Fall17-94X-V1-tight',
            'cutBasedElectronID-Fall17-94X-V1-veto',
            'mvaEleID-Fall17-iso-V1-wp80',
            'mvaEleID-Fall17-iso-V1-wp90',
            'mvaEleID-Fall17-iso-V1-wpLoose',
            'mvaEleID-Fall17-noIso-V1-wp80',
            'mvaEleID-Fall17-noIso-V1-wp90',
            'mvaEleID-Fall17-noIso-V1-wpLoose',            
            
            # V2
            #"egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-veto",
            #"egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-loose",
            #"egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-medium",
            #"egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-tight",
            #"egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wp90",
            #"egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wp80",
            #"egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wpLoose",
            #"egmGsfElectronIDs:mvaEleID-Fall17-noIso-V2-wp90",
            #"egmGsfElectronIDs:mvaEleID-Fall17-noIso-V2-wp80",
            #"egmGsfElectronIDs:mvaEleID-Fall17-noIso-V2-wpLoose",
            ),
#        discriminators = cms.vstring("mvaEleID-PHYS14-PU20bx25-nonTrig-V1-wp80",
#                                     "mvaEleID-PHYS14-PU20bx25-nonTrig-V1-wp90")
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
