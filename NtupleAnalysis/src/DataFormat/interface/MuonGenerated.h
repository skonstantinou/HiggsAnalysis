// -*- c++ -*-
// This file has been auto-generated with HiggsAnalysis/NtupleAnalysis/scripts/hplusGenerateDataFormats.py

#ifndef DataFormat_MuonGenerated_h
#define DataFormat_MuonGenerated_h

#include "DataFormat/interface/Particle.h"
#include <string>
#include <vector>
#include <functional>

class MuonGeneratedCollection: public ParticleCollection<double> {
public:
  explicit MuonGeneratedCollection(const std::string& prefix="Muons")
  : ParticleCollection(prefix),
    fMCmuon(prefix)
  {
    fMCmuon.setEnergySystematicsVariation("_MCmuon");
  }
  ~MuonGeneratedCollection() {}

  void setupBranches(BranchManager& mgr);

  std::vector<std::string> getIDDiscriminatorNames() const {
    static std::vector<std::string> n = { std::string("isCutBasedIDGlobalHighPt"), std::string("isCutBasedIDLoose"), std::string("isCutBasedIDMedium"), std::string("isCutBasedIDMediumPrompt"), std::string("isCutBasedIDTight"), std::string("isCutBasedIDTrkHighPt")};
    return n;
  }

  const ParticleCollection<double>* getMCmuonCollection() const { return &fMCmuon; }
protected:
  ParticleCollection<double> fMCmuon;

protected:
  const Branch<std::vector<bool>> *fIsCutBasedIDGlobalHighPt;
  const Branch<std::vector<bool>> *fIsCutBasedIDLoose;
  const Branch<std::vector<bool>> *fIsCutBasedIDMedium;
  const Branch<std::vector<bool>> *fIsCutBasedIDMediumPrompt;
  const Branch<std::vector<bool>> *fIsCutBasedIDTight;
  const Branch<std::vector<bool>> *fIsCutBasedIDTrkHighPt;
  const Branch<std::vector<bool>> *fIsGlobalMuon;
  const Branch<std::vector<bool>> *fIsMiniIsoLoose;
  const Branch<std::vector<bool>> *fIsMiniIsoMedium;
  const Branch<std::vector<bool>> *fIsMiniIsoTight;
  const Branch<std::vector<bool>> *fIsMiniIsoVeryTight;
  const Branch<std::vector<bool>> *fIsMvaLoose;
  const Branch<std::vector<bool>> *fIsMvaMedium;
  const Branch<std::vector<bool>> *fIsMvaTight;
  const Branch<std::vector<bool>> *fIsPFIsoLoose;
  const Branch<std::vector<bool>> *fIsPFIsoMedium;
  const Branch<std::vector<bool>> *fIsPFIsoTight;
  const Branch<std::vector<bool>> *fIsPFIsoVeryLoose;
  const Branch<std::vector<bool>> *fIsPFIsoVeryTight;
  const Branch<std::vector<bool>> *fIsSoftCutBasedId;
  const Branch<std::vector<bool>> *fIsTkIsoLoose;
  const Branch<std::vector<bool>> *fIsTkIsoTight;
  const Branch<std::vector<float>> *fEffAreaMiniIso;
  const Branch<std::vector<float>> *fRelIsoDeltaBeta03;
  const Branch<std::vector<float>> *fRelIsoDeltaBeta04;
  const Branch<std::vector<float>> *fRelMiniIso;
  const Branch<std::vector<short>> *fCharge;
};


template <typename Coll>
class MuonGenerated: public Particle<Coll> {
public:
  MuonGenerated() {}
  MuonGenerated(const Coll* coll, size_t index)
  : Particle<Coll>(coll, index),
    fMCmuon(coll->getMCmuonCollection(), index)
  {}
  ~MuonGenerated() {}

