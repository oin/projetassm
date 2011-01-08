#include "tranche_inverse.h"
#include "controleur.h"

tranche_inverse::tranche_inverse(controleur& c, effet* e, int numero_effet) : tranche_effet(c, e, numero_effet) {
	conteneur_.set_label("Inversion");
}