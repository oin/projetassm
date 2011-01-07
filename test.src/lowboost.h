#if !defined(LOWBOOST_H_9BYEBXVV)
#define LOWBOOST_H_9BYEBXVV

#include <effet.h>
#include <son.h>
#include <assm.h>
#include <iterator_part.hpp>


struct lowboost : public effet {
	lowboost(chaine_effets& s) : effet(s) {}
	virtual void operator()();
};

#endif
