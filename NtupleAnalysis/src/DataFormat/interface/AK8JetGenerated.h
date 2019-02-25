// -*- c++ -*-
// This file has been auto-generated with HiggsAnalysis/NtupleAnalysis/scripts/hplusGenerateDataFormats.py

#ifndef DataFormat_AK8JetGenerated_h
#define DataFormat_AK8JetGenerated_h

#include "DataFormat/interface/Particle.h"
#include <string>
#include <vector>
#include <functional>

class AK8JetGeneratedCollection: public ParticleCollection<double> {
public:
  explicit AK8JetGeneratedCollection(const std::string& prefix="AK8Jets")
  : ParticleCollection(prefix),
    fMCjet(prefix)
  {
    fMCjet.setEnergySystematicsVariation("_MCjet");
  }
  ~AK8JetGeneratedCollection() {}

  void setupBranches(BranchManager& mgr);

  std::vector<std::string> getBJetTagsDiscriminatorNames() const {
    static std::vector<std::string> n = { std::string("pfBoostedDoubleSecondaryVertexAK8BJetTags")};
    return n;
  }
  std::vector<std::string> getPUIDDiscriminatorNames() const {
    static std::vector<std::string> n = { std::string("")};
    return n;
  }
  std::vector<std::string> getJetIDDiscriminatorNames() const {
    static std::vector<std::string> n = { std::string("")};
    return n;
  }

  const ParticleCollection<double>* getMCjetCollection() const { return &fMCjet; }
protected:
  ParticleCollection<double> fMCjet;

protected:
  const Branch<std::vector<double>> *fNjettinessAK8Puppitau1;
  const Branch<std::vector<double>> *fNjettinessAK8Puppitau2;
  const Branch<std::vector<double>> *fNjettinessAK8Puppitau3;
  const Branch<std::vector<double>> *fAk8PFJetsCHSValueMapNjettinessAK8CHSTau1;
  const Branch<std::vector<double>> *fAk8PFJetsCHSValueMapNjettinessAK8CHSTau2;
  const Branch<std::vector<double>> *fAk8PFJetsCHSValueMapNjettinessAK8CHSTau3;
  const Branch<std::vector<double>> *fAk8PFJetsCHSValueMapak8PFJetsCHSPrunedMass;
  const Branch<std::vector<double>> *fAk8PFJetsCHSValueMapak8PFJetsCHSSoftDropMass;
  const Branch<std::vector<double>> *fAk8PFJetsPuppiSoftDropMass;
  const Branch<std::vector<double>> *fCorrPrunedMass;
  const Branch<std::vector<double>> *fSdsubjet1_axis1;
  const Branch<std::vector<double>> *fSdsubjet1_axis2;
  const Branch<std::vector<double>> *fSdsubjet1_csv;
  const Branch<std::vector<double>> *fSdsubjet1_deepcsv;
  const Branch<std::vector<double>> *fSdsubjet1_eta;
  const Branch<std::vector<double>> *fSdsubjet1_mass;
  const Branch<std::vector<double>> *fSdsubjet1_phi;
  const Branch<std::vector<double>> *fSdsubjet1_pt;
  const Branch<std::vector<double>> *fSdsubjet1_ptD;
  const Branch<std::vector<double>> *fSdsubjet2_axis1;
  const Branch<std::vector<double>> *fSdsubjet2_axis2;
  const Branch<std::vector<double>> *fSdsubjet2_csv;
  const Branch<std::vector<double>> *fSdsubjet2_deepcsv;
  const Branch<std::vector<double>> *fSdsubjet2_eta;
  const Branch<std::vector<double>> *fSdsubjet2_mass;
  const Branch<std::vector<double>> *fSdsubjet2_phi;
  const Branch<std::vector<double>> *fSdsubjet2_pt;
  const Branch<std::vector<double>> *fSdsubjet2_ptD;
  const Branch<std::vector<float>> *fPfBoostedDoubleSecondaryVertexAK8BJetTags;
  const Branch<std::vector<int>> *fHadronFlavour;
  const Branch<std::vector<int>> *fNsoftdropSubjets;
  const Branch<std::vector<int>> *fNumberOfDaughters;
  const Branch<std::vector<int>> *fPartonFlavour;
  const Branch<std::vector<int>> *fSdsubjet1_mult;
  const Branch<std::vector<int>> *fSdsubjet2_mult;
};


template <typename Coll>
class AK8JetGenerated: public Particle<Coll> {
public:
  AK8JetGenerated() {}
  AK8JetGenerated(const Coll* coll, size_t index)
  : Particle<Coll>(coll, index),
    fMCjet(coll->getMCjetCollection(), index)
  {}
  ~AK8JetGenerated() {}

  std::vector<std::function<bool()>> getBJetTagsDiscriminatorValues() const {
    static std::vector<std::function<bool()>> values = {
      [&](){ return this->pfBoostedDoubleSecondaryVertexAK8BJetTags(); }
    };
    return values;
  }
  std::vector<std::function<bool()>> getPUIDDiscriminatorValues() const {
    static std::vector<std::function<bool()>> values = {
    };
    return values;
  }
  std::vector<std::function<bool()>> getJetIDDiscriminatorValues() const {
    static std::vector<std::function<bool()>> values = {
    };
    return values;
  }

