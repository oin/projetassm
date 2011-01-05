#if !defined(ANALYSE_NOTES_H_RPACVZV8)
#define ANALYSE_NOTES_H_RPACVZV8

#include <algorithm>
#include "buffer.h"
#include "spectre.h"
#include "son.h"
#include "sommateurs.h"

namespace assm {

	template <class T>
	double energie(T d, T f) {
		return std::for_each(d, f, sommateur_de_carre()).somme();
	}
	
	template <class T>
	double hfc(T d, T f) {
		return std::for_each(d, f, sommateur_de_carre_pondere()).somme();
	}

	double spectral_flux(spectre& trame, spectre& trame_prec);
	
	// Il est parfois nécessaire de récupérer les énergies, les HFC et tout le tintouin et mildiou
	struct calculateur_energies {
		calculateur_energies(son& s, size_t taille_trame);
		buffer& operator()() { return buf_; }
	private:
		buffer buf_;
	};
	struct calculateur_energies_moyennes {
		calculateur_energies_moyennes(son& s, size_t nb_trames_precedentes, size_t taille_trame);
		buffer& operator()() { return buf_; }
	private:
		buffer buf_;
	};
	struct calculateur_hfcs {
		calculateur_hfcs(son& s, size_t taille_trame);
		buffer& operator()() { return buf_; }
	private:
		buffer buf_;
	};
	struct calculateur_variations_hfcs {
		calculateur_variations_hfcs(son& s, size_t taille_trame);
		buffer& operator()() { return buf_; }
	private:
		buffer buf_;
	};
	struct calculateur_flux_spectraux {
		calculateur_flux_spectraux(son& s, size_t taille_trame);
		buffer& operator()() { return buf_; }
	private:
		buffer buf_;
	};


	// Ce détecteur de débuts de notes permet, grâce à operator(), de renvoyer le résultat de la détection : un tableau où chaque élément indique l'indice d'un début de note
	struct detecteur_debuts_notes {
		virtual ~detecteur_debuts_notes() {}
		virtual std::vector<size_t>& operator()() = 0;
	};
	
	// On utilise ceci lorsqu'on a un tableau d'informations (HFC, énergie...) relatives chacune à un ou plusieurs échantillons (d'où la présence du multiplicateur).
	struct detecteur_debuts_notes_seuil {
		detecteur_debuts_notes_seuil(buffer& information, double seuil, size_t multiplicateur);
		virtual ~detecteur_debuts_notes_seuil() {}
		virtual std::vector<size_t>& operator()() { return debuts_notes_; }
	private:
		std::vector<size_t> debuts_notes_;
	};
}

#endif /* end of include guard: ANALYSE_NOTES_H_RPACVZV8 */
