#if !defined(DFT_MAISON_H_YGUMOCMP)
#define DFT_MAISON_H_YGUMOCMP

#include "son.h"
#include "spectre.h"

namespace assm {

void dft_maison(son& in, spectre& out);
void dft_maison_amplitude(buffer& in, buffer& out);

}

#endif /* end of include guard: DFT_MAISON_H_YGUMOCMP */
