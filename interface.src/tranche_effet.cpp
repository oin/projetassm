#include "tranche_effet.h"
#include "controleur.h"

tranche_effet::tranche_effet(controleur& c, effet* e, int numero_effet) : c_(c), e_(e), numero_effet_(numero_effet), afficheur_(c, e, numero_effet) {
	conteneur_.set_label("Effet");
	conteneur_.add(gauche_);
	pack_start(conteneur_, true, true, 5);
	pack_start(afficheur_, true, true, 5);
}

tranche_effet::~tranche_effet() {}