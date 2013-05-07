#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/QCDMeasurementFactorised.h"
#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/TransverseMass.h"
#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/DeltaPhi.h"

#include "TNamed.h"
#include <iomanip>
#include <sstream>

namespace HPlus {
  QCDMeasurementFactorised::QCDFactorisedHistogramHandler::QCDFactorisedHistogramHandler(const edm::ParameterSet& iConfig, HistoWrapper& histoWrapper) :
    fHistoWrapper(histoWrapper),
    fTauPtBinLowEdges(iConfig.getUntrackedParameter<std::vector<double> >("factorisationTauPtBinLowEdges")),
    fTauEtaBinLowEdges(iConfig.getUntrackedParameter<std::vector<double> >("factorisationTauEtaBinLowEdges")),
    fNVerticesBinLowEdges(iConfig.getUntrackedParameter<std::vector<int> >("factorisationNVerticesBinLowEdges")),
    fTransverseMassRange(iConfig.getUntrackedParameter<std::vector<double> >("factorisationTransverseMassRange")),
    fFullMassRange(iConfig.getUntrackedParameter<std::vector<double> >("factorisationFullMassRange")),
    fNUnfoldedBins((static_cast<int>(fTauPtBinLowEdges.size()) + 1) *
                   (static_cast<int>(fTauEtaBinLowEdges.size()) + 1) *
                   (static_cast<int>(fNVerticesBinLowEdges.size()) + 1)) {
    // Create transverse mass bins
    if (fTransverseMassRange.size() != 3)
      throw cms::Exception("Configuration") << "QCDMeasurementFactorised: need to provide config param. factorisationTransverseMassRange = (nbins, min, max)!";
    double myDelta = (fTransverseMassRange[2]-fTransverseMassRange[1]) / fTransverseMassRange[0];
    for (double i = 0; i < fTransverseMassRange[0]; ++i) {
      fTransverseMassBinLowEdges.push_back(i * myDelta);
    }
    // Create full mass bins
    if (fFullMassRange.size() != 3)
      throw cms::Exception("Configuration") << "QCDMeasurementFactorised: need to provide config param. factorisationFullMassRange = (nbins, min, max)!";
    myDelta = (fFullMassRange[2]-fFullMassRange[1]) / fFullMassRange[0];
    for (double i = 0; i < fFullMassRange[0]; ++i) {
      fFullMassRange.push_back(i * myDelta);
    }
    initialize();
    // Set string for binning
    std::stringstream s;
    s << "TauPt:" << fTauPtBinLowEdges.size()+1 << ":TauEta:" << fTauEtaBinLowEdges.size()+1 << ":Nvtx:" << fNVerticesBinLowEdges.size()+1 << ":";
    fBinningString = s.str();
  }

  QCDMeasurementFactorised::QCDFactorisedHistogramHandler::~QCDFactorisedHistogramHandler() { }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::initialize() {
    fCurrentBinX = 9999;
    fCurrentBinY = 9999;
    fCurrentBinZ = 9999;
    fCurrentUnfoldedBin = 9999;
  }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::setFactorisationBinForEvent(double pt, double eta, int nvtx) {
    fCurrentBinX = getTauPtBinIndex(pt);
    fCurrentBinY = getTauEtaBinIndex(eta);
    fCurrentBinZ = getNVerticesBinIndex(nvtx);
    fCurrentUnfoldedBin = getShapeBinIndex(fCurrentBinX, fCurrentBinY, fCurrentBinZ);
  }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::createCountHistogram(TFileDirectory& fdir, WrappedUnfoldedFactorisationHisto*& unfoldedHisto, std::string title) {
    // x-axis contains count (just one bin; underflow and overflow bins do not contain information), y-axis contains unfolded factorisation bins
    // Create histo
    std::string s = fBinningString+title;
    unfoldedHisto = fHistoWrapper.makeTH<TH2F>(fNUnfoldedBins, HistoWrapper::kVital, fdir, title.c_str(), s.c_str(), 1, 0., 1.);
    // Set labels to y-axis
    setAxisLabelsForUnfoldedHisto(unfoldedHisto);
  }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::createShapeHistogram(TFileDirectory& fdir, WrappedUnfoldedFactorisationHisto*& unfoldedHisto, std::string title, std::string label, int nbins, double min, double max) {
    // x-axis contains distribution, y-axis contains unfolded factorisation bins (including under- and overflows)
    // Create histo
    std::string s = fBinningString+title+";"+label;
    unfoldedHisto = fHistoWrapper.makeTH<TH2F>(fNUnfoldedBins, HistoWrapper::kVital, fdir, title.c_str(), s.c_str(), nbins, min, max);
    // Set labels to y-axis
    setAxisLabelsForUnfoldedHisto(unfoldedHisto);
  }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::fillNeventHistogram(WrappedUnfoldedFactorisationHisto* h) {
    checkProperBinning();
    h->Fill(0., fCurrentUnfoldedBin);
    //std::cout << "Filling count " << h->getHisto()->GetTitle() << " current bin=" << fCurrentUnfoldedBin << std::endl;
  }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::fillNeventHistogram(WrappedUnfoldedFactorisationHisto* h, double weight) {
    checkProperBinning();
    h->Fill(0., fCurrentUnfoldedBin, weight);
  }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::fillShapeHistogram(WrappedUnfoldedFactorisationHisto* h, double value) {
    checkProperBinning();
    h->Fill(value, fCurrentUnfoldedBin);
    //std::cout << "Filling shape " << h->getHisto()->GetTitle() << " current bin=" << fCurrentUnfoldedBin << std::endl;
  }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::fillShapeHistogram(WrappedUnfoldedFactorisationHisto* h, double value, double weight) {
    checkProperBinning();
    h->Fill(value, fCurrentUnfoldedBin, weight);
  }

  // Returns index to tau pT bin; 0 is underflow and size() is highest bin
  int QCDMeasurementFactorised::QCDFactorisedHistogramHandler::getTauPtBinIndex(double pt) {
    size_t mySize = fTauPtBinLowEdges.size();
    for (size_t i = 0; i < mySize; ++i) {
      if (pt < fTauPtBinLowEdges[i])
        return static_cast<int>(i);
    }
    return static_cast<int>(mySize);
  }

  int QCDMeasurementFactorised::QCDFactorisedHistogramHandler::getTauEtaBinIndex(double eta) {
    size_t mySize = fTauEtaBinLowEdges.size();
    for (size_t i = 0; i < mySize; ++i) {
      if (eta < fTauEtaBinLowEdges[i])
        return static_cast<int>(i);
    }
    return static_cast<int>(mySize);
  }

  int QCDMeasurementFactorised::QCDFactorisedHistogramHandler::getNVerticesBinIndex(int nvtx) {
    size_t mySize = fNVerticesBinLowEdges.size();
    for (size_t i = 0; i < mySize; ++i) {
      if (nvtx < fNVerticesBinLowEdges[i])
        return static_cast<int>(i);
    }
    return static_cast<int>(mySize);
  }

  int QCDMeasurementFactorised::QCDFactorisedHistogramHandler::getMtBinIndex(double mt) {
    size_t mySize = fTransverseMassRange.size();
    for (size_t i = 0; i < mySize; ++i) {
      if (mt < fTransverseMassRange[i])
        return static_cast<int>(i);
    }
    return static_cast<int>(mySize);
  }

  int QCDMeasurementFactorised::QCDFactorisedHistogramHandler::getFullMassBinIndex(double mass) {
    size_t mySize = fFullMassRange.size();
    for (size_t i = 0; i < mySize; ++i) {
      if (mass < fFullMassRange[i])
        return static_cast<int>(i);
    }
    return static_cast<int>(mySize);
  }

