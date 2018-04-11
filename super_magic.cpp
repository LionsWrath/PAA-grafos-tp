#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

#define INF 1000000000
#define WHITE -1

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef unordered_map<int, ii> umap;

int V, E;
vector<vi> distances;
vector<umap> adjList;
set<int> united, intersect;

int dfs_counter;
vi dfs_num, dfs_low, dfs_parent;

//--------------------------------------------------------------------------------------------------

template <typename Iter, typename Cont>
bool is_last(Iter iter, const Cont& cont) {
    return (iter != cont.end()) && (next(iter) == cont.end());
}

//--------------------------------------------------------------------------------------------------

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
                newAdjList[i][c.first] = ii(c.second);
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

vector<umap> transpose(vector<umap>& adjList) {
    vector<umap> newAdjList(V, umap());
    for (int i=0; i<V; i++) {
        for (auto& c : adjList[i]) {
            newAdjList[c.first][i] = ii(c.second); 
        }
    }

    return newAdjList;
}

void bridges(vector<umap>& adjList, int u) {
    dfs_low[u] = dfs_num[u] = dfs_counter++;

    for (auto& c : adjList[u]) {
        if (dfs_num[c.first] == WHITE) {
            dfs_parent[c.first] = u;
            bridges(adjList, c.first);

            if (dfs_low[c.first] > dfs_num[u])
                intersect.insert(adjList[u][c.first].second);

            dfs_low[u] = min(dfs_low[u], dfs_low[c.first]);
        } else if (c.first != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[c.first]);
        }
    }
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

void dijkstra(vector<umap>& adjList, vi& dist, int s) {
    dist.resize(V, INF);
    dist[s] = 0;

    priority_queue<ii, vii, greater<ii>> pq;
    pq.push(ii(0, s));

    while (!pq.empty()) {
        ii front = pq.top();
        pq.pop();

        int d = front.first;
        int u = front.second;

        if (d > dist[u]) continue;
        for (auto& c : adjList[u]) {
            if (dist[u] + c.second.first < dist[c.first]) {
                dist[c.first] = dist[u] + c.second.first;
                pq.push(ii(dist[c.first], c.first));
            }
        }
    }
}

void union_check(vector<umap>& adjList, vector<vi> distances) {
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
    distances.resize(2, vi());

    for (int i=0; i<E; i++) {
        int X, Y, W;

        cin >> X >> Y >> W;

        adjList[X-1][Y-1] = ii(W, i + 1);
    }

    dijkstra(adjList, distances[0], 0);
    vector<umap> transposed = transpose(adjList);
    dijkstra(transposed, distances[1], V-1);

    union_check(adjList, distances);

    vector<umap> subgraph = createSubgraph(adjList, united);
    findBridges(subgraph, 0);

    printSet(united);
    printSet(intersect);

    return 0;
}
