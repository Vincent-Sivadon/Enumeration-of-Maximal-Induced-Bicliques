#include "adjlst.h"

// Create a Vertex
Vertex* createVertex(int i) {
    Vertex* newVertex = malloc( sizeof(Vertex) );
    newVertex->index = i;
    newVertex->next = NULL;
    return newVertex;
}

// Add edge between two vertices s and d
void addEdge(Graph* graph, int s, int d) {
    // Add edge from s to d
    Vertex* newVertex = createVertex(d);
    newVertex->next = graph->adjlst[s];
    graph->adjlst[s] = newVertex;

    // Add edge from d to s
    newVertex = createVertex(s);
    newVertex->next = graph->adjlst[d];
    graph->adjlst[d] = newVertex;
}

// Print the graph in terminal
void printGraph(Graph* graph) {
    for (int v=0 ; v<graph->size ; v++ ){
        Vertex* temp = graph->adjlst[v] ;
        printf("\n Vertex %d\n: ", v);
        while (temp) {
            printf("%d -> ", temp->index);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Check if an edge can be placed between 2 vertices s and d
int checkEdge(Graph* graph, int s, int d)
{
    // Check Edge (s, d)
    Vertex* tmp = graph->adjlst[s]; 
    while( tmp ){
        if( tmp->index == d ) return 1;
        tmp = tmp->next;
    }

    // Check Edge (d, s)
    // Will be removed if we only study undirected graph
    tmp = graph->adjlst[d]; 
    while( tmp ){
        if( tmp->index == s ) return 1;
        tmp = tmp->next;
    }

    return 0;
}

// Declare a graph
Graph* createGraph(int N)
{
    // Allocate graph
    Graph* graph = malloc( sizeof(Graph) );
    graph->size = N;

    // Allocate adjacency list
    graph->adjlst = malloc(N * sizeof(Vertex*) );

    // Initialization
    for ( int i=0 ; i<N ; i++ )
        graph->adjlst[i] = NULL;
    
    return graph;
}


// Generate random graph
Graph* genRandGraph(int N)
{
    Graph* graph = createGraph(N);

    int maxEdges = N * (N-1) / 2; // Random graph method
    int nEdges = maxEdges / 4 ;     // Arbitrary

    // Pour chaque élément
    for(int i=0 ; i<nEdges ; i++){
        int p = rand()%N ;
        int q = rand()%N;
        if( (p!=q) & !checkEdge(graph, p,q)) addEdge(graph, p, q);
    }
    return graph;
}

// Generate a graph that represent a H2O molecule (to test checkEdge)
Graph* H2O()
{
    Graph* graph = createGraph(3);

    // 0   --> Oxygen
    // 1,2 --> Hydrogen
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);

    return graph;
}

// Generate a graph that represent a methane molecule (to test checkEdge)
Graph* Methane()
{
    Graph* graph = createGraph(5);

    // 0       --> Carbon
    // 1,2,3,4 --> Hydrogene
    addEdge(graph, 0, 1); addEdge(graph, 0, 2);
    addEdge(graph, 0, 3); addEdge(graph, 0, 4);

    return graph;
}

// Generate a graph that represent an hexagone
Graph* Hexagone() {
    Graph* graph = createGraph(6);

    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 0);

    return graph;
}
