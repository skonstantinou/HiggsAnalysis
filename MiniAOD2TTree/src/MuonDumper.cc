#include "HiggsAnalysis/MiniAOD2TTree/interface/MuonDumper.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/MiniIsolation.h"

#include "DataFormats/VertexReco/interface/Vertex.h"

MuonDumper::MuonDumper(edm::ConsumesCollector&& iConsumesCollector, std::vector<edm::ParameterSet>& psets, const edm::InputTag& recoVertexTag)
: genParticleToken(iConsumesCollector.consumes<reco::GenParticleCollection>(edm::InputTag("prunedGenParticles"))),
  vertexToken(iConsumesCollector.consumes<edm::View<reco::Vertex>>(recoVertexTag)) {
    inputCollections = psets;
    booked           = false;

    pt  = new std::vector<double>[inputCollections.size()];
    eta = new std::vector<double>[inputCollections.size()];    
    phi = new std::vector<double>[inputCollections.size()];    
    e   = new std::vector<double>[inputCollections.size()];    

    q   = new std::vector<short>[inputCollections.size()];

    //p4  = new std::vector<reco::Candidate::LorentzVector>[inputCollections.size()];
    //pdgId = new std::vector<short>[inputCollections.size()];
    isGlobalMuon = new std::vector<bool>[inputCollections.size()];
    
    isCutBasedIdLoose = new std::vector<bool>[inputCollections.size()];
    isCutBasedIdMedium = new std::vector<bool>[inputCollections.size()];
    isCutBasedIdMediumPrompt = new std::vector<bool>[inputCollections.size()];
    isCutBasedIdTight = new std::vector<bool>[inputCollections.size()];
    isCutBasedIdGlobalHighPt = new std::vector<bool>[inputCollections.size()];
    isCutBasedIdTrkHighPt = new std::vector<bool>[inputCollections.size()];
    isPFIsoVeryLoose = new std::vector<bool>[inputCollections.size()];
    isPFIsoLoose = new std::vector<bool>[inputCollections.size()];
    isPFIsoMedium = new std::vector<bool>[inputCollections.size()];
    isPFIsoTight = new std::vector<bool>[inputCollections.size()];
    isPFIsoVeryTight = new std::vector<bool>[inputCollections.size()];
    //isPFIsoVeryVeryTight = new std::vector<bool>[inputCollections.size()];                                                                                                               
    isTkIsoLoose = new std::vector<bool>[inputCollections.size()];
    isTkIsoTight = new std::vector<bool>[inputCollections.size()];
    isSoftCutBasedId = new std::vector<bool>[inputCollections.size()];
    // isSoftMvaId = new std::vector<bool>[inputCollections.size()];                                                                                                               
    isMvaLoose = new std::vector<bool>[inputCollections.size()];
    isMvaMedium = new std::vector<bool>[inputCollections.size()];
    isMvaTight = new std::vector<bool>[inputCollections.size()];
    isMiniIsoLoose = new std::vector<bool>[inputCollections.size()];
    isMiniIsoMedium = new std::vector<bool>[inputCollections.size()];
    isMiniIsoTight = new std::vector<bool>[inputCollections.size()];
    isMiniIsoVeryTight = new std::vector<bool>[inputCollections.size()];
    //isTriggerIdLoose = new std::vector<bool>[inputCollections.size()];
    //isInTimeMuon = new std::vector<bool>[inputCollections.size()];
    //isMultiIsoLoose = new std::vector<bool>[inputCollections.size()];
    //isMultiIsoMedium = new std::vector<bool>[inputCollections.size()];    
    
    relIsoDeltaBetaCorrected03 = new std::vector<float>[inputCollections.size()];
    relIsoDeltaBetaCorrected04 = new std::vector<float>[inputCollections.size()];

    MCmuon = new FourVectorDumper[inputCollections.size()];
    
    nDiscriminators = inputCollections[0].getParameter<std::vector<std::string> >("discriminators").size();
    discriminators = new std::vector<bool>[inputCollections.size()*nDiscriminators];
    
    muonToken = new edm::EDGetTokenT<edm::View<pat::Muon>>[inputCollections.size()];
    rhoToken = new edm::EDGetTokenT<double>[inputCollections.size()];
    pfcandsToken      = new edm::EDGetTokenT<edm::View<pat::PackedCandidate> >[inputCollections.size()];
    relMiniIso        = new std::vector<float>[inputCollections.size()];
    effAreaMiniIso    = new std::vector<float>[inputCollections.size()];
    
    for(size_t i = 0; i < inputCollections.size(); ++i){
      edm::InputTag inputtag = inputCollections[i].getParameter<edm::InputTag>("src");
      muonToken[i] = iConsumesCollector.consumes<edm::View<pat::Muon>>(inputtag);
    
      edm::InputTag rhoSource = inputCollections[i].getParameter<edm::InputTag>("rhoSource");
      rhoToken[i] = iConsumesCollector.consumes<double>(rhoSource);
      
      edm::InputTag pfcandinputtag = inputCollections[i].getParameter<edm::InputTag>("pfcands");
      pfcandsToken[i] = iConsumesCollector.consumes<edm::View<pat::PackedCandidate>>(pfcandinputtag);
    }
    
    useFilter = false;
    for(size_t i = 0; i < inputCollections.size(); ++i){
	bool param = inputCollections[i].getUntrackedParameter<bool>("filter",false);
        if(param) useFilter = true;
    }
}
MuonDumper::~MuonDumper(){}

