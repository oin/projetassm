#include <iostream>
#include "controleur.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) {
	srand(time(NULL));
	controleur c(argc, argv);
	c.lancer();
}