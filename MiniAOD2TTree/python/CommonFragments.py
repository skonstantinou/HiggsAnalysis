'''

Instructions:
- Import this module
- Call produceCustomisations just before cms.Path
- Add process.CustomisationsSequence to the cms.Path

'''
#================================================================================================ 
# Import modules
#================================================================================================ 
import FWCore.ParameterSet.Config as cms

#================================================================================================ 
# Function definition
#================================================================================================ 
def produceCustomisations(process, isData):
    process.CustomisationsSequence = cms.Sequence()
#    reproduceJEC(process)
#    reproduceElectronID(process)
    reproduceMETNoiseFilters(process)
    reproduceMET(process, isData)
    produceTauID(process, isData)
#    reproduceJEC(process)
    produceJets(process, isData)
    return


# AK8 Customisations
def produceAK8Customisations(process, isData):
    process.AK8CustomisationsSequence = cms.Sequence()
    produceAK8Jets(process, isData)
    return

def produceAK8Jets(process, isData):
    print "\n=== Customisation: Running JetToolbox for AK8 Jets \n"
    
    process.load("Configuration.EventContent.EventContent_cff")
    process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
    process.load('Configuration.StandardSequences.MagneticField_38T_cff')
    process.load('Configuration.StandardSequences.Services_cff')
    
    JEC = ['L1FastJet','L2Relative','L3Absolute']
    if isData:
        JEC += ['L2L3Residual']
        
    from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox
    
    jetToolbox( process, 'ak8', 'ak8JetSubs', 'out',                
                updateCollection="slimmedJetsAK8",                
                JETCorrPayload="AK8PFchs", JETCorrLevels = JEC,
                postFix='', Cut="pt > 170.0",  # Cut needed to fix this issue: https://hypernews.cern.ch/HyperNews/CMS/get/JetMET/1785/1/1/1/1/1.html
                )
    return

# Taus Customisations
from HiggsAnalysis.MiniAOD2TTree.runTauIdMVA import *
def produceTauID(process, isData):
    '''
    https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePFTauID#Rerunning_of_the_tau_ID_on_M_AN1
    '''
    print "\n=== Customisation: Rerunning Tau  MVA ID (2017V2) \n"
    na = TauIDEmbedder(process, cms,
                       debug=True,
                       toKeep = ["2017v2"]  # Options: ["2017v1", "2017v2", "newDM2017v2", "dR0p32017v2", "2016v1", "newDM2016v1"] 
                       )
    na.runTauID()
    process.CustomisationsSequence += process.rerunMvaIsolationSequence
    process.CustomisationsSequence += process.NewTauIDsEmbedded
    return

def produceJets(process, isData):
    '''
    JetToolbox twiki:
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox
    
    Using the QGTagger with Jet Toolbox: 
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetToolbox#QGTagger
    
    QuarkGluonLikelihood twiki: 
    https://twiki.cern.ch/twiki/bin/view/CMS/QuarkGluonLikelihood
    
    More info:
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/QGDataBaseVersion
    '''
    
    print "\n=== Customisation: Running JetToolbox for AK4 Jets \n"
    
    process.load("Configuration.EventContent.EventContent_cff")
    process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
    process.load('Configuration.StandardSequences.MagneticField_38T_cff')
    process.load('Configuration.StandardSequences.Services_cff')
    
    JEC = ['L1FastJet','L2Relative','L3Absolute']
    if isData:
        JEC += ['L2L3Residual']

    from JMEAnalysis.JetToolbox.jetToolbox_cff import jetToolbox
    jetToolbox( process, 'ak4', 'ak4JetSubs', 'out',
                updateCollection='cleanedPatJetsModifiedMET', 
                JETCorrLevels = JEC, JETCorrPayload="AK4PFchs", 
                bTagDiscriminators = ['pfCombinedInclusiveSecondaryVertexV2BJetTags', 'pfCombinedMVAV2BJetTags',
                                      'pfDeepCSVJetTags:probb', 'pfDeepCSVJetTags:probc', 'pfDeepCSVJetTags:probudsg', 'pfDeepCSVJetTags:probbb',
                                      'pfDeepFlavourJetTags:probb', 'pfDeepFlavourJetTags:probbb', 'pfDeepFlavourJetTags:problepb', 'pfDeepFlavourJetTags:probc',
                                      'pfDeepFlavourJetTags:probuds', 'pfDeepFlavourJetTags:probg'],
                postFix='')
    
    # Small fix required to add the variables ptD, axis2, mult. See:
    # https://hypernews.cern.ch/HyperNews/CMS/get/jet-algorithms/418/1.html
    # getattr( process, 'updatedPatJetsAK4PFCHS').userData.userFloats.src += ['QGTagger'+'AK4PFCHS'+':ptD']
    # getattr( process, 'updatedPatJetsAK4PFCHS').userData.userFloats.src += ['QGTagger'+'AK4PFCHS'+':axis2']
    # getattr( process, 'updatedPatJetsAK4PFCHS').userData.userInts.src   += ['QGTagger'+'AK4PFCHS'+':mult']
    
    return


