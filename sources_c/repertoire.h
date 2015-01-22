#ifndef _REPERTOIRE_H
#define _REPERTOIRE_H

#include <stdio.h>

#define TAILLE_MAX_NOM_FICHIER 1024

typedef struct s_repertoire* Repertoire;

typedef struct s_fichier {
    FILE* fichier;
    char nom[TAILLE_MAX_NOM_FICHIER];
} Fichier;

/**
 * initialise la structure avec les fichiers listés par la commande ls "nomRep/\*.txt"
 * retourne 1 si tout ce passe bien, 0 sinon
 */
int init_repertoire(Repertoire* r, char* nomRep, char* mode);

/*
* Recupere le prochain fichier d'un repertoir
* retourne 1 si tout ce passe bien, 0 sinon
*/
int prochain_fichier(Repertoire r, Fichier* f);

/*
* Libere la memoire d'un repertoire
*/
void free_repertoire(Repertoire* r);

#endif
