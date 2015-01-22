#include "liste_chaine.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct s_cellule * Cellule;

struct s_cellule {
    char* chaine;
    Cellule suiv;
};

struct s_liste_chaine {
    Cellule tete;
    Cellule queue;
};

int init_liste_chaine(ListeChaine* listeChaine) {
    assert(listeChaine);
    //Initialisation de la structure
    *listeChaine = malloc(sizeof(struct s_liste_chaine));
    if(*listeChaine == NULL) {
        fprintf(stderr, "[listeChaine.c: init_liste_chaine] erreur malloc sur *listeChaine\n");
        return 0;
    }
    
    (*listeChaine)->tete = NULL;
    (*listeChaine)->queue = NULL;

    return 1;
}

int ajouter_chaine(ListeChaine* listeChaine, char* chaine) {
    //Gestion de l'erreur si la chaine est vide
    assert(listeChaine);

    //Creation de la nouvelle cellule
    Cellule c_tmp = malloc(sizeof(struct s_cellule));
    if(c_tmp == NULL) {
        fprintf(stderr, "[listeChaine.c: ajouter_chaine] erreur malloc c_tmp\n");
        return 0;
    }
    c_tmp->chaine = malloc(strlen(chaine) + 1);
    if(c_tmp->chaine == NULL) {
        fprintf(stderr, "[listeChaine.c: ajouter_chaine] erreur malloc c_tmp->chaine\n");
        return 0;
    } 
    strcpy(c_tmp->chaine, chaine);
    c_tmp->suiv = NULL;

    //Gestion lorsque c'est la premiere cellule que l'on ajoute
    if((*listeChaine)->tete == NULL) {
        (*listeChaine)->tete = (*listeChaine)->queue = c_tmp;
    } else {
        (*listeChaine)->queue->suiv = c_tmp;
        (*listeChaine)->queue = c_tmp;
    }

    return 1;
}

void afficher_liste_chaine(ListeChaine listeChaine) {
    assert(listeChaine);
    if(listeChaine->tete != NULL) {
        Cellule c_tmp = listeChaine->tete;
        while(c_tmp != NULL) {
            printf("%s\n", c_tmp->chaine);
            c_tmp = c_tmp->suiv;
        }
    } else {
        printf("liste vide\n");
    }
}

int supprimer_chaine(ListeChaine* listeChaine, char* chaine) {
    assert(listeChaine);
    assert(chaine);

    if((*listeChaine)->tete != NULL) {
        Cellule c_tmp_cour = (*listeChaine)->tete;
        Cellule c_tmp_prec = NULL;
        while(c_tmp_cour != NULL) {
            //les deux chaines sont egales
            if(strcmp(c_tmp_cour->chaine, chaine) == 0) {
                if(c_tmp_cour == (*listeChaine)->tete) {//cas de la premiere Cellule
                    (*listeChaine)->tete = c_tmp_cour->suiv;
                } else {
                    c_tmp_prec->suiv = c_tmp_cour->suiv;//on decale la liste chainer
                    if(c_tmp_cour == (*listeChaine)->queue) {
                        (*listeChaine)->queue = c_tmp_prec;
                    }
                }
                free(c_tmp_cour);
                return 1;
            }
            c_tmp_prec = c_tmp_cour;
            c_tmp_cour = c_tmp_cour->suiv;
        }
    } else {
        fprintf(stderr, "[liste_chaine.c: supprimer_chaine] *listeChaine est vide\n");
    }
    return 0;
}

ListeChaine difference(ListeChaine l1, ListeChaine l2) {
    ListeChaine l_tmp;
    if(init_liste_chaine(&l_tmp) == 0) {
        fprintf(stderr, "[liste_chaine.c: difference] initialisation l_tmp non reussi\n");
        return NULL;
    }

    //Parcour de l2
    Cellule c_tmp = l2->tete;
    while(c_tmp != NULL) {
        if(liste_chaine_contains(l1, c_tmp->chaine) == 0) {
            if(ajouter_chaine(&l_tmp, c_tmp->chaine) == 0) {
                fprintf(stderr, "[liste_chaine.c: difference] erreur ajout de c_tmp->chaine dans l1 \n");
                return NULL;
            }
        }
        c_tmp = c_tmp->suiv;
    }

    return l_tmp;
}

int liste_chaine_contains(ListeChaine l1, char* chaine) {
    Cellule c_tmp = l1->tete;
    while(c_tmp != NULL) {
        if(strcmp(c_tmp->chaine, chaine) == 0) {
            return 1;
        }
        c_tmp = c_tmp->suiv;
    }
    return 0;
}

char* get_liste_chaine(ListeChaine liste, int indice) {
    int i = 0;
    Cellule c_tmp = liste->tete;
    while(c_tmp != NULL) {
        if(i == indice){
            return c_tmp->chaine;
        }
        ++i;
        c_tmp = c_tmp->suiv;
    }

    return NULL;
}

int ajouter_chaine_position(ListeChaine* listeChaine, char* chaine, int position) {
    assert(listeChaine);
    assert(chaine);

    if((*listeChaine)->tete != NULL) {
        Cellule c_tmp_cour = (*listeChaine)->tete;
        Cellule c_tmp_prec;
        int i = 0;
        while(c_tmp_cour != NULL) {
            if (i == position) {// on a trouver on l'on souhaite ajouter la chaine
                //creation de la nouvelle cellule
                Cellule c_tmp_new = malloc(sizeof(struct s_cellule));
                if(c_tmp_new == NULL) {
                    fprintf(stderr, "[listeChaine.c: ajouter_chaine_position] erreur malloc c_tmp_new\n");
                    return 0;
                }
                c_tmp_new->chaine = malloc(strlen(chaine) + 1);
                if(c_tmp_new->chaine == NULL) {
                    fprintf(stderr, "[listeChaine.c: ajouter_chaine_position] erreur malloc c_tmp_new->chaine\n");
                    return 0;
                } 
                strcpy(c_tmp_new->chaine, chaine);

                //ajout de la chaine au bonne endroit
                c_tmp_new->suiv = c_tmp_cour;

                if(c_tmp_cour == (*listeChaine)->tete) {
                    (*listeChaine)->tete = c_tmp_new;
                } else {
                    c_tmp_prec->suiv = c_tmp_new;
                }
                return 1;

            } else {//on cherche encore
                c_tmp_prec = c_tmp_cour;
                c_tmp_cour = c_tmp_cour->suiv;
                ++i;
            }
        }

    }

    return ajouter_chaine(listeChaine, chaine);
}

void free_liste_chaine(ListeChaine* listeChaine) {
    assert(listeChaine);
    Cellule c_tmp;
    while((*listeChaine)->tete != NULL) {
        c_tmp = (*listeChaine)->tete;
        (*listeChaine)->tete = (*listeChaine)->tete->suiv;
        free(c_tmp);
    }
    free(*listeChaine);
    *listeChaine = NULL;
}
