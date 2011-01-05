#if !defined(SPECTRE_H_Z9AXVFSY)
#define SPECTRE_H_Z9AXVFSY

#include "buffer.h"
#include "son.h"
#include <vector>
#include <complex>

namespace assm {

struct spectre {
	spectre(size_t taille, size_t rate);
	spectre(buffer& in_sp, buffer& in_ph, size_t rate);
	spectre(buffer& in_sp, size_t rate);
	spectre(son& s);
	spectre(std::vector<std::complex<double> >& , size_t rate);
	size_t size() const { return spectre_.size(); }
	const buffer& data() const { return spectre_; }
	buffer& data() { return spectre_; }
	buffer::iterator begin() { return spectre_.begin(); }
	buffer::iterator end() { return spectre_.end(); }
	const buffer& phase() const { return phase_; }
	buffer& phase() { return phase_; }
	size_t rate() const { return rate_; }
	void from_complex(std::vector<std::complex<double> >& in);
	void from_function(double (*f)(double)) {
		for(size_t i=0; i<spectre_.size(); ++i)
			spectre_[i] = f(frequence(i));
	}
	double frequence(double i) const {
		return 1.0 * rate() * i / spectre_.size();
	}
	size_t index(double frequence) const {
		return 1.0 * frequence * spectre_.size() / rate();
	}
	void conjugue_symetrie();
	void decaler(int index);
private:
	buffer spectre_;
	buffer phase_;
	size_t rate_;
};

}

#endif /* end of include guard: SPECTRE_H_Z9AXVFSY */
