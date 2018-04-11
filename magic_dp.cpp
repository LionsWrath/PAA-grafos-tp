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

int V, E;
//vector<vi> distances;
vector<unordered_map<int,int>> distances;
vector<umap> adjList;
set<int> united, intersect;

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

void dijkstra_sp(vector<umap>& adjList, unordered_map<int,int>& dist, int s, int v) {
    dist[s] = 0;

    priority_queue<ii, vii, greater<ii>> pq;
    pq.push(ii(0, s));

    while (!pq.empty()) {
        ii front = pq.top();
        pq.pop();

        int d = front.first;
        int u = front.second;

        if (u == v) break;
        if (d > dist[u]) continue;
        for (auto& c : adjList[u]) {
            if (dist.find(c.first) == dist.end()) dist[c.first] = INF;
            if (dist[u] + c.second.first < dist[c.first]) {
                dist[c.first] = dist[u] + c.second.first;
                pq.push(ii(dist[c.first], c.first));
            }
        }
    }
}

void dijkstra(vector<umap>& adjList, unordered_map<int,int>& dist, int s) {
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
            if (dist.find(c.first) == dist.end()) dist[c.first] = INF;
            if (dist[u] + c.second.first < dist[c.first]) {
                dist[c.first] = dist[u] + c.second.first;
                pq.push(ii(dist[c.first], c.first));
            }
        }
    }
}

void intersect_check(vector<umap>& adjList, int min) {
     for (int i=0; i<V; i++) {
        for (auto& c : adjList[i]) {
            vector<umap> newAdjList(adjList);
            unordered_map<int,int> dist;

            newAdjList[i].erase(c.first);
            dijkstra_sp(newAdjList, dist, 0, V-1);

            if (dist[V-1] != min)
                intersect.insert(c.second.second);
        }
    }    
}

void union_check(vector<umap>& adjList, vector<unordered_map<int,int>> distances) {
    for (int i=0; i<V; i++) {
        for (auto& c : adjList[i]) {
            if(distances[c.first].find(V-1) != distances[c.first].end())
                dijkstra_sp(adjList, distances[c.first], c.first, V-1);
            if (distances[0][i] + distances[c.first][V-1] + c.second.first == distances[0][V-1])
                united.insert(c.second.second);
        }
    }
}


int main() {
    cin >> V >> E;
    
    adjList.resize(V, umap());
    distances.resize(V, unordered_map<int,int>());

    for (int i=0; i<E; i++) {
        int X, Y, W;

        cin >> X >> Y >> W;

        adjList[X-1][Y-1] = ii(W, i + 1);
    }

    dijkstra(adjList, distances[0], 0);

    union_check(adjList, distances);
    intersect_check(adjList, distances[0][V-1]);

    printSet(united);
    printSet(intersect);

    return 0;
}
