#include "Graph.hpp"

#include <stdio.h>
#include <unistd.h>

// Disconnect two nodes i and j
void Graph::Disconnect(u64 i, u64 j)
{
	i = sigma[i];
	j = sigma[j];
	adj[i*N + j] = 0;
	adj[j*N + i] = 0;
}

// Get degree of node i
u64 Graph::GetDegree(u64 i)
{
	u64 count = 0;
	for (u64 j = 0; j < N; j++)
		if (AreConnected(j, i) && i!=j)
			count++;
	return count;	
}

// Change ordering to degeneracy order
void Graph::ChangeToDegeneracyOrder()
{
	std::vector<bool> visited(N, false);
	std::vector<u64> newadj(N*N);
	std::vector<u64> degrees(N);

	// Get degrees of all nodes
	for (u64 i = 0; i < N; i++)
		degrees[i] = GetDegree(i);

	for (u64 i = 0; i < N; i++)
	{
		// Find vertex of min degree
		u64 min_degree = INF;
		u64 vertex_of_min_degree;
		for (u64 k = 0; k < N; k++)
		{
			if (visited[k]) continue;

			if (degrees[k]<min_degree)
			{
				min_degree = degrees[k];
				vertex_of_min_degree = k;
			}
		}

		sigma[vertex_of_min_degree] = i;	
		visited[vertex_of_min_degree] = true;
	}


	for (u64 i = 0; i < N; i++)
		for (u64 j = 0; j < N; j++)
			newadj[sigma[i]*N + sigma[j]] = adj[i*N + j];
		

	adj = std::move(newadj);
}


// Get list of neighbors of i
std::set<u64> Graph::GetAllNeighboors(u64 i)
{
	std::set<u64> neighboors;
	for (u64 j = 0; j < N; j++)
		if (AreConnected(i,j))
			neighboors.insert(j);
	return neighboors;	
}

// Get list of neighbors of i if greater in ordering sigma
std::set<u64> Graph::GetNeighboorsVi(u64 i, u64 pivot)
{
	std::set<u64> neighboors;
	for (u64 j = 0; j < N; j++)
		if (sigma[j]>=sigma[pivot] && AreConnected(i,j) && j!=pivot)
			neighboors.insert(j);

	return neighboors;	
}




// Display graph in terminal
void Graph::Print() const
{
	for (u64 i = 0; i < N; i++)
	{
		for (u64 j = 0; j < N; j++)
			std::cout << adj[i*N + j] << " ";
		std::cout << std::endl;
	}
	
}

// Write graph to file filename
void Graph::WriteToFile(const char* filename)
{
    FILE *fp = fopen(filename, "w");
    for (u64 i = 0; i < N-1; i++)
        for (u64 j = i+1; j < N; j++)
            if (AreConnected(i,j))
                fprintf(fp, "%llu,%llu\n", i, j);   
	fclose(fp);
}