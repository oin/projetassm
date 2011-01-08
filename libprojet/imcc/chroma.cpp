#include "chroma.h"
#include <cmath>

namespace imcc {

void pitch_class_profile::operator()(const assm::spectre &s) {
	for(size_t i=1; i<s.size()-1; ++i) {
		double frequence = s.frequence(i);
		if(s.data()[i] > s.data()[i+1] && s.data()[i] > s.data()[i-1]) {
			size_t Mf = static_cast<size_t>(round(chromas_ * log2(frequence / frequence_ref_))) % chromas_;
			pcp_[Mf] += pow(s.data()[i] * s.size(), 2);
		}
	}
}

}