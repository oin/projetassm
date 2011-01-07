#include "hsl2rgb.h"
#include <iostream>

// Adapté de easyrgb.com

double hue2rgb(double v1, double v2, double vH) {
	if(vH < 0) vH += 1;
	if(vH > 1) vH -= 1;
	if(6 * vH < 1) return (v1 + (v2-v1)* 6 * vH);
	if(2 * vH < 1) return v2;
	if(3 * vH < 2) return (v1 + (v2-v1)* (2.0/3 - vH) * 6);
	return v1;
}

Gdk::Color couleur_hsl(double h, double s, double l) {
	double r, g, b, v2, v1;
	if(s == 0) {
		r = l;
		g = l;
		b = l;
	} else {
		if(l < 0.5)
			v2 = l * (1+s);
		else
			v2 = l + s - s * l;
		
		v1 = 2*l - v2;
		
		r = hue2rgb(v1, v2, h + 1.0/3);
		g = hue2rgb(v1, v2, h);
		b = hue2rgb(v1, v2, h - 1.0/3);
	}
	
	Gdk::Color ret;
	ret.set_rgb_p(r, g, b);
	
	return ret;
}