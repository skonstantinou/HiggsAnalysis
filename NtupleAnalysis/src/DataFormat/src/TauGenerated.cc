
// -*- c++ -*-
// This file has been auto-generated with HiggsAnalysis/NtupleAnalysis/scripts/hplusGenerateDataFormats.py

#include "DataFormat/interface/TauGenerated.h"

#include "Framework/interface/BranchManager.h"

void TauGeneratedCollection::setupBranches(BranchManager& mgr) {
  ParticleCollection::setupBranches(mgr);
  fMCVisibleTau.setupBranches(mgr);
  fmatchingJet.setupBranches(mgr);

  mgr.book(prefix()+"_againstElectronLooseMVA6", &fAgainstElectronLooseMVA6);
  mgr.book(prefix()+"_againstElectronMediumMVA6", &fAgainstElectronMediumMVA6);
  mgr.book(prefix()+"_againstElectronTightMVA6", &fAgainstElectronTightMVA6);
  mgr.book(prefix()+"_againstElectronVLooseMVA6", &fAgainstElectronVLooseMVA6);
  mgr.book(prefix()+"_againstElectronVTightMVA6", &fAgainstElectronVTightMVA6);
  mgr.book(prefix()+"_againstMuonLoose3", &fAgainstMuonLoose3);
  mgr.book(prefix()+"_againstMuonTight3", &fAgainstMuonTight3);
  mgr.book(prefix()+"_byIsolationMVArun2017v2DBnewDMwLTraw2017", &fByIsolationMVArun2017v2DBnewDMwLTraw2017);
  mgr.book(prefix()+"_byIsolationMVArun2017v2DBoldDMdR0p3wLTraw2017", &fByIsolationMVArun2017v2DBoldDMdR0p3wLTraw2017);
  mgr.book(prefix()+"_byIsolationMVArun2017v2DBoldDMwLTraw2017", &fByIsolationMVArun2017v2DBoldDMwLTraw2017);
  mgr.book(prefix()+"_byLooseCombinedIsolationDeltaBetaCorr3Hits", &fByLooseCombinedIsolationDeltaBetaCorr3Hits);
  mgr.book(prefix()+"_byLooseIsolationMVArun2017v2DBnewDMwLT2017", &fByLooseIsolationMVArun2017v2DBnewDMwLT2017);
  mgr.book(prefix()+"_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017", &fByLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017);
  mgr.book(prefix()+"_byLooseIsolationMVArun2017v2DBoldDMwLT2017", &fByLooseIsolationMVArun2017v2DBoldDMwLT2017);
  mgr.book(prefix()+"_byMediumCombinedIsolationDeltaBetaCorr3Hits", &fByMediumCombinedIsolationDeltaBetaCorr3Hits);
  mgr.book(prefix()+"_byMediumIsolationMVArun2017v2DBnewDMwLT2017", &fByMediumIsolationMVArun2017v2DBnewDMwLT2017);
  mgr.book(prefix()+"_byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017", &fByMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017);
  mgr.book(prefix()+"_byMediumIsolationMVArun2017v2DBoldDMwLT2017", &fByMediumIsolationMVArun2017v2DBoldDMwLT2017);
  mgr.book(prefix()+"_byTightCombinedIsolationDeltaBetaCorr3Hits", &fByTightCombinedIsolationDeltaBetaCorr3Hits);
  mgr.book(prefix()+"_byTightIsolationMVArun2017v2DBnewDMwLT2017", &fByTightIsolationMVArun2017v2DBnewDMwLT2017);
  mgr.book(prefix()+"_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017", &fByTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017);
  mgr.book(prefix()+"_byTightIsolationMVArun2017v2DBoldDMwLT2017", &fByTightIsolationMVArun2017v2DBoldDMwLT2017);
  mgr.book(prefix()+"_byVLooseCombinedIsolationDeltaBetaCorr3Hits", &fByVLooseCombinedIsolationDeltaBetaCorr3Hits);
  mgr.book(prefix()+"_byVLooseIsolationMVArun2017v2DBnewDMwLT2017", &fByVLooseIsolationMVArun2017v2DBnewDMwLT2017);
  mgr.book(prefix()+"_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017", &fByVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017);
  mgr.book(prefix()+"_byVLooseIsolationMVArun2017v2DBoldDMwLT2017", &fByVLooseIsolationMVArun2017v2DBoldDMwLT2017);
  mgr.book(prefix()+"_byVTightIsolationMVArun2017v2DBnewDMwLT2017", &fByVTightIsolationMVArun2017v2DBnewDMwLT2017);
  mgr.book(prefix()+"_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017", &fByVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017);
  mgr.book(prefix()+"_byVTightIsolationMVArun2017v2DBoldDMwLT2017", &fByVTightIsolationMVArun2017v2DBoldDMwLT2017);
  mgr.book(prefix()+"_byVVLooseCombinedIsolationDeltaBetaCorr3Hits", &fByVVLooseCombinedIsolationDeltaBetaCorr3Hits);
  mgr.book(prefix()+"_byVVLooseIsolationMVArun2017v2DBnewDMwLT2017", &fByVVLooseIsolationMVArun2017v2DBnewDMwLT2017);
  mgr.book(prefix()+"_byVVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017", &fByVVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017);
  mgr.book(prefix()+"_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017", &fByVVLooseIsolationMVArun2017v2DBoldDMwLT2017);
  mgr.book(prefix()+"_byVVTightIsolationMVArun2017v2DBnewDMwLT2017", &fByVVTightIsolationMVArun2017v2DBnewDMwLT2017);
  mgr.book(prefix()+"_byVVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017", &fByVVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017);
  mgr.book(prefix()+"_byVVTightIsolationMVArun2017v2DBoldDMwLT2017", &fByVVTightIsolationMVArun2017v2DBoldDMwLT2017);
  mgr.book(prefix()+"_decayModeFinding", &fDecayModeFinding);
  mgr.book(prefix()+"_decayModeFindingNewDMs", &fDecayModeFindingNewDMs);
  mgr.book(prefix()+"_lChTrkEta", &fLChTrkEta);
  mgr.book(prefix()+"_lChTrkPt", &fLChTrkPt);
  mgr.book(prefix()+"_lNeutrTrkEta", &fLNeutrTrkEta);
  mgr.book(prefix()+"_lNeutrTrkPt", &fLNeutrTrkPt);
  mgr.book(prefix()+"_IPxy", &fIPxy);
  mgr.book(prefix()+"_IPxySignif", &fIPxySignif);
  mgr.book(prefix()+"_charge", &fCharge);
  mgr.book(prefix()+"_decayMode", &fDecayMode);
  mgr.book(prefix()+"_mcNPizero", &fMcNPizero);
  mgr.book(prefix()+"_mcNProngs", &fMcNProngs);
  mgr.book(prefix()+"_nProngs", &fNProngs);
  mgr.book(prefix()+"_pdgOrigin", &fPdgOrigin);
}
