#include "chaine_effets.h"
#include "effet.h"

chaine_effets::chaine_effets(assm::son& s) : s_(s), s_tmp1_(s.rate()), s_tmp2_(s.rate()) {}

chaine_effets::~chaine_effets() {}

void chaine_effets::operator()() {
	// Redimensionne les sons "out"
	s_tmp1_.data().resize(in().size());
	s_tmp2_.data().resize(s_tmp1_.size());
	
	for(size_t i=0; i<effets_.size(); ++i) {
		effet& courant = *effets_[i];
		// Règle l'entrée et la sortie
		if(i % 2 == 0) {
			courant.in(s_tmp2_);
			courant.out(s_tmp1_);
		} else {
			courant.in(s_tmp1_);
			courant.out(s_tmp2_);
		}
		
		if(i == 0)
			courant.in(s_);
		
		// out <- in (pour l'instant)
		courant.out().resize(courant.in().size());
		std::copy(courant.in().data().begin(), courant.in().data().end(), courant.out().data().begin());
		
		// Applique l'effet
		courant();
	}
}

std::vector<effet*>& chaine_effets::effets() {
	return effets_;
}

void chaine_effets::in(assm::son& s) {
	s_ = s;
}

assm::son& chaine_effets::in() {
	return s_;
}

assm::son& chaine_effets::out() {
	return effets_.size() % 2 == 0 ? s_tmp2_ : s_tmp1_;
}