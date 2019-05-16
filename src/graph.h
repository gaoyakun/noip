#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
using std::vector;

template <class T>
struct GraphNode {
    T data;
};

template <>
struct GraphNode<void> {
};

template <class DataType, class WeightType, bool Directed, class EdgeListType = vector<size_t>, size_t BaseIndex = 0>
class AdjacencyTable {
    struct Node: public GraphNode<T> {
        EdgeListType edges;
    };
    vector<Node> _nodes;
public:
    typedef DataType data_type;
    typedef WeightType weight_type;
    typedef EdgeListType edgelist_type;
    typedef Node node_type;
    enum { directed = Directed };
    AdjacencyTable () {
    }
    void init (size_t numNodes) {
        _nodes.resize (numNodes + BaseIndex);
    }
    void addEdge
};

template <class WeightType, bool Directed, size_t BaseIndex = 0>
class AdjacencyMatrix {
    vector<vector<WeightType> > _edges;
    T _inf;
public:
    AdjacencyMatrix (WeightType inf): _inf(inf) {
    }
    WeightType inf () const {
        return _inf;
    }
    void init (size_t numNodes) {
        _edges.resize (numNodes + BaseIndex);
        for (size_t i = 0; i < _edges.size(); i++) {
            _edges[i].resize (numNodes + BaseIndex, _inf);
        }
    }
    void addEdge (size_t from, size_t to, WeightType weight) {
        _edges[from][to] = weight;
        if (!Directed) {
            _edges[to][from] = weight;
        }
    }
    void removeEdge (size_t from, size_t to) {
        addEdge (from, to, _inf);
    }
    T getEdge (size_t from , size_t to) const {
        return _edges[from][to];
    }
    bool hasEdge (size_t from, size_t to) const {
        return _edges[from][to] != _inf;
    }
};

#endif // __GRAPH_H__
/* test */
