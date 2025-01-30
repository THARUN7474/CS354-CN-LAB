#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure for representing an edge
struct Edge {
    int dest, weight;
    Edge(int d, int w) : dest(d), weight(w) {}
};

// Graph class
class Graph {
    int vertices;
    vector<vector<Edge>> adjList;

public:
    Graph(int v) {
        vertices = v;
        adjList.resize(v);
    }

    // Function to add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back(Edge(dest, weight));
        adjList[dest].push_back(Edge(src, weight));  // Since it's an undirected graph
    }

    // Function to find Shortest Path Tree (SPT) using Dijkstra's Algorithm
    void findSPT(int start) {
        vector<int> dist(vertices, INT_MAX);  // Stores shortest distances
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Initialize source vertex
        dist[start] = 0;
        pq.push({0, start});

        cout << "Shortest Path Tree from vertex " << char(start + 'a') << ":\n";

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;  // Ignore outdated entries

            for (auto edge : adjList[u]) {
                int v = edge.dest, weight = edge.weight;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                    cout << char(u + 'a') << " -> " << char(v + 'a') << ": " << dist[v] << endl;
                }
            }
        }
    }
};

// Driver function
int main() {
    Graph graph(4);
    graph.addEdge(0, 2, 6); // a - c
    graph.addEdge(0, 1, 6); // a - b
    graph.addEdge(0, 3, 6); // a - d
    graph.addEdge(1, 3, 2); // b - d
    graph.addEdge(2, 3, 2); // c - d

    graph.findSPT(0);  // Start SPT from vertex 'a'
    
    return 0;
}
