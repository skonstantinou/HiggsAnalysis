#include "HiggsAnalysis/MiniAOD2TTree/interface/JetDumper.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/GenParticleTools.h"

#include "DataFormats/JetReco/interface/PileupJetIdentifier.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/NtupleAnalysis_fwd.h"

JetDumper::JetDumper(edm::ConsumesCollector&& iConsumesCollector, std::vector<edm::ParameterSet>& psets)
  : genParticleToken(iConsumesCollector.consumes<reco::GenParticleCollection>(edm::InputTag("prunedGenParticles"))),
    qgTaggingVariables(new QGTaggingVariables)
{
    inputCollections = psets;
    booked           = false;

    systVariations = inputCollections[0].getParameter<bool>("systVariations");
        
    pt  = new std::vector<double>[inputCollections.size()];
    eta = new std::vector<double>[inputCollections.size()];    
    phi = new std::vector<double>[inputCollections.size()];    
    e   = new std::vector<double>[inputCollections.size()];    
    
    //p4 = new std::vector<reco::Candidate::LorentzVector>[inputCollections.size()];
    pdgId = new std::vector<short>[inputCollections.size()];
    hadronFlavour = new std::vector<int>[inputCollections.size()];
    partonFlavour = new std::vector<int>[inputCollections.size()];

    nDiscriminators = inputCollections[0].getParameter<std::vector<std::string> >("discriminators").size();
    discriminators = new std::vector<float>[inputCollections.size()*nDiscriminators];
    nUserfloats = inputCollections[0].getParameter<std::vector<std::string> >("userFloats").size();
    userfloats  = new std::vector<double>[inputCollections.size()*nUserfloats];
    nUserints   = inputCollections[0].getParameter<std::vector<std::string> >("userInts").size();
    userints    = new std::vector<int>[inputCollections.size()*nUserints];
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

    jetIDtight = new std::vector<bool>[inputCollections.size()];
    jetIDtightLeptonVeto = new std::vector<bool>[inputCollections.size()];

    jetPUIDmedium = new std::vector<bool>[inputCollections.size()];
    jetPUIDtight = new std::vector<bool>[inputCollections.size()];
    
    originatesFromW = new std::vector<bool>[inputCollections.size()];
    originatesFromZ = new std::vector<bool>[inputCollections.size()];
    originatesFromTop = new std::vector<bool>[inputCollections.size()];
    originatesFromChargedHiggs = new std::vector<bool>[inputCollections.size()];
    originatesFromUnknown = new std::vector<bool>[inputCollections.size()]; 
    
    MCjet = new FourVectorDumper[inputCollections.size()];
    if(systVariations){
      systJESup = new FourVectorDumper[inputCollections.size()];
      systJESdown = new FourVectorDumper[inputCollections.size()];
      systJERup = new FourVectorDumper[inputCollections.size()];
      systJERdown = new FourVectorDumper[inputCollections.size()];
    }
    
    // DeepCSV b-tagger
    pfDeepCSVBJetTags = new std::vector<float>[inputCollections.size()];
    
    // DeepCSV charm tagger
    pfDeepCSVCvsLJetTags = new std::vector<float>[inputCollections.size()];
    pfDeepCSVCvsBJetTags = new std::vector<float>[inputCollections.size()];
    
    // DeepFlavour b-tagger
    pfDeepFlavourBJetTags = new std::vector<float>[inputCollections.size()];
    
    axis1 = new std::vector<double>[inputCollections.size()];
    axis2 = new std::vector<double>[inputCollections.size()];
    ptD   = new std::vector<double>[inputCollections.size()];
    mult  = new std::vector<int>[inputCollections.size()];
    pullRap = new std::vector<double>[inputCollections.size()];
    pullPhi = new std::vector<double>[inputCollections.size()];
    charge = new std::vector<double>[inputCollections.size()];
}

JetDumper::~JetDumper(){}

