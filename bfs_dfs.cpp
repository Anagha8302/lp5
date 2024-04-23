#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void parallelBFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

#pragma omp parallel for
            for (int i = 0; i < adj[v].size(); ++i) {
                int n = adj[v][i];
                if (!visited[n]) {
#pragma omp critical
                    {
                        visited[n] = true;
                        q.push(n);
                    }
                }
            }
        }
    }
};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    /*
        0 -------->1
        |         / \
        |        /   \
        |       /     \
        v       v       v
        2 ----> 3       4
        |      |
        |      |
        v      v
        5      6
    */
    cout << "Breadth-First Search (BFS): ";
    g.parallelBFS(0);
    cout << endl;

    return 0;
}
/*--------------------------dfs-----------------------*/
#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

class Graph {
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void parallelDFS(int startVertex) {
        vector<bool> visited(V, false);
        stack<int> stk;

        stk.push(startVertex);
        while (!stk.empty()) {
            int v = stk.top();
            stk.pop();

            if (!visited[v]) {
                cout << v << " ";
                visited[v] = true;

#pragma omp parallel for
                for (int i = 0; i < adj[v].size(); ++i) {
                    int n = adj[v][i];
                    if (!visited[n]) {
#pragma omp critical
                        {
                            stk.push(n);
                        }
                    }
                }
            }
        }
    }
};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "Depth-First Search (DFS): ";
    g.parallelDFS(0);
    cout << endl;

    return 0;
}
