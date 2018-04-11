#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 1000000000

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int V, E, I;
vi dist;
vi parent;

void printAdjacencyList(vector<vii>& adjList) {
    for (int u=0; u<adjList.size(); u++) {
        cout << u << ": ";
        for (int j=0; j<adjList[u].size(); j++) {
            ii v = adjList[u][j];

            cout << v.first << "(" << v.second << ") ";
        }
        cout << endl;
    }
}

void printShortestPath(int v, bool first = true) {

    if (parent[v] == -1) cout << v << " -> ";
    else {
        printShortestPath(parent[v], false);
        if (first) cout << v << " P: " << dist[v] << endl;
        else cout << v << " -> ";
    }
}

void dijkstra(vector<vii>& adjList, int s) {
    dist.resize(V, INF);
    parent.resize(V, -1);

    dist[s] = 0;

    priority_queue<ii, vii, greater<ii>> pq;
    pq.push(ii(0, s));

    while (!pq.empty()) {
        ii front = pq.top();
        pq.pop();

        int d = front.first;
        int u = front.second;

        if (d > dist[u]) continue;
        for (int j=0; j<adjList[u].size(); j++) {
            ii v = adjList[u][j];

            if (dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                parent[v.first] = u;
                pq.push(ii(dist[v.first], v.first));
            }
        }
    }
}

int main() {
    cin >> V >> E;
    
    vector<vii> adjList(V, vii());

    for (int i=0; i<E; i++) {
        int X, Y, W;

        cin >> X >> Y >> W;

        adjList[X].push_back(ii(Y,W));
    }

    printAdjacencyList(adjList);

    cin >> I;

    dijkstra(adjList, I);

    for (int i=0; i<V; i++)
        printShortestPath(i); 

    return 0;
}
