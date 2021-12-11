#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "graph.hpp"

struct Vector {
    double x;
    double y;
    Vector() {}
    Vector(double x, double y) :x(x), y(y) {} 
};

std::vector<int> readGraph(std::string filename);

void drawGraph(Graph& graph);