# ===== Reproduce jet collections with the latest JEC =====
def reproduceJEC(process):
    '''
    For instructions and more details see:
    https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#CorrPatJets
    https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2016#Jets
    https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetAnalysis
    '''
    print "=== Customisation: reproducing jet collections with latest JEC"
    from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
    updateJetCollection(
        process,
        jetSource = cms.InputTag('slimmedJets'),
        #jetSource = cms.InputTag('cleanedPatJets'),
        labelName = 'UpdatedJEC',
        jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None')  # Do not forget 'L2L3Residual' on data!
    )
    # PUPPI jets
    updateJetCollection(
        process,
        jetSource = cms.InputTag('slimmedJetsPuppi'),
        labelName = 'UpdatedJECPuppi',
        jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None')  # Do not
    )
    
    # Add to customisations sequence
    process.CustomisationsSequence += process.patJetCorrFactorsUpdatedJEC
    process.CustomisationsSequence += process.updatedPatJetsUpdatedJEC
    process.CustomisationsSequence += process.patJetCorrFactorsUpdatedJECPuppi
    process.CustomisationsSequence += process.updatedPatJetsUpdatedJECPuppi
    return

# ===== Set up electron ID (VID framework) =====
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
def reproduceElectronID(process):
    '''
    For instructions and more details see:
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaIDRecipesRun2
    https://twiki.cern.ch/twiki/bin/view/CMS/EgammaMiniAODV2#2017_MiniAOD_V2
    '''
    print "\n==== Customisation: Running EGamma IDs \n"
    process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
    
    my_id_modules = [
        'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V1_cff',
        'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V1_cff',
        'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V2_cff',
        'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_iso_V2_cff',
        'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V1_cff',
        'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
        ]
    
    from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
    setupEgammaPostRecoSeq(process,
                           runVID=True, 
                           era='2017-Nov17ReReco')  
    
    switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
    for idmod in my_id_modules:
        setupAllVIDIdsInModule(process, idmod, setupVIDElectronSelection)
        

    process.egmGsfElectronIDs.physicsObjectSrc = 'slimmedElectrons'
    process.electronMVAValueMapProducer.srcMiniAOD = 'slimmedElectrons'
    process.electronMVAVariableHelper.srcMiniAOD = 'slimmedElectrons'
    
    process.CustomisationsSequence += process.egammaPostRecoSeq 
    process.CustomisationsSequence += process.electronMVAVariableHelper
    process.CustomisationsSequence += process.electronMVAValueMapProducer
    process.CustomisationsSequence += process.egmGsfElectronIDSequence
    return
    
# ===== Set up HBHE noise filter =====
def reproduceMETNoiseFilters(process):
    '''
    For instructions and more details see:
    https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2
    '''
    print "=== Customisation: reproducing ECAL Bad Calibration filter"
    baddetEcallist = cms.vuint32(
        [872439604,872422825,872420274,872423218,
         872423215,872416066,872435036,872439336,
         872420273,872436907,872420147,872439731,
         872436657,872420397,872439732,872439339,
         872439603,872422436,872439861,872437051,
         872437052,872420649,872422436,872421950,
         872437185,872422564,872421566,872421695,
         872421955,872421567,872437184,872421951,
         872421694,872437056,872437057,872437313]
        )
    
    process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter(
        "EcalBadCalibFilter",
        EcalRecHitSource = cms.InputTag("reducedEgamma:reducedEERecHits"),
        ecalMinEt        = cms.double(50.),
        baddetEcal    = baddetEcallist, 
        taggingMode = cms.bool(True),
        debug = cms.bool(False)
        )
    
    print "=== Customisation: reproducing HBHE noise filter"
    process.load('CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi')
    process.HBHENoiseFilterResultProducer.minZeros = cms.int32(99999)
    process.HBHENoiseFilterResultProducer.IgnoreTS4TS5ifJetInLowBVRegion=cms.bool(False)
    process.HBHENoiseFilterResultProducer.defaultDecision = cms.string("HBHENoiseFilterResultRun2Loose")

    # Do not apply EDfilters for HBHE noise, the discriminators for them are saved into the ttree
    process.CustomisationsSequence += process.ecalBadCalibReducedMINIAODFilter
    process.CustomisationsSequence += process.HBHENoiseFilterResultProducer
    return

