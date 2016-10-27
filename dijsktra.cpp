#include <iostream>
#include <vector>
#include <list>
#include <limits>

using namespace std;

class SafeMap
{
    private:
    int V;
    list <int> *adj;
    public:
    SafeMap (int V)
    {
        this->V = V;
        adj = new list <int> [V];
    }
    void addSafeRoute (int w, int v)
    {
        adj[w].push_back(v);
    }
    int isReachable (int s, int d);
};

int SafeMap::isReachable (int s, int d)
{
    bool *visited = new bool[V], done = false;
    vector <int> dist(V);
    list <int> queue;
    int new_dist = 0, min = INT_MAX, j;

    for (int j = 0; j < V; ++j) {
        visited[j] = false;
        dist[j] = INT_MAX;
    }
    
    visited[s] = true;
    dist[s] = 0;
    queue.push_back(s);
    list <int>::iterator i;

    while (!done) {
        min = INT_MAX;
        visited[s] = true;
        new_dist = 0;
        /* Keep track of the vertices that are visited */
        queue.push_back(s);
        for (j = 0; j < V; ++j) {
            if (min > dist[j] && !visited[j]) {
                min = dist[j];
                s = j;
            }
        }
        if (!adj[s].empty()) {
            for (i = adj[s].begin(); i != adj[s].end(); ++i) {
                /* Update the distance between the current node and source */
                new_dist = dist[s] + 1;
                if (new_dist < dist[*i]) {
                    dist[*i] = dist[s] + 1;
                }
            }
        }
        /* If all the verices are visited, we are done */
        if (queue.size() == V - 1) {
            done = true;
        }
    }
    return ((dist[d] == INT_MAX) ? -1 : dist[d]);
}

int main()
{
    SafeMap sm(9);
    int s, d;
    cin >> s >> d;

    sm.addSafeRoute(0, 1);
    sm.addSafeRoute(0, 7);
    sm.addSafeRoute(1, 2);
    sm.addSafeRoute(1, 7);
    sm.addSafeRoute(2, 3);
    sm.addSafeRoute(2, 8);
    sm.addSafeRoute(2, 5);
    sm.addSafeRoute(3, 4);
    sm.addSafeRoute(3, 5);
    sm.addSafeRoute(5, 4);
    sm.addSafeRoute(6, 5);
    sm.addSafeRoute(6, 8);
    sm.addSafeRoute(7, 6);
    sm.addSafeRoute(7, 8);
    sm.addSafeRoute(8, 6);
    /*sm.addSafeRoute(0, 1);
    sm.addSafeRoute(0, 2);
    sm.addSafeRoute(1, 2);
    sm.addSafeRoute(2, 0);
    sm.addSafeRoute(2, 3);*/

    d = sm.isReachable(s, d);
    cout << "Reachable distance: " << d << endl;
    return 0;
}

