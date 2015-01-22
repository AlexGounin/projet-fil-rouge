#ifndef _TEXTE_H
#define _TEXTE_H

#include "liste_chaine.h"
#include "repertoire.h"

struct s_texte {
    Fichier f;
    ListeChaine l;
    int nbMot;
};

typedef struct s_texte * Texte;

/*
* Permet d'initialiser un texte
* retourne 1 si tout ce passe bien, 0 sinon
*/
int init_texte(Texte* t, Fichier f, int nbMinCar, int nbMaxCar);

/*
* Affiche un texte passe en parametre
*/
void afficher_texte(Texte t);

/*
* Libere la zone memoire d'un texte
*/
void free_texte(Texte* t);

#endif
