#include "fft.h"
#include <fftw3.h>

namespace assm {

struct fftw_plan_hdl {
	fftw_plan plan;
};

fft::fft(son& in) :
	in_(in),
	intermediaire_(in.size()),
	out_(in.size(), in.rate()),
	plan_(new fftw_plan_hdl)
{
	plan_->plan = fftw_plan_dft_r2c_1d(in.size(), &(in.data()[0]), reinterpret_cast<fftw_complex*>(&(intermediaire_[0])), FFTW_ESTIMATE);
}
	
fft::~fft() {
	fftw_destroy_plan(plan_->plan);
	delete plan_;
}

spectre& fft::operator()(bool rescale) {
	fftw_execute(plan_->plan);
	
	if(rescale)
	for(std::vector<std::complex<double> >::iterator it = intermediaire_.begin(); it != intermediaire_.end(); ++it)
		*it /= rescale_factor();
	
	out_.from_complex(intermediaire_);
	return out_;
}




ffti::ffti(spectre& in) :
	in_(in),
	intermediaire_(in.size()),
	out_(in.size(), in.rate()),
	plan_(new fftw_plan_hdl)
{
	plan_->plan = fftw_plan_dft_c2r_1d(in.size(), reinterpret_cast<fftw_complex*>(&(intermediaire_[0])), &(out_.data()[0]), FFTW_ESTIMATE);
}
	
ffti::~ffti() {
	fftw_destroy_plan(plan_->plan);
	delete plan_;
}

son& ffti::operator()() {
	std::transform(in_.data().begin(), in_.data().end(), in_.phase().begin(), intermediaire_.begin(), std::polar<double>);
	fftw_execute(plan_->plan);
	return out_;
}

}