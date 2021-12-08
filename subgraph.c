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

// Print Dijkstra results
void printPath(int* dist, int N)
{
    printf("Vertex \t\t Distance\n");
    for(int i=0 ; i<N ; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Dijkstra shortest path finding algorithm
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

// Create a subgraph G_i
Graph* genSubgraph(Graph* graph, int i) {
    // Subgraph declaration
    Graph* subgraph = createGraph(graph->size);

    // Get distances from i in graph
    int* dist = dijkstra(graph, i, 2);

    //
    for (int x=0 ; x<graph->size - 1 ; x++)
        for (int y=x+1 ; y<graph->size ; y++) {
            bool are_connected = checkEdge(graph, x, y);

            // Get path length
            bool x_dist1 = ( dist[x]==1 ? true : false );
            bool y_dist1 = ( dist[y]==1 ? true : false );
            bool x_dist2 = ( dist[x]==2 ? true : false );
            bool y_dist2 = ( dist[y]==2 ? true : false ); 

            // Subgraph constructor recipe
            bool cond1 = x_dist1 && y_dist1 && are_connected ;
            bool cond2 = x_dist2 && y_dist2 && are_connected ;
            bool cond3 = x_dist1 && y_dist2 && !are_connected ;
            bool cond4 = x_dist2 && y_dist1 && !are_connected ;

            // Add and edge if one of the condition is fullfilled
            if ( cond1 || cond2 || cond3 || cond4 ) addEdge(subgraph, x, y);
        }

    return subgraph;
}