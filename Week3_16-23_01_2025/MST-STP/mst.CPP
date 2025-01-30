#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

// Comparator function for sorting edges by weight
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Disjoint Set (Union-Find)
class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int v) {
        if (parent[v] != v)
            parent[v] = find(parent[v]);
        return parent[v];
    }

    void unionSet(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
            else if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Graph class for Kruskal's MST
class Graph {
    int vertices;
    vector<Edge> edges;
public:
    Graph(int v) : vertices(v) {}

    void addEdge(int src, int dest, int weight) {
        edges.push_back(Edge(src, dest, weight));
    }

    void findMST() {
        sort(edges.begin(), edges.end(), compare);
        DisjointSet ds(vertices);
        vector<Edge> mst;
        int mstWeight = 0;

        for (Edge edge : edges) {
            if (ds.find(edge.src) != ds.find(edge.dest)) {
                mst.push_back(edge);
                mstWeight += edge.weight;
                ds.unionSet(edge.src, edge.dest);
            }
        }

        // Display MST
        cout << "Minimum Spanning Tree:\n";
        for (Edge edge : mst) {
            cout << char(edge.src + 'a') << " - " << char(edge.dest + 'a') << ": " << edge.weight << endl;
        }
        cout << "Total weight: " << mstWeight << endl;
    }
};

// Main function
int main() {
    Graph graph(4);
    graph.addEdge(0, 2, 6); // a - c
    graph.addEdge(0, 1, 6); // a - b
    graph.addEdge(0, 3, 6); // a - d
    graph.addEdge(1, 3, 2); // b - d
    graph.addEdge(2, 3, 2); // c - d

    graph.findMST();

    return 0;
}
