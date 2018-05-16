#include <bits/stdc++.h>

using namespace std; 

struct T {
    bool end;
    char c;
    unordered_map<char, shared_ptr<T>> next;
    T() {}
    T(char c) : c(c), end(false) {}
    T(const T &t) : c(t.c) {} // Only need the c value.
};

int main () {
    for (int t = 0; t < 10; ++t) {
        shared_ptr<T> trie {new T{'.'}};
        set<string> dict;
        int n; 
        cin >> n; 
        for (int i = 0; i < n; ++i) {
            shared_ptr<T> cur = trie;
            string s; 
            cin >> s;
            // Maintain dictionary.
            dict.emplace(s);
            // And Trie.
            for (int j = 0; j < s.length(); ++j) {
                if (cur->next.find(s[j]) == cur->next.end())
                    cur->next.emplace(s[j], make_shared<T>(s[j]));
                cur = cur->next[s[j]];
            }
            cur->end = true;
        }
        
        string enc;
        cin >> enc;
        n = enc.length();

        // Brute Force.
        map<string, int> mp;
        for (auto &word : dict) {
            shared_ptr<T> cur = trie;
            bool bad = false;
            // Heuristic: Check if the first twelve characters are the beginnings of a word.
            if (enc.length() > 50) {
                int LIM = 12;
                stringstream ss;
                for (int i = 0; i < LIM; ++i) {
                    char c = (enc[i] - word[i%word.length()] + 25)%26 + 65;
                    ss << c;
                }
                string dec = ss.str();

                vector<bool> dp (LIM, false);
                dp[0] = true;
                bool passed = false;
                for (int i = 0; i < LIM; ++i) {
                    if (!dp[i])
                        continue;
                    shared_ptr<T> cur = trie;
                    bool bad = false;
                    for (int j = i; j < LIM; ++j) {
                        if (cur->next.find(dec[j]) == cur->next.end()) {
                            bad = true;
                            break;
                        }
                        cur = cur->next[dec[j]];
                        if (cur->end) {
                            if (j == LIM - 1)
                                break;
                            dp[j+1] = true;
                        }
                    }
                    if (!bad) {
                        passed = true;
                        break;
                    }
                }
                if (!passed)
                    continue;
            }

            stringstream ss;
            for (int i = 0; i < n; ++i) {
                char c = (enc[i] - word[i%word.length()] + 25)%26 + 65;
                ss << c;
            }
            string dec = ss.str();

            // DP to see if valid.
            vector<int> dp(n + 1, -1);
            dp[n] = 0;
            for (int i = n - 1; i >= 0; --i) {
                shared_ptr<T> cur = trie;
                for (int j = i; j < dec.length(); ++j) {
                    if (cur->next.find(dec[j]) == cur->next.end())
                        break;
                    cur = cur->next[dec[j]];
                    if (cur->end && dp[j+1] >= 0 && (dp[i] < 0 || dp[j+1] + (j-i+1)*(j-i+1) < dp[i])) {
                        dp[i] = dp[j+1] + (j-i+1)*(j-i+1);
                    }
                }
            }
            if (dp[0] >= 0) {
                mp[dec] = dp[0];
            }
        }
        if (mp.size() == 0) {
            cout << "FAIL!" << endl;
            continue;
        }
        pair<string, int> ans = *mp.begin();
        cout << ans.first.substr(0, 10) << " " << ans.second << endl;
    }
}
