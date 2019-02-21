// -*- c++ -*-
// This file has been auto-generated with HiggsAnalysis/NtupleAnalysis/scripts/hplusGenerateDataFormats.py

#ifndef DataFormat_JetGenerated_h
#define DataFormat_JetGenerated_h

#include "DataFormat/interface/Particle.h"
#include <string>
#include <vector>
#include <functional>

class JetGeneratedCollection: public ParticleCollection<double> {
public:
  explicit JetGeneratedCollection(const std::string& prefix="Jets")
  : ParticleCollection(prefix),
    fMCjet(prefix)
  {
    fMCjet.setEnergySystematicsVariation("_MCjet");
  }
  ~JetGeneratedCollection() {}

  void setupBranches(BranchManager& mgr);

  std::vector<std::string> getBJetTagsDiscriminatorNames() const {
    static std::vector<std::string> n = { std::string("pfCombinedCvsBJetTags"), std::string("pfCombinedInclusiveSecondaryVertexV2BJetTags"), std::string("pfCombinedMVAV2BJetTags"), std::string("pfCombinedSecondaryVertexV2BJetTags"), std::string("pfDeepCSVBJetTags"), std::string("pfDeepCSVCvsBJetTags"), std::string("pfDeepFlavourBJetTags"), std::string("pfJetBProbabilityBJetTags"), std::string("pfJetProbabilityBJetTags"), std::string("pfSimpleInclusiveSecondaryVertexHighEffBJetTags"), std::string("pfSimpleSecondaryVertexHighEffBJetTags"), std::string("pfTrackCountingHighEffBJetTags"), std::string("softPFElectronBJetTags"), std::string("softPFMuonBJetTags")};
    return n;
  }
  std::vector<std::string> getPUIDDiscriminatorNames() const {
    static std::vector<std::string> n = { std::string("PUIDmedium"), std::string("PUIDtight")};
    return n;
  }
  std::vector<std::string> getJetIDDiscriminatorNames() const {
    static std::vector<std::string> n = { std::string("IDtight"), std::string("IDtightLeptonVeto")};
    return n;
  }

  const ParticleCollection<double>* getMCjetCollection() const { return &fMCjet; }
protected:
  ParticleCollection<double> fMCjet;

protected:
  const Branch<std::vector<bool>> *fIDtight;
  const Branch<std::vector<bool>> *fIDtightLeptonVeto;
  const Branch<std::vector<bool>> *fPUIDmedium;
  const Branch<std::vector<bool>> *fPUIDtight;
  const Branch<std::vector<bool>> *fOriginatesFromChargedHiggs;
  const Branch<std::vector<bool>> *fOriginatesFromTop;
  const Branch<std::vector<bool>> *fOriginatesFromUnknown;
  const Branch<std::vector<bool>> *fOriginatesFromW;
  const Branch<std::vector<bool>> *fOriginatesFromZ;
  const Branch<std::vector<double>> *fQGTaggerqgLikelihood;
  const Branch<std::vector<double>> *fAxis1;
  const Branch<std::vector<double>> *fAxis2;
  const Branch<std::vector<double>> *fCaloJetMapemEnergyFraction;
  const Branch<std::vector<double>> *fCaloJetMappt;
  //const Branch<std::vector<double>> *fPfcharge;
  const Branch<std::vector<double>> *fPileupJetIdfullDiscriminant;
  const Branch<std::vector<double>> *fPtD;
  const Branch<std::vector<double>> *fPullPhi;
  const Branch<std::vector<double>> *fPullRap;
  const Branch<std::vector<float>> *fPfCombinedCvsBJetTags;
  const Branch<std::vector<float>> *fPfCombinedCvsLJetTags;
  const Branch<std::vector<float>> *fPfCombinedInclusiveSecondaryVertexV2BJetTags;
  const Branch<std::vector<float>> *fPfCombinedMVAV2BJetTags;
  const Branch<std::vector<float>> *fPfCombinedSecondaryVertexV2BJetTags;
  const Branch<std::vector<float>> *fPfDeepCSVBJetTags;
  const Branch<std::vector<float>> *fPfDeepCSVCvsBJetTags;
  const Branch<std::vector<float>> *fPfDeepCSVCvsLJetTags;
  const Branch<std::vector<float>> *fPfDeepFlavourBJetTags;
  const Branch<std::vector<float>> *fPfJetBProbabilityBJetTags;
  const Branch<std::vector<float>> *fPfJetProbabilityBJetTags;
  const Branch<std::vector<float>> *fPfSimpleInclusiveSecondaryVertexHighEffBJetTags;
  const Branch<std::vector<float>> *fPfSimpleSecondaryVertexHighEffBJetTags;
  const Branch<std::vector<float>> *fPfTrackCountingHighEffBJetTags;
  const Branch<std::vector<float>> *fSoftPFElectronBJetTags;
  const Branch<std::vector<float>> *fSoftPFMuonBJetTags;
  const Branch<std::vector<int>> *fHadronFlavour;
  const Branch<std::vector<int>> *fMult;
  const Branch<std::vector<int>> *fPartonFlavour;
};


