#pragma once

#include <map>
#include <set>

typedef unsigned long long u64;

/* =========================== REPRESENTATION D'UN ARBRE DE SUFFIX
 * =========================== */

struct Tree {
  // ============================== MEMBRES ==============================
  int id;                         // indice de l'arbre (-1 par défaut)
  std::map<u64, Tree> subtrees;   // arbre descendants

  // =========================== CONSTRUCTEURS ===========================
  Tree() : id(-1){};   // indice de l'arbre vaut -1 par défaut
  Tree(u64 i) : id(i){};

  // ============================= FONCTIONS =============================
  // Pour construire l'arbre
  // -------------------------------------------------------------
  void insert(std::set<u64> set);   // place un set dans la hiérarchie de l'arbre de suffix
  void addSubtree(u64 i);           // ajoute un arbre descendant

  // ============================= BRANCHES =============================
  void getBranches(std::set<std::set<u64>> &bicliques,
                   std::set<u64> &tmpSet);    // Enumère toutes les branches et les
                                              // stocke dans bicliques
  std::set<std::set<u64>> getMaxBranches();   // énumère toutes les branches de taille maximale

  // ============================= VISUALISATION =============================
  void print();   // affiche dans le terminal les branches de l'arbre
};
