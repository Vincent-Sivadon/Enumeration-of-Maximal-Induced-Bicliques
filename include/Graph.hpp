#pragma once

#define INF 0x3f3f3f3f

#include "SuffixTree.hpp"
#include "Utility.hpp"

#include <vector>
#include <set>
#include <iostream>

typedef unsigned long long u64;

typedef struct {
  int degree;
  int vertex;
} vertexMin;

class Graph {
public:
	u64 N;
	std::vector<u64> adj;
	std::vector<u64> sigma;
	std::vector<u64> parentIdx;
	std::set<std::set<u64>> cliques;

	// Arcs
	void Connect(u64 i, u64 j);
	void Disconnect(u64 i, u64 j);
	bool AreConnected(u64 i, u64 j);
	bool NodeExists(u64 i);

	// Neighboors
	std::set<u64> GetAllNeighboors(u64 i);
	std::set<u64> GetNeighboorsVi(u64 i, u64 pivot);

	// Subgraph
	void SetParentIndices(const Graph& parentGraphraph, std::set<u64>& nodes_at_1, std::set<u64>& nodes_at_2, u64 pivot);
	Graph GenSubgraph(u64 i);
	std::vector<Graph> GenSubgraphGik(u64 i);


	// Independant Sets
	// ----------------
	// Normal version
	bool IsConnectedToSet(u64 i, const std::set<u64>& set);
	bool IsProper(std::set<u64>& set);
	void GetMaxIndSets(Tree& tree, std::set<u64>& tmp_set, u64 i);
	// Bron-Kerbosch version
	void ChangeToComplementary();	
	std::set<u64> InterSetAndNeighboors(std::set<u64>& set, u64 v);
	void BronKerbosch(std::set<u64>& R, std::set<u64>& P, std::set<u64>& X);
	void GetMaxIndSetsBK();


public:
	Graph(u64 N) : N(N) {
		adj.resize(N*N);
		sigma.resize(N);
		for (u64 i = 0; i < N; i++)
			sigma[i] = i;		
	}
	void Randomize();


	// Bicliques
	std::set<std::set<u64>> GetBicliques();
	void GetBicliquesParallel();

	// Display
	void Print() const;

	// Getters
	u64 GetSize() { return N; }
};

Graph make_hexagone();