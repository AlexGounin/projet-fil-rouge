#ifndef _RECHERCHE_TEXTE_H
#define _RECHERCHE_TEXTE_H

#include "lecture.h"
#include "shell.h"

typedef struct s_liste * Liste;


int rechercheParNomDeFichierTexte(char* chemin);

void afficher_liste(Liste listeChaine);
/*
 * Initialise la liste
 */
int init_liste(Liste *l);
/*
 * Ajoute une cellule a la liste contenant l'id et l'apparition
 * Cette cellule sera insérée entre deux autres ayant
 * une apparition plus grande et une plus petite
 */

int ajouter_liste(Liste *l, char* _id, int _apparition);
/*
 * Verifie si la liste est vide
 */
char liste_Vide(Liste l);
void free_liste(Liste *l);

/*
 * Recherche un fichier texte a partir d'un document donné
 */
//int rechercheParDocumentTexte();
/*
 * Recherche un fichier texte a partir d'un mot clef
 */
int rechercheParMotClefTexte();

#endif
