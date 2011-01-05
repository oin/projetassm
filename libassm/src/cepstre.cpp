#include "cepstre.h"
#include "fft.h"
#include <algorithm>
#include <cmath>
#include "multiplicateurs.h"

namespace assm {
	
	cepstre::cepstre(spectre& s) : cepstre_(s.size(), s.rate()) {
		// Ne copie que |s|
		son ce_bordoule(s.data(), s.rate());
		spectre ce_bordel(ce_bordoule);
		// Prépare la ffti de ce bordel
		ffti ma_ffti(ce_bordel);
		// Copie le résultat dans cepstre_
		ma_ffti();
		std::copy(ma_ffti.out().data().begin(), ma_ffti.out().data().end(), cepstre_.data().begin());
	}
	
}