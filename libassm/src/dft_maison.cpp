#include "dft_maison.h"
#include <complex>
#include <iostream>
namespace assm
{

void dft_maison(son& in, spectre& out) {
	std::vector<std::complex<double> > temp(in.size());
	for(unsigned int m = 0; m < out.size(); ++m) {
		temp[m] = 0;
		for(unsigned int n = 0; n < out.size(); ++n)
			temp[m] += std::polar(in.data()[n], -2*n*m*3.14159265/out.size());
		temp[m] /= in.size() / 2;
		out.data()[m] = std::abs(temp[m]);
		out.phase()[m] = std::arg(temp[m]);
	}
}

void dft_maison_amplitude(buffer& in, buffer& out) {
	std::vector<std::complex<double> > temp(in.size());
	for(unsigned int m = 0; m < out.size(); ++m) {
		temp[m] = 0;
		for(unsigned int n = 0; n < out.size(); ++n)
			temp[m] += std::polar(in.data()[n], -2*n*m*3.14159265/out.size());
		temp[m] /= in.size() / 2;
		out[m] = std::abs(temp[m]);
	}
}

} /* assm */