#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/MyEventConverter.h"

map<string,double> MyEventConverter::btag(const JetTag& jet){
	map<string,double> tagInfo;
	tagInfo["discriminator"] = jet.discriminator();
	return tagInfo;
}
