#include "distorsion.h"
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
	// Crée une bonne grosse disto de bâtard
	distorsion d(pd, 24.0);
	// Rajoute cette disto dans les effets
	c.effets().push_back(&d);
	// Exécute la chaîne d'effets
	c();
	// Le son pd est modifié, on l'écrit dans un fichier
	ecrire_wav(pd, argv[2]);
	
	return 0;
}