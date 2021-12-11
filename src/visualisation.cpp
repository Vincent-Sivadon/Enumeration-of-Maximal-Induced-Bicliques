#include "visualisation.hpp"

void writeGraph(Graph& graph, std::string filename) {
    std::ofstream file;
    file.open(filename);

    // Write number of vertices in graph
    file << graph.N << "\n";

    for(int i=0 ; i<graph.N ; i++)
        for(int j=0 ; j<graph.N ; j++) {
            if(graph.areConnected(i,j))
                file << "1\n";
            else
                file << "0\n";
        }

    file.close();
}

std::vector<int> readGraph(std::string filename) {
    std::ifstream file;
    file.open(filename);
    
    if(!file.is_open())
        std::cout << "coudln't open : " << filename << std::endl;

    // Variables
    int edge;  // will indicates if current (i,j) are connected
    int N;     // number of vertices

    // Get number of vertices
    file >> N;

    // Allocate edges array
    std::vector<int> edges(N);

    // run thourgh the file
    for (int i=0 ; i<N ; i++)
        for (int j=0 ; j<N ; j++)
            file >> edges[i*N + j];

    // Close file
    file.close();

    return edges;
}