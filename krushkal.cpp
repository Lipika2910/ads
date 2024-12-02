#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& e) const {
        return weight < e.weight;
    }
};

int find(int parent[], int u) {
    if (parent[u] != u) {
        parent[u] = find(parent, parent[u]);
    }
    return parent[u];
}

void unionSet(int parent[], int rank[], int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);
    if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

void kruskal(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end());
    vector<Edge> result;
    int parent[n], rank[n];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < edges.size(); i++) {
        Edge e = edges[i];
        if (find(parent, e.u) != find(parent, e.v)) {
            result.push_back(e);
            unionSet(parent, rank, e.u, e.v);
        }
    }

    cout << "Edges in the MST:\n";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i].u << " -- " << result[i].v << " == " << result[i].weight << endl;
    }
}

int main() {
    int n = 4; // Number of vertices
    vector<Edge> edges = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
    kruskal(edges, n);
    return 0;
}