template <typename Coll>
class JetGenerated: public Particle<Coll> {
public:
  JetGenerated() {}
  JetGenerated(const Coll* coll, size_t index)
  : Particle<Coll>(coll, index),
    fMCjet(coll->getMCjetCollection(), index)
  {}
  ~JetGenerated() {}

  std::vector<std::function<bool()>> getBJetTagsDiscriminatorValues() const {
    static std::vector<std::function<bool()>> values = {
      [&](){ return this->pfCombinedCvsBJetTags(); },
      [&](){ return this->pfCombinedInclusiveSecondaryVertexV2BJetTags(); },
      [&](){ return this->pfCombinedMVAV2BJetTags(); },
      [&](){ return this->pfCombinedSecondaryVertexV2BJetTags(); },
      [&](){ return this->pfDeepCSVBJetTags(); },
      [&](){ return this->pfDeepCSVCvsBJetTags(); },
      [&](){ return this->pfDeepFlavourBJetTags(); },
      [&](){ return this->pfJetBProbabilityBJetTags(); },
      [&](){ return this->pfJetProbabilityBJetTags(); },
      [&](){ return this->pfSimpleInclusiveSecondaryVertexHighEffBJetTags(); },
      [&](){ return this->pfSimpleSecondaryVertexHighEffBJetTags(); },
      [&](){ return this->pfTrackCountingHighEffBJetTags(); },
      [&](){ return this->softPFElectronBJetTags(); },
      [&](){ return this->softPFMuonBJetTags(); }
    };
    return values;
  }
  std::vector<std::function<bool()>> getPUIDDiscriminatorValues() const {
    static std::vector<std::function<bool()>> values = {
      [&](){ return this->PUIDmedium(); },
      [&](){ return this->PUIDtight(); }
    };
    return values;
  }
  std::vector<std::function<bool()>> getJetIDDiscriminatorValues() const {
    static std::vector<std::function<bool()>> values = {
      [&](){ return this->IDtight(); },
      [&](){ return this->IDtightLeptonVeto(); }
    };
    return values;
  }

  const Particle<ParticleCollection<double>>* MCjet() const { return &fMCjet; }

