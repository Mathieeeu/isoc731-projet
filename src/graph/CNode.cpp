#include <unordered_set>
#include <iostream>
#include <random>

class CNode 
{
private:
    int m_id;
    int m_value;
    std::unordered_set<int> m_neighbors;
    // Note : Unordered_set : liste non ordonnée d'objets (plus rapide qu'une liste classique)

public:
    CNode() : m_value(-1) {} // Lui il existe faute de meilleure solution pour une erreur (peut etre résolue entre temps jsp)
    CNode(int id) : m_id(id), m_value(0) {}

    int getId() const { return m_id; }
    int getValue() const { return m_value; }
    const std::unordered_set<int>& getNeighbors() const { return m_neighbors; }
    std::unordered_set<int>& getNeighbors() { return m_neighbors; }

    void setValue(int n) { m_value = n; }
    void incrementValue(int n) { m_value += n; }

    void addNeighbor(int neighbor_id) { m_neighbors.insert(neighbor_id); }

    int getDegree() const { return m_neighbors.size(); }
};

class CAgent : public CNode
{
private:
    float karma;
public:
    CAgent(int id) : CNode(id) { karma = 1.0; }

    float getValue() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        double random_value = dis(gen);
        return CNode::getValue() * (0.5 + random_value);
    }

    void setKarma(float k) { karma = k; }
    float getKarma() const { return karma; }
};
