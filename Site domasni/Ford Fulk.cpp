#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_N = 101;

int N, E;
int capacity[MAX_N][MAX_N];
int parent[MAX_N];

bool bfs(int s, int t, vector<vector<int>>& adj)
{
     memset(parent, -1, sizeof(parent));
     queue<int> q;
     q.push(s);
     parent[s] = -2;

     while (!q.empty())
     {
          int u = q.front();
          q.pop();

          for (int v : adj[u])
          {
               if (parent[v] == -1 && capacity[u][v] > 0)
               {
                    parent[v] = u;
                    if (v == t) return true;
                    q.push(v);
               }
          }
     }

     return false;
}

int ford_fulkerson(int s, int t)
{
     int max_flow = 0;
     vector<vector<int>> adj(N);
     for (int u = 0; u < N; u++)
     {
          for (int v = 0; v < N; v++)
          {
               if (capacity[u][v] > 0)
                    adj[u].push_back(v);
          }
     }

     while (bfs(s, t, adj))
     {
          int flow = 1000000000;

          // Find minimum capacity in the path
          for (int v = t; v != s; v = parent[v])
          {
               int u = parent[v];
               flow = min(flow, capacity[u][v]);
          }

          // Update residual capacities
          for (int v = t; v != s; v = parent[v])
          {
               int u = parent[v];
               capacity[u][v] -= flow;
               capacity[v][u] += flow;
          }

          max_flow += flow;
     }

     return max_flow;
}

int main()
{
     cout << "Number of vertices: " << endl;
     cin >> N;

     cout << "Number of edges: " << endl;
     cin >> E;

     memset(capacity, 0, sizeof(capacity));

     cout << "Enter the edges (from, to, capacity)." << endl;
     for (int i = 0; i < E; i++)
     {
          int from, to, cap;
          cin >> from >> to >> cap;
          capacity[from][to] = cap;
     }

     int source, sink;
     cout << "Source: " << endl;
     cin >> source;
     cout << "Sink: " << endl;
     cin >> sink;

     int max_flow = ford_fulkerson(source, sink);

     cout << "Maximum flow is: " << max_flow << endl;

     return 0;
}
