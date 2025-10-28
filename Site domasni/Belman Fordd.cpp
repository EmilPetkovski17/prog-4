#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX_N = 101;
const int INF = 1000000000;

int N, E;
vector<pair<int, int> > G[MAX_N];

vector<int> bellman_ford(int start)
{
     vector<int> distance;
     distance.resize(MAX_N);
     for (int i=0; i<MAX_N; i++)
     {
          distance[i] = INF; // nekoj golem broj
     }

     distance[start] = 0;

     // Relax all edges N-1 times
     for (int i = 1; i <= N-1; i++)
     {
          for (int u = 0; u < N; u++)
          {
               for (auto edge : G[u])
               {
                    int v = edge.first;
                    int w = edge.second;

                    if (distance[u] != INF && distance[v] > distance[u] + w)
                    {
                         distance[v] = distance[u] + w;
                    }
               }
          }
     }

     // Check for negative weight cycles
     bool hasNegativeCycle = false;
     for (int u = 0; u < N; u++)
     {
          for (auto edge : G[u])
          {
               int v = edge.first;
               int w = edge.second;

               if (distance[u] != INF && distance[v] > distance[u] + w)
               {
                    hasNegativeCycle = true;
               }
          }
     }

     if (hasNegativeCycle)
     {
          cout << "Graph contains a negative weight cycle!" << endl;
     }

     return distance;
}

int main()
{
     cout << "Number of cities: " << endl;
     cin >> N;

     cout << "Number of edges: " << endl;
     cin >> E;

     cout << "Enter the edges (from, to, weight)." << endl;
     for (int i=0; i<E; i++)
     {
          int from, to, weight;
          cin >> from >> to >> weight;

          G[from].push_back({to, weight});
     }

     int start;
     cout << "Start city: " << endl;
     cin >> start;

     vector<int> distance = bellman_ford(start);

     for (int i=0; i<N; i++)
     {
          cout << "min distance to " << i << " is: " << distance[i] << endl;
     }

     return 0;
}
