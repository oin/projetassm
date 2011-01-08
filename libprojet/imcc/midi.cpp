#include "midi.h"

#include <iostream>
#include <sstream>

namespace imcc {

const char *mes_notes_a_moi[12] = {"Do", "Do#", "Re", "Re#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si" };

std::string nom_note(int note, int canal) {
	std::ostringstream oss;
	
	if(canal != 10) {
		int octave = note / 12;
		int n = note % 12;
		oss << mes_notes_a_moi[n];
		oss << octave;
		return oss.str();
	} else {
		return "prout";
	}
}

std::string temps_secondes(int ticks, int bpm) {
	std::ostringstream oss;
	
	if(bpm == 0) bpm = 120;
	
	int s = ticks / bpm;
	int ds = ticks % bpm;
	oss << s << "\"";
	if(ds != 0)
	 	oss << ds << "'";
	return oss.str();
}

void lecteur_midi::lire() {
	MidiFileEvent_t e = MidiFile_getFirstEvent(mon_midi_);
	
	while(e) {
		if(MidiFileEvent_isTempoEvent(e)) {
			tempo_ = MidiFileTempoEvent_getTempo(e);
			// std::cout << "Tempo: " << tempo_ << "bpm" << std::endl;
		} else
		if(MidiFileEvent_isNoteStartEvent(e)) {
			evt_note note;
			
			note.canal_ = MidiFileNoteStartEvent_getChannel(e);
			note.debut_ = MidiFileEvent_getTick(e);
			note.duree_ = MidiFileEvent_getTick(MidiFileNoteStartEvent_getNoteEndEvent(e)) - note.debut_;
			note.note_ = MidiFileNoteStartEvent_getNote(e);
			
			notes_.push_back(note);
			
			// std::cout << nom_note(note.note_, note.canal_) << "("
			// 										<< "canal " << note.canal_
			// 										<< ", "
			// 										<< "temps " << temps_secondes(note.debut_, tempo_)
			// 										<< ", "
			// 										<< "durée " << temps_secondes(note.duree_, tempo_)
			// 										<< ")"
			// 										<< std::endl;
		}
		e = MidiFileEvent_getNextEventInFile(e);
	}
}

void lecteur_midi::jouer(assm::son& buf) {
	std::list<evt_note> notes_restantes(notes_);
	evt_note note_actuelle;
	unsigned int temps = 0;
	bool presence_note_actuelle = false;
	int unite_de_temps_de_son = (int)(buf.rate() * (double)(MidiFile_getTimeFromTick(mon_midi_, 1)));
	assm::sinusoide mon_synthe(440.0, buf.rate());
	
	while(!(notes_restantes.empty() && !presence_note_actuelle)) {
		for(std::list<evt_note>::iterator it = notes_restantes.begin(); it != notes_restantes.end(); ++it) {
			evt_note n = *it;
			if(n.debut_ == static_cast<int>(temps) /*&& n.canal_ == 0*/) {
				note_actuelle = n;
				presence_note_actuelle = true;
				it = notes_restantes.erase(it);
				mon_synthe = assm::sinusoide((int)((440.0 / 32) * pow(2, ((note_actuelle.note_ - 9.0) / 12))), buf.rate());
			}
		}
		if(!presence_note_actuelle || note_actuelle.debut_ + note_actuelle.duree_ < static_cast<int>(temps)) {
			presence_note_actuelle = false;
		} else {
			// Joue encore une unité de temps de son
			presence_note_actuelle = true;
			for(int n = 0; n < unite_de_temps_de_son; ++n)
				buf.data().push_back(mon_synthe());
		}
		++temps;
	}
}

}