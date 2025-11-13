#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

bool compare(Edge a, Edge b) {
    return a.w < b.w;
}

int findParent(int node, vector<int> &parent) {
    if (node == parent[node])
        return node;
    return parent[node] = findParent(parent[node], parent);
}

void unionSet(int u, int v, vector<int> &parent, vector<int> &rank) {
    u = findParent(u, parent);
    v = findParent(v, parent);

    if (u != v) {
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[v] < rank[u])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
    }
}

int main() {
    int n = 5, e = 7;
    vector<Edge> edges = {
        {1, 2, 2}, {1, 4, 6}, {2, 3, 3},
        {2, 4, 8}, {2, 5, 5}, {3, 5, 7}, {4, 5, 9}
    };

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(n + 1), rank(n + 1, 0);
    for (int i = 1; i <= n; ++i) parent[i] = i;

    int mstWeight = 0;
    vector<Edge> mst;

    for (auto &edge : edges) {
        int u = edge.u, v = edge.v, w = edge.w;
        if (findParent(u, parent) != findParent(v, parent)) {
            unionSet(u, v, parent, rank);
            mst.push_back(edge);
            mstWeight += w;
        }
    }

    cout << "Edges in MST:\n";
    for (auto &e : mst)
        cout << e.u << " - " << e.v << " (" << e.w << ")\n";
    cout << "Total weight of MST: " << mstWeight << endl;
}
