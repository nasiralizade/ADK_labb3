#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <queue>
#include <climits>
#include <sstream>
// // labb 3 del 3

/**
 * Representerar en kant i en graf
 */
struct Edge {
    int source, sink, capacity, flow;
    std::shared_ptr<Edge> reverse;

    Edge(const int source, const int sink, const int capacity) : source(source), sink(sink), capacity(capacity),
                                                                 flow(0) {
    }
};

using EdgePtr = std::shared_ptr<Edge>; // För att slippa skriva std::shared_ptr<Edge> hela tiden
using EdgeList = std::vector<EdgePtr>;
using Graph = std::array<EdgeList, 4001>; // En array av listor med edges (max 4000 noder)

void readFlowAndSolve();

void addEdge(Graph &graph, int source, int sink, int capacity);

int calcMaxFlow(const Graph &graph, int s, int t);

void printGraph(const Graph &graph, int number_of_vertices, int s, int t, int max_flow);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    readFlowAndSolve();
    return 0;
}

/**
 * Läser in en graf och löser maxflödesproblemet
 */
void readFlowAndSolve() {
    // Antal noder, startnod, slutnod, antal kanter
    int numberOfVertices, s, t, numberOfEdges;
    Graph graph;
    std::cin >> numberOfVertices >> s >> t >> numberOfEdges;
    int u, v, c; // Källa, sänka, kapacitet
    while (numberOfEdges--) {
        std::cin >> u >> v >> c;
        addEdge(graph, u, v, c);
    }
    int maxFlow = calcMaxFlow(graph, s, t);
    printGraph(graph, numberOfVertices, s, t, maxFlow);
}

/**
 * Lägger till en kant i grafen med kapacitet capacity
 * @param graph
 * @param source
 * @param sink
 * @param capacity
 */
void addEdge(Graph &graph, int source, int sink, int capacity) {
    auto edge = std::make_shared<Edge>(source, sink, capacity);
    auto reverse = std::make_shared<Edge>(sink, source, 0);
    edge->reverse = reverse;
    reverse->reverse = edge;
    graph[source].push_back(edge);
    graph[sink].push_back(reverse);
}
/**
 * Bredden-först-sökning i grafen för att hitta en väg från s till t (en typ av bfs)
 * @param graph
 * @param s källan
 * @param t sänkan
 * @param path en vektor som håller reda på vilka kanter som ingår i vägen
 * @return true om det finns en väg från s till t
 */
bool bfs(const Graph &graph, int s, int t, std::vector<EdgePtr> &path) {
    std::queue<int> q;
    q.push(s);
    std::fill(path.begin(), path.end(), nullptr);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (auto &edge: graph[current]) { // Gå igenom alla kanter från noden
            if (path[edge->sink] == nullptr && edge->sink != s && edge->capacity > edge->flow) {
                path[edge->sink] = edge; // Spara kanten
                q.push(edge->sink); // Lägg till noden i kön
            }
        }
    }
    return path[t] != nullptr;
}
/**
 * Beräknar maxflödet i en graf med Edmonds-Karp algoritmen
 * @param graph
 * @param s källan
 * @param t sänkan
 * @return maxflödet
 */
int calcMaxFlow(const Graph &graph, int s, int t) {
    int maxFlow = 0;
    std::vector<EdgePtr> path(graph.size(), nullptr);

    while (bfs(graph, s, t, path)) { // Så länge det finns en väg från s till t
        int flow = INT_MAX;
        for (auto edge = path[t]; edge != nullptr; edge = path[edge->source]) {
            flow = std::min(flow, edge->capacity - edge->flow); // Hitta den minsta kapaciteten i vägen
        }
        for (auto edge = path[t]; edge != nullptr; edge = path[edge->source]) { // Uppdatera flödet
            edge->flow += flow;
            edge->reverse->flow -= flow;
        }
        maxFlow += flow;
    }
    return maxFlow;
}



void printGraph(const Graph &graph, int number_of_vertices, int s, int t, int max_flow) {
    std::cout << number_of_vertices << "\n" << s << " " << t << " " << max_flow << "\n";

    std::stringstream output; // Skapa en ström för att skriva ut kanterna
    int numLines = 0;
    for (auto &list: graph) {
        for (auto &e: list) {
            if (e->flow > 0) {
                output << e->source << " " << e->sink << " " << e->flow << "\n";
                numLines++;
            }
        }
    }
    std::cout << numLines << "\n";
    std::cout << output.str();
    std::cout << std::flush;
}
