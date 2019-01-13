#ifndef MuonDumper_h
#define MuonDumper_h

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"

#include <string>
#include <vector>

#include "TTree.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/BaseDumper.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/FourVectorDumper.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

namespace reco {
  class Vertex;
}

class MuonDumper : public BaseDumper {
    public:
	MuonDumper(edm::ConsumesCollector&& iConsumesCollector, std::vector<edm::ParameterSet>& psets, const edm::InputTag& recoVertexTag);
	~MuonDumper();

        void book(TTree*);
        bool fill(edm::Event&, const edm::EventSetup&);
        void reset();

    private:
	void fillMCMatchInfo(size_t ic, edm::Handle<reco::GenParticleCollection>& genParticles, const pat::Muon& muon);
	
        edm::EDGetTokenT<edm::View<pat::Muon>> *muonToken;
        edm::EDGetTokenT<reco::GenParticleCollection> genParticleToken;
        edm::EDGetTokenT<edm::View<reco::Vertex>> vertexToken;

        std::vector<short> *q;

        std::vector<bool> *isGlobalMuon;
        
	// Muon Selectors (https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_selectors_Since_9_4_X)
	std::vector<bool> *isCutBasedIdLoose;
	std::vector<bool> *isCutBasedIdMedium;
	std::vector<bool> *isCutBasedIdMediumPrompt;
	std::vector<bool> *isCutBasedIdTight;
	std::vector<bool> *isCutBasedIdGlobalHighPt;
	std::vector<bool> *isCutBasedIdTrkHighPt;
	std::vector<bool> *isPFIsoVeryLoose;
	std::vector<bool> *isPFIsoLoose;
	std::vector<bool> *isPFIsoMedium;
	std::vector<bool> *isPFIsoTight;
	std::vector<bool> *isPFIsoVeryTight;
	//std::vector<bool> *isPFIsoVeryVeryTight;
	std::vector<bool> *isTkIsoLoose;
	std::vector<bool> *isTkIsoTight;
	std::vector<bool> *isSoftCutBasedId;
	// std::vector<bool> *isSoftMvaId;
	std::vector<bool> *isMvaLoose;
	std::vector<bool> *isMvaMedium;
	std::vector<bool> *isMvaTight;
	std::vector<bool> *isMiniIsoLoose;
	std::vector<bool> *isMiniIsoMedium;
	std::vector<bool> *isMiniIsoTight;
	std::vector<bool> *isMiniIsoVeryTight;
	//std::vector<bool> *isTriggerIdLoose;
	//std::vector<bool> *isInTimeMuon;
	//std::vector<bool> *isMultiIsoLoose;
	//std::vector<bool> *isMultiIsoMedium;
	
	std::vector<float> *relIsoDeltaBetaCorrected03; // isol cone 0.3
        std::vector<float> *relIsoDeltaBetaCorrected04; // isol cone 0.4
	
	edm::EDGetTokenT<double> *rhoToken;
	edm::EDGetTokenT<edm::View<pat::PackedCandidate> > *pfcandsToken;
	std::vector<float> *relMiniIso;
	std::vector<float> *effAreaMiniIso;
        
        // 4-vector for generator muon
        FourVectorDumper *MCmuon;
};
#endif
