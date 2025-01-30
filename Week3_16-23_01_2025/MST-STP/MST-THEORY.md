## **Explanation of Minimum Spanning Tree (MST)**

A **Minimum Spanning Tree (MST)** is a subset of edges in a connected, weighted graph that:

1. Connects all vertices together.
2. Has no cycles.
3. Has the minimum possible total edge weight.

### **Kruskal’s Algorithm (Used in Your Code)**
Kruskal's algorithm is a greedy algorithm that finds the MST by:

1. **Sorting** all edges in ascending order of weight.
2. **Using Disjoint Set (Union-Find)** to check if adding an edge forms a cycle.
3. **Adding edges** until all vertices are connected.

### **Steps in Your Code**
- The graph edges are stored in a list.
- The edges are **sorted** based on weight.
- The **union-find** data structure is used to check if an edge forms a cycle.
- If an edge does not form a cycle, it is **added** to the MST.
- The MST and its total weight are printed.

---

## **C++ Code for MST (Kruskal’s Algorithm)**
Here’s the C++ equivalent of your Java program for finding the MST:

```cpp
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
```

### **Key Features in C++ Implementation**
- **`struct Edge`** stores edges with `src`, `dest`, and `weight`.
- **`DisjointSet`** manages the Union-Find operations.
- **Sorting edges** by weight using `sort()`.
- **Union-Find operations** prevent cycles.
- **Displaying MST** after selecting the minimum edges.

Let me know if you need **Shortest Path Tree (SPT) in C++** as well! 🚀


# **Kruskal’s Algorithm – Detailed Explanation**  

## **What is Kruskal’s Algorithm?**  
Kruskal’s Algorithm is a **Greedy Algorithm** used to find the **Minimum Spanning Tree (MST)** of a graph. It finds the subset of edges that:  
1. **Connect all vertices** without forming a cycle.  
2. **Minimize the total edge weight** of the spanning tree.  

---
## **Understanding the Minimum Spanning Tree (MST)**
A **spanning tree** is a subgraph of a connected graph that includes all the vertices with no cycles and the minimum number of edges (i.e., `V-1` edges for `V` vertices).  
A **Minimum Spanning Tree (MST)** is a spanning tree where the sum of the edge weights is **minimized**.

### **Example Graph:**
Consider a weighted graph:  

```
       6
   a ------ c
   | \      |
  6|  \2    |2
   |   \    |
   b ------ d
       2
```

Here, **Vertices** = `{a, b, c, d}`  
Edges = `{(a, b, 6), (a, c, 6), (a, d, 6), (b, d, 2), (c, d, 2)}`  

---
## **Steps in Kruskal’s Algorithm**  
Kruskal’s algorithm follows **three main steps**:

### **Step 1: Sort all edges by weight**  
We first sort the edges in **ascending order** based on their weights:

| Edge  | Weight |
|-------|--------|
| (b, d) | 2 |
| (c, d) | 2 |
| (a, b) | 6 |
| (a, c) | 6 |
| (a, d) | 6 |

---
### **Step 2: Pick the smallest edge and check for cycles**
We use the **Disjoint Set Union (DSU)** (also called **Union-Find**) to ensure no cycles are formed.

#### **What is Disjoint Set Union (DSU)?**
- **Find operation**: Determines the root/parent of a set.
- **Union operation**: Combines two sets.

Initially, each vertex is its **own set**:

```
a   b   c   d   (Each is its own parent)
```

---
### **Step 3: Add edges to the MST**
We **add edges one by one** while ensuring no cycles form.

1️⃣ **Add (b, d, 2)**  
   - `b` and `d` belong to different sets → **Add the edge**  
   - Merge sets `{b, d}`  

```
a   (b,d)   c
```

---

2️⃣ **Add (c, d, 2)**  
   - `c` and `d` belong to different sets → **Add the edge**  
   - Merge sets `{b, c, d}`  

```
a   (b, c, d)
```

---

3️⃣ **Add (a, b, 6)**  
   - `a` and `b` belong to different sets → **Add the edge**  
   - Merge sets `{a, b, c, d}`  

```
(a, b, c, d)
```

✅ We have **V-1 = 3 edges**, so we stop.

---
### **Final MST**
The **Minimum Spanning Tree (MST)**:

```
       6
   a ------ b
          |  
          2
          d
         / 
        2  
       c
```

Total MST weight = `2 + 2 + 6 = 10`

---
## **Time Complexity Analysis**
| Step | Complexity |
|------|------------|
| Sorting edges | \(O(E \log E)\) |
| Finding parent (DSU) | \(O(\log V)\) |
| Union operation (DSU) | \(O(\log V)\) |
| **Overall Complexity** | \(O(E \log E)\) |

Since **E ≥ V**, Kruskal’s algorithm is **efficient for sparse graphs**.

---
## **Why Use Kruskal’s Algorithm?**
✔️ **Best for sparse graphs** (fewer edges).  
✔️ **Simple and intuitive** due to sorting + DSU.  
✔️ **Works for disconnected graphs** (finds an MST for each component).  

---
### **Comparison with Prim’s Algorithm**
| Feature | Kruskal’s Algorithm | Prim’s Algorithm |
|---------|------------------|------------------|
| Approach | Greedy (sort edges) | Greedy (start from a vertex) |
| Data Structure | Disjoint Set (DSU) | Priority Queue (Heap) |
| Best for | Sparse graphs | Dense graphs |
| Time Complexity | \(O(E \log E)\) | \(O(V^2)\) or \(O(E + V \log V)\) with heap |

---

## **Conclusion**
Kruskal’s algorithm is an efficient and **greedy approach** to finding the MST of a graph. It **sorts the edges, processes them in increasing order of weight, and uses the Union-Find data structure** to ensure no cycles are formed.

Would you like an example of the **step-by-step execution in code**? 🚀