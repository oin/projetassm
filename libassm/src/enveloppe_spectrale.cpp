#include "enveloppe_spectrale.h"
#include "filtres.h"
#include "cepstre.h"
#include "fft.h"
#include <cmath>

double partie_reelle(std::complex<double> c) {
	return c.real();
}

namespace assm {
	enveloppe_spectrale::enveloppe_spectrale(spectre& s, size_t ordre) : enveloppe_spectrale_(s.size(), s.rate()), spectre_log_(s.size(), s.rate()) {
		// Passe le spectre en échelle log
		std::transform(s.data().begin(), s.data().end(), spectre_log_.data().begin(), log);
		
		// Fait un cepstre
		cepstre kepstr(spectre_log_);
		
		// Filtre le cepstre
		std::transform(kepstr().begin(), kepstr().end(), kepstr().begin(), filtrage_passe_bas(s.size(), ordre));
		
		// Fait la FFT du cepstre
		fft fft_du_cepstre(kepstr.as_son());
		fft_du_cepstre(false);
		
		// Prend la partie réelle de la FFT du cepstre
		std::transform(fft_du_cepstre.out_complex().begin(), fft_du_cepstre.out_complex().end(), enveloppe_spectrale_.data().begin(), partie_reelle);
		
		// Divise par N
		for(size_t i=0; i<enveloppe_spectrale_.size(); ++i) {
			enveloppe_spectrale_.data()[i] /= enveloppe_spectrale_.size();
		}
	}
}