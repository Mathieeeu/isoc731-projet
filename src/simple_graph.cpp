#include "graph/CGraph.cpp"
#include <string>

int main() {
    CGraph graph;
    int N = 10;
    int n = 2;

    // 1. On initialise tous nos noeuds avec la valeur 0
    graph.addMultipleAgents(N);
    graph.exportToGEXF("../output/simulation/simple_graph_0.gexf");
    // Note : Agent est juste un Node mais "réaliste", càd que sa valeur n'est pas précise mais aléatoire

    // 2. On crée un lien entre deux noeuds randoms et on augmente la valeur du noeud de 1
    srand(time(NULL));
    int node1 = rand() % N;
    int node2 = rand() % N;
    graph.addEdge(node1, node2);
    graph.getNodeById(node1)->incrementValue(1);
    graph.getNodeById(node2)->incrementValue(1);
    graph.exportToGEXF("../output/simulation/simple_graph_1.gexf");

    // 3. Chacun des AUTRES noeuds se connecte avec le noeud de plus grande valeur et incrémente sa valeur de la valeur de l'autre noeud
    for (int i = 0; i < N; i++) {
        if (i != node1 && i != node2) {
            int id_node = graph.connectToHighestValue(i);
            int value1 = graph.getNodeById(i)->getValue() + 1;
            float value2 = ((CAgent*)graph.getNodeById(id_node))->getValue();
            graph.getNodeById(i)->incrementValue(value2);
            graph.getNodeById(id_node)->incrementValue(value1);
            graph.exportToGEXF("../output/simulation/simple_graph_" + std::to_string(n++) + ".gexf");
        }
    }

    // graph.exportToGEXF("../output/simulation/simple_graph_final.gexf");

    return 0;
}
/*
Ils se connectent tous au noeud de plus grande valeur 

et quand on rajoute les "agents", c'est un peu pareil avec quelques connexions entre noeuds moins importants
*/