// -*- c++ -*-
#include "Framework/interface/BaseSelector.h"
#include "Framework/interface/makeTH.h"

#include "EventSelection/interface/CommonPlots.h"
#include "EventSelection/interface/EventSelections.h"

#include "TDirectory.h"

class Hplus2tbAnalysis: public BaseSelector {
public:
  explicit Hplus2tbAnalysis(const ParameterSet& config, const TH1* skimCounters);
  virtual ~Hplus2tbAnalysis() {}

  /// Books histograms
  virtual void book(TDirectory *dir) override;
  /// Sets up branches for reading the TTree
  virtual void setupBranches(BranchManager& branchManager) override;
  /// Called for each event
  virtual void process(Long64_t entry) override;

private:
  // Input parameters
  const DirectionalCut<double> cfg_PrelimTopMVACut;
  const std::string cfg_LdgTopDefinition;

  // Common plots
  CommonPlots fCommonPlots;

  // Event selection classes and event counters (in same order like they are applied)
  Count cAllEvents;
  Count cTrigger;
  METFilterSelection fMETFilterSelection;
  Count cVertexSelection;
  ElectronSelection fElectronSelection;
  MuonSelection fMuonSelection;
  TauSelection fTauSelection;
  JetSelection fJetSelection;
  BJetSelection fBJetSelection;
  Count cBTaggingSFCounter;
  METSelection fMETSelection;
  TopSelectionBDT fTopSelection;
  Count cTopTaggingSFCounter;
  // FatJetSelection fFatJetSelection;
  Count cSelected;
    
  // Non-common histograms
  // WrappedTH1 *hAssociatedTop_Pt;
  // WrappedTH1 *hAssociatedTop_Eta;
};

#include "Framework/interface/SelectorFactory.h"
REGISTER_SELECTOR(Hplus2tbAnalysis);

