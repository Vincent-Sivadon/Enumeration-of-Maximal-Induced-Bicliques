#pragma once

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <stdbool.h>

typedef unsigned long long u64;

/* ============================== INTERFACE vers une représentation d'adjacence ============================== */
struct Adj
{
    /* =========== CONSTRUCTEURS =========== */
    virtual ~Adj() = default;

    /* ============= PRINCIPAL ============= */
    virtual void connect(u64 i, u64 j) = 0;      // Crée un lien entre deux sommets i et j
    virtual bool areConnected(u64 i, u64 j) = 0; // Indique si deux sommets sont reliés ou non
    virtual std::vector<u64> findDegrees() = 0;
    virtual void deleteVertex(u64 i) = 0;
    virtual void findMinDegree(u64 &vertexMinDeg, u64 &minDeg) = 0;
    virtual void degenOrder(std::vector<u64> &orderedVertices) = 0;

    /* ============ VISUALISATION ============ */
    virtual void print() const = 0; // Affiche le contenu de l'adjacence
};

/* ============================== IMPLEMENTATION de Adj : MATRICE D'ADJACENCE ============================== */
struct Mat : public Adj
{
    /* ============== MEMBRES ============== */
    std::vector<u64> adj;
    u64 N;

    /* =========== CONSTRUCTEURS =========== */
    Mat(u64 N) : N(N) { adj.resize(N * N); }
    virtual ~Mat() = default;

    /* ============= PRINCIPAL ============= */
    void connect(u64 i, u64 j) override;      // Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
    bool areConnected(u64 i, u64 j) override; // Indique si deux sommets sont reliés ou non
    std::vector<u64> findDegrees() override;
    void deleteVertex(u64 i) override;
    void findMinDegree(u64 &vertexMinDeg, u64 &minDeg) override;
    void degenOrder(std::vector<u64> &orderedVertices) override;

    /* ============ VISUALISATION ============ */
    void print() const override; // Affiche le contenu de la matrice d'adjacence
};

/* ============================== IMPLEMENTATION de Adj : LISTE D'ADJACENCE ============================== */
struct Lst : public Adj
{
    /* ============== MEMBRES ============== */
    std::map<u64, std::set<u64>> adj;
    u64 N;

    /* =========== CONSTRUCTEURS =========== */
    Lst(u64 N) : N(N) {}
    virtual ~Lst() = default;

    /* ============= PRINCIPAL ============= */
    void connect(u64 i, u64 j) override;      // Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
    bool areConnected(u64 i, u64 j) override; // Indique si deux sommets sont reliés ou non
    std::vector<u64> findDegrees() override;
    void deleteVertex(u64 i) override;
    void findMinDegree(u64 &vertexMinDeg, u64 &minDeg) override;
    void degenOrder(std::vector<u64> &orderedVertices) override;

    /* ============ VISUALISATION ============ */
    void print() const override; // Affiche le contenu de la liste d'adjacence
};

/* ====================== MATRICE : implementation ====================== */
// Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
void Mat::connect(u64 i, u64 j)
{
    adj[i * N + j] = 1;
    adj[j * N + i] = 1;
}

// Indique si deux sommets sont reliés ou non
bool Mat::areConnected(u64 i, u64 j)
{
    // Si adj[i][j] = 1 alors connectés sinon adj[i][j] = 0
    return adj[i * N + j];
}

// Affiche le contenu de la matrice d'adjacence
void Mat::print() const
{
    // Pour chaque paire de sommet (i,j)
    for (u64 i = 0; i < N; i++)
    {
        for (u64 j = 0; j < N; j++)
        {
            std::cout << adj[i * N + j] << " ";
        }
        std::cout << "\n";
    }
}

//
std::vector<u64> Mat::findDegrees()
{
    std::vector<u64> vertDeg(N);

    for (int i = 0; i < N; i++)
    {
        u64 nbVoisins = 0;
        for (int j = 0; j < N; j++)
            if (adj[i * N + j] == 1)
                nbVoisins++;
        vertDeg[i] = nbVoisins;
    }

    return vertDeg;
}

//
void Mat::deleteVertex(u64 i)
{
    // Search for all i neighboors
    for (int k = 0; k < N; k++)
        if (adj[i * N + k] == 1)
            adj[i * N + k] = 0;
}

//
void Mat::findMinDegree(u64 &vertexMinDeg, u64 &minDeg)
{
    std::vector<u64> vertDeg = findDegrees();
    vertexMinDeg = 0;
    minDeg = 0;

    for (u64 i = 0; i < N; i++)
        if (vertDeg[i] < minDeg)
        {
            minDeg = vertDeg[i];
            vertexMinDeg = i;
        }
}

void Mat::degenOrder(std::vector<u64> &orderedVertices)
{
    // Allocation
    orderedVertices.resize(N);

    u64 tmp = 0;
    u64 vertexMinDeg, minDeg;

    for (int i = 0; i < N; i++)
    {
        findMinDegree(vertexMinDeg, minDeg);
        orderedVertices[i] = vertexMinDeg;

        deleteVertex(i);
    }
}

/* ====================== LISTE : implementation ====================== */
// Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
void Lst::connect(u64 i, u64 j)
{
    adj[i].insert(j); // insère i dans la liste des voisins de j
    adj[j].insert(i); // insère j dans la liste des voisins de i
}

// Indique si deux sommets sont reliés ou non
bool Lst::areConnected(u64 i, u64 j)
{
    // pour chaque sommet 'v' de la liste des voisins de i
    for (const auto &v : adj[i])
        if (v == j)
            return true;
    return false;
}

// Affiche le contenu de la liste d'adjacence
void Lst::print() const
{
    // Pour chaque sommet 'vertex' et sa liste de voisin 'vertexNeighboors'
    for (const auto &[vertex, vertexNeighboors] : adj)
    {
        //
        std::cout << "\n Neighboors of vertex " << vertex << " :\n";

        // affiche l'indice de chaque sommet de la liste de voisins
        for (const auto &i : vertexNeighboors)
            std::cout << " -> " << i;

        //
        std::cout << "\n";
    }
}

std::vector<u64> Lst::findDegrees()
{
    std::vector<u64> vertDeg(N);

    for (const auto &adji : adj)
        vertDeg[adji.first] = adji.second.size();

    return vertDeg;
}

//
void Lst::deleteVertex(u64 i)
{
    std::set<u64> voisins;
    voisins = adj[i];

    adj.erase(i);

    for (const auto &node : voisins)
        adj[node].erase(i);
}

void Lst::findMinDegree(u64 &vertexMinDeg, u64 &minDeg)
{
    std::vector<u64> vertDeg = findDegrees();
    vertexMinDeg = 0;
    minDeg = 0;

    for (u64 i = 0; i < N; i++)
        if (vertDeg[i] < minDeg)
        {
            minDeg = vertDeg[i];
            vertexMinDeg = i;
        }
}

void Lst::degenOrder(std::vector<u64> &orderedVertices)
{
    // Allocation
    orderedVertices.resize(N);

    u64 tmp = 0;
    u64 vertexMinDeg, minDeg;

    for (int i = 0; i < N; i++)
    {
        findMinDegree(vertexMinDeg, minDeg);
        orderedVertices[i] = vertexMinDeg;

        deleteVertex(i);
    }
}