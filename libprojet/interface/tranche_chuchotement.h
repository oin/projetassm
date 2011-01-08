#if !defined(TRANCHE_CHUCHOTEMENT_H_N7AVJ33N)
#define TRANCHE_CHUCHOTEMENT_H_N7AVJ33N

#include "tranche_effet.h"

struct tranche_chuchotement : public tranche_effet {
	tranche_chuchotement(controleur&, effet*, int);
	~tranche_chuchotement() {}
};

#endif /* end of include guard: TRANCHE_CHUCHOTEMENT_H_N7AVJ33N */
