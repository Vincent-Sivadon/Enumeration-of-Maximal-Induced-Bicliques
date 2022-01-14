#include <map>
#include <set>
#include <iostream>

#include "suffixTree.hpp"


namespace GM {


// Enumère tout les 
void Tree::getBranches(std::set<std::set<u64>>& bicliques, std::set<u64>& tmpSet)
{
    for(const auto& [i, subtree] : subtrees)
    {
        tmpSet.insert(i);
        subtrees[i].getBranches(bicliques, tmpSet);
        tmpSet.erase(i);
    }

    bicliques.insert(tmpSet);
}

// Enumère tout les "mots maximals" du suffix tree
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


void Tree::addSubtree(u64 i)
{
    Tree subtree(i);
    subtrees.insert({i, subtree});
}


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


void Tree::print()
{
    if (id != -1) 
        std::cout << id << " ";
    for (auto [id, subtree] : subtrees)
        subtree.print();
    std::cout << "\n";
}


} // end namespace GM