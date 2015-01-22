#ifndef _SHELL_H
#define _SHELL_H

#include <stdarg.h>

/**
 * n : nombre de paramètre envoyé après n
 * les autres paramètres doivent être de type char*, ou bien directement des "mqjdmfdqj"
 * exemple d'utilisation :
 * executer_commande(3, "ls -l", nomFichier, " > fichier.tmp")
 * 3 pour 3 chaines de caractère
 * nomFichier doit être de type char*
 */
int executer_commande(int n, char* c, ...);

/**
 * fait un ls sur le repertoire rep et envoie le résultat
 * dans le fichier de nom res
 */
int ls(char *rep, char* res);

/**
 * récupère le nombre de ligne d'un fichier
 * retourne 0 si erreur ou 0 ligne
 * le nombre de ligne sinon
 */
int nb_ligne_fichier(char* nomFichier);

/**
 * récupère la ième ligne d'un fichier
 */
int recupererIemeLigne(char* nomFic, int ligne, char* contenu);

#endif
