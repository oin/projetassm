#if !defined(INVERSE_H_9BYEBXVV)
#define INVERSE_H_9BYEBXVV

#include <effet.h>
#include <son.h>

struct inverse : public effet {
	inverse(chaine_effets& s) : effet(s){}
	size_t allongement() { return 0; }
	virtual void operator()();
};

#endif
