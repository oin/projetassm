#if !defined(CHAINE_EFFETS_H_LWTJ7TOI)
#define CHAINE_EFFETS_H_LWTJ7TOI

#include <vector>
#include <son.h>

class effet;

struct chaine_effets {
	chaine_effets(assm::son& s);
	virtual ~chaine_effets();
	virtual void operator()();
	std::vector<effet*>& effets();
	void in(assm::son&);
	assm::son& in();
	assm::son& out();
private:
	void mettre_a_jour_son();
	
	std::vector<effet*> effets_;
	assm::son& s_;
	assm::son s_tmp1_, s_tmp2_;
};

#endif /* end of include guard: CHAINE_EFFETS_H_LWTJ7TOI */