  const Particle<ParticleCollection<double>>* MCjet() const { return &fMCjet; }

  double NjettinessAK8Puppitau1() const { return this->fCollection->fNjettinessAK8Puppitau1->value()[this->index()]; }
  double NjettinessAK8Puppitau2() const { return this->fCollection->fNjettinessAK8Puppitau2->value()[this->index()]; }
  double NjettinessAK8Puppitau3() const { return this->fCollection->fNjettinessAK8Puppitau3->value()[this->index()]; }
  double ak8PFJetsCHSValueMapNjettinessAK8CHSTau1() const { return this->fCollection->fAk8PFJetsCHSValueMapNjettinessAK8CHSTau1->value()[this->index()]; }
  double ak8PFJetsCHSValueMapNjettinessAK8CHSTau2() const { return this->fCollection->fAk8PFJetsCHSValueMapNjettinessAK8CHSTau2->value()[this->index()]; }
  double ak8PFJetsCHSValueMapNjettinessAK8CHSTau3() const { return this->fCollection->fAk8PFJetsCHSValueMapNjettinessAK8CHSTau3->value()[this->index()]; }
  double ak8PFJetsCHSValueMapak8PFJetsCHSPrunedMass() const { return this->fCollection->fAk8PFJetsCHSValueMapak8PFJetsCHSPrunedMass->value()[this->index()]; }
  double ak8PFJetsCHSValueMapak8PFJetsCHSSoftDropMass() const { return this->fCollection->fAk8PFJetsCHSValueMapak8PFJetsCHSSoftDropMass->value()[this->index()]; }
  double ak8PFJetsPuppiSoftDropMass() const { return this->fCollection->fAk8PFJetsPuppiSoftDropMass->value()[this->index()]; }
  double corrPrunedMass() const { return this->fCollection->fCorrPrunedMass->value()[this->index()]; }
  double sdsubjet1_axis1() const { return this->fCollection->fSdsubjet1_axis1->value()[this->index()]; }
  double sdsubjet1_axis2() const { return this->fCollection->fSdsubjet1_axis2->value()[this->index()]; }
  double sdsubjet1_csv() const { return this->fCollection->fSdsubjet1_csv->value()[this->index()]; }
  double sdsubjet1_deepcsv() const { return this->fCollection->fSdsubjet1_deepcsv->value()[this->index()]; }
  double sdsubjet1_eta() const { return this->fCollection->fSdsubjet1_eta->value()[this->index()]; }
  double sdsubjet1_mass() const { return this->fCollection->fSdsubjet1_mass->value()[this->index()]; }
  double sdsubjet1_phi() const { return this->fCollection->fSdsubjet1_phi->value()[this->index()]; }
  double sdsubjet1_pt() const { return this->fCollection->fSdsubjet1_pt->value()[this->index()]; }
  double sdsubjet1_ptD() const { return this->fCollection->fSdsubjet1_ptD->value()[this->index()]; }
  double sdsubjet2_axis1() const { return this->fCollection->fSdsubjet2_axis1->value()[this->index()]; }
  double sdsubjet2_axis2() const { return this->fCollection->fSdsubjet2_axis2->value()[this->index()]; }
  double sdsubjet2_csv() const { return this->fCollection->fSdsubjet2_csv->value()[this->index()]; }
  double sdsubjet2_deepcsv() const { return this->fCollection->fSdsubjet2_deepcsv->value()[this->index()]; }
  double sdsubjet2_eta() const { return this->fCollection->fSdsubjet2_eta->value()[this->index()]; }
  double sdsubjet2_mass() const { return this->fCollection->fSdsubjet2_mass->value()[this->index()]; }
  double sdsubjet2_phi() const { return this->fCollection->fSdsubjet2_phi->value()[this->index()]; }
  double sdsubjet2_pt() const { return this->fCollection->fSdsubjet2_pt->value()[this->index()]; }
  double sdsubjet2_ptD() const { return this->fCollection->fSdsubjet2_ptD->value()[this->index()]; }
  float pfBoostedDoubleSecondaryVertexAK8BJetTags() const { return this->fCollection->fPfBoostedDoubleSecondaryVertexAK8BJetTags->value()[this->index()]; }
  int hadronFlavour() const { return this->fCollection->fHadronFlavour->value()[this->index()]; }
  int nsoftdropSubjets() const { return this->fCollection->fNsoftdropSubjets->value()[this->index()]; }
  int numberOfDaughters() const { return this->fCollection->fNumberOfDaughters->value()[this->index()]; }
  int partonFlavour() const { return this->fCollection->fPartonFlavour->value()[this->index()]; }
  int sdsubjet1_mult() const { return this->fCollection->fSdsubjet1_mult->value()[this->index()]; }
  int sdsubjet2_mult() const { return this->fCollection->fSdsubjet2_mult->value()[this->index()]; }

protected:
  Particle<ParticleCollection<double>> fMCjet;

};

#endif
