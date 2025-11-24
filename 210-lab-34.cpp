#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int SIZE = 12; 

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent.at(i) = i;
            rank.at(i) = 1;
        }
    }
    int find(int i) {
        return (parent.at(i) == i) ? i : (parent.at(i) = find(parent.at(i)));
    }
    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank.at(s1) < rank.at(s2)) parent.at(s1) = s2;
            else if (rank.at(s1) > rank.at(s2)) parent.at(s2) = s1;
            else parent.at(s2) = s1, rank.at(s1)++;
        }
    }
};
                              
class Graph {
public:

    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {

        adjList.resize(SIZE);

        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList.at(src).push_back(make_pair(dest, weight));
            adjList.at(dest).push_back(make_pair(src, weight));
        }
    }
    void printGraph(const vector<string>& cityNames) {
        cout << "WEST COAST TRANSPORTATION:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << "City " << i << " - " << cityNames.at(i) << ":" << endl;
            for (Pair v: adjList.at(i))
            cout << "   -> City " << i+1 << ": " << cityNames.at(v.first) << ", Distance: " << v.second << " miles" << endl;
        }
    }

    vector<int> bfs(int src, const vector<string>& cN) {
        int V = adjList.size();
        vector<bool> visited(V, false);
        vector<int> res;
    
        queue<int> q;
    
        visited.at(src) = true;
        q.push(src);

        cout << "\nLayer-by-Layer West Coast Transportation Expansion (BFS) from City "<< src << " (" << cN.at(src) << "):" << endl;
        cout << "Purpose: Analyzing reachable cities by distance from " << cN.at(src) << endl;
        cout << "=================================================" << endl;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            res.push_back(curr);

            cout << "Departing from City " << curr << " (" << cN.at(curr) << "): " << endl;

            for (auto &x : adjList.at(curr)) {
                int c = 1;
                int next = x.first;
                int dist = x.second;
                if (!visited.at(next)) {
                    visited.at(next) = true;
                    q.push(next);
                    cout << "  -> Next stop: City " << next << " (" << cN.at(next) << ") - Distance: " << dist << " miles" << endl;
                }
            }
        }
    
    return res;
    }


    void dfsRec(vector<bool> &visited, int s, vector<int> &res, const vector<string>& cN) {
        visited.at(s) = true;
        res.push_back(s);

        for (auto &i : adjList.at(s)) {
            int dist = i.second;
            int next = i.first;
            if (!visited.at(next)) {
                cout << "Departing from City " << s << " (" << cN.at(s) << ")" << endl;
                cout << " -> Travel route to City " << next << " (" << cN.at(next) << ") - Distance: " << dist << " miles" << endl;
                dfsRec(visited, next, res, cN);
            }
        }    
    }

     vector<int> dfs(int src, const vector<string>& cN) {
        vector<bool> visited(adjList.size(), false);
        vector<int> res;
        cout << "\nTravel Route Trace (DFS) from City " << src << " (" << cN.at(src) << "):" << endl;
        cout << "Purpose: Exploring possible travel itineraries through the West Coast transportation network" << endl;
        cout << "=================================================" << endl;
        dfsRec(visited, src, res, cN);
        return res;
    }

    vector<int> dijkstra(int src) {
        int V = adjList.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V, INT_MAX);

        dist[src] = 0;
        pq.emplace(0, src);

        while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int d = top.first;
        int u = top.second;

        if (d > dist.at(u)) continue;

        for (auto &p : adjList.at(u)) {
            int v = p.first;
            int w = p.second;
            if (dist.at(u) + w < dist.at(v)) {
                dist.at(v) = dist.at(u) + w;
                pq.emplace(dist.at(v), v);
            }
        }
    }
    return dist;
    }

    void kruskalsMST(int V, const vector<Edge>& ed ) {
        vector<vector<int>> e;
        for (auto &edge : ed) {
            e.push_back({edge.src, edge.dest, edge.weight});
        }
        sort(e.begin(), e.end(), [](vector<int>& a, vector<int>& b){ return a.at(2) < b.at(2); });

        DSU dsu(V);
        int cost = 0, count = 0;

        cout << "\nMinimum Spanning Tree edges:" << endl;
        for (auto &edge : e) {
            int x = edge.at(0), y = edge.at(1), w = edge.at(2);
            if (dsu.find(x) != dsu.find(y)) {
                dsu.unite(x, y);
                cost += w;
                cout << "Edge from " << x << " to " << y << " with capacity: " << w << " units" << endl;
                if (++count == V - 1) break;
            }
        }
        cout << "Total MST cost: " << cost << " units" << endl;
    }
    
};

void menu();

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
        {5, 10, 420},  // LS -> SLC
        {10, 11, 520}  // SLC -> DEN
    };

    vector<string> cNames= {    "San Francisco", "San Jose","Sacramento","Los Angeles","San Diego","Las Vegas","Phoenix", "Tucson",       
    "Seattle","Portland","Salt Lake City","Denver"};

    Graph g(edges);

    g.printGraph(cNames);

    g.dfs(0, cNames);

    g.bfs(0, cNames);

    vector<int> dist = g.dijkstra(0); 
    cout << "\nShortest path from node 0:" << " (" << cNames.at(0) << ")" << endl;
    for (int i = 0; i < dist.size(); i++) {
        cout << "0 -> " << i << " : ";
        if (dist.at(i) == INT_MAX){
            cout << "unreachable" << endl;
        }
        else{
            cout << dist.at(i) << endl;
        } 
    }

    g.kruskalsMST(SIZE, edges);






    return 1;

}

void menu(){
    cout << "West Coast Transportation Network Menu:" << endl;
    cout << "[1] Display transportation network" << endl;
    cout << "[2] Explore reachable cities (BFS)" << endl;
    cout << "[3] Trace travel routes (DFS)" << endl;
    cout << "[4] Calculate shortest paths (Dijkstra)" << endl;
    cout << "[5] Find Minimum Spanning Tree (Kruskal)" << endl;
    cout << "[0] Exit" << endl;
    cout << "Enter your choice: ";


}