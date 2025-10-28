#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 101;
const int INF = 1000000000;

int N, E;
int dist[MAX_N][MAX_N];

void floyd_warshall()
{
     for (int k = 0; k < N; k++)
     {
          for (int i = 0; i < N; i++)
          {
               for (int j = 0; j < N; j++)
               {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                         dist[i][j] = dist[i][k] + dist[k][j];
                    }
               }
          }
     }
}

int main()
{
     cout << "Number of cities: " << endl;
     cin >> N;

     cout << "Number of edges: " << endl;
     cin >> E;

     // Initialize distances
     for (int i = 0; i < N; i++)
     {
          for (int j = 0; j < N; j++)
          {
               if (i == j) dist[i][j] = 0;
               else dist[i][j] = INF;
          }
     }

     cout << "Enter the edges (from, to, weight)." << endl;
     for (int i = 0; i < E; i++)
     {
          int from, to, weight;
          cin >> from >> to >> weight;
          dist[from][to] = weight;
     }

     floyd_warshall();

     cout << "Shortest distances between all pairs:" << endl;
     for (int i = 0; i < N; i++)
     {
          for (int j = 0; j < N; j++)
          {
               if (dist[i][j] == INF) cout << "INF ";
               else cout << dist[i][j] << " ";
          }
          cout << endl;
     }

     return 0;
}
