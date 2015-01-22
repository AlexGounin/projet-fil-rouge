#ifndef _DESCRIPTEUR_TEXTE_H
#define _DESCRIPTEUR_TEXTE_H

#include <stdio.h>

#include "texte.h"
#include "liste_chaine.h"
#include "config.h"

#define TAILLE_MAX 11

/*
* Creer un descripteur a partir de son id, d'un texte et d'un chemin.
* le chemin represente l'endoit ou l'on souhaite sauvegarder notre descripteur
*/
int creation_descripteur_texte(int id, Texte *texte, char *chemin, int seuil, int nombre_limite);

/*
* Permet d'obtenir le nombre d'occurance d'un mots dans un texte, toutes les
* occurance sont supprimer au fur et a mesure du texte.
*/
int get_nb_occurance_mot(Texte *texte, char *mots);

/*
* Permet d'inserer dans une tableau un nb d'occurance
* retourne l'indice si tout ce passe bien, -1 sinon
*/
int inserer_nbOccurance(int *tab, int taille, int nbOccurance);

/*
* Permet de calculer le nombre d'occurance de chaque mots d'un texte.
* Ecrit dans le fichier si le mots est retenue comme pertinant
* retourne le nombre de mots pertinant
*/
int gestion_mot_occurance(FILE *f, Texte *texte, int seuil, int nombre_limite);


#endif
