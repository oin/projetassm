#include "effet.h"
#include <algorithm>

void effet::dry(double d) {
	dry_ = std::min(std::max(0.0, d), 1.0);
}

void effet::wet(double d) {
	dry(1 - d);
}

double effet::dry() const {
	return dry_;
}

double effet::wet() const {
	return 1.0 - dry_;
}

void effet::cible(assm::son& s) {
	s_ = s;
}

assm::son& effet::cible() {
	return s_;
}

void effet::debut(double d) {
	debut_ = d;
}

void effet::fin(double f) {
	fin_ = f;
}

double effet::debut() const {
	return debut_;
}

double effet::fin() const {
	return fin_;
}

size_t effet::echantillon_debut() const {
	return debut_ * s_.size();
}

size_t effet::echantillon_fin() const {
	return fin_ * s_.size();
}

void effet::limites(double d, double f) {
	debut(d);
	fin(f);
}

void effet::allonger() {
	// On rajoute des échantillons sur la fin si le son n'est pas assez grand, sinon on bouge la fin
	double allongement_ = allongement();
	if(echantillon_fin() + allongement_ > s_.size())
		s_.data().resize(echantillon_fin() + allongement_);
	else
		fin_ += allongement_ * 1.0 / s_.size();
}