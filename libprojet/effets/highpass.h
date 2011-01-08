#if !defined(HIGHPASS_H_9BYEBXVV)
#define HIGHPASS_H_9BYEBXVV

#include <effet.h>

struct highpass : public effet {
	highpass(chaine_effets& s, double f = 100) : effet(s), freq_(f) {}
	double freq() const { return freq_; }
	void freq(double f) { freq_ = f; }
	virtual void operator()();
private:
	double freq_;	
};

#endif
