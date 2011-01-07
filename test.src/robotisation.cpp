#include "robotisation.h"

using namespace assm;

double phase_aleatoire() {
	return ((rand() * 1.0 / RAND_MAX) * 2 * 3.14159)-3.14159;
}

void appliquer_fenetre_de_hann(son& s) {
	for(size_t n=0; n<s.size(); ++n) {
		s.data()[n] = 0.5 * (1 - cos(2 * 3.14159 * n / s.size()));
	}
}

void robotisation::operator()() {
	size_t taille_fft = 1024;
	son fenetre(taille_fft, 44100);

	// Fait une fenêtre de Hann
	son fenetre_hann(taille_fft, 44100);
	appliquer_fenetre_de_hann(fenetre_hann);
		
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
		// Fait caca sur les phases
		std::generate(ma_fft.out().phase().begin(), ma_fft.out().phase().end(), phase_aleatoire);
		// Fait une conjugué-symétrie
		ma_fft.out().conjugue_symetrie();
		// Fait la FFTI
		ma_ffti();
		// Recopie le résultat dans la sortie au bon endroit
		std::transform(ma_ffti.out().begin(), ma_ffti.out().end(), out().data().begin() + i,out().data().begin() + i,std::plus<double>());
	}
}