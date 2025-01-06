#include "graph/CGraph.cpp"

int main() {
    CGraph graph;

    // Ajout de l'ensemble des noeuds
    graph.addMultipleNodes(10);

    // Ajout de l'ensemble des arêtes
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 1);
    graph.addEdge(2, 4);
    graph.addEdge(5, 6);
    graph.addEdge(5, 7);
    graph.addEdge(5, 5);
    graph.addEdge(5, 1);

    // Ajout de liens pour tous les noeuds vers le noeud 0
    for (int i = 6; i < graph.getNodes().size(); i++) {
        graph.addEdge(i, 0);
    }

    // // Ajout de liens aléatoires
    // graph.addRandomEdges(0.1);

    // Changement des poids des noeuds et des arêtes
    graph.getNodeById(2)->setValue(5);
    graph.getNodeById(6)->setValue(10);
    graph.getEdgeByNodes(1, 2)->setWeight(5);
    // Note : c'est pas parfait, si le noeud n'est pas trouvé, ça plante, il faudrait gérer les erreurs...

    // Recherche de la composante connexe la plus grande
    std::unordered_set<int> largestComponent = graph.getLargestConnectedComponent();
    std::cout << "Taille de la composante connexe la plus grande : " << largestComponent.size() << std::endl;
    
    // Affichage du degré maximum du graphe
    std::cout << "Degr\202 max du graphe : " << graph.getMaxDegree() << std::endl;

    // Exportation dans un format utilisable sur Gephi
    graph.exportToGEXF("../output/main.gexf");

    return 0;
}

// g++ -o graph main.cpp
// ./graph
