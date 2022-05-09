#include <iostream>
#include <list>
#include <vector>
#include <assert.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

class Tomita
{
public:
    Tomita(std::vector<std::vector<int>> listAdj, int const nbVertices);
    virtual ~Tomita();
    void listofMaxCliques(std::vector<std::vector<int>> listAdj, int nbVertices, std::vector<int> &vertices);
    void expand(std::vector<int> v1, std::vector<int> v2, std::vector<int> Qu);

private:
    std::vector<std::vector<int>> _listAdj;
    int _nbVertices;
};

Tomita::Tomita(std::vector<std::vector<int>> listAdj, int const nbVertices)
    : _listAdj(listAdj), _nbVertices(nbVertices)
{
}

Tomita::~Tomita() {}

bool isSetEMpty(std::vector<int> setTocheck)
{
    return (setTocheck.size() == 0) ? true : false;
}

std::vector<int> unionOfSets(std::vector<int> &A, std::vector<int> &B)
{
    std::vector<int>::iterator it;
    for (auto i : B)
    {
        it = std::find(A.begin(), A.end(), i);
        if (it == A.end())
            A.push_back(i);
    }
    return A;
}

std::vector<int> intersectionOfSets(std::vector<int> &A, std::vector<int> &B)
{
    std::vector<int>::iterator it;
    std::vector<int> output;
    for (auto i : B)
    {
        it = std::find(A.begin(), A.end(), i);
        if (it != A.end())
            output.push_back(i);
    }
    return output;
}

std::vector<int> diffOfSets (std::vector<int> &A, std::vector<int> &B)
{
    std::vector<int>::iterator it;
    std::vector<int> output;
    for (auto i : A)
    {
        it = std::find(B.begin(), B.end(), i);
        if (it == B.end())
            output.push_back(i);
    }
    return output;
}


void Tomita::expand(std::vector<int> v1, std::vector<int> v2, std::vector<int> Qu)
{
    if (isSetEMpty(v1))
        std::cout << "clique,";
    else
    {
        int max_size = 0;
        int candidat = v1[0];
        for(auto u:v1)
        {
            std::vector<int> tmp_gammaU = _listAdj[u];
            int tmp = (intersectionOfSets(v2,tmp_gammaU)).size();
            max_size = ((tmp > max_size) ? tmp : max_size);
            candidat = u;
        }
        std::vector<int> gammaU = _listAdj[candidat];
        std::vector<int> setDiff = diffOfSets(v2,gammaU);
        while (! isSetEMpty(setDiff))
        {
            for (auto q:setDiff)
            {
                std::cout << "q, " <<",";
                std::vector <int> singleQ = {q};
                Qu = unionOfSets(Qu, singleQ);

                std::vector <int> subgQ = intersectionOfSets(v1,_listAdj[q]);
                std::vector <int> candQ = intersectionOfSets(v2, _listAdj[q]);
                expand(subgQ,candQ,Qu);
                v2 = diffOfSets(v2, singleQ);
                std::cout << "back," << "\n";
                Qu = diffOfSets(Qu, singleQ);
            }
        }
    }
}

void Tomita::listofMaxCliques(std::vector<std::vector<int>> listAdj, int nbVertices, std::vector<int> &vertices)
{
    int i;
    std::vector<int> Q{};
    expand(vertices, vertices,Q);
}