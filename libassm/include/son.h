#if !defined(SON_H_NS4EAZUO)
#define SON_H_NS4EAZUO

#include "buffer.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <cmath>
#include <limits>

namespace assm {

template <class T>
double normaliser(T valeur) {
	return static_cast<double>(valeur * 1.0f / std::numeric_limits<T>::max());
}

template <class T>
T denormaliser(double valeur) {
	return static_cast<T>(floor(1.0 * valeur * std::numeric_limits<T>::max()));
}

struct son {
	son(size_t);
	son(size_t, size_t);
	son(double, size_t, bool);
	son(buffer&, size_t);
	// template <class It>
	// 	son(It itd, It itf, size_t r) : rate_(r) {
	// 		append_raw(itd, itf);
	// 	}
	template <class It>
	void append_raw(It itd, It itf) {
		std::transform(itd, itf, std::back_inserter(tampon_), normaliser<typename std::iterator_traits<It>::value_type>);
	}
	template <class It>
	void set_raw(It itd, It itf) {
		std::transform(itd, itf, tampon_.begin(), normaliser<typename std::iterator_traits<It>::value_type>);
	}
	template <class It>
	void convert_to(It itd) {
		std::transform(tampon_.begin(), tampon_.end(), itd, denormaliser<typename std::iterator_traits<It>::value_type>);
	}
	size_t size() { return tampon_.size(); }
	buffer& data() { return tampon_; }
	buffer::iterator begin() { return tampon_.begin(); }
	buffer::iterator end() { return tampon_.end(); }
	size_t rate() { return rate_; }
	void volume(double v);
	void attenuer(double a);
	double duree() { return temps(size()); }
	double temps(size_t indice, double multiplicateur = 1.0);
	size_t indice(double temps, double diviseur = 1.0);
	void resize(size_t indice) { tampon_.resize(indice); }
private:
	buffer tampon_;
	size_t rate_;
};

}

#endif /* end of include guard: SON_H_NS4EAZUO */
