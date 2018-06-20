lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt"

#================================================================================================ 
# Class Definition
#================================================================================================ 
import os

class Dataset:
    def __init__(self, url, dbs="global", dataVersion="80Xmc", dasQuery="", lumiMask=lumiMask, name=""):
        self.URL = url
        self.DBS = dbs
        self.dataVersion = dataVersion
        if not os.path.dirname(lumiMask):
            lumiMask = os.path.join(os.environ['CMSSW_BASE'],"src/HiggsAnalysis/MiniAOD2TTree/data",lumiMask)
        self.lumiMask = lumiMask
        self.DASquery = dasQuery
	self.name = name

    def isData(self):
        if "data" in self.dataVersion:
            return True
        return False

    def getName(self):
	return self.name


#================================================================================================ 
# Data
#================================================================================================ 

datasetsTauData = []
das = ""
datasetsTauData.append(Dataset('/Tau/Run2017B-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_297050-299329_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017B.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017C-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_299368-302029_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017C.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017D-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_302031-302663_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017D.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017E-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_303824-304797_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017E.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017F-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_305040-306460_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017F.txt"))

datasetsJetHTData = []
das = ""


datasetsMuonData = []
das = ""
datasetsMuonData.append(Dataset('/SingleMuon/Run2017B-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_297050-299329_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017B.txt"))
datasetsMuonData.append(Dataset('/SingleMuon/Run2017C-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_299368-302029_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017C.txt"))
datasetsMuonData.append(Dataset('/SingleMuon/Run2017D-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_302031-302663_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017D.txt"))
datasetsMuonData.append(Dataset('/SingleMuon/Run2017E-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_303824-304797_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017E.txt"))
datasetsMuonData.append(Dataset('/SingleMuon/Run2017F-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_305040-306460_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017F.txt"))


datasetsElectronData = []
das = ""
datasetsElectronData.append(Dataset('/SingleElectron/Run2017C-PromptReco-v3/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
datasetsElectronData.append(Dataset('/SingleElectron/Run2017D-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))



datasetsZeroBiasData = []
das = ""
#datasetsZeroBiasData.append(Dataset('/ZeroBias1/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias2/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias3/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias4/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias5/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias6/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias7/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias8/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias9/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
datasetsZeroBiasData.append(Dataset('/ZeroBias10/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))





#================================================================================================ 
# MC, 94X
#================================================================================================ 
datasetsSignalTB = []
das = ""


datasetsSignalTauNu = []
#datasetsSignalTauNu.append(Dataset('', dataVersion="94Xmc", dasQuery=das))
#datasetsSignalTauNu.append(Dataset('', dataVersion="94Xmc", dasQuery=das))
datasetsSignalTauNu.append(Dataset('/ChargedHiggs_TTToHplusBWB_HplusToTauNu_M-160_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))
datasetsSignalTauNu.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-200_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))
datasetsSignalTauNu.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-500_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))
datasetsSignalTauNu.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-1000_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))


datasetsSingleTop = []
datasetsSingleTop.append(Dataset('/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('', dataVersion="94Xmc", dasQuery=das))


datasetsTop = []
datasetsTop.append(Dataset('/TT_Mtt-700to1000_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTop.append(Dataset('/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))


datasetsTTJets = []
datasetsTTJets.append(Dataset('/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsTTJets_SingleLeptFromT = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=150&instance=prod%2Fglobal&input=dataset%3D%2FTTJets*%2FRunII*PUMoriond17_80X_mcRun2*%2FMINIAODSIM"
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))

datasetsDY = []
das = ""
#datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v7-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das, name="DYJetsToLL_M-50_ext1"))
#datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das, name="DYJetsToLL_M-50_ext2"))
#datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY.append(Dataset('/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY.append(Dataset('/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY.append(Dataset('/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY.append(Dataset('/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))


datasetsDY_HT = []
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsDYJetsToQQ = []


datasetsZprime = []


datasetsWJets = []
datasetsWJets.append(Dataset('/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))


datasetsWJetsToQQ = []


datasetsZJetsToQQ = []


datasetsDiboson = []
datasetsDiboson.append(Dataset('/WW_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDiboson.append(Dataset('/WZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDiboson.append(Dataset('/ZZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDiboson.append(Dataset('/ZZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDiboson.append(Dataset('/WZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDiboson.append(Dataset('/WW_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsDibosonToQQ = []


datasetsQCD = []
datasetsQCD.append(Dataset('/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_80to120_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_120to170_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))



datasetsQCDMuEnriched = []


datasetsQCDbEnriched = []


datasetsQCD_HT_GenJets5 = []


datasetsQCD_HT_BGenFilter = []


datasetsQCD_HT = []


datasetsTTWJetsToQQ = []


datasetsTTTT = []


datasetsTTBB = []


datasetsTTZToQQ = []



datasetsNeutrino = []



#================================================================================================ 
# MC, Trigger Development
#================================================================================================ 
datasetsSignalTauNu_TRGdev = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FChargedHiggs_*%2*%2/RAWAODSIM"
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_TTToHplusBWB_HplusToTauNu_M-80_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_TTToHplusBWB_HplusToTauNu_M-160_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-200_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v2/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-500_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-1000_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))


#================================================================================================ 
# Dataset Grouping
#================================================================================================ 
tauLegDatasets = []
#tauLegDatasets.extend(datasetsZeroBiasData)
tauLegDatasets.extend(datasetsMuonData)
#tauLegDatasets.extend(datasetsDY)
tauLegDatasets.extend(datasetsDY_HT)
#tauLegDatasets.extend(datasetsZprime)
# tauLegDatasets.extend(datasetsWJets_reHLT)
# tauLegDatasets.extend(datasetsQCDMuEnriched_reHLT)
# tauLegDatasets.extend(datasetsH125)

tauLegSingleElectronDatasets = []
tauLegSingleElectronDatasets.extend(datasetsElectronData)

metLegDatasets = []
metLegDatasets.extend(datasetsTauData)
metLegDatasets.extend(datasetsDY)
#metLegDatasets.extend(datasetsTop)
metLegDatasets.extend(datasetsTTJets)
metLegDatasets.extend(datasetsSingleTop)
metLegDatasets.extend(datasetsWJets)
metLegDatasets.extend(datasetsQCD)

l1Datasets = []
l1Datasets.extend(datasetsZeroBiasData)
l1Datasets.extend(datasetsNeutrino)
l1Datasets.extend(datasetsQCD)

signalAnalysisDatasets = []
signalAnalysisDatasets.extend(datasetsTauData)
signalAnalysisDatasets.extend(datasetsDY) 
signalAnalysisDatasets.extend(datasetsTTJets)
#signalAnalysisDatasets.extend(datasetsTop)
signalAnalysisDatasets.extend(datasetsSingleTop)
signalAnalysisDatasets.extend(datasetsWJets)
#signalAnalysisDatasets.extend(datasetsWJetsHT)  
signalAnalysisDatasets.extend(datasetsDiboson)
#signalAnalysisDatasets.extend(datasetsQCD)
signalAnalysisDatasets.extend(datasetsSignalTauNu)
#signalAnalysisDatasets.extend(datasetsSignalTB)
#signalAnalysisDatasets.extend(datasetsSignalTauNu_TRGdev)

#signalAnalysisDatasets.extend(datasetsDY_reHLT)
#signalAnalysisDatasets.extend(datasetsTop_reHLT)
#signalAnalysisDatasets.extend(datasetsWJets_reHLT)
#signalAnalysisDatasets.extend(datasetsDiboson_reHLT)
##signalAnalysisDatasets.extend(datasetsQCD_reHLT)
#signalAnalysisDatasets.extend(datasetsSignalTauNu_reHLT)
##signalAnalysisDatasets.extend(datasetsSignalTB_reHLT)

# Signal Analysis (h2tb)
hplus2tbAnalysisDatasets = []
hplus2tbAnalysisDatasets.extend(datasetsJetHTData)
hplus2tbAnalysisDatasets.extend(datasetsSignalTB)
#hplus2tbAnalysisDatasets.extend(datasetsSignalTB_ext1)
hplus2tbAnalysisDatasets.extend(datasetsTop)
#hplus2tbAnalysisDatasets.extend(datasetsTTJets) #-ve weights
#hplus2tbAnalysisDatasets.extend(datasetsTTJets_SingleLeptFromT)
hplus2tbAnalysisDatasets.extend(datasetsSingleTop)
hplus2tbAnalysisDatasets.extend(datasetsDYJetsToQQ)
hplus2tbAnalysisDatasets.extend(datasetsWJetsToQQ)
# hplus2tbAnalysisDatasets.extend(datasetsZJetsToQQ_reHLT) # PUMoriond17?
hplus2tbAnalysisDatasets.extend(datasetsDibosonToQQ)
# hplus2tbAnalysisDatasets.extend(datasetsQCD)
hplus2tbAnalysisDatasets.extend(datasetsQCD_HT)
hplus2tbAnalysisDatasets.extend(datasetsQCDbEnriched)
hplus2tbAnalysisDatasets.extend(datasetsTTWJetsToQQ)  
hplus2tbAnalysisDatasets.extend(datasetsTTTT) 
# hplus2tbAnalysisDatasets.extend(datasetsTTBB) # PUMoriond17?
hplus2tbAnalysisDatasets.extend(datasetsTTZToQQ)
# hplus2tbAnalysisDatasets.extend(datasetsQCDMuEnriched)
# hplus2tbAnalysisDatasets.extend(datasetsQCD_HT_BGenFilter) 
# hplus2tbAnalysisDatasets.extend(datasetsQCD_HT_GenJets5) 


# Trigger Efficiency (h2tb)
JetTriggersDatasets = []
#JetTriggersDatasets.extend(datasetsJetHTData)  
#JetTriggersDatasets.extend(datasetsMuonData03Feb)
# JetTriggersDatasets.extend(datasetsMuonData17Apr)
#JetTriggersDatasets.extend(datasetsSignalTB) 
JetTriggersDatasets.extend(datasetsTop)
#JetTriggersDatasets.extend(datasetsQCD_HT)   
JetTriggersDatasets.extend(datasetsQCDMuEnriched)

# Top BDT Systematics
TopSystBDTDatasets = []
#TopSystBDTDatasets.extend(datasetsJetHTData_03Feb2017)
TopSystBDTDatasets.extend(datasetsTop)
#TopSystBDTDatasets.extend(datasetsTopSyst)
#TopSystBDTDatasets.extend(datasetsDY)
#TopSystBDTDatasets.extend(datasetsQCD_HT)
#TopSystBDTDatasets.extend(datasetsMuonData03Feb)
#TopSystBDTDatasets.extend(datasetsTTWJetsToLNu)
#TopSystBDTDatasets.extend(datasetsQCDMuEnriched)
#TopSystBDTDatasets.extend(datasetsDiboson)
#TopSystBDTDatasets.extend(datasetsDibosonWW)



#================================================================================================ 
# Class Definition
#================================================================================================ 
class DatasetGroup:
    def __init__(self, analysis):
        self.verbose   = False
        self.analysis  = analysis
        self.GroupDict = {}
        self.CreateGroups()

    def SetVerbose(verbose):
        self.verbose = verbose
        return


    def Verbose(self, msg, printHeader=False):
        '''
        Simple print function. If verbose option is enabled prints, otherwise does nothing.
        '''
        if not self.verbose:
            return
        self.Print(msg, printHeader)
        return


    def Print(self, msg, printHeader=True):
        '''
        Simple print function. If verbose option is enabled prints, otherwise does nothing.
        '''
        fName = __file__.split("/")[-1]
        cName = self.__class__.__name__
        name  = fName + ": " + cName
        if printHeader:
                print "=== ", name
        print "\t", msg
        return


    def CreateGroups(self):
        '''
        Create dataset grouping in a dictionary for easy access.
        '''

        analyses = ["SignalAnalysis", "Hplus2tbAnalysis", "JetTriggers", "TopSystBDT", "TauLeg", "TauLegSingleElectron", "METLeg", "L1Study", "All"]
        if self.analysis not in analyses:
            raise Exception("Unknown analysis \"%s\". Please select one of the following: \"%s" % (self.analysis, "\", \"".join(analyses) + "\".") )

        self.GroupDict["SignalAnalysis"]   = signalAnalysisDatasets
        self.GroupDict["Hplus2tbAnalysis"] = hplus2tbAnalysisDatasets
        self.GroupDict["TauLeg"]           = tauLegDatasets
        self.GroupDict["TauLegSingleElectron"] = tauLegSingleElectronDatasets
        self.GroupDict["METLeg"]           = metLegDatasets
        self.GroupDict["L1Study"]          = l1Datasets
        self.GroupDict["All"]              = signalAnalysisDatasets + hplus2tbAnalysisDatasets + metLegDatasets + metLegDatasets
        """
        self.GroupDict["JetTriggers"]      = JetTriggersDatasets
        self.GroupDict["TopSystBDT"]       = TopSystBDTDatasets
        self.GroupDict["All"]              = signalAnalysisDatasets + hplus2tbAnalysisDatasets + metLegDatasets + metLegDatasets + TopSystBDTDatasets
        """
        return


    def GetDatasetList(self):
        '''
        Return the dataset list according to the analysis name. 
        Uses pre-defined dictionary mapping: analysis->dataset list
        '''
        return self.GroupDict[self.analysis]


    def PrintDatasets(self, printHeader=False):
        '''
        Print all datasets for given analysis
        '''
        datasetList = self.GroupDict[self.analysis]

        if printHeader==True:
            self.Print("The datasets for analysis \"%s\" are:\n\t%s" % (self.analysis, "\n\t".join(str(d.URL) for d in datasetList) ), True)
        else:
            self.Print("\n\t".join(str(d.URL) for d in datasetList), False)
        return
