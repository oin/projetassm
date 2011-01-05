#if !defined(FICHIERS_H_HXUCY3TX)
#define FICHIERS_H_HXUCY3TX

#include "son.h"
#include <string>
#include <fstream>

namespace assm {

void lire_raw(std::string fichier, son& s);
void lire_raw_stereo(std::string fichier, son& s_gauche, son& s_droit);
void ecrire_raw(son& s, std::string fichier);

void lire_wav(std::string fichier, son& s);
void lire_wav_stereo(std::string fichier, son& s_gauche, son& s_droit);
void ecrire_wav(son& s, std::string fichier);

}

#endif /* end of include guard: FICHIERS_H_HXUCY3TX */
