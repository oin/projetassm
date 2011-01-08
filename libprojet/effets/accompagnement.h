#if !defined(ACCOMPAGNEMENT_H_ML7CM511)
#define ACCOMPAGNEMENT_H_ML7CM511

#include "effet.h"

struct accompagnement : public effet {
	accompagnement(chaine_effets& s) : effet(s), intolerance_(10) {}
	virtual void operator()();
	void intolerance(double i) { intolerance_ = static_cast<int>(i); }
	int intolerance() { return intolerance_; }
private:
	int intolerance_;
};

#endif /* end of include guard: ACCOMPAGNEMENT_H_ML7CM511 */
