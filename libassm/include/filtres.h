#if !defined(FILTRES_H_QGIFFI09)
#define FILTRES_H_QGIFFI09

namespace assm {
	
	struct filtrage_passe_bas {
		filtrage_passe_bas(unsigned int taille, unsigned int ordre);
		double operator()(double valeur);
	private:
		unsigned int taille_, ordre_, n_;
	};
	
}

#endif /* end of include guard: FILTRES_H_QGIFFI09 */
