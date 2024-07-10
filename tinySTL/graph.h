#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Graph {
public:
    Graph(int vertices);
    void addEdge(int u, int v);
    void DFS();
    void BFS();
private:
    void DFSUtil(int v, vector<bool>& visited);
    int vertices;
    vector<vector<int>> adjList;
};

Graph::Graph(int vertices) : vertices(vertices) {
    adjList.resize(vertices);
}

void Graph::addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

void Graph::DFSUtil(int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";

    sort(adjList[v].begin(), adjList[v].end());
    for (int i : adjList[v]) {
        if (!visited[i]) {
            DFSUtil(i, visited);
        }
    }
}

void Graph::DFS() {
    vector<bool> visited(vertices, false);
    for (int i = 0; i < vertices; ++i) {
        if (!visited[i]) {
            DFSUtil(i, visited);
        }
    }
    cout << endl;
}

void Graph::BFS() {
    vector<bool> visited(vertices, false);
    queue<int> q;

    for (int i = 0; i < vertices; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            q.push(i);

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                cout << v << " ";

                sort(adjList[v].begin(), adjList[v].end());
                for (int j : adjList[v]) {
                    if (!visited[j]) {
                        visited[j] = true;
                        q.push(j);
                    }
                }
            }
        }
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.DFS();
    g.BFS();

    return 0;
}
