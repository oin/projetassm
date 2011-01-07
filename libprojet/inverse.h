#if !defined(INVERSE_H_9BYEBXVV)
#define INVERSE_H_9BYEBXVV

#include "effet.h"
#include <son.h>

struct inverse : public effet {
	inverse(chaine_effets& s) : effet(s) {}
	virtual void operator()();
};

#endif
