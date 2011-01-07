#if !defined(TRANCHE_INVERSE_H_NR261POV)
#define TRANCHE_INVERSE_H_NR261POV

#include "tranche_effet.h"

struct tranche_inverse : public tranche_effet {
	tranche_inverse(controleur&, effet*, int);
	~tranche_inverse() {}
};

#endif /* end of include guard: TRANCHE_INVERSE_H_NR261POV */
