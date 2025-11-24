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
        {5, 10, 420},  // LS -> SLC
        {10, 11, 520}  // SLC -> DEN
    };

    vector<string> cNames= {    "San Francisco", "San Jose","Sacramento","Los Angeles","San Diego","Las Vegas","Phoenix", "Tucson",       
    "Seattle","Portland","Salt Lake City","Denver"};

    Graph g(edges);

    g.printGraph(cNames);

    g.dfs(0, cNames);

    g.bfs(0, cNames);






    return 1;

}