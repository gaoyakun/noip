#ifndef __GRAPH_H__
#define __GRAPH_H__

namespace graph {

template <class WeightType, unsigned N_VERTICES, unsigned N_EDGES>
struct AdjacentTable {
    struct Edge {
        int next;
        int to;
        WeightType weight;
    };
    Edge edges[N_EDGES];
    unsigned numEdges;
    int head[N_VERTICES];
    unsigned numVertices;

    AdjacentTable () {
        numEdges = 0;
        numVertices = 0;
    }

    void addEdge (int from, int to, WeightType weight) {
        edges[numEdges].to = to;
        edges[numEdges].weight = weight;
        edges[numEdges].next = head[from];
        head[from] = numEdges++;
    }
};

template <class WeightType, unsigned N_VERTICES>
struct AdjacentMatrix {
    struct Edge {
        bool connected;
        WeightType weight;
        operator bool () const {
            return connected;
        }
    };
    Edge edges[N_VERTICES][N_VERTICES];

    AdjacentMatrix () {
        for (unsigned i = 0; i < N_VERTICES; i++) {
            for (unsigned j = 0; j < N_VERTICES; j++) {
                edges[i][j].connected = false;
            }
        }
    }

    void addEdge (int from, int to, WeightType weight) {
        edges[from][to].connected = true;
        edges[from][to].weight = weight;
    }
};

}

#endif // __GRAPH_H__
