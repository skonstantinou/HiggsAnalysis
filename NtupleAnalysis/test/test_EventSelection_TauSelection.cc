// -*- c++ -*-
#include "catch.hpp"

#include "EventSelection/interface/TauSelection.h"
#include "Framework/interface/Exception.h"
#include "Framework/interface/ParameterSet.h"
#include "Framework/interface/EventWeight.h"
#include "Framework/interface/HistoWrapper.h"
#include "Framework/interface/BranchManager.h"
#include "DataFormat/interface/Event.h"

#include "test_createTree.h"

#include <string>
#include <iostream>
#include "TTree.h"

TEST_CASE("TauSelection", "[EventSelection]") {
  SECTION("Default (empty) discriminators") {
    boost::property_tree::ptree tmp = getMinimalConfig();
    ParameterSet pset1(tmp, true);
    REQUIRE_NOTHROW(Event event1(pset1));
  }
  SECTION("againstElectronDiscr validity") {
    boost::property_tree::ptree tmp = getMinimalConfig();
    tmp.put("TauSelection.againstElectronDiscr", "");
    ParameterSet pset1(tmp, true);
    REQUIRE_NOTHROW(Event event1(pset1));
    tmp.put("TauSelection.againstElectronDiscr", "againstElectronLooseMVA5");
    ParameterSet pset2(tmp, true);
    REQUIRE_NOTHROW(Event event2(pset2));
    tmp.put("TauSelection.againstElectronDiscr", "dummy");
    ParameterSet pset3(tmp, true);
    REQUIRE_THROWS_AS(Event event3(pset3), hplus::Exception);
  }
  SECTION("againstMuonDiscr validity") {
    boost::property_tree::ptree tmp = getMinimalConfig();
    tmp.put("TauSelection.againstMuonDiscr", "");
    ParameterSet pset1(tmp, true);
    REQUIRE_NOTHROW(Event event1(pset1));
    tmp.put("TauSelection.againstMuonDiscr", "againstMuonTight3");
    ParameterSet pset2(tmp, true);
    REQUIRE_NOTHROW(Event event2(pset2));
    tmp.put("TauSelection.againstMuonDiscr", "dummy");
    ParameterSet pset3(tmp, true);
    REQUIRE_THROWS_AS(Event event3(pset3), hplus::Exception);
  }
  SECTION("isolationDiscr validity") {
    boost::property_tree::ptree tmp = getMinimalConfig();
    tmp.put("TauSelection.isolationDiscr", "");
    ParameterSet pset1(tmp, true);
    REQUIRE_NOTHROW(Event event1(pset1));
    tmp.put("TauSelection.isolationDiscr", "byLooseCombinedIsolationDeltaBetaCorr3Hits");
    ParameterSet pset2(tmp, true);
    REQUIRE_NOTHROW(Event event2(pset2));
    tmp.put("TauSelection.isolationDiscr", "dummy");
    ParameterSet pset3(tmp, true);
    REQUIRE_THROWS_AS(Event event3(pset3), hplus::Exception);
  }

  // Create config for testing
  boost::property_tree::ptree tmp = getMinimalConfig();
  tmp.put("TauSelection.applyTriggerMatching", true);
  tmp.put("TauSelection.triggerMatchingCone", 0.1);
  tmp.put("TauSelection.tauPtCut", 41.0);
  tmp.put("TauSelection.tauEtaCut", 2.1);
  tmp.put("TauSelection.tauLdgTrkPtCut", 10.0);
  tmp.put("TauSelection.prongs", 1);
  tmp.put("TauSelection.rtau", -10.0);
  tmp.put("TauSelection.againstElectronDiscr", "againstElectronLooseMVA5");
  tmp.put("TauSelection.againstMuonDiscr", "againstMuonTight3");
  tmp.put("TauSelection.isolationDiscr", "byLooseCombinedIsolationDeltaBetaCorr3Hits");
  ParameterSet psetDefault(tmp, true);
  // Create necessary objects for testing
  TDirectory* f = getDirectory("test_TauSelection");
  CommonPlots* commonPlotsPointer = 0;
  EventWeight weight;
  HistoWrapper histoWrapper(weight, "Debug");
  EventCounter ec(weight);
  TauSelection sel1(psetDefault.getParameter<ParameterSet>("TauSelection"),
                    ec, histoWrapper, commonPlotsPointer, "default");
  sel1.bookHistograms(f);
  
  // Setup events for testing
  auto tree = new TTree("Events", "Events");
  unsigned int run;           tree->Branch("run",   &run);
  unsigned int lumi;          tree->Branch("lumi",  &lumi);
  unsigned long long nevent;  tree->Branch("event", &nevent);
  std::vector<float> pt;   tree->Branch("Taus_pt", &pt);
  std::vector<float> eta;  tree->Branch("Taus_eta", &eta);
  std::vector<float> phi;  tree->Branch("Taus_phi", &phi);
  std::vector<float> e;    tree->Branch("Taus_e", &e);
  std::vector<float> mcpt;   tree->Branch("Taus_pt_MCVisibleTau", &mcpt);
  std::vector<float> mceta;  tree->Branch("Taus_eta_MCVisibleTau", &mceta);
  std::vector<float> mcphi;  tree->Branch("Taus_phi_MCVisibleTau", &mcphi);
  std::vector<float> mce;    tree->Branch("Taus_e_MCVisibleTau", &mce);
  std::vector<short> mcPdgId;    tree->Branch("Taus_pdgId", &mcPdgId);
  std::vector<short> pdgOrigin;    tree->Branch("Taus_pdgOrigin", &pdgOrigin);
  std::vector<float> lTrkPt;   tree->Branch("Taus_lChTrkPt", &lTrkPt);
  std::vector<float> lTrkEta;  tree->Branch("Taus_lChTrkEta", &lTrkEta);
  std::vector<int> decayMode;    tree->Branch("Taus_decayMode", &decayMode);
  std::vector<short> nProngs;    tree->Branch("Taus_nProngs", &nProngs);
  std::vector<short> mcProngs;    tree->Branch("Taus_mcNProngs", &mcProngs);
  std::vector<bool> eDiscr;    tree->Branch("Taus_againstElectronLooseMVA5", &eDiscr);
  std::vector<bool> e2Discr;    tree->Branch("Taus_againstElectronLooseMVA5", &e2Discr);
  std::vector<bool> e3Discr;    tree->Branch("Taus_againstElectronMediumMVA5", &e3Discr);
  std::vector<bool> muDiscr;   tree->Branch("Taus_againstMuonTight3", &muDiscr);
  std::vector<bool> isolDiscr; tree->Branch("Taus_byLooseCombinedIsolationDeltaBetaCorr3Hits", &isolDiscr);
  std::vector<bool> dm;        tree->Branch("Taus_decayModeFinding", &dm);
  std::vector<float> trgpt;   tree->Branch("HLTTau_pt", &trgpt);
  std::vector<float> trgeta;  tree->Branch("HLTTau_eta", &trgeta);
  std::vector<float> trgphi;  tree->Branch("HLTTau_phi", &trgphi);
  std::vector<float> trge;    tree->Branch("HLTTau_e", &trge);
  
  run = 1;
  lumi = 1;
  nevent = 1; // no trigger taus
  dm  = std::vector<bool>{true, true, true, true, true, true, true, true};
  eDiscr = std::vector<bool>{true, true, true, true, true, true, true, true};
  e2Discr = std::vector<bool>{true, true, true, true, true, true, true, true};
  e3Discr = std::vector<bool>{true, true, true, false, false, false, false, false};
  muDiscr = std::vector<bool>{true, true, true, true, true, true, true, true};
  isolDiscr = std::vector<bool>{true, true, true, true, true, true, true, true};
  pt  = std::vector<float>{50.f,  20.f,  11.f,  51.f,  75.f,  11.f,  13.f, 90.f};
  eta = std::vector<float>{-2.3f, -2.3f, -1.1f, -1.4f,  0.2f,  0.7f, 3.3f,  3.3f};
  phi = std::vector<float>{-2.9f, -0.5f,  1.f,  -2.3f, -1.7f,  0.3f, 0.8f,  1.1f};
  e   = std::vector<float>{50.f,  20.f,  11.f,  50.f,  75.f,  11.f,  13.f, 90.f};
  mcpt  = std::vector<float>{50.f,  20.f,  11.f,  51.f,  75.f,  11.f,  13.f, 90.f};
  mceta = std::vector<float>{-2.3f, -2.3f, -1.1f, -1.4f,  0.2f,  0.7f, 3.3f,  3.3f};
  mcphi = std::vector<float>{-2.9f, -0.5f,  1.f,  -2.3f, -1.7f,  0.3f, 0.8f,  1.1f};
  mce   = std::vector<float>{50.f,  20.f,  11.f,  50.f,  75.f,  11.f,  13.f, 90.f};
  mcPdgId = std::vector<short>{15,    15,    15,    15,    15,    15,    15,   15};
  pdgOrigin = std::vector<short>{0, 0, 0, 0, 0, 0, 0, 0};
  lTrkPt = std::vector<float>{5.f,  20.f,  11.f,  5.f,  70.f,  11.f,  13.f, 90.f};
  lTrkEta = std::vector<float>{-2.3f, -2.3f, -1.1f, -1.4f, 0.23f, 0.7f, 3.3f, 3.3f};
  decayMode = std::vector<int>{1, 5, 11, 11, 6, 0, 2, 10};
  nProngs = std::vector<short>{1, 1, 1, 1, 1, 1, 1, 1, 1};
  mcProngs = std::vector<short>{1, 1, 1, 1, 1, 1, 1, 1, 1};
  tree->Fill();
  nevent = 2; // with trigger taus
  trgpt  = std::vector<float>{51.f,   11.1f,  75.3f,  50.4f};
  trgeta = std::vector<float>{-2.24f, -1.12f,  0.22f,  -1.43f};
  trgphi = std::vector<float>{-2.93f,   1.05f,  -1.74f, -2.27f};
  trge   = std::vector<float>{51.f,   11.1f,  75.3f,  50.4f};
  tree->Fill();
  nevent = 3; // dm
  dm  = std::vector<bool>{true, false, false, false, true, true, false, true};
  tree->Fill();
  nevent = 4; // against e
  dm  = std::vector<bool>{true, true, true, true, true, true, true, true};
  eDiscr = std::vector<bool>{true, false, false, false, true, true, false, true};
  tree->Fill();
  nevent = 5; // against mu
  eDiscr = std::vector<bool>{true, true, true, true, true, true, true, true};
  muDiscr = std::vector<bool>{true, false, false, false, true, true, false, true};
  tree->Fill();
  nevent = 6; // isolation
  muDiscr = std::vector<bool>{true, true, true, true, true, true, true, true};
  isolDiscr = std::vector<bool>{true, false, false, false, true, true, false, true};
  tree->Fill();
  nevent = 7; // anti-isolation
  muDiscr = std::vector<bool>{true, true, true, true, true, true, true, true};
  isolDiscr = std::vector<bool>{false, false, false, false, false, true, false, true};
  tree->Fill(); 
  nevent = 8; // e->tau
  isolDiscr = std::vector<bool>{true, false, false, false, true, true, false, true};
  mcPdgId = std::vector<short>{11,    11,    11,    11,    11,    11,    11,   11};
  tree->Fill();
  nevent = 9; // mu->tau
  mcPdgId = std::vector<short>{13,    13,    13,    13,    13,    13,    13,   13};
  tree->Fill();
  nevent = 10; // jet->tau
  mcPdgId = std::vector<short>{2,    2,    2,    2,    2,    2,    2,   2};
  tree->Fill();
  
  
  BranchManager mgr;
  mgr.setTree(tree);
  Event event(psetDefault);
  //event.setupBranches(mgr);
  
  SECTION("trg matching swithched off") {
    tmp.put("TauSelection.applyTriggerMatching", false);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet noTrgPset(tmp,true);
    TauSelection tausel(noTrgPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(noTrgPset);
    event2.setupBranches(mgr);
    mgr.setEntry(0);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 8 );
  }
  SECTION("trg matching swithched off") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(0);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 0 );
    mgr.setEntry(1);
    data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 4 );
  }  
  SECTION("decay mode finding") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 4 );
    mgr.setEntry(2);
    data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 );
  }
  SECTION("generic discriminators") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    boost::property_tree::ptree discrs;
    boost::property_tree::ptree child;
    child.put("", "againstElectronLooseMVA5");
    discrs.push_back(std::make_pair("", child));
    child.put("", "againstElectronMediumMVA5");
    discrs.push_back(std::make_pair("", child));
    child.put("", "againstElectronLooseMVA5");
    discrs.push_back(std::make_pair("", child));
    tmp.add_child("TauSelection.discriminators", discrs);
    ParameterSet newPset(tmp, true);
    Event event2(newPset);
    event2.setupBranches(mgr);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 );
    mgr.setEntry(3);
    data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 1 );
  }
  SECTION("against e discriminator") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    Event event2(newPset);
    event2.setupBranches(mgr);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 4 );
    mgr.setEntry(3);
    data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 );
  }
  SECTION("against mu discriminator") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 4 );
    mgr.setEntry(4);
    data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 );
  }  
  SECTION("pt cut") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", 41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 3 );
  }  
  SECTION("eta cut") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 1.2);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 );
  }
  SECTION("ldg trg pt cut") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 10.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 );
  }
  SECTION("nprongs == 1") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", 1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 1 );
  }
  SECTION("nprongs == 3") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", 3);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 );
  } 
  SECTION("nprongs == 1 or 3") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", 13);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 3 );
  } 
  SECTION("isolation") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 4 );
    mgr.setEntry(5);
    data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 );
  } 
  SECTION("anti-isolation") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 4 );
    CHECK( data.getAntiIsolatedTaus().size() == 0 );
    CHECK( data.isAntiIsolated() == false );
    CHECK( data.hasIdentifiedTaus() == true );
    CHECK( data.hasAntiIsolatedTaus() == false );
    mgr.setEntry(5);
    data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 );
    CHECK( data.getAntiIsolatedTaus().size() == 2 );
    CHECK( data.isAntiIsolated() == false );
    CHECK( data.hasIdentifiedTaus() == true );
    CHECK( data.hasAntiIsolatedTaus() == true );
    mgr.setEntry(6);
    data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 0 );
    CHECK( data.getAntiIsolatedTaus().size() == 4 );
    CHECK( data.isAntiIsolated() == true );
    CHECK( data.hasIdentifiedTaus() == false );
    CHECK( data.hasAntiIsolatedTaus() == true );
  }
  SECTION("rtau") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.5);
    tmp.put("TauSelection.prongs", -1);
    tmp.put("TauSelection.rtau", 0.5);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK( data.getSelectedTaus().size() == 2 ); 
    CHECK( std::fabs(data.getRtauOfSelectedTau() - 0.93928) < 0.0001 ); 
  } 
  SECTION("getSelectedTau() behavior") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.5);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(0);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    REQUIRE_THROWS_AS ( data.getSelectedTau(), hplus::Exception ); 
    mgr.setEntry(1);
    data = tausel.silentAnalyze(event2);
    REQUIRE_NOTHROW ( data.getSelectedTau() ); 
  }
  SECTION("sorting of selected taus") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "noTrgMatch");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    CHECK ( data.getSelectedTaus()[0].pt() == 75. );
    CHECK ( data.getSelectedTaus()[1].pt() == 51. ); 
    CHECK ( data.getSelectedTaus()[2].pt() == 50. ); 
    CHECK ( data.getSelectedTaus()[3].pt() == 11. ); 
  }
  SECTION("tau mis-ID SF (non-configured)") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "misIDSF");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    REQUIRE( data.hasIdentifiedTaus() );
    CHECK( data.getTauMisIDSF() == 1.0 );
    CHECK( data.getAntiIsolatedTauMisIDSF() == 1.0 );
  }
  SECTION("tau mis-ID SF (etotau1)") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    tmp.put("TauSelection.tauMisidetificationEToTauSF", 0.1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "misIDSF");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(7);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    REQUIRE( data.hasIdentifiedTaus() );
    CHECK( data.getSelectedTau().pdgId() == 11 );
    CHECK( data.getTauMisIDSF() == Approx(0.1) );
    CHECK( data.getAntiIsolatedTauMisIDSF() == Approx(0.1) );
  }
  SECTION("tau mis-ID SF (etotau2)") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    tmp.put("TauSelection.tauMisidetificationEToTauBarrelSF", 0.1);
    tmp.put("TauSelection.tauMisidetificationEToTauEndcapSF", 0.5);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "misIDSF");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(7);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    REQUIRE( data.hasIdentifiedTaus() );
    CHECK( data.getSelectedTau().pdgId() == 11 );
    CHECK( data.getTauMisIDSF() == Approx(0.1) );
    CHECK( data.getAntiIsolatedTauMisIDSF() == Approx(0.1) );
  }
  SECTION("tau mis-ID SF (mutotau1)") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    tmp.put("TauSelection.tauMisidetificationMuToTauSF", 0.1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "misIDSF");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(8);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    REQUIRE( data.hasIdentifiedTaus() );
    CHECK( data.getSelectedTau().pdgId() == 13 );
    CHECK( data.getTauMisIDSF() == Approx(0.1) );
    CHECK( data.getAntiIsolatedTauMisIDSF() == Approx(0.1) );
  }
  SECTION("tau mis-ID SF (mutotau2)") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    tmp.put("TauSelection.tauMisidetificationMuToTauBarrelSF", 0.1);
    tmp.put("TauSelection.tauMisidetificationMuToTauEndcapSF", 0.5);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "misIDSF");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(8);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    REQUIRE( data.hasIdentifiedTaus() );
    CHECK( data.getSelectedTau().pdgId() == 13 );
    CHECK( data.getTauMisIDSF() == Approx(0.1) );
    CHECK( data.getAntiIsolatedTauMisIDSF() == Approx(0.1) );
  }
  SECTION("tau mis-ID SF (jettotau1)") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    tmp.put("TauSelection.tauMisidetificationJetToTauSF", 0.1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "misIDSF");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(9);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    REQUIRE( data.hasIdentifiedTaus() );
    CHECK( data.getSelectedTau().pdgId() == 2 );
    CHECK( data.getTauMisIDSF() == Approx(0.1) );
    CHECK( data.getAntiIsolatedTauMisIDSF() == Approx(0.1) );
  }
  SECTION("tau mis-ID SF (jettotau2)") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    tmp.put("TauSelection.tauMisidetificationJetToTauBarrelSF", 0.1);
    tmp.put("TauSelection.tauMisidetificationJetToTauEndcapSF", 0.5);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "misIDSF");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(9);
    TauSelection::Data data = tausel.silentAnalyze(event2);
    REQUIRE( data.hasIdentifiedTaus() );
    CHECK( data.getSelectedTau().pdgId() == 2 );
    CHECK( data.getTauMisIDSF() == Approx(0.1) );
    CHECK( data.getAntiIsolatedTauMisIDSF() == Approx(0.1) );
  }
  SECTION("protection for double counting of events") {
    tmp.put("TauSelection.applyTriggerMatching", true);
    tmp.put("TauSelection.tauPtCut", -41.0);
    tmp.put("TauSelection.tauEtaCut", 12.1);
    tmp.put("TauSelection.tauLdgTrkPtCut", 0.0);
    tmp.put("TauSelection.prongs", -1);
    ParameterSet newPset(tmp,true);
    TauSelection tausel(newPset.getParameter<ParameterSet>("TauSelection"),
                        ec, histoWrapper, commonPlotsPointer, "dblcount");
    tausel.bookHistograms(f);
    Event event2(newPset);
    event2.setupBranches(mgr);
    mgr.setEntry(1);
    CHECK( ec.getValueByName("passed tau selection (dblcount)") == 0);
    REQUIRE_NOTHROW( tausel.silentAnalyze(event2) );
    CHECK( ec.getValueByName("passed tau selection (dblcount)") == 0);
    REQUIRE_NOTHROW( tausel.analyze(event2) );
    CHECK( ec.getValueByName("passed tau selection (dblcount)") == 1);
    REQUIRE_THROWS_AS( tausel.analyze(event2), hplus::Exception );
    REQUIRE_THROWS_AS( tausel.silentAnalyze(event2), hplus::Exception );
  }
  
  ec.setOutput(f);
  ec.serialize();
  closeDirectory(f);
}