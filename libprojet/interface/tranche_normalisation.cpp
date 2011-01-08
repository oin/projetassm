#include "tranche_normalisation.h"
#include "controleur.h"

tranche_normalisation::tranche_normalisation(controleur& c, effet* e, int numero_effet) : tranche_effet(c, e, numero_effet) {
	conteneur_.set_label("Normalisation");
}