void MuonDumper::book(TTree* tree){
    booked = true;
    for(size_t i = 0; i < inputCollections.size(); ++i){
        std::string name = inputCollections[i].getUntrackedParameter<std::string>("branchname","");
        if(name.length() == 0) name = inputCollections[i].getParameter<edm::InputTag>("src").label();
    
        tree->Branch((name+"_pt").c_str(),&pt[i]);
        tree->Branch((name+"_eta").c_str(),&eta[i]);
        tree->Branch((name+"_phi").c_str(),&phi[i]);
        tree->Branch((name+"_e").c_str(),&e[i]);

        tree->Branch((name+"_charge").c_str(),&q[i]);

        tree->Branch((name+"_isGlobalMuon").c_str(),&isGlobalMuon[i]);
	
	tree->Branch((name+"_isCutBasedIDLoose").c_str(), &isCutBasedIdLoose[i]);
	tree->Branch((name+"_isCutBasedIDMedium").c_str(), &isCutBasedIdMedium[i]);
	tree->Branch((name+"_isCutBasedIDMediumPrompt").c_str(), &isCutBasedIdMediumPrompt[i]);
	tree->Branch((name+"_isCutBasedIDTight").c_str(), &isCutBasedIdTight[i]);
	tree->Branch((name+"_isCutBasedIDGlobalHighPt").c_str(), &isCutBasedIdGlobalHighPt[i]);
	tree->Branch((name+"_isCutBasedIDTrkHighPt").c_str(), &isCutBasedIdTrkHighPt[i]);
	tree->Branch((name+"_isPFIsoVeryLoose").c_str(), &isPFIsoVeryLoose[i]);
	tree->Branch((name+"_isPFIsoLoose").c_str(), &isPFIsoLoose[i]);
	tree->Branch((name+"_isPFIsoMedium").c_str(), &isPFIsoMedium[i]);
	tree->Branch((name+"_isPFIsoTight").c_str(), &isPFIsoTight[i]);
	tree->Branch((name+"_isPFIsoVeryTight").c_str(), &isPFIsoVeryTight[i]);
	//tree->Branch((name+"_isPFIsoVeryVeryTight")c_str(), &isPFIsoVeryVeryTight[i]);
	tree->Branch((name+"_isTkIsoLoose").c_str(), &isTkIsoLoose[i]);
	tree->Branch((name+"_isTkIsoTight").c_str(), &isTkIsoTight[i]);
	tree->Branch((name+"_isSoftCutBasedId").c_str(), &isSoftCutBasedId[i]);
	//tree->Branch((name+"_isSoftMvaId").c_str(), &isSoftMvaId[i]);
	tree->Branch((name+"_isMvaLoose").c_str(), &isMvaLoose[i]);
	tree->Branch((name+"_isMvaMedium").c_str(), &isMvaMedium[i]);
	tree->Branch((name+"_isMvaTight").c_str(), &isMvaTight[i]);
	tree->Branch((name+"_isMiniIsoLoose").c_str(), &isMiniIsoLoose[i]);
	tree->Branch((name+"_isMiniIsoMedium").c_str(), &isMiniIsoMedium[i]);
	tree->Branch((name+"_isMiniIsoTight").c_str(), &isMiniIsoTight[i]);
	tree->Branch((name+"_isMiniIsoVeryTight").c_str(), &isMiniIsoVeryTight[i]);
	//tree->Branch((name+"_isTriggerIdLoose").c_str(), &isTriggerIdLoose[i]);
        //tree->Branch((name+"_isInTimeMuon").c_str(), &isInTimeMuon[i]);
        //tree->Branch((name+"_isMultiIsoLoose").c_str(), &isMultiIsoLoose[i]);
        //tree->Branch((name+"_isMultiIsoMedium").c_str(), &isMultiIsoMedium[i]);
        
	tree->Branch((name+"_relIsoDeltaBeta03").c_str(),&relIsoDeltaBetaCorrected03[i]); // cone 0.3
        tree->Branch((name+"_relIsoDeltaBeta04").c_str(),&relIsoDeltaBetaCorrected04[i]); // cone 0.4
	
        tree->Branch((name+"_relMiniIso").c_str(), &relMiniIso[i]);
        tree->Branch((name+"_effAreaMiniIso").c_str(), &effAreaMiniIso[i]);
	
        MCmuon[i].book(tree, name, "MCmuon");
        
        std::vector<std::string> discriminatorNames = inputCollections[i].getParameter<std::vector<std::string> >("discriminators");
        for(size_t iDiscr = 0; iDiscr < discriminatorNames.size(); ++iDiscr) {
            tree->Branch((name+"_"+discriminatorNames[iDiscr]).c_str(),&discriminators[inputCollections.size()*iDiscr+i]);
        }
    }
}

