#include <iostream>
#include <vector>
#define INF 999
using namespace std;

int cost[100][100], v; 
int dist[100], src, dest;
bool visited[100];
int parent[100];

void init() {
    for (int i = 0; i < v; i++) {
        parent[i] = -1;   
        dist[i] = INF;
        visited[i] = false;
    }
    dist[src] = 0;
}

int getNearest() {
    int minvalue = INF;
    int minnode = -1;
    for (int i = 0; i < v; i++) {
        if (!visited[i] && dist[i] < minvalue) {
            minvalue = dist[i];
            minnode = i;
        }
    }
    return minnode; 
}

void dijkstra() {
    for (int i = 0; i < v; i++) {
        int nearest = getNearest();
        if (nearest == -1) break;  
        visited[nearest] = true;
        
        for (int adj = 0; adj < v; adj++) {
            if (!visited[adj] && cost[nearest][adj] != INF && dist[nearest] != INF) {
                if (dist[nearest] + cost[nearest][adj] < dist[adj]) {
                    dist[adj] = dist[nearest] + cost[nearest][adj];
                    parent[adj] = nearest;
                }
            }
        }
    }
}

void displayPath(int node) {
    vector<int> path;
    for (int v = node; v != -1; v = parent[v]) {
        path.insert(path.begin(), v); 
    }

    cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    cout << "Enter number of nodes: ";
    cin >> v;

    cout << "Enter cost matrix (use " << INF << " for no edge):\n";
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            cin >> cost[i][j];

    cout << "Enter source node: ";
    cin >> src;

    cout << "Enter destination node: ";
    cin >> dest;

    init();
    dijkstra();

    if (dist[dest] >= INF) {
        cout << "No path exists from " << src << " to " << dest << endl;
    } else {
        cout << "Shortest distance from " << src << " to " << dest << " is " << dist[dest] << endl;
        displayPath(dest);
    }

    return 0;
}
/*Input:
Enter number of nodes: 5
Enter cost matrix (use 999 for no edge):
0 10 999 30 100
10 0 50 999 999
999 50 0 20 10
30 999 20 0 60
100 999 10 60 0
Enter source node: 0
Enter destination node: 4
*/

/*
Output:
Shortest distance from 0 to 4 is 60
Path: 0 -> 3 -> 2 -> 4
*/
