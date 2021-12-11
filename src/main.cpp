#include "graph.hpp"
#include "visualisation.hpp"

int main() {
    Graph hex = Hexagone();
    writeGraph(hex, "./hexagone.dat");
    std::vector<int> hex_edges(hex.N);
    hex_edges = readGraph("./hexagone.dat");
    return 0;
}