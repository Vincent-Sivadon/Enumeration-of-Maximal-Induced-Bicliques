#include <map>
#include <set>

typedef unsigned long long u64;

namespace GM {

struct Tree {
    int id;
    std::map<u64, Tree> subtrees;

    Tree() : id(-1) {};
    Tree(u64 i) : id(i) {};

    void insert(std::set<u64> set);
    void print();
    void addSubtree(u64 i);
    void getBranches(std::set<std::set<u64>>& bicliques, std::set<u64>& tmpSet);
    std::set<std::set<u64>> getMaxBranches();
};


} // end namespace GM