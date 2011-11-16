#include "ExtractableMaxCounter.h"
#include <iostream>

#include "TMath.h"




ExtractableMaxCounter::ExtractableMaxCounter(std::string id, std::string distribution, std::string description,
                                       std::vector< std::string > counterHisto, std::string counterItem)
: Extractable(id, distribution, description) {
  for (size_t i = 0; i < counterHisto.size(); ++i) {
    vCounters.push_back(new ExtractableCounter(id, counterHisto[i], counterItem));
  }
}

ExtractableMaxCounter::~ExtractableMaxCounter() {
  for (size_t i = 0; i < vCounters.size(); ++i) {
    delete vCounters[i];
  }
}

double ExtractableMaxCounter::doExtract(std::vector< Dataset* > datasets, NormalisationInfo* info) {
  // First item should contain the nominal results
  double myNominalResult = vCounters[0]->doExtract(datasets, info);
  double myMaxRatio = 0.0;
  for (size_t i = 1; i < vCounters.size(); ++i) {
    double myVariation = vCounters[i]->doExtract(datasets, info);
    //std::cout << "ratio: " << myVariation / myNominalResult << std::endl;
    if (TMath::Abs(myVariation / myNominalResult - 1.0) > myMaxRatio)
      myMaxRatio = TMath::Abs(myVariation / myNominalResult - 1.0);
  }
  return myMaxRatio; // Relative uncertainty
  return -1.;
}

void ExtractableMaxCounter::print() {
  std::cout << "Row / Counter: ";
  Extractable::print();
  vCounters[0]->print();
}
