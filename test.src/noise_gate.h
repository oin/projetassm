#if !defined(NOISE_GATE_H_9BYEBXEE)
#define NOISE_GATE_H_9BYEBXEE

#include <effet.h>
#include <son.h>

struct noise_gate : public effet {
	noise_gate(chaine_effets& s, double l = 0.1) : effet(s), limit_(l) {}
	double limit() const { return limit_; }
	void limit(double g) { limit_ = g; }
	size_t allongement() { return 0; }
	virtual void operator()();
private:
	double limit_;
};

#endif /* end of include guard: DISTORSION_H_9BYEBXJJ */
