#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;  // maximum number of nodes
int n, m;               // number of nodes and edges
int c[MAXN][MAXN];      // capacity of edges
int f[MAXN][MAXN];      // flow of edges
int d[MAXN];            // distance of each node from source
int p[MAXN];            // parent of each node in augmenting path

vector<int> adj[MAXN];  // adjacency list of graph

bool bfs(int s, int t) {
    memset(d, -1, sizeof(d));  // initialize distances to -1
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (d[v] == -1 && f[u][v] < c[u][v]) {
                d[v] = d[u] + 1;
                p[v] = u;
                q.push(v);
            }
        }
    }
    return d[t] != -1;  // return true if there is a path from s to t
}

int max_flow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {        // while there is an augmenting path from s to t
        int aug_flow = INT_MAX; // initialize augmenting flow to infinity
        for (int v = t; v != s; v = p[v]) {
            int u = p[v];
            aug_flow = min(aug_flow, c[u][v] - f[u][v]);
        }
        for (int v = t; v != s; v = p[v]) {
            int u = p[v];
            f[u][v] += aug_flow;  // increase flow along forward edge
            f[v][u] -= aug_flow;  // decrease flow along backward edge
        }
        flow += aug_flow;         // increase total flow
    }
    return flow;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        c[u][v] += w;
    }
    int s, t;
    cin >> s >> t;
    cout << "Maximum flow is " << max_flow(s, t) << endl;
    return 0;
}
