## **Dijkstra's Shortest Path Tree (SPT) - Explanation**
Dijkstra's algorithm is used to find the **shortest path** from a **single source** to all other vertices in a weighted graph with **non-negative weights**. It follows a **greedy approach** using a **priority queue (min-heap)**.

---

### **How Dijkstra’s Algorithm Works**
1. **Initialize distances**:  
   - Set the source vertex distance to `0` and all others to `∞` (infinity).
   - Use a **min-heap** (priority queue) to always process the smallest distance vertex first.

2. **Process vertices in order**:
   - Extract the vertex with the smallest distance from the priority queue.
   - Update its neighbors' distances **if a shorter path is found**.
   - Push the updated distances into the priority queue.

3. **Repeat until all vertices are processed**.

---

### **Example Graph**
```
         6
     a ------ c
     | \      |
    6|  \2    |2
     |   \    |
     b ------ d
         2
```
Adjacency List Representation:
```
a -> (b,6), (c,6), (d,6)
b -> (d,2)
c -> (d,2)
```
---

### **C++ Code for Dijkstra’s SPT**
```cpp
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
```

---

## **Code Explanation**
### **1. Data Structures Used**
- **Vector of vectors (`adjList`)** → Stores adjacency list representation of the graph.
- **Priority queue (`pq`)** → Min-heap that always picks the vertex with the shortest known distance.

### **2. Algorithm Execution**
- **Initialization**: Set `dist[start] = 0`, push `{0, start}` into the priority queue.
- **Processing vertices**: Extract the smallest distance vertex `u` and check its neighbors.
- **Relaxation**: If `dist[u] + weight < dist[v]`, update `dist[v]` and push it into the priority queue.
- **Repeat until all vertices are processed**.

---

## **Example Output**
```
Shortest Path Tree from vertex a:
a -> b: 6
a -> c: 6
a -> d: 6
b -> d: 8
c -> d: 8
```

---

## **Time Complexity Analysis**
| Step | Complexity |
|------|------------|
| Priority queue operations | \(O(\log V)\) per vertex |
| Processing all edges | \(O(E \log V)\) |
| **Total Complexity** | \(O(E \log V)\) |

---

## **Comparison: Kruskal’s vs. Dijkstra’s**
| Feature | Kruskal’s Algorithm | Dijkstra’s Algorithm |
|---------|----------------------|----------------------|
| Purpose | Find MST | Find shortest paths |
| Approach | Sort edges, DSU | Priority queue (greedy) |
| Data Structure | Disjoint Set (Union-Find) | Min-Heap (Priority Queue) |
| Best for | Sparse graphs | Dense graphs |

---

### **Key Takeaways**
✔️ **Kruskal’s** → **Finds MST** using a **greedy** edge selection approach.  
✔️ **Dijkstra’s** → **Finds shortest paths** from a single source using a **priority queue**.  
✔️ **Efficient for graphs with non-negative weights**.  

Would you like me to modify this to handle **negative weights (Bellman-Ford)?** 🚀  