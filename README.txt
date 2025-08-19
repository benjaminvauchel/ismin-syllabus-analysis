========================================
ANALYSE DU SYLLABUS DU CYCLE ISMIN
========================================

========================================
Introduction

Ce programme a pour objectif de caracteriser les relations entre les UPs/GPs du syllabus du cycle ISMIN, dans le but de l'améliorer.

========================================
Structure du programme

Le programme est composé de 6 fichiers C (et 5 fichiers d'en-tête) :
listeDisciplines.c  initialisation.c   enregistrement.c  relations.c  algorithmique.c	main.c
listeDisciplines.h  initialisation.h   enregistrement.h  relations.h  algorithmique.h

========================================
Autres fichiers

Sont fournis les deux fichiers sources légèrement modifiés (uniquement caractères ASCII) :
nodes.csv	edges.csv

Deux fichiers au format PDF représentant le graphe relationnel et le graphe de précédence sont inclus.
graphe.pdf	graphePrecedence.pdf

Fichier makefile

========================================
Modification/Utilisation

Il suffit de décommenter les différents blocs écrits dans la fonction main du fichier main.c
Le code déjà décommenté est essentiel pour tout calculer.
Si vous avez un doute, le code commenté contient // ou //// en fin de ligne.
Certaines lignes sont doublement commentées (////) : il n'est pas utile de les décommenter, car ce sont des fonctions d'affichage dans la console qui ne sont pas pratiques.

La lecture des prototypes des fonctions dans les fichiers d'en-tête permet de mieux comprendre les fonctions.
Le "rapport" explique aussi le fonctionnement de certaines fonctions et certains choix.

========================================
Compilation

Le programme contient un fichier makefile.
Pour compiler le code, saisir l'instruction :
$ make main

Pour exécuter :
$ ./main

========================================
Exportation des graphes au format PDF

Pour visualiser les graphes au format PDF, il faut installer graphviz :
$ sudo apt-get install graphviz

Pour convertir un fichier dot en pdf :
$ dot <fichier.dot> -Tpdf -o <fichier.pdf>
