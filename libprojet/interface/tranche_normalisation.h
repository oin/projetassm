#if !defined(TRANCHE_NORMALISATION_H_I2MIG2KC)
#define TRANCHE_NORMALISATION_H_I2MIG2KC

#include "tranche_effet.h"

struct tranche_normalisation : public tranche_effet {
	tranche_normalisation(controleur&, effet*, int);
	~tranche_normalisation() {}
};

#endif /* end of include guard: TRANCHE_NORMALISATION_H_I2MIG2KC */
