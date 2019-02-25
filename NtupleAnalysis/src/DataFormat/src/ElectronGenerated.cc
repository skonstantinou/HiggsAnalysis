
// -*- c++ -*-
// This file has been auto-generated with HiggsAnalysis/NtupleAnalysis/scripts/hplusGenerateDataFormats.py

#include "DataFormat/interface/ElectronGenerated.h"

#include "Framework/interface/BranchManager.h"

void ElectronGeneratedCollection::setupBranches(BranchManager& mgr) {
  ParticleCollection::setupBranches(mgr);
  fMCelectron.setupBranches(mgr);

  mgr.book(prefix()+"_cutBasedElectronID_Fall17_94X_V2_loose", &fCutBasedElectronID_Fall17_94X_V2_loose);
  mgr.book(prefix()+"_cutBasedElectronID_Fall17_94X_V2_medium", &fCutBasedElectronID_Fall17_94X_V2_medium);
  mgr.book(prefix()+"_cutBasedElectronID_Fall17_94X_V2_tight", &fCutBasedElectronID_Fall17_94X_V2_tight);
  mgr.book(prefix()+"_cutBasedElectronID_Fall17_94X_V2_veto", &fCutBasedElectronID_Fall17_94X_V2_veto);
  mgr.book(prefix()+"_mvaEleID_Fall17_iso_V1_wp80", &fMvaEleID_Fall17_iso_V1_wp80);
  mgr.book(prefix()+"_mvaEleID_Fall17_iso_V1_wp90", &fMvaEleID_Fall17_iso_V1_wp90);
  mgr.book(prefix()+"_mvaEleID_Fall17_iso_V1_wpLoose", &fMvaEleID_Fall17_iso_V1_wpLoose);
  mgr.book(prefix()+"_mvaEleID_Fall17_iso_V2_wp80", &fMvaEleID_Fall17_iso_V2_wp80);
  mgr.book(prefix()+"_mvaEleID_Fall17_iso_V2_wp90", &fMvaEleID_Fall17_iso_V2_wp90);
  mgr.book(prefix()+"_mvaEleID_Fall17_iso_V2_wpHZZ", &fMvaEleID_Fall17_iso_V2_wpHZZ);
  mgr.book(prefix()+"_mvaEleID_Fall17_iso_V2_wpLoose", &fMvaEleID_Fall17_iso_V2_wpLoose);
  mgr.book(prefix()+"_mvaEleID_Fall17_noIso_V1_wp80", &fMvaEleID_Fall17_noIso_V1_wp80);
  mgr.book(prefix()+"_mvaEleID_Fall17_noIso_V1_wp90", &fMvaEleID_Fall17_noIso_V1_wp90);
  mgr.book(prefix()+"_mvaEleID_Fall17_noIso_V1_wpLoose", &fMvaEleID_Fall17_noIso_V1_wpLoose);
  mgr.book(prefix()+"_mvaEleID_Fall17_noIso_V2_wp80", &fMvaEleID_Fall17_noIso_V2_wp80);
  mgr.book(prefix()+"_mvaEleID_Fall17_noIso_V2_wp90", &fMvaEleID_Fall17_noIso_V2_wp90);
  mgr.book(prefix()+"_mvaEleID_Fall17_noIso_V2_wpLoose", &fMvaEleID_Fall17_noIso_V2_wpLoose);
  mgr.book(prefix()+"_effAreaIsoDeltaBeta", &fEffAreaIsoDeltaBeta);
  mgr.book(prefix()+"_effAreaMiniIso", &fEffAreaMiniIso);
  mgr.book(prefix()+"_relIsoDeltaBeta", &fRelIsoDeltaBeta);
  mgr.book(prefix()+"_relMiniIso", &fRelMiniIso);
  mgr.book(prefix()+"_charge", &fCharge);
}
