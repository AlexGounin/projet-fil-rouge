#include "texte.h"

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_MOT 100

int ponctuation(char c) {
    return 
        c == ',' || c == '.' ||
        c == ':' || c == ';' ||
        c == '(' || c == ')' ||
        c == '?' || c == '!' ||
        c == '%' || c == '"'
        ;
}

void supprimerPonctuation(char* mot) {
    char c = mot[0];
    int i = 0;
    while (c != '\0') {
        if (ponctuation(c))
            mot[i] = '\0';
        i++;
        c = mot[i];
    }
}

void supprimerChiffre(char* mot) {
    char c = mot[0];
    int i = 0;
    while (c != '\0') {
        if (c >= 48 && c <= 57)
            mot[i] = '\0';
        i++;
        c = mot[i];
    }
}

void lowercase(char* mot) {
    char c = mot[0];
    int i = 0;
    while (c != '\0') {
        if (c >= 65 && c <= 90)
            mot[i] = mot[i] + 32;
        i++;
        c = mot[i];
    }
}

void supprimerArticle(char* mot) {
    int i = 0;
    while (mot[i] != '\0' && mot[i] != '\'') i++;
    if (mot[i] == '\'' && i < 4) {
        strcpy(mot, mot + i + 1);
    }
}

void nettoyer_mot(char* mot) {
    supprimerPonctuation(mot);
    supprimerChiffre(mot);
    lowercase(mot);
    supprimerArticle(mot);
}

void respecterConfig(char* chaine, int nbmin, int nbmax) {
    if (strlen(chaine) < nbmin)
        chaine[0] = '\0';
    if (strlen(chaine) > nbmax)
        chaine[0] = '\0';
}

ListeChaine nettoyer_liste(ListeChaine l, int nbmin, int nbmax, int *nbMot) {
    char* chaine;
    int i = 0;
    while ((chaine = get_liste_chaine(l, i++)) != NULL) {
        nettoyer_mot(chaine);
    }
    i = 0;
    while ((chaine = get_liste_chaine(l, i++)) != NULL) {
        if (strlen(chaine) != 0)
            i++;
    }
    *nbMot = i;

    i = 0;
    while ((chaine = get_liste_chaine(l, i++)) != NULL) {
        respecterConfig(chaine, nbmin, nbmax);
    }

    ListeChaine l2;
    init_liste_chaine(&l2);
    i = 0;
    while ((chaine = get_liste_chaine(l, i++)) != NULL) {
        if (strlen(chaine) != 0)
            ajouter_chaine(&l2, chaine);
    }
    return l2;
}

int initialiser_structure_texte(Texte* t, Fichier f) {
    *t = malloc(sizeof(struct s_texte));
    if (*t == NULL) {
        fprintf(stderr, "[texte.c: init_texte] erreur malloc sur *t\n");
        return 0;
    }
    (*t)->f = f;
    return 1;
}

int init_texte(Texte* t, Fichier f, int nbMin, int nbMax) {
    if (initialiser_structure_texte(t, f) == 0) return 0;
    char chaine[TAILLE_MAX_MOT];
    char* sub;
    ListeChaine l;
    init_liste_chaine(&l);
    while (fscanf(f.fichier, "%s", chaine) != EOF) {
        if (strncmp(chaine, "<phrase>", strlen("<phrase>")) == 0) {
            strcpy(chaine, chaine + 8);
            ajouter_chaine(&l, chaine);
            while (fscanf(f.fichier, "%s", chaine) != EOF) {

                if ((sub = strstr(chaine, "</phrase>")) != NULL) {
                    sub[0] = '\0';
                    ajouter_chaine(&l, chaine);
                    break;
                }
                ajouter_chaine(&l, chaine);
            }
        }
    }
    ListeChaine l2 = nettoyer_liste(l, nbMin, nbMax, &((*t)->nbMot));
    free_liste_chaine(&l);
    (*t)->l = l2;

    return 1;
}

void afficher_texte(Texte t) {
    afficher_liste_chaine(t->l);
}

void free_texte(Texte *t) {
    free_liste_chaine(&(*t)->l);
    *t = NULL;
}
