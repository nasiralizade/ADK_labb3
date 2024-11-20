#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <queue>
#include <climits>
#include <sstream>
#include <list>


struct Edge {
    int source, sink, capacity, flow;
    std::shared_ptr<Edge> reverse;

    Edge(const int source, const int sink, const int capacity) : source(source), sink(sink), capacity(capacity),
                                                                 flow(0) {
    }
};

using EdgePtr = std::shared_ptr<Edge>;
using EdgeList = std::vector<EdgePtr>;
using Graph = std::array<EdgeList, 10005>;

void addEdge(Graph &graph, int source, int sink, int capacity);

int calcMaxFlow(const Graph &graph, int s, int t);

bool bfs(const Graph &graph, int s, int t, std::vector<EdgePtr> &path) {
    std::queue<int> q;
    q.push(s);
    //std::fill(path.begin(), path.end(), nullptr);
    path.assign(graph.size(), nullptr);
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (auto &edge: graph[current]) {
            // Gå igenom alla kanter från noden
            if (path[edge->sink] == nullptr && edge->sink != s && edge->capacity > edge->flow) {
                path[edge->sink] = edge; // Spara kanten
                q.push(edge->sink); // Lägg till noden i kön
            }
        }
    }
    return path[t] != nullptr;
}

int calcMaxFlow(const Graph &graph, int s, int t) {
    int maxFlow = 0;
    std::vector<EdgePtr> path(graph.size(), nullptr);

    while (bfs(graph, s, t, path)) {
        // Så länge det finns en väg från s till t
        int flow_i = INT_MAX;
        for (auto edge = path[t]; edge != nullptr; edge = path[edge->source]) {
            flow_i = std::min(flow_i, edge->capacity - edge->flow);
        }
        for (auto edge = path[t]; edge != nullptr; edge = path[edge->source]) {
            edge->flow += flow_i;
            edge->reverse->flow -= flow_i;
        }
        maxFlow += flow_i;
    }
    return maxFlow;
}

void addEdge(Graph &graph, int source, int sink, int capacity) {
    auto edge = std::make_shared<Edge>(source, sink, capacity);
    auto reverse = std::make_shared<Edge>(sink, source, 0);
    edge->reverse = reverse;
    reverse->reverse = edge;
    graph[source].push_back(edge);
    graph[sink].push_back(reverse);
}

// steg
class Biprep {
private:
    std::vector<std::list<int> > adjA;
    std::vector<std::list<int> > adjB;
    int x, y, e, numVertices;

public:
    Biprep() = default;

    void readBipartiteGraph();

    void writeFlowGraph();

    void readMaxFlowSolution();

    void writeBipMatchSolution();

    int num_vertices() const {
        return numVertices;
    }

    Graph flowGraph;
};

void Biprep::readBipartiteGraph() {
    std::cin >> x >> y >> e;
    numVertices = x + y + 2;
    adjA.resize(numVertices + 1);

    for (int i = 0; i < e; ++i) {
        // Läs in kanterna som tas emot från standard in och lägg till i adjA
        int a, b;
        std::cin >> a >> b;
        adjA[a + 1].push_back(b + 1);
    }

    for (int i = 1; i <= x; ++i) {
        // Lägg till kanter från source till vänster (source = 1)
        adjA[1].push_back(i + 1);
    }

    for (int i = x + 1; i < numVertices - 1; ++i) {
        // Lägg till kanter från höger till sink (sink = numVertices)
        adjA[i + 1].push_back(numVertices);
    }
}

void Biprep::writeFlowGraph() {
    for (int i = 1; i <= numVertices; ++i) {
        for (int j: adjA[i]) {
            //addEdge(flowGraph, i, j, 1);
            if (i < flowGraph.size() && j < flowGraph.size()) {
                addEdge(flowGraph, i, j, 1);
            } else {
                std::cerr << "Index out of range: i = " << i << ", j = " << j << "\n";
            }
        }
    }
}

void Biprep::readMaxFlowSolution() {
    adjB.resize(numVertices + 1);

    for (int u = 1; u <= numVertices; ++u) {
        // Loop över noder i X
        for (auto &edge: flowGraph[u]) {
            if (edge->flow == 1 && edge->source != 1 && edge->sink != numVertices) {
                adjB[u-1].push_back(edge->sink-1);
            }
        }
    }
}

void Biprep::writeBipMatchSolution() {
    std::cout << x << " " << y << "\n";
    int matchCount = 0;
    for (int i = 1; i <= x; ++i) {
        matchCount += adjB[i].size();
    }
    std::cout << matchCount << "\n";

    for (int i = 1; i <= x; ++i) {
        for (int j: adjB[i]) {
            std::cout << i << " " << j << "\n";
        }
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Biprep biprep;
    biprep.readBipartiteGraph();
    biprep.writeFlowGraph();
    auto t = biprep.num_vertices();
    int maxFlow = calcMaxFlow(biprep.flowGraph, 1, t);
    biprep.readMaxFlowSolution();
    biprep.writeBipMatchSolution();
    return 0;
}
