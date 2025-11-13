#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii;

void primsMST(int n, vector<vector<pii>> &adj) {
    vector<int> key(n + 1, INT_MAX);
    vector<bool> inMST(n + 1, false);
    vector<int> parent(n + 1, -1);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    key[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "Edges in MST:\n";
    int totalWeight = 0;
    for (int i = 2; i <= n; ++i) {
        cout << parent[i] << " - " << i << " (" << key[i] << ")\n";
        totalWeight += key[i];
    }
    cout << "Total weight of MST: " << totalWeight << endl;
}

int main() {
    int n = 5;
    vector<vector<pii>> adj(n + 1);

    adj[1].push_back({2, 2});
    adj[1].push_back({4, 6});
    adj[2].push_back({1, 2});
    adj[2].push_back({3, 3});
    adj[2].push_back({4, 8});
    adj[2].push_back({5, 5});
    adj[3].push_back({2, 3});
    adj[3].push_back({5, 7});
    adj[4].push_back({1, 6});
    adj[4].push_back({2, 8});
    adj[4].push_back({5, 9});
    adj[5].push_back({2, 5});
    adj[5].push_back({3, 7});
    adj[5].push_back({4, 9});

    primsMST(n, adj);
}
