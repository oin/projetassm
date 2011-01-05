#if !defined(TRACER_H_IW28C09T)
#define TRACER_H_IW28C09T

#include "buffer.h"
#include "spectre.h"
#include "son.h"
#include <string>

namespace assm
{

struct gnuplot_ctrl_hdl;

struct traceur {
	traceur();
	virtual ~traceur();
	void reset();
	void tracer(son&, std::string t = "", bool amplitude = false, bool fixed_range = true);
	void tracer(spectre&, std::string t = "", bool amplitude = false, bool bark = false, bool fixed_range = true/*, bool logscale = false*/);
	void tracer(buffer& v, std::string t = "");
	void tracer(buffer& v, buffer& v2, std::string t = "");
	void tracer(std::vector<std::string>& v, std::vector<double>& v2, std::string t = "");
	void x_range(double, double);
	void y_range(double, double);
	void x_label(std::string);
	void y_label(std::string);
	void commande(std::string);
	void style(std::string);
	void ligne_verticale(double x0, double y0 = -1.0, double y1 = 1.0);
private:
	gnuplot_ctrl_hdl *handle_;
};

} /* assm */

#endif /* end of include guard: TRACER_H_IW28C09T */
