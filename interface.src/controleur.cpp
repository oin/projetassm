#include "controleur.h"
#include "fenetre.h"
#include <iostream>
#include <assm.h>

controleur::controleur(int argc, char** argv) : gtk_(argc, argv), btn_appliquer_(Gtk::Stock::APPLY), btn_entree_(Gtk::Stock::OPEN), btn_sortie_(Gtk::Stock::SAVE), liste_(*this), s_(44100), fx_(s_), tr1_(*this, 0), aff_entree_(apercu_), aff_sortie_(apercu_) {
	aff_entree_.peut_selectionner(false);
	aff_sortie_.peut_selectionner(false);
	
	w_.set_title("ASSM 3.11 for Workgroups");
	w_.set_border_width(5);
	
	scl_effets_.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	
	btn_appliquer_.set_sensitive(false);
	btn_appliquer_.signal_clicked().connect(sigc::mem_fun(*this, &controleur::appliquer_effets));
	btns_bas_.add(btn_appliquer_);
	hbx_bas_.add(btns_bas_);
	
	vbx_effets_.pack_start(tr1_, false, false, 5);
	
	scl_effets_.add(vbx_effets_);
	
	btn_entree_.signal_clicked().connect(sigc::mem_fun(*this, &controleur::ouvrir_fichier_entree));
	hbx_entree_fichier_.pack_start(btn_entree_, false, false, 5);
	lbl_entree_fichier_.set_label("(pas de fichier)");
	lbl_entree_fichier_.set_ellipsize(Pango::ELLIPSIZE_MIDDLE);
	lbl_entree_fichier_.set_line_wrap(false);
	lbl_entree_fichier_.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	hbx_entree_fichier_.pack_start(lbl_entree_fichier_, true, true, 5);
	// btn_entree_.set_label("...");
	vbx_entree_gauche_.add(hbx_entree_fichier_);
	
	frm_entree_.set_label("Entrée");
	frm_entree_.add(vbx_entree_gauche_);
	
	hbx_entree_.pack_start(frm_entree_, true, true, 5);
	hbx_entree_.pack_start(aff_entree_, true, true, 5);
	
	btn_sortie_.signal_clicked().connect(sigc::mem_fun(*this, &controleur::choisir_fichier_sortie));
	hbx_sortie_fichier_.pack_start(btn_sortie_, false, false, 5);
	lbl_sortie_fichier_.set_label("(pas de fichier)");
	lbl_sortie_fichier_.set_ellipsize(Pango::ELLIPSIZE_MIDDLE);
	lbl_sortie_fichier_.set_line_wrap(false);
	lbl_sortie_fichier_.set_alignment(Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
	hbx_sortie_fichier_.pack_start(lbl_sortie_fichier_, true, true, 5);
	
	vbx_sortie_gauche_.add(hbx_sortie_fichier_);
	
	frm_sortie_.set_label("Sortie");
	frm_sortie_.add(vbx_sortie_gauche_);
	
	hbx_sortie_.pack_start(frm_sortie_, true, true, 5);
	hbx_sortie_.pack_start(aff_sortie_, true, true, 5);
	
	vbx_principale_.pack_start(liste_, false, false, 5);
	vbx_principale_.pack_start(hbx_entree_, false, false, 5);
	vbx_principale_.pack_start(scl_effets_, true, true, 5);
	vbx_principale_.pack_start(hbx_sortie_, false, false, 5);
	vbx_principale_.pack_start(hbx_bas_, false, false, 5);
	
	w_.add(vbx_principale_);
}

controleur::~controleur() {}

void controleur::lancer() {
	w_.show_all_children();
	Gtk::Main::run(w_);
}

void controleur::appliquer_effets() {
	w_.set_sensitive(false);
	// Applique les effets
	fx_();
	// Enregistre le fichier
	try {
		assm::ecrire_wav(fx_.out(), nom_fichier_out_);
	} catch(...) {
		lbl_sortie_fichier_.set_label("(pas de fichier)");
		Gtk::MessageDialog md(w_, "Écriture impossible", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
		md.set_secondary_text("L'écriture du fichier a échoué parce que c'est la crise, bordel !");
		md.run();
	}
	w_.set_sensitive(true);
}

void controleur::creer_noisegate() {
	std::cout << "Noise gate" << std::endl;
}

void controleur::creer_delay() {
	
}

void controleur::creer_normalisation() {
	
}

void controleur::creer_distorsion() {
	
}

void controleur::charger_son(std::string n) {
	assm::son s_tmp_(44100);
	
	assm::lire_wav(n, s_tmp_);
	
	s_.data().clear();
	
	s_.data() = s_tmp_.data();
	
	apercu_.set(s_);
	
	lbl_entree_fichier_.set_label(n);
	
	w_.queue_draw();
}

void controleur::ouvrir_fichier_entree() {
	Gtk::FileChooserDialog d(w_, "Ouvrir (WAV 44,1kHz/Mono/16bits)");
	d.set_transient_for(w_);
	d.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	d.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	d.set_select_multiple(false);
	d.set_local_only(true);
	d.set_create_folders(false);
	Gtk::FileFilter filtre_wav;
	filtre_wav.add_mime_type("audio/x-wav");
	filtre_wav.add_mime_type("audio/wav");
	filtre_wav.add_mime_type("audio/wave");
	filtre_wav.add_mime_type("audio/x-pn-wav");
	filtre_wav.set_name("Fichiers WAVE mono 16 bits");
	d.set_filter(filtre_wav);
	int r = d.run();
	if(r == Gtk::RESPONSE_OK) {
		// Un nouveau fichier est à charger
		try {
			charger_son(d.get_filename());
		} catch(...) {
			lbl_entree_fichier_.set_label("(pas de fichier)");
			Gtk::MessageDialog md(w_, "Fichier invalide", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
			md.set_secondary_text("Le chargement a échoué car ce fichier est invalide, sa mère.");
			md.run();
		}
	}
}

void controleur::choisir_fichier_sortie() {
	Gtk::FileChooserDialog d(w_, "Enregistrer (WAV 44,1kHz/Mono/16bits)", Gtk::FILE_CHOOSER_ACTION_SAVE);
	d.set_transient_for(w_);
	d.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	d.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
	d.set_select_multiple(false);
	d.set_local_only(true);
	d.set_create_folders(false);
	Gtk::FileFilter filtre_wav;
	filtre_wav.add_mime_type("audio/x-wav");
	filtre_wav.add_mime_type("audio/wav");
	filtre_wav.add_mime_type("audio/wave");
	filtre_wav.add_mime_type("audio/x-pn-wav");
	filtre_wav.set_name("Fichiers WAVE mono 16 bits");
	d.set_filter(filtre_wav);
	int r = d.run();
	if(r == Gtk::RESPONSE_OK) {
		// Un fichier est choisi
		nom_fichier_out_ = d.get_filename();
		// On peut maintenant activer le bouton Appliquer
		btn_appliquer_.set_sensitive(true);
		// On affiche ce nom
		lbl_sortie_fichier_.set_label(nom_fichier_out_);
	}
}