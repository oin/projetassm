#include "chaine_effets.h"

chaine_effets::chaine_effets(assm::son& s) : s_(s) {
	mettre_a_jour_son();
}

chaine_effets::~chaine_effets() {}

void chaine_effets::operator()() {
	for(std::vector<effet*>::iterator it = effets_.begin(); it != effets_.end(); ++it)
		(**it)();
}

std::vector<effet*>& chaine_effets::effets() {
	return effets_;
}

void chaine_effets::cible(assm::son& s) {
	s_ = s;
	mettre_a_jour_son();
}

const assm::son& chaine_effets::cible() const {
	return s_;
}
	
void chaine_effets::mettre_a_jour_son() {
	for(std::vector<effet*>::iterator it = effets_.begin(); it != effets_.end(); ++it)
		(*it)->cible(s_);
}