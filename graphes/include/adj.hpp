#pragma once

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <stdbool.h>

typedef unsigned long long u64;
typedef struct vertexMin
{
    int degree;
    int vertex;
} vertexMin;

/**
 * @brief structure dont les champs permettent de stocker les sommets dans l'ordre de leurs suppression ainsi que leurs degrés respectifs
 * degTab  -> contient les degrés des sommets,
 * vertTab -> contient les sommets.
 */
typedef struct degenElem
{
    std::vector<int> degTab;
    std::vector<int> vertTab;
} degenElem;

/* ============================== INTERFACE vers une représentation d'adjacence ============================== */
struct Adj
{
    /* =========== CONSTRUCTEURS =========== */
    virtual ~Adj() = default;

    /* ============= PRINCIPAL ============= */
    virtual void connect(u64 i, u64 j) = 0;               // Crée un lien entre deux sommets i et j
    virtual bool areConnected(u64 i, u64 j) = 0;          // Indique si deux sommets sont reliés ou non
    virtual std::vector<int> verticesdegrees() const = 0; // Permet de connaitre Le degré de chaque sommet dans le graphe
    virtual void deConnected(u64 i, u64 j) = 0;           // supprimer le lien entre deux sommets i et j
    virtual vertexMin findMinVertex() = 0;                // Trouver le sommet de degré minimal
    virtual degenElem degenOrder() = 0;                   // Fonction permettant de connaitre l'ordre de dégénrescence du graphe.
    virtual bool isGraphEmpty() const = 0;                // Fonction permettant de vérifier si le graphe est vide ou pas.
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
    void connect(u64 i, u64 j) override;               // Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
    bool areConnected(u64 i, u64 j) override;          // Indique si deux sommets sont reliés ou non
    std::vector<int> verticesdegrees() const override; // Permet de connaitre le degré de toux les sommets du graphe
    void deConnected(u64 i, u64 j) override;           // Supprimer le lien entre deux sommets i et j
    vertexMin findMinVertex() override;                // Trouver le sommet de degré minimal
    degenElem degenOrder() override;                   // Fonction permettant de connaitre l'ordre de dégénrescence du graphe.
    bool isGraphEmpty() const override;                         // Fonction permettant de savoir si le graphe est vide ou pas.
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
    void connect(u64 i, u64 j) override;               // Crée un lien entre deux sommets i et j (lors de la construction d'un graphe)
    bool areConnected(u64 i, u64 j) override;          // Indique si deux sommets sont reliés ou non
    std::vector<int> verticesdegrees() const override; // Permet de connaitre le degré de toux les sommets du graphe
    void deConnected(u64 i, u64 j) override;           // Supprimer le lien entre deux sommets i et j
    vertexMin findMinVertex() override;                // Trouver le sommet de degré minimal
    degenElem degenOrder() override;                   // Fonction permettant de connaitre l'ordre de dégénrescence du graphe.
    bool isGraphEmpty() const override;                         // Fonction permettant de savoir si le graphe est vide ou pas.
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

// Permet de connaitre le degré de tous les sommets du graphe
std::vector<int> Mat::verticesdegrees() const
{
    std::vector<int> vertDeg(N);
    int ctn = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (adj[i * N + j] == 1)
                ctn++;
    vertDeg.push_back(ctn);

    return vertDeg;
}

// Supprimé le lien entre deux sommets i et j
void Mat::deConnected(u64 i, u64 j)
{
    adj[i * N + j] = 0;
    adj[j * N + i] = 0;
}

// Trouver le sommet de degré minimal
vertexMin Mat::findMinVertex()
{
    vertexMin s;
    std::vector<int> degrees = verticesdegrees();
    int vertexWithMinDeg = 0;
    for (int i = 0; i < N; i++)
    {
        if (degrees[i] <= 0)
            continue;
        vertexWithMinDeg = i;
        break;
    }
    int minDeg = degrees[vertexWithMinDeg];

    for (int i = 0; i < N; i++)
    {
        if (degrees[i] < minDeg)
        {
            minDeg = degrees[i];
            vertexWithMinDeg = i;
        }
    }
    s.degree = minDeg;
    s.vertex = vertexWithMinDeg;

    return s;
}

// Calcul de l'ordre de degenerescence du graphe.
degenElem Mat::degnOrder() 
{
    degenElem dge;
    std::vector<int> rmdeg;
    std::vector<int> rmVertices;
    int tmp = 0;
    while (!isGraphEmpty() && tmp++ < 10)
    {
        vertexMin s = findMinVertex();
        rmdeg.push_back(s.degree);
        rmVertices.push_back(s.vertex);

        for (auto u : graph[s.vertex])
        {
            deConnected(s.vertex,u);
        }
    }
    dge.degTab  = rmdeg;
    dge.vertTab = rmVertices;
    return dge;
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

// Permet de connaitre le degré de tous les sommets du graphe
std::vector<int> Lst::verticesdegrees() const
{
    std::vector<int> vertDeg(N);

    for (auto &i : adj)
        vertDeg.push_back(i.second.size());
    return vertDeg;
}

// Supprimé le lien entre deux sommets i et j
void Lst::deConnected(u64 i, u64 j)
{
    // parcourir la liste des voisins du premier sommet à la recherche du second puis le supprimer dès qu'on l'aura trouver
    for (int k = 0; k < adj[i].size(); k++)
    {
        if (adj[i][k] == j)
        {
            adj[i].erase(adj[i].begin + k);
            break;
        }
    }

    // parcourir la liste des voisins du deuxième sommet à la recherche du premier puis le supprimer dès qu'on l'aura trouver
    for (int k = 0; k < adj[j].size(); k++)
    {
        if (adj[j][k] == i)
        {
            adj[j].erase(adj[j].begin() + k);
            break;
        }
    }
}

// Trouver le sommet de degré minimal
vertexMin Lst::findMinVertex()
{
    vertexMin s;
    std::vector<int> degrees = verticesdegrees();
    int vertexWithMinDeg = 0;
    for (int i = 0; i < N; i++)
    {
        if (degrees[i] <= 0)
            continue;
        vertexWithMinDeg = i;
        break;
    }
    int minDeg = degrees[vertexWithMinDeg];

    for (int i = 0; i < N; i++)
    {
        if (degrees[i] < minDeg)
        {
            minDeg = degrees[i];
            vertexWithMinDeg = i;
        }
    }
    s.degree = minDeg;
    s.vertex = vertexWithMinDeg;

    return s;
}

// Verifier si le graphe est vide ou pas
bool Lst::isGraphEmpty() const
{
    auto degrees = verticesdegrees() const;
    return std::all_of(degrees.cbegin(), degrees.cend(), [](auto const &e) {
        return e == 0;
    });
}

// calcul de l'ordre de degenerescence du graphe
degenElem Lst::degnOrder() 
{
    degenElem dge;
    std::vector<int> rmdeg;
    std::vector<int> rmVertices;
    int tmp = 0;
    while (!isGraphEmpty() && tmp++ < 10)
    {
        vertexMin s = findMinVertex();
        rmdeg.push_back(s.degree);
        rmVertices.push_back(s.vertex);

        for (auto u : graph[s.vertex])
        {
            deConnected(s.vertex,u);
        }
    }
    dge.degTab  = rmdeg;
    dge.vertTab = rmVertices;
    return dge;
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