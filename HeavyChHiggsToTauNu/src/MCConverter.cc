#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/MCConverter.h"
#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/MyMET.h"
#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/MyEvent.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

using std::vector;
using edm::Handle;
using edm::SimVertexContainer;
using edm::SimTrackContainer;
using edm::HepMCProduct;

using std::cout;
using std::endl;

MCConverter::MCConverter(const edm::InputTag& genJetLabel, const edm::InputTag& simHitLabel,
                         const edm::InputTag& genLabel, const edm::InputTag& hepMcReplLabel):
        genJets(genJetLabel),
        simHits(simHitLabel),
        genParticles(genLabel),
        hepMcProductReplacement(hepMcReplLabel)
{}
MCConverter::~MCConverter() {}

void MCConverter::addMC(MyEvent *saveEvent, const edm::Event& iEvent) const {
        try {
                addMCParticles(iEvent, saveEvent->mcParticles, saveEvent->mcMET);
        } catch(const cms::Exception& e) {
                if(e.category() == "ProductNotFound")
                        return;
                else
                        throw;
        }

        saveEvent->mcPrimaryVertex = getMCPrimaryVertex(iEvent);
        setSimTracks(iEvent, *saveEvent);
        saveEvent->hasMCdata = true;
}

MyMCParticle MCConverter::convert(const reco::GenJet& genJet){
	MyMCParticle mcJet(genJet.px(),genJet.py(),genJet.pz(),genJet.energy());
	mcJet.pid = 0; //= genJet.pdgId();
	mcJet.status = 4;
	return mcJet;
}

void MCConverter::addMCJets(const edm::Event& iEvent, vector<MyMCParticle>& mcParticles) const {
	Handle<reco::GenJetCollection> genJetHandle;
        iEvent.getByLabel(genJets, genJetHandle);

        const reco::GenJetCollection & genJetCollection = *(genJetHandle.product());
        //cout << "MC GenJets " << genJetCollection.size();

        reco::GenJetCollection::const_iterator iJet;
        for(iJet = genJetCollection.begin(); iJet!= genJetCollection.end(); ++iJet){

          if(iJet->et() < 20 || fabs(iJet->eta()) > 2.5) continue;
          //cout << "     GenJet Et,eta " << iJet->et() << " " << iJet->eta() << endl;
          mcParticles.push_back(convert(*iJet));
        }
        //cout << ", saved " << mcParticles.size() << endl;
}


MyGlobalPoint MCConverter::getMCPrimaryVertex(const edm::Event& iEvent) const {
	Handle<SimVertexContainer> simVertices;
	iEvent.getByLabel(simHits, simVertices);

	if(simVertices->size() > 0)
                return MyGlobalPoint((*simVertices)[0].position().x(),
                                     (*simVertices)[0].position().y(),
                                     (*simVertices)[0].position().z());
        else
                return MyGlobalPoint(-999, -999, -999);
}