bool MuonDumper::fill(edm::Event& iEvent, const edm::EventSetup& iSetup){
    if (!booked) return true;
    
    // Get genParticles
    edm::Handle <reco::GenParticleCollection> genParticlesHandle;
    if (!iEvent.isRealData())
      iEvent.getByToken(genParticleToken, genParticlesHandle);
    // Get vertex
    edm::Handle<edm::View<reco::Vertex> > vertexHandle;
    iEvent.getByToken(vertexToken, vertexHandle);
    
    for(size_t ic = 0; ic < inputCollections.size(); ++ic){
	edm::InputTag inputtag = inputCollections[ic].getParameter<edm::InputTag>("src");
	std::vector<std::string> discriminatorNames = inputCollections[ic].getParameter<std::vector<std::string> >("discriminators");
	edm::Handle<edm::View<pat::Muon>> muonHandle;
        iEvent.getByToken(muonToken[ic], muonHandle);

	edm::Handle<edm::View<pat::PackedCandidate> > pfcandHandle;
        iEvent.getByToken(pfcandsToken[ic], pfcandHandle);
	
	if(muonHandle.isValid()){
	  
	    // Setup handles for rho
	    edm::Handle<double> rhoHandle;
	    iEvent.getByToken(rhoToken[ic], rhoHandle);
	  
            for(size_t i=0; i<muonHandle->size(); ++i) {
    		const pat::Muon& obj = muonHandle->at(i);

		pt[ic].push_back(obj.p4().pt());
                eta[ic].push_back(obj.p4().eta());
                phi[ic].push_back(obj.p4().phi());
                e[ic].push_back(obj.p4().energy());
		
                q[ic].push_back(obj.charge());
                
		isGlobalMuon[ic].push_back(obj.isGlobalMuon());
		
		// Muon Selectors: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Muon_selectors_Since_9_4_X
		isCutBasedIdLoose[ic].push_back(obj.passed(reco::Muon::CutBasedIdLoose));
		isCutBasedIdMedium[ic].push_back(obj.passed(reco::Muon::CutBasedIdMedium));
		isCutBasedIdMediumPrompt[ic].push_back(obj.passed(reco::Muon::CutBasedIdMediumPrompt));
		isCutBasedIdTight[ic].push_back(obj.passed(reco::Muon::CutBasedIdTight));
		isCutBasedIdGlobalHighPt[ic].push_back(obj.passed(reco::Muon::CutBasedIdGlobalHighPt));
		isCutBasedIdTrkHighPt[ic].push_back(obj.passed(reco::Muon::CutBasedIdTrkHighPt));
		isPFIsoVeryLoose[ic].push_back(obj.passed(reco::Muon::PFIsoVeryLoose));
		isPFIsoLoose[ic].push_back(obj.passed(reco::Muon::PFIsoLoose));
		isPFIsoMedium[ic].push_back(obj.passed(reco::Muon::PFIsoMedium));
		isPFIsoTight[ic].push_back(obj.passed(reco::Muon::PFIsoTight));
		isPFIsoVeryTight[ic].push_back(obj.passed(reco::Muon::PFIsoVeryTight));
		//isPFIsoVeryVeryTight[ic].push_back(obj.passed(reco::Muon::PFIsoVeryVeryTight));                                                                                                    
		isTkIsoLoose[ic].push_back(obj.passed(reco::Muon::TkIsoLoose));
		isTkIsoTight[ic].push_back(obj.passed(reco::Muon::TkIsoTight));
		isSoftCutBasedId[ic].push_back(obj.passed(reco::Muon::SoftCutBasedId));
		// isSoftMvaId[ic].push_back(obj.passed(reco::Muon::SoftMvaId));                                                                                            
		isMvaLoose[ic].push_back(obj.passed(reco::Muon::MvaLoose));
		isMvaMedium[ic].push_back(obj.passed(reco::Muon::MvaMedium));
		isMvaTight[ic].push_back(obj.passed(reco::Muon::MvaTight));
		isMiniIsoLoose[ic].push_back(obj.passed(reco::Muon::MiniIsoLoose));
		isMiniIsoMedium[ic].push_back(obj.passed(reco::Muon::MiniIsoMedium));
		isMiniIsoTight[ic].push_back(obj.passed(reco::Muon::MiniIsoTight));
		isMiniIsoVeryTight[ic].push_back(obj.passed(reco::Muon::MiniIsoVeryTight));
		//isTriggerIdLoose[ic].push_back(obj.passed(reco::Muon::TriggerIdLoose));                                                                                          
		//isInTimeMuon[ic].push_back(obj.passed(reco::Muon::InTimeMuon));                                                                                        
		//isMultiIsoLoose[ic].push_back(obj.passed(reco::Muon::MultiIsoLoose));                                                                                                       
		//isMultiIsoMedium[ic].push_back(obj.passed(reco::Muon::MultiIsoMedium));
		
		
                // Calculate relative isolation in cone of DeltaR=0.3
                double isolation03 = (obj.pfIsolationR03().sumChargedHadronPt
                  + std::max(obj.pfIsolationR03().sumNeutralHadronEt
                        + obj.pfIsolationR03().sumPhotonEt
                        - 0.5 * obj.pfIsolationR03().sumPUPt, 0.0));
                double relIso03 = isolation03 / obj.pt();
                relIsoDeltaBetaCorrected03[ic].push_back(relIso03);

                // Calculate relative isolation in cone of DeltaR=0.4
                double isolation04 = (obj.pfIsolationR04().sumChargedHadronPt
		  + std::max(obj.pfIsolationR04().sumNeutralHadronEt
		  + obj.pfIsolationR04().sumPhotonEt
		  - 0.5 * obj.pfIsolationR04().sumPUPt, 0.0));
                double relIso04 = isolation04 / obj.pt();
                relIsoDeltaBetaCorrected04[ic].push_back(relIso04);

		// Calculate Mini-Isolation
		relMiniIso[ic].push_back(getMiniIsolation_DeltaBeta(pfcandHandle, dynamic_cast<const reco::Candidate *>(&obj), 0.05, 0.2, 10., false));
		effAreaMiniIso[ic].push_back(getMiniIsolation_EffectiveArea(pfcandHandle, dynamic_cast<const reco::Candidate *>(&obj), 0.05, 0.2, 10., false, false, *rhoHandle));
		
		//p4[ic].push_back(obj.p4());
		for(size_t iDiscr = 0; iDiscr < discriminatorNames.size(); ++iDiscr) {
		    discriminators[inputCollections.size()*iDiscr+ic].push_back(obj.muonID(discriminatorNames[iDiscr]));
		}
		
                // MC match info
                if (!iEvent.isRealData())
                  fillMCMatchInfo(ic, genParticlesHandle, obj);
            }
        }
    }
    return filter();
}

