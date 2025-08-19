# Analyse du syllabus du cycle ISMIN (2021)

## Description du projet
Ce projet, réalisé dans le cadre du cours **Algorithmique et Programmation II** à l'[École des Mines de Saint-Étienne](https://www.mines-stetienne.fr/), a pour objectif de développer un outil capable d’analyser le graphe relationnel entre les Unités Pédagogiques (UP) et les Groupes Pédagogiques (GP) du cycle ISMIN.  

Le programme lit les fichiers fournis (`nodes.csv` et `edges.csv`) et extrait des informations utiles sur la structure du cursus : relations entre UP et GP, composantes connexes, degrés des sommets, chemins élémentaires, et plus encore.

---

## Structure du projet

```text
.
├── Makefile
├── README.md             # Ce fichier
├── build/                # Objets compilés et exécutable
├── include/              # Fichiers header
├── input/                # Fichiers CSV en entrée
├── output/               # Résultats générés et graphes PDF
└── src/                  # Code source C
```
---

## Contenu des fichiers d’entrée

### `nodes.csv`
- Contient trois champs : `nom`, `x`, `y`.
- Chaque nœud représente une UP ou un GP.
- La coordonnée `x` correspond au semestre, `y` est un identifiant local.
- Convention :
  - Les noms des **GP** sont en majuscules.
  - Les noms des **UP** commencent par une majuscule suivie de minuscules.

### `edges.csv`
- Contient quatre champs : `x1, y1, x2, y2`.
- Une arête entre deux nœuds `(x1, y1)` et `(x2, y2)` modélise une relation entre ces nœuds.

---

## Structure du programme

### Fichiers principaux
- `initialisation.h` : structures de données principales (`Discipline`, `Graphe`) et fonctions de lecture/init.
- `listeDisciplines.h` : liste chaînée de disciplines avec fonctions d’insertion, suppression, comptage et affichage.
- `graph.h` : fonctions de manipulation du graphe, calcul de composantes connexes, exploration des chemins élémentaires, construction du graphe de précédence.
- `graphMetrics.h` : calcul des degrés entrants/sortants, tri des UP selon leurs relations.
- `export.h` : fonctions pour sauvegarder les matrices, listes chaînées et graphes au format texte ou dot.
- `display.h` : fonctions pour afficher dans la console les matrices, listes et statistiques du graphe.

### Structures clés
- `Discipline` : contient `nom`, `x`, `y` et `type` (UP ou GP).
- `Graphe` : contient nombre de sommets, nombre d’arêtes et matrice d’adjacence.
- `ListeDisciplines` : liste chaînée de disciplines pour stocker et trier les UP/GP.

---

## Fonctionnalités

### Intégrité et chargement des fichiers
- Vérifie si les nœuds dans `edges.csv` existent dans `nodes.csv`.
- Chaque nœud reçoit un **identifiant unique**, permettant une matrice d’adjacence 2D compacte.

### Indicateurs descriptifs
- Nombre total de sommets, UP et GP.
- Degré entrant, sortant et nombre de relations de chaque nœud.
- Identification des UP et GP isolés.
- Détermination des composantes connexes.

### Tri et classement
- Les UP sont triées par **nombre de relations décroissant** dans une liste chaînée.
- Permet d’afficher les **top *n* UP/GP** ayant le plus de relations.

### Graphe de précédence
- Construction à partir du graphe relationnel :
  - Suppression des arêtes intra-semestre.
  - Orientation des arêtes reliant des semestres différents.
- Exploration des **chemins élémentaires**.
- Identification des **séquences d’arcs les plus longues**.

---
## Installation et exécution
1. Cloner le projet :
```bash
git clone <url_du_projet>
cd <nom_du_projet>
```
2. Compiler le programme :
```bash
make
```
3. Exécuter :
```bash
./build/main
```
4. Les résultats sont générés dans le dossier `output/`.

---

## Résultats et visualisation
- **Graphes**
  - [Graphe relationnel](output/graphe.pdf)
  - [Graphe de précédence](output/graphePrecedence.pdf)
- **Fichiers de sortie**
  - [matAdjacence.csv](output/matAdjacence.csv) : matrice d’adjacence du graphe
  - [matAdjacenceGPrec.txt](output/matAdjacenceGPrec.txt) : matrice d'adjacence du graphe de précédence
  - [matCorrespondance.csv](output/matCorrespondance.csv) : correspondance des identifiants
  - [tabMatieres.csv](output/tabMatieres.csv) : tableau des disciplines (UP/GP)
  - [cheminsElem.txt](output/cheminsElem.txt) : chemins élémentaires du graphe de précédence
  - [listeTriee.txt](output/listeTriee.txt) : UP triées par nombre de relations décroissant
  - [tabCompoConnexes.txt](output/tabCompoConnexes.txt) : tableau de numéros de la composante connexe de chaque sommet
  - [graphe.dot](output/graphe.dot) : graphe relationnel  
    **Remarque :** Les sommets isolés sont affichés en rouge, les GPs sous forme de rectangles et les UPs sous forme d’ovales.
  - [graphePrecedence1.dot](output/graphePrecedence1.dot) : graphe de précédence
- Conversion des fichiers `dot` en PDF via **Graphviz** :
```bash
sudo apt-get install graphviz
dot <fichier.dot> -Tpdf -o <fichier.pdf>
```

## Choix algorithmiques et limitations
- **Matrice d’adjacence 2D** avec stockage des degrés entrants/sortants pour optimiser les calculs.
- **Listes chaînées** pour le tri par insertion des UP par nombre de relations.
- Algorithmes récursifs pour explorer les chemins élémentaires.
- Limitation : Certaines métriques (prérequis éloignés dans le temps, dates au plus tôt/au plus tard) ne sont pas encore implémentées.

---

## License
Ce projet est distribué sous licence MIT, libre d’utilisation, de modification et de redistribution.

