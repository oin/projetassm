#if !defined(EFFET_H_40COJBYD)
#define EFFET_H_40COJBYD

#include <son.h>

struct effet {
	effet(assm::son& s) : s_(s), dry_(0.0), debut_(0.0), fin_(1.0) {}
	virtual ~effet() {}
	virtual size_t allongement() const = 0;
	virtual void operator()() = 0; // appliquer
	
	void dry(double);
	void wet(double);
	double dry() const;
	double wet() const;
	
	void cible(assm::son&);
	assm::son& cible();
	
	void debut(double);
	void fin(double);
	double debut() const;
	double fin() const;
	size_t echantillon_debut() const;
	size_t echantillon_fin() const;
	void limites(double d, double f);
protected:
	void allonger();
private:
	assm::son& s_;
	double dry_;
	double debut_, fin_;
};

#endif /* end of include guard: EFFET_H_40COJBYD */
