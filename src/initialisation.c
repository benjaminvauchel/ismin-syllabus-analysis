#include "initialisation.h"

void initGraphe(Graphe *G, const int nbSommets) {
	G->nbAretes = 0;
	G->nbSommets = nbSommets;
	G->matAdjacence = (int **) malloc((nbSommets + 1) * sizeof(int *));
    for (int i = 0; i <= nbSommets; i++) {
    	G->matAdjacence[i] = (int *) calloc((nbSommets + 1), sizeof(int));
    }
}

int compterLignesFicNoeuds(const char *nomFicNoeuds) {
	FILE *fichier = fopen(PATH_NODES_CSV, "r");
	int nbNoeuds = 0;

    if (fichier != NULL) {
        char c;
        while ((c = fgetc(fichier)) != EOF) { 
            if(c == '\n') {
                nbNoeuds++;
            }
        }
        nbNoeuds--; // La dernière ligne du fichier est vide.
        fclose(fichier);
    }
    else {
    	printf("[compterLignesFicNoeuds] Erreur : Fichier introuvable.\n");
    }
    return nbNoeuds;
}

int **lireFicNoeuds(Discipline *tabMatieres, const int nbNoeuds, int *nbSemestres, int *yMax) {
    FILE *fichier = fopen(PATH_NODES_CSV, "r");
    
    if (fichier != NULL) {
        char nom[TAILLE_MAX];
        int x, y;
        char c;
        
        *nbSemestres = 0;
        *yMax = 0;
        
        fseek(fichier, 6, SEEK_SET); // On repart du début du fichier (en sautant les en-tetes)

		for (int noNoeud = 1; noNoeud <= nbNoeuds; noNoeud++) {
        	fscanf(fichier, "\n %[^,], %c", nom, &c); // On lit systematiquement le caractere suivant la virgule pour voir si la virgule fait partie du nom ou pas
            fseek(fichier, -sizeof(char), SEEK_CUR);
            while (((int) c < 49) || ((int) c > 57)) { // Tant que ce qui suit n'est pas un chiffre
                char suite_nom[TAILLE_MAX];
                fscanf(fichier, "%[^,],", suite_nom); // On lit la chaine jusqu'a la virgule suivante
                strcat(nom, ", "); // On ajoute la virgule au nom
                strcat(nom, suite_nom); // On regroupe pour faire un seul nom d'UP
                fscanf(fichier, " %c", &c); // On lit le caractere qui suit la virgule de nouveau
                fseek(fichier, -sizeof(char), SEEK_CUR);
			}
            fscanf(fichier, "%d, %d", &x, &y);
            
            *nbSemestres = max(*nbSemestres, x);
            *yMax = max(*yMax, y);
            strcpy(tabMatieres[noNoeud].nom, nom);
            tabMatieres[noNoeud].x = x;
            tabMatieres[noNoeud].y = y;
            
        }

		// Initialisation de matCorrespondance
		int **matCorrespondance = (int **) malloc((*nbSemestres + 1)*sizeof(int *));
        for (int i = 1; i <= *nbSemestres; i++) {
            matCorrespondance[i] = (int *) calloc((*yMax + 1), sizeof(int));
        }

        fseek(fichier, 6*sizeof(char), SEEK_SET); // On repart du début du fichier (en sautant les en-tetes)
        for (int noNoeud = 1; noNoeud <= nbNoeuds; noNoeud++) {
        	fscanf(fichier, "\n %[^,], %c", nom, &c); // On lit systematiquement le caractere suivant la virgule pour voir si la virgule fait partie du nom ou pas
            fseek(fichier, -sizeof(char), SEEK_CUR);
            while (((int) c < 49) || ((int) c > 57)) { // Tant que ce qui suit n'est pas un chiffre
                char suite_nom[TAILLE_MAX];
                fscanf(fichier, "%[^,],", suite_nom); // On lit la chaine jusqu'a la virgule suivante
                fscanf(fichier, " %c", &c); // On lit le caractere qui suit la virgule de nouveau
                fseek(fichier, -sizeof(char), SEEK_CUR);
			}
            fscanf(fichier, "%d, %d", &x, &y);
            matCorrespondance[x][y] = noNoeud;
        }
    fclose(fichier);
    return matCorrespondance;
    }
    else {
        printf("Fichier introuvable.\n");
    }
}

void lireFicAretes(Graphe *G, int **matCorrespondance) {
    FILE* fichier = fopen(PATH_EDGES_CSV, "r");
        
    if (fichier != NULL) {
        int x1,y1,x2,y2;
        char s[1];

        fseek(fichier, 7*sizeof(char), SEEK_SET); // On saute les en-tetes + le crochet
        while (fscanf(fichier, "[%d,%[ ]%d],[%d,%[ ]%d]\n", &x1, s, &y1, &x2, s, &y2) != EOF) {
			int id1 = matCorrespondance[x1][y1];
			int id2 = matCorrespondance[x2][y2];
			if (((id1 != 0) && (id2 != 0)) && (!(G->matAdjacence[id1][id2]))) {
				(G->nbAretes)++;
	            G->matAdjacence[id1][id2] = 1;
	        }
        }
    }
    else {
        printf("Fichier introuvable.");
    }
}


