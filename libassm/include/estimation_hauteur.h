#if !defined(ESTIMATION_HAUTEUR_H_K9RXGQ0N)
#define ESTIMATION_HAUTEUR_H_K9RXGQ0N

#include <vector>
#include "son.h"

namespace assm {
	double autocorrelation(size_t tau, buffer& s, size_t t = 0);
	
	double difference(size_t tau, buffer& s, size_t t = 0);

	
	void calculer_autocorrelation(buffer& s, buffer& resultat, size_t t = 0);
	
	void calculer_difference(buffer& s, buffer& resultat, size_t t = 0);
	
	void calculer_cmndf(buffer& s, buffer& resultat, size_t t = 0);
	
	size_t indice_premier_pic(const buffer& valeurs, size_t pas = 1, size_t debut = 0, double seuil = 0);
	
	size_t indice_premier_zero(const buffer& valeurs, double seuil = 0);
}

#endif /* end of include guard: ESTIMATION_HAUTEUR_H_K9RXGQ0N */
