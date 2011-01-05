#if !defined(MULTIPLICATEURS_H_TRVTE2BP)
#define MULTIPLICATEURS_H_TRVTE2BP

template <class T>
struct multiplier_par {
	multiplier_par(T v) : valeur_(v) {}
	T operator()(T x) { return x*valeur_; }
private:
	T valeur_;
};

#endif /* end of include guard: MULTIPLICATEURS_H_TRVTE2BP */
