#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    chdir("../ARBORESCENCE");
    Image image;
    Fichier f;
    strcpy(f.nom, "IMG_RGB/02.txt");
    f.fichier = fopen("IMG_RGB/02.txt", "r");
    init_image(&image, f);
    afficher_image(image);
    free_image(&image);
    return 0;
}
