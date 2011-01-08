#if !defined(CHUCHOTEMENT_H_9BYEBXEE)
#define CHUCHOTEMENT_H_9BYEBXEE

#include "effet.h"

struct chuchotement : public effet {
	chuchotement(chaine_effets& s) : effet(s){}
	virtual void operator()();
};

#endif
