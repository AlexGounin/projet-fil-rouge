#include "liste_base_descripteur.h"
#include "liste_chaine.h"

#include <stdlib.h>


int main(int argc, char *argv[])
{
    system("touch test.txt");
    LBD mylbd;
    ListeChaine myListeChaine;

    init_lbd(&mylbd, "test.txt");
    init_liste_chaine(&myListeChaine);

    
    ajouter_lbd(&mylbd, "terre");
    ajouter_lbd(&mylbd, "lune");

    ecrire_lbd(mylbd);

    ajouter_lbd(&mylbd, "eau");
   	ajouter_lbd(&mylbd, "feu");
    ecrire_lbd(mylbd);

    myListeChaine = get_fichier_indexer(mylbd);
    afficher_liste_chaine(myListeChaine);

    free_lbd(&mylbd);

    remove("test.txt");
    return 0;
}
