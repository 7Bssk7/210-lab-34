#include <iostream>
#include <vector>
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
        for (int i = 0; i < adjList.size(); i++) {
            for (Pair v: adjList[i])
                cout << "(" << i << ", " << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
};

int main(){

    return 1;

}