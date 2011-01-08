#if !defined(LOWBOOST_H_9BYEBXVV)
#define LOWBOOST_H_9BYEBXVV

#include <effet.h>

struct lowboost : public effet {
	lowboost(chaine_effets& s) : effet(s) {}
	virtual void operator()();
};

#endif
