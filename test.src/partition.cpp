#include "partition.h"
#include <assm.h>
#include <iterator_part.hpp>
#include <iostream>
#include <imcc.h>
using namespace assm;
using namespace imcc;

void partition::operator()() {
		// Partition magique!

		size_t taille_fft = 1024;
	  	son fenetre(taille_fft, 44100);
		note ancienne_note;
		lecteur_midi l(nom_fichier_);
		
		MidiFile_t file = MidiFile_new(1, MIDI_FILE_DIVISION_TYPE_PPQ, echantillon_fin()-echantillon_debut());
		MidiFileTrack_t track = MidiFile_createTrack(file);
		
		double note_start=0.0;
		for(size_t i=echantillon_debut(); i+taille_fft<echantillon_fin(); i += taille_fft){
		  
		  std::copy(in().data().begin() + i, in().data().begin() + i + taille_fft, fenetre.begin());
		  std::vector<double> autocorrelation;
		  // Faire des choses magiques : une autocorrélation !
		  calculer_autocorrelation(fenetre.data(), autocorrelation);
		  
		  // Trouve la fréquence du premier pic
		  size_t premier_pic = indice_premier_pic(autocorrelation);
		  double frequence_premier_pic = 1.0 / fenetre.temps(premier_pic);
		  
		  // Transforme la fréquence en note
		  note note_pic(frequence_premier_pic);		  
		  
		  // Si c'est une note nouvelle, alors on en parle :
		  if(note_pic != ancienne_note) {
		      MidiFileEvent_t g2 = MidiFileTrack_createNoteStartAndEndEvents(track, 0,127, 10, 440, 1,1); /* returns the start event */
		      MidiFileEvent_t g = MidiFileTrack_createNoteStartAndEndEvents(track, note_start, in().temps(i), 10, ancienne_note.frequence(), 1,1); /* returns the start event */
		      MidiFileEvent_t g3 = MidiFileTrack_createNoteOnEvent(track,note_start , 10,440, 1);
		      MidiFileEvent_t g4 = MidiFileTrack_createNoteOffEvent(track, in().temps(i),10,440, 10);
		      MidiFileTempoEvent_setTempo(g,60);
		      evt_note ma_note;
		      ma_note.canal_ = 0;
		      ma_note.note_ = ancienne_note.frequence();
		      ma_note.debut_ = (int)note_start;
		      ma_note.duree_ = (int)in().temps(i)-note_start;
		      l.notes().push_back(ma_note);
		      std::cout << ancienne_note.nom() << ancienne_note.octave() << " @ " << note_start << "s avec une durée de "<<in().temps(i)-note_start << std::endl;
		      ancienne_note = note_pic;
		      note_start = in().temps(i);
		    }
		  
		}
		MidiFile_save(file,nom_fichier_);
		/*
		c'est une struct qu'y a dans libprojet/imcc/midi.h
		tu fais un struct par note
		et tu l'ajoutes à un midi
		pour ça
		faut faire une instance de lecteur_midi
		genre
		lecteur_midi l;
		et ensuite pour rajouter les notes :
		l.notes().push_back(ma_note)
		avec ma_note qui est de type evt_note
		evt_note ma_note;
		ma_note.canal_ = 0;
		ma_note.note_ = euuuh
		pour avoir la note midi
		faut faire une instance de assm::note
		genre assm::note n(frequence)
		et pour le pitch midi, c'est n.midi_pitch()
		et pour les durées
		là aussi ça risque d'être tendax
		
		
		*/
}