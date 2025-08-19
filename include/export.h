#ifndef EXPORT_H
#define EXPORT_H

#define OUTPUT_DIR "output/"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  // For POSIX
#include <sys/types.h>
#ifdef _WIN32
#include <direct.h>    // _mkdir on Windows
#endif
#include "initialisation.h"
#include "listeDisciplines.h"

// Vérifie si le dossier au chemin donné existe.
int dossierExiste(const char *path);

// Crée un dossier au chemin donné s'il n'existe pas.
// Note : Utilise mkdir pour POSIX et _mkdir pour Windows.
void creerDossier(const char *path);

// Enregistre dans un fichier texte le tableau des matieres avec l'identifiant (id), le semestre (x), l'identifiant de semestre (y) et le nom de la matiere.
void enregistrerTabMatieres(const char *nomFichier, const Discipline *tabMatieres, const int nbNoeuds);

// Enregistre la matrice de correspondance des identifiants des matieres.
// matCorrespondance[x][y] = id avec id le nouvel identifiant attribue.
void enregistrerMatCorrespondance(const char *nomFichier, int **matCorrespondance, const int nbSemestres, const int yMax);

// Enregistre dans un fichier la matrice d'adjacence.
// Enregistre les degres s'ils ont ete calcules.
void enregistrerMatAdjacence(const Graphe *G, const char *nomFichier);

// Enregistre dans un fichier le numero de la composante connexe de chaque sommet.
void enregistrerTabMarque(const char *nomFichier, const Graphe *G, const int *tabCompoConnexes);

// Enregistre dans un fichier la liste des disciplines en entree avec leur identifiant, x, y et leur nom.
void enregistrerListeDisc(const ListeDisciplines *liste, const char *nomFichier);

// Enregistre dans un fichier dot le graphe en entree. L'utilisation de graphviz permet de l'exporter en pdf.
// Voir README pour visualiser le graphe dans un fichier pdf.
void enregistrerGraphe(const Graphe *G, const Discipline *tabMatieres, const int nbSemestres, const char *nomFichier);

// Enregistre dans un fichier l'ensemble des listes chainees de disciplines d'un tableau.
void enregistrerChaines(const char *nomFichier, ListeDisciplines **chaines, const int taille);

#endif
