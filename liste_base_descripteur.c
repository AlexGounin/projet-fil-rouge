#include <stdio.h>
#include "liste_base_descripteur.h"
#include "liste_chaine.h"

typedef struct s_cellule *Cellule;

struct s_cellule {
    int id;
    char *nom;
    Cellule suiv;
} s_cellule;

struct s_liste_base_descripteur {
    FILE *f;
    Cellule tete;
    Cellule queue;
} s_liste_base_descripteur;

//=========================================================================================
int init_lbd(LBD * lbd, char cheminFichier[])
{
    int _id = 0;
    *lbd = (LBD) malloc(sizeof(s_liste_base_descripteur));      //on alloue une case mémoire a notre liste chainée
    (*lbd)->f = fopen(cheminFichier, "r+");     //on précise dans quel fichier devra être écrit le liste_base_descripteur
    
    if((*lbd)->f == NULL) {
        perror("[liste_base_descripteur.c]init_lbd");
        fprintf(stderr, "[liste_base_descripteur.c: init_lbd] erreur lors de l'ouverture de %s\n", cheminFichier);
        return 0;
    }
    (*lbd)->tete = NULL;
    (*lbd)->queue = NULL;

    char _nom[1024];
    fseek((*lbd)->f, 0, SEEK_SET);
    while (fscanf((*lbd)->f, "%d\t%1024s\n", &_id, _nom) != EOF) {
        // printf("%d %s\n", _id, _nom);
        ajouter_lbd(lbd, _nom);
    }
    // afficher_liste_chaine(get_fichier_indexer(*lbd));
    return 1;
}

//=========================================================================================
int ajouter_lbd(LBD * lbd, char* str)     //utile pour les tests
{
    Cellule nouvelle = (Cellule) malloc(sizeof(s_cellule));
    if (nouvelle == NULL) {
        perror("[liste_base_descripteur.c]ajouter_lbd");
        return 0;
    }
    
    if (lbd_vide((*lbd))) {
        nouvelle->id = 0;
    } else {
        nouvelle->id = prochain_id_lbd((*lbd));
    }
    
    nouvelle->nom = NULL;
    nouvelle->nom =  malloc(strlen(str)+1);
    nouvelle->suiv = NULL;

    if (nouvelle->nom == NULL) {
        perror("[liste_base_descripteur.c]ajouter_lbd");
        return 0;
    } else {
        strcpy(nouvelle->nom,str);
    }

    if ((*lbd)->tete == NULL) {
        (*lbd)->tete = (*lbd)->queue = nouvelle;
        return 1;
    } else {
        /* on empile dans queue */
        (*lbd)->queue->suiv = nouvelle;
        (*lbd)->queue = nouvelle;

        return 1;
    }
}

//=========================================================================================
char lbd_vide(LBD lbd)
{
    return lbd->tete == NULL;
}

//=========================================================================================
void ecrire_lbd(LBD lbd)
{
    if (!lbd_vide(lbd))
    {
        Cellule celCourante = lbd->tete;
        fseek(lbd->f, 0, SEEK_SET);
        /* tant  qu'on a pas parcouru toute la liste */
        while (celCourante != NULL)
        {
            /* on écrit dans le fichier */
            fprintf(lbd->f, "%d\t%s\n", celCourante->id, celCourante->nom);
            celCourante = celCourante->suiv;
        }
    }
}

//=========================================================================================
int prochain_id_lbd(LBD lbd)
{
    if (lbd_vide(lbd))
        return 0;
    return lbd->queue->id + 1;
}

//=========================================================================================
void free_lbd(LBD * lbd)
{
    fclose((*lbd)->f);
    free(*lbd);
    *lbd = NULL;
}

//=========================================================================================
ListeChaine get_fichier_indexer(LBD lbd) {
    int valide;

    ListeChaine nouvelle = NULL;

    valide = init_liste_chaine(&nouvelle);
    if (!valide) {
        return NULL;
    }
    // tant  qu'on a pas parcouru toute la liste
    Cellule celCourante = lbd->tete;
    while ((celCourante) != NULL)
    {
        valide = ajouter_chaine(&nouvelle, celCourante->nom);
        if (valide == 1) {
            celCourante = celCourante->suiv;
        } else {
            fprintf(stderr, "[lbd : getFichierIndexer] code d'erreur retourné par ajouter_chaine\n");
            free_liste_chaine(&nouvelle);
            return NULL;
        }
    }
    
    return nouvelle;
}