void JetDumper::book(TTree* tree){
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
    tree->Branch((name+"_pfDeepCSVCvsLJetTags").c_str(), &pfDeepCSVCvsLJetTags[i]);
    tree->Branch((name+"_pfDeepCSVCvsBJetTags").c_str(), &pfDeepCSVCvsBJetTags[i]);
    tree->Branch((name+"_pfDeepFlavourBJetTags").c_str(), &pfDeepFlavourBJetTags[i]);
    
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
      branch_name = branch_name.erase(pos_semicolon,1);
      tree->Branch((name+"_"+branch_name).c_str(),&userfloats[inputCollections.size()*iDiscr+i]);
    }
    std::vector<std::string> userintNames = inputCollections[i].getParameter<std::vector<std::string> >("userInts");
    for(size_t iDiscr = 0; iDiscr < userintNames.size(); ++iDiscr) {
      std::string branch_name = userintNames[iDiscr];
      size_t pos_semicolon = branch_name.find(":");
      branch_name = branch_name.erase(pos_semicolon,1);
      tree->Branch((name+"_"+branch_name).c_str(),&userints[inputCollections.size()*iDiscr+i]);
    }

    tree->Branch((name+"_IDtight").c_str(),&jetIDtight[i]);
    tree->Branch((name+"_IDtightLeptonVeto").c_str(),&jetIDtightLeptonVeto[i]);

    tree->Branch((name+"_PUIDmedium").c_str(),&jetPUIDmedium[i]);
    tree->Branch((name+"_PUIDtight").c_str(),&jetPUIDtight[i]);
    
    tree->Branch((name+"_originatesFromW").c_str(),&originatesFromW[i]);
    tree->Branch((name+"_originatesFromZ").c_str(),&originatesFromZ[i]);
    tree->Branch((name+"_originatesFromTop").c_str(),&originatesFromTop[i]);
    tree->Branch((name+"_originatesFromChargedHiggs").c_str(),&originatesFromChargedHiggs[i]);
    tree->Branch((name+"_originatesFromUnknown").c_str(),&originatesFromUnknown[i]);
    
    MCjet[i].book(tree, name, "MCjet");
    
    if(systVariations){
      systJESup[i].book(tree, name, "JESup");
      systJESdown[i].book(tree, name, "JESdown");
      systJERup[i].book(tree, name, "JERup");
      systJERdown[i].book(tree, name, "JERdown");
    }
    
    tree->Branch((name+"_axis1").c_str(), &axis1[i]);    
    tree->Branch((name+"_axis2").c_str(), &axis2[i]);    
    tree->Branch((name+"_ptD").c_str(),   &ptD[i]);    
    tree->Branch((name+"_mult").c_str(),  &mult[i]);
    tree->Branch((name+"_pullRap").c_str(), &pullRap[i]);
    tree->Branch((name+"_pullPhi").c_str(), &pullPhi[i]);
    tree->Branch((name+"_pfcharge").c_str(), &charge[i]);
  }
}

