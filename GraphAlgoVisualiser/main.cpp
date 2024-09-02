#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int dest;
    int weight;
};

struct Graph {
    int V;
    vector<vector<Edge>> adjList;
};

// Function prototypes
void displayGraph(const Graph& graph);
void DFS(const Graph& graph, int start);
void BFS(const Graph& graph, int start);
void dijkstra(const Graph& graph, int start);
void primMST(const Graph& graph);

int main() {
    Graph graph;

    // Input number of vertices
    cout << "Enter number of vertices: ";
    cin >> graph.V;

    // Initialize edges
    graph.adjList.resize(graph.V);

    // Input edges
    for (int i = 0; i < graph.V; i++) {
        int edges = 0;
        cout<<"Enter the number of edges from the Vertex "<< i << ": ";
        cin >> edges;
        for(int j = 0; j < edges; j++) {
            cout << "Enter " << j + 1 << " th " << "Edge "<< "from Vertex " << i << ": ";
            Edge edge;
            cin >> edge.dest >> edge.weight;
            graph.adjList[i].push_back(edge);
        }
    }

    while (true) {
        cout << "\n--- Graph Algorithms Suite ---\n";
        cout << "1. Display Graph\n";
        cout << "2. Depth-First Search (DFS)\n";
        cout << "3. Breadth-First Search (BFS)\n";
        cout << "4. Dijkstra's Algorithm\n";
        cout << "5. Prim's Minimum Spanning Tree (MST)\n";
        cout << "6. Exit\n";
        cout << "Select an option: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                displayGraph(graph);
                break;
            case 2: {
                int startVertex;
                cout << "Enter starting vertex: ";
                cin >> startVertex;
                DFS(graph, startVertex);
                break;
            }
            case 3: {
                int startVertex;
                cout << "Enter starting vertex: ";
                cin >> startVertex;
                BFS(graph, startVertex);
                break;
            }
            case 4: {
                int startVertex;
                cout << "Enter starting vertex: ";
                cin >> startVertex;
                dijkstra(graph, startVertex);
                break;
            }
            case 5:
                primMST(graph);
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}

void displayGraph(const Graph& graph) {
    for (int i = 0; i < graph.V; i++) {
        cout << "Vertex " << i << ":";
        for (const auto& edge : graph.adjList[i]) {
            cout << " -> " << edge.dest << " (Weight: " << edge.weight << ")";
        }
        cout << endl;
    }
}

void DFSUtil(int v, vector<bool>& visited, const Graph& graph) {
    visited[v] = true;
    cout << v << " ";

    for (const auto& edge : graph.adjList[v]) {
        if (!visited[edge.dest]) {
            DFSUtil(edge.dest, visited, graph);
        }
    }
}

void DFS(const Graph& graph, int start) {
    vector<bool> visited(graph.V, false);
    DFSUtil(start, visited, graph);
    cout << endl;
}

void BFS(const Graph& graph, int start) {
    vector<bool> visited(graph.V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        cout << v << " ";
        q.pop();

        for (const auto& edge : graph.adjList[v]) {
            if (!visited[edge.dest]) {
                visited[edge.dest] = true;
                q.push(edge.dest);
            }
        }
    }
    cout << endl;
}

void dijkstra(const Graph& graph, int start) {
    vector<int> dist(graph.V, INT_MAX);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : graph.adjList[u]) {
            int v = edge.dest;
            int weight = edge.weight;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print the distances
    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < graph.V; i++) {
        cout << i << "\t" << dist[i] << "\n";
    }
}

int minKey(const vector<int>& key, const vector<bool>& inMST, int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void primMST(const Graph& graph) {
    vector<int> parent(graph.V, -1);
    vector<int> key(graph.V, INT_MAX);
    vector<bool> inMST(graph.V, false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph.V - 1; count++) {
        int u = minKey(key, inMST, graph.V);
        inMST[u] = true;

        for (const auto& edge : graph.adjList[u]) {
            int v = edge.dest;
            int weight = edge.weight;

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    // Print the MST
    cout << "Edge\tWeight\n";
    for (int i = 1; i < graph.V; i++) {
        cout << parent[i] << " - " << i << "\t" << key[i] << "\n";
    }
}