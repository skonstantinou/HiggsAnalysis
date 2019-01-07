#include "HiggsAnalysis/MiniAOD2TTree/interface/FatJetDumper.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/GenParticleTools.h"

#include "DataFormats/JetReco/interface/PileupJetIdentifier.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/NtupleAnalysis_fwd.h"

FatJetDumper::FatJetDumper(edm::ConsumesCollector&& iConsumesCollector, std::vector<edm::ParameterSet>& psets)
  : genParticleToken(iConsumesCollector.consumes<reco::GenParticleCollection>(edm::InputTag("prunedGenParticles"))),
    qgTaggingVariables(new QGTaggingVariables)
{
    inputCollections = psets;
    booked           = false;
    systVariations = inputCollections[0].getParameter<bool>("systVariations");
    
    /*
      mcjecPath      = inputCollections[0].getUntrackedParameter<std::string>("mcjecPath");
      datajecPath    = inputCollections[0].getUntrackedParameter<std::string>("datajecPath");
      
      std::vector<JetCorrectorParameters> mcJECparams;
      mcJECparams.push_back(JetCorrectorParameters(mcjecPath+"_MC_L2Relative_AK8PFchs.txt"));
      mcJECparams.push_back(JetCorrectorParameters(mcjecPath+"_MC_L3Absolute_AK8PFchs.txt"));
      mcJEC = new FactorizedJetCorrector(mcJECparams);
      
      std::vector<JetCorrectorParameters> dataJECparams;
      dataJECparams.push_back(JetCorrectorParameters(datajecPath+"_DATA_L2Relative_AK8PFchs.txt"));
      dataJECparams.push_back(JetCorrectorParameters(datajecPath+"_DATA_L3Absolute_AK8PFchs.txt"));
      dataJECparams.push_back(JetCorrectorParameters(datajecPath+"_DATA_L2L3Residual_AK8PFchs.txt"));
      dataJEC = new FactorizedJetCorrector(dataJECparams);
      
      std::vector<JetCorrectorParameters> mcJECparams_PUPPI;
      mcJECparams_PUPPI.push_back(JetCorrectorParameters(mcjecPath+"_MC_L2Relative_AK8PFPuppi.txt"));
      mcJECparams_PUPPI.push_back(JetCorrectorParameters(mcjecPath+"_MC_L3Absolute_AK8PFPuppi.txt"));
      mcJEC_PUPPI = new FactorizedJetCorrector(mcJECparams_PUPPI);
      
      std::vector<JetCorrectorParameters> dataJECparams_PUPPI;
      dataJECparams_PUPPI.push_back(JetCorrectorParameters(datajecPath+"_DATA_L2Relative_AK8PFPuppi.txt"));
      dataJECparams_PUPPI.push_back(JetCorrectorParameters(datajecPath+"_DATA_L3Absolute_AK8PFPuppi.txt"));
      dataJECparams_PUPPI.push_back(JetCorrectorParameters(datajecPath+"_DATA_L2L3Residual_AK8PFPuppi.txt"));
      dataJEC_PUPPI = new FactorizedJetCorrector(dataJECparams_PUPPI);
    */
    
    pt  = new std::vector<double>[inputCollections.size()];
    eta = new std::vector<double>[inputCollections.size()];    
    phi = new std::vector<double>[inputCollections.size()];    
    e   = new std::vector<double>[inputCollections.size()];    

    //p4 = new std::vector<reco::Candidate::LorentzVector>[inputCollections.size()];
    pdgId = new std::vector<short>[inputCollections.size()];
    hadronFlavour = new std::vector<int>[inputCollections.size()];
    partonFlavour = new std::vector<int>[inputCollections.size()];

    nDiscriminators   = inputCollections[0].getParameter<std::vector<std::string> >("discriminators").size();
    discriminators    = new std::vector<float>[inputCollections.size()*nDiscriminators];
    nUserfloats       = inputCollections[0].getParameter<std::vector<std::string> >("userFloats").size();
    userfloats        = new std::vector<double>[inputCollections.size()*nUserfloats];
    nUserints         = inputCollections[0].getParameter<std::vector<std::string> >("userInts").size();
    userints          = new std::vector<int>[inputCollections.size()*nUserints];
        
    jetToken   = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    jetJESup   = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    jetJESdown = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    jetJERup   = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    jetJERdown = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    for(size_t i = 0; i < inputCollections.size(); ++i){
        edm::InputTag inputtag = inputCollections[i].getParameter<edm::InputTag>("src");
        jetToken[i] = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtag);

	if(systVariations){
	  edm::InputTag inputtagJESup = inputCollections[i].getParameter<edm::InputTag>("srcJESup");
          jetJESup[i]   = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtagJESup);

          edm::InputTag inputtagJESdown = inputCollections[i].getParameter<edm::InputTag>("srcJESdown");
          jetJESdown[i] = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtagJESdown);

          edm::InputTag inputtagJERup = inputCollections[i].getParameter<edm::InputTag>("srcJERup");
          jetJERup[i]   = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtagJERup);
        
          edm::InputTag inputtagJERdown = inputCollections[i].getParameter<edm::InputTag>("srcJERdown");
          jetJERdown[i] = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtagJERdown);
	}
    }
    
    useFilter = false;
    for(size_t i = 0; i < inputCollections.size(); ++i){
      bool param = inputCollections[i].getUntrackedParameter<bool>("filter",false);
      if(param) useFilter = true;
    }
    
    rho_token = iConsumesCollector.consumes<double>(inputCollections[0].getParameter<edm::InputTag>("rho"));
    vertex_token = iConsumesCollector.consumes<reco::VertexCollection>(inputCollections[0].getParameter<edm::InputTag>("vertices"));
    
    jetIDloose = new std::vector<bool>[inputCollections.size()];
    jetIDtight = new std::vector<bool>[inputCollections.size()];
    jetIDtightLeptonVeto = new std::vector<bool>[inputCollections.size()];

    jetPUIDloose = new std::vector<bool>[inputCollections.size()];
    jetPUIDmedium = new std::vector<bool>[inputCollections.size()];
    jetPUIDtight = new std::vector<bool>[inputCollections.size()];
    
    MCjet = new FourVectorDumper[inputCollections.size()];
    
    if(systVariations){
      systJESup = new FourVectorDumper[inputCollections.size()];
      systJESdown = new FourVectorDumper[inputCollections.size()];
      systJERup = new FourVectorDumper[inputCollections.size()];
      systJERdown = new FourVectorDumper[inputCollections.size()];
    }
    
    pfDeepCSVBJetTags = new std::vector<float>[inputCollections.size()];
    pfDeepCSVCJetTags = new std::vector<float>[inputCollections.size()];
    pfDeepCSVUDSGJetTags = new std::vector<float>[inputCollections.size()];
    
    corrPrunedMass    = new std::vector<double>[inputCollections.size()];
    numberOfDaughters = new std::vector<int>[inputCollections.size()];
    nSubjets          = new std::vector<int>[inputCollections.size()];
    
    sdsubjet1_pt      = new std::vector<double>[inputCollections.size()];
    sdsubjet1_eta     = new std::vector<double>[inputCollections.size()];
    sdsubjet1_phi     = new std::vector<double>[inputCollections.size()];
    sdsubjet1_mass    = new std::vector<double>[inputCollections.size()];
    sdsubjet1_csv     = new std::vector<double>[inputCollections.size()];
    sdsubjet1_deepcsv = new std::vector<double>[inputCollections.size()];
    sdsubjet1_axis1   = new std::vector<double>[inputCollections.size()];
    sdsubjet1_axis2   = new std::vector<double>[inputCollections.size()];
    sdsubjet1_ptD     = new std::vector<double>[inputCollections.size()];
    sdsubjet1_mult    = new std::vector<int>[inputCollections.size()];
    
    sdsubjet2_pt      = new std::vector<double>[inputCollections.size()];
    sdsubjet2_eta     = new std::vector<double>[inputCollections.size()];
    sdsubjet2_phi     = new std::vector<double>[inputCollections.size()];
    sdsubjet2_mass    = new std::vector<double>[inputCollections.size()];
    sdsubjet2_csv     = new std::vector<double>[inputCollections.size()];
    sdsubjet2_deepcsv = new std::vector<double>[inputCollections.size()];
    sdsubjet2_axis1   = new std::vector<double>[inputCollections.size()];
    sdsubjet2_axis2   = new std::vector<double>[inputCollections.size()];
    sdsubjet2_ptD     = new std::vector<double>[inputCollections.size()];
    sdsubjet2_mult    = new std::vector<int>[inputCollections.size()];
}

