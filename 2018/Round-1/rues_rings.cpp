#include <bits/stdc++.h> 

using namespace std;

int main () {
    int cases = 10;
    while (cases--) {
        int n;
        cin >> n;
        map<int, vector<int>> mp;
        for (int i = 0; i < n; ++i) {
            int id, k;
            cin >> id >> k;
            int mind = 1e9;
            for (int j = 0; j < k; ++j) {
                int temp;
                cin >> temp;
                mind = min(mind, temp);
            }
            mp[mind].push_back(id);
        }

        vector<int> ans = (*mp.begin()).second;
        sort(ans.begin(), ans.end());

        cout << (*mp.begin()).first << " {";
        for (int i = 0; i < ans.size(); ++i) {
            if (i) cout << ",";
            cout << ans[i];
        }
        cout << "}\r\n";
    }
}
