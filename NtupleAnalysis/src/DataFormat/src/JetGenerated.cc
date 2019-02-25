
// -*- c++ -*-
// This file has been auto-generated with HiggsAnalysis/NtupleAnalysis/scripts/hplusGenerateDataFormats.py

#include "DataFormat/interface/JetGenerated.h"

#include "Framework/interface/BranchManager.h"

void JetGeneratedCollection::setupBranches(BranchManager& mgr) {
  ParticleCollection::setupBranches(mgr);
  fMCjet.setupBranches(mgr);

  mgr.book(prefix()+"_IDtight", &fIDtight);
  mgr.book(prefix()+"_IDtightLeptonVeto", &fIDtightLeptonVeto);
  mgr.book(prefix()+"_PUIDmedium", &fPUIDmedium);
  mgr.book(prefix()+"_PUIDtight", &fPUIDtight);
  mgr.book(prefix()+"_originatesFromChargedHiggs", &fOriginatesFromChargedHiggs);
  mgr.book(prefix()+"_originatesFromTop", &fOriginatesFromTop);
  mgr.book(prefix()+"_originatesFromUnknown", &fOriginatesFromUnknown);
  mgr.book(prefix()+"_originatesFromW", &fOriginatesFromW);
  mgr.book(prefix()+"_originatesFromZ", &fOriginatesFromZ);
  mgr.book(prefix()+"_QGTaggerqgLikelihood", &fQGTaggerqgLikelihood);
  mgr.book(prefix()+"_axis1", &fAxis1);
  mgr.book(prefix()+"_axis2", &fAxis2);
  mgr.book(prefix()+"_caloJetMapemEnergyFraction", &fCaloJetMapemEnergyFraction);
  mgr.book(prefix()+"_caloJetMappt", &fCaloJetMappt);
  //mgr.book(prefix()+"_pfcharge", &fPfcharge);
  mgr.book(prefix()+"_pileupJetIdfullDiscriminant", &fPileupJetIdfullDiscriminant);
  mgr.book(prefix()+"_ptD", &fPtD);
  mgr.book(prefix()+"_pullPhi", &fPullPhi);
  mgr.book(prefix()+"_pullRap", &fPullRap);
  mgr.book(prefix()+"_pfCombinedCvsBJetTags", &fPfCombinedCvsBJetTags);
  mgr.book(prefix()+"_pfCombinedCvsLJetTags", &fPfCombinedCvsLJetTags);
  mgr.book(prefix()+"_pfCombinedInclusiveSecondaryVertexV2BJetTags", &fPfCombinedInclusiveSecondaryVertexV2BJetTags);
  mgr.book(prefix()+"_pfCombinedMVAV2BJetTags", &fPfCombinedMVAV2BJetTags);
  mgr.book(prefix()+"_pfCombinedSecondaryVertexV2BJetTags", &fPfCombinedSecondaryVertexV2BJetTags);
  mgr.book(prefix()+"_pfDeepCSVBJetTags", &fPfDeepCSVBJetTags);
  mgr.book(prefix()+"_pfDeepCSVCvsBJetTags", &fPfDeepCSVCvsBJetTags);
  mgr.book(prefix()+"_pfDeepCSVCvsLJetTags", &fPfDeepCSVCvsLJetTags);
  mgr.book(prefix()+"_pfDeepFlavourBJetTags", &fPfDeepFlavourBJetTags);
  mgr.book(prefix()+"_pfJetBProbabilityBJetTags", &fPfJetBProbabilityBJetTags);
  mgr.book(prefix()+"_pfJetProbabilityBJetTags", &fPfJetProbabilityBJetTags);
  mgr.book(prefix()+"_pfSimpleInclusiveSecondaryVertexHighEffBJetTags", &fPfSimpleInclusiveSecondaryVertexHighEffBJetTags);
  mgr.book(prefix()+"_pfSimpleSecondaryVertexHighEffBJetTags", &fPfSimpleSecondaryVertexHighEffBJetTags);
  mgr.book(prefix()+"_pfTrackCountingHighEffBJetTags", &fPfTrackCountingHighEffBJetTags);
  mgr.book(prefix()+"_softPFElectronBJetTags", &fSoftPFElectronBJetTags);
  mgr.book(prefix()+"_softPFMuonBJetTags", &fSoftPFMuonBJetTags);
  mgr.book(prefix()+"_hadronFlavour", &fHadronFlavour);
  mgr.book(prefix()+"_mult", &fMult);
  mgr.book(prefix()+"_partonFlavour", &fPartonFlavour);
}
