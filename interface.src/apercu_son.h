#if !defined(APERCU_SON_H_KNSHXPES)
#define APERCU_SON_H_KNSHXPES

#include <son.h>
#include <vector>

struct apercu_son {
	apercu_son() : s_(son_vide_), apercu_(nb_points_) {
		reconstruire();
	}
	
	apercu_son(assm::son& s) : s_(s), apercu_(nb_points_) {
		reconstruire();
	}
	
	virtual ~apercu_son() {}
	
	virtual void reconstruire();
	std::vector<double>& operator()() { return apercu_; }
	size_t size() const { return apercu_.size(); }
	size_t real_size() const { return s_.size(); }
	size_t pas() const { return pas_; }
	enum { nb_points_ = 512 };
private:
	assm::son& s_;
	size_t pas_;
	std::vector<double> apercu_;
	static assm::son son_vide_;
};

#endif /* end of include guard: APERCU_SON_H_KNSHXPES */
