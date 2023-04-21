#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <tuple>

using namespace std;

int n = 0;
vector<int> x, y, k, c;

void read_input() {
    cin >> n;
    x = vector<int>(n+1);
    y = vector<int>(n+1);
    k = vector<int>(n+1);
    c = vector<int>(n+1);
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        cin >> k[i];
}

void process() {
    vector<long long> dist(n+1);
    vector<int> prev(n+1);
    vector<bool> popped(n+1, false);
    int count = 0;
    long long cost = 0;

    vector<int> powerplant;
    vector<pair<int,int>> connections;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;

    for (int i = 1; i <= n; i++) {
        dist[i] = c[i];
        prev[i] = 0;
        q.push({c[i], i});
    }

    while (count < n) {
        auto [d, u] = q.top();
        q.pop();
        if (!popped[u]) {
            popped[u] = true;
            if (prev[u] == 0) {
                powerplant.push_back(u);
            } else {
                connections.push_back({u, prev[u]});
            }
            count++;
            cost += dist[u];
            for (int v = 1; v <= n; v++)
                if (!popped[v]) {
                    long long new_dist = ((long long)k[u] + k[v]) * (abs(x[u] - x[v]) + abs(y[u] - y[v]));
                    if (new_dist < dist[v]) {
                        dist[v] = new_dist;
                        prev[v] = u;
                        q.push({dist[v], v});
                    }
                }
        }
    }

    cout << cost << endl;
    cout << powerplant.size() << endl;
    for (int i: powerplant)
        cout << i << ' ';
    cout << endl;
    cout << connections.size() << endl;
    for (auto [u,v]: connections)
        cout << u << ' ' << v << endl;
}


int main() {
    read_input();
    process();
    return 0;
}