bool JetDumper::fill(edm::Event& iEvent, const edm::EventSetup& iSetup){
    if (!booked) return true;
/*
    if (!fJECUncertainty.size()) {
      for(size_t i = 0; i < inputCollections.size(); ++i) {
        edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
        iSetup.get<JetCorrectionsRecord>().get(inputCollections[i].getParameter<std::string>("jecPayload"),JetCorParColl);
//        bool found = true;
        try {
          JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
          fJECUncertainty.push_back(new JetCorrectionUncertainty(JetCorPar));
        } catch(cms::Exception e) {
          std::cout << "Warning: cannot find cell 'Uncertainty' in JEC uncertainty table; JEC uncertainty forced to 0" << std::endl;
//          found = false;
          fJECUncertainty.push_back(nullptr);
        }

//        if (found) {
//          JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
//          fJECUncertainty.push_back(new JetCorrectionUncertainty(JetCorPar));
//        } else {
//          fJECUncertainty.push_back(nullptr);
//        }
//
      }
    }
*/
    


    edm::Handle <reco::GenParticleCollection> genParticlesHandle;
    if (!iEvent.isRealData())
      iEvent.getByToken(genParticleToken, genParticlesHandle);

    for(size_t ic = 0; ic < inputCollections.size(); ++ic){
        std::vector<std::string> discriminatorNames = inputCollections[ic].getParameter<std::vector<std::string> >("discriminators");
	std::vector<std::string> userfloatNames = inputCollections[ic].getParameter<std::vector<std::string> >("userFloats");
	std::vector<std::string> userintNames = inputCollections[ic].getParameter<std::vector<std::string> >("userInts");
	
        edm::Handle<edm::View<pat::Jet>> jetHandle;
        iEvent.getByToken(jetToken[ic], jetHandle);

	if(jetHandle.isValid()){

	    for(size_t i=0; i<jetHandle->size(); ++i) {
    		const pat::Jet& obj = jetHandle->at(i);

		pt[ic].push_back(obj.p4().pt());
                eta[ic].push_back(obj.p4().eta());
                phi[ic].push_back(obj.p4().phi());
                e[ic].push_back(obj.p4().energy());

		//p4[ic].push_back(obj.p4());
		
		qgTaggingVariables->compute(&obj, true);
                axis1[ic].push_back(qgTaggingVariables->getAxis1());
		axis2[ic].push_back(qgTaggingVariables->getAxis2());
                ptD[ic].push_back(qgTaggingVariables->getPtD());
		mult[ic].push_back(qgTaggingVariables->getMult());
		pullRap[ic].push_back(qgTaggingVariables->getPullRap());
                pullPhi[ic].push_back(qgTaggingVariables->getPullPhi());
		charge[ic].push_back(qgTaggingVariables->getCharge());
		
		for(size_t iDiscr = 0; iDiscr < discriminatorNames.size(); ++iDiscr) {
                    //std::cout << inputCollections[ic].getUntrackedParameter<std::string>("branchname","") << " / " << discriminatorNames[iDiscr] << std::endl;
		    discriminators[inputCollections.size()*iDiscr+ic].push_back(obj.bDiscriminator(discriminatorNames[iDiscr]));
		}
		
		pfDeepCSVBJetTags[ic].push_back( obj.bDiscriminator("pfDeepCSVJetTags:probb") + obj.bDiscriminator("pfDeepCSVJetTags:probbb"));
		pfDeepCSVCvsLJetTags[ic].push_back( obj.bDiscriminator("pfDeepCSVJetTags:probc") / (obj.bDiscriminator("pfDeepCSVJetTags:probc") + obj.bDiscriminator("pfDeepCSVJetTags:probudsg")));
		pfDeepCSVCvsBJetTags[ic].push_back( obj.bDiscriminator("pfDeepCSVJetTags:probc") / (obj.bDiscriminator("pfDeepCSVJetTags:probc") + obj.bDiscriminator("pfDeepCSVJetTags:probb") + obj.bDiscriminator("pfDeepCSVJetTags:probbb")));
		pfDeepFlavourBJetTags[ic].push_back(obj.bDiscriminator("pfDeepFlavourJetTags:probb")+obj.bDiscriminator("pfDeepFlavourJetTags:probbb")+obj.bDiscriminator("pfDeepFlavourJetTags:problepb"));
		
                for(size_t iDiscr = 0; iDiscr < userfloatNames.size(); ++iDiscr) {
                    //std::cout << inputCollections[ic].getUntrackedParameter<std::string>("branchname","") << " / " << userfloatNames[iDiscr] << std::endl;
                    userfloats[inputCollections.size()*iDiscr+ic].push_back(obj.userFloat(userfloatNames[iDiscr]));
                }
		for(size_t iDiscr = 0; iDiscr < userintNames.size(); ++iDiscr) {
		  // std::cout << inputCollections[ic].getUntrackedParameter<std::string>("branchname","") << " / " << userintNames[iDiscr] << std::endl;
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
		jetIDtight[ic].push_back(passJetID(kJetIDTight, obj));
                jetIDtightLeptonVeto[ic].push_back(passJetID(kJetIDTightLepVeto, obj));

		// Jet PU ID
                // https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetID
               
 		double PUID = 0;
                if(obj.hasUserData("pileupJetId:fullDiscriminant")){
 		  PUID = obj.userFloat("pileupJetId:fullDiscriminant");
 		}
                int puIDflag = static_cast<int>(PUID);
		jetPUIDmedium[ic].push_back(PileupJetIdentifier::passJetId(puIDflag, PileupJetIdentifier::kMedium));
		jetPUIDtight[ic].push_back(PileupJetIdentifier::passJetId(puIDflag, PileupJetIdentifier::kTight));
                
                // MC origin
                bool fromW = false;
                bool fromZ = false;
                bool fromTop = false;
                bool fromHplus = false;
                bool fromUnknown = false;
                if (!iEvent.isRealData()) {
                  // Find MC parton matching to jet
                  size_t iCandidate = 0;
                  double myBestDeltaR = 9999;
                  reco::Candidate::LorentzVector jetMomentum = obj.p4();
                  for (size_t iMC=0; iMC < genParticlesHandle->size(); ++iMC) {
                    const reco::Candidate & p = (*genParticlesHandle)[iMC];
                    int absPid = std::abs(p.pdgId());
                    if (absPid >= 1 && absPid <= 5) {
                      double myDeltaR = deltaR(jetMomentum, p.p4());
                      if (myDeltaR < 0.4 && myDeltaR < myBestDeltaR) {
                        myBestDeltaR = myDeltaR;
                        iCandidate = iMC;
                      }
                    }
                  }
                  if (iCandidate > 0) {
                    // Analyze ancestry
                    const reco::Candidate & p = (*genParticlesHandle)[iCandidate];
                    std::vector<const reco::Candidate*> ancestry = GenParticleTools::findAncestry(genParticlesHandle, &p);
                    for (auto& pa: ancestry) {
                      int absPid = std::abs(pa->pdgId());
                      if (absPid == kFromW)
                        fromW = true;
                      else if (absPid == kFromZ)
                        fromZ = true;
                      else if (absPid == kFromHplus)
                        fromHplus = true;
                      else if (absPid == 6)
                        fromTop = true;
                    }
                  } else {
                    fromUnknown = true;
                  }
                } else {
                  fromUnknown = true;
                }
                originatesFromW[ic].push_back(fromW);
                originatesFromZ[ic].push_back(fromZ);
                originatesFromTop[ic].push_back(fromTop);
                originatesFromChargedHiggs[ic].push_back(fromHplus);
                originatesFromUnknown[ic].push_back(fromUnknown);
                
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
/*
                  // JES
                  double uncUp = 0.0;
                  double uncDown = 0.0;
                  if (fJECUncertainty[ic] != nullptr) {
                    fJECUncertainty[ic]->setJetEta(obj.eta());
                    fJECUncertainty[ic]->setJetPt(obj.pt()); // here you must use the CORRECTED jet pt
                    uncUp = fJECUncertainty[ic]->getUncertainty(true);
                  }
                  systJESup[ic].add(obj.p4().pt()*(1.0+uncUp),
                                    obj.p4().eta(),
                                    obj.p4().phi(),
                                    obj.p4().energy()*(1.0+uncUp));
                  if (fJECUncertainty[ic] != nullptr) {
                    // Yes, one needs to set pt and eta again
                    fJECUncertainty[ic]->setJetEta(obj.eta());
                    fJECUncertainty[ic]->setJetPt(obj.pt()); // here you must use the CORRECTED jet pt
                    uncDown = fJECUncertainty[ic]->getUncertainty(false);
                  }
                  systJESdown[ic].add(obj.p4().pt()*(1.0-uncDown),
                                      obj.p4().eta(),
                                      obj.p4().phi(),
                                      obj.p4().energy()*(1.0-uncDown));
                  // JER
*/                
                }
            }
        }
    }
    return filter();
}

