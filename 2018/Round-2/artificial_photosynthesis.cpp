#include <bits/stdc++.h> 

using namespace std;

int ci, wi, so, oo;
int si, oi, co, wo;

int dp[101][101][101][101];

int solve (int c, int o, int w, int s) {
    c = min(c, 100);
    o = min(o, 100); 
    w = min(w, 100);
    s = min(s, 100);
    if (dp[c][o][w][s] >= 0)
        return dp[c][o][w][s];

    int &best = dp[c][o][w][s];
        best = o;
    if (c >= ci && w >= wi)
        best = max(best, solve(c-ci, o+oo, w-wi, s+so));
    if (s >= si && o >= oi)
        best = max(best, solve(c+co, o-oi, w+wo, s-si));
    return dp[c][o][w][s] = best;
}

int main () {
    int cases = 10;
    while (cases--) {
        memset(dp, -1, sizeof(dp));
        int c, o, w, s;
        cin >> c >> o >> w >> s;
        cin >> ci >> wi >> so >> oo;
        cin >> si >> oi >> co >> wo;

        cout << solve(c, o, w, s) << "\r\n";
    }
}
