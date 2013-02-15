import FWCore.ParameterSet.Config as cms

import HiggsAnalysis.HeavyChHiggsToTauNu.HChSignalAnalysisParameters_cff as param
hPlusGlobalElectronVetoFilter = cms.EDFilter("HPlusGlobalElectronVetoFilter",
	ElectronSelections = param.ElectronSelection,
        vertexSrc = cms.InputTag(param.primaryVertexSelection.selectedSrc.value()),
        histogramAmbientLevel = cms.untracked.string("Debug"),
        filter = cms.bool(True),
        eventCounter = param.eventCounter.clone(),
)
