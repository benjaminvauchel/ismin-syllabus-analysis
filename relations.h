#ifndef RELATIONS_H
#define RELATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initialisation.h"
#include "listeDisciplines.h"
#include "enregistrement.h"

// Genere une liste chainee de disciplines triee dans l'ordre decroissant de relations pour chaque sommet.
// La tete est le sommet dont le nombre de relations est le plus eleve, la queue est le sommet dont le nombre de relations est le plus faible.
void trierTabMatieres(const Graphe *G, const Discipline *tabMatieres, ListeDisciplines *listeTriee, const int *nbRelations);

// Calcule le degre entrant de chaque sommet et le stocke sur la colonne 0.
//	degE(s) = G->matAdjacence[0][s]
// Calcule le degre sortant de chaque sommet et le stocke sur la ligne 0.
//	degS(s) = G->matAdjacence[s][0]
// G->matAdjacence[0][0] contient le nombre d'aretes du graphe. 
int calculerDegres(Graphe *G);

// Renvoie le degre entrant minimal et le ou les sommets correspondants dans la liste chainee listeMin, et le degre entrant maximal et le ou les sommets correspondants
// dans la liste chainee listeMax
void calculerDegresEntrant(const Graphe *G, const Discipline *tabMatieres, ListeDisciplines *listeMin, ListeDisciplines *listeMax, int *degMin, int *degMax);

// Renvoie le degre sortant minimal et le ou les sommets correspondants dans la liste chainee listeMin, et le degre sortant maximal et le ou les sommets correspondants
// dans la liste chainee listeMax
void calculerDegresSortant(const Graphe *G, const Discipline *tabMatieres, ListeDisciplines *listeMin, ListeDisciplines *listeMax, int *degMin, int *degMax);

// Cree un tableau contenant le nombre de relations = le degre de chaque sommet.
// Pour tout sommet s dans V, nbRelations[s] = deg(S).
void creerTabNbRelations(const Graphe *G, int *nbRelations);


#endif
