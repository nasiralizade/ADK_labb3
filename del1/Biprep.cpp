//
// Created by Nasir Alizade on 2024-11-10.
//

#include "Biprep.h"

void Biprep::readBipartiteGraph() {
    // Läs antal hörn och kanter
    cin >> x >> y >> e;

    numVertices = x + y + 2; // 2 extra för source och sink
    adjA.resize(numVertices+1); // 1-indexing

    for (int i = 1; i <= e; i++) {
        // lägg till kanter från A till B som vi får från input
        int a, b;
        cin >> a >> b;
        adjA[a + 1].push_back(b + 1);
    }

    for (int i = 1; i <= x; i++) {
        // lägg till kanter från source till vänster
        adjA[1].push_back(i + 1);
    }
    for (int i = x+1; i < numVertices-1; i++) {
        // lägg till kanter från höger till sink
        adjA[i+1].push_back(numVertices);
    }
}

void Biprep::writeFlowGraph() {
    int totalEdges = x+y+e;
    cout<<numVertices<<"\n";
    cout<<"1 "<< numVertices<<"\n"; // source(1) to sink (numberOfVertices)
    cout<<totalEdges<<"\n";
    for (int i=1; i<=numVertices; i++) {
        for (int j: adjA[i]) {
            cout<<i<<" "<<j<<" 1\n";
        }
    }
    // Var noggrann med att flusha utdata när flödesgrafen skrivits ut!
    cout.flush();
    // Debugutskrift
    cerr << "Skickade iväg flödesgrafen\n";
}

void Biprep::readMaxFlowSolution() {
    // Läs in antal hörn, kanter, källa, sänka, och totalt flöde
    // (Antal hörn, källa och sänka borde vara samma som vi i grafen vi
    // skickade iväg)
    int totalFlow,source,sink,edgeCount;
    cin>>numVertices>>source>>sink>>totalFlow>>edgeCount;
    adjB.resize(numVertices+1);
    for (int i = 0; i < edgeCount; ++i) {
        int u, v, f;
        cin >> u >> v >> f;
        if (f == 1 && u != 1 && v != numVertices) {
            adjB[u-1].push_back(v-1);
        }
    }
}

void Biprep::writeBipMatchSolution() {
    // rad 1
    cout << x << " " << y << "\n";
    int matchCount = 0;
    for (int i=1; i<=x+1; i++) { // only between X and Y
        matchCount += adjB[i].size();
    }
    // rad 2
    cout << matchCount << "\n";


    for (int i = 1; i <= x; ++i) {
        for (int j: adjB[i]) {
            cout << i << " " << j << "\n";
        }
    }
    cout.flush();
    // Debugutskrift
    cerr << "Skickade iväg matchningen\n";
}