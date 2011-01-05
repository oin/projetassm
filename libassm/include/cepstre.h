#if !defined(CEPSTRE_H_UIVG5JTZ)
#define CEPSTRE_H_UIVG5JTZ

#include "buffer.h"
#include "son.h"
#include "spectre.h"

namespace assm {
	
	struct cepstre {
		cepstre(spectre& s);
		buffer& operator()() { return cepstre_.data(); }
		son& as_son() { return cepstre_; }
	private:
		son cepstre_;
	};
	
}

#endif /* end of include guard: CEPSTRE_H_UIVG5JTZ */
