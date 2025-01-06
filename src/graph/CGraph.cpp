#include <unordered_map>
#include <set>
#include <fstream>
#include <iostream>
#include <vector>
#include "CNode.cpp"
#include "CEdge.cpp"

class CGraph
{
private:
    std::unordered_map<int, CNode> m_nodes;
    std::set<CEdge> m_edges;
    // Note : Unordered_map : hashmap liant les noeuds et leur valeur (recherche plus rapide qu'une liste classique)
    // Note : Pour 'pair' un élement de m_nodes : pair.first = 'id du noeud', pair.second = 'CNode'
    // Note : Set = liste ordonnée d'objets

public:
    void addNode(int n) {
        m_nodes[n] = CNode(n);
    }

    void addMultipleNodes(int number, int start = 0) {
        for (int i = start; i < start + number; i++) {
            addNode(i);
        }
    }

    void addAgent(int n) {
        m_nodes[n] = CAgent(n);
    }

    void addMultipleAgents(int number, int start = 0) {
        for (int i = start; i < start + number; i++) {
            addAgent(i);
        }
    }

    void addEdge(int node1, int node2) {
        CEdge edge(node1, node2);
        if (m_edges.find(edge) == m_edges.end()) {
            m_edges.insert(edge);
            m_nodes[node1].addNeighbor(node2);
            m_nodes[node2].addNeighbor(node1);
        }
        // Note : node1 et node2 sont les ids des noeuds source et cible
    }

    void addRandomEdges(float probability) {
        int nb = 0;
        srand(time(NULL)); // Initialisation de la graine pour la fonction rand()
        for (const auto& pair1 : m_nodes) {
            for (const auto& pair2 : m_nodes) {
                if (pair1.first < pair2.first && (float)rand() / RAND_MAX < probability) {
                    addEdge(pair1.first, pair2.first);
                    nb++;
                }
            }
        }
        // std::cout << nb << " edges added" << std::endl;
    }

    // Connexion d'un noeud à un autre qui a la valeur maximale (renvoie l'id du noeud sélectionné)
    int connectToHighestValue(int node) {
        int max = -1;
        srand(time(NULL));
        std::vector<int> maxNodes;
        for (const auto& pair : m_nodes) {
            if (pair.second.getValue() > max) {
                max = pair.second.getValue();
                maxNodes.clear();
                maxNodes.push_back(pair.first);
            } else if (pair.second.getValue() == max) {
                maxNodes.push_back(pair.first);
            }
        }
        if (!maxNodes.empty()) {
            int randomIndex = rand() % maxNodes.size();
            addEdge(node, maxNodes[randomIndex]);
            return maxNodes[randomIndex];
        }
        // Note : On choisit un noeud aléatoire parmi les noeuds de valeur maximale (s'il n'y en a qu'un, il sera forcément choisi)
        return -1;
    }

    const std::unordered_map<int, CNode>& getNodes() const { return m_nodes; }
    const std::set<CEdge>& getEdges() const { return m_edges; }

    int getDegree(int id) {
        return m_nodes[id].getDegree();
    }

    int getMaxDegree() {
        int maxDegree = 0;
        for (const auto& pair : m_nodes) {
            maxDegree = std::max(maxDegree, pair.second.getDegree());
        }
        return maxDegree;
    }

    CNode* getNodeById(int id) {
        auto it = m_nodes.find(id);
        if (it != m_nodes.end()) {
            return &it->second;
        }
        return nullptr;
    }

    CEdge* getEdgeByNodes(int node1, int node2) {
        CEdge edge(node1, node2);
        auto it = m_edges.find(edge);
        if (it != m_edges.end()) {
            return const_cast<CEdge*>(&(*it));
        }
        return nullptr;
    }

    // Récupération de l'ensemble des noeuds connectés à un noeud donné
    std::unordered_set<int> getConnectedComponent(int id, std::unordered_set<int>& visited) {
        std::unordered_set<int> component;
        std::unordered_set<int> toVisit;
        toVisit.insert(id);
        while (!toVisit.empty()) {
            int current = *toVisit.begin();
            toVisit.erase(toVisit.begin());
            visited.insert(current);
            component.insert(current);
            for (int neighbor : m_nodes[current].getNeighbors()) {
                if (visited.find(neighbor) == visited.end()) {
                    toVisit.insert(neighbor);
                }
            }
        }
        return component;
    }

