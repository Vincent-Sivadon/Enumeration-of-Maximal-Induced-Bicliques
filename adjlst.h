#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

// Vertex struct
typedef struct Vertex {
    int index;
    struct Vertex* next;
} Vertex;


// Graph struct
typedef struct {
    int size;
    Vertex** adjlst;
} Graph;


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




// A utility function to find the vertex with minimum distance value
int minDist(int* dist, bool* visited, int N)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for(int v=0 ; v<N ; v++)
        if ( !visited[v] && dist[v]<=min)
            min = dist[v], min_index = v;

    return min_index;
}

//
void printPath(int* dist, int N)
{
    printf("Vertex \t\t Distance\n");
    for(int i=0 ; i<N ; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}


//
int* dijkstra(Graph* graph, int src)
{
    // Number of Vertices
    int N = graph->size;

    // Declaration
    bool visited[N];    // false if not yet visited
    int  previous[N];  // previous node visited
    int* dist = malloc(N * sizeof(int));    // dist[i] shortest distance from src to i

    // Initialization
    for(int i=0 ; i<N ; i++)
        dist[i] = INT_MAX, visited[i] = false;
    dist[src] = 0;

    for(int i=0 ; i<N ; i++){

        // The unvisited vertex with the smallest distance from src
        int u = minDist(dist, visited, N);

        // Becomes visited
        visited[u] = true;

        // Run through all neighbors of u
        // and update shortest distance dist[neighbor] if needed
        Vertex* tmp = graph->adjlst[u] ;
        while( tmp ){
            if( dist[u]+1 < dist[tmp->index] && visited[tmp->index]==false ){
                dist[tmp->index] = dist[u]+1;
                previous[tmp->index] = u;
            }
            tmp = tmp->next;
        }
    }
    return dist;
}