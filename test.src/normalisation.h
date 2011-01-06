#if !defined(NORMALISATION_H_9BYEBXVV)
#define NORMALISATION_H_9BYEBXVV

#include <effet.h>
#include <son.h>

struct normalisation : public effet {
	normalisation(chaine_effets& s) : effet(s){}
	size_t allongement() const { return 0; }
	virtual void operator()();
};

#endif /* end of include guard: DISTORSION_H_9BYEBXJJ */
