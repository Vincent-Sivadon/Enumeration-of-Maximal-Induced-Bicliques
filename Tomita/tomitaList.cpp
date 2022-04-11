#include <iostream>
#include <vector>

#include <algorithm>


std::vector<int> diffOfSets(std::vector<int> &A, std::vector<int> &B) {
  std::vector<int>::iterator it;
  std::vector<int> output;
  for (auto i : A) {
    it = std::find(B.begin(), B.end(), i);
    if (it == B.end()) output.push_back(i);
  }
  return output;
}


std::vector<int> intersectionOfSets(std::vector<int> &A, std::vector<int> &B) {
  std::vector<int>::iterator it;
  std::vector<int> output;
  for (auto i : B) {
    it = std::find(A.begin(), A.end(), i);
    if (it != A.end()) output.push_back(i);
  }
  return output;
}

std::vector<int> unionOfSets(std::vector<int> &A, std::vector<int> &B) {
  std::vector<int>::iterator it;
  std::vector<int> output = A;

  for (auto i : B) {
    it = std::find(A.begin(), A.end(), i);
    if (it == A.end()) A.push_back(i);
  }
  return output;
}


int choosePivotElement(std::vector<int> &CAND, std::vector<int> &SUBG,
                       std::vector<std::vector<int>> &graph) {
  int pivot = -1;
  int maxSize = -1;

  for (const auto &u : SUBG) {
    std::vector<int> gammaU = graph[u];
    std::vector<int> inter = intersectionOfSets(gammaU, CAND);
    int sizeOfInter = inter.size();

    if (sizeOfInter >= maxSize) {
      pivot = u;
      maxSize = sizeOfInter;
    }
  }

  return pivot;
}

bool isSetEMpty(std::vector<int> &setTocheck) { return (setTocheck.size() == 0) ? true : false; }

void expandTomitaList(std::vector<int> SUBG, std::vector<int> CAND,
                      std::vector<std::vector<int>> &graph) {
  if (isSetEMpty(SUBG)) std::cout << " clique, ";
  else {
    int currentPivot = choosePivotElement(SUBG, CAND, graph);
    std::vector<int> gammaPivot = graph[currentPivot];
    std::vector<int> EXTu = diffOfSets(CAND, gammaPivot);
    while (not EXTu.empty()) {
      int q = EXTu[0];
      std::cout << q << ", ";
      std::vector<int> gammaQ = graph[q];
      std::vector<int> SUBGq = intersectionOfSets(SUBG, gammaQ);
      std::vector<int> CANDq = intersectionOfSets(CAND, gammaQ);
      expandTomitaList(SUBGq, CANDq, graph);
      std::vector<int> singleq = {q};
      CAND = diffOfSets(CAND, singleq);
      EXTu = diffOfSets(CAND, gammaPivot);
      std::cout << "back, ";
    }
  }
}

void cliques(std::vector<std::vector<int>> &graph, std::vector<int> vertices) {
  std::cout << " Start of clique finding !"
            << "\n\n";
  expandTomitaList(vertices, vertices, graph);
  std::cout << " End of clique finding !"
            << "\n";
}

void addEdge(std::vector<std::vector<int>> &graph, int a, int b) {
  graph[a].push_back(b);
  graph[b].push_back(a);
}


int main() {
  std::vector<std::vector<int>> graph(9);

  addEdge(graph, 0, 1);
  addEdge(graph, 0, 8);
  addEdge(graph, 1, 2);
  addEdge(graph, 2, 3);
  addEdge(graph, 2, 7);
  addEdge(graph, 2, 8);
  addEdge(graph, 3, 4);
  addEdge(graph, 3, 5);
  addEdge(graph, 3, 6);
  addEdge(graph, 3, 7);
  addEdge(graph, 4, 5);
  addEdge(graph, 5, 7);
  addEdge(graph, 5, 6);
  addEdge(graph, 6, 7);
  addEdge(graph, 8, 1);


  std::vector<int> V(graph.size());
  for (int i = graph.size() - 1; i > -1; i--) V[i] = i;

  cliques(graph, V);
  return 0;
}
