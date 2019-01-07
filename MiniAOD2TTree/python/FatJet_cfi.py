#================================================================================================
# Import modules
#================================================================================================
import FWCore.ParameterSet.Config as cms

AK8Jets = cms.PSet(
    branchname = cms.untracked.string("AK8Jets"),
    src        = cms.InputTag("selectedPatJetsAK8PFCHS"),
    systVariations = cms.bool(False), # bug => requires fix!
    srcJESup   = cms.InputTag("shiftedPatJetEnUpModiedMET"),
    srcJESdown = cms.InputTag("shiftedPatJetEnDownModiedMET"),
    srcJERup   = cms.InputTag("shiftedPatSmearedJetResUp"),
    srcJERdown = cms.InputTag("shiftedPatSmearedJetResDown"),
        
    discriminators = cms.vstring(
        "pfCombinedInclusiveSecondaryVertexV2BJetTags",
        "pfBoostedDoubleSecondaryVertexAK8BJetTags",
        "pfCombinedCvsBJetTags",
        "pfCombinedCvsLJetTags",
        ),
    userFloats = cms.vstring(
        "ak8PFJetsCHSValueMap:NjettinessAK8CHSTau1",
        "ak8PFJetsCHSValueMap:NjettinessAK8CHSTau2",
        "ak8PFJetsCHSValueMap:NjettinessAK8CHSTau3",
        "ak8PFJetsCHSValueMap:ak8PFJetsCHSPrunedMass",
        "ak8PFJetsCHSValueMap:ak8PFJetsCHSSoftDropMass",
        "NjettinessAK8Puppi:tau1",
        "NjettinessAK8Puppi:tau2",
        "NjettinessAK8Puppi:tau3",
        "ak8PFJetsPuppiSoftDropMass",
        ),
    userInts = cms.vstring(
        ),
#   mcjecPath   = cms.untracked.string("jec/Summer16_23Sep2016V4"),
#   datajecPath = cms.untracked.string("jec/Summer16_23Sep2016BCDV4"), 
    rho         = cms.InputTag("fixedGridRhoFastjetAll"),
    vertices    = cms.InputTag("offlineSlimmedPrimaryVertices"),
)


AK8JetsPuppi = cms.PSet(
    branchname = cms.untracked.string("AK8PuppiJets"),
    src        = cms.InputTag("selectedPatJetsAK8PFPuppi"),
    systVariations = cms.bool(False), # bug => requires fix!
    srcJESup   = cms.InputTag("shiftedPatJetEnUpModiedMET"),
    srcJESdown = cms.InputTag("shiftedPatJetEnDownModiedMET"),
    srcJERup   = cms.InputTag("shiftedPatSmearedJetResUpModiedMET"),
    srcJERdown = cms.InputTag("shiftedPatSmearedJetResDownModiedMET"),
    discriminators = cms.vstring(
        "pfCombinedInclusiveSecondaryVertexV2BJetTags",
        "pfBoostedDoubleSecondaryVertexAK8BJetTags",
        "pfCombinedCvsBJetTags",
        "pfCombinedCvsLJetTags",
        ),
    userFloats = cms.vstring(
        "ak8PFJetsPuppiSoftDropValueMap:nb1AK8PuppiSoftDropN2",
        "ak8PFJetsPuppiSoftDropValueMap:nb1AK8PuppiSoftDropN3",
        "ak8PFJetsPuppiSoftDropValueMap:nb2AK8PuppiSoftDropN2",
        "ak8PFJetsPuppiSoftDropValueMap:nb2AK8PuppiSoftDropN3",
        "ak8PFJetsPuppiFilteredMass",
        "ak8PFJetsPuppiTrimmedMass",
        "ak8PFJetsPuppiSoftDropMass",
        ),
    userInts = cms.vstring(
        ),
    #    mcjecPath   = cms.untracked.string("jec/Summer16_23Sep2016V4"),
    #    datajecPath = cms.untracked.string("jec/Summer16_23Sep2016BCDV4"), 
    rho         = cms.InputTag("fixedGridRhoFastjetAll"),
    vertices    = cms.InputTag("offlineSlimmedPrimaryVertices"),
)


FatJets = cms.VPSet()
FatJets.append(AK8Jets)
#FatJets.append(AK8JetsPuppi)

FatJetsNoSysVariations = cms.VPSet()
for i in range(len(FatJets)):
    pset = FatJets[i].clone()
    pset.systVariations = cms.bool(False)
    FatJetsNoSysVariations.append(pset)
