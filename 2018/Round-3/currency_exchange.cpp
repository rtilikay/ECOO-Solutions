#include <bits/stdc++.h> 

using namespace std;

const int N = 10101;
const double INF = 1e9;

vector<pair<int, double>> adj[N];

int main () {
    int cases = 10;
    while (cases--) {
        for (int i = 0; i < N; ++i)
            adj[i].clear();
        int n, m;
        double d;
        cin >> n >> m >> d;
        for (int i = 0; i < m; ++i) {
            int a, b;
            double c;
            cin >> a >> b >> c;
            c = log(c);
            adj[a].push_back(make_pair(b, c));
        }

        vector<double> dist(n+1, INF);
        dist[1] = 0;

        for (int k = 0; k < n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (auto &p : adj[i]) {
                    dist[p.first] = min(dist[p.first], dist[i] + p.second);
                }
            }
        }
        
        double ans = dist[n];
        bool inf = ans < -log(1e9/d);
        for (int k = 0; k < n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (auto &p : adj[i]) {
                    dist[p.first] = min(dist[p.first], dist[i] + p.second);
                }
            }
        }
        inf |= dist[n] < ans;
        
        if (inf) {
            cout << "Billionaire!" << endl;
        }
        else {
            cout << fixed << setprecision(2) << d*exp(-ans) << endl;
        }
    }
}
