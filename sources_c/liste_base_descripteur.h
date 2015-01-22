#ifndef _LISTE_BASE_DESCRIPTEUR_H
#define _LISTE_BASE_DESCRIPTEUR_H

#include "liste_chaine.h"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct s_liste_base_descripteur * ListeBaseDescripteur;

typedef ListeBaseDescripteur LBD;

/*
 * charge toutes les lignes du fichier cheminFichier en mémoire
 * format d'une ligne:
 *  id/nomFichier.txt
 */
int init_lbd(LBD * lbd, char cheminFichier[]);

/**
 * réécrit entièrement 
 */
void ecrire_lbd(LBD lbd);

/*
 * pour tester l'ecriture
 * permet de remplir la liste chainée
 */
int ajouter_lbd(LBD * lbd, char* str);

/**
 * retourne le prochain id disponible
 * RMQ : utile pour la construction d'un descripteur
 */
int prochain_id_lbd(LBD lbd);

/**
 * libère la mémoire pour éviter la perte de mémoire
 */
void free_lbd(LBD* lbd);

/**
 * 1 si lbd est vide
 * 0 sinon
 */
char lbd_vide(LBD lbd);


ListeChaine get_fichier_indexer(LBD lbd);

#endif
