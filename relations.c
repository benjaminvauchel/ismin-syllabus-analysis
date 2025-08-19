#include "relations.h"

int calculerDegres(Graphe *G) {
	int nbAretes = 0;
	for (int i = 1; i <= G->nbSommets; i++) {
		for (int j = 1; j <= G->nbSommets; j++) {
			if (G->matAdjacence[i][j]) {
				++G->matAdjacence[i][0];
				++G->matAdjacence[0][j];
				nbAretes++;
			}
		}
	}
	G->matAdjacence[0][0] = nbAretes;
	return nbAretes;
}

void creerTabNbRelations(const Graphe *G, int *nbRelations) {
	for (int id = 1; id <= G->nbSommets; id++) {
		nbRelations[id] = G->matAdjacence[id][0] + G->matAdjacence[0][id];
	}
}

void trierTabMatieres(const Graphe *G, const Discipline *tabMatieres, ListeDisciplines *listeTriee, const int *nbRelations) {
	ajouterDisc(listeTriee, tabMatieres[1], 1);
	for (int i = 2; i <= G->nbSommets; i++) {
		if (tabMatieres[i].type == UP) {
			NoeudDiscipline *nouveau = (NoeudDiscipline *) malloc(sizeof(NoeudDiscipline));
			nouveau->id = i;
			nouveau->disc = tabMatieres[i];
			NoeudDiscipline *courant = listeTriee->tete;
			NoeudDiscipline *precedent = listeTriee->tete;

			while ((courant != NULL) && (nbRelations[i] < nbRelations[courant->id])) {
				precedent = courant;
				courant = courant->suiv;
			}
			if (courant == listeTriee->tete) {
				ajouterDisc(listeTriee, tabMatieres[i], i);
			}
			else {
				precedent->suiv = nouveau;
				nouveau->suiv = courant;
			}
		}
	}
}


void calculerDegresEntrant(const Graphe *G, const Discipline *tabMatieres, ListeDisciplines *listeMin, ListeDisciplines *listeMax, int *degMin, int *degMax) {
	initListeDisc(listeMin);
	initListeDisc(listeMax);
	*degMin = *degMax = 0;
	
	for (int j = 1; j <= G->nbSommets; j++) {
		*degMin = min(G->matAdjacence[0][j], *degMin);
		*degMax = max(G->matAdjacence[0][j], *degMax);
	}
	for (int j = 1; j <= G->nbSommets; j++) {
		if (G->matAdjacence[0][j] == *degMin) {
			ajouterDisc(listeMin, tabMatieres[j], j);
		}
		if (G->matAdjacence[0][j] == *degMax) {
			ajouterDisc(listeMax, tabMatieres[j], j);
		}
	}
}

void calculerDegresSortant(const Graphe *G, const Discipline *tabMatieres, ListeDisciplines *listeMin, ListeDisciplines *listeMax, int *degMin, int *degMax) {
	initListeDisc(listeMin);
	initListeDisc(listeMax);
	*degMin = *degMax = 0;
	
	for (int i = 1; i <= G->nbSommets; i++) {
		*degMin = min(G->matAdjacence[i][0], *degMin);
		*degMax = max(G->matAdjacence[i][0], *degMax);
	}
	for (int i = 1; i <= G->nbSommets; i++) {
		if (G->matAdjacence[i][0] == *degMin) {
			ajouterDisc(listeMin, tabMatieres[i], i);
		}
		if (G->matAdjacence[i][0] == *degMax) {
			ajouterDisc(listeMax, tabMatieres[i], i);
		}
	}
}
