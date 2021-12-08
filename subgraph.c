#include "subgraph.h"

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
int* dijkstra(Graph* graph, int src, int limit)
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
    
        if (dist[u] >= limit) break;

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