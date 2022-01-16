#include <map>
#include <set>
#include <iostream>

#include "suffixTree.hpp"


/* =========================== CONSTRUCTION =========================== */

// Ajoute un arbre descendant
void Tree::addSubtree(u64 i)
{
    Tree subtree(i);
    subtrees.insert({i, subtree});
}

// place un set dans la hiérarchie de l'arbre de suffix
void Tree::insert(std::set<u64> set)
{
    // Extraction du premier élément du set
    auto iIter = set.begin();
    u64 i = *(iIter);

    addSubtree(i);
    
    // si le set a plus d'un élément
    if (set.size() > 1)
    {
        set.erase(iIter);
        subtrees[i].insert(set);
    }
}



/* =========================== BRANCHES =========================== */

// Enumère toutes les branches et les stocke dans bicliques
void Tree::getBranches(std::set<std::set<u64>>& bicliques, std::set<u64>& tmpSet)
{
    if(subtrees.size() != 0)
    {
        for(const auto& [i, subtree] : subtrees)
        {
            tmpSet.insert(i);
            subtrees[i].getBranches(bicliques, tmpSet);
            tmpSet.erase(i);
        }
    } else {
        bicliques.insert(tmpSet);
    }
}

// Enumère toutes les branches de taille maximale
std::set<std::set<u64>> Tree::getMaxBranches()
{
    std::set<std::set<u64>> bicliques;
    std::set<u64> tmpSet;
    std::set<std::set<u64>> bicliquesMax;

    // Enumère tout les bicliques
    getBranches(bicliques, tmpSet);

    // Taille max du biclique
    u64 maxSize = 0;
    for(const auto& biclique : bicliques)
        if(biclique.size()>maxSize) maxSize = biclique.size();
    
    // On garde uniquement les bicliques maximales
    for(const auto& biclique : bicliques)
        if( biclique.size() == maxSize) bicliquesMax.insert(biclique);

    return bicliquesMax;
}



/* =========================== VISUALISATION =========================== */

void Tree::print()
{
    std::set<std::set<u64>> bicliques;
    std::set<u64> tmpSet;

    // Enumère tout les bicliques
    getBranches(bicliques, tmpSet);

    std::cout << bicliques.size() << "\n";
    for(auto& set : bicliques) {
        for(auto& i : set) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}
