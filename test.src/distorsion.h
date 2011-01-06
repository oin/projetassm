#if !defined(DISTORSION_H_9BYEBXJJ)
#define DISTORSION_H_9BYEBXJJ

#include <effet.h>
#include <son.h>

struct distorsion : public effet {
	distorsion(assm::son& s, double g = 1.0) : effet(s), gain_(g) {}
	double gain() const { return gain_; }
	void gain(double g) { gain_ = g; }
	size_t allongement() const { return 0; }
	virtual void operator()();
private:
	double gain_;
};

#endif /* end of include guard: DISTORSION_H_9BYEBXJJ */
