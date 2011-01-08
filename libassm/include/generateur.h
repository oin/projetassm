#if !defined(GENERATEUR_H_3NR93IPB)
#define GENERATEUR_H_3NR93IPB

#include "son.h"
#include <cmath>
#include <ctime>
#include <algorithm>
#include <memory>

namespace assm {

template <class Gen>
void append(Gen g, double temps_ms, son& son) {
	std::generate_n(std::back_inserter(son.data()), static_cast<size_t>(std::floor(temps_ms * 1.0 / 1000 * son.rate())), g);
}

void append_sinus(double frequence, double temps_ms, son& son);

// Le Silence
struct silence {
	double operator()() { return 0; }
};

// Le Bordel Absolu
struct bruit_blanc {
	bruit_blanc() { srand(time(NULL)); }
	double operator()() { return ((rand() - RAND_MAX / 2.0) * 2.0 / RAND_MAX); }
};

#if !defined(M_PI)
#define M_PI 3.1415926
#endif

// Le Sinus
struct sinusoide {
	size_t	frame_actuelle_, // ne pas confondre avec Femme Actuelle
		sample_rate_;
	double frequence_;
	sinusoide(double frequence, size_t sample_rate) : frame_actuelle_(0), sample_rate_(sample_rate), frequence_(frequence) {}
	double operator()() { return sin(frame_actuelle_++ * 2 * M_PI * frequence_ / sample_rate_); }
};

}

#endif /* end of include guard: GENERATEUR_H_3NR93IPB */
