// #include "fenetre.h"
// #include <cstdlib>
// #include <string>
// #include <iostream>
// 
// #include <assm.h>
// #include "apercu_son.h"
// #include "wave_afficheur.h"
// #include "liste_effets.h"

// fenetre::fenetre() : gtk_(argc, argv) {
// 	if(argc != 2) {
// 		std::cerr << "Usage: " << argv[0] << " <wav_in>" << std::endl;
// 		exit(1);
// 	}
// 	assm::son s_(44100);
// 	lire_wav(argv[1], s_);
// 	apercu_son as_(s_);
// 	wave_afficheur aff_(as_);
// 	
// 	win_.set_title(std::string(argv[1]));
// 	
// 	// win_.add(aff_);
// 	
// 	liste_effets l;
// 	win_.add(l);
// 	
// 	win_.show_all_children();
// }