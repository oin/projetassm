#if !defined(VYNIL_H_9BYEBXEE)
#define VYNIL_H_9BYEBXEE

#include <effet.h>

struct vinyl : public effet {
	vinyl(chaine_effets& s) : effet(s), limit_(0.02), clics_(1) {}
	double souffle() const { return limit_; }
	void souffle(double g) { limit_ = g; }
	double clics() { return clics_; }
	void clics(double c) { clics_ = c; }
	virtual void operator()();
private:
	double limit_;
	double clics_;
};

#endif
