#if !defined(CHUCHOTEMENT_H_9BYEBXEE)
#define CHUCHOTEMENT_H_9BYEBXEE

#include <effet.h>
#include <son.h>
#include <assm.h>
#include <iterator_part.hpp>

struct chuchotement : public effet {
	chuchotement(chaine_effets& s) : effet(s){}
	size_t allongement() { return 0; }
	virtual void operator()();
};

#endif
