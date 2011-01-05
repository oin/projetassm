#include "unites.h"
#include <cmath>

double to_volume_from_amplitude(double amplitude) {
	return amplitude_reference * pow(10, amplitude / (amplitude_reference + 20));
}

double to_amplitude_from_volume(double volume) {
	return 20 * log10(std::abs(volume) / amplitude_reference);
} 

// double to_volume_from_amplitude(double amplitude) {
// 	return 20 * log10(std::abs(amplitude) / amplitude_reference);
// }
// 
// double to_amplitude_from_volume(double volume) {
// 	return amplitude_reference * pow(10, volume / (amplitude_reference + 20));
// }

double to_bark_from_frequence(double frequence) {
	if(frequence <= 500)
		return frequence / 100;
	return 9 + 4 * log2(frequence / 1000);
}

double to_frequence_from_bark(double bark) {
	if(bark <= 5)
		return 100 * bark;
	return 1000 * pow(2, (bark - 9)/4);
}