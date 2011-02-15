//#######################################################################
// -*- C++ -*-
//       File Name:  InvMassVetoOnJets.cc
// Original Author:  Alexandros Attikis
//         Created:  14 February 2011
//     Description:  Designed to veto on DiJet and TriJet Invariant Masses
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################

#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/InvMassVetoOnJets.h"
#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/MakeTH.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1F.h"
#include "Math/GenVector/VectorUtil.h"
#include "DataFormats/Math/interface/LorentzVector.h"


namespace HPlus {
  InvMassVetoOnJets::Data::Data(const InvMassVetoOnJets *invMassVetoOnJets, bool passedEvent):
    fInvMassVetoOnJets(invMassVetoOnJets), fPassedEvent(passedEvent) {}
  InvMassVetoOnJets::Data::~Data() {}

  InvMassVetoOnJets::InvMassVetoOnJets(const edm::ParameterSet& iConfig, EventCounter& eventCounter, EventWeight& eventWeight):
    fPtCut(iConfig.getUntrackedParameter<double>("ptCut")),
    fEtaCut(iConfig.getUntrackedParameter<double>("etaCut")),
    fInvMassVetoOnJetsCount(eventCounter.addCounter("InvMassVetoOnJets main")),
    fInvMassVetoOnJetsPtCutSubCount(eventCounter.addSubCounter("InvMassVetoOnJets main", "PtCut")),
    fInvMassVetoOnJetsEtaCutSubCount(eventCounter.addSubCounter("InvMassVetoOnJets main", "EtaCut")),
    fInvMassVetoOnJetsDiJetsCutSubCount(eventCounter.addSubCounter("InvMassVetoOnJets main", "InvMassVetoOnDiJets cut")),
    fInvMassVetoOnJetsTriJetsCutSubCount(eventCounter.addSubCounter("InvMassVetoOnJets main", "InvMassVetoOnTriJets cut")),
    fEventWeight(eventWeight)
  {
    edm::Service<TFileService> fs;
    // Histograms
    hDiJetInvMass           = makeTH<TH1F>(*fs, "DiJetInvMass", "DiJetInvMass", 1000, 0.0, 1000.0);
    hDiJetInvMassCutFail    = makeTH<TH1F>(*fs, "DiJetInvMassCutFail", "DiJetInvMassCutFail", 1000, 0.0, 1000.0);
    hDiJetInvMassCutPass    = makeTH<TH1F>(*fs, "DiJetInvMassCutPass", "DiJetInvMassCutPass", 1000, 0.0, 1000.0);
    hTriJetInvMass          = makeTH<TH1F>(*fs, "TriJetInvMass", "TriJetInvMass", 1000, 0.0, 1000.0);
    hTriJetInvMassCutFail   = makeTH<TH1F>(*fs, "TriJetInvMassCutFail", "TriJetInvMassCutFail", 1000, 0.0, 1000.0);
    hTriJetInvMassCutPass   = makeTH<TH1F>(*fs, "TriJetInvMassCutPass", "TriJetInvMassCutPass", 1000, 0.0, 1000.0);
    hInvMass                = makeTH<TH1F>(*fs, "InvMass", "InvMass", 1000, 0.0, 1000.0);
    hInvMassCutFail         = makeTH<TH1F>(*fs, "InvMassCutFail", "InvMassCutFail", 1000, 0.0, 1000.0);
    hInvMassCutPass         = makeTH<TH1F>(*fs, "InvMassCutPass", "InvMassCutPass", 1000, 0.0, 1000.0);

  }

  InvMassVetoOnJets::~InvMassVetoOnJets() {}

