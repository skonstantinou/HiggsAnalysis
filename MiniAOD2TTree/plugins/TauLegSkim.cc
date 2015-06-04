/** \class TauLegSkim
 *
 *  
 *  Filter to select events for 
 *  tau+MET trigger tau-leg efficiency study
 *
 *  \author Sami Lehti  -  HIP Helsinki
 *
 */

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"

#include "FWCore/Framework/interface/TriggerNamesService.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "FWCore/Framework/interface/LuminosityBlock.h"

#include <iostream>
#include <regex>

class TauLegSkim : public edm::EDFilter {

    public:
        explicit TauLegSkim(const edm::ParameterSet&);
        ~TauLegSkim();

  	virtual bool filter(edm::Event&, const edm::EventSetup& );

   private:
	edm::InputTag triggerResults;
	std::vector<std::string> triggerBits;

        edm::InputTag	tauCollection;
        edm::InputTag	muonCollection;

        std::vector<std::string> tauDiscriminators;
        std::vector<std::string> muonDiscriminators;

	double tauPtCut,tauEtaCut;
	double muonPtCut,muonEtaCut;

        int nEvents, nSelectedEvents;
};

TauLegSkim::TauLegSkim(const edm::ParameterSet& iConfig) {
    triggerResults     = iConfig.getParameter<edm::InputTag>("TriggerResults");
    triggerBits        = iConfig.getParameter<std::vector<std::string> >("HLTPaths");

    tauCollection      = iConfig.getParameter<edm::InputTag>("TauCollection");
    tauDiscriminators  = iConfig.getParameter<std::vector<std::string> >("TauDiscriminators");
    muonCollection     = iConfig.getParameter<edm::InputTag>("MuonCollection");
    muonDiscriminators = iConfig.getParameter<std::vector<std::string> >("MuonDiscriminators");

    tauPtCut           = iConfig.getParameter<double>("TauPtCut");
    tauEtaCut          = iConfig.getParameter<double>("TauEtaCut");                            

    muonPtCut          = iConfig.getParameter<double>("MuonPtCut");                            
    muonPtCut          = iConfig.getParameter<double>("MuonEtaCut");                            

    nEvents         = 0;
    nSelectedEvents = 0;
}


TauLegSkim::~TauLegSkim(){
    std::cout << "TauLegSkim: " //  	edm::LogVerbatim("TauLegSkim") 
              << " Number_events_read " << nEvents
              << " Number_events_kept " << nSelectedEvents
              << " Efficiency         " << ((double)nSelectedEvents)/((double) nEvents) << std::endl;
}


bool TauLegSkim::filter(edm::Event& iEvent, const edm::EventSetup& iSetup ){

    nEvents++;

    // Trigger bits
    edm::Handle<edm::TriggerResults> trghandle;
    iEvent.getByLabel(triggerResults,trghandle);
    if(trghandle.isValid()){
        edm::TriggerResults tr = *trghandle;
        bool fromPSetRegistry;
        edm::Service<edm::service::TriggerNamesService> tns;
        std::vector<std::string> hlNames; 
        tns->getTrigPaths(tr, hlNames, fromPSetRegistry);

//	bool passed = false;
        for(size_t i = 0; i < triggerBits.size(); ++i){
	    std::regex hlt_re(triggerBits[i]);
	    int n = 0;
            for(std::vector<std::string>::const_iterator j = hlNames.begin(); j!= hlNames.end(); ++j){
		if (std::regex_search(*j, hlt_re)) {
		    if(trghandle->accept(n)) {
//			passed = true;
                        break;
		    }
                }
		n++;
            }
        }
//	if(!passed) return false; 
    }

    // Tau
    std::vector<pat::Tau> selectedTaus;
    edm::Handle<edm::View<pat::Tau> > tauhandle;
    iEvent.getByLabel(tauCollection, tauhandle);
    if(tauhandle.isValid()){
        for(size_t i=0; i<tauhandle->size(); ++i) {
            const pat::Tau& tau = tauhandle->at(i);
	    if(tau.p4().pt() < tauPtCut) continue;
	    if(abs(tau.p4().eta()) > tauEtaCut) continue;
	    bool d = true;
	    for(size_t j=0; j<tauDiscriminators.size(); ++j) {
		d = d && tau.tauID(tauDiscriminators[j]);
	    }
	    if(!d) continue;
	    selectedTaus.push_back(tau);
	}
    }
    if(selectedTaus.size() != 1) return false;

    // Muon
    std::vector<pat::Muon> selectedMuons;
    edm::Handle<edm::View<pat::Muon> > muonhandle;
    iEvent.getByLabel(muonCollection, muonhandle);
    if(muonhandle.isValid()){
        for(size_t i=0; i<muonhandle->size(); ++i) {
            const pat::Muon& muon = muonhandle->at(i);
            if(muon.p4().pt() < muonPtCut) continue;
            if(abs(muon.p4().eta()) > muonEtaCut) continue;
	    selectedMuons.push_back(muon);
        }
    }
    if(selectedMuons.size() != 1) return false;
/*
    double muTauInvMass = (selectedMuons[0].p4() + selectedTaus[0].p4()).M();
std::cout << "check muTauInvMass " << muTauInvMass << std::endl;
    if(muTauInvMass < 70) return false;
*/
    nSelectedEvents++;
    return true;
}

DEFINE_FWK_MODULE(TauLegSkim);   

