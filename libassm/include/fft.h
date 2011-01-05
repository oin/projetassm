#if !defined(FFT_H_AQZA6MGV)
#define FFT_H_AQZA6MGV

#include "son.h"
#include "spectre.h"
#include <vector>
#include <complex>

namespace assm {

struct fftw_plan_hdl;

struct fft {
	fft(son&);
	virtual ~fft();
	spectre& out() { return out_; }
	std::vector<std::complex<double> >& out_complex() { return intermediaire_; }
	spectre& operator()(bool rescale = true);
	double rescale_factor() { return intermediaire_.size() /** 1.0 / 2*/; }
private:
	son& in_;
	std::vector<std::complex<double> > intermediaire_;
	spectre out_;
	fftw_plan_hdl *plan_;
}; 


struct ffti {
	ffti(spectre&);
	// ffti(son&);
	virtual ~ffti();
	son& out() { return out_; }
	son& operator()();
private:
	spectre& in_;
	std::vector<std::complex<double> > intermediaire_;
	son out_;
	fftw_plan_hdl *plan_;
};

}

#endif /* end of include guard: FFT_H_AQZA6MGV */