Hplus2tbAnalysis::Hplus2tbAnalysis(const ParameterSet& config, const TH1* skimCounters)
  : BaseSelector(config, skimCounters),
    cfg_PrelimTopMVACut(config, "FakeBTopSelectionBDT.MVACut"),
    cfg_LdgTopDefinition(config.getParameter<std::string>("FakeBTopSelectionBDT.LdgTopDefinition")),
    fCommonPlots(config.getParameter<ParameterSet>("CommonPlots"), CommonPlots::kHplus2tbAnalysis, fHistoWrapper),
    cAllEvents(fEventCounter.addCounter("all events")),
    cTrigger(fEventCounter.addCounter("passed trigger")),
    fMETFilterSelection(config.getParameter<ParameterSet>("METFilter"), fEventCounter, fHistoWrapper, &fCommonPlots, ""),
    cVertexSelection(fEventCounter.addCounter("passed PV")),
    fElectronSelection(config.getParameter<ParameterSet>("ElectronSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, "Veto"),
    fMuonSelection(config.getParameter<ParameterSet>("MuonSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, "Veto"),
    fTauSelection(config.getParameter<ParameterSet>("TauSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, "Veto"),
    fJetSelection(config.getParameter<ParameterSet>("JetSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, ""),
    fBJetSelection(config.getParameter<ParameterSet>("BJetSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, ""),
    cBTaggingSFCounter(fEventCounter.addCounter("b-tag SF")),
    fMETSelection(config.getParameter<ParameterSet>("METSelection")), // no subcounter in main counter
    fTopSelection(config.getParameter<ParameterSet>("TopSelectionBDT"), fEventCounter, fHistoWrapper, &fCommonPlots, ""),
    cTopTaggingSFCounter(fEventCounter.addCounter("top-tag SF")),
    // fFatJetSelection(config.getParameter<ParameterSet>("FatJetSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, "Veto"),
    cSelected(fEventCounter.addCounter("Selected Events"))
{ }


void Hplus2tbAnalysis::book(TDirectory *dir) {

  if (0) std::cout << "=== Hplus2tbAnalysis::book()" << std::endl;
  // Book common plots histograms
  fCommonPlots.book(dir, isData());

  // Book histograms in event selection classes
  fMETFilterSelection.bookHistograms(dir);
  fElectronSelection.bookHistograms(dir);
  fMuonSelection.bookHistograms(dir);
  fTauSelection.bookHistograms(dir);
  fJetSelection.bookHistograms(dir);
  fBJetSelection.bookHistograms(dir);
  fMETSelection.bookHistograms(dir);
  fTopSelection.bookHistograms(dir);
  // fFatJetSelection.bookHistograms(dir);

  // Book non-common histograms
  // hAssociatedTop_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "associatedTop_Pt", "Associated t pT;p_{T} (GeV/c)", nBinsPt, minPt, maxPt);
  // hAssociatedTop_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "associatedTop_Eta", "Associated t eta;#eta", nBinsEta, minEta, maxEta);
  return;
}


void Hplus2tbAnalysis::setupBranches(BranchManager& branchManager) {
  fEvent.setupBranches(branchManager);
  return;
}


void Hplus2tbAnalysis::process(Long64_t entry) {

  // Sanity check
  if (cfg_LdgTopDefinition != "MVA" &&  cfg_LdgTopDefinition != "Pt")
    {
      throw hplus::Exception("config") << "Unsupported method of defining the leading top (=" << cfg_LdgTopDefinition << "). Please select from \"MVA\" and \"Pt\".";
    }

  //====== Initialize
  fCommonPlots.initialize();
  fCommonPlots.setFactorisationBinForEvent(std::vector<float> {});
  cAllEvents.increment();

  //================================================================================================   
  // 1) Apply trigger 
  //================================================================================================   
  if (0) std::cout << "=== Trigger" << std::endl;
  if ( !(fEvent.passTriggerDecision()) ) return;
  
  cTrigger.increment();
  int nVertices = fEvent.vertexInfo().value();
  fCommonPlots.setNvertices(nVertices);
  fCommonPlots.fillControlPlotsAfterTrigger(fEvent);

  //================================================================================================   
  // 2) MET filters (to remove events with spurious sources of fake MET)
  //================================================================================================   
  if (0) std::cout << "=== MET Filter" << std::endl;
  const METFilterSelection::Data metFilterData = fMETFilterSelection.analyze(fEvent);
  if (!metFilterData.passedSelection()) return;
  fCommonPlots.fillControlPlotsAfterMETFilter(fEvent);  

  //================================================================================================   
  // 3) Primarty Vertex (Check that a PV exists)
  //================================================================================================   
  if (0) std::cout << "=== Vertices" << std::endl;
  if (nVertices < 1) return;
  cVertexSelection.increment();
  fCommonPlots.fillControlPlotsAtVertexSelection(fEvent);
  
  //================================================================================================   
  // 4) Electron veto (Fully hadronic + orthogonality)
  //================================================================================================   
  if (0) std::cout << "=== Electron veto" << std::endl;
  const ElectronSelection::Data eData = fElectronSelection.analyze(fEvent);
  if (eData.hasIdentifiedElectrons()) return;

  //================================================================================================
  // 5) Muon veto (Fully hadronic + orthogonality)
  //================================================================================================
  if (0) std::cout << "=== Muon veto" << std::endl;
  const MuonSelection::Data muData = fMuonSelection.analyze(fEvent);
  if (muData.hasIdentifiedMuons()) return;

  //================================================================================================   
  // 6) Tau Veto (HToTauNu Orthogonality)
  //================================================================================================   
  if (0) std::cout << "=== Tau Veto" << std::endl;
  const TauSelection::Data tauData = fTauSelection.analyze(fEvent);
  if (tauData.hasIdentifiedTaus() ) return;

  //================================================================================================
  // 7) Jet selection
  //================================================================================================
  if (0) std::cout << "=== Jet selection" << std::endl;
  const JetSelection::Data jetData = fJetSelection.analyzeWithoutTau(fEvent);
  if (!jetData.passedSelection()) return;
  fCommonPlots.fillControlPlotsAfterTopologicalSelections(fEvent, true);
 
  //================================================================================================  
  // 8) BJet selection
  //================================================================================================
  if (0) std::cout << "=== BJet selection" << std::endl;
  const BJetSelection::Data bjetData = fBJetSelection.analyze(fEvent, jetData);
  if (!bjetData.passedSelection()) return;
  // fCommonPlots.fillControlPlotsAfterBJetSelection(fEvent, bjetData);

  //================================================================================================  
  // 9) BJet SF  
  //================================================================================================
  if (0) std::cout << "=== BJet SF" << std::endl;
  if (fEvent.isMC()) 
    {
      fEventWeight.multiplyWeight(bjetData.getBTaggingScaleFactorEventWeight());
    }
  cBTaggingSFCounter.increment();

  //================================================================================================
  // - MET selection
  //================================================================================================
  if (0) std::cout << "=== MET selection" << std::endl;
  const METSelection::Data METData = fMETSelection.silentAnalyze(fEvent, nVertices);
  // if (!METData.passedSelection()) return;

  //================================================================================================
  // 11) Top selection
  //================================================================================================
  if (0) std::cout << "=== Top (BDT) selection" << std::endl;
  const TopSelectionBDT::Data topData = fTopSelection.analyze(fEvent, jetData, bjetData);
  bool passPrelimMVACut = false;  
  if (cfg_LdgTopDefinition == "MVA")
    {
      passPrelimMVACut = cfg_PrelimTopMVACut.passedCut( std::min(topData.getMVAmax1(), topData.getMVAmax2()) );
    }
  else
    {
      passPrelimMVACut = cfg_PrelimTopMVACut.passedCut( std::min(topData.getMVALdgInPt(), topData.getMVASubldgInPt()) );
    }
  //if (!passPrelimMVACut) return; // duplicate and thus not needed!  commented out on 27 june 2018
  // NOTE: The two iffs below if removed will cause fillControlPlotsAfterStandardSelections() to crash. 
  // Need to make necessary changes to fillControlPlots..()
  if (!topData.hasFreeBJet()) return;
  if (!passPrelimMVACut) return;

  //================================================================================================
  // PreSelections
  //================================================================================================
  if (0) std::cout << "\n=== PreSelections" << std::endl;
  fCommonPlots.fillControlPlotsAfterStandardSelections(fEvent, jetData, bjetData, METData, QuarkGluonLikelihoodRatio::Data(), topData, bjetData.isGenuineB());  
  
  //================================================================================================
  // All Selections
  //================================================================================================
  if (0) std::cout << "=== All Selections" << std::endl;
  if (topData.getSelectedCleanedTopsMVA().size() != 2) return; // new
  if (!topData.passedSelection()) return;

  if (fEvent.isMC()) 
    {
      fEventWeight.multiplyWeight(topData.getTopTaggingScaleFactorEventWeight());
    }
  cTopTaggingSFCounter.increment();


//  //================================================================================================
//  // *) FatJet veto
//  //================================================================================================
//  if (0) std::cout << "\n=== FatJet veto" << std::endl;
//  const FatJetSelection::Data fatjetData = fFatJetSelection.analyze(fEvent, topData);
//  // const FatJetSelection::Data fatjetData = fFatJetSelection.analyzeWithoutTop(fEvent);
//  // if (fatjetData.fatjetMatchedToTopFound()) return;
//  if (!fatjetData.passedSelection()) return;

  // Increment counters & fill histograms
  cSelected.increment();


  //================================================================================================
  // Fill final plots
  //===============================================================================================
  int isGenuineB = bjetData.isGenuineB();
  fCommonPlots.fillControlPlotsAfterAllSelections(fEvent, isGenuineB);
 
  //================================================================================================
  // Finalize
  //================================================================================================
  fEventSaver.save();

  return;
}
