#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

vector<vector<int>> G;
vector<vector<pair<int, int>>> E;
int n, m;

void read_graph(char* file_name, vector<vector<int>>& G, vector<vector<pair<int,int>>>& E) {
    ifstream fin;
    fin.open(file_name);
    fin >> n >> m;
    G = vector<vector<int>>(n, vector<int>(n, 0));
    E = vector<vector<pair<int, int>>>(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        E[u].emplace_back(v, w);
        G[u][v] = w;
    }
    fin.close();
}

void push(int u, int v, vector<int>& e, vector<int>& h, vector<vector<int>>& G_f, queue<int>& q) {
    int delta = min(e[u], G_f[u][v]);
    cout << "push: " << "(Node " << u << ", e " << e[u] << ", h " << h[u] << ") --> " << "(Node " << v << ", e " << e[v] << ", h " << h[v] << ") : " << delta << endl;
    G_f[u][v] -= delta;
    G_f[v][u] += delta;
    e[u] -= delta;
    e[v] += delta;
    q.push(v);
    cout << "(Node " << u << ", e " << e[u] << ", h " << h[u] << ")(Node " << v << ", e " << e[v] << ", h " << h[v] << ")" << endl;
    cin.get();
}

void relabel(int u, vector<int>& e, vector<int>& h, vector<vector<int>>& G_f) {
    int tmp = 3 * n;
    cout << "relabel (Node " << u << ", e " << e[u] << ", h " << h[u] << "): ";
    for (int v = 0; v < n; v++)
        if (G_f[u][v] > 0) {
            tmp = min(tmp, h[v]);
            cout << "(Node " << v << ", e " << e[v] << ", h " << h[v] << ")";
        }
    cout << endl;
    h[u] = tmp + 1;
    cout << "(Node " << u << ", e " << e[u] << ", nh " << h[u] << ")" << endl;
    cin.get();
}

void init_preflow(vector<vector<int>>& G, vector<int>& h, vector<int>& e, queue<int>& q) {
    h[0] = n;
    for (int v = 0; v < n; v++)
        if (G[0][v] > 0) {
            e[v] += G[0][v];
            e[0] -= G[0][v];
            G[v][0] += G[0][v];
            G[0][v] = 0;
            q.push(v);
        }
}

pair<vector<vector<int>>, int> max_flow(vector<vector<int>>& G) {
    vector<vector<int>> G_f(G);
    vector<int> h(n, 0);
    vector<int> e(n, 0);
    vector<int> next_v(n, 0);
    queue<int> q;

    init_preflow(G_f, h, e, q);
    while (q.size() > 0) {
        int u = q.front();
        q.pop();
        if (u == n-1) continue;
        while (e[u] > 0) {
            if (next_v[u] == n) {
                relabel(u, e, h, G_f);
                next_v[u] = 0;
            } else if (G_f[u][next_v[u]] > 0 && h[u] == h[next_v[u]]+1) {
                push(u, next_v[u], e, h, G_f, q);
            } else {
                next_v[u]++;
            }
        }
    }
    return {G_f, -e[0]};
}

void output_flow(int flow, vector<vector<pair<int,int>>>& E, vector<vector<int>>& G_f) {
    cout << "max flow: " << flow << endl;
    for (int u = 0; u < n; u++)
        for (auto [v, w]: E[u])
            if (G_f[u][v] < w)
                cout << u << " --> " << v << " : " << w - G_f[u][v] << endl;  
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Need file name" << endl;
        return -1;
    }
    read_graph(argv[1], G, E);
    auto [G_f, f] = max_flow(G);
    output_flow(f, E, G_f);
    return 0;
}