#include "config.h"

#include "lecture.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_config_texte(int* nb_car_mot_min, int* nb_car_mot_max) {
    char* home = getenv("HOME");
    char* chemin = concat(2, home, "/.indexation/config_texte.txt");
    FILE* f = fopen(chemin, "r");
    if (f == NULL) {
        perror("lecture config_texte.txt");
        fprintf(stderr, "[config.c: get_config_texte] erreur fopen : %s\n", chemin);
        *nb_car_mot_min = 4;
        *nb_car_mot_max = 10;
    } else {
        if (fscanf(f, "%d", nb_car_mot_min) == -1)
            *nb_car_mot_min = 4;
        
        if (fscanf(f, "%d", nb_car_mot_max) == -1)
            *nb_car_mot_max = 10;
        fclose(f);
    }
    printf(
        "Configuration texte prise (personnalisable dans le fichier \"~/.indexation/config_texte.txt\") : \n"
        "\tNombre minimum de caractère : %d\n"
        "\tNombre maximum de caractère : %d\n",
        *nb_car_mot_min, *nb_car_mot_max);
    free(chemin);
}

void get_config_descripteur_texte(int* seuil, int* nombre_limite) {
    char* home = getenv("HOME");
    char* chemin = concat(2, home, "/.indexation/config_descripteur_texte.txt");
    FILE* f = fopen(chemin, "r");
    if (f == NULL) {
        perror("lecture config_descripteur_texte.txt");
        fprintf(stderr, "[config.c : get_config_descripteur_texte] erreur fopen : %s\n", chemin);
        *seuil = 5;
        *nombre_limite = 10;
        printf("config descripteur texte prise par défaut :\n"
            "\tseuil = 5\n"
            "\tnombre_limite = 10\n");
    } else {
        if (fscanf(f, "%d", seuil) == -1)
            *seuil = 5;
        
        if (fscanf(f, "%d", nombre_limite) == -1)
            *nombre_limite = 10;
        fclose(f);
    }
    printf(
        "Configuration descripteur texte prise (personnalisable dans le fichier \"~/.indexation/config_descripteur_texte.txt\") : \n"
        "\tSeuil : %d\n"
        "\tNombre limite : %d\n",
        *seuil, *nombre_limite);
    free(chemin);
}

void get_config_image(int* pasDeQuantification) {
    char* home = getenv("HOME");
    char* chemin = concat(2, home, "/.indexation/config_image.txt");
    FILE* f = fopen(chemin, "rt");
    if (f == NULL) {
        perror("lecture config_descripteur_texte.txt");
        fprintf(stderr, "[config.c : get_config_image] erreur fopen : %s\n", chemin);
        *pasDeQuantification = 2;
    } else {
        if (fscanf(f, "%d", pasDeQuantification) == -1)
            *pasDeQuantification = 2;
        fclose(f);
    }
    printf(
        "Configuration image prise (personnalisable dans le fichier \"~/.indexation/config_image.txt\") : \n"
        "\tPas de quantification : %d\n",
        *pasDeQuantification);
    free(chemin);
}

void get_config_audio(int* nbEchantillon, int* nbIntervalle) {
    char* home = getenv("HOME");
    char* chemin = concat(2, home, "/.indexation/config_audio.txt");
    FILE* f = fopen(chemin, "rt");
    if (f == NULL) {
        perror("lecture config_descripteur_texte.txt");
        fprintf(stderr, "[config.c : get_config_audio] erreur fopen : %s\n", chemin);
        *nbEchantillon = 1024;
        *nbIntervalle= 50;
    } else {
        if (fscanf(f, "%d", nbEchantillon) == -1)
            *nbEchantillon = 1024;
        
        if (fscanf(f, "%d", nbIntervalle) == -1)
            *nbIntervalle = 50;
        fclose(f);
    }
    printf(
        "Configuration audio prise (personnalisable dans le fichier \"~/.indexation/config_audio.txt\") : \n"
        "\tNombre d'échantillon par fenêtre : %d\n"
        "\tNombre d'intervalle par histogramme %d\n",
        *nbEchantillon, *nbIntervalle);
    free(chemin);
}

char* get_index_mot_clef() {
    char* home = getenv("HOME");
    char* chemin = concat(2, home, "/.indexation/TEXTE/INDEX_MOT_CLEF/index_mot_clef.txt");
    free(home);
    return chemin;
}

char* get_lbd_texte() {
    char* home = getenv("HOME");
    char* chemin = concat(2, home, "/.indexation/TEXTE/LISTE_DESCRIPTEUR/liste_descripteur.txt");
    // free(home);
    return chemin;
}

char* get_lbd_image_ng() {
    char* home = getenv("HOME");
    char* chemin = concat(2, home, "/.indexation/IMG_NG/LISTE_DESCRIPTEUR/liste_descripteur.txt");
    // free(home);
    return chemin;
}

char* get_lbd_image_rgb() {
    char* home = getenv("HOME");
    char* chemin = concat(2, home, "/.indexation/IMG_RGB/LISTE_DESCRIPTEUR/liste_descripteur.txt");
    // free(home);
    return chemin;
}

char* get_lbd_audio() {
    char* home = getenv("HOME");
    char* chemin = concat(2, home, "/.indexation/SON/LISTE_DESCRIPTEUR/liste_descripteur.txt");
    // free(home);
    return chemin;
}

char* get_descripteur_texte(int id) {
    char* home = getenv("HOME");
    char id_char[100];
    sprintf(id_char, "%d.txt", id);
    char* chemin = concat(3, home, "/.indexation/TEXTE/DESCRIPTEURS/", id_char);
    // free(home);
    return chemin;
}

char* get_descripteur_image_ng(int id) {
    char* home = getenv("HOME");
    char id_char[100];
    sprintf(id_char, "%d.txt", id);
    char* chemin = concat(3, home, "/.indexation/IMG_NG/DESCRIPTEURS/", id_char);
    // free(home);
    return chemin;
}

char* get_descripteur_image_rgb(int id) {
    char* home = getenv("HOME");
    char id_char[100];
    sprintf(id_char, "%d.txt", id);
    char* chemin = concat(3, home, "/.indexation/IMG_RGB/DESCRIPTEURS/", id_char);
    // free(home);
    return chemin;
}

char* get_descripteur_audio(int id) {
    char* home = getenv("HOME");
    char id_char[100];
    sprintf(id_char, "%d.txt", id);
    char* chemin = concat(3, home, "/.indexation/SON/DESCRIPTEURS/", id_char);
    // free(home);
    return chemin;
}
