#include "export.h"

int dossierExiste(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0 && (st.st_mode & S_IFDIR)) {
        return 1;
    }
    return 0;
}

void creerDossier(const char *path) {
	#ifdef _WIN32
		if (!dossierExiste(path)) {
			if (_mkdir(path) != 0) {
				perror("Erreur lors de la creation du dossier.");
			} else {
				printf("Dossier cree avec succes.\n");
			}
		}
	#else
		if (!dossierExiste(path)) {
			if (mkdir(path, 0777) != 0) {
				perror("Erreur lors de la creation du dossier.");
			} else {
				printf("Dossier cree avec succes.\n");
			}
		}
	#endif
}


void enregistrerTabMatieres(const char *nomFichier, const Discipline *tabMatieres, const int nbNoeuds) {
	creerDossier(OUTPUT_DIR);
	char path[TAILLE_MAX];
	snprintf(path, sizeof(path), "%s%s", OUTPUT_DIR, nomFichier);
	FILE *fichier = fopen(path, "w");

	if (fichier != NULL) {
		for (int id = 1; id <= nbNoeuds; id++) {
			if (tabMatieres[id].type == GP) {
				fprintf(fichier, "%d,%d,%d,GP,%s\n", id, tabMatieres[id].x, tabMatieres[id].y, tabMatieres[id].nom);
			}
			else {
				fprintf(fichier, "%d,%d,%d,UP,%s\n", id, tabMatieres[id].x, tabMatieres[id].y, tabMatieres[id].nom);
			}
		}
	fclose(fichier);
	}
	else {
		printf("Fichier introuvable.\n");
	}
}

void enregistrerMatCorrespondance(const char *nomFichier, int **matCorrespondance, const int nbSemestres, const int yMax) {
	creerDossier(OUTPUT_DIR);
	char path[TAILLE_MAX];
	snprintf(path, sizeof(path), "%s%s", OUTPUT_DIR, nomFichier);
	FILE *fichier = fopen(path, "w");

	if (fichier != NULL) {
		for (int x = 1; x <= nbSemestres; x++) {
			for (int y = 1; y < yMax; y++) {
				fprintf(fichier, "%d,", matCorrespondance[x][y]);
			}
			fprintf(fichier, "\n");
		}
	fclose(fichier);
	}
	else {
		printf("Fichier introuvable.\n");
	}
}

void enregistrerMatAdjacence(const Graphe *G, const char *nomFichier) {
	creerDossier(OUTPUT_DIR);
	char path[TAILLE_MAX];
	snprintf(path, sizeof(path), "%s%s", OUTPUT_DIR, nomFichier);
	FILE *fichier = fopen(path, "w");

	if (fichier != NULL) {
		int start = G->matAdjacence[0][0] ? 0 : 1; // Si les degres ont ete calcules, on les enregistre.
		for (int id1 = start; id1 <= G->nbSommets; id1++) {
		    for (int id2 = start; id2 <= G->nbSommets; id2++) {
		        fprintf(fichier, "%d,", G->matAdjacence[id1][id2]);
		    }
		    fprintf(fichier, "\n");
		}
	fclose(fichier);
	}
	else {
		printf("Fichier introuvable.\n");
	}
}

void enregistrerListeDisc(const ListeDisciplines *liste, const char *nomFichier) {
	creerDossier(OUTPUT_DIR);
	char path[TAILLE_MAX];
	snprintf(path, sizeof(path), "%s%s", OUTPUT_DIR, nomFichier);
	FILE *fichier = fopen(path, "w");
	
	if (fichier != NULL) {
		NoeudDiscipline *courant = liste->tete;
		while (courant != NULL) {
			fprintf(fichier, "%d %d %d %s\n", courant->id, courant->disc.x, courant->disc.y, courant->disc.nom);
			courant = courant->suiv;
		}
	fclose(fichier);
	}
	else {
		printf("Fichier introuvable.\n");
	}
}

