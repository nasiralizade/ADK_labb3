/**
 * Exempel på in- och utdatahantering för maxflödeslabben i kursen
 * ADK.
 *
 * Använder iostreams i C++.
 * Anmärkning: scanf/printf-rutinerna från C-exemplet går att använda
 * även i C++ och är ofta märkbart snabbare än cin/cout som det här
 * programmet använder.
 *
 * Author: Per Austrin
 */

#include "Biprep.h"

int main(void) {
    // Två trick för att göra cin/cout lite snabbare.
    // Se http://kattis.csc.kth.se/doc/iostreamio
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    Biprep biprep;
    biprep.readBipartiteGraph();
    biprep.writeFlowGraph();
    biprep.readMaxFlowSolution();
    biprep.writeBipMatchSolution();
    // debugutskrift
    cerr << "Bipred avslutar\n";
    return 0;
}