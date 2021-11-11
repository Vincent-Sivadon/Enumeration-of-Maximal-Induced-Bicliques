
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
    tmp = graph->adjlst[d]; 
    while( tmp ){
        if( tmp->index == s ) return 1;
        tmp = tmp->next;
    }

    return 0;
}


// Generate random graph
Graph* genGraph(int N, double* masses, double* radii)
{
    // Allocate graph
    Graph* graph = malloc( sizeof(Graph) );
    graph->size = N;

    // Allocate adjacency list
    graph->adjlst = malloc(N * sizeof(Vertex*) );

    // Initialization
    for ( int i=0 ; i<N ; i++ )
        graph->adjlst[i] = NULL;

    int maxEdges = N * (N-1) / 2; // Random graph method
    int nEdges = maxEdges/2 ;     // Arbitrary

    // Pour chaque élément
    for(int i=0 ; i<nEdges ; i++){
        int p = rand()%N ;
        int q = rand()%N;
        addEdge(graph, p, q);
    }
    return graph;
}
