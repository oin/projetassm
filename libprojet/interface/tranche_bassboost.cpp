#include "tranche_bassboost.h"
#include "controleur.h"

tranche_bassboost::tranche_bassboost(controleur& c, effet* e, int numero_effet) : tranche_effet(c, e, numero_effet) {
	conteneur_.set_label("Bass boost");
}