void MuonDumper::fillMCMatchInfo(size_t ic, edm::Handle<reco::GenParticleCollection>& genParticles, const pat::Muon& ele) {
  double deltaRBestMatch = 9999.0;
  reco::Candidate::LorentzVector p4BestMatch(0,0,0,0);
  if(genParticles.isValid()){
    for (size_t iMC=0; iMC < genParticles->size(); ++iMC) {
      const reco::Candidate & gp = (*genParticles)[iMC];
      if (abs(gp.pdgId()) != 13) continue;
      reco::Candidate::LorentzVector p4 = gp.p4();
      double DR = deltaR(p4,ele.p4());
      if (DR < 0.1 && DR < deltaRBestMatch) {
        deltaRBestMatch = DR;
        p4BestMatch = p4;
      }
    }
  }
  MCmuon[ic].add(p4BestMatch.pt(), p4BestMatch.eta(), p4BestMatch.phi(), p4BestMatch.energy());
}


void MuonDumper::reset(){
    if(booked){         
      for(size_t ic = 0; ic < inputCollections.size(); ++ic){
                        
        pt[ic].clear();
        eta[ic].clear();
        phi[ic].clear();
        e[ic].clear();  

        q[ic].clear();

        isGlobalMuon[ic].clear();

	isCutBasedIdLoose[ic].clear();
	isCutBasedIdMedium[ic].clear();
	isCutBasedIdMediumPrompt[ic].clear();
	isCutBasedIdTight[ic].clear();
	isCutBasedIdGlobalHighPt[ic].clear();
	isCutBasedIdTrkHighPt[ic].clear();
	isPFIsoVeryLoose[ic].clear();
	isPFIsoLoose[ic].clear();
	isPFIsoMedium[ic].clear();
	isPFIsoTight[ic].clear();
	isPFIsoVeryTight[ic].clear();
        //isPFIsoVeryVeryTight[ic].clear();                                                                                                                                                    
	isTkIsoLoose[ic].clear();
	isTkIsoTight[ic].clear();
	isSoftCutBasedId[ic].clear();
        // isSoftMvaId[ic].clear();                                                                                                                                                    
	isMvaLoose[ic].clear();
	isMvaMedium[ic].clear();
	isMvaTight[ic].clear();
	isMiniIsoLoose[ic].clear();
	isMiniIsoMedium[ic].clear();
	isMiniIsoTight[ic].clear();
	isMiniIsoVeryTight[ic].clear();
        //isTriggerIdLoose[ic].clear();                                                                                                                                                  
        //isInTimeMuon[ic].clear();                                                                                                                                                  
        //isMultiIsoLoose[ic].clear();                                                                                                                                                      
        //isMultiIsoMedium[ic].clear();
	
        relIsoDeltaBetaCorrected03[ic].clear();
	relIsoDeltaBetaCorrected04[ic].clear();
	
	relMiniIso[ic].clear();
	effAreaMiniIso[ic].clear();
	
        MCmuon[ic].reset();
      }
      for(size_t ic = 0; ic < inputCollections.size()*nDiscriminators; ++ic){
        discriminators[ic].clear();
      }
    }  
}
