#pragma once

#define INF 0x3f3f3f3f

#include "SuffixTree.hpp"
#include "Utility.hpp"

#include <vector>
#include <set>
#include <iostream>

typedef unsigned long long u64;

class Graph {

private:
	u64 N;								// Size of the graph
	std::vector<u64> adj;				// Adjacency Matrix
	std::vector<u64> sigma;				// Ordering
	std::vector<u64> parentIdx;			// If is a subgraph, keep track of the parent indices
	std::set<std::set<u64>> cliques;	// To store cliques

	/************ Core ************/

	// Connects two nodes i and j
	inline void Connect(u64 i, u64 j) { adj[sigma[i]*N + sigma[j]] = 1;
										adj[sigma[j]*N + sigma[i]] = 1; }
	// Disconnect two nodes i and j
	void Disconnect(u64 i, u64 j);
	// Check if two nodes are connected
	inline bool AreConnected(u64 i, u64 j) { if (adj[sigma[i]*N + sigma[j]] == 1)
												return true; 
												return false; }
	// Get degree of node i
	u64 GetDegree(u64 i);
	// Change ordering to degeneracy order
	void ChangeToDegeneracyOrder();
	// Get list of neighbors of i
	std::set<u64> GetAllNeighboors(u64 i);
	// Get list of neighbors of i if greater in ordering sigma
	std::set<u64> GetNeighboorsVi(u64 i, u64 pivot);


	/************ Subgraphs ************/

	// For a subgraph : to keep track of the correspondance between subgraph indices and parent indices
	void SetParentIndices(const Graph& parentGraph, std::set<u64>& nodes_at_1, std::set<u64>& nodes_at_2, u64 pivot);
	// Subgraph Gi generation
	Graph GenSubgraph(u64 i);
	// Subgraphs Gik generation
	std::vector<Graph> GenSubgraphGik(u64 i);

	/************ Independant Sets ************/

	// Check if i is connected to a node of set in graph
	bool IsConnectedToSet(u64 i, const std::set<u64>& set);
	// Check if a set is proper
	bool IsProper(std::set<u64>& set);
	// Get a list of maximal independant sets of graph
	void GetMaxIndSets(Tree& tree, std::set<u64>& tmp_set, u64 i);


	/************ Bron-Kerbosch ************/

	// Modify the graph to be it's complementary
	void ChangeToComplementary();	
	// Get the intersection of set and neighbors of v
	std::set<u64> InterSetAndNeighboors(std::set<u64>& set, u64 v);
	// Insert graph maximal independant sets in cliques
	void BronKerbosch(std::set<u64>& R, std::set<u64>& P, std::set<u64>& X);
	// BronKerbosch function call wrapper
	void GetMaxIndSetsBK();


	/************ Tomita ************/

	// Tomita algorithm to get maximal independant sets (stored in cliques)
	void ExpandTomita(std::set<u64> &SUBG, std::set<u64> &CAND, std::set<u64> &Q);


public:
	Graph() {}
	Graph(u64 N) : N(N) {
		adj.resize(N*N);
		sigma.resize(N);
		for (u64 i = 0; i < N; i++)
			sigma[i] = i;		
	}

	/************ Initialization ************/

	// Attribute edges randomly
	void Randomize();
	// Initialize graph from file filename
	void InitFromFile(const char* filename);
	// Init hexagone shapped graph
	void MakeHexagone();


	/************ Bicliques ************/

	// Algorithm 1
	std::set<std::set<u64>> GetBicliques();
	// Algorithm 2
	std::set<std::set<u64>> GetBicliques2();
	//
	void GetBicliquesParallel();

	/************ Others ************/

	// Print graph in terminal
	void Print() const;
	// Write graph to file filename
	void WriteToFile(const char* filename);
};