#if !defined(CHROMA_H_RK7F1PGZ)
#define CHROMA_H_RK7F1PGZ

#include <assm.h>
#include <vector>

namespace imcc {

struct pitch_class_profile {
	pitch_class_profile(int nb_chromas = 12, double frequence_ref = 262) : chromas_(nb_chromas), pcp_(chromas_), frequence_ref_(frequence_ref) {}
	~pitch_class_profile() {}	
	void operator()(const assm::spectre& s);
	std::vector<double>& pcp() { return pcp_; }
	int size() { return chromas_; }
private:	
	int chromas_;
	std::vector<double> pcp_;
	double frequence_ref_;
};

}

#endif /* end of include guard: CHROMA_H_RK7F1PGZ */
