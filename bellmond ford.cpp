#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Function to find the shortest path from the source vertex 'S' to all other vertices
    // in a graph using Bellman-Ford algorithm.
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        // Initialize the distance vector to hold the distances from the source
        vector<int> dist(V, 1e9); // 1e9 represents a large number (infinity).
        dist[S] = 0; // Distance to the source itself is 0.

        // Relax all edges (V - 1) times.
        for (int i = 0; i < V - 1; ++i) {
            for (int j = 0; j < edges.size(); ++j) {
                int u = edges[j][0]; // Start vertex of the edge.
                int v = edges[j][1]; // End vertex of the edge.
                int wt = edges[j][2]; // Weight of the edge.

                // Relax the edge if a shorter path is found.
                if (dist[u] != 1e9 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Check for negative-weight cycles.
        for (int j = 0; j < edges.size(); ++j) {
            int u = edges[j][0];
            int v = edges[j][1];
            int wt = edges[j][2];

            // If a shorter path can still be found, then there is a negative-weight cycle.
            if (dist[u] != 1e9 && dist[u] + wt < dist[v]) {
                return {-1}; // Return -1 to indicate a negative-weight cycle.
            }
        }

        return dist; // Return the shortest distances from source.
    }
};

int main() {
    Solution sol;

    int V, E, source;
    // Input number of vertices and edges from user
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> edges;

    // Input all edges (u, v, wt) from user
    cout << "Enter " << E << " edges as 'u v wt' (start vertex, end vertex, and weight):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back({u, v, wt});
    }

    // Input the source vertex
    cout << "Enter the source vertex: ";
    cin >> source;

    // Call the Bellman-Ford algorithm and get the result
    vector<int> result = sol.bellman_ford(V, edges, source);

    // If result contains -1, there is a negative-weight cycle.
    if (result[0] == -1) {
        cout << "Negative weight cycle detected!" << endl;
    } else {
        // Print the shortest distances.
        cout << "Vertex Distance from Source " << source << endl;
        for (int i = 0; i < V; ++i) {
            cout << i << " \t\t " << result[i] << endl;
        }
    }

    return 0;
}