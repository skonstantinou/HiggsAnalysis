#ifndef QGTaggingVariables_h
#define QGTaggingVariables_h

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
#include "HiggsAnalysis/MiniAOD2TTree/interface/FourVectorDumper.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/JetReco/interface/Jet.h"

/*
  Code from: RecoJets/JetProducers/plugins/QGTagger.cc
*/

class QGTaggingVariables {
  
 public:
  
 QGTaggingVariables():
  axis1(0), axis2(0), ptD(0), totalmult(0){};
  ~QGTaggingVariables(){};
  
  double getAxis1() const { return axis1; }
  double getAxis2() const { return axis2; }
  double getPtD()   const { return ptD;   }
  int    getMult() const { return totalmult; }
  double getPullRap() const { return pullRap; }
  double getPullPhi() const { return pullPhi; }
  double getCharge() const { return charge; }
  
  void compute(const reco::Jet *jet, bool isReco)
  {
    // Initialize Variables
    axis1 = 0;
    axis2 = 0;
    ptD = 0;
    totalmult = 0;
    pullRap = 0.0;
    pullPhi = 0.0;
    charge = 0.0;
    
    if (jet->numberOfDaughters() == 0) return;
    
    float sum_weight    = 0.0;
    float sum_dEta      = 0.0; 
    float sum_dPhi      = 0.0;
    float sum_dEta2     = 0.0;
    float sum_dPhi2     = 0.0; 
    float sum_dEta_dPhi = 0.0;
    float sum_pt        = 0.0;
    
    // Quality Cuts currently hard-coded to false. Not stored for packedCandidates yet. We'll need to fix it if useQC is changed to true.
    bool useQC = false;  
    
    // Loop over all the jet constituents (PF Candidates)
    for(auto part : jet->getJetConstituentsQuick())
      {
	if(part->charge())
	  { 
	    if(isReco) 
	      {
		auto p = dynamic_cast<const pat::PackedCandidate*>(part);
		if (!p) std::cout << "ERROR: QGTagging variables cannot be computed for these jets!" << std::endl;
		if (!(p->fromPV() > 1 && p->trackHighPurity())) continue;
		if(useQC) 
		  {
		    if(p->dzError()==0 || p->dxyError()==0 ) continue;
		    if((p->dz()*p->dz())/(p->dzError()*p->dzError() ) > 25. ) continue; 
		    if((p->dxy()*p->dxy()) / (p->dxyError()*p->dxyError()) < 25.) ++totalmult;
		  } else ++totalmult;
	      } else ++totalmult;
	  }
	else { // neutral particles
	  if (part->pt() < 1.0) continue;
	  ++totalmult;
	} // Charged/Neutral particles
	
	float dEta = part->eta() - jet->eta();
	float dPhi = reco::deltaPhi(part->phi(), jet->phi());
	float partPt = part->pt(); 
	float weight = partPt*partPt; 
	
	sum_weight += weight;
	sum_pt += partPt;
	sum_dEta += dEta * weight;
	sum_dPhi += dPhi * weight;
	sum_dEta2+= dEta*dEta * weight;
	sum_dEta_dPhi += dEta*dPhi * weight;
	sum_dPhi2 += dPhi*dPhi * weight;
	
      } // Closes loop over all jet constituents 
    
    // Calculate axis2 and ptD
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;
    float ave_dEta = 0.0;
    float ave_dPhi = 0.0;
    float ave_dEta2 = 0.0; 
    float ave_dPhi2 = 0.0;  
    
    if(sum_weight > 0)
      {
	ptD = sqrt(sum_weight)/sum_pt;
	ave_dEta = sum_dEta/sum_weight;
	ave_dPhi = sum_dPhi/sum_weight;
	ave_dEta2 = sum_dEta2/sum_weight;
	ave_dPhi2 = sum_dPhi2/sum_weight;
	a = ave_dEta2 - ave_dEta*ave_dEta;
	b = ave_dPhi2 - ave_dPhi*ave_dPhi;
	c = -(sum_dEta_dPhi/sum_weight - ave_dEta*ave_dPhi);
      } 
    else ptD = 0;
    
    float delta = sqrt(fabs( (a-b)*(a-b) + 4*c*c ));
    if(a+b-delta > 0) axis2 = sqrt(0.5*(a+b-delta));
    else              axis2 = 0.0; 
    if(a+b+delta > 0) axis1 = sqrt(0.5*(a+b+delta));
    else              axis1 = 0.0; 

    // Calculate Pull
    double jetRap = jet -> rapidity();
    double jetPhi = jet -> phi();

    if (jet->pt() == 0) return;

    int nConst = jet->numberOfDaughters();
    for (int iDau = 0; iDau<nConst; ++iDau)
      {
        const auto *con = jet->daughter(iDau);
	const double dRap = con->rapidity() - jetRap;
        const double dPhi = reco::deltaPhi(con->phi(), jetPhi);
	const double dR = sqrt(dRap*dRap + dPhi*dPhi);
        pullRap += dRap*con->pt()*dR;
        pullPhi += dPhi*con->pt()*dR;

        if (con->charge() == 0) continue;
        charge += float(con->charge())*con->pt();
      }
    pullRap /= jet->pt();
    pullPhi /= jet->pt();
    charge  /= jet->pt();
  }
  
 private:
  double axis1;
  double axis2;
  double ptD;
  int totalmult;
  double pullRap;
  double pullPhi;
  double charge;
};

#endif
