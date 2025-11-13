#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // (distance, node)

void dijkstra(int src, vector<vector<pii>> &adj, int n) {
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distances from node " << src << ":\n";
    for (int i = 1; i <= n; ++i)
        cout << "Node " << i << " -> " << dist[i] << endl;
}

int main() {
    int n = 5; // number of nodes
    vector<vector<pii>> adj(n + 1);

    // edges: u -> v with weight w
    adj[1].push_back({2, 2});
    adj[1].push_back({3, 4});
    adj[2].push_back({3, 1});
    adj[2].push_back({4, 7});
    adj[3].push_back({5, 3});
    adj[4].push_back({5, 1});

    int src = 1;
    dijkstra(src, adj, n);
    return 0;
}
