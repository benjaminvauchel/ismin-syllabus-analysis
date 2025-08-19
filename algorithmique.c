#include "algorithmique.h"

int determinerType(Discipline *tabMatieres, const int nbNoeuds) {
	int nbUPs = 0;
	int i;
	for (int id = 1; id <= nbNoeuds; id++) {	// On parcourt chaque noeud
		// Seul cas particulier : la LV2 qui est une UP alors qu'elle ne contient que des majuscules
		if (!strcmp(tabMatieres[id].nom, "LV2")) {
			tabMatieres[id].type = UP;
			nbUPs++;
		}
		else {
			i = 0;
			while (tabMatieres[id].nom[i] != 0) { // On lit la chaine de caractere jusqu'au bout
				if ((tabMatieres[id].nom[i] >= 97) && (tabMatieres[id].nom[i] <= 122)) { // Si on trouve une minuscule, on arrete et on considere que c'est un UP
					tabMatieres[id].type = UP;
					nbUPs++;
					break;
				}
				i++;
			}
		}
	}
	return nbUPs;
}


void compterSommetsIsoles(const Graphe *G, const Discipline *tabMatieres, int *UPIsoles, int *GPIsoles) {
	*UPIsoles = 0;
	*GPIsoles = 0;
	for (int i = 1; i <= G->nbSommets; i++) {
		if ((G->matAdjacence[i][0] == 0) && (G->matAdjacence[0][i] == 0)) {
			if (tabMatieres[i].type == UP) {
				++*UPIsoles;
			}
			else {
				++*GPIsoles;
			}
		}
	}
}

void visiterGraphe(const Graphe *G, int *tabCompoConnexes, const int sommet, const int composanteConnexe) {
	//printf("%d, ", sommet);

	tabCompoConnexes[sommet] = composanteConnexe;			// On marque le sommet

	for (int i = 1; i <= G->nbSommets; i++) {
		if ((G->matAdjacence[sommet][i] == 1) && (tabCompoConnexes[i] == 0)) { // On parcourt les successeurs
			visiterGraphe(G, tabCompoConnexes, i, composanteConnexe);
		}
		if ((G->matAdjacence[i][sommet] == 1) && (tabCompoConnexes[i] == 0)) { // On parcourt les predecesseurs
			visiterGraphe(G, tabCompoConnexes, i, composanteConnexe);
		}
	}
}

int compterCompoConnexes(const Graphe* G, int *tabCompoConnexes) {
	int nbCompoConnexes = 0;
	for (int sommet = 1; sommet <= G->nbSommets; sommet++) {
		if (tabCompoConnexes[sommet] == 0) {
			visiterGraphe(G, tabCompoConnexes, sommet, ++nbCompoConnexes);
		}
	}
	enregistrerTabMarque("tabCompoConnexes.txt", G, tabCompoConnexes);
	return nbCompoConnexes;
}

void construireGraphePrecedence(const Graphe *G, Graphe *GPrec, const Discipline *tabMatieres) {
	initGraphe(GPrec, G->nbSommets);
	for (int i = 1; i <= G->nbSommets; i++) {
		for (int j = 1; j <= G->nbSommets; j++) {
			if (tabMatieres[i].x != tabMatieres[j].x) {
				if (G->matAdjacence[i][j]) {
					if (tabMatieres[i].x < tabMatieres[j].x) {
						GPrec->matAdjacence[i][j] = 1;
					}
					else {
						GPrec->matAdjacence[j][i] = 1;
					}
				}
			}
		}
	}
}


void tableauToListe(const int *tab, const int taille, ListeDisciplines *liste, const Discipline *tabMatieres) {
	for (int i = taille; i >= 0; i--) {
		if (tab[i] != 0) {
			ajouterDisc(liste, tabMatieres[tab[i]], tab[i]);
		}
	}
}

void explore(const Graphe *G, int *chemin, bool *tabMarque, const int position, const int profondeur, const Discipline *tabMatieres, ListeDisciplines **chemins, int *k) {
	chemin[profondeur] = position;
	tabMarque[position] = true;

	if (G->matAdjacence[position][0] == 0) {
		tableauToListe(chemin, profondeur, chemins[(*k)], tabMatieres);
		//afficherListeDisc(chemins[*k]);
		++*k;
		chemins[*k] = (ListeDisciplines *) malloc(sizeof(ListeDisciplines));
		initListeDisc(chemins[*k]);
	}
	else {
		for(int i=1; i <= G->nbSommets; i++) {
			if ((G->matAdjacence[position][i] == 0) || (tabMarque[i])) continue;
			explore(G, chemin, tabMarque, i, profondeur + 1, tabMatieres, chemins, k);
		}
	}
	tabMarque[position] = false;
}


// Renvoie le nombre de chemins elementaires
int explorerTousCheminsElem(const Graphe *G, ListeDisciplines **chemins, const Discipline *tabMatieres) {
	int k = -1;
	bool *tabMarque = (bool *) malloc(G->nbSommets * sizeof(bool));
	int *chemin = (int *) malloc(G->nbSommets * sizeof(int));
	
	for (int position = 1; position <= G->nbSommets; position++) {
		for (int j = 1; j <= G->nbSommets; j++) {
			tabMarque[j] = 0;
			chemin[j] = 0;
		}
		if (G->matAdjacence[0][position] == 0) {
			k++;
			chemins[k] = (ListeDisciplines *) malloc(sizeof(ListeDisciplines));
			initListeDisc(chemins[k]);
			explore(G, chemin, tabMarque, position, 0, tabMatieres, chemins, &k);
		}
	}
	return k;
}

void plusLonguesSeq(ListeDisciplines **chemins, const int taille) {
	int longueurMax = 0;
	int *longueurs = (int *) calloc(taille, sizeof(int));
	for (int i = 0; i < taille; i++) {
		longueurs[i] = compterDisc(chemins[i]);
		longueurMax = max(longueurMax, longueurs[i]);
	}
	for (int i = 0; i < taille; i++) {
		if (longueurs[i] == longueurMax) {
			afficherListeDisc(chemins[i]);
		}
	}
}

