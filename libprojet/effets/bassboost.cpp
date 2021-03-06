#include "bassboost.h"
#include <assm.h>

using namespace assm;

void filtrePassBas(son& s,double ordre){
size_t i;
s.data()[0]=1.3;
s.data()[(int)ordre/2]=2;

  for(i=1;i<(ordre/2);i++){
    s.data()[i]=1.3;
  }
  
 for(i=(int)(ordre/2);i<s.size();i++){
    s.data()[i]=1;
  }
}

void applique_fenetre_de_hann(son& s) {
	for(size_t n=0; n<s.size(); ++n) {
		s.data()[n] = 0.5 * (1 - cos(2 * 3.14159 * n / s.size()));
	}
}

void lowboost::operator()() {
	// lowboost
	size_t taille_fft = 1024;
	son fenetre(taille_fft, 44100);
	son fenetretmp(taille_fft, 44100);
	
	// Fait une fenêtre de Hann
	son fenetre_hann(taille_fft, 44100);
	applique_fenetre_de_hann(fenetre_hann);
	
	son filtre(taille_fft, 44100);
	// jusqu'à 300 Hz
	filtrePassBas(filtre, 7); 
	
	fft ma_fft(fenetre);
	ffti ma_ffti(ma_fft.out());
	
	for(size_t i=echantillon_debut(); i+taille_fft<echantillon_fin(); i += taille_fft/2){
	  
		// Copie de l'entrée dans la fenêtre
		std::copy(in().data().begin() + i, in().data().begin() + i + taille_fft, fenetre.begin());
		
		//Application de la fênetre de Hann pour le chevauchement
		std::transform(fenetre_hann.data().begin(), fenetre_hann.data().end(), fenetre.data().begin(), fenetre.data().begin(), std::multiplies<double>());
				
		// Fait la FFT
		ma_fft();
		// Fait le lowboost
		std::transform(filtre.data().begin(), filtre.data().end(), ma_fft.out().data().begin(), ma_fft.out().data().begin(), std::multiplies<double>());

		// Fait une conjugué-symétrie
		ma_fft.out().conjugue_symetrie();
		// Fait la FFTI
		ma_ffti();
		// Recopie le résultat dans la sortie au bon endroit
		std::transform(ma_ffti.out().begin(), ma_ffti.out().end(), out().data().begin() + i,out().data().begin() + i,std::plus<double>());
	}

	mixer_drywet();
}