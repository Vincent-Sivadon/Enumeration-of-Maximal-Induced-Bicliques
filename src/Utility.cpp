#include "Utility.hpp"

void printSet(std::set<u64>& set)
{
    for (const auto& node : set)
        std::cout << node << " ";
    std::cout << std::endl;
}

void printSets(std::set<std::set<u64>>& sets)
{
    for (const auto& set : sets)
    {
        for (const auto& node : set)
            std::cout << node << " ";
        std::cout << std::endl;
    }
}

void printVec(std::vector<u64>& vec)
{
    for (const auto& i : vec)
        std::cout << i << " ";
    std::cout << std::endl;
}