#include "spectre.h"
#include <cassert>

namespace assm
{

spectre::spectre(size_t taille, size_t rate) :
	spectre_(taille),
	phase_(taille),
	rate_(rate) {}

spectre::spectre(buffer& in_sp, buffer& in_ph, size_t rate) :
	spectre_(in_sp),
	phase_(in_ph),
	rate_(rate) {}

spectre::spectre(buffer& in_sp, size_t rate) :
	spectre_(in_sp),
	rate_(rate) {}

spectre::spectre(std::vector<std::complex<double> >& in, size_t rate) :
	spectre_(in.size()),
	phase_(in.size()),
	rate_(rate)
{
	from_complex(in);
}

spectre::spectre(son& s) :
	spectre_(s.data()),
	phase_(s.size()),
	rate_(s.rate()) {}

void spectre::from_complex(std::vector<std::complex<double> >& in) {
	std::transform(in.begin(), in.end(), spectre_.begin(), std::abs<double>);
	std::transform(in.begin(), in.end(), phase_.begin(), std::arg<double>);
}

void spectre::decaler(int indice) {
	assert(frequence(std::abs(indice)) <= rate() / 2);
	double sens = indice >= 0;
	
	// La contrepéterie, c'est l'art de décaler les sons.
	
	if(sens)
	for(int i=size()-1; i >= 0; --i) {
		size_t dest = i + indice;
		if(dest >= 0 && dest < size())
			data()[dest] = data()[i];
		if(i < indice || i > (int)size() - indice)
			data()[i] = 0;
	}
	else
	for(size_t i=0; i < size(); ++i) {
		size_t dest = i + indice;
		if(dest >= 0 && dest < size())
			data()[dest] = data()[i];
		if((int)i < indice || (int)i > (int)size() - indice)
			data()[i] = 0;
	}
}

void spectre::conjugue_symetrie() {
	for(size_t i=0; i<size()/2; ++i) {
		std::complex<double> valeur = std::conj(std::polar(spectre_[i], phase_[i]));
		spectre_[size() - 1 - i] = std::abs(valeur);
		phase_[size() - 1 - i] = std::arg(valeur);
	}
}

} /* assm */