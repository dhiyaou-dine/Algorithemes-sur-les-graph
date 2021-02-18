#include "treeMST.h"
#include<iostream>
#include<string>

//-------------------------------------------------------------//
//---------------------ALGORITHME DE KRUSKAL-------------------//
//-------------------------------------------------------------//

// la classe Edge(arrete)
//source
int Edge::getSource() const
{
	return m_source;
}
//destination
int Edge::getDestination() const
{
	return m_destination;
}
//poind
int Edge::getWeight() const
{
	return m_weight;
}
//la classe graphe

Graph::Graph()
{
}
//l'utilisation d'un pointeur dans notre classe implique la redefinition du constructeur par copie
Graph::Graph(Graph const& graph): m_nbrSommet(graph.m_nbrSommet), m_nbrEdge(graph.m_nbrEdge), m_edge(0)
{
	m_edge = new Edge(*graph.m_edge);
}
// definition du destructeur
Graph::~Graph()
{
	delete m_edge;
}
//nombre de sommet
int Graph::getNbrSommet()
{
	return m_nbrSommet;
}
//nombre d'arrete
int Graph::getNbrEdge() 
{
	return m_nbrEdge;
}
//construction d'un graph
Graph* Graph::constructGraphe(int nbrSommet, int nbrEdge)
{
	Graph* graph = new Graph;
	graph->m_nbrSommet = nbrSommet;
	graph->m_nbrEdge = nbrEdge;
	graph->m_edge = new Edge[nbrEdge];
	return graph;
}
// classe de sous-ensemble
//parent
int subset::getParent()
{
	return m_parent;
}
//rang
int subset::getRank()
{
	return m_rank;
}
//insertion d'un parent
void subset::setParent(int parent)
{
	m_parent = parent;
}
//insertion du rang
void subset::setRank(int rank)
{
	m_rank = rank;
}
//comparaison entre deux arretes
int comparaisonOfTwoEdges(const void* a, const void* b)
{
	Edge* a1 = (Edge*)a;
	Edge* a2 = (Edge*)b;
	return a1->m_weight > a2->m_weight;
}
//ALGOTITHME DE KRUSHKAL
void KruskalMST(Graph* graph)
{
    int const nbrSommet(graph->m_nbrSommet);
	Edge result[nbrSommet];
	int e(0); // parcourir le tableau result
	int i(0); // pour les edge trié

	// etape 1: trie du tableau des edge pour former des sous-ensemble 
	qsort(graph->m_edge, graph->m_nbrEdge, sizeof(graph->m_edge[0]), comparaisonOfTwoEdges);
	// allocation dynamique d'un tableau pour creer nbrSommet sous ensemble
	subset* subsets = new subset[nbrSommet* sizeof(subset)];
	// creation des sous-ensemble
	for (int v(0); v < nbrSommet; v++)
	{
		subsets[v].setParent(v);
		subsets[v].setRank(0);
	}
	// on prend nbrSommet - 1 nombre de edge
	while (e < nbrSommet - 1 && i < graph->getNbrEdge())
	{
		// etape 2: je prend le plus petit edge et j'incremente l'indice pour la prochaine iteration
		Edge next_edge = graph->m_edge[i++];
		int x = findSetOfElement(subsets, next_edge.getSource());
		int y = findSetOfElement(subsets, next_edge.getDestination());
		// j'introduit edge courant s'il ne cree pas de cycle et j'incremente
		if (x != y)
		{
			result[e++] = next_edge;
			unionOfTwoSubsets(subsets, x, y);
		}
		// sinon, je ne prend pas en compte le edge
		// affichage du tableau de edge result du MST
		std::cout <<"Nos edges MST"<<std::endl;
		int minimumCost = 0;
		for (i = 0; i < e; ++i)
		{
			std::cout << result[i].getSource() << " -- " << result[i].getDestination()
				<< " == " << result[i].getWeight() << std::endl;
			minimumCost = minimumCost + result[i].getWeight();
		}
		// return;
		std::cout << "Cout minimal Spanning Tree: " << minimumCost
			<< std::endl;
	}

}
// recherche de sous ensemble contenant un element donné 
// on utilise la methode des graphes
int findSetOfElement(subset subsets[], int i)
{
	// on cherche la racine est le condisere comme parent de l'element courant
	// on utilise la methodes des chemin(optimisée) 
	if (subsets[i].m_parent != i)
	{
		findSetOfElement(subsets, subsets[i].m_parent);
	}
	return subsets[i].m_parent;
}

void unionOfTwoSubsets(subset subsets[], int x, int y)
{
	// on cherche le sous-ensemble(donc, la racine) de chaque element x et y
	int xRoot = findSetOfElement(subsets, x);
	int yRoot = findSetOfElement(subsets, y);
	// je compare les rangs de x et y et je considere le plus grand commme racines des deux sous-ensemble
	if (subsets[xRoot].m_rank < subsets[yRoot].m_rank)
	{
		subsets[xRoot].m_parent = yRoot;
	}
	else if (subsets[xRoot].m_rank > subsets[yRoot].m_rank)
	{
		subsets[yRoot].m_parent = xRoot;
	}
	else
	{
		subsets[xRoot].m_parent = yRoot;
		subsets[yRoot].m_rank++;
	}
}

//-------------------------------------------------------------//
//---------------------ALGORITHME DE PRIM----------------------//
//-------------------------------------------------------------//

int minKey(int key[], bool mstSet[])
{
	// initialisation du min et de sa clè(poid sur le noeud courant)
	int min = INT_MAX, min_index;
	for (int v(0); v < V; v++)
	{
		if (mstSet[v] == false && key[v] < min)
		{
			min = key[v];
			min_index = v;
		}
	}
	return min_index;
}

void printMST(int parent[], int graph[V][V])
{
	std::cout << "Edge/ weight" << std::endl;
	for (int v(0); v < V; v++)
	{
		std::cout << parent[v] << "-" << v << "/t" << graph[v][parent[v]];
	}
}

void primMST(int graph[V][V])
{
	// stackage des element du MST
	int parent[V];
	// stackage des clé(poid des sommet)
	int key[V];
	// element representant les sommet stocké
	bool mstSet[V];

	// initialisation des clés à l'inifini
	for (int v(0); v < V; v++)
	{
		key[v] = INT_MAX;
		mstSet[v] = false;// aucun sommet n'est inclu
	}
	// initialisation du premier element à 0 et le parent à -1
	key[0] = 0;
	parent[0] = -1;

	// on parcourt le tableau des cles pour chercher une clé minimum
	// on parcourt le tableau des representant pour voir si l'element est deja pris
	for (int conteur(0); conteur < V - 1; conteur++)// on veut V-1 arret, V le nombre de sommet
	{
		// recherche d'un element avec une cle minimum
		int u = minKey(key, mstSet);
		// on ajoute l'element trouver
		mstSet[u] = true;
		// mise à jour des valeur de cles et des indices des parent non ajouté dans le MST
		for (int v(0); v < V; v++)
		{
			// graph[u][v] est non vide seulement pour les valeurs m de mstSet[v] telque mstSet[v] = false
			// si v n'est pas dans le MST
			// on met ajour les valeur key[v] seulemnt si graph[u][v] < key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
			{
				parent[v] = u;
				key[v] = graph[u][v];
			}
		}
	}
	// affichage de graphe
	printMST(parent, graph);
}

//-------------------------------------------------------------//
//-------------------ALGORITHME DE DIJKSTRA--------------------//
//-------------------------------------------------------------//