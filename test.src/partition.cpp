#include "partition.h"
#include <assm.h>
#include <iterator_part.hpp>
#include <iostream>

using namespace assm;

void partition::operator()() {
		// Partition magique!

		size_t taille_fft = 1024;
	  	son fenetre(taille_fft, 44100);
		note ancienne_note;

		double note_start=0.0;
		for(size_t i=echantillon_debut(); i+taille_fft<echantillon_fin(); i += taille_fft){
		  
		  std::copy(in().data().begin() + i, in().data().begin() + i + taille_fft, fenetre.begin());
		  std::vector<double> autocorrelation;
		  // Faire des choses magiques : une autocorrélation !
		  calculer_autocorrelation(fenetre.data(), autocorrelation);
		  
		  // Trouve la fréquence du premier pic
		  size_t premier_pic = indice_premier_pic(autocorrelation);
		  double frequence_premier_pic = 1.0 / fenetre.temps(premier_pic);
		  
		  // Transforme la fréquence en note
		  note note_pic(frequence_premier_pic);		  
		  
		  // Si c'est une note nouvelle, alors on en parle :
		  if(note_pic != ancienne_note) {
		      std::cout << ancienne_note.nom() << ancienne_note.octave() << " @ " << note_start << "s avec une durée de "<<in().temps(i)-note_start << std::endl;
		      ancienne_note = note_pic;
		      note_start = in().temps(i);
		    }
		  
		}
		
		
}