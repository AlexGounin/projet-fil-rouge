#ifndef _LISTE_CHAINE_H
#define _LISTE_CHAINE_H

#include <stdio.h>

typedef struct s_liste_chaine * ListeChaine;

/**
* Initialise une ListeChaine
* retourne 1 si tout ce passe bien 0 sinon
*/
int init_liste_chaine(ListeChaine* listeChaine);

/**
* Ajout d'une chaine a une ListeChaine
* retourne 1 si tout ce passebien 0 sinon
*/
int ajouter_chaine(ListeChaine* listeChaine, char* chaine);

/*
* Retourne une ListeChaine contenant la difference entre l1 et l2
* l1 etant la liste servant de base et l2 de comparaison
* on retournera alors ce qui est dans l2 mais pas dans l1.
* si erreur retourne NULL
*/
ListeChaine difference(ListeChaine l1, ListeChaine l2);

/*
* Supprine une chaine dans une ListeChaine
* retourne 1 si tout ce passe bien 0 sinon
*/
int supprimer_chaine(ListeChaine* listeChaine, char* chaine);

/**
* Libere la place en memoire d'une ListeChaine
*/
void free_liste_chaine(ListeChaine* listeChaine);

/*
* Affiche une ListeChaine en entier
*/
void afficher_liste_chaine(ListeChaine listeChaine);

/*
* Indique si la chaine est comprise dans l1
* retourne 1 si tout ce passe bien, 0 sinon
*/
int liste_chaine_contains(ListeChaine l1, char* chaine);

/*
* Permet de recuperer la reference d'une chaine
* retourne NULL si erreur.
*/
char* get_liste_chaine(ListeChaine liste, int indice);

/*
* Ajoute une chaine a une position donner
* retourne 1 si tout ce passe bien, 0 sinon
*/
int ajouter_chaine_position(ListeChaine* listeChaine, char* chaine, int position);

#endif
