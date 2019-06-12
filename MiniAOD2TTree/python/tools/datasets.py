#lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt"
lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt"
#================================================================================================ 
# Class Definition
#================================================================================================ 
import os

class Dataset:
    def __init__(self, url, dbs="global", dataVersion="94Xmc", dasQuery="", lumiMask=lumiMask, name=""):
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
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTau%2FRun2017*-31Mar2018-*%2FMINIAOD"
datasetsTauData.append(Dataset('/Tau/Run2017B-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_297050-299329_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017B.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017C-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_299368-302029_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017C.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017D-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_302031-302663_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017D.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017E-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_303824-304797_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017E.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017F-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_305040-306460_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017F.txt"))

datasetsJetHTData = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FJetHT%2FRun2017*-31Mar2018-*%2FMINIAOD"
datasetsJetHTData.append(Dataset('/JetHT/Run2017B-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_297050-299329_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017B.txt"))
datasetsJetHTData.append(Dataset('/JetHT/Run2017C-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_299368-302029_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017C.txt"))
datasetsJetHTData.append(Dataset('/JetHT/Run2017D-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_302031-302663_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017D.txt"))
datasetsJetHTData.append(Dataset('/JetHT/Run2017E-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_303824-304797_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017E.txt"))
datasetsJetHTData.append(Dataset('/JetHT/Run2017F-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_305040-306460_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017F.txt"))

datasetsBTagCSVData = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FBTagCSV%2FRun2017*-31Mar2018-*%2FMINIAOD"
datasetsBTagCSVData.append(Dataset('/BTagCSV/Run2017B-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_297050-299329_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017B.txt"))
datasetsBTagCSVData.append(Dataset('/BTagCSV/Run2017C-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_299368-302029_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017C.txt"))
datasetsBTagCSVData.append(Dataset('/BTagCSV/Run2017D-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_302031-302663_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017D.txt"))
datasetsBTagCSVData.append(Dataset('/BTagCSV/Run2017E-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_303824-304797_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017E.txt"))
datasetsBTagCSVData.append(Dataset('/BTagCSV/Run2017F-31Mar2018-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_305040-306460_13TeV_EOY2017ReReco_Collisions17_JSON_v1_Run2017F.txt"))

datasetsMuonData = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FSingleMuon%2FRun2017*-31Mar2018-*%2FMINIAOD"
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
# MC, 92X
#================================================================================================ 
datasetsSignalTB_92X = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FChargedHiggs_HplusTB_HplusToTB_M-*_13TeV_amcatnlo_pythia8%2FRunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v*%2FMINIAODSIM"
datasetsSignalTB_92X.append(Dataset('/ChargedHiggs_HplusTB_HplusToTB_M-200_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM',dataVersion="92Xmc",dasQuery=das))
datasetsSignalTB_92X.append(Dataset('/ChargedHiggs_HplusTB_HplusToTB_M-500_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM',dataVersion="92Xmc",dasQuery=das))
datasetsSignalTB_92X.append(Dataset('/ChargedHiggs_HplusTB_HplusToTB_M-1000_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM',dataVersion="92Xmc",dasQuery=das))

datasetsSignalTauNu = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FChargedHiggs_*_M-*_13TeV_amcatnlo_pythia8%2FRunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v*%2FMINIAODSIM"
#datasetsSignalTauNu.append(Dataset('', dataVersion="94Xmc", dasQuery=das))
#datasetsSignalTauNu.append(Dataset('', dataVersion="94Xmc", dasQuery=das))
datasetsSignalTauNu.append(Dataset('/ChargedHiggs_TTToHplusBWB_HplusToTauNu_M-160_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))
datasetsSignalTauNu.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-200_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))
datasetsSignalTauNu.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-500_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))
datasetsSignalTauNu.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-1000_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))

datasetsTTJets_92X = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8%2FRunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v3%2FMINIAODSIM"
datasetsTTJets_92X.append(Dataset('/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v3/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))

datasetsWJets_92X = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FWJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8%2FRunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v1%2FMINIAODSIM"
datasetsWJets_92X.append(Dataset('/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="92Xmc", dasQuery=das))

#================================================================================================ 
# MC, 94X
#================================================================================================ 
#das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset+dataset%3D%2F*%2FRunIIFall17*12Apr2018*%2FMINIAODSIM+status%3D*"

datasetsTTJets = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTJets*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsTTJets.append(Dataset('/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTJets.append(Dataset('/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsTTJets.append(Dataset('/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsTTJets_HT = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTJets_HT*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsTTJets_HT.append(Dataset('/TTJets_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTJets_HT.append(Dataset('/TTJets_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTJets_HT.append(Dataset('/TTJets_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTJets_HT.append(Dataset('/TTJets_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsTTJets_SingleLeptFromT = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTJets_SingleLept*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromTbar_genMET-150_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromT_genMET-150_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTJets_SingleLeptFromT.append(Dataset('/TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsSingleTop = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FST*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsSingleTop.append(Dataset('/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_s-channel_4f_hadronicDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_t-channel_top_5f_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('/ST_t-channel_top_5f_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsTop = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTT*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsTop.append(Dataset('/TT_Mtt-700to1000_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTop.append(Dataset('/TT_Mtt-1000toInf_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsTop.append(Dataset('/TT_Mtt-1000toInf_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTop.append(Dataset('/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsTop.append(Dataset('/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsTop.append(Dataset('/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsTop.append(Dataset('/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsTopToSemileptonic = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTToSe*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
#datasetsTopToSemileptonic.append(Dataset('/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsTopToSemileptonic.append(Dataset('/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsTopToSemileptonic.append(Dataset('/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopToSemileptonic.append(Dataset('/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsTopToLeptonic = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTTo2L2Nu_TuneCP5_*13TeV_*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
#datasetsTopToLeptonic.append(Dataset("/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
#datasetsTopToLeptonic.append(Dataset("/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
#datasetsTopToLeptonic.append(Dataset("/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTopToLeptonic.append(Dataset("/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTopToLeptonic.append(Dataset("/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))

datasetsTTH = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FttH*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsTTH.append(Dataset("/ttH_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTH.append(Dataset("/ttH_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTH.append(Dataset("/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTH.append(Dataset("/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTH.append(Dataset("/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTH.append(Dataset("/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
#datasetsTTH.append(Dataset("/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
#datasetsTTH.append(Dataset("/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
#datasetsTTH.append(Dataset("/ttHJetTobb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
#datasetsTTH.append(Dataset("/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
#datasetsTTH.append(Dataset("/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))

datasetsTTHToTauTau = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FttH*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsTTHToTauTau.append(Dataset("/ttH_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTHToTauTau.append(Dataset("/ttH_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTHToTauTau.append(Dataset("/ttHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
#datasetsTTHToTauTau.append(Dataset("/ttHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))

datasetsTTGJets = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTGJets*%2FRunIIFall17MiniAODv2-*%2FMINIAODSIM"
datasetsTTGJets.append(Dataset("/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTGJets.append(Dataset("/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTGJets.append(Dataset("/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
datasetsTTGJets.append(Dataset("/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))
#datasetsTTGJets.append(Dataset("/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM", dataVersion="94Xmc", dasQuery=das))

datasetsDY = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FDY*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
#datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsDY_HT = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FDY*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDY_HT.append(Dataset('/DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsDYJetsToQQ = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FDY*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsDYJetsToQQ.append(Dataset('/DYJetsToQQ_HT180_13TeV_TuneCP5-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsZprime = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FZprimeToTauTau*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsZprime.append(Dataset('/ZprimeToTauTau_M-1000_TuneCP5_13TeV-pythia8-tauola/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsZprime.append(Dataset('/ZprimeToTauTau_M-1500_TuneCP5_13TeV-pythia8-tauola/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsZprime.append(Dataset('/ZprimeToTauTau_M-2000_TuneCP5_13TeV-pythia8-tauola/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsZprime.append(Dataset('/ZprimeToTauTau_M-2500_TuneCP5_13TeV-pythia8-tauola/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsZprime.append(Dataset('/ZprimeToTauTau_M-3000_TuneCP5_13TeV-pythia8-tauola/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsZprime.append(Dataset('/ZprimeToTauTau_M-3500_TuneCP5_13TeV-pythia8-tauola/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsZprime.append(Dataset('/ZprimeToTauTau_M-4000_TuneCP5_13TeV-pythia8-tauola/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsZprime.append(Dataset('/ZprimeToTauTau_M-4000_TuneCP5_13TeV-pythia8-tauola/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsWJets = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FWJetsTo*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsWJets.append(Dataset('/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets.append(Dataset('/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets.append(Dataset('/WJetsToLNu_BGenFilter_Wpt-200toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets.append(Dataset('/WJetsToLNu_BGenFilter_Wpt-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsWJets_HT = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FWJetsTo*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsWJets_HT.append(Dataset('/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets_HT.append(Dataset('/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets_HT.append(Dataset('/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets_HT.append(Dataset('/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets_HT.append(Dataset('/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets_HT.append(Dataset('/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets_HT.append(Dataset('/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJets_HT.append(Dataset('/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsWJetsToQQ = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FWJetsToQQ*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsWJetsToQQ.append(Dataset('/WJetsToQQ_HT400to600_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJetsToQQ.append(Dataset('/WJetsToQQ_HT600to800_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsWJetsToQQ.append(Dataset('/WJetsToQQ_HT-800toInf_qc19_3j_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsWJetsToQQ.append(Dataset('/WJetsToQQ_HT400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsWJetsToQQ.append(Dataset('/WJetsToQQ_HT600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsZJetsToQQ = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FZJetsToQQ*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsZJetsToQQ.append(Dataset('/ZJetsToQQ_HT400to600_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsZJetsToQQ.append(Dataset('/ZJetsToQQ_HT600to800_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsZJetsToQQ.append(Dataset('/ZJetsToQQ_HT-800toInf_qc19_4j_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsZJetsToQQ.append(Dataset('/ZJetsToQQ_HT400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsZJetsToQQ.append(Dataset('/ZJetsToQQ_HT600to800_3j_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsZJetsToQQ.append(Dataset('/ZJetsToQQ_HT-800toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsZJetsToQQ.append(Dataset('/ZJetsToQQ_HT600to800_3j_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsDibosonToQQ = []
dasWW = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FWW*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
dasWZ = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FWZ_Tune*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
dasZZ = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FZZ*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsDibosonToQQ.append(Dataset('/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
datasetsDibosonToQQ.append(Dataset('/WZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWZ))
datasetsDibosonToQQ.append(Dataset('/ZZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasZZ))
#datasetsDibosonToQQ.append(Dataset('/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
#datasetsDibosonToQQ.append(Dataset('/WWTo4Q_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
#datasetsDibosonToQQ.append(Dataset('/ZZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasZZ))

datasetsDiboson = []
dasWW = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FWW*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
dasWZ = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FWZ_Tune*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
dasZZ = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FZZ*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsDiboson.append(Dataset('/WW_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
#datasetsDiboson.append(Dataset('/WWTo4Q_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
#datasetsDiboson.append(Dataset('/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
datasetsDiboson.append(Dataset('/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
#datasetsDiboson.append(Dataset('/WWToLNuQQ_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
#datasetsDiboson.append(Dataset('/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
datasetsDiboson.append(Dataset('/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
datasetsDiboson.append(Dataset('/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
#datasetsDiboson.append(Dataset('/WWTo2L2Nu_NNPDF31_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
datasetsDiboson.append(Dataset('/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWW))
datasetsDiboson.append(Dataset('/WZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasWZ))
datasetsDiboson.append(Dataset('/ZZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasZZ))
#datasetsDiboson.append(Dataset('/ZZTo2Q2Nu_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasZZ))
#datasetsDiboson.append(Dataset('/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasZZ))
#datasetsDiboson.append(Dataset('/ZZTo2L2Nu_13TeV_powheg_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=dasZZ))

datasetsQCD = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FQCD_Pt*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsQCD.append(Dataset('/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_15to30_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_80to120_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_80to120_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_120to170_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD.append(Dataset('/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_170to300_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_300to470_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_470to600_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_600to800_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD.append(Dataset('/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_pilot_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD.append(Dataset('/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD.append(Dataset('/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_second_pilot_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsQCDMuEnriched = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FQCD_Pt*MuE*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDMuEnriched.append(Dataset('/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsQCDbEnriched = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FQCD_bE*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT100to200_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT200to300_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT200to300_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT300to500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT300to500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT300to500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT500to700_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT500to700_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT500to700_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCDbEnriched.append(Dataset('/QCD_bEnriched_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsQCD_HT = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FQCD_HT*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsQCD_HT.append(Dataset('/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT.append(Dataset('/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT.append(Dataset('/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD_HT.append(Dataset('/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT.append(Dataset('/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD_HT.append(Dataset('/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT.append(Dataset('/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD_HT.append(Dataset('/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT.append(Dataset('/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD_HT.append(Dataset('/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT.append(Dataset('/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD_HT.append(Dataset('/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT.append(Dataset('/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD_HT.append(Dataset('/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT.append(Dataset('/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD_HT.append(Dataset('/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsQCD_HT_BGenFilter = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FQCD_HT*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT100to200_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT200to300_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT300to500_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT500to700_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT700to1000_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT700to1000_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT1000to1500_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT1500to2000_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT2000toInf_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsQCD_HT_BGenFilter.append(Dataset('/QCD_HT2000toInf_BGenFilter_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsQCD_HT_GenJets5 = []

datasetsTTWJetsToQQ = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTWJetsToQQ*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsTTWJetsToQQ.append(Dataset('/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTWJetsToQQ.append(Dataset('/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsTTTT = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTTT*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
#datasetsTTTT.append(Dataset('/TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTTT.append(Dataset('/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTTT.append(Dataset('/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsTTBB = []

datasetsTTZToQQ = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTTZToQQ*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsTTZToQQ.append(Dataset('/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTTZToQQ.append(Dataset('/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsNeutrino = []

datasetsTopSyst = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FTT*%2FRunIIFall17MiniAODv2-PU2017_12Apr2018*94X*2017*v*%2FMINIAODSIM"
datasetsTopSyst.append(Dataset('/TTToHadronic_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop178p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop178p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop175p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop175p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop171p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop169p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop166p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop166p5_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop166p5_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_mtop166p5_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_TuneCP5up_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_TuneCP5up_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_TuneCP5down_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_TuneCP5down_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsTopSyst.append(Dataset('/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

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
signalAnalysisDatasets.extend(datasetsQCD_HT)
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
## Data 17
hplus2tbAnalysisDatasets.extend(datasetsJetHTData)
hplus2tbAnalysisDatasets.extend(datasetsBTagCSVData)
## Signal 92X
hplus2tbAnalysisDatasets.extend(datasetsSignalTB)
## TT (Mtt, fully hadronic, semileptonic, fully leptonic)
hplus2tbAnalysisDatasets.extend(datasetsTop)
hplus2tbAnalysisDatasets.extend(datasetsTopToSemileptonic)
hplus2tbAnalysisDatasets.extend(datasetsTopToLeptonic)
hplus2tbAnalysisDatasets.extend(datasetsTTJets)
## Backgrounds
hplus2tbAnalysisDatasets.extend(datasetsTTGJets)
hplus2tbAnalysisDatasets.extend(datasetsTTH)
hplus2tbAnalysisDatasets.extend(datasetsTTJets_HT)
hplus2tbAnalysisDatasets.extend(datasetsTTWJetsToQQ)
hplus2tbAnalysisDatasets.extend(datasetsTTZToQQ)
hplus2tbAnalysisDatasets.extend(datasetsTTTT)
hplus2tbAnalysisDatasets.extend(datasetsWJetsToQQ)
hplus2tbAnalysisDatasets.extend(datasetsZJetsToQQ)
hplus2tbAnalysisDatasets.extend(datasetsSingleTop)
hplus2tbAnalysisDatasets.extend(datasetsDibosonToQQ)
hplus2tbAnalysisDatasets.extend(datasetsDYJetsToQQ)
hplus2tbAnalysisDatasets.extend(datasetsQCD_HT)
hplus2tbAnalysisDatasets.extend(datasetsQCD_HT_BGenFilter)
hplus2tbAnalysisDatasets.extend(datasetsQCDbEnriched)

# Trigger Efficiency (h2tb)
JetTriggersDatasets = []
JetTriggersDatasets.extend(datasetsMuonData)
JetTriggersDatasets.extend(datasetsTop)
JetTriggersDatasets.extend(datasetsTopToLeptonic)
JetTriggersDatasets.extend(datasetsTopToSemileptonic)
JetTriggersDatasets.extend(datasetsQCDMuEnriched)
JetTriggersDatasets.extend(datasetsDYJetsToQQ)
JetTriggersDatasets.extend(datasetsWJetsToQQ)

# Top BDT Systematics
TopSystBDTDatasets = []
TopSystBDTDatasets.extend(datasetsTop)
TopSystBDTDatasets.extend(datasetsTopSyst)
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
        self.GroupDict["JetTriggers"]      = JetTriggersDatasets
        """
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
