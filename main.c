#include <stdbool.h>
#include "initialisation.h"
#include "enregistrement.h"
#include "listeDisciplines.h"
#include "relations.h"
#include "algorithmique.h"


int main() {


    const int nbNoeuds = compterLignesFicNoeuds(NOM_NOEUD);

	printf("Le fichier contient %d noeuds.\n", nbNoeuds); //
    
    Graphe G;
	initGraphe(&G, nbNoeuds);
    Discipline *tabMatieres = (Discipline *) malloc((nbNoeuds + 1) * sizeof(Discipline));

	int nbSemestres, yMax;
    int **matCorrespondance = lireFicNoeuds(tabMatieres, nbNoeuds, &nbSemestres, &yMax);
    int nbUPs = determinerType(tabMatieres, nbNoeuds);
	printf("nombre d'UPs : %d\nnombre de GPs : %d\n", nbUPs, nbNoeuds - nbUPs); //


	afficherTabMatieres(tabMatieres, nbNoeuds); //
	enregistrerTabMatieres("tabMatieres.csv", tabMatieres, nbNoeuds); //

    lireFicAretes(&G, matCorrespondance);
    calculerDegres(&G);

////    afficherMatCorrespondance(matCorrespondance, nbSemestres, yMax); ////
	enregistrerMatCorrespondance("matCorrespondance.csv", matCorrespondance, nbSemestres, yMax); //

////    afficherMatAdjacence(&G); ////
	enregistrerMatAdjacence(&G, "matAdjacence.csv"); //


	ListeDisciplines *listeMin = malloc(sizeof(ListeDisciplines));
	ListeDisciplines *listeMax = malloc(sizeof(ListeDisciplines));
	int degMin, degMax;
	calculerDegresSortant(&G, tabMatieres, listeMin, listeMax, &degMin, &degMax);

	printf("degMin = %d, degMax = %d\n", degMin, degMax);	//
	printf("Liste Min :\n");								//
	afficherListeDiscEntier(listeMin);						//
	printf("Liste Max :\n");								//
	afficherListeDiscEntier(listeMax);						//

	int UPIsoles, GPIsoles;	//
	compterSommetsIsoles(&G, tabMatieres, &UPIsoles, &GPIsoles); //
	printf("Nombre d'UP isoles : %d\nNombre de GP isoles : %d\n", UPIsoles, GPIsoles); //


	ListeDisciplines *listeTriee = (ListeDisciplines *) malloc(sizeof(ListeDisciplines));
	initListeDisc(listeTriee);
	int *nbRelations = (int *) malloc(G.nbSommets * sizeof(int));
	creerTabNbRelations(&G, nbRelations);
	trierTabMatieres(&G, tabMatieres, listeTriee, nbRelations);
	afficherListeDiscEntier(listeTriee); //
	enregistrerListeDisc(listeTriee, "listeTriee.txt"); //
	

	enregistrerGraphe(&G, tabMatieres, nbSemestres, "graphe");
	
	int *tabCompoConnexes = (int*) calloc(G.nbSommets + 1, sizeof(int));
	int nbCompoConnexes = compterCompoConnexes(&G, tabCompoConnexes);
	printf("Il y a %d composantes connexes.\n", nbCompoConnexes); //
	
	printf("Il y a %d arêtes.\n", G.nbAretes); //
	
	printf("Le top 5 des UP ayant le plus de relations est :\n"); //
	afficherTopNbRelations(&G, listeTriee, nbRelations, 5); //
	
	Graphe GPrec;
	construireGraphePrecedence(&G, &GPrec, tabMatieres);
	GPrec.nbAretes = calculerDegres(&GPrec);
	enregistrerMatAdjacence(&GPrec, "matAdjacenceGPrec.txt"); //
	enregistrerGraphe(&GPrec, tabMatieres, nbSemestres, "graphePrecedence1");
	int *tabCompoConnexesGPrec = (int*) calloc(GPrec.nbSommets + 1, sizeof(int));
	int nbCompoConnexesGPrec = compterCompoConnexes(&GPrec, tabCompoConnexesGPrec);


	ListeDisciplines **chemins = (ListeDisciplines **) malloc(TAILLE_TAB * sizeof(ListeDisciplines *));
	int nbChemins = explorerTousCheminsElem(&GPrec, chemins, tabMatieres);
	afficherChaines(chemins, nbChemins);						//
	enregistrerChaines("cheminsElem.txt", chemins, nbChemins);	//
	plusLonguesSeq(chemins, nbChemins);							//

	free(tabMatieres);
	freeListeDisc(listeMin);
	freeListeDisc(listeMax);
	freeListeDisc(listeTriee);
	for (int i = 0; i < TAILLE_TAB; i++) {
		if (chemins[i] != NULL) {
			freeListeDisc(chemins[i]);
			chemins[i] = NULL;
		}
	}
	free(chemins);
	
    return 0;
}



