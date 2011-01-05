#if !defined(SEUILLEUR_H_R7LXTDVU)
#define SEUILLEUR_H_R7LXTDVU

namespace assm {
	template <class T, class T2>
	struct seuil {
		seuil(T seuil, T2 zero) : seuil_(seuil), zero_(zero) {}
		T2 operator()(T valeur) {
			return valeur > seuil_ ? static_cast<T2>(valeur) : zero_;
		}
	private:
		T seuil_;
		T2 zero_;
	};
	
	template <class T, class T2>
	seuil<T,T2> seuilleur(T s, T2 z) {
		return seuil<T,T2>(s, z);
	}
	
	template <class T>
	seuil<T,T> seuilleur(T s) {
		return seuil<T,T>(s, 0);
	}
	
	/*
	Facile d'utilisation, propre et sans danger pour les enfants :
		std::transform(tableau.begin(), tableau.end(), seuilleur(5, 0));
		
	Faites des seuils complexes en famille, ou entre amis :
		std::transform(tableau.begin(), tableau.end(), std::back_inserter(tableau_de_bool), seuilleur(5, false));
	*/
}

#endif /* end of include guard: SEUILLEUR_H_R7LXTDVU */