  bool IDtight() const { return this->fCollection->fIDtight->value()[this->index()]; }
  bool IDtightLeptonVeto() const { return this->fCollection->fIDtightLeptonVeto->value()[this->index()]; }
  bool PUIDmedium() const { return this->fCollection->fPUIDmedium->value()[this->index()]; }
  bool PUIDtight() const { return this->fCollection->fPUIDtight->value()[this->index()]; }
  bool originatesFromChargedHiggs() const { return this->fCollection->fOriginatesFromChargedHiggs->value()[this->index()]; }
  bool originatesFromTop() const { return this->fCollection->fOriginatesFromTop->value()[this->index()]; }
  bool originatesFromUnknown() const { return this->fCollection->fOriginatesFromUnknown->value()[this->index()]; }
  bool originatesFromW() const { return this->fCollection->fOriginatesFromW->value()[this->index()]; }
  bool originatesFromZ() const { return this->fCollection->fOriginatesFromZ->value()[this->index()]; }
  double QGTaggerqgLikelihood() const { return this->fCollection->fQGTaggerqgLikelihood->value()[this->index()]; }
  double axis1() const { return this->fCollection->fAxis1->value()[this->index()]; }
  double axis2() const { return this->fCollection->fAxis2->value()[this->index()]; }
  double caloJetMapemEnergyFraction() const { return this->fCollection->fCaloJetMapemEnergyFraction->value()[this->index()]; }
  double caloJetMappt() const { return this->fCollection->fCaloJetMappt->value()[this->index()]; }
  //double charge() const { return this->fCollection->fPfcharge->value()[this->index()]; }
  double pileupJetIdfullDiscriminant() const { return this->fCollection->fPileupJetIdfullDiscriminant->value()[this->index()]; }
  double ptD() const { return this->fCollection->fPtD->value()[this->index()]; }
  double pullPhi() const { return this->fCollection->fPullPhi->value()[this->index()]; }
  double pullRap() const { return this->fCollection->fPullRap->value()[this->index()]; }
  float pfCombinedCvsBJetTags() const { return this->fCollection->fPfCombinedCvsBJetTags->value()[this->index()]; }
  float pfCombinedCvsLJetTags() const { return this->fCollection->fPfCombinedCvsLJetTags->value()[this->index()]; }
  float pfCombinedInclusiveSecondaryVertexV2BJetTags() const { return this->fCollection->fPfCombinedInclusiveSecondaryVertexV2BJetTags->value()[this->index()]; }
  float pfCombinedMVAV2BJetTags() const { return this->fCollection->fPfCombinedMVAV2BJetTags->value()[this->index()]; }
  float pfCombinedSecondaryVertexV2BJetTags() const { return this->fCollection->fPfCombinedSecondaryVertexV2BJetTags->value()[this->index()]; }
  float pfDeepCSVBJetTags() const { return this->fCollection->fPfDeepCSVBJetTags->value()[this->index()]; }
  float pfDeepCSVCvsBJetTags() const { return this->fCollection->fPfDeepCSVCvsBJetTags->value()[this->index()]; }
  float pfDeepCSVCvsLJetTags() const { return this->fCollection->fPfDeepCSVCvsLJetTags->value()[this->index()]; }
  float pfDeepFlavourBJetTags() const { return this->fCollection->fPfDeepFlavourBJetTags->value()[this->index()]; }
  float pfJetBProbabilityBJetTags() const { return this->fCollection->fPfJetBProbabilityBJetTags->value()[this->index()]; }
  float pfJetProbabilityBJetTags() const { return this->fCollection->fPfJetProbabilityBJetTags->value()[this->index()]; }
  float pfSimpleInclusiveSecondaryVertexHighEffBJetTags() const { return this->fCollection->fPfSimpleInclusiveSecondaryVertexHighEffBJetTags->value()[this->index()]; }
  float pfSimpleSecondaryVertexHighEffBJetTags() const { return this->fCollection->fPfSimpleSecondaryVertexHighEffBJetTags->value()[this->index()]; }
  float pfTrackCountingHighEffBJetTags() const { return this->fCollection->fPfTrackCountingHighEffBJetTags->value()[this->index()]; }
  float softPFElectronBJetTags() const { return this->fCollection->fSoftPFElectronBJetTags->value()[this->index()]; }
  float softPFMuonBJetTags() const { return this->fCollection->fSoftPFMuonBJetTags->value()[this->index()]; }
  int hadronFlavour() const { return this->fCollection->fHadronFlavour->value()[this->index()]; }
  int mult() const { return this->fCollection->fMult->value()[this->index()]; }
  int partonFlavour() const { return this->fCollection->fPartonFlavour->value()[this->index()]; }

protected:
  Particle<ParticleCollection<double>> fMCjet;

};

#endif