  int QCDMeasurementFactorised::QCDFactorisedHistogramHandler::getShapeBinIndex(int tauPtBin, int tauEtaBin, int nvtxBin) {
    int myTauPtBins = static_cast<int>(fTauPtBinLowEdges.size()) + 1;
    int myTauEtaBins = static_cast<int>(fTauEtaBinLowEdges.size()) + 1;
    //int myNVerticesBins = static_cast<int>(fNVerticesBinLowEdges.size()) + 1;
    //std::cout << " bin=" << tauPtBin << " taueta=" << tauEtaBin << " nvtx=" << nvtxBin << std::endl;
    //std::cout << "total index=" << nvtxBin + tauEtaBin*myNVerticesBins + tauPtBin*myNVerticesBins*myTauEtaBins << endl;
    return tauPtBin + tauEtaBin*myTauPtBins + nvtxBin*myTauPtBins*myTauEtaBins;
  }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::setAxisLabelsForUnfoldedHisto(WrappedUnfoldedFactorisationHisto* h) {
    if (!h->isActive()) return;
    int myTauPtBins = static_cast<int>(fTauPtBinLowEdges.size()) + 1;
    int myTauEtaBins = static_cast<int>(fTauEtaBinLowEdges.size()) + 1;
    int myNVerticesBins = static_cast<int>(fNVerticesBinLowEdges.size()) + 1;
    for (int k = 0; k < myNVerticesBins; ++k) {
      for (int j = 0; j < myTauEtaBins; ++j) {
        for (int i = 0; i < myTauPtBins; ++i) {
          std::stringstream s;
          // tau pT
          if (i == 0)
            s << "#tau pT<" << static_cast<int>(fTauPtBinLowEdges[0]);
          else if (i == myTauPtBins - 1)
            s << "#tau pT>" << static_cast<int>(fTauPtBinLowEdges[fTauPtBinLowEdges.size()-1]);
          else
            s << "#tau pT=" << static_cast<int>(fTauPtBinLowEdges[i-1]) << ".." << static_cast<int>(fTauPtBinLowEdges[i]);
          s << "/";
          // tau eta
          if (j == 0)
            s << "#tau eta<" << setprecision(2) << fTauEtaBinLowEdges[0];
          else if (j == myTauEtaBins - 1)
            s << "#tau eta>" << setprecision(2) << fTauEtaBinLowEdges[fTauEtaBinLowEdges.size()-1];
          else
            s << "#tau eta=" << setprecision(2) << fTauEtaBinLowEdges[j-1] << ".." << setprecision(2) << fTauEtaBinLowEdges[j];
          s << "/";
          // Nvertices
          if (k == 0)
            s << "N_{vtx}<" << static_cast<int>(fNVerticesBinLowEdges[0]);
          else if (k == myNVerticesBins - 1)
            s << "N_{vtx}>" << static_cast<int>(fNVerticesBinLowEdges[fNVerticesBinLowEdges.size()-1]);
          else
            s << "N_{vtx}=" << static_cast<int>(fNVerticesBinLowEdges[k-1]) << ".." << static_cast<int>(fNVerticesBinLowEdges[k]);
          h->getHisto()->GetYaxis()->SetBinLabel(getShapeBinIndex(i,j,k)+1,s.str().c_str());
        }
      }
    }
  }

  void QCDMeasurementFactorised::QCDFactorisedHistogramHandler::checkProperBinning() {
    if (fCurrentBinX == 9999 || fCurrentBinY == 9999 || fCurrentBinZ == 9999 || fCurrentUnfoldedBin == 9999)
      throw cms::Exception("Logic") << "QCDMeasurementFactorised: need to call QCDFactorisedHistogramHandler::setFactorisationBinForEvent() for the event! Check your code!";
  }

  // ----- End of QCDFactorisedHistogramHandler implementation -----

