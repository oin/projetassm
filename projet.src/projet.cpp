#include "controleur.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) {
	// Lance le générateur de nombres aléatoires
	srand(time(NULL));
	// Prépare le contrôleur de l'application interactive laser
	controleur c(argc, argv);
	// Lance la fusée
	c.lancer();
}