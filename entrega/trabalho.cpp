#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

#include <stack>

#define INF 10000000000000000
#define WHITE -1

using namespace std;

typedef long long ll;
typedef pair<ll, int> lli;
typedef pair<int, int> ii;
typedef vector<lli> vlli;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef unordered_map<int, lli> umap;

int V, E;
vector<vll> distances;
vector<umap> adjList, tAdjList;
set<int> united, intersect;

int dfs_counter;
vi dfs_num, dfs_low, dfs_parent;

template <typename Iter, typename Cont>
bool is_last(Iter iter, const Cont& cont) {
    return (iter != cont.end()) && (next(iter) == cont.end());
}

void printAdjacencyList(const vector<umap>& adjList) {
    for (int u=0; u<adjList.size(); u++) {
        cout << u << ": ";
        for (auto& c : adjList[u]) {
            cout << c.first << "(" << c.second.first << ", " << c.second.second << ") ";
        }
        cout << endl;
    }
}

void printSet(const set<int> edges) {
    cout << edges.size() << endl;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        cout << *it;

        if (!is_last(it, edges))
            cout << " ";
    }
    cout << endl;
}

vector<umap> createSubgraph(vector<umap>& adjList, const set<int>& edges) {
    vector<umap> newAdjList(V, umap());

    for (int i=0; i<V; i++) {
        for (auto& c : adjList[i]) {
            if (edges.find(c.second.second) != edges.end()) {
                newAdjList[i][c.first] = lli(c.second);
            }
        }
    }

    for (int i=0; i<V; i++) {
        for (auto& c : newAdjList[i]) {
            if (newAdjList[c.first].find(i) == newAdjList[c.first].end()) {
                newAdjList[c.first][i] = newAdjList[i][c.first];  
            }
        }
    }

    return newAdjList;
}

void bridges(vector<umap>& adjList, int u) {
    stack<pair<int,int>> nodes;  
    nodes.push(ii(u,-1));

    do {
        int v = nodes.top().first;
        int p = nodes.top().second;
        nodes.pop();

        if (dfs_num[v] == WHITE) {

            dfs_parent[v] = p;
            dfs_low[v] = dfs_counter;
            dfs_num[v] = dfs_counter++;

            nodes.push(ii(v,p));

            for (auto &c : adjList[v]) {
                if (dfs_num[c.first] == WHITE) {
                    nodes.push(ii(c.first, v));
                } else if (c.first != dfs_parent[v]) {
                    dfs_low[v] = min(dfs_low[v], dfs_num[c.first]);
                }
            }
        } else {
            if (dfs_low[v] > dfs_num[p]) {
                intersect.insert(adjList[p][v].second);
            }

            dfs_low[p] = min(dfs_low[p], dfs_low[v]);
        }
    } while (!nodes.empty());
}

void findBridges(vector<umap>& adjList, int u) {
    dfs_num.resize(V, WHITE); // Talvez melhorar a geração do subgrafo
    dfs_low.resize(V, 0);
    dfs_parent.resize(V, 0);

    for (int i=0; i<V; i++) {
        if (dfs_num[i] == WHITE && !adjList[i].empty()) {
            bridges(adjList, u);
        }
    } 
}

void dijkstra(vector<umap>& adjList, vll& dist, int s) {
    dist.resize(V, INF);
    dist[s] = 0;

    priority_queue<lli, vlli, greater<lli>> pq;
    pq.push(lli(0, s));

    while (!pq.empty()) {
        lli front = pq.top();
        pq.pop();

        ll d = front.first;
        int u = front.second;

        if (d > dist[u]) continue;
        for (auto& c : adjList[u]) {
            if (dist[u] + c.second.first < dist[c.first]) {
                dist[c.first] = dist[u] + c.second.first;
                pq.push(lli(dist[c.first], c.first));
            }
        }
    }
}

void union_check(vector<umap>& adjList, vector<vll> distances) {
    for (int i=0; i<V; i++) {
        for (auto& c : adjList[i]) {
            if (distances[0][i] + distances[1][c.first] + c.second.first == distances[0][V-1])
                united.insert(c.second.second);
        }
    }
}

int main() {
    cin >> V >> E;
    
    adjList.resize(V, umap());
    tAdjList.resize(V, umap());
    distances.resize(2, vll());

    for (int i=0; i<E; i++) {
        int X, Y;
        ll W;

        cin >> X >> Y >> W;

        adjList[X-1][Y-1]  = lli(W, i + 1);
        tAdjList[Y-1][X-1] = lli(W, i + 1);
    }

    dijkstra( adjList, distances[0], 0);
    dijkstra(tAdjList, distances[1], V-1);

    union_check(adjList, distances);

    vector<umap> subgraph = createSubgraph(adjList, united);
    findBridges(subgraph, 0);

    printSet(united);
    printSet(intersect);

    return 0;
}
