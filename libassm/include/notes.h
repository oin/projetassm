#if !defined(NOTES_H_12QTZ35D)
#define NOTES_H_12QTZ35D

#include <string>
#include <cmath>

namespace assm {
	
	enum { frequence_la3 = 440, midi_pitch_la3 = 69 };
	
	enum note_t {
		DO, DO_DIESE, RE, RE_DIESE, MI, FA, FA_DIESE, SOL, SOL_DIESE, LA, LA_DIESE, SI, NB_NOTES,
		DO_BEMOL = SI,
		RE_BEMOL = DO_DIESE,
		MI_BEMOL = RE_DIESE,
		FA_BEMOL = MI,
		MI_DIESE = FA,
		SOL_BEMOL = FA_DIESE,
		LA_BEMOL = SOL_DIESE,
		SI_BEMOL = LA_DIESE,
		SI_DIESE = DO
	};
	
	enum intervalle_t {
		UNISSON,
		SECONDE_MINEURE,
		SECONDE_MAJEURE,
		TIERCE_MINEURE,
		TIERCE_MAJEURE,
		QUARTE,
		QUARTE_AUGMENTEE,
		QUINTE,
		SIXTE_MINEURE,
		SIXTE_MAJEURE,
		SEPTIEME_MINEURE,
		SEPTIEME_MAJEURE,
		OCTAVE
	};
	
	
	struct note {
		typedef unsigned char midi_note_t;
		
		note(double frequence = 440) : midi_note_(static_cast<midi_note_t>(round(midi_pitch_la3 + NB_NOTES * log2(frequence / frequence_la3)))) {}
		note(midi_note_t midi_note, bool octave_up) : midi_note_(octave_up ? midi_note + NB_NOTES : midi_note) {}
		note(note_t n, int octave) : midi_note_(NB_NOTES * (octave + 1) + static_cast<int>(n)) {}
		virtual ~note() {}
		int octave() const { return static_cast<int>(midi_note_ / NB_NOTES); }
		note_t ton() const { return static_cast<note_t>(midi_note_ % NB_NOTES);}
		midi_note_t midi_pitch() const { return midi_note_; }
		double frequence() { return frequence_la3 * pow(2, (midi_note_ - midi_pitch_la3) * 1.0 / 12); }
		note suivante() const { return note(midi_note_ + 1, false); }
		note precedente() const { return note(midi_note_ - 1, false); }
		note intervalle_relatif(intervalle_t incr) const { return note(midi_note_ + static_cast<midi_note_t>(incr), false); }
		std::string nom() const { return notes_italien[ton()]; }
		std::string nom_anglosaxon() const { return notes_anglosaxon[ton()]; }
		bool operator!=(const note& n) const { return n.midi_note_ != midi_note_; }
		bool operator==(const note& n) const { return !operator!=(n); }
		bool operator<(const note& n) const { return n.midi_note_ < midi_note_; }
		bool operator<=(const note& n) const { return n.midi_note_ <= midi_note_; }
	private:
		midi_note_t midi_note_;
		static const std::string notes_italien[NB_NOTES];
		static const std::string notes_anglosaxon[NB_NOTES];
	};

}

#endif /* end of include guard: NOTES_H_12QTZ35D */
