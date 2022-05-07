#include "Graph.hpp"

#include <unistd.h>

// Attribute edges randomly
void Graph::Randomize()
{
    // Init random seed
	srand(getpid());

	// For every pair of nodes
	for (u64 i = 0; i < N-1; i++)
		for (u64 j = i+1; j < N; j++) {
			// Rand number between 0 and 1
			double r = (double) rand() / (double) RAND_MAX;

			// Connect i and j if r<0.003
			if (r < 0.001)
				Connect(i, j);
    }
}

// Initialize graph from file filename
void Graph::InitFromFile(const char* filename)
{
	u64 i,j,number_of_nodes=0;

	// Open file
	FILE *fp = fopen(filename, "r");

	// Read a first time to get number of nodes
	while (fscanf(fp, "%llu,%llu\n", &i, &j) != EOF)
	{
		if (i>number_of_nodes) number_of_nodes=i;
		if (j>number_of_nodes) number_of_nodes=j;
	}
	fclose(fp);

	// Declare graph
	Graph g(number_of_nodes+1);

	// Connect nodes
	fp = fopen(filename, "r");
	while (fscanf(fp, "%llu,%llu\n", &i, &j) != EOF)
		g.Connect(i,j);
	fclose(fp);

	// Define graph
	*this = g;
}


// Init hexagone shapped graph
void Graph::MakeHexagone()
{
	Graph g(6);
	g.Connect(0,1);
	g.Connect(0,5);
	g.Connect(1,2);
	g.Connect(2,3);
	g.Connect(3,4);
	g.Connect(4,5);
	*this = g;
}