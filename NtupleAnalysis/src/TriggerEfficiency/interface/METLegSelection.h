#ifndef TriggerEfficiency_METLegSelection_h
#define TriggerEfficiency_METLegSelection_h

#include "TriggerEfficiency/interface/BaseSelection.h"
#include "Math/VectorUtil.h"

class METLegSelection : public BaseSelection {
 public:
  METLegSelection();
  ~METLegSelection();

  bool offlineSelection(const Event&);
  bool onlineSelection(const Event&);

 private:

};

METLegSelection::METLegSelection(){}
METLegSelection::~METLegSelection(){}

bool METLegSelection::offlineSelection(const Event& fEvent){

  xvariable = fEvent.met_Type1().et();

  std::vector<Tau> selectedTaus;
  for(Tau tau: fEvent.taus()) {
    if(!(tau.pt() > 20)) continue;
    if(!(std::abs(tau.eta()) < 2.1)) continue;
    if(!(tau.lTrkPt() > 20)) continue;
    if(!(tau.nProngs() == 1)) continue;
    if(!tau.decayModeFinding()) continue;

    selectedTaus.push_back(tau);
  }
  size_t ntaus = selectedTaus.size();

  size_t njets = 0;
  for(Jet jet: fEvent.jets()) {
    bool skipJet = false;
    for(std::vector<Tau>::iterator i = selectedTaus.begin(); i!= selectedTaus.end(); ++i){
      double deltaR = ROOT::Math::VectorUtil::DeltaR(jet.p4(),i->p4());
      if(deltaR < 0.5) skipJet = true;
    }
    if(skipJet) continue;
    if(!(jet.pt() > 30)) continue;
    if(!jet.PUIDtight()) continue;

    ++njets;
  }

  size_t nmuons = 0;
  for(Muon muon: fEvent.muons()) {
    if(muon.pt() > 15 && std::abs(muon.eta()) < 2.1)
      ++nmuons;
  }

  size_t nelectrons = 1;//0;                                                                                                                           
  /*                                                                                                                                                     
  for(Electron electron: fEvent.electrons()) {                                                                                                         
    if(electron.pt() > 15 && std::abs(electron.eta()) < 2.4)                                                                                           
      ++nelectrons;                                                                                                                                    
  }                                                                                                                                                    
  */
  bool selected = false;
  if(ntaus > 0 && njets > 2 && nmuons == 0 && nelectrons == 0) selected = true;
  return selected;
}
bool METLegSelection::onlineSelection(const Event& fEvent){
  return true;
}

#endif
