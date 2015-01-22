#include "r_son.h"

#include "audio.h"
#include "repertoire.h"
#include "liste_base_descripteur.h"
#include "config.h"

#define TAILLE_MAX_NOM 1024

void comparerFichierSon(FILE* corpus, FILE* requete, char* cheminFichier) {

}

void rechercherUnSon() {
    int nbEchantillon, nbIntervalle;
    get_config_audio(&nbEchantillon, &nbIntervalle);

    Fichier f;
    printf("Requête son (jingle) : ");
    scanf("%1024s", f.nom);

    f.fichier = fopen(f.nom, "r");
    if (f.fichier == NULL) {
        perror("[r_son]rechercherUnSon");
        fprintf(stderr, "Erreur lors de l'ouverture de %s\n", f.nom);
        return;
    }
    indexer_fichier_audio(f, nbEchantillon, nbIntervalle, 0, "fichier_tmp");

    LBD lbd;
    char* cheminLBD = get_lbd_audio();
    if (init_lbd(&lbd, cheminLBD) == 0) {
        fprintf(stderr, "L'indexation audio doit être effectué avant la recherche.\n");
        return;
    }
    ListeChaine l = get_fichier_indexer(lbd);
    char* fichierIndexer;
    char* cheminDescripteur;
    for (int i = 0; (fichierIndexer = get_liste_chaine(l, i)) != NULL; ++i) {
        printf("Comparaison avec %s\n", fichierIndexer);
        cheminDescripteur = get_descripteur_audio(i);
        FILE* corpus = fopen(cheminDescripteur, "r");
        if (corpus == NULL) {
            perror("[r_son.c: fopen]");
            fprintf(stderr, "Erreur ouverture %s\n", cheminDescripteur);
        }
        comparerFichierSon(corpus, f.fichier, fichierIndexer);
    }

    free(cheminLBD);
    free_liste_chaine(&l);
    free_lbd(&lbd);

    fclose(f.fichier);
    remove("fichier_tmp");
}
