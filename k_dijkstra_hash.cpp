#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

#define INF 1000000000

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef unordered_map<int, ii> umap;

int V, E, I;
vi dist;
vector<set<int>> parent;
vector<umap> adjList;
set<int> united, intersect;

bool first_find = true;

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

void unitePath(const set<int>& path) {
    united.insert(path.begin(), path.end());
}

void intersectPath(const set<int>& path) {
    if (first_find) {
        intersect = path;
        first_find = false;
    } else {
        set<int> newIntersect;

        set_intersection( 
                intersect.begin(), 
                intersect.end(), 
                path.begin(), 
                path.end(),
                inserter(newIntersect, newIntersect.begin()));

        intersect = newIntersect;
    }
}

void generateShortestPaths(int v, set<int> path = set<int>(), int sum = 0) {
    if (sum > dist[V-1]) return;
    if (parent[v].size() == 0) {
        unitePath(path);
        intersectPath(path);
    } else {
        for (auto u : parent[v]) {
            ii c = adjList[u][v];

            set<int> newPath = path;
            newPath.insert(c.second);
            
            generateShortestPaths(u, newPath, sum + c.first);
        }
    }
}

void dijkstra(vector<umap>& adjList, int s) {
    dist.resize(V, INF);
    parent.resize(V, set<int>());

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
            if (dist[u] + c.second.first <= dist[c.first]) {
                dist[c.first] = dist[u] + c.second.first;
                parent[c.first].insert(u);
                pq.push(ii(dist[c.first], c.first));
            }
        }
    }
}

int main() {
    cin >> V >> E;
    
    adjList.resize(V, umap());

    for (int i=0; i<E; i++) {
        int X, Y, W;

        cin >> X >> Y >> W;

        adjList[X-1][Y-1] = ii(W, i + 1);
    }

    //printAdjacencyList(adjList);

    dijkstra(adjList, 0);
    generateShortestPaths(V-1);

    printSet(united);
    printSet(intersect);

    return 0;
}
