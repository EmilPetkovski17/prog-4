#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_N = 101;
int N; // number of nodes

struct Edge {
    int to, rev;
    int cap;
};

vector<Edge> G[MAX_N];
int level[MAX_N];
int iter[MAX_N];

// Add edge to the graph
void add_edge(int from, int to, int cap) {
    G[from].push_back({to, (int)G[to].size(), cap});
    G[to].push_back({from, (int)G[from].size()-1, 0}); // reverse edge
}

// BFS to build level graph
void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (Edge e : G[v]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

// DFS to send flow
int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < G[v].size(); i++) {
        Edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

// Dinic main function
int max_flow(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) break; // no more augmenting paths
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, 1e9)) > 0) {
            flow += f;
        }
    }
    return flow;
}

int main() {
    int E;
    cout << "Number of nodes and edges: ";
    cin >> N >> E;
    cout << "Enter edges (from, to, capacity):\n";
    for (int i = 0; i < E; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }
    int s, t;
    cout << "Source and sink: ";
    cin >> s >> t;
    cout << "Max flow: " << max_flow(s, t) << endl;
    return 0;
}