  QCDMeasurementFactorised::QCDMeasurementFactorised(const edm::ParameterSet& iConfig, EventCounter& eventCounter, EventWeight& eventWeight, HistoWrapper& histoWrapper):
    fEventWeight(eventWeight),
    fHistoWrapper(histoWrapper),
    // Input parameters
    fDeltaPhiCutValue(iConfig.getUntrackedParameter<double>("deltaPhiTauMET")),
    fTopRecoName(iConfig.getUntrackedParameter<std::string>("topReconstruction")),
    fApplyNprongsCutForTauCandidate(iConfig.getUntrackedParameter<bool>("applyNprongsCutForTauCandidate")),
    fApplyRtauCutForTauCandidate(iConfig.getUntrackedParameter<bool>("applyRtauCutForTauCandidate")),
    fDoAnalysisVariationWithTraditionalMethod(iConfig.getUntrackedParameter<bool>("doAnalysisVariationWithTraditionalMethod")),
    fDoAnalysisVariationWithABCDMethod(iConfig.getUntrackedParameter<bool>("doAnalysisVariationWithABCDMethod")),
    fDoAnalysisVariationWithDoubleABCDMethod(iConfig.getUntrackedParameter<bool>("doAnalysisVariationWithDoubleABCDMethod")),
    // Counters - do not change order
    fAllCounter(eventCounter.addCounter("Offline selection begins")),
    fWJetsWeightCounter(eventCounter.addCounter("WJets inc+exl weight")),
    fMETFiltersCounter(eventCounter.addCounter("MET filters")),
    fTriggerCounter(eventCounter.addCounter("Trigger and HLT_MET")),
    fPrimaryVertexCounter(eventCounter.addCounter("PrimaryVertex")),
    fTausExistAfterCandidateSelectionCounter(eventCounter.addCounter("TauCandidate selection")),
    fTausExistAfterNprongsCutCounter(eventCounter.addCounter("TauCand+Nprong")),
    fTausExistAfterRtauCutCounter(eventCounter.addCounter("TauCand+Rtau")),
    fMultipleTausAfterTauSelection(eventCounter.addCounter("Multiple tau candidates exist")),
    fTausAfterScaleFactorsCounter(eventCounter.addCounter("Tau after scale factors")),
    fVetoTauCounter(eventCounter.addCounter("Killed by VetoTauSelection")),
    fElectronVetoCounter(eventCounter.addCounter("ElectronSelection")),
    fMuonVetoCounter(eventCounter.addCounter("MuonSelection")),
    fNJetsCounter(eventCounter.addCounter("JetSelection")),
    fMETTriggerScaleFactorCounter(eventCounter.addCounter("Trg MET scale factor")),
    fStandardSelectionsCounter(eventCounter.addCounter("Selected after std. selections")),
    fStandardSelectionsWithMET30Counter(eventCounter.addCounter("Selected after std. selections and MET30")),
    fStandardSelectionsWithTailKillerCounter(eventCounter.addCounter("Selected after std. selections and tail killer")),
    fStandardSelectionsWithTailKillerAndMET30Counter(eventCounter.addCounter("Selected after std. selections and MET30 and tail killer")),
    /*fFullTauIDCounter(eventCounter.addCounter("FullTauIDCounter")),
    fMETCounter(eventCounter.addCounter("MET")),
    fBTaggingCounter(eventCounter.addCounter("bTagging")),
    fBTaggingScaleFactorCounter(eventCounter.addCounter("btag scale factor")),
    fQCDTailKillerCounter(eventCounter.addCounter("QCD tail killer")),
    fDeltaPhiTauMETCounter(eventCounter.addCounter("DeltaPhiTauMET")),
    fMaxDeltaPhiJetMETCounter(eventCounter.addCounter("maxDeltaPhiJetMET")),
    fTopSelectionCounter(eventCounter.addCounter("top selection")),
    fCoincidenceAfterMETCounter(eventCounter.addCounter("coincidence after MET")),
    fCoincidenceAfterBjetsCounter(eventCounter.addCounter("coincidence after Btag")),
    fCoincidenceAfterDeltaPhiCounter(eventCounter.addCounter("coincidence after Delta phi")),
    fCoincidenceAfterSelectionCounter(eventCounter.addCounter("coincidence after full selection")),*/
    fTriggerSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("trigger"), eventCounter, fHistoWrapper),
    fPrimaryVertexSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("primaryVertexSelection"), eventCounter, fHistoWrapper),
    fTauSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("tauSelection"), eventCounter, fHistoWrapper),
    fVetoTauSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("vetoTauSelection"),
                      iConfig.getUntrackedParameter<edm::ParameterSet>("fakeTauSFandSystematics"),
                      eventCounter, fHistoWrapper),
    fElectronSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("ElectronSelection"), fPrimaryVertexSelection.getSelectedSrc(), eventCounter, fHistoWrapper),
    fMuonSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("MuonSelection"), eventCounter, fHistoWrapper),
    fJetSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("jetSelection"), eventCounter, fHistoWrapper),
    fMETSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("MET"), eventCounter, fHistoWrapper, "MET"),
    fBTagging(iConfig.getUntrackedParameter<edm::ParameterSet>("bTagging"), eventCounter, fHistoWrapper),
    fTopSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("topSelection"), eventCounter, fHistoWrapper),
    fTopChiSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("topChiSelection"), eventCounter, fHistoWrapper),
    fTopWithBSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("topWithBSelection"), eventCounter, fHistoWrapper),
    fTopWithWSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("topWithWSelection"), eventCounter, fHistoWrapper),
    fBjetSelection(iConfig.getUntrackedParameter<edm::ParameterSet>("bjetSelection"), eventCounter, fHistoWrapper),
    fFullHiggsMassCalculator(eventCounter, fHistoWrapper),
    fGenparticleAnalysis(iConfig.getUntrackedParameter<edm::ParameterSet>("GenParticleAnalysis"), eventCounter, fHistoWrapper),
    //fForwardJetVeto(iConfig.getUntrackedParameter<edm::ParameterSet>("forwardJetVeto"), eventCounter, fHistoWrapper),
    fEvtTopology(iConfig.getUntrackedParameter<edm::ParameterSet>("EvtTopology"), eventCounter, fHistoWrapper),
    fTauTriggerEfficiencyScaleFactor(iConfig.getUntrackedParameter<edm::ParameterSet>("tauTriggerEfficiencyScaleFactor"), fHistoWrapper),
    fMETTriggerEfficiencyScaleFactor(iConfig.getUntrackedParameter<edm::ParameterSet>("metTriggerEfficiencyScaleFactor"), fHistoWrapper),
    fPrescaleWeightReader(iConfig.getUntrackedParameter<edm::ParameterSet>("prescaleWeightReader"), fHistoWrapper, "PrescaleWeight"),
    fPileupWeightReader(iConfig.getUntrackedParameter<edm::ParameterSet>("pileupWeightReader"), fHistoWrapper, "PileupWeight"),
    fWJetsWeightReader(iConfig.getUntrackedParameter<edm::ParameterSet>("wjetsWeightReader"), fHistoWrapper, "WJetsWeight"),
    fFakeTauIdentifier(iConfig.getUntrackedParameter<edm::ParameterSet>("fakeTauSFandSystematics"), fHistoWrapper, "TauCandidates"),
    fMETFilters(iConfig.getUntrackedParameter<edm::ParameterSet>("metFilters"), eventCounter),
    fQCDTailKiller(iConfig.getUntrackedParameter<edm::ParameterSet>("QCDTailKiller"), eventCounter, fHistoWrapper),
    fTree(iConfig.getUntrackedParameter<edm::ParameterSet>("Tree"), fBTagging.getDiscriminator()),
    fCommonPlots(eventCounter, fHistoWrapper),
    fQCDFactorisedHistogramHandler(iConfig, fHistoWrapper),
    //fCommonPlotsAfterTrigger(fCommonPlots.createCommonPlotsFilledAtEveryStep("Trigger",true,"Trigger")),
    //fCommonPlotsAfterVertexSelection(fCommonPlots.createCommonPlotsFilledAtEveryStep("VertexSelection",false,"Vtx")),
    fCommonPlotsAfterTauSelection(fCommonPlots.createCommonPlotsFilledAtEveryStep("TauSelection",false,"TauID")),
    fCommonPlotsAfterTauWeight(fCommonPlots.createCommonPlotsFilledAtEveryStep("TauWeight",true,"Tau")),
    fCommonPlotsAfterElectronVeto(fCommonPlots.createCommonPlotsFilledAtEveryStep("ElectronVeto",true,"e veto")),
    fCommonPlotsAfterMuonVeto(fCommonPlots.createCommonPlotsFilledAtEveryStep("MuonVeto",true,"#mu veto")),
    fCommonPlotsAfterJetSelection(fCommonPlots.createCommonPlotsFilledAtEveryStep("JetSelection",true,"#geq3j")),
    fCommonPlotsAfterMETScaleFactor(fCommonPlots.createCommonPlotsFilledAtEveryStep("MET scale factor",true,"E_{T}^{miss} scale factor"))
  {
    edm::Service<TFileService> fs;
    // Save the module configuration to the output ROOT file as a TNamed object
    fs->make<TNamed>("parameterSet", iConfig.dump().c_str());

    // Book histograms
    hVerticesBeforeWeight = fHistoWrapper.makeTH<TH1F>(HistoWrapper::kVital, *fs, "verticesBeforeWeight", "Number of vertices without weighting;Vertices;N_{events} / 1 Vertex", 50, 0, 50);
    hVerticesAfterWeight = fHistoWrapper.makeTH<TH1F>(HistoWrapper::kVital, *fs, "verticesAfterWeight", "Number of vertices with weighting; Vertices;N_{events} / 1 Vertex", 50, 0, 50);
    hVerticesTriggeredBeforeWeight = fHistoWrapper.makeTH<TH1F>(HistoWrapper::kInformative, *fs, "verticesTriggeredBeforeWeight", "Number of vertices triggered without weighting;Vertices;N_{events} / 1 Vertex", 50, 0, 50);
    hVerticesTriggeredAfterWeight = fHistoWrapper.makeTH<TH1F>(HistoWrapper::kInformative, *fs, "verticesTriggeredAfterWeight", "Number of vertices triggered with weighting; Vertices;N_{events} / 1 Vertex", 50, 0, 50);

    // Selection flow histogram
    hSelectionFlow = fHistoWrapper.makeTH<TH1F>(HistoWrapper::kVital, *fs, "QCD_SelectionFlow", "QCD_SelectionFlow;;N_{events}", 12, 0, 12);
    hSelectionFlow->GetXaxis()->SetBinLabel(1+kQCDOrderTrigger,"Trigger");
    hSelectionFlow->GetXaxis()->SetBinLabel(1+kQCDOrderTauCandidateSelection,"#tau cand.");
    hSelectionFlow->GetXaxis()->SetBinLabel(1+kQCDOrderElectronVeto,"Isol. e veto");
    hSelectionFlow->GetXaxis()->SetBinLabel(1+kQCDOrderMuonVeto,"Isol. #mu veto");
    hSelectionFlow->GetXaxis()->SetBinLabel(1+kQCDOrderJetSelection,"N_{jets}");

    // Factorisation histograms are inside the nested variation class

    // Tree
    fTree.enableNonIsoLeptons(true);
    fTree.init(*fs);

    // Measurement variations
    if (fDoAnalysisVariationWithTraditionalMethod) {
      fVariationTraditionalReference = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedTraditional, "TradReference");
      fVariationTraditionalPlusMET30 = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedTraditional, "TradPlusMET30");
      fVariationTraditionalPlusTailKiller = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedTraditional, "TradPlusTailKiller");
      fVariationTraditionalPlusMET30AndTailKiller = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedTraditional, "TradPlusMET30TailKiller");
      fVariationTraditionalPlusCollinearTailKiller = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedTraditional, "TradPlusCollinearTailKiller");
      fVariationTraditionalPlusMET30AndCollinearTailKiller = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedTraditional, "TradPlusMET30CollinearTailKiller");
    }
    if (fDoAnalysisVariationWithABCDMethod) {
      fVariationABCDReference = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedABCD, "ABCDReference");
      fVariationABCDPlusMET30 = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedABCD, "ABCDPlusMET30");
      fVariationABCDPlusTailKiller = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedABCD, "ABCDPlusTailKiller");
      fVariationABCDPlusMET30AndTailKiller = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedABCD, "ABCDPlusMET30TailKiller");
      fVariationABCDPlusCollinearTailKiller = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedABCD, "ABCDPlusCollinearTailKiller");
      fVariationABCDPlusMET30AndCollinearTailKiller = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                                  kQCDFactorisedABCD, "ABCDPlusMET30CollinearTailKiller");
    }
    if (fDoAnalysisVariationWithDoubleABCDMethod) {
      fVariationDoubleABCD = new QCDFactorisedVariation(fs, &fQCDFactorisedHistogramHandler, eventCounter, fCommonPlots,
                                                        kQCDFactorisedDoubleABCD, "DoubleABCD");
    }

    TFileDirectory myDir = fs->mkdir("tests");
    fCollinearSystemJetsFakingTauGenuineTaus = new JetDetailHistograms(fHistoWrapper, myDir, "CollinearSystemJetsFakingTauGenuineTaus", true);
    fCollinearSystemJetsFakingTauFakeTaus = new JetDetailHistograms(fHistoWrapper, myDir, "CollinearSystemJetsFakingTauFakeTaus", true);
    fCollinearSystemJetsOppositeToTau = new JetDetailHistograms(fHistoWrapper, myDir, "CollinearSystemJetsOppositeToTau", true);
  }

  QCDMeasurementFactorised::~QCDMeasurementFactorised() {}

  bool QCDMeasurementFactorised::filter(edm::Event& iEvent, const edm::EventSetup& iSetup) {
    fQCDFactorisedHistogramHandler.initialize();

//------ Read the prescale for the event and set the event weight as the prescale
    fEventWeight.beginEvent();
    const double prescaleWeight = fPrescaleWeightReader.getWeight(iEvent, iSetup);
    fEventWeight.multiplyWeight(prescaleWeight);
    fTree.setPrescaleWeight(prescaleWeight);


//------ Vertex weight
    double myWeightBeforePileupReweighting = fEventWeight.getWeight();
    if(!iEvent.isRealData()) {
      const double myPileupWeight = fPileupWeightReader.getWeight(iEvent, iSetup);
      fEventWeight.multiplyWeight(myPileupWeight);
      fTree.setPileupWeight(myPileupWeight);
    }

    VertexSelection::Data pvData = fPrimaryVertexSelection.analyze(iEvent, iSetup);
    size_t nVertices = pvData.getNumberOfAllVertices();
    hVerticesBeforeWeight->Fill(nVertices, myWeightBeforePileupReweighting);
    hVerticesAfterWeight->Fill(nVertices);
    fTree.setNvertices(nVertices);
    increment(fAllCounter);


//------ For combining W+Jets inclusive and exclusive samples, do an event weighting here
    if(!iEvent.isRealData()) {
      const double wjetsWeight = fWJetsWeightReader.getWeight(iEvent, iSetup);
      fEventWeight.multiplyWeight(wjetsWeight);
    }
    increment(fWJetsWeightCounter);


//------ MET (noise) filters for data (reject events with instrumental fake MET)
    if(iEvent.isRealData()) {
      if(!fMETFilters.passedEvent(iEvent, iSetup)) return false;
    }
    increment(fMETFiltersCounter);


//------ Apply trigger and HLT_MET cut or trigger parametrisation
    const TriggerSelection::Data triggerData = fTriggerSelection.analyze(iEvent, iSetup);
    if (!triggerData.passedEvent()) return false;
    increment(fTriggerCounter);
    //fCommonPlotsAfterTrigger->fill();
    hSelectionFlow->Fill(kQCDOrderTrigger);
    if(triggerData.hasTriggerPath()) // protection if TriggerSelection is disabled
      fTree.setHltTaus(triggerData.getTriggerTaus());

    hVerticesTriggeredBeforeWeight->Fill(nVertices, myWeightBeforePileupReweighting);
    hVerticesTriggeredAfterWeight->Fill(nVertices);


//------ GenParticle analysis (must be done here when we effectively trigger all MC)
    if (!iEvent.isRealData()) {
      GenParticleAnalysis::Data genData = fGenparticleAnalysis.analyze(iEvent, iSetup);
      fTree.setGenMET(genData.getGenMET());
    }


//------ Primary vertex selection
    if (!pvData.passedEvent()) return false;
    increment(fPrimaryVertexCounter);
    //fCommonPlotsAfterVertexSelection->fill();
    //fCommonPlots.fillControlPlots(iEvent, pvData);


//------ Tau candidate selection
    // Do tau candidate selection
    TauSelection::Data tauCandidateDataTmp = fTauSelection.analyze(iEvent, iSetup, pvData.getSelectedVertex()->z());
    if (!tauCandidateDataTmp.passedEvent()) return false;
    increment(fTausExistAfterCandidateSelectionCounter);
    edm::PtrVector<pat::Tau> mySelectedTauList = tauCandidateDataTmp.getSelectedTausBeforeIsolation();
    // Apply nprongs if requested
    if (fApplyNprongsCutForTauCandidate) {
      edm::PtrVector<pat::Tau> myTmpVector;
      for (edm::PtrVector<pat::Tau>::iterator iTau = mySelectedTauList.begin(); iTau != mySelectedTauList.end(); ++iTau) {
        if (fTauSelection.getPassesNProngsStatusOfTauObject(*iTau))
          myTmpVector.push_back(*iTau);
      }
      mySelectedTauList = myTmpVector;
      myTmpVector.clear();
      if (!mySelectedTauList.size()) return false;
    }
    increment(fTausExistAfterNprongsCutCounter);
    // Apply Rtau cut if requested
    if (fApplyRtauCutForTauCandidate) {
      edm::PtrVector<pat::Tau> myTmpVector;
      for (edm::PtrVector<pat::Tau>::iterator iTau = mySelectedTauList.begin(); iTau != mySelectedTauList.end(); ++iTau) {
        if (fTauSelection.getPassesRtauStatusOfTauObject(*iTau))
          myTmpVector.push_back(*iTau);
      }
      mySelectedTauList = myTmpVector;
      myTmpVector.clear();
      if (!mySelectedTauList.size()) return false;
    }
    increment(fTausExistAfterRtauCutCounter);
    if (mySelectedTauList.size() > 1)
      increment(fMultipleTausAfterTauSelection);
    // Dirty hack to make code crash if tauCandidateData.getSelectedTau() is called
    const_cast<TauSelection::Data*>(&tauCandidateDataTmp)->invalidate();
    // Important NOTE: Beyond this line, use only 'mySelectedTau' as the tau object
    edm::Ptr<pat::Tau> mySelectedTau = fTauSelection.selectMostLikelyTau(mySelectedTauList, pvData.getSelectedVertex()->z());
    TauSelection::Data tauCandidateData = fTauSelection.setSelectedTau(mySelectedTau, true);
    fCommonPlots.initialize(iEvent, iSetup, pvData, tauCandidateData, fFakeTauIdentifier, fElectronSelection, fMuonSelection, fJetSelection, fMETSelection, fBTagging, fTopChiSelection, fEvtTopology);
    // Obtain MC matching - for EWK without genuine taus
    FakeTauIdentifier::Data tauMatchData = fFakeTauIdentifier.matchTauToMC(iEvent, *(mySelectedTau));
    // note: do not require here that only one tau has been found (mySelectedTau is the selected tau in the event)
    fCommonPlotsAfterTauSelection->fill();
    // Set factorisation bin
    fQCDFactorisedHistogramHandler.setFactorisationBinForEvent(mySelectedTau->pt(), mySelectedTau->eta(), nVertices);

//------ Scale factors for tau fakes and for tau trigger
    // Apply scale factor for fake tau
    double myFakeTauScaleFactor = 1.0;
    if (!iEvent.isRealData()) {
      myFakeTauScaleFactor = fFakeTauIdentifier.getFakeTauScaleFactor(tauMatchData.getTauMatchType(), mySelectedTau->eta());
      fEventWeight.multiplyWeight(myFakeTauScaleFactor);
    }
    fTree.setTauFakeWeight(myFakeTauScaleFactor, fFakeTauIdentifier.getFakeTauSystematics(tauMatchData.getTauMatchType(), mySelectedTau->eta()));
    // Apply scale factor tau part of trigger
    const TauTriggerEfficiencyScaleFactor::Data tauTriggerWeightData = fTauTriggerEfficiencyScaleFactor.applyEventWeight(*(mySelectedTau), iEvent.isRealData(), fEventWeight);
    fTree.setTauTriggerWeight(tauTriggerWeightData.getEventWeight(), tauTriggerWeightData.getEventWeightAbsoluteUncertainty());
    increment(fTausAfterScaleFactorsCounter);
    hSelectionFlow->Fill(kQCDOrderTauCandidateSelection);
    fCommonPlotsAfterTauWeight->fill();


//------ Veto against second tau in event
    const VetoTauSelection::Data vetoTauData = fVetoTauSelection.analyze(iEvent, iSetup, mySelectedTau, pvData.getSelectedVertex()->z());
    //    if (vetoTauData.passedEvent()) return false;
    if (!vetoTauData.passedEvent()) increment(fVetoTauCounter);
    // Note: no return statement should be added here


//------ Global electron veto
    const ElectronSelection::Data electronData = fElectronSelection.analyze(iEvent, iSetup);
    if (!electronData.passedEvent()) return false;
    increment(fElectronVetoCounter);
    fCommonPlotsAfterElectronVeto->fill();
    hSelectionFlow->Fill(kQCDOrderElectronVeto);
    /*NonIsolatedElectronVeto::Data nonIsolatedElectronVetoData = fNonIsolatedElectronVeto.analyze(iEvent, iSetup);
    if (!nonIsolatedElectronVetoData.passedEvent())  return false;
    increment(fNonIsolatedElectronVetoCounter);*/
    // Control plot


//------ Global muon veto
    const MuonSelection::Data muonData = fMuonSelection.analyze(iEvent, iSetup, pvData.getSelectedVertex());
    if (!muonData.passedEvent()) return false;
    increment(fMuonVetoCounter);
    fCommonPlotsAfterMuonVeto->fill();
    hSelectionFlow->Fill(kQCDOrderMuonVeto);
    /*NonIsolatedMuonVeto::Data nonIsolatedMuonVetoData = fNonIsolatedMuonVeto.analyze(iEvent, iSetup, pvData.getSelectedVertex());
    if (!nonIsolatedMuonVetoData.passedEvent()) return; 
    increment(fNonIsolatedMuonVetoCounter);*/
    // Control plot


//------ Jet selection
    const JetSelection::Data jetData = fJetSelection.analyze(iEvent, iSetup, mySelectedTau, nVertices);
    if (!jetData.passedEvent()) return false;
    increment(fNJetsCounter);
    fCommonPlotsAfterJetSelection->fill();
    hSelectionFlow->Fill(kQCDOrderJetSelection);


//------ Scale factor for MET trigger
    const METSelection::Data metData = fMETSelection.analyze(iEvent, iSetup, mySelectedTau, jetData.getAllJets());
    METTriggerEfficiencyScaleFactor::Data metTriggerWeight = fMETTriggerEfficiencyScaleFactor.applyEventWeight(*(metData.getSelectedMET()), iEvent.isRealData(), fEventWeight);
    fTree.setMETTriggerWeight(metTriggerWeight.getEventWeight(), metTriggerWeight.getEventWeightAbsoluteUncertainty());
    increment(fMETTriggerScaleFactorCounter);
    fCommonPlotsAfterMETScaleFactor->fill();


//------ Standard selections are done, fill tree and quit if user asked for it
    if (fTree.isActive()) {
      doTreeFilling(iEvent, iSetup, pvData, mySelectedTau, electronData, muonData, jetData, metData);
      return true;
    }


//----- Standard selections are done, now do analysis variations
    const BTagging::Data btagData = fBTagging.analyze(iEvent, iSetup, jetData.getSelectedJetsPt20());
    const QCDTailKiller::Data qcdTailKillerData = fQCDTailKiller.analyze(iEvent, iSetup, mySelectedTau, jetData.getSelectedJetsIncludingTau(), metData.getSelectedMET());
    //const double myDeltaPhi = DeltaPhi::reconstruct(*(mySelectedTau), *(metData.getSelectedMET())) * 57.3; // converted to degrees
    const double myTransverseMass = TransverseMass::reconstruct(*(mySelectedTau), *(metData.getSelectedMET()));
    double myFullMass = -1.0;
    if (btagData.passedEvent()) {
      const FullHiggsMassCalculator::Data FullHiggsMassData = fFullHiggsMassCalculator.analyze(iEvent, iSetup, mySelectedTau, btagData, metData);
      myFullMass = FullHiggsMassData.getHiggsMass();
    }
    // Increment counters
    increment(fStandardSelectionsCounter);
    if (metData.getSelectedMET()->et() > 30.0) {
      increment(fStandardSelectionsWithMET30Counter);
      if (qcdTailKillerData.passedEvent()) {
        increment(fStandardSelectionsWithTailKillerAndMET30Counter);
      }
    }
    if (qcdTailKillerData.passedEvent()) {
      increment(fStandardSelectionsWithTailKillerCounter);
    }

    // Proceed to analysis variations

    // Good old times (HIG-11-019) variation
    if (fDoAnalysisVariationWithTraditionalMethod) {
      fVariationTraditionalReference->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      if (metData.getSelectedMET()->et() > 30.0) {
        fVariationTraditionalPlusMET30->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
      if (qcdTailKillerData.passedEvent()) {
        fVariationTraditionalPlusTailKiller->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
      if (metData.getSelectedMET()->et() > 30.0 && qcdTailKillerData.passedEvent()) {
        fVariationTraditionalPlusMET30AndTailKiller->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
      if (qcdTailKillerData.passedCollinearCuts()) {
        fVariationTraditionalPlusCollinearTailKiller->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
      if (metData.getSelectedMET()->et() > 30.0 && qcdTailKillerData.passedCollinearCuts()) {
        fVariationTraditionalPlusMET30AndCollinearTailKiller->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
    }
    // ABCD method (experimental)
    if (fDoAnalysisVariationWithABCDMethod) {
      fVariationABCDReference->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      // MET>30 cut applied
      if (metData.getSelectedMET()->et() > 30.0) {
        fVariationABCDPlusMET30->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
      // QCD tail killer applied
      if (qcdTailKillerData.passedEvent()) {
        fVariationABCDPlusTailKiller->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
      // Both MET>30 cut and QCD tail killer applied
      if (metData.getSelectedMET()->et() > 30.0 && qcdTailKillerData.passedEvent()) {
        fVariationABCDPlusMET30AndTailKiller->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
      if (qcdTailKillerData.passedCollinearCuts()) {
        fVariationABCDPlusCollinearTailKiller->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
      if (metData.getSelectedMET()->et() > 30.0 && qcdTailKillerData.passedCollinearCuts()) {
        fVariationABCDPlusMET30AndCollinearTailKiller->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
      }
    }
    // Double ABCD method (very experimental)
    if (fDoAnalysisVariationWithDoubleABCDMethod) {
      fVariationDoubleABCD->doSelection(mySelectedTau, fTauSelection, jetData, metData, btagData, qcdTailKillerData, myTransverseMass, myFullMass);
    }

    // Additional tests
    testInvestigateCollinearEvents(iEvent, qcdTailKillerData, jetData, electronData, muonData, iEvent.isRealData(), tauMatchData.isFakeTau());

    //------ End of QCD measurement
    return true;
  }

  void QCDMeasurementFactorised::doTreeFilling(edm::Event& iEvent, const edm::EventSetup& iSetup, const VertexSelection::Data& pvData, const edm::Ptr<pat::Tau>& selectedTau, const ElectronSelection::Data& electronData, const MuonSelection::Data& muonData, const JetSelection::Data& jetData, const METSelection::Data& metData) {
    // Obtain btagging data
    const BTagging::Data btagData = fBTagging.analyze(iEvent, iSetup, jetData.getSelectedJets());
    // Obtain QCD tail killer
    const QCDTailKiller::Data qcdTailKillerData = fQCDTailKiller.analyze(iEvent, iSetup, selectedTau, jetData.getSelectedJetsIncludingTau(), metData.getSelectedMET());
    // const QCDTailKiller::Data qcdTailKillerData = fQCDTailKiller.analyze(iEvent, iSetup, selectedTau, jetData.getSelectedJets(), metData.getSelectedMET()); //testing
    // Obtain alphaT
    const EvtTopology::Data evtTopologyData = fEvtTopology.analyze(iEvent, iSetup, *(selectedTau), jetData.getSelectedJetsIncludingTau());

    // FIXME: Add filling of tree for QCD tail killer
    // FIXME: Add filling of weights (wjets ...)
    // Fill tree
    if(metData.getSelectedMET().isNonnull())
      fTree.setSelectedMet(metData.getSelectedMET());
    if(metData.getRawMET().isNonnull())
      fTree.setRawMET(metData.getRawMET());
    if(metData.getType1MET().isNonnull())
      fTree.setType1MET(metData.getType1MET());
    if(metData.getType2MET().isNonnull())
      fTree.setType2MET(metData.getType2MET());
    if(metData.getCaloMET().isNonnull())
      fTree.setCaloMET(metData.getCaloMET());
    if(metData.getTcMET().isNonnull())
      fTree.setTcMET(metData.getTcMET());
    fTree.setFillWeight(fEventWeight.getWeight());
    //if (!iEvent.isRealData()) {
    //  fEventWeight.multiplyWeight(btagData.getScaleFactor()); // needed to calculate the scale factor and the uncertainties
    //}
    fTree.setBTagging(btagData.passedEvent(), btagData.getScaleFactor(), btagData.getScaleFactorAbsoluteUncertainty());
    // Top reconstruction in different versions
    if (selectedTau.isNonnull() && btagData.passedEvent()) {
      //const TopSelection::Data topSelectionData = fTopSelection.analyze(iEvent, iSetup, jetData.getSelectedJets(), btagData.getSelectedJets());
      //const BjetSelection::Data bjetSelectionData = fBjetSelection.analyze(iEvent, iSetup, jetData.getSelectedJets(), btagData.getSelectedJets(), selectedTau, metData.getSelectedMET());
      const TopChiSelection::Data topChiSelectionData = fTopChiSelection.analyze(iEvent, iSetup, jetData.getSelectedJets(), btagData.getSelectedJets());
      //const TopWithBSelection::Data topWithBSelectionData = fTopWithBSelection.analyze(iEvent, iSetup, jetData.getSelectedJets(), bjetSelectionData.getBjetTopSide());
      fTree.setTop(topChiSelectionData.getTopP4());
    }
    // Sphericity, Aplanarity, Planarity, alphaT
    fTree.setDiJetMassesNoTau(evtTopologyData.alphaT().vDiJetMassesNoTau);
    fTree.setAlphaT(evtTopologyData.alphaT().fAlphaT);
    fTree.setSphericity(evtTopologyData.MomentumTensor().fSphericity);
    fTree.setAplanarity(evtTopologyData.MomentumTensor().fAplanarity);
    fTree.setPlanarity(evtTopologyData.MomentumTensor().fPlanarity);
    fTree.setCircularity(evtTopologyData.MomentumTensor().fCircularity);
    fTree.setMomentumTensorEigenvalues(evtTopologyData.MomentumTensor().fQOne, evtTopologyData.MomentumTensor().fQTwo, evtTopologyData.MomentumTensor().fQThree);
    fTree.setSpherocityTensorEigenvalues(evtTopologyData.SpherocityTensor().fQOne, evtTopologyData.SpherocityTensor().fQTwo, evtTopologyData.SpherocityTensor().fQThree);
    fTree.setCparameter(evtTopologyData.SpherocityTensor().fCparameter);
    fTree.setDparameter(evtTopologyData.SpherocityTensor().fDparameter);
    fTree.setJetThrust(evtTopologyData.SpherocityTensor().fJetThrust);
    fTree.setAllJets(jetData.getAllIdentifiedJets());
    fTree.setSelJets(jetData.getSelectedJets());
    fTree.setSelJetsInclTau(jetData.getSelectedJetsIncludingTau());
    fTree.setMHT(jetData.getMHTvector());
    fTree.setMHTSelJets(jetData.getSelectedJets());
    fTree.setMHTAllJets(jetData.getAllIdentifiedJets());
    //fTree.setDeltaPhi(fakeMETData.closestDeltaPhi());
    fTree.setNonIsoLeptons(muonData.getNonIsolatedMuons(), electronData.getNonIsolatedElectrons());
    if (selectedTau.isNonnull() && btagData.passedEvent()) {
      // FullH+ mass
      FullHiggsMassCalculator::Data FullHiggsMassDataTmp = fFullHiggsMassCalculator.analyze(iEvent, iSetup, selectedTau, btagData, metData);
      fTree.setHplusMassDiscriminant(FullHiggsMassDataTmp.getDiscriminant());
      fTree.setHplusMassHiggsMass(FullHiggsMassDataTmp.getHiggsMass());
      fTree.setHplusMassTopMass(FullHiggsMassDataTmp.getTopMass());
      fTree.setHplusMassSelectedNeutrinoPzSolution(FullHiggsMassDataTmp.getSelectedNeutrinoPzSolution());
      fTree.setHplusMassNeutrinoPtSolution(FullHiggsMassDataTmp.getNeutrinoPtSolution());
      fTree.setHplusMassMCNeutrinoPz(FullHiggsMassDataTmp.getMCNeutrinoPz());
    }
    fTree.setPassedTailKillerBackToBack(qcdTailKillerData.passedBackToBackCuts());
    fTree.setPassedTailKillerCollinear(qcdTailKillerData.passedCollinearCuts());

    for (int i = 0; i < qcdTailKillerData.getNConsideredJets(); ++i) {
      fTree.setRadiusFromBackToBackCornerJet(qcdTailKillerData.getRadiusFromBackToBackCorner(i));
      fTree.setRadiusFromCollinearCornerJet(qcdTailKillerData.getRadiusFromCollinearCorner(i));
      fTree.setTailKillerYaxisIntercept(qcdTailKillerData.getTailKillerYaxisIntercept(i));
    }

    fTree.fill(iEvent, selectedTau, jetData.getSelectedJets());
  }

  void QCDMeasurementFactorised::testInvestigateCollinearEvents(const edm::Event& iEvent, const QCDTailKiller::Data& qcdTailKillerData, const JetSelection::Data& jetData, const ElectronSelection::Data& eData, const MuonSelection::Data& muData, const bool isRealData, const bool isFakeTau) {
    //std::cout << "QCD tail killer status: " << qcdTailKillerData.passedBackToBackCuts() << " " << qcdTailKillerData.passedCollinearCuts() << std::endl;
    if (!qcdTailKillerData.passedBackToBackCuts()) return;
    if (qcdTailKillerData.passedCollinearCuts()) return;

    // Situation is that the jet faking tau is collinear with MET and the recoiling jet is back-to-back with MET
    // Why does rejecting these events make the mT closure test agree?
    // I.e. why is there a correlation between the collinear system and tau isolation?

    // Obtain jet that is faking the tau
    edm::Ptr<pat::Jet> myJetFakingTheTau = jetData.getReferenceJetToTau();
    if (myJetFakingTheTau.isNull()) return;
    // Obtain jet that is back to back to the jet faking the tau
    edm::Ptr<pat::Jet> myJetOppositeToTau;
    for (int i = 0; i < qcdTailKillerData.getNConsideredJets(); ++i) {
      if (myJetOppositeToTau.isNull() && !qcdTailKillerData.passCollinearCutForJet(i)) {
        myJetOppositeToTau = jetData.getSelectedJetsIncludingTau()[i]; // sorted by Et
      }
    }
    if (myJetOppositeToTau.isNull()) return;

    // Fill jet detail histograms
    if (isFakeTau) {
      fCollinearSystemJetsFakingTauFakeTaus->fill(myJetFakingTheTau, isRealData);
      fCollinearSystemJetsFakingTauFakeTaus->fillLeptonDetails(iEvent, myJetFakingTheTau, eData, muData, isRealData);
    } else {
      fCollinearSystemJetsFakingTauGenuineTaus->fill(myJetFakingTheTau, isRealData);
      fCollinearSystemJetsFakingTauGenuineTaus->fillLeptonDetails(iEvent, myJetFakingTheTau, eData, muData, isRealData);
    }
    fCollinearSystemJetsOppositeToTau->fill(myJetOppositeToTau, isRealData);
    fCollinearSystemJetsOppositeToTau->fillLeptonDetails(iEvent, myJetOppositeToTau, eData, muData, isRealData);
    // Answered by the detail histograms:
    // Multiplicity of PF charged particles in jet faking the tau
    // Multiplicity of PF charged particles for recoiling jet
    // Multiplicity of PF gammas in jet faking the tau
    // Multiplicity of PF gammas for recoiling jet
    // ET(RECO) / ET(GEN) for jet faking tau
    // ET(RECO) / ET(GEN) for recoiling jet
    // Flavor of the jet faking the tau (is it a b jet?)

    // Jet faking tau overlapping with electron or muon?
    // Jet faking tau overlapping with electron or muon from a b jet?
  }

  QCDMeasurementFactorised::QCDFactorisedVariation::QCDFactorisedVariation(edm::Service< TFileService >& fs, QCDFactorisedHistogramHandler* histoHandler, EventCounter& eventCounter, CommonPlots& commonPlots, QCDFactorisedVariationType methodType, std::string prefix)
  : fMethodType(methodType),
    fAfterStandardSelectionsCounter(eventCounter.addSubCounter(prefix,"After std. selections")),
    fAfterLeg1Counter(eventCounter.addSubCounter(prefix,"After leg1 selections")),
    fAfterLeg2Counter(eventCounter.addSubCounter(prefix,"After leg2 selections")),
    fAfterLeg1AndLeg2Counter(eventCounter.addSubCounter(prefix,"After leg1 and leg2 selections")),
    fHistoHandler(histoHandler),
    fCommonPlotsAfterStandardSelections(commonPlots.createCommonPlotsFilledAtEveryStep(prefix+" Std. selections",false,prefix+" Std. selections")),
    fCommonPlotsAfterMET(commonPlots.createCommonPlotsFilledAtEveryStep(prefix+" Std. selections+MET",false,prefix+" Std. selections+MET")),
    fCommonPlotsAfterMETAndBtag(commonPlots.createCommonPlotsFilledAtEveryStep(prefix+" Std. selections+MET+btag",false,prefix+" Std. selections+MET+btag")),
    fCommonPlotsAfterLeg1(commonPlots.createCommonPlotsFilledAtEveryStep(prefix+"Leg1 (MET+btag+...)",false,prefix+" Leg1 (MET+btag+...)")),
    fCommonPlotsAfterLeg2(commonPlots.createCommonPlotsFilledAtEveryStep(prefix+"Leg2 (tau isol.)",false,prefix+" Leg2 (tau isol.)"))
  {
    // Create histograms
    std::string myDirTitle = "QCDfactorised_"+prefix;
    TFileDirectory myDir = fs->mkdir(myDirTitle.c_str());

    // NQCD Histograms
    fHistoHandler->createCountHistogram(myDir, hNevtAfterStandardSelections, "NevtAfterStandardSelections");
    fHistoHandler->createCountHistogram(myDir, hNevtAfterLeg1, "NevtAfterLeg1");
    fHistoHandler->createCountHistogram(myDir, hNevtAfterLeg2, "NevtAfterLeg2");
    fHistoHandler->createCountHistogram(myDir, hNevtAfterLeg1AndLeg2, "NevtAfterLeg1AndLeg2");; // for closure test

    // Shape histograms (some needed for closure test)
    fHistoHandler->createShapeHistogram(myDir, hMtShapesAfterStandardSelections, "MtAfterStandardSelections", "Transverse mass, GeV/c^{2}", 80, 0, 400.);
    fHistoHandler->createShapeHistogram(myDir, hInvariantMassShapesAfterStandardSelections, "MassAfterStandardSelections", "Invariant mass, GeV/c^{2}", 100, 0, 500.);
    fHistoHandler->createShapeHistogram(myDir, hMtShapesAfterLeg1, "MtAfterLeg1", "Transverse mass, GeV/c^{2}", 80, 0, 400.);
    fHistoHandler->createShapeHistogram(myDir, hInvariantMassShapesAfterLeg1, "MassAfterLeg1", "Invariant mass, GeV/c^{2}", 100, 0, 500.);
    fHistoHandler->createShapeHistogram(myDir, hMtShapesAfterLeg1WithoutBtag, "MtAfterLeg1WithoutBtag", "Transverse mass, GeV/c^{2}", 80, 0, 400.);
    fHistoHandler->createShapeHistogram(myDir, hMtShapesAfterLeg2, "MtAfterLeg2", "Transverse mass, GeV/c^{2}", 80, 0, 400.);
    fHistoHandler->createShapeHistogram(myDir, hInvariantMassShapesAfterLeg2, "MassAfterLeg2", "Invariant mass, GeV/c^{2}", 100, 0, 500.);
    fHistoHandler->createShapeHistogram(myDir, hMtShapesAfterLeg1AndLeg2, "MtAfterLeg1AndLeg2", "Transverse mass, GeV/c^{2}", 80, 0, 400.);
    fHistoHandler->createShapeHistogram(myDir, hInvariantMassShapesAfterLeg1AndLeg2, "MassAfterLeg1AndLeg2", "Invariant mass, GeV/c^{2}", 100, 0, 500.);

    // Data-driven control histograms
    fHistoHandler->createShapeHistogram(myDir, hCtrlRtau, "CtrlRtau", "Rtau", 60, 0, 1.2);
    fHistoHandler->createShapeHistogram(myDir, hCtrlNjets, "CtrlNjets", "N_{jets}", 20, 0, 20.);
    fHistoHandler->createShapeHistogram(myDir, hCtrlMET, "CtrlMET", "E_{T}^{miss}, GeV", 100, 3, 500.);
    fHistoHandler->createShapeHistogram(myDir, hCtrlNbjets, "CtrlNbjets", "N_{b jets}", 20, 0, 20.);
    fHistoHandler->createShapeHistogram(myDir, hCtrlQCDTailKillerJet1, "CtrlQCDTailKillerJet1", "sqrt((180^{o} - #Delta#phi(#tau,E_{T}^{miss}))^2+(#Delta#phi(jet_{1},E_{T}^{miss}))^2), ^{o}", 52, 0, 260.);
    fHistoHandler->createShapeHistogram(myDir, hCtrlQCDTailKillerJet2, "CtrlQCDTailKillerJet2", "sqrt((180^{o} - #Delta#phi(#tau,E_{T}^{miss}))^2+(#Delta#phi(jet_{2},E_{T}^{miss}))^2), ^{o}", 52, 0, 260.);
    fHistoHandler->createShapeHistogram(myDir, hCtrlQCDTailKillerJet3, "CtrlQCDTailKillerJet3", "sqrt((180^{o} - #Delta#phi(#tau,E_{T}^{miss}))^2+(#Delta#phi(jet_{3},E_{T}^{miss}))^2), ^{o}", 52, 0, 260.);
    fHistoHandler->createShapeHistogram(myDir, hCtrlQCDTailKillerJet4, "CtrlQCDTailKillerJet4", "sqrt((180^{o} - #Delta#phi(#tau,E_{T}^{miss}))^2+(#Delta#phi(jet_{4},E_{T}^{miss}))^2), ^{o}", 52, 0, 260.);

    // Closure test oF MET
    fHistoHandler->createShapeHistogram(myDir, hCtrlMETAfterLeg1, "CtrlMETAfterLeg1", "E_{T}^{miss}, GeV", 100, 0, 500.);
    fHistoHandler->createShapeHistogram(myDir, hCtrlMETAfterLeg2, "CtrlMETAfterLeg2", "E_{T}^{miss}, GeV", 100, 0, 500.);
    fHistoHandler->createShapeHistogram(myDir, hCtrlMETAfterBJets, "CtrlMETAfterBJets", "E_{T}^{miss}, GeV", 100, 0, 500.);
  }

  QCDMeasurementFactorised::QCDFactorisedVariation::~QCDFactorisedVariation() { }

  void QCDMeasurementFactorised::QCDFactorisedVariation::doSelection(const edm::Ptr<pat::Tau>& selectedTau, const TauSelection& tauSelection, const JetSelection::Data jetData, const METSelection::Data& metData, const BTagging::Data& btagData, const QCDTailKiller::Data& tailKillerData, const double mT, const double fullMass) {
    if (fMethodType == kQCDFactorisedTraditional)
      doTraditionalSelection(selectedTau, tauSelection, jetData, metData, btagData, tailKillerData, mT, fullMass);
    else if (fMethodType == kQCDFactorisedABCD)
      doABCDSelection(selectedTau, tauSelection, jetData, metData, btagData, tailKillerData, mT, fullMass);
    else if (fMethodType == kQCDFactorisedDoubleABCD)
      doDoubleABCDSelection(selectedTau, tauSelection, jetData, metData, btagData, tailKillerData, mT, fullMass);
    else
      throw cms::Exception("Logic") << "QCDMeasurementFactorised::QCDFactorisedVariation::doSelection(): unknown method type! Fix code!";
  }

  void QCDMeasurementFactorised::QCDFactorisedVariation::doTraditionalSelection(const edm::Ptr<pat::Tau>& selectedTau, const TauSelection& tauSelection, const JetSelection::Data jetData, const METSelection::Data& metData, const BTagging::Data& btagData, const QCDTailKiller::Data& tailKillerData, const double mT, const double fullMass) {
    // Traditional method

    // Standard selections have been done, fill histograms
    fCommonPlotsAfterStandardSelections->fill();
    double myMetValue = metData.getSelectedMET()->et();
    increment(fAfterStandardSelectionsCounter);
    fHistoHandler->fillNeventHistogram(hNevtAfterStandardSelections);
    fHistoHandler->fillShapeHistogram(hMtShapesAfterStandardSelections, mT);
    fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterStandardSelections, fullMass);
    fHistoHandler->fillShapeHistogram(hCtrlRtau, tauSelection.getRtauOfTauObject(selectedTau));
    fHistoHandler->fillShapeHistogram(hCtrlNjets, jetData.getHadronicJetCount());

    // Leg 2 (tau ID)
    bool myLeg2PassedStatus = tauSelection.getPassesIsolationStatusOfTauObject(selectedTau) &&
      tauSelection.getPassesNProngsStatusOfTauObject(selectedTau) &&
      tauSelection.getPassesRtauStatusOfTauObject(selectedTau);
    if (myLeg2PassedStatus) {
      increment(fAfterLeg2Counter);
      fCommonPlotsAfterLeg2->fill();
      fHistoHandler->fillNeventHistogram(hNevtAfterLeg2);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg2, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterLeg2, fullMass);
      fHistoHandler->fillShapeHistogram(hCtrlMETAfterLeg2, myMetValue);
    }

    // Leg 1 / MET cut
    fHistoHandler->fillShapeHistogram(hCtrlMET, myMetValue);
    if (!metData.passedEvent()) return;
    fCommonPlotsAfterMET->fill();
    fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg1WithoutBtag, mT);

    // Leg 1 / b tagging
    fHistoHandler->fillShapeHistogram(hCtrlNbjets, btagData.getBJetCount());
    if (!btagData.passedEvent()) return;
    fCommonPlotsAfterMETAndBtag->fill();
    fHistoHandler->fillShapeHistogram(hCtrlMETAfterBJets, myMetValue);

    // Leg 1 / QCD tail killer
    fHistoHandler->fillShapeHistogram(hCtrlQCDTailKillerJet1, tailKillerData.getRadiusFromBackToBackCorner(0));
    fHistoHandler->fillShapeHistogram(hCtrlQCDTailKillerJet2, tailKillerData.getRadiusFromBackToBackCorner(1));
    fHistoHandler->fillShapeHistogram(hCtrlQCDTailKillerJet3, tailKillerData.getRadiusFromBackToBackCorner(2));
    fHistoHandler->fillShapeHistogram(hCtrlQCDTailKillerJet4, tailKillerData.getRadiusFromBackToBackCorner(3));
    if (!tailKillerData.passedEvent()) return;

    // Leg 1 passed
    increment(fAfterLeg1Counter);
    fHistoHandler->fillNeventHistogram(hNevtAfterLeg1);
    fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg1, mT);
    fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterLeg1, fullMass);
    fHistoHandler->fillShapeHistogram(hCtrlMETAfterLeg1, myMetValue);
    fCommonPlotsAfterLeg1->fill();

    // Leg 1 and leg 2 passed (for control only)
    if (myLeg2PassedStatus) {
      increment(fAfterLeg1AndLeg2Counter);
      fHistoHandler->fillNeventHistogram(hNevtAfterLeg1AndLeg2);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg1AndLeg2, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterLeg1AndLeg2, fullMass);
    }
  }

  void QCDMeasurementFactorised::QCDFactorisedVariation::doABCDSelection(const edm::Ptr<pat::Tau>& selectedTau, const TauSelection& tauSelection, const JetSelection::Data jetData, const METSelection::Data& metData, const BTagging::Data& btagData, const QCDTailKiller::Data& tailKillerData, const double mT, const double fullMass) {
    // ABCD method with MET and tau isolation as variables

    // Obtain booleans
    bool myLeg1PassedStatus = metData.passedEvent() && btagData.passedEvent() && tailKillerData.passedEvent();
    bool myLeg2PassedStatus = tauSelection.getPassesIsolationStatusOfTauObject(selectedTau) &&
      tauSelection.getPassesNProngsStatusOfTauObject(selectedTau) &&
      tauSelection.getPassesRtauStatusOfTauObject(selectedTau);
    double myMetValue = metData.getSelectedMET()->et();

    fHistoHandler->fillShapeHistogram(hCtrlRtau, tauSelection.getRtauOfTauObject(selectedTau));
    fHistoHandler->fillShapeHistogram(hCtrlNjets, jetData.getHadronicJetCount());
    // For cell A, negate the selections
    if (!myLeg1PassedStatus && !myLeg2PassedStatus) {
      increment(fAfterStandardSelectionsCounter);
      fHistoHandler->fillNeventHistogram(hNevtAfterStandardSelections);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterStandardSelections, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterStandardSelections, fullMass);
      fCommonPlotsAfterStandardSelections->fill();
    }

    // Cell C (i.e. Leg 2 i.e. tau ID, not passed Leg1)
    if (myLeg2PassedStatus && !myLeg1PassedStatus) {
      increment(fAfterLeg2Counter);
      fHistoHandler->fillNeventHistogram(hNevtAfterLeg2);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg2, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterLeg2, fullMass);
      fHistoHandler->fillShapeHistogram(hCtrlMETAfterLeg2, myMetValue);
      fCommonPlotsAfterLeg2->fill();
    }

    // Cell B (i.e. Leg 1, not passed Leg2)
    if (!myLeg2PassedStatus) {
      // Leg 1 / MET cut
      fHistoHandler->fillShapeHistogram(hCtrlMET, myMetValue);
      if (!metData.passedEvent()) return;
      fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg1WithoutBtag, mT);
      fCommonPlotsAfterMET->fill();

      // Leg 1 / b tagging
      fHistoHandler->fillShapeHistogram(hCtrlNbjets, btagData.getBJetCount());
      if (!btagData.passedEvent()) return;
      fCommonPlotsAfterMETAndBtag->fill();
      fHistoHandler->fillShapeHistogram(hCtrlMETAfterBJets, myMetValue);

      // Leg 1 / QCD tail killer
      fHistoHandler->fillShapeHistogram(hCtrlQCDTailKillerJet1, tailKillerData.getRadiusFromBackToBackCorner(0));
      fHistoHandler->fillShapeHistogram(hCtrlQCDTailKillerJet2, tailKillerData.getRadiusFromBackToBackCorner(1));
      fHistoHandler->fillShapeHistogram(hCtrlQCDTailKillerJet3, tailKillerData.getRadiusFromBackToBackCorner(2));
      fHistoHandler->fillShapeHistogram(hCtrlQCDTailKillerJet4, tailKillerData.getRadiusFromBackToBackCorner(3));
      if (!tailKillerData.passedEvent()) return;
      // Leg 1 passed
      increment(fAfterLeg1Counter);
      fHistoHandler->fillNeventHistogram(hNevtAfterLeg1);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg1, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterLeg1, fullMass);
      fHistoHandler->fillShapeHistogram(hCtrlMETAfterLeg1, myMetValue);
      fCommonPlotsAfterLeg1->fill();
    }

    // Cell D, i.e. leg 1 and leg 2 passed (for control only)
    if (myLeg1PassedStatus && myLeg2PassedStatus) {
      increment(fAfterLeg1AndLeg2Counter);
      fHistoHandler->fillNeventHistogram(hNevtAfterLeg1AndLeg2);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg1AndLeg2, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterLeg1AndLeg2, fullMass);
    }
  }

  void QCDMeasurementFactorised::QCDFactorisedVariation::doDoubleABCDSelection(const edm::Ptr<pat::Tau>& selectedTau, const TauSelection& tauSelection, const JetSelection::Data jetData, const METSelection::Data& metData, const BTagging::Data& btagData, const QCDTailKiller::Data& tailKillerData, const double mT, const double fullMass) {
    // ABCD method inside MET leg (for double ABCD)

    // Obtain booleans
    bool myLeg1PassedStatus = metData.passedEvent() && btagData.passedEvent() && tailKillerData.passedEvent();
    bool myLeg2PassedStatus = tauSelection.getPassesIsolationStatusOfTauObject(selectedTau) &&
      tauSelection.getPassesNProngsStatusOfTauObject(selectedTau) &&
      tauSelection.getPassesRtauStatusOfTauObject(selectedTau);
    double myMetValue = metData.getSelectedMET()->et();

    if (myLeg2PassedStatus) return;
    if (!metData.passedEvent()) return;

    bool myPassBtagStatus = btagData.passedEvent();
    bool myPassTailKillerStatus = tailKillerData.passedEvent();

    // Cell A
    if (!myPassBtagStatus && !myPassTailKillerStatus) {
      increment(fAfterStandardSelectionsCounter);
      fHistoHandler->fillNeventHistogram(hNevtAfterStandardSelections);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterStandardSelections, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterStandardSelections, fullMass);
      fCommonPlotsAfterStandardSelections->fill();
    }

    // Cell C
    if (myPassBtagStatus && !myPassTailKillerStatus) {
      increment(fAfterLeg2Counter);
      fHistoHandler->fillNeventHistogram(hNevtAfterLeg2);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg2, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterLeg2, fullMass);
      fHistoHandler->fillShapeHistogram(hCtrlMETAfterLeg2, myMetValue);
      fCommonPlotsAfterLeg2->fill();
    }

    // Cell B
    if (!myPassBtagStatus && myPassTailKillerStatus) {
      increment(fAfterLeg1Counter);
      fHistoHandler->fillNeventHistogram(hNevtAfterLeg1);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg1, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterLeg1, fullMass);
      fHistoHandler->fillShapeHistogram(hCtrlMETAfterLeg1, myMetValue);
      fCommonPlotsAfterLeg1->fill();
    }

    // Cell D (for control only)
    if (myPassBtagStatus && myPassTailKillerStatus) {
      increment(fAfterLeg1AndLeg2Counter);
      fHistoHandler->fillNeventHistogram(hNevtAfterLeg1AndLeg2);
      fHistoHandler->fillShapeHistogram(hMtShapesAfterLeg1AndLeg2, mT);
      fHistoHandler->fillShapeHistogram(hInvariantMassShapesAfterLeg1AndLeg2, fullMass);
    }
  }

}

// TODO:
// test plots for closure tests (b jet, leptons in b jets, gen jet ET / reco jet ET)
