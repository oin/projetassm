#if !defined(CHAINE_EFFETS_H_LWTJ7TOI)
#define CHAINE_EFFETS_H_LWTJ7TOI

#include "effet.h"
#include <vector>

struct chaine_effets {
	chaine_effets(assm::son& s);
	virtual ~chaine_effets();
	virtual void operator()();
	std::vector<effet*>& effets();
	void cible(assm::son&);
	const assm::son& cible() const;
private:
	void mettre_a_jour_son();
	
	std::vector<effet*> effets_;
	assm::son& s_;
};

#endif /* end of include guard: CHAINE_EFFETS_H_LWTJ7TOI */
