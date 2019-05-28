#ifndef __GRAPH_H__
#define __GRAPH_H__

namespace graph {

template <unsigned N_VERTICES, unsigned N_EDGES>
struct AdjacentTable {
    struct Edge {
        int next;
        int to;
        int weight;
    };
    Edge edges[N_EDGES];
    unsigned numEdges;
    int head[N_VERTICES];
    unsigned numVertices;

    AdjacentTable () {
        numEdges = 0;
        numVertices = 0;
    }

    void addEdge (int from, int to, int weight) {
        edges[numEdges].to = to;
        edges[numEdges].weight = weight;
        edges[numEdges].next = head[from];
        head[from] = numEdges++;
    }
};

}

#endif // __GRAPH_H__
