#include "descripteur_texte.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


/*
* composition du fichier texte
* ID
* liste des mot \t nombre d'occurence
* nombre total de mots
* taille du texte en nombre de mots
*************
* exemple:
* 1
* jeux  45
* anniversaire 20
* 2
* 1023
*/

int creation_descripteur_texte(int id, Texte *texte, char *chemin, int seuil, int nb_limite) {
    assert(chemin);

    FILE* f = fopen(chemin, "w+");
    if(f == NULL) {
        perror("[descripteur_texte: creation_descripteur_texte] ouverture fichier");
        fprintf(stderr, "[descripteur_texte.c: creation_descripteur_texte] erreur sur ouverture fichier: %s\n", chemin);
        return 0;
    }
    //ecriture de l'id dans le fichier
    fprintf(f, "%d\n", id);

    //ajout des mots et de leur occurance
    int nbMots = gestion_mot_occurance(f, texte, seuil, nb_limite);

    //ajout du nombre mot significatif
    fprintf(f, "%d\n", nbMots);

    //ajout de la taille du texte
    fprintf(f, "%d\n", (*texte)->nbMot);

    fclose(f);
    return 1;
}

int get_nb_occurance_mot(Texte *texte, char *mots) {
    assert(mots);

    int nbOccurance = 0;
    while (liste_chaine_contains((*texte)->l, mots)) {
        ++nbOccurance;
        supprimer_chaine(&((*texte)->l), mots);
    }

    return nbOccurance;
}

int inserer_nbOccurance(int *tab, int taille, int nbOccurance) {
    for (int i = 0; i < taille; ++i)
    {
        if(nbOccurance >= tab[i]) {
            //on fait le decalage
            for (int j = (taille - 1); j > i ; --j) {
                tab[j] = tab[j-1];
            }
            tab[i] = nbOccurance;
            return i;
        }
    }

    return -1;
}

int gestion_mot_occurance(FILE *f, Texte *texte, int seuilApparitionMin, int nbMotsMax) {
    assert(f);

    // definition des tableau pour retenir les mots et leurs occurances
    ListeChaine motsRetenue;
    if(init_liste_chaine(&motsRetenue) == 0) {
        fprintf(stderr, "[descripteur_texte.c : gestion_mot_occurance] erreur sur l'init_liste_Chaine\n");
        return 0;
    }

    int occuranceMot[nbMotsMax];

    //init du tableau
    for (int i = 0; i < nbMotsMax; ++i)
    {
        occuranceMot[i] = 0;
    }
    char *motsCourant = get_liste_chaine((*texte)->l, 0);
    int nbOccurance, nbMots = 0, indice;

    //parcourt de tous les mots de la liste,
    //on ne passe que par l'indice 0 car get_nb_occurance_mot
    //supprime le mot deja traite.
    while(motsCourant != NULL) {
        nbOccurance = get_nb_occurance_mot(texte, motsCourant);
        //si le mot est retenu
        if(nbOccurance >= seuilApparitionMin) {
            //ajout du nombre d'occurance et test si le mot etait pertiant
            if((indice = inserer_nbOccurance(occuranceMot, nbMotsMax, nbOccurance)) != -1) {
                if(ajouter_chaine_position(&motsRetenue, motsCourant, indice) == 0) {
                    fprintf(stderr, "[descripteur_texte.c: gestion_mot_occurance] erreur sur ajout: %s, position: %d\n", motsCourant, indice);
                    return 0;
                }
            }

            //gestion de l'incrementation de l'indice des tableaux
            if(nbMots < nbMotsMax) {
                ++nbMots;
            }
        }
        // free(motsCourant);
        motsCourant = get_liste_chaine((*texte)->l, 0);
    }

    //ecriture de tous les mots et de leur occurences dans le fichier
    for (int i = 0; i < nbMotsMax; ++i)
    {
        if(occuranceMot[i] != 0) {
            fprintf(f, "%s\t%d\n", get_liste_chaine(motsRetenue, i), occuranceMot[i]);
        }
    }

    return nbMots;
}
