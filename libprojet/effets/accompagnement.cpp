#include "accompagnement.h"
#include <assm.h>
#include <imcc.h>

using namespace assm;
using namespace imcc;

#include <iostream>

void accompagnement::operator()() {
	// It's magic !
	
	size_t taille_fft = 512;
  	son fenetre(taille_fft, in().rate());

	note ancienne_note, derniere_correcte;
	int nb_anciennes = 0;
	
	sinusoide mon_synthe(440, fenetre.rate());
	
	for(size_t i=echantillon_debut(); i+taille_fft<echantillon_fin(); i += taille_fft) {
		std::copy(in().data().begin() + i, in().data().begin() + i + taille_fft, fenetre.begin());
		
		std::vector<double> autocorrelation;
		calculer_autocorrelation(fenetre.data(), autocorrelation);

		// Trouve la fréquence du premier pic
		size_t premier_pic = indice_premier_pic(autocorrelation);
		double frequence_premier_pic = 1.0 / fenetre.temps(premier_pic);

		// Transforme la fréquence en note (permet d'arrondir)
		note note_pic(frequence_premier_pic);
		
		if(ancienne_note == note_pic) {
			++nb_anciennes;
			if(nb_anciennes >= intolerance_) {
				// Si on est au moment où la note est devenue "valide", on réécrit les trames d'avant, on réécrit l'histoire, mec !
				if(nb_anciennes == intolerance_ && note_pic != derniere_correcte) {
					for(int z=intolerance_; z>0; --z) {
						mon_synthe.frequence_ = note_pic.frequence();
						std::generate<std::vector<double>::iterator, sinusoide&>(out().begin() + i - z*taille_fft, out().begin() + i - (z-1)*taille_fft, mon_synthe);
					}
				}
				derniere_correcte = note_pic;
			}
		}
		else {
			ancienne_note = note_pic;
			nb_anciennes = 0;
		}
		// Joue la dernière note correcte
		mon_synthe.frequence_ = derniere_correcte.frequence();
		std::generate<std::vector<double>::iterator, sinusoide&>(out().begin() + i, out().begin() + i + taille_fft, mon_synthe);
	}
	
	mixer_drywet();
}