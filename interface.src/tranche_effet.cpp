#include "tranche_effet.h"
#include "controleur.h"

tranche_effet::tranche_effet(controleur& c, effet* e) : c_(c), e_(e), afficheur_(c.apercu(), e) {
	conteneur_.set_label("Effet");
	conteneur_.add(gauche_);
	pack_start(conteneur_, true, true, 5);
	pack_start(afficheur_, true, true, 5);
}

tranche_effet::~tranche_effet() {}