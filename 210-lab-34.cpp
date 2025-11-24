#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 12; 

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
                cout << "(" << i << ", " << v.first << ", " << v.second << ") ";
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
    
};

int main(){
    vector<Edge> edges = {
        {0, 1, 50},    // SF -> SJ
        {0, 2, 90},    // SF -> SAC
        {2, 9, 580},   // SAC -> PDX
        {9, 8, 170},   // PDX -> SEA
        {1, 3, 340},   // SJ -> LA
        {3, 4, 120},   // LA -> SD
        {3, 5, 270},   // LA -> LS
        {4, 6, 355},   // SD -> PHX
        {6, 7, 115},   // PHX -> TUS
        {6, 5, 300},   // PHX -> LS
        {5, 10, 420},  // LS -> SLC
        {10, 11, 520}  // SLC -> DEN
    };

    Graph g(edges);

    g.printGraph();



    return 1;

}