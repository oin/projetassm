#include "estimation_hauteur.h"
#include <algorithm>
#include <iostream>
namespace assm {
	
	double autocorrelation(size_t tau, buffer& s, size_t t) {
		double gamma = 0;
		for(size_t n=t; n < t + s.size() - tau; ++n)
			gamma += s[n] * s[n + tau];
		return gamma / s.size();
	}
	
	double difference(size_t tau, buffer& s, size_t t) {
		double gamma = 0;
		for(size_t n=t; n < t + s.size() - tau; ++n)
			gamma += pow(s[n] - s[n + tau], 2);
		return gamma;
	}
		
	void calculer_autocorrelation(buffer& s, buffer& resultat, size_t t) {
		for(size_t tau=0; tau<s.size(); ++tau)
			resultat.push_back(autocorrelation(tau, s, t));
	}

	size_t indice_premier_pic(const buffer& valeurs, size_t pas, size_t debut, double seuil) {
		// On cherche à partir de quand ça ne monte plus
		for(; debut < valeurs.size() - pas && valeurs[debut] > valeurs[debut + pas]; debut += pas);
		// On cherche le pic ici
		for(; debut < valeurs.size() - pas && (valeurs[debut] <= valeurs[debut + pas] || valeurs[debut] < seuil); debut += pas);
		// On devrait être au pic
		// Si le pas est supérieur à 1, on doit chercher le maximum local
		if(pas > 1) {
			pas /= 2;
			size_t borne_inf = std::max(0, static_cast<int>(debut) - static_cast<int>(pas));
			size_t borne_sup = std::min(debut + pas, valeurs.size());
			return std::distance(valeurs.begin(), std::max_element(valeurs.begin() + borne_inf, valeurs.begin() + borne_sup));
		}
		return debut;
	}
	
	void calculer_difference(buffer& s, buffer& resultat, size_t t) {
		for(size_t tau=0; tau<s.size(); ++tau) {
			double gamma = 0;
			for(size_t n=t; n < t + s.size() - tau; ++n)
				gamma += pow(s[n] - s[n + tau], 2);
			resultat.push_back(gamma);
		}
	}
	
	void calculer_cmndf(buffer& s, buffer& resultat, size_t t) {
		double somme_des_differences = 0;
		resultat.push_back(1);
		for(size_t tau=1; tau<s.size(); ++tau) {
			double diff = difference(tau, s, t);
			double gamma = diff;
			somme_des_differences += diff;
			gamma /= (1.0 / tau) * somme_des_differences;
			resultat.push_back(gamma);
		}
	}
	
	size_t indice_premier_zero(const buffer& valeurs, double seuil) {
		for(size_t i=0; i < valeurs.size(); ++i) {
			if(valeurs[i] <= seuil)
				return i;
		}
		return 0;
	}
}