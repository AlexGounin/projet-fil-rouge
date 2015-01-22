#include "descripteur_image.h"

#include "config.h"

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int creation_descripteur_image(int id, Image *image, char *chemin, int pasDeQuantification) {
    assert(image);
    assert(chemin);

    quantification_image(image, pasDeQuantification);
    // afficher_image(*image);
    int max = puissance(2, ((*image)->nbComposante * pasDeQuantification));
    int tab[max];
    histogramme_image(*image, tab, pasDeQuantification);

    FILE *f = fopen(chemin, "w+");
    if(f == NULL) {
        perror("[descripteur_image:creation] fopen");
        fprintf(stderr, "[descripteur_image.c: creation_descripteur_image] erreur fopen %s\n", chemin);
        return 0;
    }
    //ecriture de l'id dans le fichier
    fprintf(f, "%d\n", id);

    for (int i = 0; i < max; ++i) {
        fprintf(f, "%d\n", tab[i]);
    }

    fclose(f);
    return 1;
}

void quantification_image(Image *image, int pasDeQuantification) {
    assert(image);

    if(pasDeQuantification <= 0 || pasDeQuantification > 8) {
        fprintf(stderr, "[descripteur_image.c: quantification_image] pasDeQuantification: %d non conforme\n", pasDeQuantification);
        pasDeQuantification = 2;
    }
    int taille = (*image)->hauteur * (*image)->largeur;
    unsigned char masque = 255 << (8 - pasDeQuantification);
    if ((*image)->nbComposante == 3) {
        /* parcours de tout les pixels */
        for (int i = 0; i < taille; ++i) {
            /* décalage pour chaque composante */
            for (int cmp = 0; cmp < (*image)->nbComposante; ++cmp) {
                // printf("cmp : %d valeur : %d -> ", cmp, (*image)->pixel[cmp][i]);
                (*image)->pixel[cmp][i] = ((*image)->pixel[cmp][i] & masque) >> ((cmp + 1) * pasDeQuantification);
                // printf("%d\n", (*image)->pixel[cmp][i]);
            }
            
            /* construction du pixel quantifié sur la composante ROUGE */
            for (int cmp = 0; cmp < (*image)->nbComposante; ++cmp)
                (*image)->pixel[ROUGE][i] = (*image)->pixel[ROUGE][i] | (*image)->pixel[cmp][i];
        }
    } else {
        for (int i = 0; i < taille; ++i)
        {
            (*image)->pixel[0][i] = ((*image)->pixel[0][i] & masque) >> (3 * pasDeQuantification);
        }
    }
}

void histogramme_image(Image image, int *tab, int pasQuantification) {
    assert(tab);

    int max = puissance(2, (image->nbComposante * pasQuantification));
    //init du tableau au valeur 0
    for(int i = 0; i < max; i++) {
        tab[i] = 0;
    }
    // if(image->nbComposante == 3){
    //     modif_image_histogramme(&image, pasQuantification);
    // }
    int taille = image->hauteur * image->largeur;
    /* parcourt de toutes les valeurs possible */
    for (int valeur = 0; valeur < max; ++valeur)
        /* parcours de tout les pixels pour compter le nombre d'occurence de valeur */
        for (int numPixel = 0; numPixel < taille; ++numPixel)
            if(image->pixel[ROUGE][numPixel] == valeur)
                ++tab[valeur];
}

// void modif_image_histogramme(Image *image, int pasQuantification) {
//     assert(image);
//     int num_tmp;
//     for (int numPixel = 0; numPixel < (*image)->hauteur * (*image)->largeur; ++numPixel)
//     {
//         num_tmp = 0;
//         for (int composante = 0; composante < (*image)->nbComposante ; ++composante)
//         {
//             num_tmp += (*image)->pixel[composante][numPixel] << ((*image)->nbComposante - 1 - composante);
//         }
//         (*image)->pixel[ROUGE][numPixel] = num_tmp;
//     }
//     (*image)->nbComposante = 1;
// }

int puissance(int a, int b) {
    if(b != 0) {
        int sum = 1;
        for(int i = 0; i < b; i++) {
            sum *= a;
        }
        return sum;
    } else {
        return 1;
    }
}