void enregistrerGraphe(const Graphe *G, const Discipline *tabMatieres, const int nbSemestres, const char *nomFichier) {
	creerDossier(OUTPUT_DIR);
	char nomFichierDot[TAILLE_MAX];
	sprintf(nomFichierDot, "%s%s.dot", OUTPUT_DIR, nomFichier);
	FILE *fichier = fopen(nomFichierDot, "w");
	
	if (fichier != NULL) {
		// Debut //
		fprintf(fichier, "digraph G {\n");
		fprintf(fichier, "ranksep=2.5;\n"); // 2.0
		
		// Initialisation des semestres //
		fprintf(fichier, "\tnode [shape=plaintext, fontsize=16];\n");
		for (int sem = 5; sem <= nbSemestres+4; sem++) {
			fprintf(fichier, "S%d -> ", sem);
		}
		fseek(fichier, -4*sizeof(char), SEEK_CUR);
		
		// Creation de tous les noeuds //
		fprintf(fichier, ";\n\tnode [shape=ellipse];\n");
		for (int i = 1; i <= G->nbSommets; i++) {
			fprintf(fichier, "\t\"(%d, %d)\"", tabMatieres[i].x, tabMatieres[i].y);
			if (G->matAdjacence[i][0] != 0) { // Si le degre sortant est non nul, alors on parcours la ligne pour ajouter les voisins
				fprintf(fichier, " -> ");		
				for (int j = 1; j <= G->nbSommets; j++) { // On parcourt la ligne
					if (G->matAdjacence[i][j]) { // Si on trouve un voisin, on l'ajoute
						fprintf(fichier, "\"(%d, %d)\", ", tabMatieres[j].x, tabMatieres[j].y);
					}
				}
				fseek(fichier, -2*sizeof(char), SEEK_CUR); // Retire la virgule de fin inutile
			}
			else if (G->matAdjacence[0][i] == 0) {
				fprintf(fichier, " [color=red]");
			}
			fprintf(fichier, ";\n");
		}
		
		// On met les noeuds au niveau de leur semestre //
		for (int id = 1; id <= G->nbSommets; id++) {
			fprintf(fichier, "{rank = same; S%d; \"(%d, %d)\"}\n", tabMatieres[id].x+4, tabMatieres[id].x, tabMatieres[id].y);
			// On distingue les UP des GP avec leur forme : carree pour GP et elliptique pour UP //
			if (tabMatieres[id].type == GP) {
				fprintf(fichier, "\t\"(%d, %d)\" [shape=box]", tabMatieres[id].x, tabMatieres[id].y);			
			}
		}

		fprintf(fichier, "}");
//		// NE FONCTIONNE PAS	
//		char commande[TAILLE_MAX];
//		sprintf(commande, "dot %s -Tpdf -o %s.pdf", nomFichierDot, nomFichier); 
//		system(commande);
		
	}
	else {
		printf("Erreur de fichier.\n");
	}
}

void enregistrerTabMarque(const char *nomFichier, const Graphe *G, const int *tabCompoConnexes) {
	creerDossier(OUTPUT_DIR);
	char path[TAILLE_MAX];
	snprintf(path, sizeof(path), "%s%s", OUTPUT_DIR, nomFichier);
	FILE *fichier = fopen(path, "w");
	if (fichier != NULL) {
		for (int s = 1; s <= G->nbSommets; s++) {
	        fprintf(fichier, "%d\n", tabCompoConnexes[s]);
		}
	fclose(fichier);
	}
	else {
		printf("Fichier introuvable.\n");
	}
}

void enregistrerChaines(const char *nomFichier, ListeDisciplines **chaines, const int taille) {
	creerDossier(OUTPUT_DIR);
	char path[TAILLE_MAX];
	snprintf(path, sizeof(path), "%s%s", OUTPUT_DIR, nomFichier);
	FILE *fichier = fopen(path, "w");
	if (fichier != NULL) {
		for (int i = 0; i < taille; i++) {
			NoeudDiscipline *courant = chaines[i]->tete;
			if (courant != NULL) {
				fprintf(fichier, "%d ", courant->id);		
				while (courant->suiv != NULL) {
					courant = courant->suiv;
					fprintf(fichier, "-> %d ", courant->id);
				}
				if (chaines[i]->tete != NULL)
					fprintf(fichier, "\n");
			}
		}
		fclose(fichier);
	}
	else {
		printf("Fichier introuvable.\n");
	}
}
