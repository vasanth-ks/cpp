#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>

using namespace std;

typedef pair <int, int> iPair;

class SafeMap
{
    private:
    int V;
    list <iPair> *adj;
    public:
    SafeMap (int V)
    {
        this->V = V;
        adj = new list <iPair> [V];
    }
    void addSafeRoute (int u, int v, int w)
    {
        adj[u].push_back({v, w});
    }
    int isReachable (int s, int d);
};

int SafeMap::isReachable (int s, int d)
{
    vector <int> distance(V, INT_MAX);
    vector <bool> visited(V, false);
    
    auto myComp = [](const iPair &a, const iPair &b) {
        return a.second > b.second;
    };

    priority_queue <iPair, vector <iPair>, decltype(myComp)> q(myComp);
    
    distance[s] = 0;
    q.push({s, distance[s]});
    
    while (!q.empty()) {
        iPair curr = q.top();
        q.pop();
        
        visited[curr.first] = true;
        list <iPair> neighbors = adj[curr.first];
        
        for (auto n : neighbors) {
            int dist = 0;
            
            if (!visited[n.first]) {
                dist = distance[curr.first] + n.second;
                if (dist < distance[n.first]) {
                    distance[n.first] = dist;
                    q.push({n.first, distance[n.first]});
                }
            }
        }
        
    }

    return ((distance[d] == INT_MAX) ? -1 : distance[d]);
}

int main()
{
    SafeMap sm(9);
    int s, d;
    cin >> s >> d;

    sm.addSafeRoute(0, 1, 4);
    //sm.addSafeRoute(0, 7, 8);
    sm.addSafeRoute(1, 2, 8);
    sm.addSafeRoute(1, 7, 11);
    sm.addSafeRoute(2, 3, 7);
    sm.addSafeRoute(2, 8, 2);
    sm.addSafeRoute(2, 5, 4);
    sm.addSafeRoute(3, 4, 9);
    sm.addSafeRoute(3, 5, 14);
    sm.addSafeRoute(4, 5, 10);
    sm.addSafeRoute(5, 6, 2);
    sm.addSafeRoute(6, 7, 1);
    sm.addSafeRoute(6, 8, 6);
    sm.addSafeRoute(7, 8, 7);
    /*sm.addSafeRoute(0, 1);
    sm.addSafeRoute(0, 2);
    sm.addSafeRoute(1, 2);
    sm.addSafeRoute(2, 0);
    sm.addSafeRoute(2, 3);*/

    d = sm.isReachable(s, d);
    cout << "Reachable distance: " << d << endl;
    return 0;
}

