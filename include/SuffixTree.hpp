#pragma once

#include <map>
#include <set>

typedef unsigned long long u64;

// Suffix Tree
struct Tree {
  int id;                         // indice de l'arbre (-1 par défaut)
  std::map<u64, Tree> subtrees;   // arbre descendants

  Tree() : id(-1){};      // indice de l'arbre vaut -1 par défaut
  Tree(u64 i) : id(i){};

  /* place un set dans la hiérarchie de l'arbre de suffix */
  void insert(std::set<u64> set);   
  /* ajoute un arbre descendant */
  void addSubtree(u64 i);

  /* Enumère toutes les branches et les stocke dans bicliques */
  void getBranches(std::set<std::set<u64>> &bicliques,
                   std::set<u64> &tmpSet);
  /* énumère toutes les branches de taille maximale */
  std::set<std::set<u64>> getMaxBranches();   

  /* affiche dans le terminal les branches de l'arbre */
  void print();
};
