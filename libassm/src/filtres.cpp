#include "filtres.h"

namespace assm {
	filtrage_passe_bas::filtrage_passe_bas(unsigned int taille, unsigned int ordre) : taille_(taille), ordre_(ordre), n_(0) {}
	
	double filtrage_passe_bas::operator()(double valeur) {
		if(n_ == 0 || n_ == ordre_ / 2) {
			++n_;
			return 1 * valeur;
		}
		if(n_ >= 1 && n_ < ordre_ / 2) {
			++n_;
			return 2 * valeur;
		}
		if(n_ > ordre_ / 2 && n_ <= taille_ - 1) {
			++n_;
			return 0;
		}
		return valeur;
	}
}