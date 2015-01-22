#ifndef _LECTURE_H
#define _LECTURE_H

#include <stdio.h>
#include <stdarg.h>

/*
* Permet de vider le buffer pour le scanf
*/
void viderBuffer();

int longueur_chaine(int n, char* c, va_list params);

/**
 * Permet de lire une ligne dans un fichier
 * retourne 0 si bien passé
 * 1 sinon
 */
int lireLigne(char* chaine, int size, FILE* f);

/*
 * ne pas oublier de free la chaine retourné
 */
char* concat(int n, char* c, ...);

/*
* Permet de lire une chaine de caractere au clavier
*/
char* lireClavier();

#endif