FatJetDumper::~FatJetDumper(){
  //delete mcJEC;
  //delete mcJEC_PUPPI;
  //delete dataJEC;
  //delete dataJEC_PUPPI;
}

void FatJetDumper::book(TTree* tree){
  booked = true;
  
  for(size_t i = 0; i < inputCollections.size(); ++i){
    std::string name = inputCollections[i].getUntrackedParameter<std::string>("branchname","");
    if(name.length() == 0) name = inputCollections[i].getParameter<edm::InputTag>("src").label();
    tree->Branch((name+"_pt").c_str(),&pt[i]);
    tree->Branch((name+"_eta").c_str(),&eta[i]);
    tree->Branch((name+"_phi").c_str(),&phi[i]);
    tree->Branch((name+"_e").c_str(),&e[i]);    
    //tree->Branch((name+"_p4").c_str(),&p4[i]);
    tree->Branch((name+"_pdgId").c_str(),&pdgId[i]);
    tree->Branch((name+"_hadronFlavour").c_str(),&hadronFlavour[i]);
    tree->Branch((name+"_partonFlavour").c_str(),&partonFlavour[i]);
    tree->Branch((name+"_pfDeepCSVBJetTags").c_str(), &pfDeepCSVBJetTags[i]);
    tree->Branch((name+"_pfDeepCSVCJetTags").c_str(), &pfDeepCSVBJetTags[i]);
    tree->Branch((name+"_pfDeepCSVUDSGJetTags").c_str(), &pfDeepCSVBJetTags[i]);
    
    std::vector<std::string> discriminatorNames = inputCollections[i].getParameter<std::vector<std::string> >("discriminators");
    for(size_t iDiscr = 0; iDiscr < discriminatorNames.size(); ++iDiscr) {
      std::string branch_name = discriminatorNames[iDiscr];
      size_t pos_semicolon = branch_name.find(":");
      if (pos_semicolon!=std::string::npos){
        branch_name = branch_name.erase(pos_semicolon,1);
      }
      tree->Branch((name+"_"+branch_name).c_str(),&discriminators[inputCollections.size()*iDiscr+i]);
    }
    std::vector<std::string> userfloatNames = inputCollections[i].getParameter<std::vector<std::string> >("userFloats");
    for(size_t iDiscr = 0; iDiscr < userfloatNames.size(); ++iDiscr) {
      std::string branch_name = userfloatNames[iDiscr];
      size_t pos_semicolon = branch_name.find(":");
      if (pos_semicolon!=std::string::npos){
	branch_name = branch_name.erase(pos_semicolon,1);
      }
      tree->Branch((name+"_"+branch_name).c_str(),&userfloats[inputCollections.size()*iDiscr+i]);
    }
    std::vector<std::string> userintNames = inputCollections[i].getParameter<std::vector<std::string> >("userInts");
    for(size_t iDiscr = 0; iDiscr < userintNames.size(); ++iDiscr) {
      std::string branch_name = userintNames[iDiscr];
      size_t pos_semicolon = branch_name.find(":");
      branch_name = branch_name.erase(pos_semicolon,1);
      tree->Branch((name+"_"+branch_name).c_str(),&userints[inputCollections.size()*iDiscr+i]);
    }
        
    tree->Branch((name+"_IDloose").c_str(),&jetIDloose[i]);
    tree->Branch((name+"_IDtight").c_str(),&jetIDtight[i]);
    tree->Branch((name+"_IDtightLeptonVeto").c_str(),&jetIDtightLeptonVeto[i]);

    tree->Branch((name+"_PUIDloose").c_str(),&jetPUIDloose[i]);
    tree->Branch((name+"_PUIDmedium").c_str(),&jetPUIDmedium[i]);
    tree->Branch((name+"_PUIDtight").c_str(),&jetPUIDtight[i]);
    
    MCjet[i].book(tree, name, "MCjet");
    
    if(systVariations){
      systJESup[i].book(tree, name, "JESup");
      systJESdown[i].book(tree, name, "JESdown");
      systJERup[i].book(tree, name, "JERup");
      systJERdown[i].book(tree, name, "JERdown");
    }
    
    tree->Branch((name+"_corrPrunedMass").c_str(), &corrPrunedMass[i]);
    tree->Branch((name+"_numberOfDaughters").c_str(), &numberOfDaughters[i]);
    
    tree->Branch((name+"_nsoftdropSubjets").c_str(),  &nSubjets[i]);
    tree->Branch((name+"_sdsubjet1_pt").c_str(),   &sdsubjet1_pt[i]);
    tree->Branch((name+"_sdsubjet1_eta").c_str(),  &sdsubjet1_eta[i]);
    tree->Branch((name+"_sdsubjet1_phi").c_str(),  &sdsubjet1_phi[i]);
    tree->Branch((name+"_sdsubjet1_mass").c_str(), &sdsubjet1_mass[i]);
    tree->Branch((name+"_sdsubjet1_csv").c_str(),  &sdsubjet1_csv[i]);
    tree->Branch((name+"_sdsubjet1_deepcsv").c_str(), &sdsubjet1_deepcsv[i]);
    tree->Branch((name+"_sdsubjet1_axis1").c_str(),&sdsubjet1_axis1[i]);
    tree->Branch((name+"_sdsubjet1_axis2").c_str(),&sdsubjet1_axis2[i]);
    tree->Branch((name+"_sdsubjet1_ptD").c_str(),  &sdsubjet1_ptD[i]);
    tree->Branch((name+"_sdsubjet1_mult").c_str(), &sdsubjet1_mult[i]);
    
    tree->Branch((name+"_sdsubjet2_pt").c_str(),   &sdsubjet2_pt[i]);
    tree->Branch((name+"_sdsubjet2_eta").c_str(),  &sdsubjet2_eta[i]);
    tree->Branch((name+"_sdsubjet2_phi").c_str(),  &sdsubjet2_phi[i]);
    tree->Branch((name+"_sdsubjet2_mass").c_str(), &sdsubjet2_mass[i]);
    tree->Branch((name+"_sdsubjet2_csv").c_str(),  &sdsubjet2_csv[i]);
    tree->Branch((name+"_sdsubjet2_deepcsv").c_str(), &sdsubjet2_deepcsv[i]);
    tree->Branch((name+"_sdsubjet2_axis1").c_str(),&sdsubjet2_axis1[i]);
    tree->Branch((name+"_sdsubjet2_axis2").c_str(),&sdsubjet2_axis2[i]);
    tree->Branch((name+"_sdsubjet2_ptD").c_str(),  &sdsubjet2_ptD[i]);
    tree->Branch((name+"_sdsubjet2_mult").c_str(), &sdsubjet2_mult[i]);
  }
}

