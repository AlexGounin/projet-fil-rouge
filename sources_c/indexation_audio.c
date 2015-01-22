#include "indexation_image.h"

#include "audio.h"
#include "config.h"
#include "liste_base_descripteur.h"
#include "liste_chaine.h"
#include "repertoire.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>

int indexer_audio() {
    // liste_image = creer_liste_image
    // tant que il reste des images
        // loader l'image avec la structure image
        // ecrire descripteur de l'image
        // ajouter l'image liste_base_image
    // fin tant que
    printf(
        "*********************************\n"
        "*        INDEXATION AUDIO       *\n"
        "*********************************\n");
    int nbEchantillon, nbIntervalle;
    get_config_audio(&nbEchantillon, &nbIntervalle);

    Repertoire r;
    if (init_repertoire(&r, "*.bin", "rb") == 0) {
        fprintf(stderr, "[indexation_audio] erreur init_repertoire");
        return 0;
    }
    Fichier f;

    char* cheminLbd = get_lbd_audio();
    char* cheminDescripteur;
    int id;
    LBD lbd;
    if (init_lbd(&lbd, cheminLbd) == 0) return 0;

    ListeChaine l = get_fichier_indexer(lbd);
    int nbFichierIndexe = 0;
    while (prochain_fichier(r, &f) != -1) {
        if (!liste_chaine_contains(l, f.nom)) {
            printf("Indexation de : %s\n", f.nom);
            id = prochain_id_lbd(lbd);
            cheminDescripteur = get_descripteur_audio(id);
            indexer_fichier_audio(f, nbEchantillon, nbIntervalle,id, cheminDescripteur);
            nbFichierIndexe++;
            ajouter_lbd(&lbd, f.nom);
            free(cheminDescripteur);
        }
    }
    if (nbFichierIndexe == 0)
        printf("Aucun nouveau fichier à indexer.\n");
    ecrire_lbd(lbd);

    free(cheminLbd);
    free_liste_chaine(&l);
    free_lbd(&lbd);
    free_repertoire(&r);
    return 1;
}