  std::vector<std::function<bool()>> getIDDiscriminatorValues() const {
    static std::vector<std::function<bool()>> values = {
      [&](){ return this->isCutBasedIDGlobalHighPt(); },
      [&](){ return this->isCutBasedIDLoose(); },
      [&](){ return this->isCutBasedIDMedium(); },
      [&](){ return this->isCutBasedIDMediumPrompt(); },
      [&](){ return this->isCutBasedIDTight(); },
      [&](){ return this->isCutBasedIDTrkHighPt(); }
    };
    return values;
  }

  const Particle<ParticleCollection<double>>* MCmuon() const { return &fMCmuon; }

  bool isCutBasedIDGlobalHighPt() const { return this->fCollection->fIsCutBasedIDGlobalHighPt->value()[this->index()]; }
  bool isCutBasedIDLoose() const { return this->fCollection->fIsCutBasedIDLoose->value()[this->index()]; }
  bool isCutBasedIDMedium() const { return this->fCollection->fIsCutBasedIDMedium->value()[this->index()]; }
  bool isCutBasedIDMediumPrompt() const { return this->fCollection->fIsCutBasedIDMediumPrompt->value()[this->index()]; }
  bool isCutBasedIDTight() const { return this->fCollection->fIsCutBasedIDTight->value()[this->index()]; }
  bool isCutBasedIDTrkHighPt() const { return this->fCollection->fIsCutBasedIDTrkHighPt->value()[this->index()]; }
  bool isGlobalMuon() const { return this->fCollection->fIsGlobalMuon->value()[this->index()]; }
  bool isMiniIsoLoose() const { return this->fCollection->fIsMiniIsoLoose->value()[this->index()]; }
  bool isMiniIsoMedium() const { return this->fCollection->fIsMiniIsoMedium->value()[this->index()]; }
  bool isMiniIsoTight() const { return this->fCollection->fIsMiniIsoTight->value()[this->index()]; }
  bool isMiniIsoVeryTight() const { return this->fCollection->fIsMiniIsoVeryTight->value()[this->index()]; }
  bool isMvaLoose() const { return this->fCollection->fIsMvaLoose->value()[this->index()]; }
  bool isMvaMedium() const { return this->fCollection->fIsMvaMedium->value()[this->index()]; }
  bool isMvaTight() const { return this->fCollection->fIsMvaTight->value()[this->index()]; }
  bool isPFIsoLoose() const { return this->fCollection->fIsPFIsoLoose->value()[this->index()]; }
  bool isPFIsoMedium() const { return this->fCollection->fIsPFIsoMedium->value()[this->index()]; }
  bool isPFIsoTight() const { return this->fCollection->fIsPFIsoTight->value()[this->index()]; }
  bool isPFIsoVeryLoose() const { return this->fCollection->fIsPFIsoVeryLoose->value()[this->index()]; }
  bool isPFIsoVeryTight() const { return this->fCollection->fIsPFIsoVeryTight->value()[this->index()]; }
  bool isSoftCutBasedId() const { return this->fCollection->fIsSoftCutBasedId->value()[this->index()]; }
  bool isTkIsoLoose() const { return this->fCollection->fIsTkIsoLoose->value()[this->index()]; }
  bool isTkIsoTight() const { return this->fCollection->fIsTkIsoTight->value()[this->index()]; }
  float effAreaMiniIso() const { return this->fCollection->fEffAreaMiniIso->value()[this->index()]; }
  float relIsoDeltaBeta03() const { return this->fCollection->fRelIsoDeltaBeta03->value()[this->index()]; }
  float relIsoDeltaBeta04() const { return this->fCollection->fRelIsoDeltaBeta04->value()[this->index()]; }
  float relMiniIso() const { return this->fCollection->fRelMiniIso->value()[this->index()]; }
  short charge() const { return this->fCollection->fCharge->value()[this->index()]; }

protected:
  Particle<ParticleCollection<double>> fMCmuon;

};

#endif
