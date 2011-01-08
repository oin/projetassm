#if !defined(TRANCHE_BASSBOOST_H_HNR51UH3)
#define TRANCHE_BASSBOOST_H_HNR51UH3

#include "tranche_effet.h"

struct tranche_bassboost : public tranche_effet {
	tranche_bassboost(controleur&, effet*, int);
	~tranche_bassboost() {}
};

#endif /* end of include guard: TRANCHE_BASSBOOST_H_HNR51UH3 */