    // Récupération du plus grand ensemble de noeuds connectés du graphe
    std::unordered_set<int> getLargestConnectedComponent() {
        std::unordered_set<int> visited;
        std::unordered_set<int> largestComponent;
        for (const auto& pair : m_nodes) {
            if (visited.find(pair.first) == visited.end()) {
                std::unordered_set<int> component = getConnectedComponent(pair.first, visited);
                // Note : Ici on "demande" à chaque noeud de trouver l'ensemble de ses voisins et de les ajouter à visited si ils ne le sont pas déjà
                if (component.size() > largestComponent.size()) {
                    largestComponent = component;
                }
            }
        }
        return largestComponent;
        // Note : Sur "largestComponent", il est possible d'effectuer les opérations : largestComponent.size(), largestComponent.find(5), etc.
    }

    // déconnexion aléatoire parmi les noeuds
    void disconnectRandomNodes() {
        srand(time(NULL));
        float probability = 0.2;

        for (const auto& pair : m_nodes) {          
            int nb_neighbors = 0;
            int nb_defectections = 0;
            for (int neighbor : pair.second.getNeighbors()) {
                if ((float)rand()/RAND_MAX < probability) {
                    m_edges.erase(CEdge(pair.first, neighbor));
                    m_nodes[pair.first].getNeighbors().erase(neighbor);
                    m_nodes[neighbor].getNeighbors().erase(pair.first);
                    nb_defectections++;
                }
                nb_neighbors++;
            }
            ((CAgent*)getNodeById(pair.first))->setKarma((float)nb_defectections/nb_neighbors);
        }
    }

    // Connexion au karma le plus élevé
    int connectToHighestKarma(int node) {
        int max = -1;
        srand(time(NULL));
        std::vector<int> maxNodes;
        for (const auto& pair : m_nodes) {
            if (((CAgent*)getNodeById(pair.first))->getKarma() > max) {
                max = pair.second.getValue();
                maxNodes.clear();
                maxNodes.push_back(pair.first);
            } else if (((CAgent*)getNodeById(pair.first))->getKarma() == max) {
                maxNodes.push_back(pair.first);
            }
        }
        if (!maxNodes.empty()) {
            int randomIndex = rand() % maxNodes.size();
            addEdge(node, maxNodes[randomIndex]);
            return maxNodes[randomIndex];
        }
        // Note : On choisit un noeud aléatoire parmi les noeuds de valeur maximale (s'il n'y en a qu'un, il sera forcément choisi)
        return -1;
    }

    // connexion aléatoire parmi les noeuds
    void connectRandomNodes() {
        int N = m_nodes.size();
        for (int i = 0; i < N; i++) {
            connectToHighestKarma(i);
            
        }
    }

    void exportToGEXF(const std::string& filename) 
    {
        std::ofstream file(filename);

        // En-tête du fichier GEXF
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
        file << "<graph node=\"static\" defaultedgetype=\"undirected\">\n";

        // Définition des attributs d'un noeud
        file << "<attributes class=\"node\" mode=\"static\">\n";
        file << "<attribute id=\"0\" title=\"Value\" type=\"integer\"/>\n";
        file << "</attributes>\n";

        // Définition des attributs d'une arête
        file << "<attributes class=\"edge\" mode=\"static\">\n";
        file << "<attribute id=\"0\" title=\"Weight\" type=\"integer\"/>\n";
        file << "</attributes>\n";
        // Note : Pas utilisé ici, mais peut être utile pour ajouter des poids aux arêtes

        // Export des noeuds
        file << "<nodes>\n";
        const auto& nodes = getNodes();
        for (const auto& pair : nodes) {
            const CNode& node = pair.second;
            file << "<node id=\"" << node.getId() << "\" label=\"" << node.getId() << "\">\n";
            file << "<attvalues>\n";
            file << "<attvalue for=\"0\" value=\"" << node.getValue() << "\"/>\n";
            file << "</attvalues>\n";
            file << "</node>\n";
        }
        file << "</nodes>\n";

        // Export des arêtes
        file << "<edges>\n";
        int edgeId = 0;
        const auto& edges = getEdges();
        for (const auto& edge : edges) {
            file << "<edge id=\"" << edgeId++ << "\" source=\"" << edge.getNode1() << "\" target=\"" << edge.getNode2() << "\" >\n";
            file << "<attvalues>\n";
            file << "<attvalue for=\"0\" value=\"" << edge.getWeight() << "\"/>\n";
            file << "</attvalues>\n";
            file << "</edge>\n";
        }
        file << "</edges>\n";

        file << "</graph>\n";
        file << "</gexf>\n";

        file.close();

        std::cout << "Graph exported to " << filename << std::endl;
    }
};
