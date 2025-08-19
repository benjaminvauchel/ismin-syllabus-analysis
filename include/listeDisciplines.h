#ifndef LISTEDISCIPLINES_H
#define LISTEDISCIPLINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initialisation.h"

typedef struct _NoeudDiscipline {
	Discipline disc;
	int id;
	struct _NoeudDiscipline *suiv;
} NoeudDiscipline;

typedef struct {
	NoeudDiscipline *tete;
} ListeDisciplines;

// Initialise une liste chainee contenant les disciplines.
void initListeDisc(ListeDisciplines *liste);

// Ajoute une discipline en tete de liste chainee.
void ajouterDisc(ListeDisciplines *liste, const Discipline disc, const int id);

// Supprime le premier element d'une liste chainee.
int popListeDisc(ListeDisciplines *liste);

// Libere une liste chainee.
void freeListeDisc(ListeDisciplines *liste);

// Affiche dans la console les identifiants d'une liste donnee.
void afficherListeDisc(const ListeDisciplines *liste);

// Compte le nombre de noeuds dans une liste chainee donnee.
int compterDisc(const ListeDisciplines *liste);

#endif
