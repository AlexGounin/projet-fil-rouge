CC=gcc
CFLAGS=-Wall -Werror -std=c99 -g
EXE=moteur indexation test_repertoire test_image test_texte test_liste_base_descripteur test_descripteur_image test_liste_chaine

all: $(EXE)

test_liste_chaine: test_liste_chaine.o liste_chaine.o

test_repertoire: test_repertoire.o repertoire.o shell.o lecture.o

test_texte: test_texte.o texte.o repertoire.o liste_chaine.o shell.o lecture.o config.o

test_image: test_image.o image.o repertoire.o shell.o lecture.o config.o

test_audio: test_audio.o audio.o repertoire.o liste_chaine.o shell.o lecture.o config.o

test_liste_base_descripteur: test_liste_base_descripteur.o liste_base_descripteur.o liste_chaine.o

test_descripteur_image: test_descripteur_image.o descripteur_image.o image.o config.o lecture.o

test_descripteur_texte: test_descripteur_texte.o descripteur_texte.o liste_chaine.o texte.o	config.o lecture.o

indexation: indexation.o indexation_audio.o indexation_image.o indexation_texte.o descripteur_texte.o descripteur_image.o audio.o image.o texte.o liste_chaine.o config.o liste_base_descripteur.o repertoire.o lecture.o shell.o

moteur: moteur.o recherche_texte.o r_texte.o r_son.o config.o liste_base_descripteur.o shell.o lecture.o liste_chaine.o repertoire.o audio.o

clean:
	rm -f *.o $(EXE)
