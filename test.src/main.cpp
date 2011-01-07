#include "distorsion.h"
#include "delay.h"
#include "robotisation.h"
#include "inverse.h"
#include "vynil.h"
#include "lowboost.h"
#include "lowpass.h"
#include "highpass.h"
#include "partition.h"
#include <iostream>
#include <chaine_effets.h>
#include <assm.h>

int main(int argc, char **argv) {
	using namespace assm;
	
	if(argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <wav_in> <wav_out>" << std::endl;
		std::cerr << "Fichiers WAV mono 16 bits uniquement." << std::endl;
		return 1;
	}
	
	// Crée un buffer son à 44,1kHz
	son pd(44100);
	// Lit le fichier (en mono)
	lire_wav(argv[1], pd);
	
	// Crée une chaîne d'effets sur le son
	chaine_effets c(pd);
	delay d(c);
	c.effets().push_back(&d);
	d.debut(0.2);
	d.fin(0.3);
	d.time(0.2);
	d.wet(0.3);
	d.feedback(0.4);
	/*
	// Crée une bonne grosse disto de bâtard
	distorsion d(c, 24.0);
	d.debut(0.2);
	distorsion d2(c, 14.0);
	// Rajoute cette disto dans les effets
	c.effets().push_back(&d);
	c.effets().push_back(&d2);
	*/
	/*	
	distorsion d(c, 0.4);
	c.effets().push_back(&d);
*/
	/*
	robotisation r(c);
	std::cout<<"Ttry??\n";
	c.effets().push_back(&r);
	std::cout<<"BAD??\n";
	*/
	/*
	vynil v(c,0.2);
	v.debut(0.001);
	c.effets().push_back(&v);
	*/
	/*
	inverse i(c);
	c.effets().push_back(&i);
	*/
	/*
	lowboost l(c);
	c.effets().push_back(&l);*/
<<<<<<< HEAD
	/*
	lowpass l(c,200);
	c.effets().push_back(&l);
	*/
	/*
	highpass h(c,1200);
	c.effets().push_back(&h);
	*/
=======
	
	// lowpass l(c,200);
	// c.effets().push_back(&l);
	
>>>>>>> 6638f2801a3bd2fbceb626e3b9bbc52ca9d95b64
// 	r.debut(0);
// 	r.fin(1);
	
	partition p(c,"test.midi");
	c.effets().push_back(&p);
	/*
	delay d(c,0.2);
	d.feedback(0.9);
	d.debut(0);
	d.fin(1);
	d.wet(0.5);
	c.effets().push_back(&d);
	distorsion d2(c, 14.0);
	c.effets().push_back(&d2);*/
	// Exécute la chaîne d'effets
	c();

	// Le son pd est modifié, on l'écrit dans un fichier
	ecrire_wav(c.out(), argv[2]);
	return 0;
}