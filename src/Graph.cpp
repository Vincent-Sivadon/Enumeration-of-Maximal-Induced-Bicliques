#include "Graph.hpp"

#include <stdio.h>

void Graph::Randomize()
{
	// For every pair of nodes
	for (u64 i = 0; i < N-1; i++)
		for (u64 j = i+1; j < N; j++) {
			// Rand number between 0 and 1
			double r = (double) rand() / (double) RAND_MAX;

			// Connect i and j if r<0.003
			if (r < 0.003)
				Connect(i, j);
    }
}

void Graph::Connect(u64 i, u64 j)
{
	i = sigma[i];
	j = sigma[j];
	adj[i*N + j] = 1;
	adj[j*N + i] = 1;
}

void Graph::Disconnect(u64 i, u64 j)
{
	i = sigma[i];
	j = sigma[j];
	adj[i*N + j] = 0;
	adj[j*N + i] = 0;
}

bool Graph::AreConnected(u64 i, u64 j)
{
	i = sigma[i];
	j = sigma[j];
	if (adj[i*N + j] == 1)
		return true;
	return false;
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

bool Graph::NodeExists(u64 i)
{
	i = sigma[i];
	if ( adj[i] != -1) return true;
	return false;
}


std::set<u64> Graph::GetAllNeighboors(u64 i)
{
	std::set<u64> neighboors;
	for (u64 j = 0; j < N; j++)
		if (AreConnected(i,j) && NodeExists(i))
			neighboors.insert(j);
	return neighboors;	
}

// Get all neighboors from the vertices following i in sigma order
std::set<u64> Graph::GetNeighboorsVi(u64 i, u64 pivot)
{
	std::set<u64> neighboors;
	for (u64 j = 0; j < N; j++)
		if (sigma[j]>=sigma[pivot] && AreConnected(i,j) && NodeExists(j) && j!=pivot)
			neighboors.insert(j);

	return neighboors;	
}

u64 Graph::GetDegree(u64 i)
{
	u64 count = 0;
	for (u64 j = 0; j < N; j++)
		if (AreConnected(i,j) && i!=j)
			count++;
	return count;	
}


void Graph::ChangeToDegeneracyOrder()
{
	std::vector<bool> visited(N, false);

	for (u64 i = 0; i < N; i++)
	{
		// Find vertex of min degree
		u64 min_degree = INF;
		u64 vertex_of_min_degree;
		for (u64 k = 0; k < N; k++)
		{
			if (visited[k]) continue;

			u64 degree = GetDegree(k);
			if (degree<min_degree)
			{
				min_degree = degree;
				vertex_of_min_degree = k;
			}
		}

		sigma[vertex_of_min_degree] = i;	
		visited[vertex_of_min_degree] = true;
	}
	
}


Graph make_hexagone()
{
	Graph g(6);
	g.Connect(0,1);
	g.Connect(0,5);
	g.Connect(1,2);
	g.Connect(2,3);
	g.Connect(3,4);
	g.Connect(4,5);

    return g;
}