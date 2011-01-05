#include "analyse_notes.h"

#include "iterator_part.hpp"
#include "fft.h"
#include <queue>

namespace assm {
	
	calculateur_energies::calculateur_energies(son& s, size_t taille_trame) {
		son fenetre(taille_trame, s.rate());
		fft ma_fft(fenetre);
		buffer::iterator it = s.begin(), ite = s.end();
		for(; it != ite;) {
			std::copy(iterator_parter(it, fenetre.size()), iterator_parter(ite), fenetre.begin());
			ma_fft();
			buf_.push_back(energie(ma_fft.out().data().begin(), ma_fft.out().data().end()));
		}
	}
	
	calculateur_energies_moyennes::calculateur_energies_moyennes(son& s, size_t nb_trames_precedentes, size_t taille_trame) {
		std::queue<double> trames_precedentes;
		double somme_precedente = 0;
		son fenetre(taille_trame, s.rate());
		fft ma_fft(fenetre);
		buffer::iterator it = s.begin(), ite = s.end();
		for(; it != ite;) {
			std::copy(iterator_parter(it, fenetre.size()), iterator_parter(ite), fenetre.begin());
			ma_fft();
			
			double nrj = energie(ma_fft.out().data().begin(), ma_fft.out().data().end());
			
			if(trames_precedentes.size() == nb_trames_precedentes) {
				double nrjmoyenne = nrj / (1.0 / nb_trames_precedentes * somme_precedente);
				somme_precedente -= trames_precedentes.front();
				trames_precedentes.pop();
				buf_.push_back(nrjmoyenne);
			} else {
				buf_.push_back(0);
			}
			somme_precedente += nrj;
			trames_precedentes.push(nrj);
		}
	}
	
	calculateur_hfcs::calculateur_hfcs(son& s, size_t taille_trame) {
		son fenetre(taille_trame, s.rate());
		fft ma_fft(fenetre);
		buffer::iterator it = s.begin(), ite = s.end();
		for(; it != ite;) {
			std::copy(iterator_parter(it, fenetre.size()), iterator_parter(ite), fenetre.begin());
			ma_fft();
			buf_.push_back(hfc(ma_fft.out().data().begin(), ma_fft.out().data().end()));
		}
	}
	
	calculateur_variations_hfcs::calculateur_variations_hfcs(son& s, size_t taille_trame) {
		son fenetre(taille_trame, s.rate());
		fft ma_fft(fenetre);
		buffer::iterator it = s.begin(), ite = s.end();
		double hfc_avant = 0;
		for(; it != ite;) {
			std::copy(iterator_parter(it, fenetre.size()), iterator_parter(ite), fenetre.begin());
			ma_fft();
			double nrj = energie(ma_fft.out().data().begin(), ma_fft.out().data().end());
			double hfc_ici = hfc(ma_fft.out().data().begin(), ma_fft.out().data().end());
			if(hfc_avant == 0 || nrj == 0)
				buf_.push_back(0);
			else
				buf_.push_back(hfc_ici * hfc_ici / (hfc_avant * nrj));
			hfc_avant = hfc_ici;
		}
	}
	
	calculateur_flux_spectraux::calculateur_flux_spectraux(son& s, size_t taille_trame) {
		son fenetre(taille_trame, s.rate());
		fft ma_fft(fenetre);
		spectre spectre_davant(taille_trame, s.rate());
		buffer::iterator it = s.begin(), ite = s.end();
		for(; it != ite;) {
			std::copy(iterator_parter(it, fenetre.size()), iterator_parter(ite), fenetre.begin());
			ma_fft();
			if(spectre_davant.size() != 0)
				buf_.push_back(spectral_flux(ma_fft.out(), spectre_davant));
			spectre_davant = ma_fft.out();
		}
	}
	
	// Flux spectral :
	
	double spectral_flux(spectre& trame, spectre& trame_prec) {
		double resultat = 0;
		for(size_t i=0; i<trame.size(); ++i) {
			double actuel = trame.data()[i] - trame_prec.data()[i];
			if(actuel > 0)
				resultat += actuel;
		}
		return resultat;
	}
	
	// Détecteur de débuts de notes avec seuil
	detecteur_debuts_notes_seuil::detecteur_debuts_notes_seuil(buffer& information, double seuil, size_t multiplicateur) {
		// Détection des débuts de notes
		for(size_t i=1; i < information.size(); ++i)
			// On évite de compter les trucs qui se suivent
			if(information[i] > seuil && information[i-1] <= seuil) {
				// Début de note
				debuts_notes_.push_back(i * multiplicateur);
			}
		}
}