#if !defined(DELAY_H_9BYEVXJJ)
#define DELAY_H_9BYEVXJJ

#include <effet.h>
#include <son.h>

struct delay : public effet {
	delay(chaine_effets& c, double t = 1.0) : effet(c), time_(t) {}
	double time() const { return time_; }
	void time(double t) { time_ = t; }
	double feedback() const { return feedback_; }
	void feedback(double t) { feedback_ = t; }
	size_t allongement() const { return 0; }
	virtual void operator()();
private:
	double time_;
	double feedback_;
};

#endif /* end of include guard: DISTORSION_H_9BYEBXJJ */
