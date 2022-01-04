#include <iostream>
#include <iterator>
#include <set>
#include "graph.hpp"

using namespace std;

bool Isproper(Graph g, set<int> maxIndset )
{
    for (auto i = maxIndset.begin(); i!= (maxIndset.end())--;i++)
        for(auto j = i++; j!=maxIndset.end();j++)
        {
            if (g.areConnected(*i,*j) ) return true;
        }
    return false;
}

int main()
{
    return 0;
}