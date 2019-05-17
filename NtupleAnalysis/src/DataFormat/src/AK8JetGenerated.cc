
// -*- c++ -*-
// This file has been auto-generated with HiggsAnalysis/NtupleAnalysis/scripts/hplusGenerateDataFormats.py

#include "DataFormat/interface/AK8JetGenerated.h"

#include "Framework/interface/BranchManager.h"

void AK8JetGeneratedCollection::setupBranches(BranchManager& mgr) {
  ParticleCollection::setupBranches(mgr);
  fMCjet.setupBranches(mgr);

  mgr.book(prefix()+"_NjettinessAK8Puppitau1", &fNjettinessAK8Puppitau1);
  mgr.book(prefix()+"_NjettinessAK8Puppitau2", &fNjettinessAK8Puppitau2);
  mgr.book(prefix()+"_NjettinessAK8Puppitau3", &fNjettinessAK8Puppitau3);
  mgr.book(prefix()+"_ak8PFJetsCHSValueMapNjettinessAK8CHSTau1", &fAk8PFJetsCHSValueMapNjettinessAK8CHSTau1);
  mgr.book(prefix()+"_ak8PFJetsCHSValueMapNjettinessAK8CHSTau2", &fAk8PFJetsCHSValueMapNjettinessAK8CHSTau2);
  mgr.book(prefix()+"_ak8PFJetsCHSValueMapNjettinessAK8CHSTau3", &fAk8PFJetsCHSValueMapNjettinessAK8CHSTau3);
  mgr.book(prefix()+"_ak8PFJetsCHSValueMapak8PFJetsCHSPrunedMass", &fAk8PFJetsCHSValueMapak8PFJetsCHSPrunedMass);
  mgr.book(prefix()+"_ak8PFJetsCHSValueMapak8PFJetsCHSSoftDropMass", &fAk8PFJetsCHSValueMapak8PFJetsCHSSoftDropMass);
  mgr.book(prefix()+"_ak8PFJetsPuppiSoftDropMass", &fAk8PFJetsPuppiSoftDropMass);
  mgr.book(prefix()+"_corrPrunedMass", &fCorrPrunedMass);
  mgr.book(prefix()+"_sdsubjet1_axis1", &fSdsubjet1_axis1);
  mgr.book(prefix()+"_sdsubjet1_axis2", &fSdsubjet1_axis2);
  mgr.book(prefix()+"_sdsubjet1_csv", &fSdsubjet1_csv);
  mgr.book(prefix()+"_sdsubjet1_deepcsv", &fSdsubjet1_deepcsv);
  mgr.book(prefix()+"_sdsubjet1_eta", &fSdsubjet1_eta);
  mgr.book(prefix()+"_sdsubjet1_mass", &fSdsubjet1_mass);
  mgr.book(prefix()+"_sdsubjet1_phi", &fSdsubjet1_phi);
  mgr.book(prefix()+"_sdsubjet1_pt", &fSdsubjet1_pt);
  mgr.book(prefix()+"_sdsubjet1_ptD", &fSdsubjet1_ptD);
  mgr.book(prefix()+"_sdsubjet2_axis1", &fSdsubjet2_axis1);
  mgr.book(prefix()+"_sdsubjet2_axis2", &fSdsubjet2_axis2);
  mgr.book(prefix()+"_sdsubjet2_csv", &fSdsubjet2_csv);
  mgr.book(prefix()+"_sdsubjet2_deepcsv", &fSdsubjet2_deepcsv);
  mgr.book(prefix()+"_sdsubjet2_eta", &fSdsubjet2_eta);
  mgr.book(prefix()+"_sdsubjet2_mass", &fSdsubjet2_mass);
  mgr.book(prefix()+"_sdsubjet2_phi", &fSdsubjet2_phi);
  mgr.book(prefix()+"_sdsubjet2_pt", &fSdsubjet2_pt);
  mgr.book(prefix()+"_sdsubjet2_ptD", &fSdsubjet2_ptD);
  mgr.book(prefix()+"_pfBoostedDoubleSecondaryVertexAK8BJetTags", &fPfBoostedDoubleSecondaryVertexAK8BJetTags);
  mgr.book(prefix()+"_hadronFlavour", &fHadronFlavour);
  mgr.book(prefix()+"_nsoftdropSubjets", &fNsoftdropSubjets);
  mgr.book(prefix()+"_numberOfDaughters", &fNumberOfDaughters);
  mgr.book(prefix()+"_partonFlavour", &fPartonFlavour);
  mgr.book(prefix()+"_sdsubjet1_mult", &fSdsubjet1_mult);
  mgr.book(prefix()+"_sdsubjet2_mult", &fSdsubjet2_mult);
}
