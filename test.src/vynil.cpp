#include "vynil.h"
#include <iostream>

using namespace assm;

void appliquer_fenetre_de_hanna(son& s) {
	s.data()[0] = 0;
	for(size_t n=1; n<s.size(); ++n) {
		s.data()[n] = 0.5 * (1 - cos(2 * 3.14159 * n / s.size()));
	}
}

void appliquer_fenetre_de_Bartlett(son& s) {
	s.data()[0] = 0;
	for(size_t n=1; n<s.size()/2; ++n) {
		s.data()[n] = (2.0*n)/s.size();
		
	}
	for(size_t n=s.size()/2; n<s.size(); ++n) {
		s.data()[n] = (2.0*(s.size()-n))/s.size();
	}
}

void vynil::operator()() {
  
	size_t taille_fft = 1024;
	son fenetre(taille_fft, 44100);

	// Fait une fenêtre de Hann
	son fenetre_hann(taille_fft, 44100);
	appliquer_fenetre_de_hanna(fenetre_hann);

	fft ma_fft(fenetre);
	ffti ma_ffti(ma_fft.out());
	std::cout<<"Limit: "<<limit_<<" \n";
	std::fill(out().data().begin()+echantillon_debut(), out().data().begin()+echantillon_fin(),0.0);
	for(size_t i=echantillon_debut(); i+taille_fft<echantillon_fin(); i += taille_fft/2){
	  
		// Copie de l'entrée dans la fenêtre
		std::copy(in().data().begin() + i, in().data().begin() + i + taille_fft, fenetre.begin());
		
		//Application de la fênetre de Hann pour le chevauchement
		std::transform(fenetre_hann.data().begin(), fenetre_hann.data().end(), fenetre.data().begin(), fenetre.data().begin(), std::multiplies<double>());
		
		// Fait la FFT
		ma_fft();
		
		for(size_t j=0; j<taille_fft; ++j){
		      if(ma_fft.out().data()[j] < limit_/taille_fft){
			  ma_fft.out().data()[j] = limit_/taille_fft;			
		      }
		}
		// Fait une conjugué-symétrie
		ma_fft.out().conjugue_symetrie();
		// Fait la FFTI
		ma_ffti();
		// Génère des transitoires aléatoirement
		bool transitoire_ici = (rand() % 10 < 1);
		static const int taille_transitoire = 10;
		if(transitoire_ici) {
			size_t bin_transitoire = rand() % (taille_fft - taille_transitoire);
			for(size_t j=0; j < taille_transitoire; ++j)
				ma_ffti.out().data()[bin_transitoire + j] = 0.9;
		}
		// Recopie le résultat dans la sortie au bon endroit
		std::transform(ma_ffti.out().begin(), ma_ffti.out().end(), out().data().begin() + i,out().data().begin() + i,std::plus<double>());
	}

}