# ===== Set up MET uncertainties =====

def reproduceMET(process,isdata):
    '''
    For instructions and more details see:
    https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription#A_tool_to_help_you_calculate_MET
    https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC
    https://github.com/cms-jet/JECDatabase/tree/master/SQLiteFiles
    https://github.com/cms-jet/JRDatabase/tree/master/SQLiteFiles
    2017 ECAL problem: instructions for Type1 MET in https://twiki.cern.ch/twiki/bin/viewauth/CMS/SUSRecommendations18
    '''
    from CondCore.DBCommon.CondDBSetup_cfi import CondDBSetup
    import os

    if isdata:
        era="Fall17_17Nov2017_V32_94X_DATA"
    else:
        era="Fall17_17Nov2017_V32_94X_MC"
        
    jerera="Fall17_V3_94X"

    
##___________________________External JEC file________________________________||
 
    process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
#                               connect = cms.string("sqlite:PhysicsTools/PatUtils/data/"+era+".db"),
                               connect = cms.string("sqlite:"+era+"_JEC.db"),
                               toGet =  cms.VPSet(
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PF"),
                label= cms.untracked.string("AK4PF")
                ),
            cms.PSet(
                record = cms.string("JetCorrectionsRecord"),
                tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PFchs"),  
                label= cms.untracked.string("AK4PFchs")
                ),
            cms.PSet(record  = cms.string("JetCorrectionsRecord"),
                tag     = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PFPuppi"),
                label   = cms.untracked.string("AK4PFPuppi")
                ),
            cms.PSet(record  = cms.string("JetCorrectionsRecord"),
                tag     = cms.string("JetCorrectorParametersCollection_"+era+"_AK8PFchs"),
                label   = cms.untracked.string("AK8PFchs")
                ),
    
            )
                               )
    process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')

##___________________________External JER file________________________________||
    
    process.jer = cms.ESSource("PoolDBESSource",CondDBSetup,
#                               connect = cms.string("sqlite:PhysicsTools/PatUtils/data/JER/"+jerera+"_MC.db"),
                               connect = cms.string("sqlite:"+jerera+"_MC_JER.db"),
                               toGet =  cms.VPSet(
        #######
        ### read the PFchs  

        cms.PSet(
          record = cms.string('JetResolutionRcd'),
          tag    = cms.string('JR_'+jerera+'_MC_PtResolution_AK4PFchs'),
          label  = cms.untracked.string('AK4PFchs_pt')
          ),
        cms.PSet(
          record = cms.string("JetResolutionRcd"),
          tag    = cms.string('JR_'+jerera+'_MC_PhiResolution_AK4PFchs'),
          label  = cms.untracked.string("AK4PFchs_phi")
          ),
        cms.PSet( 
          record = cms.string('JetResolutionScaleFactorRcd'),
          tag    = cms.string('JR_'+jerera+'_MC_SF_AK4PFchs'),
          label  = cms.untracked.string('AK4PFchs')
          ),
        
        ### read the AK8 JER
        cms.PSet(
          record = cms.string('JetResolutionRcd'),
          tag    = cms.string('JR_'+jerera+'_MC_PtResolution_AK8PFchs'),
          label  = cms.untracked.string('AK8PFchs_pt')
          ),
        cms.PSet(
          record = cms.string("JetResolutionRcd"),
          tag    = cms.string('JR_'+jerera+'_MC_PhiResolution_AK8PFchs'),
          label  = cms.untracked.string("AK8PFchs_phi")
          ),
        cms.PSet( 
          record = cms.string('JetResolutionScaleFactorRcd'),
          tag    = cms.string('JR_'+jerera+'_MC_SF_AK8PFchs'),
          label  = cms.untracked.string('AK8PFchs')
          ),
        
          
        #######
        ### read the Puppi JER

#        cms.PSet( 
#          record = cms.string('JetResolutionRcd'),
#          tag    = cms.string('JR_'+jerera+'_MC_PtResolution_AK4PFPuppi'),
#          label  = cms.untracked.string('AK4PFPuppi_pt')
#          ),
#        cms.PSet(
#          record = cms.string("JetResolutionRcd"),
#          tag = cms.string('JR_'+jerera+'_MC_PhiResolution_AK4PFPuppi'),
#          label= cms.untracked.string("AK4PFPuppi_phi")
#          ),
#        cms.PSet(
#          record = cms.string('JetResolutionScaleFactorRcd'),
#          tag    = cms.string('JR_'+jerera+'_MC_SF_AK4PFPuppi'),
#          label  = cms.untracked.string('AK4PFPuppi')
#          ),
        ) 
    )
          
    process.es_prefer_jer = cms.ESPrefer("PoolDBESSource",'jer')

    # TWiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETUncertaintyPrescription#Instructions_for_9_4_X_X_9_for_2
    from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
    
    #default configuration for miniAOD reprocessing, change the isData flag to run on data
    #for a full met computation, remove the pfCandColl input
    runMetCorAndUncFromMiniAOD(process,
                               isData=isdata,
                               fixEE2017 = True,
                               fixEE2017Params = {'userawPt': True, 'ptThreshold':50.0, 'minEtaThreshold':2.65, 'maxEtaThreshold': 3.139},
                               postfix = "ModifiedMET"
                               )
    process.CustomisationsSequence += process.fullPatMetSequenceModifiedMET
    
