#include "recherche_texte.h"
//#include "fonctions_communes"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_cellule * Cellule;

struct s_cellule {
    int apparition;
    char id[20];
    Cellule suiv;
};

struct s_liste {
    int nbrElement;
    Cellule tete;
    Cellule queue;
};


void afficher_liste(Liste listeChaine) {
    assert(listeChaine);
    if(listeChaine->tete != NULL) {
        Cellule c_tmp = listeChaine->tete;
        while(c_tmp != NULL) {
            printf("%s / %d\n", c_tmp->id,c_tmp->apparition);
            c_tmp = c_tmp->suiv;
        }
    } else {
        printf("liste vide\n");
    }
}

int init_liste(Liste *l){
    *l = (Liste) malloc(sizeof(struct s_liste));      //on alloue une case mémoire a notre liste chainée
    if(l == NULL){
        perror("[liste_base_descripteur.c]init_lbd");
        return 0;
    }
    (*l)->nbrElement = 0;
    (*l)->tete = NULL;
    (*l)->queue = NULL;

    return 1;
}

int ajouter_liste(Liste *l, char* _id, int _apparition){
    Cellule nouvelle = (Cellule) malloc(sizeof(struct s_cellule));
    Cellule courrante = (*l)->tete;
    Cellule precedent = NULL;
    int add = 0;

    if (nouvelle == NULL) {
        perror("[liste_base_descripteur.c]ajouter_lbd");
        return 0;
    }
    
    strcpy(nouvelle->id, _id);
    nouvelle->apparition = _apparition;
    nouvelle->suiv = NULL;

    if ((*l)->tete == NULL) {
        (*l)->tete = (*l)->queue = nouvelle;
        (*l)->nbrElement = (*l)->nbrElement+1;
        
        return 1;
    }else{
        /* on empile dans queue */
        while((courrante != NULL) && (add == 0)){
            if(courrante->apparition >= _apparition){
                add = 1;
            }           
            precedent = courrante;
            courrante = courrante->suiv;
        }

        nouvelle->suiv = courrante;
        precedent->suiv = nouvelle;
        (*l)->nbrElement = (*l)->nbrElement+1;
        return 1;
    }
}

char liste_Vide(Liste l){
    return (l->tete == NULL);
}

void free_liste(Liste *l){
    assert(l);
    Cellule c_tmp;
    while((*l)->tete != NULL) {
        c_tmp = (*l)->tete;
        (*l)->tete = (*l)->tete->suiv;
        free(c_tmp);
    }
    free(*l);
}

//int rechercheParDocumentTexte(){

//}

int rechercheParNomDeFichierTexte(char* chemin) {

    printf("Veuillez entrer le nom de fichier a chercher : ");
    char cmde[256];
    char* motChercher = lireClavier();
    //viderBuffer();
    printf("\n");

    sprintf(cmde,"grep %s %s | cut -d / -f 2", motChercher,chemin); 
    system(cmde);
    printf("\n");
    printf("Recherche terminée\n");
    return 1;
}

int rechercheParMotClefTexte() {
    int apparition=0;
    int comp = 0; 
    
    Liste l;
    init_liste(&l);

    /* chercher dans index_mot_clef.txt si le mot existe dans les fichiers */
    /* s'il existe, rechercher grace a l'identifiant dans liste_base_descripteur le nom du fichier */
    printf("Veuillez entrer le mot clef a chercher : ");
    
    viderBuffer();
    char* motChercher = lireClavier();
    printf("mot lu\n");
    
    //ouvre le fichier qui contient tous les mots clef
    FILE *index = fopen("TEXTE/INDEX_MOT_CLEF/index_mot_clef.txt","r");
    if(index == NULL){
        fprintf(stderr, "[recherche_texte: rechercheParMotClefTexte] erreur fopen\n");
        return 0;
    }
    //On regarde si le mot clé est présent dans index_mot_clef.txt
    int retourScan = 0, n=0;
    char motLu[100];
    do {
        retourScan = fscanf(index, "%s", motLu);
        n++;
        //comp = strcmp(motLu, motChercher);
    } while((retourScan != EOF) && (strcmp(motLu, motChercher) != 0));
    printf("recherche finie, dernier mot lu : %s\n",motLu);
    
    //On lit l'id des fichier où apparaissent ce mot clef, ainsi que le nombre d'apparition
    char _id[10];
    Cellule celluleCour = NULL;
    if(strcmp(motLu, motChercher) == 0){
        do{
            retourScan = fscanf(index, "%s", _id);
            printf("id lu : %s\n",_id);
            comp = strcmp("-1", _id);
            printf("comp id = -1 : %d\n",comp);
            if(comp != 0) {
                retourScan = fscanf(index,"%d",&apparition);
                printf("apparition lu : %d\n\t scanf : %d\n",apparition,retourScan);
                if(retourScan != EOF){
                    ajouter_liste(&l,_id,apparition);
                    
                }
            }
        }while((strcmp("-1", _id) != 0) && (retourScan != EOF));
        printf("mot trouvé, pile actualisée\n");

        celluleCour = l->tete;
        printf("NULL %d\n",celluleCour == NULL);
        afficher_liste(l);
        printf("plante ici ?");
        
        char cmde[256];
        while(celluleCour != NULL){
            printf("passe dans while");
            //executer_commande(3, "grep ", _id, "TEXTE/LISTE_BASE_DESCRIPTEUR/liste_base_descripteur.txt | cut -d / -f 2");    
            sprintf(cmde, "grep %s TEXTE/LISTE_BASE_TEXTE/liste_base_descripteur.txt | cut -d / -f 2", _id);
            system(cmde);
            celluleCour = celluleCour->suiv;
        }
    }else{
        printf("Aucun fichier ne correspond\n\n");
    }
    
    fclose(index);
    printf("fichier fermé\n");
    /* donner le résultat */
    celluleCour = l->tete;
    

    printf("\n");

    return 1;
}