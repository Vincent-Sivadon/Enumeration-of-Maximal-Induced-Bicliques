#pragma once

#define INF 0x3f3f3f3f

#include "SuffixTree.hpp"

#include <vector>
#include <set>
#include <iostream>

typedef unsigned long long u64;

typedef struct {
  int degree;
  int vertex;
} vertexMin;

class Graph {
private:
	u64 N;
	std::vector<u64> adj;
	std::vector<u64> sigma;

	void Disconnect(u64 i, u64 j);
	bool AreConnected(u64 i, u64 j);
	bool NodeExists(u64 i);
	std::set<u64> GetAllNeighboors(u64 i);
	std::set<u64> GetNeighboorsVi(u64 i);

	// Subgraph
	void SetParentIndices(const Graph& parentGraphraph, std::set<u64>& nodes_at_1, std::set<u64>& nodes_at_2, u64 pivot);

public:
	std::vector<u64> parentIdx;
	Graph GenSubgraph(u64 i);

	Graph(u64 N) : N(N) {
		adj.resize(N*N);
		sigma.resize(N);
		for (u64 i = 0; i < N; i++)
			sigma[i] = i;		
	}
	void Randomize();

	void Connect(u64 i, u64 j);


	// Display
	void Print() const;

	// Getters
	u64 GetSize() { return N; }
};