bool FatJetDumper::fill(edm::Event& iEvent, const edm::EventSetup& iSetup){
    
  if (!booked) return true;
  
    edm::Handle <reco::GenParticleCollection> genParticlesHandle;
    if (!iEvent.isRealData())
      iEvent.getByToken(genParticleToken, genParticlesHandle);
    
    // Vertex
    edm::Handle<reco::VertexCollection> vertex_handle;
    iEvent.getByToken(vertex_token,vertex_handle);
    
    // Rho
    edm::Handle<double> rho_handle;
    iEvent.getByToken(rho_token,rho_handle);
    
    for(size_t ic = 0; ic < inputCollections.size(); ++ic){
      
        std::vector<std::string> discriminatorNames   = inputCollections[ic].getParameter<std::vector<std::string> >("discriminators");
	std::vector<std::string> userfloatNames       = inputCollections[ic].getParameter<std::vector<std::string> >("userFloats");
	std::vector<std::string> userintNames         = inputCollections[ic].getParameter<std::vector<std::string> >("userInts");
	
        edm::Handle<edm::View<pat::Jet>> jetHandle;
        iEvent.getByToken(jetToken[ic], jetHandle);
	
	if(jetHandle.isValid()){

	    for(size_t i=0; i<jetHandle->size(); ++i) {
    		const pat::Jet& obj = jetHandle->at(i);

		pt[ic].push_back(obj.p4().pt());
                eta[ic].push_back(obj.p4().eta());
                phi[ic].push_back(obj.p4().phi());
                e[ic].push_back(obj.p4().energy());
		
		/*
		  
		// FIXME
		// L2L3 Corrected Jet only for the pruned mass correction
		double corr = 0.0;
		FactorizedJetCorrector *jecAK8_ = ( iEvent.isRealData() ) ? dataJEC : mcJEC;
		jecAK8_ -> setJetEta ( obj.eta()     * obj.jecFactor("Uncorrected") );
		jecAK8_ -> setJetPt  ( obj.pt()      * obj.jecFactor("Uncorrected") );
		jecAK8_ -> setJetE   ( obj.energy()  * obj.jecFactor("Uncorrected") );
		jecAK8_ -> setJetA   ( obj.jetArea() );
		jecAK8_->setRho   ( *rho_handle );
		jecAK8_->setNPV   ( vertex_handle->size() );
		corr = jecAK8_->getCorrection(); 
		
		corrPrunedMass[ic].push_back(obj.userFloat("ak8PFJetsCHSPrunedMass")*corr);
		*/
		
		pfDeepCSVBJetTags[ic].push_back(obj.bDiscriminator("pfDeepCSVJetTags:probb")+obj.bDiscriminator("pfDeepCSVJetTags:probbb"));
                pfDeepCSVCJetTags[ic].push_back(obj.bDiscriminator("pfDeepCSVJetTags:probc"));
                pfDeepCSVUDSGJetTags[ic].push_back(obj.bDiscriminator("pfDeepCSVJetTags:probudsg"));
		
		for(size_t iDiscr = 0; iDiscr < discriminatorNames.size(); ++iDiscr) {
		  //std::cout << inputCollections[ic].getUntrackedParameter<std::string>("branchname","") << " / " << discriminatorNames[iDiscr] << std::endl;
		  discriminators[inputCollections.size()*iDiscr+ic].push_back(obj.bDiscriminator(discriminatorNames[iDiscr]));
		}
                for(size_t iDiscr = 0; iDiscr < userfloatNames.size(); ++iDiscr) {
		  //std::cout << inputCollections[ic].getUntrackedParameter<std::string>("branchname","") << " / " << userfloatNames[iDiscr] << std::endl;
		  userfloats[inputCollections.size()*iDiscr+ic].push_back(obj.userFloat(userfloatNames[iDiscr]));
                }
		for(size_t iDiscr = 0; iDiscr < userintNames.size(); ++iDiscr) {
		  //std::cout << inputCollections[ic].getUntrackedParameter<std::string>("branchname","") << " / " << userintNames[iDiscr] << std::endl;
		  userints[inputCollections.size()*iDiscr+ic].push_back(obj.userInt(userintNames[iDiscr]));
		}
				
		int genParton = 0;
		if(obj.genParton()){
		  genParton = obj.genParton()->pdgId();
		}
		pdgId[ic].push_back(genParton);
		hadronFlavour[ic].push_back(obj.hadronFlavour());
		partonFlavour[ic].push_back(obj.partonFlavour());

                // Jet ID
                jetIDloose[ic].push_back(passJetID(kJetIDLoose, obj));
                jetIDtight[ic].push_back(passJetID(kJetIDTight, obj));
                jetIDtightLeptonVeto[ic].push_back(passJetID(kJetIDTightLepVeto, obj));

		// Jet PU ID
                // https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetID
               
 		double PUID = 0;
                if(obj.hasUserData("pileupJetId:fullDiscriminant")){
 		  PUID = obj.userFloat("pileupJetId:fullDiscriminant");
 		}
                int puIDflag = static_cast<int>(PUID);
		jetPUIDloose[ic].push_back(PileupJetIdentifier::passJetId(puIDflag, PileupJetIdentifier::kLoose));
		jetPUIDmedium[ic].push_back(PileupJetIdentifier::passJetId(puIDflag, PileupJetIdentifier::kMedium));
		jetPUIDtight[ic].push_back(PileupJetIdentifier::passJetId(puIDflag, PileupJetIdentifier::kTight));
                
		// GenJet
                if (obj.genJet() != nullptr) {
                  MCjet[ic].add(obj.genJet()->pt(), obj.genJet()->eta(), obj.genJet()->phi(), obj.genJet()->energy());
                } else {
                  MCjet[ic].add(0.0, 0.0, 0.0, 0.0);
                }
                
                // Systematics
		if (systVariations && !iEvent.isRealData()) {
	          edm::Handle<edm::View<pat::Jet>> jetJESupHandle;
        	  iEvent.getByToken(jetJESup[ic], jetJESupHandle);
		  
                  if(jetJESupHandle.isValid()){
                    const pat::Jet& sysobj = jetJESupHandle->at(i);
                    systJESup[ic].add(sysobj.p4().pt(),
                                      sysobj.p4().eta(),
                                      sysobj.p4().phi(),
                                      sysobj.p4().energy());
                  }

                  edm::Handle<edm::View<pat::Jet>> jetJESdownHandle;
                  iEvent.getByToken(jetJESdown[ic], jetJESdownHandle);
                      
                  if(jetJESdownHandle.isValid()){
                    const pat::Jet& sysobj = jetJESdownHandle->at(i);
                    systJESdown[ic].add(sysobj.p4().pt(),
                                        sysobj.p4().eta(),
                                        sysobj.p4().phi(),
                                        sysobj.p4().energy());
                  }
		  
                  edm::Handle<edm::View<pat::Jet>> jetJERupHandle;
                  iEvent.getByToken(jetJERup[ic], jetJERupHandle);
                      
                  if(jetJERupHandle.isValid()){
                    const pat::Jet& sysobj = jetJERupHandle->at(i);
                    systJERup[ic].add(sysobj.p4().pt(),
                                      sysobj.p4().eta(),
                                      sysobj.p4().phi(),
                                      sysobj.p4().energy());
                  }
                
                  edm::Handle<edm::View<pat::Jet>> jetJERdownHandle;
                  iEvent.getByToken(jetJERdown[ic], jetJERdownHandle);
                
                  if(jetJERdownHandle.isValid()){
                    const pat::Jet& sysobj = jetJERdownHandle->at(i);  
                    systJERdown[ic].add(sysobj.p4().pt(),
                                        sysobj.p4().eta(),
                                        sysobj.p4().phi(),
                                        sysobj.p4().energy());
                  }
		}
		
		numberOfDaughters[ic].push_back(obj.numberOfDaughters());
		
		//reco::CATopJetTagInfo const * caTopTagInfo = dynamic_cast<reco::CATopJetTagInfo const * > (obj.tagInfo("caTop"));
		//if (caTopTagInfo != 0) {
		//  float minMass = caTopTagInfo->properties().minMass;
		//  float nSubs   = caTopTagInfo->properties().nSubJets;
		//std::cout<<"caTopTagInfo -> minMass ="<<minMass<<std::endl;
		//  std::cout<<"caTopTagInfo -> nSubjets="<<nSubs<<std::endl;
		//}
		
		
		std::vector<pat::Jet> sdsubjets; sdsubjets.clear();
		auto &subjets = obj.subjets("SoftDropPuppi");
		for (auto const & sj: subjets)
		  {
		    sdsubjets.push_back(sj);
		  }

		nSubjets[ic].push_back(sdsubjets.size());
		if (sdsubjets.size() == 0)
		  {
		    sdsubjet1_pt[ic].push_back(-99.9); 
		    sdsubjet1_eta[ic].push_back(-99.9);
		    sdsubjet1_phi[ic].push_back(-99.9);
		    sdsubjet1_mass[ic].push_back(-99.9);
		    sdsubjet1_csv[ic].push_back(-99.9);
		    sdsubjet1_deepcsv[ic].push_back(-99.9);
		    sdsubjet1_axis1[ic].push_back(-99.9);
                    sdsubjet1_axis2[ic].push_back(-99.9);
                    sdsubjet1_ptD[ic].push_back(-99.9);
                    sdsubjet1_mult[ic].push_back(-999);
		    
		    sdsubjet2_pt[ic].push_back(-99.9);
		    sdsubjet2_eta[ic].push_back(-99.9);
		    sdsubjet2_phi[ic].push_back(-99.9);
		    sdsubjet2_mass[ic].push_back(-99.9);
		    sdsubjet2_csv[ic].push_back(-99.9);
		    sdsubjet2_deepcsv[ic].push_back(-99.9);
		    sdsubjet2_axis1[ic].push_back(-99.9);
                    sdsubjet2_axis2[ic].push_back(-99.9);
                    sdsubjet2_ptD[ic].push_back(-99.9);
                    sdsubjet2_mult[ic].push_back(-999);
		  }
		else if (sdsubjets.size() == 1)
		  {
		    qgTaggingVariables->compute(&(sdsubjets[0]), true);
                    double sj1_axis1 = qgTaggingVariables->getAxis1();
                    double sj1_axis2 = qgTaggingVariables->getAxis2();
                    double sj1_ptD   = qgTaggingVariables->getPtD();
                    int sj1_mult     = qgTaggingVariables->getMult();
		    
		    sdsubjet1_pt[ic].push_back(  sdsubjets[0].pt());
		    sdsubjet1_eta[ic].push_back( sdsubjets[0].eta());
		    sdsubjet1_phi[ic].push_back( sdsubjets[0].phi());
		    sdsubjet1_mass[ic].push_back(sdsubjets[0].mass());
		    sdsubjet1_csv[ic].push_back( sdsubjets[0].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
		    sdsubjet1_deepcsv[ic].push_back(sdsubjets[0].bDiscriminator("pfDeepCSVJetTags:probb") + sdsubjets[0].bDiscriminator("pfDeepCSVJetTags:probbb"));
		    sdsubjet1_axis1[ic].push_back(sj1_axis1);
                    sdsubjet1_axis2[ic].push_back(sj1_axis2);
                    sdsubjet1_ptD[ic].push_back(sj1_ptD);
                    sdsubjet1_mult[ic].push_back(sj1_mult);
		    
		    sdsubjet2_pt[ic].push_back(-99.9);
		    sdsubjet2_eta[ic].push_back(-99.9);
		    sdsubjet2_phi[ic].push_back(-99.9);
		    sdsubjet2_mass[ic].push_back(-99.9);
		    sdsubjet2_csv[ic].push_back(-99.9);
		    sdsubjet2_deepcsv[ic].push_back(-99.9);
		    sdsubjet2_axis1[ic].push_back(-99.9);
                    sdsubjet2_axis2[ic].push_back(-99.9);
                    sdsubjet2_ptD[ic].push_back(-99.9);
                    sdsubjet2_mult[ic].push_back(-999);
		  }
		else if (sdsubjets.size() == 2)
		  {
		    qgTaggingVariables->compute(&(sdsubjets[0]), true);
                    double sj1_axis1 = qgTaggingVariables->getAxis1();
                    double sj1_axis2 = qgTaggingVariables->getAxis2();
                    double sj1_ptD   = qgTaggingVariables->getPtD();
                    int sj1_mult     = qgTaggingVariables->getMult();
		    
		    sdsubjet1_pt[ic].push_back(  sdsubjets[0].pt());
		    sdsubjet1_eta[ic].push_back( sdsubjets[0].eta());
		    sdsubjet1_phi[ic].push_back( sdsubjets[0].phi());
		    sdsubjet1_mass[ic].push_back(sdsubjets[0].mass());
		    sdsubjet1_csv[ic].push_back( sdsubjets[0].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
		    sdsubjet1_deepcsv[ic].push_back(sdsubjets[0].bDiscriminator("pfDeepCSVJetTags:probb") + sdsubjets[0].bDiscriminator("pfDeepCSVJetTags:probbb"));
		    sdsubjet1_axis1[ic].push_back(sj1_axis1);
                    sdsubjet1_axis2[ic].push_back(sj1_axis2);
                    sdsubjet1_ptD[ic].push_back(sj1_ptD);
                    sdsubjet1_mult[ic].push_back(sj1_mult);
		        
		    qgTaggingVariables->compute(&(sdsubjets[1]), true);
                    double sj2_axis1 = qgTaggingVariables->getAxis1();
                    double sj2_axis2 = qgTaggingVariables->getAxis2();
                    double sj2_ptD   = qgTaggingVariables->getPtD();
                    int sj2_mult     = qgTaggingVariables->getMult();
		    
		    sdsubjet2_pt[ic].push_back(  sdsubjets[1].pt());
		    sdsubjet2_eta[ic].push_back( sdsubjets[1].eta());
		    sdsubjet2_phi[ic].push_back( sdsubjets[1].phi());
		    sdsubjet2_mass[ic].push_back(sdsubjets[1].mass());
		    sdsubjet2_csv[ic].push_back( sdsubjets[1].bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
		    sdsubjet2_deepcsv[ic].push_back(sdsubjets[1].bDiscriminator("pfDeepCSVJetTags:probb") + sdsubjets[1].bDiscriminator("pfDeepCSVJetTags:probbb"));
		    sdsubjet2_axis1[ic].push_back(sj2_axis1);
                    sdsubjet2_axis2[ic].push_back(sj2_axis2);
                    sdsubjet2_ptD[ic].push_back(sj2_ptD);
                    sdsubjet2_mult[ic].push_back(sj2_mult);
		  }
		else {
		  throw cms::Exception("CorruptData") << "Softdrop subjets not valid! Fat jets can have only 0, 1 or 2 Soft Drop Subjets!";
		}
	    }
        }
    }
    return filter();
}

void FatJetDumper::reset(){

    for(size_t ic = 0; ic < inputCollections.size(); ++ic){
	pt[ic].clear();
	eta[ic].clear();
	phi[ic].clear();
	e[ic].clear();
//        p4[ic].clear();
        pdgId[ic].clear();
	hadronFlavour[ic].clear();
	partonFlavour[ic].clear();

        jetIDloose[ic].clear();
        jetIDtight[ic].clear();
        jetIDtightLeptonVeto[ic].clear();

        jetPUIDloose[ic].clear();
	jetPUIDmedium[ic].clear();
	jetPUIDtight[ic].clear();
        
        MCjet[ic].reset();

        // Systematics
	if(systVariations){
	  systJESup[ic].reset();
          systJESdown[ic].reset();
          systJERup[ic].reset();
          systJERdown[ic].reset();
	}

	pfDeepCSVBJetTags[ic].clear();
        pfDeepCSVCJetTags[ic].clear();
        pfDeepCSVUDSGJetTags[ic].clear();
	
	corrPrunedMass[ic].clear();
	numberOfDaughters[ic].clear();
	nSubjets[ic].clear();
	sdsubjet1_pt[ic].clear();
	sdsubjet1_eta[ic].clear();
	sdsubjet1_phi[ic].clear();
	sdsubjet1_mass[ic].clear();
	sdsubjet1_csv[ic].clear();
	sdsubjet1_deepcsv[ic].clear();
	sdsubjet1_axis1[ic].clear();
        sdsubjet1_axis2[ic].clear();
        sdsubjet1_ptD[ic].clear();
        sdsubjet1_mult[ic].clear();
	
	sdsubjet2_pt[ic].clear();
	sdsubjet2_eta[ic].clear();
	sdsubjet2_phi[ic].clear();
	sdsubjet2_mass[ic].clear();
	sdsubjet2_csv[ic].clear();
	sdsubjet2_deepcsv[ic].clear();
	sdsubjet2_axis1[ic].clear();
        sdsubjet2_axis2[ic].clear();
        sdsubjet2_ptD[ic].clear();
        sdsubjet2_mult[ic].clear();
    }
    for(size_t ic = 0; ic < inputCollections.size()*nDiscriminators; ++ic){
      discriminators[ic].clear();
    }
    for(size_t ic = 0; ic < inputCollections.size()*nUserfloats; ++ic){
      userfloats[ic].clear();
    }
    for(size_t ic = 0; ic < inputCollections.size()*nUserints; ++ic){
      userints[ic].clear();
    }
}

bool FatJetDumper::passJetID(int id, const pat::Jet& jet) {
  // Recipy taken from https://twiki.cern.ch/twiki/bin/view/CMS/JetID (read on 14.08.2015)
  double eta = fabs(jet.eta());
  if (eta < 3.0) {
    // PF Jet ID       Loose   Tight   TightLepVeto
    // Neutral Hadron Fraction < 0.99  < 0.90  < 0.90
    // Neutral EM Fraction     < 0.99  < 0.90  < 0.90
    // Number of Constituents  > 1     > 1     > 1
    // Muon Fraction           -       -       < 0.8
    int nConstituents = jet.chargedMultiplicity() + jet.electronMultiplicity()
      + jet.muonMultiplicity() + jet.neutralMultiplicity();
    if (id == kJetIDLoose) {
      if (!(jet.neutralHadronEnergyFraction() < 0.99)) return false;
      if (!(jet.neutralEmEnergyFraction()     < 0.99)) return false;
      if (!(nConstituents                     > 1   )) return false;
    } else if (id == kJetIDTight) {
      if (!(jet.neutralHadronEnergyFraction() < 0.90)) return false;
      if (!(jet.neutralEmEnergyFraction()     < 0.90)) return false;
      if (!(nConstituents                     > 1   )) return false;      
    } else if (id == kJetIDTightLepVeto) {
      if (!(jet.neutralHadronEnergyFraction() < 0.90)) return false;
      if (!(jet.neutralEmEnergyFraction()     < 0.90)) return false;
      if (!(nConstituents                     > 1   )) return false;      
      if (!(jet.muonEnergyFraction()          < 0.80)) return false;
    }
    if (eta < 2.4) {
      // And for -2.4 <= eta <= 2.4 in addition apply
      // Charged Hadron Fraction > 0     > 0     > 0
      // Charged Multiplicity    > 0     > 0     > 0
      // Charged EM Fraction     < 0.99  < 0.99  < 0.90
      if (id == kJetIDLoose) {
        if (!(jet.chargedHadronEnergyFraction() > 0.0 )) return false;
        if (!(jet.chargedHadronMultiplicity()   > 0   )) return false;
        if (!(jet.chargedEmEnergyFraction()     < 0.99)) return false;
      } else if (id == kJetIDTight) {
        if (!(jet.chargedHadronEnergyFraction() > 0.0 )) return false;
        if (!(jet.chargedHadronMultiplicity()   > 0   )) return false;
        if (!(jet.chargedEmEnergyFraction()     < 0.99)) return false;        
      } else if (id == kJetIDTightLepVeto) {
        if (!(jet.chargedHadronEnergyFraction() > 0.0 )) return false;
        if (!(jet.chargedHadronMultiplicity()   > 0   )) return false;
        if (!(jet.chargedEmEnergyFraction()     < 0.90)) return false;
      }
    }
  } else {
    //     PF Jet ID                   Loose   Tight
    //     Neutral EM Fraction         < 0.90  < 0.90
    //     Number of Neutral Particles > 10    >10 
    if (id == kJetIDLoose) {
      if (!(jet.neutralEmEnergyFraction() < 0.90)) return false;
      if (!(jet.neutralMultiplicity()     > 10  )) return false;    
    } else if (id == kJetIDTight) {
      if (!(jet.neutralEmEnergyFraction() < 0.90)) return false;
      if (!(jet.neutralMultiplicity()     > 10  )) return false;    
    }
  }
  return true;
}


