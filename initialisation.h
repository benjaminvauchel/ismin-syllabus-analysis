#ifndef INITIALISATION_H
#define INITIALISATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) ((a)>(b) ? (a) : (b))
#define min(a,b) ((a)<(b) ? (a) : (b))

#define NOM_ARETE "edges.csv"
#define NOM_NOEUD "nodes.csv"
#define TAILLE_MAX 100

typedef enum _Type {GP, UP} Type; 

typedef struct {
    char nom[TAILLE_MAX];
    int x;
    int y;
    Type type;
} Discipline;

typedef struct {
	int nbSommets;
    int nbAretes;
	int **matAdjacence;
} Graphe;

// Initialise un graphe avec sa matrice d'adjacence.
void initGraphe(Graphe *G, const int nbSommets);

// Renvoie le nombre de sommets du graphe dans un fichier (ex : nodes.csv).
int compterLignesFicNoeuds(const char *nomFicNoeuds);

// Lit le fichier des noeuds d'un graphe et stocke les UP/GP (de type Discipline)
// dans le tableau tabMatieres.
// Retourne une matrice de correspondance qui a chaque UP associe un nouvel identifiant
// unique tel que matCorrespondance[x][y] = id.
int **lireFicNoeuds(Discipline *tabMatieres, const int nbNoeuds, int *nbSemestres, int *yMax);

// Lit le fichier des aretes, enregistre les aretes dans la matrice d'adjacence du graphe G.
void lireFicAretes(Graphe *G, int **matCorrespondance);

#endif
