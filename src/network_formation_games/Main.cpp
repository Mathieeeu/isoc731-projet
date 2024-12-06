#include <iostream>
#include <boost/graph/adjacency_list.hpp>rt
#include <boost/graph/graphviz.hpp>

int main() {
    using namespace boost;
    typedef adjacency_list<vecS, vecS, undirectedS> Graph;

    Graph g(5);
    add_edge(0, 1, g);
    add_edge(1, 2, g);
    add_edge(2, 3, g);
    add_edge(3, 4, g);
    add_edge(4, 0, g);

    // Affichage du graphe
    write_graphviz(std::cout, g);
    return 0;
}