  //  InvMassVetoOnJets::Data InvMassVetoOnJets::analyze( const reco::Candidate& tau, const edm::PtrVector<pat::Jet>& jets ){
  InvMassVetoOnJets::Data InvMassVetoOnJets::analyze( const edm::PtrVector<pat::Jet>& jets ){

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Description                                                                                                
    /// Uses the jet-collection to reconstruct all the possible di-jet combinations.The motivation behind the creation
    /// of this method is to be able to veto events with candidate di-jet combinations having an invariant mass close 
    /// to the mass of the W boson or the top quark. In this way we can get rid of hadronic events that include
    /// W->qq and t->bW decays.
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /// Declaration of variables    
    bool bPassedEvent = false;
    bool bInvMassCutFail = false;
    bool bInvMassWithinWWindow = false;
    bool bInvMassWithinTopWindow = false;
    const float WMass   = 80.399;  // PDG value
    const float WMassWindow   = 0.1*WMass;  // PDG value
    const float TopMass = 172.000; 
    const float TopMassWindow = 0.1*TopMass;

    /* DiJet code - works fine but obsolete -> Integrated with TriJet
    /// Return true if there are less than two jets.
    if(jets.size()<2) return Data(this, true);
    else{
      /// Loop over jet collection - mth Jet
      for(edm::PtrVector<pat::Jet>::const_iterator iter = jets.begin(); iter != jets.end(); ++iter) {
	edm::Ptr<pat::Jet> mJet = *iter;
	
	/// Loop over jet collection - nth Jet
	for(edm::PtrVector<pat::Jet>::const_iterator iter2 = iter+1; iter2 != jets.end(); ++iter2) {
	  edm::Ptr<pat::Jet> nJet = *iter2;
	  
	  /// Calculate the DiJet Mass
	  float DiJetInvMass = sqrt( pow(nJet->energy()+mJet->energy(),2) - (nJet->p4().Vect() + mJet->p4().Vect()).Mag2() );

	  /// Fill histograms
	  hDiJetInvMass->Fill(DiJetInvMass, fEventWeight.getWeight());
	  hInvMass->Fill(DiJetInvMass, fEventWeight.getWeight());

	  /// Make decision on DiJet Mass
	  if( DiJetInvMass <= (WMass+WMassWindow) && DiJetInvMass >= (WMass-WMassWindow) ){
	    bInvMassWithinWWindow = true;
	    hDiJetInvMassCutFail->Fill(DiJetInvMass, fEventWeight.getWeight());
	    hInvMassCutFail->Fill(DiJetInvMass, fEventWeight.getWeight());
	  }
	  else{
	    bInvMassWithinWWindow   = false;
	    bInvMassWithinTopWindow = false;
	    hDiJetInvMassCutPass->Fill(DiJetInvMass, fEventWeight.getWeight());
	    hInvMassCutPass->Fill(DiJetInvMass, fEventWeight.getWeight());
	  }
	  /// Make final boolean decision
	  if( (bInvMassWithinWWindow) || (bInvMassWithinTopWindow) ){
	    bPassedEvent = false;
	    hDiJetInvMassCutFail->Fill(DiJetInvMass, fEventWeight.getWeight());
	    break;
	  }
	  else{
	    bPassedEvent = true;
	    hDiJetInvMassCutPass->Fill(DiJetInvMass, fEventWeight.getWeight());
	  }

	}//eof: second jet loop
      }//eof: first jet loop
    */

    /// Return true if there are less than 2 jets since no calculation is possible (for safety)
    if(jets.size()<2){
      bPassedEvent = true;
      return Data(this, bPassedEvent);
    }
    /// If there are less than 3 jets only perform DiJet calculation
    else if(jets.size()<3){
      edm::PtrVector<pat::Jet>::const_iterator jet1 = jets.begin();
      edm::PtrVector<pat::Jet>::const_iterator jet2 = jets.begin()+1;
      const LorentzVector myWCandidate ( (*jet1)->p4()+(*jet2)->p4() );
      double DiJetInvMass = myWCandidate.M();
      /// Make decision on DiJet Mass
      if( DiJetInvMass <= (WMass+WMassWindow) && DiJetInvMass >= (WMass-WMassWindow) ){
	bInvMassWithinWWindow = true;
	hDiJetInvMassCutFail->Fill(DiJetInvMass, fEventWeight.getWeight());
	hInvMassCutFail->Fill(DiJetInvMass, fEventWeight.getWeight());
	bPassedEvent = false;
	hDiJetInvMassCutFail->Fill(DiJetInvMass, fEventWeight.getWeight());
      }
      else{
	bInvMassWithinWWindow = false;
	bPassedEvent = true;
	hDiJetInvMassCutPass->Fill(DiJetInvMass, fEventWeight.getWeight());
	hInvMassCutPass->Fill(DiJetInvMass, fEventWeight.getWeight());
      }
    }//eof: else if(jets.size()<3){
    else{
      /// If NJets>3, perform a triple loop within which to calculate di-jet and tri-jet invariant mass

      /// loop over jet collection - mth Jet
      for(edm::PtrVector<pat::Jet>::const_iterator jet = jets.begin(); jet != jets.end(); ++jet) {
	edm::Ptr<pat::Jet> mJet = *jet;
	
	if(!(mJet->pt() > fPtCut)) continue;
	if(!(std::abs(mJet->eta()) < fEtaCut)) continue;

	/// Loop over jet collection - oth Jet, where: n = m+1
	for(edm::PtrVector<pat::Jet>::const_iterator jet2 = jet+1; jet2 != jets.end(); ++jet2) {
	  edm::Ptr<pat::Jet> nJet = *jet2;
	  
	  if(!(nJet->pt() > fPtCut)) continue;
	  if(!(std::abs(nJet->eta()) < fEtaCut)) continue;

	  /// Calculate the DiJet Mass
	  // float DiJetInvMass = sqrt( pow(nJet->energy()+mJet->energy(),2) - (nJet->p4().Vect() + mJet->p4().Vect()).Mag2() );
	  const LorentzVector myWCandidate ( mJet->p4() + nJet->p4() );
	  double DiJetInvMass = myWCandidate.M();
	  
	  /// Fill histograms
	  hDiJetInvMass->Fill(DiJetInvMass, fEventWeight.getWeight());
	  hInvMass->Fill(DiJetInvMass, fEventWeight.getWeight());
	  
	  /// Make decision on DiJet Mass
	  if( DiJetInvMass <= (WMass+WMassWindow) && DiJetInvMass >= (WMass-WMassWindow) ){
	    bInvMassWithinWWindow = true;
	    bPassedEvent = false;
	    hDiJetInvMassCutFail->Fill(DiJetInvMass, fEventWeight.getWeight());
	    hInvMassCutFail->Fill(DiJetInvMass, fEventWeight.getWeight());
	    break;
	  }
	  else{
	    bInvMassWithinWWindow   = false;
	    bPassedEvent = true;
	    hDiJetInvMassCutPass->Fill(DiJetInvMass, fEventWeight.getWeight());
	    hInvMassCutPass->Fill(DiJetInvMass, fEventWeight.getWeight());
	  }
	  /// Loop over jet collection - oth Jet, where: o = n+1 = m+2
	  for(edm::PtrVector<pat::Jet>::const_iterator jet3 = jet+2; jet3 != jets.end(); ++jet2) {
	    edm::Ptr<pat::Jet> oJet = *jet3;
	    
	    /// Increment counter if 3rd loop also survives jet Pt and Eta Cuts
	    if(!(oJet->pt() > fPtCut)) continue;
	    increment(fInvMassVetoOnJetsPtCutSubCount);
	    
	    if(!(std::abs(oJet->eta()) < fEtaCut)) continue;
	    increment(fInvMassVetoOnJetsEtaCutSubCount);

	    /// Calculate the TriJet Mass
	    const LorentzVector myTopCandidate ( mJet->p4() + nJet->p4() + oJet->p4() );
	    double TriJetInvMass = myTopCandidate.M();
	    
	    /// Fill histograms
	    hTriJetInvMass->Fill(TriJetInvMass, fEventWeight.getWeight());
	    hInvMass->Fill(DiJetInvMass, fEventWeight.getWeight());
	    
	    /// Make decision on TriJet Mass
	    if( TriJetInvMass <= (TopMass+TopMassWindow) && DiJetInvMass >= (TopMass-TopMassWindow) ){
	      bInvMassWithinTopWindow = true;
	      bPassedEvent = false;
	      hTriJetInvMassCutFail->Fill(TriJetInvMass, fEventWeight.getWeight());
	      hInvMassCutFail->Fill(TriJetInvMass, fEventWeight.getWeight());
	      break;
	    }
	    else{
	      bInvMassWithinTopWindow = false;
	      bPassedEvent = true;
	      hTriJetInvMassCutPass->Fill(TriJetInvMass, fEventWeight.getWeight());
	      hInvMassCutPass->Fill(TriJetInvMass, fEventWeight.getWeight());
	    }
	  }//eof: third jet loop
	}//eof: second jet loop
      }//eof: first jet loop
    }// njets >3 

    if(!bPassedEvent && bInvMassWithinWWindow) increment(fInvMassVetoOnJetsDiJetsCutSubCount);
    if(!bPassedEvent && bInvMassWithinWWindow) increment(fInvMassVetoOnJetsTriJetsCutSubCount);

    return Data(this, bPassedEvent);
  }//eof:  InvMassVetoOnJets::Data InvMassVetoOnJets::InvMassVetoOnJets( const edm::PtrVector<pat::Jet>& jets ){
}//eof: namespace HPlus {
