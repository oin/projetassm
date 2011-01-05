#include "generateur.h"

namespace assm {

void append_sinus(double frequence, double temps_ms, son& son) {
	append(sinusoide(frequence, son.rate()), temps_ms, son);
}

}