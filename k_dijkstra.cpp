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

int V, E, I;
vi dist;
vector<set<int>> parent;
vector<set<int>> paths;
vector<vii> adjList;
vii edges;

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

void unitePathSets() {
    set<int> united;

    for (int i=0; i<paths.size(); i++) {
        united.insert(paths[i].begin(), paths[i].end());
    }

    for (auto e : united) 
        cout << e << " ";
    cout << endl;
}

void intersectPathSets() {
    set<int> intersect;

    for (int i=1; i<paths.size(); i++) {
        set_intersection(
                paths[i-1].begin(), paths[i-1].end(), 
                paths[i].begin(), paths[i].end(),
                inserter(intersect, intersect.begin()));
    }

    for (auto e : intersect)
        cout << e << " ";
    cout << endl;
}

int calculatePathWeight(vi path) {
    
    int sum = 0;
    for (int i=path.size()-2; i>=0; i--) {
        auto it = find_if(adjList[path[i+1]].begin(), adjList[path[i+1]].end(),
                [&path, &i](const ii& e){ return e.first == path[i]; });

        sum += (*it).second;
    }

    return sum;
}

void convertPathToSet(vi path) {
    set<int> converted;
    
    for (int i=path.size()-2; i>=0; i--) {
        for (int j=0; j<edges.size(); j++) {
            if (edges[j].first == path[i+1] && edges[j].second == path[i]) 
                converted.insert(j+1);
        }
    }

    paths.push_back(converted);
}

void generateShortestPaths(int v, vi path) {
    path.push_back(v);

    if (parent[v].size() == 0) {
        if (dist[V-1] == calculatePathWeight(path)) {
            for (vi::reverse_iterator it = path.rbegin(); it != path.rend(); ++it)
                cout << *it + 1 << " -> ";

            cout << " P: " << calculatePathWeight(path) << endl;
            convertPathToSet(path);
        }
    } else {
        for (auto u : parent[v]) {
            generateShortestPaths(u, path);
        }
    }
}

void dijkstra(vector<vii>& adjList, int s) {
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
        for (int j=0; j<adjList[u].size(); j++) {
            ii v = adjList[u][j];

            if (dist[u] + v.second <= dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                parent[v.first].insert(u);
                pq.push(ii(dist[v.first], v.first));
            }
        }
    }
}

int main() {
    cin >> V >> E;
    
    adjList.resize(V, vii());

    for (int i=0; i<E; i++) {
        int X, Y, W;

        cin >> X >> Y >> W;

        edges.push_back(ii(X,Y));
        adjList[X].push_back(ii(Y,W));
    }

    printAdjacencyList(adjList);

    dijkstra(adjList, 0);
    generateShortestPaths(V-1, vi());

    unitePathSets();
    intersectPathSets();

    return 0;
}
