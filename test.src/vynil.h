#if !defined(VYNIL_H_9BYEBXEE)
#define VYNIL_H_9BYEBXEE

#include <effet.h>
#include <son.h>
#include <assm.h>
#include <iterator_part.hpp>

struct vynil : public effet {
	vynil(chaine_effets& s, double l = 0.1) : effet(s), limit_(l) {}
	double limit() const { return limit_; }
	void limit(double g) { limit_ = g; }
	size_t allongement() { return 0; }
	virtual void operator()();
private:
	double limit_;
};

#endif
