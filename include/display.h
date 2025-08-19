#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initialisation.h"
#include "listeDisciplines.h"

// Affiche dans la console le tableau des matieres avec l'identifiant (id), le semestre (x), l'identifiant de semestre (y) et le nom de la matiere.
void afficherTabMatieres(const Discipline *tabMatieres, const int nbNoeuds);

// Affiche dans la console la matrice de correspondance des identifiants des matieres.
// matCorrespondance[x][y] = id avec id le nouvel identifiant attribue.
void afficherMatCorrespondance(const int **matCorrespondance, const int nbSemestres, const int yMax);

// Affiche dans la console la matrice d'adjacence.
// Affiche les degres s'ils ont ete calcules.
void afficherMatAdjacence(const Graphe *G);

// Affiche dans la console la liste des disciplines en entree avec leur identifiant, x, y et leur nom.
void afficherListeDiscEntier(const ListeDisciplines *liste);

// Affiche dans la console le top n des sommets (UP ou GP) ayant le plus de relations.
void afficherTopNbRelations(const Graphe *G, const ListeDisciplines *listeTriee, const int *nbRelations, const int n);

// Affiche l'ensemble des listes chainees de disciplines d'un tableau.
// Utile pour afficher les chemins elementaires d'un graphe.
void afficherChaines(ListeDisciplines **chaines, const int taille);

#endif // DISPLAY_H