#include "r_texte.h"

#include "lecture.h"
#include "r_son.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define TOUT_VA_BIEN 0
#define ERR_NB_PARAM 1
#define ERR_NON_REP  2

void usage(char* exec) {
	printf("Usage: %s repertoire_source.\n", exec);
}

void printMenu() {
	// system("clear");
	printf("# MENU GENERAL #\n");
	printf("a: Chercher un texte.\n");
	printf("b: Chercher une image en niveau de gris.\n");
	printf("c: Chercher une image couleur.\n");
	printf("d: Chercher un son.\n");
	printf("e: Fermer le programme.\n\n");
	printf("Veuillez entrer votre choix : ");
}

/**
 * execution du programme : ./moteur repertoire_source
 */
int main(int argc, char *argv[]) {

	char* choix;
	do  {
		printMenu();
		choix = lireClavier();
		if (strlen(choix) != 2) {
			switch (choix[0]) {
				case 'a': choixModeRechercheTexte(argv[1]); break;
				case 'b': break;
				case 'c': break;
				case 'd': rechercherUnSon(); break;
				default: if (choix[0] != 'e') printf("Choix invalide.\n");
			}
		} else
			printf("Le nombre de caractère doit être de un.\n");
		free(choix);
	} while (strlen(choix) == 2 && choix[0] != 'e');

	printf("Fin du programme.\n");

	return 0;
}
