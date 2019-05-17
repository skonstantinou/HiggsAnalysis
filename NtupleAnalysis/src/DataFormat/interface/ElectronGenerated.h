// -*- c++ -*-
// This file has been auto-generated with HiggsAnalysis/NtupleAnalysis/scripts/hplusGenerateDataFormats.py

#ifndef DataFormat_ElectronGenerated_h
#define DataFormat_ElectronGenerated_h

#include "DataFormat/interface/Particle.h"
#include <string>
#include <vector>
#include <functional>

class ElectronGeneratedCollection: public ParticleCollection<double> {
public:
  explicit ElectronGeneratedCollection(const std::string& prefix="Electrons")
  : ParticleCollection(prefix),
    fMCelectron(prefix)
  {
    fMCelectron.setEnergySystematicsVariation("_MCelectron");
  }
  ~ElectronGeneratedCollection() {}

  void setupBranches(BranchManager& mgr);

  std::vector<std::string> getIDDiscriminatorNames() const {
    static std::vector<std::string> n = { std::string("cutBasedElectronID_Fall17_94X_V2_loose"), std::string("cutBasedElectronID_Fall17_94X_V2_medium"), std::string("cutBasedElectronID_Fall17_94X_V2_tight"), std::string("cutBasedElectronID_Fall17_94X_V2_veto"), std::string("mvaEleID_Fall17_iso_V1_wp80"), std::string("mvaEleID_Fall17_iso_V1_wp90"), std::string("mvaEleID_Fall17_iso_V1_wpLoose"), std::string("mvaEleID_Fall17_iso_V2_wp80"), std::string("mvaEleID_Fall17_iso_V2_wp90"), std::string("mvaEleID_Fall17_iso_V2_wpHZZ"), std::string("mvaEleID_Fall17_iso_V2_wpLoose"), std::string("mvaEleID_Fall17_noIso_V1_wp80"), std::string("mvaEleID_Fall17_noIso_V1_wp90"), std::string("mvaEleID_Fall17_noIso_V1_wpLoose"), std::string("mvaEleID_Fall17_noIso_V2_wp80"), std::string("mvaEleID_Fall17_noIso_V2_wp90"), std::string("mvaEleID_Fall17_noIso_V2_wpLoose")};
    return n;
  }

  const ParticleCollection<double>* getMCelectronCollection() const { return &fMCelectron; }
protected:
  ParticleCollection<double> fMCelectron;

protected:
  const Branch<std::vector<bool>> *fCutBasedElectronID_Fall17_94X_V2_loose;
  const Branch<std::vector<bool>> *fCutBasedElectronID_Fall17_94X_V2_medium;
  const Branch<std::vector<bool>> *fCutBasedElectronID_Fall17_94X_V2_tight;
  const Branch<std::vector<bool>> *fCutBasedElectronID_Fall17_94X_V2_veto;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_iso_V1_wp80;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_iso_V1_wp90;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_iso_V1_wpLoose;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_iso_V2_wp80;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_iso_V2_wp90;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_iso_V2_wpHZZ;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_iso_V2_wpLoose;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_noIso_V1_wp80;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_noIso_V1_wp90;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_noIso_V1_wpLoose;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_noIso_V2_wp80;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_noIso_V2_wp90;
  const Branch<std::vector<bool>> *fMvaEleID_Fall17_noIso_V2_wpLoose;
  const Branch<std::vector<float>> *fEffAreaIsoDeltaBeta;
  const Branch<std::vector<float>> *fEffAreaMiniIso;
  const Branch<std::vector<float>> *fRelIsoDeltaBeta;
  const Branch<std::vector<float>> *fRelMiniIso;
  const Branch<std::vector<short>> *fCharge;
};


template <typename Coll>
class ElectronGenerated: public Particle<Coll> {
public:
  ElectronGenerated() {}
  ElectronGenerated(const Coll* coll, size_t index)
  : Particle<Coll>(coll, index),
    fMCelectron(coll->getMCelectronCollection(), index)
  {}
  ~ElectronGenerated() {}