#    process.selectedPatJetsForMetT1T2Corr.src = cms.InputTag("cleanedPatJets")
#    process.patPFMetT1.src = cms.InputTag("slimmedMETs")
#
#    process.CustomisationsSequence += process.patJetCorrFactorsReapplyJEC 
#    process.CustomisationsSequence += process.patJetsReapplyJEC
#    process.CustomisationsSequence += process.basicJetsForMet
#    process.CustomisationsSequence += process.jetSelectorForMet
#    process.CustomisationsSequence += process.cleanedPatJets
#    process.CustomisationsSequence += process.metrawCalo
#    process.CustomisationsSequence += process.selectedPatJetsForMetT1T2Corr   
#    process.CustomisationsSequence += process.patPFMetT1T2Corr
#    process.CustomisationsSequence += process.patPFMetT1

#    process.CustomisationsSequence += process.patMetCorrectionSequence

    if isdata:
        return

#    process.CustomisationsSequence += process.patMetUncertaintySequence #only for MC
#    process.CustomisationsSequence += process.patShiftedModuleSequence #only for MC


    """    
    # puppi jets and puppi met
    from PhysicsTools.PatAlgos.slimming.puppiForMET_cff import makePuppiesFromMiniAOD
    makePuppiesFromMiniAOD(process);

    runMetCorAndUncFromMiniAOD(process,
                             isData=isdata,
                             pfCandColl=cms.InputTag("puppiForMET"),
                             recoMetFromPFCs=True,
                             reclusterJets=True,
                             jetFlavor="AK4PFPuppi",
                             postfix="Puppi"
                             )
    process.patPFMetPuppi.addGenMET = cms.bool(False)
    process.basicJetsForMetPuppi.src = cms.InputTag("slimmedJetsPuppi")
    process.patPFMetT1Puppi.src = cms.InputTag("slimmedMETsPuppi")

    process.producePatPFMETCorrectionsPuppi.remove(process.patPFMetPuppi)
    process.CustomisationsSequence += process.producePatPFMETCorrectionsPuppi

#    process.CustomisationsSequence += process.pfNoLepPUPPI
#    process.CustomisationsSequence += process.puppiNoLep
#    process.CustomisationsSequence += process.pfLeptonsPUPPET
#    process.CustomisationsSequence += process.puppiMerged
#    process.CustomisationsSequence += process.puppiForMET
##    process.CustomisationsSequence += process.pfMetPuppi
##    process.CustomisationsSequence += process.patPFMetPuppi
#    process.CustomisationsSequence += process.ak4PFJetsPuppi
#    process.CustomisationsSequence += process.basicJetsForMetPuppi
#    process.CustomisationsSequence += process.jetSelectorForMetPuppi
#    process.CustomisationsSequence += process.cleanedPatJetsPuppi
#    process.CustomisationsSequence += process.pfMetPuppi
#    process.CustomisationsSequence += process.metrawCaloPuppi
#    process.CustomisationsSequence += process.patPFMetT1Puppi
#
#    process.CustomisationsSequence += process.patMetUncertaintySequencePuppi
#    process.CustomisationsSequence += process.patShiftedModuleSequencePuppi
#    process.CustomisationsSequence += process.patMetCorrectionSequencePuppi
    """