void MCConverter::addMCParticles(const edm::Event& iEvent, vector<MyMCParticle>& mcParticles, MyMET& mcMET) const {
        addMCJets(iEvent, mcParticles);

	Handle<reco::GenParticleCollection> mcEventHandle;
	iEvent.getByLabel(genParticles, mcEventHandle);

        if(edm::isDebugEnabled())
                LogDebug("MyEventConverter") << "MC particles size " << mcEventHandle->size() << std::endl;
	double mcMetX = 0;
	double mcMetY = 0;

	const reco::GenParticleCollection genParticles(*mcEventHandle);

	reco::GenParticleCollection::const_iterator i;
	for(i = genParticles.begin(); i!= genParticles.end(); ++i){
                /*
		cout << "  particle " 
		     << " " << i->pdgId()
		     << " " << i->status()
		     << " " << i->pt()
		     << " " << i->eta()
		     << " " << i->phi()
		     << endl;
                */

		int id = i->pdgId();

                if(abs(id) == 12 || abs(id) == 14 || abs(id) == 16){
                        mcMetX += i->px();
                        mcMetY += i->py();
                }

                if( ( i->status() == 1 ) ||
                    ( abs(id) == 12 || abs(id) == 14 || abs(id) == 16 || abs(id) <= 21) ||
                    ( i->status() == 3) ) {

                        // searching parents

                        vector<int> motherList;
			const reco::Candidate* mother = i->mother();
                        if(!mother)
                                continue;
                        while(mother->mother() != NULL){
				int motherId = mother->pdgId();
                                mother = mother->mother();
				if(mother->pdgId() != motherId) {
					motherList.push_back(motherId);
				}
			}

                        if(motherList.size() > 0){
                          if(motherList[0] != id){
                                MyMCParticle mcParticle(i->px(), i->py(), i->pz(), i->energy());
                                mcParticle.pid    = id;
                                mcParticle.status = i->status();
                                //mcParticle.barcode = (*i)->barcode();

                                mcParticle.mother = motherList;
                                //mcParticle.motherBarcodes = motherBarcodes;
                                mcParticles.push_back(mcParticle);
                          }
                        }
		}
	}
	mcMET.Set(mcMetX,mcMetY);

/*
        Handle<HepMCProduct> mcEventHandle;
        iEvent.getByLabel(hepMcProduct, mcEventHandle);

        const HepMC::GenEvent* mcEvent = mcEventHandle->GetEvent() ;
        //cout << "MC particles size " << mcEvent->particles_size() << endl;

        double mcMetX = 0;
        double mcMetY = 0;
        HepMC::GenEvent::particle_const_iterator i;
        for(i = mcEvent->particles_begin(); i!= mcEvent->particles_end(); i++){

                        cout << "  particle " << (*i)->barcode()
                             << " " << (*i)->pdg_id()
                             << " " << (*i)->status()
                             << " " << (*i)->momentum().perp()
                             << " " << (*i)->momentum().eta()
                             << " " << (*i)->momentum().phi()
                             << endl;


		int id = (*i)->pdg_id();

                if((*i)->status() == 1 && (abs(id) == 12 || abs(id) == 14 || abs(id) == 16)){
                        mcMetX += (*i)->momentum().x();
                        mcMetY += (*i)->momentum().y();
                }

//                        if( ( (*i)->status() == 1 && (*i)->momentum().perp() > 1) ||
                if( ( (*i)->status() == 1 ) ||
                    ( abs(id) == 12 || abs(id) == 14 || abs(id) == 16 || abs(id) <= 21) ||
                    ( (*i)->status() == 3) ) {

                        // searching parents

                        vector<int> motherList;
                        vector<int> motherBarcodes;
                        if( (*i)->production_vertex() ) {
                                HepMC::GenVertex::particle_iterator iMother =
                                  (*i)->production_vertex()->particles_begin(HepMC::parents);
				if(*iMother != 0) {
                                    while( (*iMother)->production_vertex() ) {
                                        int motherId = (*iMother)->pdg_id();
					int motherBarCode = (*iMother)->barcode();
                                        //cout << "          mother ids,barcode " << motherId 
                                        //     << " " << (*iMother)->barcode() << endl;
                                        iMother = (*iMother)->production_vertex()->particles_begin(HepMC::parents);
					if((*iMother)->pdg_id() != motherId) {
						motherList.push_back(motherId);
						motherBarcodes.push_back(motherBarCode);
					}
                                    }
				}
                        }

			if(motherList.size() > 0){
			  if(motherList[0] != id){
				MyMCParticle mcParticle;
				mcParticle.pid    = id;
				mcParticle.status = (*i)->status();
				mcParticle.barcode = (*i)->barcode();
                               	mcParticle.SetE((*i)->momentum().e());
                               	mcParticle.SetPx((*i)->momentum().px());
                               	mcParticle.SetPy((*i)->momentum().py());
                               	mcParticle.SetPz((*i)->momentum().pz());

                                //mcParticle.motherLine = myMCMotherIterator;
                                mcParticle.mother = motherList;
				mcParticle.motherBarcodes = motherBarcodes;
				//cout << "SAVING particle " << mcParticle.barcode << " " << mcParticle.pid << endl;
				mcParticles.push_back(mcParticle);
			  }
			}
		}
	}
	mcMET.Set(mcMetX,mcMetY);
*/
	// newSource from muon->tau conversion, saving the MC tau and its decay products
        Handle<HepMCProduct> mcEventHandle2;
        iEvent.getByLabel(hepMcProductReplacement, mcEventHandle2);

        if(mcEventHandle2.isValid()){

                const HepMC::GenEvent* mcEvent = mcEventHandle2->GetEvent() ;
                //cout << "MC particles size " << mcEvent->particles_size() << endl;

                HepMC::GenEvent::particle_const_iterator i;
                for(i = mcEvent->particles_begin(); i!= mcEvent->particles_end(); i++){
/*
                        cout << "  particle " << (*i)->barcode()
                             << " " << (*i)->pdg_id()
                             << " " << (*i)->status()
                             << " " << (*i)->momentum().perp()
                             << " " << (*i)->momentum().eta()
                             << " " << (*i)->momentum().phi()
                             << endl;
*/

                        int id = (*i)->pdg_id();

                        // searching parents
                        // searching parents

                        vector<int> motherList;
                        vector<int> motherBarcodes;
                        if( (*i)->production_vertex() ) {
                                HepMC::GenVertex::particle_iterator iMother =
                                        (*i)->production_vertex()->particles_begin(HepMC::parents);
                                while( *iMother && (*iMother)->production_vertex() ) {
                                        int motherId = (*iMother)->pdg_id();
                                        int motherBarCode = (*iMother)->barcode();
                                        //cout << "          mother ids,barcode " << motherId
                                        //     << " " << (*iMother)->barcode() << endl;
                                        iMother = (*iMother)->production_vertex()->particles_begin(HepMC::parents);
                                        // If the mother doesn't have mother, add to the motherList
                                        if(!*iMother || (*iMother)->pdg_id() != motherId) {
                                                motherList.push_back(motherId);
                                                motherBarcodes.push_back(motherBarCode);
                                        }
                                }
                        }

                        if(motherList.size() == 0 || motherList[0] != id){
                                MyMCParticle mcParticle((*i)->momentum().px(), (*i)->momentum().py(), (*i)->momentum().pz(), (*i)->momentum().e());
                                mcParticle.pid    = id;
                                mcParticle.status = (*i)->status();
                                mcParticle.barcode = (*i)->barcode();

                                //mcParticle.motherLine = myMCMotherIterator;
                                mcParticle.mother = motherList;
                                mcParticle.motherBarcodes = motherBarcodes;
                                //cout << "SAVING particle " << mcParticle.barcode << " " << mcParticle.pid << endl;
                                mcParticles.push_back(mcParticle);
                        }
                }
	}
}

