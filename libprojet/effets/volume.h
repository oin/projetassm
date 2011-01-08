#if !defined(VOLUME_H_1R2ZU1X6)
#define VOLUME_H_1R2ZU1X6

#include "effet.h"

struct volume : public effet {
	volume(chaine_effets& c, double g = 1.0) : effet(c), gain_(g) {}
	double gain() const { return gain_; }
	void gain(double g) { gain_ = g; }
	virtual void operator()();
private:
	double gain_;
};

#endif /* end of include guard: VOLUME_H_1R2ZU1X6 */
