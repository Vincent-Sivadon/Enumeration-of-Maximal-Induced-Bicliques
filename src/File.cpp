/* */

#include "Graph.hpp"

void Graph::WriteToFile(const char* filename)
{
    FILE *fp = fopen(filename, "w");
    for (u64 i = 0; i < N-1; i++)
        for (u64 j = i+1; j < N; j++)
            if (AreConnected(i,j))
                fprintf(fp, "%llu,%llu\n", i, j);   
	fclose(fp);
}

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