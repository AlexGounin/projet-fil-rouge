#include "liste_chaine.h"

int main() {
    ListeChaine liste;
    ListeChaine l1;

    //test init
    if(init_liste_chaine(&liste) == 0) {
        fprintf(stderr, "[test_liste_chaine.c: main] Erreur sur init_liste_chaine\n");
    }
    if(init_liste_chaine(&l1) == 0) {
        fprintf(stderr, "[test_liste_chaine.c: main] Erreur sur init_liste_chaine\n");
    }

    afficher_liste_chaine(liste);

    char tab[10];
    for(int i = 2; i < 6; i++) {
        sprintf(tab, "coucou %d", i+1);
        if(ajouter_chaine(&liste, tab)){

        }
    }

    for(int i = 0; i < 8; i++) {
        sprintf(tab, "coucou %d", i+1);
        if(ajouter_chaine(&l1, tab)) {

        }
    }

    printf("chaine: %s\n", get_liste_chaine(l1, 3));
    // if(liste_chaine_contains(liste, "coucou 3") == 0) {
    //  fprintf(stderr, "[test_liste_chaine.c: main] Erreur sur copier_liste_chaine\n");
    // } else {
    //  printf("la chaine est contenue dans la liste\n");
    // }
    ListeChaine l2 = difference(liste, l1);
    printf("liste:\n");
    afficher_liste_chaine(liste);
    printf("l1:\n");
    afficher_liste_chaine(l1);
    printf("l2:\n");
    afficher_liste_chaine(l2);

    // if(supprimer_chaine(&liste, "coucou 5") == 0) {
    //  printf("chaine non supprimer\n");
    // } else {
    //  printf("chaine suppr\n");
    // }
    // free_liste_chaine(&liste);

    // afficher_liste_chaine(liste);

    return 0;

}
