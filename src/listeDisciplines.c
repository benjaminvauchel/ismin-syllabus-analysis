#include "listeDisciplines.h"

void initListeDisc(ListeDisciplines *liste) {
	liste->tete = NULL;
}

void ajouterDisc(ListeDisciplines *liste, const Discipline disc, const int id) {
	NoeudDiscipline *noeud = (NoeudDiscipline *) malloc(sizeof(NoeudDiscipline));
	noeud->id = id;
	noeud->disc = disc;
	noeud->suiv = liste->tete;
	liste->tete = noeud;
}

int popListeDisc(ListeDisciplines *liste) {
	NoeudDiscipline *premier = liste->tete;
	if (premier != NULL) {
		liste->tete = liste->tete->suiv;
		free(premier);
		premier = NULL;
		return 0;
	}
	return -1;
}

void freeListeDisc(ListeDisciplines *liste) {
 	while (!popListeDisc(liste)) {}
    if (liste != NULL) {
        free(liste);
        liste = NULL;
    }
}

void afficherListeDisc(const ListeDisciplines *liste) {
	NoeudDiscipline *courant = liste->tete;
	while (courant != NULL) {
		printf("%d -> ", courant->id);
		courant = courant->suiv;
	}
	printf("NULL\n");
}

int compterDisc(const ListeDisciplines *liste) {
	int n = 0;
	NoeudDiscipline *courant = liste->tete;
	while (courant != NULL) {
		courant = courant->suiv;
		n++;
	}
	return n;
}
