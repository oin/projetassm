#include "lowpass.h"
#include <assm.h>

using namespace assm;

void PassBas(son& s,double ordre){
size_t i;
s.data()[0]=1;
s.data()[(int)ordre/2]=1;

  for(i=1;i<(ordre/2);i++){
    s.data()[i]=1;
  }
  
 for(i=(int)(ordre/2);i<s.size();i++){
    s.data()[i]=0;
  }
}

void fenetre_de_hann(son& s) {
	for(size_t n=0; n<s.size(); ++n) {
		s.data()[n] = 0.5 * (1 - cos(2 * 3.14159 * n / s.size()));
	}
}

void lowpass::operator()() {
	// lowpass


	size_t taille_fft = 1024;
	double ordre = (freq_*taille_fft)/44100; 
	son fenetre(taille_fft, 44100);
	son fenetretmp(taille_fft, 44100);
	
	// Fait une fenêtre de Hann
	son fenetre_hann(taille_fft, 44100);
	fenetre_de_hann(fenetre_hann);
	
	son filtre(taille_fft, 44100);
	PassBas(filtre,ordre); 
	
	fft ma_fft(fenetre);
	ffti ma_ffti(ma_fft.out());
	
	std::fill(out().data().begin()+echantillon_debut(), out().data().begin()+echantillon_fin(),0.0);
	
	for(size_t i=echantillon_debut(); i+taille_fft<echantillon_fin(); i += taille_fft/2){
	  
		// Copie de l'entrée dans la fenêtre
		std::copy(in().data().begin() + i, in().data().begin() + i + taille_fft, fenetre.begin());
		
		//Application de la fênetre de Hann pour le chevauchement
		std::transform(fenetre_hann.data().begin(), fenetre_hann.data().end(), fenetre.data().begin(), fenetre.data().begin(), std::multiplies<double>());
				
		// Fait la FFT
		ma_fft();
		// Fait le lowpass
		std::transform(filtre.data().begin(), filtre.data().end(), ma_fft.out().data().begin(), ma_fft.out().data().begin(), std::multiplies<double>());

		// Fait une conjugué-symétrie
		ma_fft.out().conjugue_symetrie();
		// Fait la FFTI
		ma_ffti();
		// Recopie le résultat dans la sortie au bon endroit
		std::transform(ma_ffti.out().begin(), ma_ffti.out().end(), out().data().begin() + i,out().data().begin() + i,std::plus<double>());
	}
}