
// -*- c++ -*-
// This file has been auto-generated with HiggsAnalysis/NtupleAnalysis/scripts/hplusGenerateDataFormats.py

#include "DataFormat/interface/MuonGenerated.h"

#include "Framework/interface/BranchManager.h"

void MuonGeneratedCollection::setupBranches(BranchManager& mgr) {
  ParticleCollection::setupBranches(mgr);
  fMCmuon.setupBranches(mgr);

  mgr.book(prefix()+"_isCutBasedIDGlobalHighPt", &fIsCutBasedIDGlobalHighPt);
  mgr.book(prefix()+"_isCutBasedIDLoose", &fIsCutBasedIDLoose);
  mgr.book(prefix()+"_isCutBasedIDMedium", &fIsCutBasedIDMedium);
  mgr.book(prefix()+"_isCutBasedIDMediumPrompt", &fIsCutBasedIDMediumPrompt);
  mgr.book(prefix()+"_isCutBasedIDTight", &fIsCutBasedIDTight);
  mgr.book(prefix()+"_isCutBasedIDTrkHighPt", &fIsCutBasedIDTrkHighPt);
  mgr.book(prefix()+"_isGlobalMuon", &fIsGlobalMuon);
  mgr.book(prefix()+"_isMiniIsoLoose", &fIsMiniIsoLoose);
  mgr.book(prefix()+"_isMiniIsoMedium", &fIsMiniIsoMedium);
  mgr.book(prefix()+"_isMiniIsoTight", &fIsMiniIsoTight);
  mgr.book(prefix()+"_isMiniIsoVeryTight", &fIsMiniIsoVeryTight);
  mgr.book(prefix()+"_isMvaLoose", &fIsMvaLoose);
  mgr.book(prefix()+"_isMvaMedium", &fIsMvaMedium);
  mgr.book(prefix()+"_isMvaTight", &fIsMvaTight);
  mgr.book(prefix()+"_isPFIsoLoose", &fIsPFIsoLoose);
  mgr.book(prefix()+"_isPFIsoMedium", &fIsPFIsoMedium);
  mgr.book(prefix()+"_isPFIsoTight", &fIsPFIsoTight);
  mgr.book(prefix()+"_isPFIsoVeryLoose", &fIsPFIsoVeryLoose);
  mgr.book(prefix()+"_isPFIsoVeryTight", &fIsPFIsoVeryTight);
  mgr.book(prefix()+"_isSoftCutBasedId", &fIsSoftCutBasedId);
  mgr.book(prefix()+"_isTkIsoLoose", &fIsTkIsoLoose);
  mgr.book(prefix()+"_isTkIsoTight", &fIsTkIsoTight);
  mgr.book(prefix()+"_effAreaMiniIso", &fEffAreaMiniIso);
  mgr.book(prefix()+"_relIsoDeltaBeta03", &fRelIsoDeltaBeta03);
  mgr.book(prefix()+"_relIsoDeltaBeta04", &fRelIsoDeltaBeta04);
  mgr.book(prefix()+"_relMiniIso", &fRelMiniIso);
  mgr.book(prefix()+"_charge", &fCharge);
}
