#include "fichiers.h"
#include <sstream>
#include <cstdlib>
typedef short T;

namespace assm {

void lire_raw(std::string fichier, son& s) 	 {
	std::ifstream f(fichier.c_str(), std::ios::binary | std::ios::ate);
	size_t taille = f.tellg();
	f.seekg(0, std::ios::beg);
	std::vector<T> contenu(taille / sizeof(T));
	f.read(reinterpret_cast<char*>(&(contenu[0])), taille);
	s.append_raw(contenu.begin(), contenu.end());
}

void lire_raw_stereo(std::string fichier, son& s_gauche, son& s_droit) {
	std::ifstream f(fichier.c_str(), std::ios::binary | std::ios::ate);
	size_t taille = f.tellg();
	f.seekg(0, std::ios::beg);
	std::vector<T> contenu(taille / sizeof(T));
	f.read(reinterpret_cast<char*>(&(contenu[0])), taille);
	std::vector<T> contenu_g(contenu.size() / 2), contenu_d(contenu.size() / 2);
	for(size_t i=0; i<contenu_g.size(); ++i) {
		contenu_g[i] = contenu[i*2];
		contenu_d[i] = contenu[i*2+1];
	}
	s_gauche.append_raw(contenu_g.begin(), contenu_g.end());
	s_droit.append_raw(contenu_d.begin(), contenu_d.end());
}

void ecrire_raw(son& s, std::string fichier) {
	std::ofstream f(fichier.c_str(), std::ios::binary);
	std::vector<T> contenu(s.size());
	s.convert_to(contenu.begin());
	size_t taille = s.size() * sizeof(T);
	f.write(reinterpret_cast<char*>(&(contenu[0])), taille);
}
	
void lire_wav(std::string fichier, son& s) {
	std::stringstream commande, commande2;
	std::string fichier_tmp = fichier + "_tmp.raw";
	
	commande <<  "sox \"" << fichier << "\" -r " << s.rate() << " -c1 -s2 \"" << fichier_tmp << "\"";
	system(commande.str().c_str());
	
	lire_raw(fichier, s);
	
	commande2 <<  "rm \"" << fichier_tmp << "\"";
	system(commande2.str().c_str());
}

void lire_wav_stereo(std::string fichier, son& s_gauche, son& s_droit) {
	std::stringstream commande, commande2;
	std::string fichier_tmp = fichier + "_tmp.raw";
	
	commande <<  "sox \"" << fichier << "\" -r " << s_gauche.rate() << " -c1 -s2 \"" << fichier_tmp << "\"";
	system(commande.str().c_str());
	
	lire_raw_stereo(fichier, s_gauche, s_droit);
	
	commande2 <<  "rm \"" << fichier_tmp << "\"";
	system(commande2.str().c_str());
}

void ecrire_wav(son& s, std::string fichier) {
	std::stringstream commande, commande2;
	std::string fichier_tmp = fichier + "_tmp.raw";
	
	ecrire_raw(s, fichier_tmp);
	
	commande <<  "sox -r " << s.rate() << " -c1 -s2 \"" << fichier_tmp << "\" \"" << fichier << "\"";
	system(commande.str().c_str());
	
	commande2 <<  "rm \"" << fichier_tmp << "\"";
	system(commande2.str().c_str());
}

}