  std::vector<std::function<bool()>> getIDDiscriminatorValues() const {
    static std::vector<std::function<bool()>> values = {
      [&](){ return this->cutBasedElectronID_Fall17_94X_V2_loose(); },
      [&](){ return this->cutBasedElectronID_Fall17_94X_V2_medium(); },
      [&](){ return this->cutBasedElectronID_Fall17_94X_V2_tight(); },
      [&](){ return this->cutBasedElectronID_Fall17_94X_V2_veto(); },
      [&](){ return this->mvaEleID_Fall17_iso_V1_wp80(); },
      [&](){ return this->mvaEleID_Fall17_iso_V1_wp90(); },
      [&](){ return this->mvaEleID_Fall17_iso_V1_wpLoose(); },
      [&](){ return this->mvaEleID_Fall17_iso_V2_wp80(); },
      [&](){ return this->mvaEleID_Fall17_iso_V2_wp90(); },
      [&](){ return this->mvaEleID_Fall17_iso_V2_wpHZZ(); },
      [&](){ return this->mvaEleID_Fall17_iso_V2_wpLoose(); },
      [&](){ return this->mvaEleID_Fall17_noIso_V1_wp80(); },
      [&](){ return this->mvaEleID_Fall17_noIso_V1_wp90(); },
      [&](){ return this->mvaEleID_Fall17_noIso_V1_wpLoose(); },
      [&](){ return this->mvaEleID_Fall17_noIso_V2_wp80(); },
      [&](){ return this->mvaEleID_Fall17_noIso_V2_wp90(); },
      [&](){ return this->mvaEleID_Fall17_noIso_V2_wpLoose(); }
    };
    return values;
  }

  const Particle<ParticleCollection<double>>* MCelectron() const { return &fMCelectron; }

  bool cutBasedElectronID_Fall17_94X_V2_loose() const { return this->fCollection->fCutBasedElectronID_Fall17_94X_V2_loose->value()[this->index()]; }
  bool cutBasedElectronID_Fall17_94X_V2_medium() const { return this->fCollection->fCutBasedElectronID_Fall17_94X_V2_medium->value()[this->index()]; }
  bool cutBasedElectronID_Fall17_94X_V2_tight() const { return this->fCollection->fCutBasedElectronID_Fall17_94X_V2_tight->value()[this->index()]; }
  bool cutBasedElectronID_Fall17_94X_V2_veto() const { return this->fCollection->fCutBasedElectronID_Fall17_94X_V2_veto->value()[this->index()]; }
  bool mvaEleID_Fall17_iso_V1_wp80() const { return this->fCollection->fMvaEleID_Fall17_iso_V1_wp80->value()[this->index()]; }
  bool mvaEleID_Fall17_iso_V1_wp90() const { return this->fCollection->fMvaEleID_Fall17_iso_V1_wp90->value()[this->index()]; }
  bool mvaEleID_Fall17_iso_V1_wpLoose() const { return this->fCollection->fMvaEleID_Fall17_iso_V1_wpLoose->value()[this->index()]; }
  bool mvaEleID_Fall17_iso_V2_wp80() const { return this->fCollection->fMvaEleID_Fall17_iso_V2_wp80->value()[this->index()]; }
  bool mvaEleID_Fall17_iso_V2_wp90() const { return this->fCollection->fMvaEleID_Fall17_iso_V2_wp90->value()[this->index()]; }
  bool mvaEleID_Fall17_iso_V2_wpHZZ() const { return this->fCollection->fMvaEleID_Fall17_iso_V2_wpHZZ->value()[this->index()]; }
  bool mvaEleID_Fall17_iso_V2_wpLoose() const { return this->fCollection->fMvaEleID_Fall17_iso_V2_wpLoose->value()[this->index()]; }
  bool mvaEleID_Fall17_noIso_V1_wp80() const { return this->fCollection->fMvaEleID_Fall17_noIso_V1_wp80->value()[this->index()]; }
  bool mvaEleID_Fall17_noIso_V1_wp90() const { return this->fCollection->fMvaEleID_Fall17_noIso_V1_wp90->value()[this->index()]; }
  bool mvaEleID_Fall17_noIso_V1_wpLoose() const { return this->fCollection->fMvaEleID_Fall17_noIso_V1_wpLoose->value()[this->index()]; }
  bool mvaEleID_Fall17_noIso_V2_wp80() const { return this->fCollection->fMvaEleID_Fall17_noIso_V2_wp80->value()[this->index()]; }
  bool mvaEleID_Fall17_noIso_V2_wp90() const { return this->fCollection->fMvaEleID_Fall17_noIso_V2_wp90->value()[this->index()]; }
  bool mvaEleID_Fall17_noIso_V2_wpLoose() const { return this->fCollection->fMvaEleID_Fall17_noIso_V2_wpLoose->value()[this->index()]; }
  float effAreaIsoDeltaBeta() const { return this->fCollection->fEffAreaIsoDeltaBeta->value()[this->index()]; }
  float effAreaMiniIso() const { return this->fCollection->fEffAreaMiniIso->value()[this->index()]; }
  float relIsoDeltaBeta() const { return this->fCollection->fRelIsoDeltaBeta->value()[this->index()]; }
  float relMiniIso() const { return this->fCollection->fRelMiniIso->value()[this->index()]; }
  short charge() const { return this->fCollection->fCharge->value()[this->index()]; }

protected:
  Particle<ParticleCollection<double>> fMCelectron;

};

#endif
