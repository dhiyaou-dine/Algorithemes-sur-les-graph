// kruskal.cpp  

#include <iostream>
#include "treeMST.h"
int main()
{
    // code test pour l'algorithme de kruskal
    // code test pour l'algorithme de Prim

    /* soit le graph
        2 3
    (0)--(1)--(2)
    | / \ |
    6| 8/ \5 |7
    | / \ |
    (3)-------(4)
            9     */
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };

    // Print the solution  
    primMST(graph);

}
 