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

void effet::in(assm::son& s) {
	s_ = &s;
}

assm::son& effet::in() {
	return *s_;
}

void effet::out(assm::son& s) {
	s_out_ = &s;
}

assm::son& effet::out() {
	return *s_out_;
}

void effet::debut(double d) {
	debut_ = std::min(std::max(0.0, d), 1.0);
	if(debut_ > fin_)
		std::swap(debut_, fin_);
}

void effet::fin(double f) {
	fin_ = std::min(std::max(0.0, f), 1.0);
	if(debut_ > fin_)
		std::swap(debut_, fin_);
}

double effet::debut() const {
	return debut_;
}

double effet::fin() const {
	return fin_;
}

size_t effet::echantillon_debut() {
	return debut_ * in().size();
}

size_t effet::echantillon_fin() {
	return fin_ * in().size();
}

void effet::limites(double d, double f) {
	debut(d);
	fin(f);
}