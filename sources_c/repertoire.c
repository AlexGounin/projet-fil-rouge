#include "repertoire.h"
#include "shell.h"
#include "lecture.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>

#define LISTE_FICHIER "liste_fichier.tmp"

struct s_repertoire {
    Fichier* liste_fichier;
    int nb_fichier;
    int fichier_courant;
};

void ouvrirFichier(Repertoire* r, char* nomFichier, char* mode) {
    (*r)->liste_fichier[(*r)->nb_fichier - 1].fichier = fopen(nomFichier, mode);
    if ((*r)->liste_fichier[(*r)->nb_fichier - 1].fichier == NULL) {
        perror(nomFichier);
        fprintf(stderr, "[repertoire.c: init_repertoire] erreur lors de l'ouverture de : %s\n", nomFichier);
    }
}

int listerFichier(char* extension) {
    if (executer_commande(4, "find `pwd` -maxdepth 1 -type f -name '", extension, "' > ", LISTE_FICHIER) == 0) {
        fprintf(stderr, "[repertoire.c: init_repertoire] erreur ls ou repertoire vide.\n");
        return 0;
    }
    return nb_ligne_fichier(LISTE_FICHIER);
}

int init_structure_rep(Repertoire *r, char* extension, int nbFichier) {
    /* initialisation de la structure */
    *r = malloc(sizeof(struct s_repertoire));
    if (*r == NULL) {
        fprintf(stderr, "[repertoire.c: init_repertoire] erreur malloc sur *r\n");
        return 0;
    }
    (*r)->liste_fichier = NULL;
    (*r)->nb_fichier = 0;
    (*r)->fichier_courant = -1;

    (*r)->liste_fichier = (Fichier*) malloc(sizeof(struct s_fichier) * nbFichier);
    if ((*r)->liste_fichier == NULL) {
        perror("repertoire.c: init_repertoire");
        return 0;
    }
    return 1;
}

int init_repertoire(Repertoire* r, char* extension, char* mode) {
    /* listage des fichiers dans le repertoire */
    int nbFichier;
    if ((nbFichier = listerFichier(extension)) == 0) return 0;

    /* initialisation de la structure */
    if (init_structure_rep(r, extension, nbFichier) == 0) return 0;
    
    /* ouverture de tout les fichiers */
    FILE* listeFichier = fopen(LISTE_FICHIER, "r+");

    /* indiceFichierCourant */
    int* iFC = &((*r)->nb_fichier);
    *iFC = 0;

    Fichier* tabF = (*r)->liste_fichier;
    while (lireLigne(tabF[*iFC].nom, TAILLE_MAX_NOM_FICHIER, listeFichier) != 0) {
        (*iFC)++;
        ouvrirFichier(r, (*r)->liste_fichier[*iFC - 1].nom, mode);
    }

    remove(LISTE_FICHIER);
    fclose(listeFichier);
    return 1;
}

int prochain_fichier(Repertoire r, Fichier* f) {
    if (r->fichier_courant + 1 == r->nb_fichier) {
        return -1;
    }
    (r->fichier_courant)++;
    *f = r->liste_fichier[r->fichier_courant];
    return 1;
}

void free_repertoire(Repertoire* r) {
    for (int i = 0; i < (*r)->nb_fichier; ++i) {
        FILE* f = (*r)->liste_fichier[i].fichier;
        if (fclose(f) != 0)
            fprintf(stderr, "[repertoire.c: free_repertoire] erreur sur un close.\n");
    }
    free((*r)->liste_fichier);
    free(*r);
    *r = NULL;
}
