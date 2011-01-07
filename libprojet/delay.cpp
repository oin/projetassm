#include "delay.h"

void delay::operator()() {
		// Delay lay lay lay !
		size_t echantillon_delay = static_cast<size_t>(time_ * in().rate());
		
		assm::son tmp(out().size(), out().rate());
		
		for(size_t i=echantillon_debut(); i + echantillon_delay < echantillon_fin(); ++i) {
			tmp.data()[i + echantillon_delay] = in().data()[i] + tmp.data()[i] * feedback_;
		}
		
		// Copie tmp dans le son à l'emplacement qu'il faut
		std::copy(tmp.begin() + echantillon_debut(), tmp.begin()  + echantillon_fin(), out().begin() + echantillon_debut());
		
		// Mixe
		mixer_drywet();
		
		// // Mixage
		// 		for(size_t i=echantillon_debut(); i<echantillon_fin(); ++i) {
		// 			out().data()[i] =
		// 				// On mixe le signal généré
		// 				std::min(1.0, std::max(-1.0, tmp.data()[i])) * wet() 
		// 				+
		// 				// Et le signal d'origine
		// 				in().data()[i] * dry();
		// 		}
		// 		
		// 		// for(size_t i=echantillon_debut()+echantillon_delay; i<echantillon_fin(); ++i) {
		// 		// 	out().data()[i] = out().data()[i] + out().data()[i-echantillon_delay] * feedback_;
		// 		// 
		// 		// }
}