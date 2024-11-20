//
// Created by Nasir Alizade on 2024-11-10.
//

#ifndef BIPREP_H
#define BIPREP_H
#include <iostream>
#include <list>
#include <vector>
using std::cin;
using std::cout;
using std::cerr;
using std::vector;


class Biprep {
private:
    vector<std::list<int> > adjA;
    vector<std::list<int> > adjB;
    int x, y, e, numVertices;
public:
    Biprep() = default;

    void readBipartiteGraph();
    void writeFlowGraph();
    void readMaxFlowSolution();
    void writeBipMatchSolution();
};



#endif //BIPREP_H