#if !defined(NORMALISATION_H_9BYEBXVV)
#define NORMALISATION_H_9BYEBXVV

#include <effet.h>

struct normalisation : public effet {
	normalisation(chaine_effets& s) : effet(s) {}
	virtual void operator()();
};

#endif
