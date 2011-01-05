#include "tracer.h"
extern "C" {
	#include "gnuplot_i.h"
}
#include "unites.h"
#include <sstream>
#include <cmath>

namespace assm
{

struct gnuplot_ctrl_hdl {
	gnuplot_ctrl *handle;
};

traceur::traceur() : handle_(new gnuplot_ctrl_hdl) {
	handle_->handle = gnuplot_init();
	gnuplot_setstyle(handle_->handle, (char*)"lines");
}

traceur::~traceur() {
	gnuplot_close(handle_->handle);
	delete handle_;
}

void traceur::reset() {
	// Efface les lignes
	commande("unset arrow");
	// Fait un reset
	gnuplot_resetplot(handle_->handle);
}

void traceur::tracer(son& s, std::string t, bool amplitude, bool fixed_range) {
	std::vector<double> echelle(s.size());
	std::vector<double> data(s.data().begin(), s.data().end());
	
	for(size_t i = 0; i < echelle.size(); ++i)
		echelle[i] = s.temps(i);
	
	if(fixed_range)
		x_range(0, s.duree());
	gnuplot_set_xlabel(handle_->handle, (char*)"temps (s)");
	
	if(amplitude) {
		std::transform(data.begin(), data.end(), data.begin(), to_amplitude_from_volume);
		gnuplot_set_ylabel(handle_->handle, (char*)"amplitude (dB)");
	}
	else {
		gnuplot_set_ylabel(handle_->handle, (char*)"volume");
		if(fixed_range)
			y_range(-1, 1);
	}
	
	gnuplot_plot_xy(handle_->handle, &(echelle[0]), &(data[0]), data.size(), (char*)t.c_str());
}

void traceur::tracer(spectre& s, std::string t, bool amplitude, bool bark, bool fixed_range/*, bool logscale*/) {
	std::vector<double> echelle(s.size());
	std::vector<double> data(s.data().begin(), s.data().end());
	
	for(size_t i = 0; i < echelle.size(); ++i)
		echelle[i] = i * 1.0 * s.rate() / echelle.size();
	
	if(bark) {
		gnuplot_set_xlabel(handle_->handle, (char*)"plage (Bark)");
		if(fixed_range)
			x_range(0, to_bark_from_frequence(s.rate() / 2));
		std::transform(echelle.begin(), echelle.end(), echelle.begin(), to_bark_from_frequence);
	} else {
		gnuplot_set_xlabel(handle_->handle, (char*)"fréquence (Hz)");
		if(fixed_range)
			x_range(0.1, s.rate() / 2);
		//if(logscale) commande("set logscale y");
	}
	
	if(amplitude) {
		std::transform(data.begin(), data.end(), data.begin(), to_amplitude_from_volume);
		gnuplot_set_ylabel(handle_->handle, (char*)"amplitude (dB)");
		if(fixed_range)
			y_range(-20, 120);
	}
	else {
		gnuplot_set_ylabel(handle_->handle, (char*)"volume");
		// if(fixed_range)
		// 			y_range(0, 1);
	}

	gnuplot_plot_xy(handle_->handle, &(echelle[0]), &(data[0]), data.size(), (char*)t.c_str());
}

void traceur::x_range(double x0, double x1) {
	std::ostringstream cmd;
	cmd << "set xrange [" << x0 << ":" << x1 << "]";
	commande(cmd.str());
}

void traceur::y_range(double y0, double y1) {
	std::ostringstream cmd;
	cmd << "set yrange [" << y0 << ":" << y1 << "]";
	commande(cmd.str());
}

void traceur::commande(std::string s) {
	gnuplot_cmd(handle_->handle, const_cast<char*>(s.c_str()));
}

void traceur::tracer(buffer& v, std::string t) {
	gnuplot_plot_x(handle_->handle, &(v[0]), v.size(), (char*)t.c_str());
}

void traceur::tracer(buffer& v, buffer& v2, std::string t) {
	gnuplot_plot_xy(handle_->handle, &(v[0]), &(v2[0]), v.size(), (char*)t.c_str());
}

void traceur::tracer(std::vector<std::string>& v, std::vector<double>& v2, std::string t) {
	char **tab = new char*[v.size()];
	for(size_t i=0; i<v.size(); ++i)
		tab[i] = (char*)(v[i]).c_str();
	
	gnuplot_plot_str_x(handle_->handle, &(v2[0]), &(tab[0]), v.size(), (char*)t.c_str());
	delete[] tab;
}

void traceur::style(std::string s) {
	gnuplot_setstyle(handle_->handle, (char*)s.c_str());
}

void traceur::x_label(std::string s) {
	gnuplot_set_xlabel(handle_->handle, (char*)s.c_str());
}

void traceur::y_label(std::string s) {
	gnuplot_set_ylabel(handle_->handle, (char*)s.c_str());
}

void traceur::ligne_verticale(double x0, double y0, double y1) {
	std::ostringstream oss;
	oss << "set arrow from " << x0 << "," << y0 << " to " << x0 << "," << y1 << " nohead lw 0.7 lc rgb \"blue\"" << std::endl;
	commande(oss.str());
}

} /* assm */