void JetDumper::reset(){

    for(size_t ic = 0; ic < inputCollections.size(); ++ic){
	pt[ic].clear();
	eta[ic].clear();
	phi[ic].clear();
	e[ic].clear();
//        p4[ic].clear();
        pdgId[ic].clear();
	hadronFlavour[ic].clear();
	partonFlavour[ic].clear();

	jetIDtight[ic].clear();
        jetIDtightLeptonVeto[ic].clear();

	jetPUIDmedium[ic].clear();
	jetPUIDtight[ic].clear();
        
        originatesFromW[ic].clear();
        originatesFromZ[ic].clear();
        originatesFromTop[ic].clear();
        originatesFromChargedHiggs[ic].clear();
        originatesFromUnknown[ic].clear();
        
        MCjet[ic].reset();
        // Systematics
	if(systVariations){
          systJESup[ic].reset();
          systJESdown[ic].reset();
          systJERup[ic].reset();
          systJERdown[ic].reset();
	}
	
	pfDeepCSVBJetTags[ic].clear();
	pfDeepCSVCvsLJetTags[ic].clear();
	pfDeepCSVCvsBJetTags[ic].clear();
	pfDeepFlavourBJetTags[ic].clear();
	
	axis1[ic].clear();
	axis2[ic].clear();
        ptD[ic].clear();
	mult[ic].clear();
	pullRap[ic].clear();
        pullPhi[ic].clear();
        charge[ic].clear();
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

bool JetDumper::passJetID(int id, const pat::Jet& jet) {
  // Recipe taken from https://twiki.cern.ch/twiki/bin/view/CMS/JetID (read on 14.08.2015)
  // Recipe taken from https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2016 (28.3.2018)
  // Recipe taken from https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2017 (5.12.2018)
  double eta = fabs(jet.eta());
  if (eta < 2.7) {     
    
    // Valid For AK4CHS and PUPPI
    
    // PF Jet ID                 Tight   TightLepVeto
    // Neutral Hadron Fraction   < 0.90    < 0.90
    // Neutral EM Fraction       < 0.90    < 0.90
    // Number of Constituents    > 1       > 1 
    // Muon Fraction             -         < 0.8
    
    int nConstituents = jet.chargedMultiplicity() + jet.neutralMultiplicity();
    
    if (id == kJetIDTight) {
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
      
      // Valid For AK4CHS and PUPPI
      
      // Additionally apply:
      // PF Jet ID                 Tight   TightLepVeto
      // Charged Hadron Fraction   > 0.00    > 0.00
      // Charged Multiplicity      > 0.00    > 0.00
      // Neutral EM Fraction       -         < 0.80
      
      if (id == kJetIDTight) {
        if (!(jet.chargedHadronEnergyFraction() > 0.))   return false;
        if (!(jet.chargedMultiplicity()         > 0))    return false;
      } else if (id == kJetIDTightLepVeto) {
        if (!(jet.chargedHadronEnergyFraction() > 0.))   return false;
        if (!(jet.chargedMultiplicity()         > 0))    return false;
        if (!(jet.chargedEmEnergyFraction()     < 0.80)) return false;
      }
    }
  } else {
    if (eta <= 3.0) {
      
      // Valid For AK4CHS
      
      // PF Jet ID                    Tight
      // Neutral EM Fraction          > 0.02 and <0.99
      // Number of Neutral Particles  > 2
      if (id == kJetIDTight) {
        if (!(jet.neutralEmEnergyFraction()     > 0.02)) return false;
        if (!(jet.neutralEmEnergyFraction()     < 0.99)) return false;
        if (!(jet.neutralMultiplicity()         > 2))    return false;
      }
      
      //  // Valid For AK4 PUPPI
      //
      //  // PF Jet ID                    Tight
      //  // Neutral Hadron Fraction      < 0.99
      //
      //  if (id == kJetIDTight) {
      // if (!(jet.neutralHadronEnergyFraction() < 0.99)) return false;
      ///  }
      
    }else{
      
      // Valid For AK4CHS
      
      // PF Jet ID                   Tight
      // Neutral EM Fraction         < 0.90
      // Neutral Hadron Fraction     > 0.02
      // Number of Neutral Particles > 10
      if (id == kJetIDTight) {
        if (!(jet.neutralEmEnergyFraction() < 0.90)) return false;
        if (!(jet.neutralHadronEnergyFraction() > 0.02)) return false;
	if (!(jet.neutralMultiplicity()     > 10  )) return false;    
      }
      
      //  // Valid For AK4 PUPPI
      //
      //  // PF Jet ID                    Tight
      //  // Neutral EM Fraction          < 0.90
      //  // Neutral Hadron Fraction      > 0.02
      //  // Number of Neutral Particles  > 2 and < 15
      // 
      //  if (id == kJetIDTight) {
      //        if (!(jet.neutralEmEnergyFraction() < 0.90)) return false;
      //if (!(jet.neutralHadronEnergyFraction() > 0.02)) return false;
      //if (!(jet.neutralMultiplicity() > 2 )) return false;
      //if (!(jet.neutralMultiplicity() < 15 )) return false;
      //  } 
      
    }
  }
  return true;
}


