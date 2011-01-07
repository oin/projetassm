#if !defined(EFFET_H_40COJBYD)
#define EFFET_H_40COJBYD

#include <son.h>
#include "chaine_effets.h"

struct effet {
	effet(chaine_effets& c) : s_(0), s_out_(0), dry_(0.0), debut_(0.0), fin_(1.0) {}
	virtual ~effet() {}
	virtual void operator()() = 0; // appliquer
	
	void dry(double);
	void wet(double);
	double dry() const;
	double wet() const;
	
	void in(assm::son&);
	assm::son& in();
	
	void out(assm::son&);
	assm::son& out();
	
	void debut(double);
	void fin(double);
	double debut() const;
	double fin() const;
	size_t echantillon_debut();
	size_t echantillon_fin();
	void limites(double d, double f);
protected:
	void mixer_drywet();
private:
	assm::son* s_;
	assm::son* s_out_;
	double dry_;
	double debut_, fin_;
};

#endif /* end of include guard: EFFET_H_40COJBYD */
