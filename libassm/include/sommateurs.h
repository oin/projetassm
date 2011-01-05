#if !defined(SOMMATEURS_H_THA04K7J)
#define SOMMATEURS_H_THA04K7J

class sommateur_de_carre {
	double somme_;
public:
	sommateur_de_carre() : somme_(0) {}
	void operator()(double v) { somme_ += v * v; }
	double somme() { return somme_; }
};

class sommateur_de_carre_pondere {
	double somme_;
	int i_;
public:
	sommateur_de_carre_pondere() : somme_(0), i_(0) {}
	void operator()(double v) { somme_ += v * v * i_++; }
	double somme() { return somme_; }
};

#endif /* end of include guard: SOMMATEURS_H_THA04K7J */
