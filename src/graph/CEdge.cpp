#include <algorithm>
#include <tuple>

class CEdge 
{
private:
    int m_node1;
    int m_node2;
    int m_weight;
    // Note : Node1 est plus petit des deux ids
    // Note : Weight est implémenté au cas où on voudrait ajouter des poids aux arêtes (par defaut = 1)

public:
    CEdge(int node1, int node2) : m_node1(std::min(node1, node2)), m_node2(std::max(node1, node2)), m_weight(1) {}

    int getNode1() const { return m_node1; }
    int getNode2() const { return m_node2; }
    int getWeight() const { return m_weight; }
    
    void setWeight(int weight) { m_weight = weight; }

    bool operator==(const CEdge &autre) const { return std::tie(m_node1, m_node2) == std::tie(autre.m_node1, autre.m_node2); } 
    bool operator<(const CEdge &autre) const { return std::tie(m_node1, m_node2) < std::tie(autre.m_node1, autre.m_node2); }
    // Note : Operateur < pour l'organisation dans les std::set<CEdge> (liste ordonnée) dans CGraph.cpp
    
};
