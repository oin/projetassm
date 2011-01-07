#if !defined(ROBOTISATION_H_9BYEBXEE)
#define ROBOTISATION_H_9BYEBXEE

#include <effet.h>
#include <son.h>
#include <assm.h>
#include <iterator_part.hpp>

struct robotisation : public effet {
	robotisation(chaine_effets& s) : effet(s){}
	size_t allongement() { return 0; }
	virtual void operator()();
};

#endif
