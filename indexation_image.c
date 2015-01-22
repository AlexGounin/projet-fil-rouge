#include "indexation_image.h"

#include "image.h"
#include "shell.h"
#include "config.h"
#include "liste_base_descripteur.h"
#include "liste_chaine.h"
#include "descripteur_image.h"
#include "repertoire.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>

int indexer_image(int ng) {
    // liste_image = creer_liste_image
    // tant que il reste des images
        // loader l'image avec la structure image
        // ecrire descripteur de l'image
        // ajouter l'image liste_base_image
    // fin tant que
    printf(
        "*********************************\n"
        "*        INDEXATION IMAGE       *\n"
        "*********************************\n");
    int pasDeQuantification;
    get_config_image(&pasDeQuantification);
    int err;
    Repertoire r;
    err = init_repertoire(&r, "*.txt", "rt");
    if (err == 0) {
        fprintf(stderr, "[indexation_image: indexer_image] erreur init_repertoire\n");
        return 0;
    }
    Fichier f;
    Image i;
    LBD lbd;
    char* cheminLbd;
    if (ng)
        cheminLbd = get_lbd_image_ng();
    else
        cheminLbd = get_lbd_image_rgb();
    if (init_lbd(&lbd, cheminLbd) == 0) return 0;

    char* cheminDescripteur;
    int id;

    ListeChaine l = get_fichier_indexer(lbd);
    int nbFichierIndexe = 0;
    while (prochain_fichier(r, &f) != -1) {
        if (!liste_chaine_contains(l, f.nom)) {
            printf("Indexation de : %s\n", f.nom);
            err = init_image(&i, f);
            if (err == 0) {
                fprintf(stderr, "Erreur lors de l'initialisation de l'image %s.\n", f.nom);
            } else {
                id = prochain_id_lbd(lbd);
                if (i->nbComposante == 1) {
                    cheminDescripteur = get_descripteur_image_ng(id);
                } else {
                    cheminDescripteur = get_descripteur_image_rgb(id);
                }
                if (creation_descripteur_image(id, &i, cheminDescripteur, pasDeQuantification) == 0) {
                    fprintf(stderr, "[indexation_image: indexer_image] erreur creation_descripteur_image, id: %d\n", id);
                }
                
                ajouter_lbd(&lbd, f.nom);

                free(cheminDescripteur);
                free_image(&i);
                nbFichierIndexe++;
            }
        }
    }
    if (nbFichierIndexe == 0)
        printf("Aucun nouveau fichier à indexer.\n");
    ecrire_lbd(lbd);

    free_liste_chaine(&l);
    free_lbd(&lbd);
    free_repertoire(&r);
    free(cheminLbd);
    return 1;
}

int indexer_image_ng() {
    return indexer_image(1);
}

int indexer_image_rgb() {
    return indexer_image(0);
}
