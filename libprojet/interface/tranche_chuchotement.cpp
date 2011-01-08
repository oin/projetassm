#include "tranche_chuchotement.h"
#include "controleur.h"

tranche_chuchotement::tranche_chuchotement(controleur& c, effet* e, int numero_effet) : tranche_effet(c, e, numero_effet) {
	conteneur_.set_label("Chuchotement");
}