#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 7; 

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  
                              
class Graph {
public:

    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {

        adjList.resize(SIZE);

        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " ---> ";
            for (Pair v: adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    vector<int> bfs(int src) {
        int V = adjList.size();
        vector<bool> visited(V, false);
        vector<int> res;
    
        queue<int> q;
    
        visited[src] = true;
        q.push(src);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            res.push_back(curr);

            for (auto &x : adjList[curr]) {
                int next = x.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
    
    return res;
    }


    void dfsRec(vector<bool> &visited, int s, vector<int> &res) {
        visited[s] = true;
        res.push_back(s);

        for (auto &i : adjList[s]) {
            int next = i.first;
            if (!visited[next]) {
                dfsRec(visited, next, res);
            }
        }
    }

     vector<int> dfs(int src) {
        vector<bool> visited(adjList.size(), false);
        vector<int> res;
        dfsRec(visited, src, res);
        return res;
    }
    
};

int main(){
    vector<Edge> edges = {
        {0, 1, 12}, 
        {0, 2, 8}, 
        {0, 3, 21},
        {2, 3, 6}, 
        {2, 6, 2}, 
        {2, 5, 5}, 
        {2, 4, 4},
        {5, 6, 6}, 
        {5, 4, 9}
    };

    Graph g(edges);

    g.printGraph();

    vector<int> bsf_order = g.bfs(0);
    cout << "BFS starting from vertex 0:" << endl;
    for (int v : bsf_order) cout << v << " ";
    cout << endl;

    vector<int> dsf_order = g.dfs(0);
    cout << "DFS starting from vertex 0:" << endl;
    for (int v : dsf_order) cout << v << " ";
    cout << endl;





    return 1;

}