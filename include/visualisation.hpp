#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "graph.hpp"

void writeGraph(Graph& graph, std::string filename);

std::vector<int> readGraph(std::string filename);