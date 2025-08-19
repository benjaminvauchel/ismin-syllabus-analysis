#include "display.h"

void afficherTabMatieres(const Discipline *tabMatieres, const int nbNoeuds) {
	for (int id = 1; id <= nbNoeuds; id++) {
        printf("id = %d, x = %d, y = %d, nom = %s\n", id, tabMatieres[id].x, tabMatieres[id].y, tabMatieres[id].nom);
    }
}

void afficherMatCorrespondance(const int **matCorrespondance, const int nbSemestres, const int yMax) {
	for (int sem = 1; sem <= nbSemestres; sem++) {
		for (int y = 1; y < yMax; y++) {
			printf("%d ", matCorrespondance[sem][y]);
		}
		printf("\n");
	}
}

void afficherMatAdjacence(const Graphe *G) {
	int start = (G->matAdjacence[0][0] > 0) ? 0 : 1; // Si les degres ont ete calcules, on les affiche.
    for (int i = start; i <= G->nbSommets; i++) {
        for (int j = start; j <= G->nbSommets; j++) {
            printf("%d ", G->matAdjacence[i][j]);
        }
        printf("\n");
    }
}

void afficherListeDiscEntier(const ListeDisciplines *liste) {
	NoeudDiscipline *courant = liste->tete;
	while (courant != NULL) {
		printf("%d %d %d %s\n", courant->id, courant->disc.x, courant->disc.y, courant->disc.nom);
		courant = courant->suiv;
	}
}


void afficherTopNbRelations(const Graphe *G, const ListeDisciplines *listeTriee, const int *nbRelations, const int n) {
	printf("nombre de relations\tnom de l'UP\n");
	NoeudDiscipline *courant = listeTriee->tete;
	int i = 1;
	int total = min(G->nbSommets, n);
	while ((courant != NULL) && (i++ <= total)) {
		printf("%d\t\t\t%s\n", nbRelations[courant->id], courant->disc.nom);
		courant = courant->suiv;
	}
}

void afficherChaines(ListeDisciplines **chaines, const int taille) {
	for (int i = 0; i < taille; i++) {
		NoeudDiscipline *courant = chaines[i]->tete;
		if (courant != NULL) {
			printf("%d ", courant->id);		
			while (courant->suiv != NULL) {
				courant = courant->suiv;
				printf("-> %d ", courant->id);
			}
			if (chaines[i]->tete != NULL)
				printf("\n");
		}
	}
}