void MCConverter::setSimTracks(const edm::Event& iEvent, MyEvent& event){
  vector<MySimTrack>& simTracks(event.simTracks);
  // save sim tracks in cone of 0.7 around tau candidate leading track
  const double myMatchCone = 0.70;

  Handle<SimTrackContainer> simTrackHandle;
  iEvent.getByType<SimTrackContainer>(simTrackHandle);
  Handle<SimVertexContainer> simVertices;
  iEvent.getByType<SimVertexContainer>(simVertices);

  // Loop over tau candidates
  vector<MyJet*> taujets = event.getCollection("caloRecoTauProducer");
  for (vector<MyJet*>::const_iterator iJet = taujets.begin() ; iJet != taujets.end(); ++iJet) {
    // Get leading track
    const MyTrack* myLdgTrack = (*iJet)->leadingTrack();
    if(!myLdgTrack)
      continue;
//    cout << "jet ldg track eta=" << myLdgTrack.eta()
//	 << " phi=" << myLdgTrack.phi() << endl;

    // Loop over SimTracks in container
    SimTrackContainer::const_iterator iSim = simTrackHandle->begin();
    for( ; iSim != simTrackHandle->end(); ++iSim) {
//      const math::XYZTLorentzVectorD & myMomentum = (*iSim).momentum();
      TLorentzVector myMomentum((*iSim).momentum().x(),(*iSim).momentum().y(),(*iSim).momentum().z(),(*iSim).momentum().t());
      ////      const HepLorentzVector myMomentum = (*iSim).momentum();
      if (myMomentum.Et() > 1) { // require sim track pt > 1 GeV
	if (myLdgTrack->p4().DeltaR(myMomentum) < myMatchCone ){
//myDeltaR(myLdgTrack->eta(), myMomentum.eta(),
//		   myLdgTrack->phi(), myMomentum.phi()) < myMatchCone) {
	  //cout << "- simTrack eta=" << myMomentum.eta()
	  //     << " phi=" << myMomentum.phi()
	  //     << " myDeltaR=" 
	  //     << myDeltaR(myLdgTrack.eta(), myMomentum.eta(),
	  //        myLdgTrack.phi(), myMomentum.phi()) << endl;

	  // Save sim track
	  MySimTrack mySim;
	  mySim.SetXYZM(myMomentum.X(), myMomentum.Y(), myMomentum.Z(), 0);
	  mySim.theGenPID = (*iSim).genpartIndex();
	  mySim.theType = (*iSim).type();
	  mySim.theTrackID = (int)(*iSim).trackId();
	  // Production point of sim track
	  if ((*iSim).vertIndex() >= 0) {
	    SimVertex mySimVertex = (*simVertices)[(*iSim).vertIndex()];
	    mySim.thePosition.SetXYZ(mySimVertex.position().x(),
				     mySimVertex.position().y(),
				     mySimVertex.position().z());
	  } else {
	    mySim.thePosition.SetXYZ(0,0,0);
	  }
	  // ECAL hit point
	  const math::XYZVectorD & myPos = (*iSim).trackerSurfacePosition();
	  ////const Hep3Vector myPos = (*iSim).trackerSurfacePosition();
	  mySim.trackEcalHitPoint.SetX(myPos.x());
	  mySim.trackEcalHitPoint.SetY(myPos.y());
	  mySim.trackEcalHitPoint.SetZ(myPos.z());
	  // Store sim track
	  //mySim.print();
	  simTracks.push_back(mySim);
	}
      }
    }
  }
}

