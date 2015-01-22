#include "descripteur_image.h"

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * test le bon fonctionnement du module image et descripteur_image
 */
int main() {
    chdir("../ARBORESCENCE");
	//Gestion de l'image
	Image image;
    Fichier f;
    strcpy(f.nom, "IMG_RGB/01.txt");
    f.fichier = fopen(f.nom, "r");
    if (f.fichier == NULL) {
        perror(f.nom);
        return 1;
    }
    if(0 == init_image(&image, f)) {
    	printf("erreur init image\n");
    	return 0;
    }

    if(!creation_descripteur_image(5, &image, get_descripteur_image_rgb(0), 2)) {
    	fprintf(stderr, "erreur sur la creation d'un descripteur_image\n");
    	return 0;
    }

    // printf("test puissance: %d\n", puissance(2, 6));
    // printf("image 1:\n");
    // afficher_image(image);

    // quantification_image(&image, 3);

    // printf("image 2 quantifier:\n");
    // afficher_image(image);

    // int tab[puissance(2, (image->nbComposante * 3))];
    // histogramme_image(image, tab, 3);

    // printf("tab\n");
    // for(int i = 0; i < puissance(2, (image->nbComposante * 3)); i++)
    // 	printf("%d\n", tab[i]);
    
    // modif_image_histogramme(&image, 2);
    // afficher_image(image);

    return 0;
}
