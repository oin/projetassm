#include "son.h"
#include "unites.h"
#include <algorithm>
#include <iostream>
#include <cmath>

namespace assm {

son::son(size_t r) : rate_(r) {}
son::son(size_t t, size_t r) : tampon_(t), rate_(r) {}
son::son(double t, size_t r, bool) : tampon_(t*r), rate_(r) {}
son::son(buffer& b, size_t r) : tampon_(b), rate_(r) {}

void son::volume(double v) {
	v = std::max(std::min(v, 1.0), 0.0);
	for(buffer::iterator it = tampon_.begin(); it != tampon_.end();)
		*it++ *= v;
}

void son::attenuer(double a) {
	// std::cout << "utilisation de son::attenuer() : attention pb échelle" << std::endl;
	a = std::max(std::min(a, 120.0), 0.0);
	for(buffer::iterator it = tampon_.begin(); it != tampon_.end(); ++it)
		*it = to_volume_from_amplitude(to_amplitude_from_volume(*it) - a);
}

double son::temps(size_t indice, double multiplicateur) {
	return indice * 1.0 / rate() * multiplicateur;
}

size_t son::indice(double temps, double diviseur) {
	return static_cast<size_t>(round(temps * rate() / diviseur));
}

}