#include <bits/stdc++.h> 

using namespace std;

int n, x, y, z;

string encode (string s) {
    stringstream ss;
    for (char c : s) {
        if (c == '0')
            ss << (char)(z + '0');
        else if (c % 2 == 0) {
            int v = c - '0' + x;
            ss << to_string(v);
        } else {
            int v = max(0, c - '0' - y);
            ss << to_string(v);
        }
    }
    return ss.str();
}

int main () {
    int cases = 10;
    while(cases--) {
        cin >> n >> x >> y >> z;
        vector<string> ids(n);
        for (int i = 0; i < n; ++i)
            cin >> ids[i];
        string tmp;
        cin >> tmp;
        vector<int> fails;
        for (int i = 0; i < n; ++i) {
            string newid;
            cin >> newid;
            if (encode(ids[i]) != newid)
                fails.push_back(i+1);
        }
        if (fails.size() == 0)
            cout << "MATCH\r\n";
        else {
            cout << "FAIL: ";
            for (int i = 0; i < fails.size(); ++i) {
                if (i) cout << ",";
                cout << fails[i];
            }
            cout << "\r\n";
        }
        cin >> tmp;
    }
}
