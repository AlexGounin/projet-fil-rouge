#include "indexation_texte.h"

#include "texte.h"
#include "config.h"
#include "liste_base_descripteur.h"
#include "liste_chaine.h"
#include "descripteur_texte.h"
#include "repertoire.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>

int indexer_texte() {
    // liste_image = creer_liste_image
    // tant que il reste des images
        // loader l'image avec la structure image
        // ecrire descripteur de l'image
        // ajouter l'image liste_base_image
    // fin tant que
    printf(
        "*********************************\n"
        "*        INDEXATION TEXTE       *\n"
        "*********************************\n");
    int nbMinCar, nbMaxCar;
    get_config_texte(&nbMinCar, &nbMaxCar);
    int seuil, nombreLimite;
    get_config_descripteur_texte(&seuil, &nombreLimite);
    int err;
    Repertoire r;
    if (init_repertoire(&r, "*.xml", "rt") == 0) {
        fprintf(stderr, "[indexationTexte] erreur init_repertoire");
        return 0;
    }
    Fichier f;
    Texte t;
    LBD lbd;
    char* cheminLbd = get_lbd_texte();
    if (init_lbd(&lbd, cheminLbd) == 0) return 0;

    char* cheminDescripteur;
    int id;
    ListeChaine l = get_fichier_indexer(lbd);
    int nbFichierIndexer = 0;
    while (prochain_fichier(r, &f) != -1) {
        if (!liste_chaine_contains(l, f.nom)) {
            printf("Indexation de : %s\n", f.nom);
            err = init_texte(&t, f, nbMinCar, nbMaxCar);
            if (err == 0) {
                fprintf(stderr, "Erreur lors de l'initialisation du texte %s.\n", f.nom);
            } else {
                id = prochain_id_lbd(lbd);

                cheminDescripteur = get_descripteur_texte(id);
                if (creation_descripteur_texte(id, &t, cheminDescripteur, seuil, nombreLimite) == 0) {
                    fprintf(stderr, "[indexation_texte: indexer_texte] erreur creation_descripteur_texte, id: %d\n", id);
                }
                
                ajouter_lbd(&lbd, f.nom);
                free_texte(&t);
                nbFichierIndexer++;
            }
        }
    }
    if (nbFichierIndexer == 0) {
        printf("Aucun nouveau fichier à indexer.\n");
    }
    ecrire_lbd(lbd);
    
    free(cheminLbd);
    free_lbd(&lbd);
    free_repertoire(&r);
    free_liste_chaine(&l);
    return 1;
}
