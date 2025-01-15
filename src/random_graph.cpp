#include "graph/CGraph.cpp"

int main() {

    // Nombre de noeuds du graphe et probabilité de connexion
    // int N = 100;
    // float p = 0.01;
    // Note : Il y a (N² * p) / 2 arêtes en moyenne

    for (float p = 0.0; p < 0.1; p += 0.01) {
        CGraph graph;
        graph.addMultipleNodes(100);
        graph.addRandomEdges(p);
        std::cout << "p=" << p << "\t: " << (float)graph.getLargestConnectedComponent().size() / (float)graph.getNodes().size()*100.0 << "%" << "\t: " << graph.getMaxDegree() << std::endl;
    }

    // std::cout << "Nombre de noeuds : " << graph.getNodes().size() << std::endl;
    // std::cout << "Nombre d'aretes: " << graph.getEdges().size() << std::endl;
    // std::cout << "Taille de la composante connexe la plus grande : " << graph.getLargestConnectedComponent().size() << std::endl;

    // graph.exportToGEXF("../output/random_graph.gexf");

}

/*
ANALYSE 
Question 1 :




*/