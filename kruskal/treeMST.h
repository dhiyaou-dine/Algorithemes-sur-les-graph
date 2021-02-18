#pragma once
#ifndef DEF_TREEMST
#define DEF_TREEMST

/*
* *algorithe de krushkal: chemin le plus court pour aller d'une source à une destination 
* sur un arbre(graphe) non orienté
*/
// classes relatives à l'algorithe me krushkal
// on otulise la regle de l'encapsulation.
// rendre toute la classe public faciletrai l'ipmlémentation mais n'est pas tres sure

//-------------------------------------------------------------//
//---------------------ALGORITHME DE KRUSKAL-------------------//
//-------------------------------------------------------------//
//classe representant une arrete. source(point de depart), destination(point d'arriver), weight(poids)

class Edge
{
private:
	int m_source;
	int m_destination;
	int m_weight;
public:
	//on se suffit du constructeur/constructeur par copie générer par le compilateur
	int getSource() const;
	int getDestination() const;
	int getWeight() const;
	friend int comparaisonOfTwoEdges(const void* a, const void* b);
};
// classe representant un graphe
class Graph
{
private:
	int m_nbrSommet;
	int m_nbrEdge;
	Edge* m_edge;
public:
	//constructeur par defaut
	Graph();
	//constructeur par copie
	Graph(Graph const& graph);
	//destructeur
	~Graph();
	int getNbrSommet() ;
	int getNbrEdge();
	// fonction de construction d'un graphe

	Graph* constructGraphe(int nbrSommet, int nbrEdge);
	friend void KruskalMST(Graph* graph);
};

// calsse d'un sous-ensemble
class subset
{
private:
	int m_parent;
	int m_rank;
public:
	//on se suffit du constructeur/constructeur par copie générer par le compilateur 
	int getParent();
	int getRank();
	void setParent(int parent);
	void setRank(int rank);
	// recherche de sous ensemble contenant un element donné 
	// on utilise la methode des graphes
	friend int findSetOfElement(subset subsets[], int i);

	// fonction effectuant l'union de deux sous ensemble contenant x et y respectivement
	// on utilise le rank (au lieu de la hauteur) de la branche
	friend void unionOfTwoSubsets(subset subsets[], int x, int y);
};

//-------------------------------------------------------------//
//---------------------ALGORITHME DE PRIM----------------------//
//-------------------------------------------------------------//

// une valeur de V qui peut etre lu ou modifier
#define V 5

// fonction qui renvoie la clé minimal associée au noeud suivent
int minKey(int key[], bool mstSet[]);
// fonction affichant le MST construit à partir du tableu parent, contenant le parent de chaque element
void printMST(int parent[], int graph[V][V]);
// construction et affichage d'un graph construit avec le principe d'agencement de brache par maximum
void primMST(int graph[V][V]);


#endif // !DEF_TREEMST



