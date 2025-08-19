#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "initialisation.h"
#include "listeDisciplines.h"
#include "export.h"
#include "graphMetrics.h"

#define TAILLE_TAB 500

// Pour chaque sommet, determine le type de sommet (UP ou GP) selon le nom du sommet. Le type est stocke dans chaque structure de donnees Discipline du
// tableau tabMatieres.
// Renvoie le nombre d'UP.
int determinerType(Discipline *tabMatieres, const int nbNoeuds);

// Visite un graphe NON ORIENTE de maniere recursive.
// Marque chaque sommet dans tabCompoConnexes avec un numero de composante connexe.
// Fonction auxiliaire a compterCompoConnexes.
void visiterGraphe(const Graphe* G, int* tabCompoConnexes, const int sommet, const int composanteConnexe);

// Renvoie le nombre de composantes connexes du graphe G.
// Sauvegarde le numero de composante connexe de chaque sommet dans un tableau et dans un fichier texte.
// Tous les sommets d'une meme composante connexe ont le meme numero de composante connexe.
int compterCompoConnexes(const Graphe* G, int *tabCompoConnexes);

// Compte le nombre d'UP et de GP isoles
void compterSommetsIsoles(const Graphe *G, const Discipline *tabMatieres, int *UPIsoles, int *GPIsoles);

// Construit le graphe de precedence correspondant au graphe G :
// 	- supprime les aretes intra-semestre
//	- oriente les aretes reliant les semestres
//	- stocke dans un tableau l'ensemble des chemins élémentaires partant du premier sommet possible.
void construireGraphePrecedence(const Graphe *G, Graphe *GPrec, const Discipline *tabMatieres);

// Fonction auxiliaire qui convertit un tableau d'identifiants en liste chainee = chemin elementaire
void tableauToListe(const int *tab, const int taille, ListeDisciplines *liste, const Discipline *tabMatieres);

// Explore les chemins partant de position recursivement
void explore(const Graphe *G, int *chemin, bool *tabMarque, const int position, const int profondeur, const Discipline *tabMatieres, ListeDisciplines **chemins, int *k);

// Explore tous les chemins d'un graphe de precedence en faisant varier le sommet de depart
int explorerTousCheminsElem(const Graphe *G, ListeDisciplines **chemins, const Discipline *tabMatieres);

// Affiche les plus longues sequences d'arcs du graphe de precedence.
void plusLonguesSeq(ListeDisciplines **chemins, const int taille);

#endif
