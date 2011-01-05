#if !defined(ENVELOPPE_SPECTRALE_H_CKAXA6IL)
#define ENVELOPPE_SPECTRALE_H_CKAXA6IL

#include "spectre.h"

namespace assm {
	struct enveloppe_spectrale {
		enveloppe_spectrale(spectre& s, size_t ordre);
		spectre& operator()() { return enveloppe_spectrale_; }
		spectre& origine_log() { return spectre_log_; }
	private:
		spectre enveloppe_spectrale_;
		spectre spectre_log_;
	};
}

#endif /* end of include guard: ENVELOPPE_SPECTRALE_H_CKAXA6IL */
