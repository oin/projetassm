#if !defined(__MIDI_HPP)
#define __MIDI_HPP
#include "midifile.h"
#include <string>
#include <list>
#include <assm.h>

namespace imcc {

struct evt_note {
	int canal_;
	int note_;
	int debut_;
	int duree_;
};

struct lecteur_midi {
	typedef std::list<evt_note> liste_de_notes;
	typedef std::list<evt_note>::iterator iterator;
	lecteur_midi(std::string nom_fichier) : nom_fichier_(nom_fichier), mon_midi_(MidiFile_load(const_cast<char*>(nom_fichier.c_str()))) {}
	lecteur_midi() {}
	std::list<evt_note> notes() { return notes_; }
	void lire();
	void jouer(assm::son&);
	size_t size() { return notes_.size(); }
	iterator begin() { return notes_.begin(); }
	iterator end() { return notes_.end(); }
private:
	std::string nom_fichier_;
	MidiFile_t mon_midi_;
	std::list<evt_note> notes_;
	int tempo_;
};

}

#endif