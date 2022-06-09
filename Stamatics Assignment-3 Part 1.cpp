#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> ;
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update> ;

#define ll long long
#define ld long double
#define endl '\n'
#define all(v) v.begin(), v.end()
#define ff first
#define ss second

class DSU {
private:
    int n;
    vector<int> p;  // parent
    vector<int> size, rank;
public:
    DSU (int number_of_elements) {
        n = number_of_elements;
        p.resize(n+1);
        size.resize(n+1, 1);
        rank.resize(n+1, 0);
        for (int i = 0; i <= n; i++) {
            p[i] = i;
        }
    }
    int get (int v) {
        return p[v] = (p[v] == v) ? v : get(p[v]);    // path compression
    }
    void union_by_size (int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        p[b] = a;
        size[a] += size[b];
    }
    void union_by_rank (int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return;
        if (rank[a] < rank[b]) swap(a, b);
        p[b] = a;
        if (rank[a] == rank[b]) rank[a]++; 
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edges.insert({u, v});
        edges.insert({v, u});
    }
    vector<vector<int>> queries;
    for (int i = 1; i <= k; i++) {
        string type; cin >> type;
        int u, v; cin >> u >> v;
        if (type == "cut") {
            queries.push_back({1, u, v});
            edges.erase(edges.find({u, v}));
            edges.erase(edges.find({v, u}));
        }
        else {
            queries.push_back({2, u, v});
        }
    }
    reverse(all(queries));
    DSU t1(n);
    for (auto edge : edges) {
        t1.union_by_rank(edge.first, edge.second);
    }
    vector<string> ans;
    for (int i = 0; i < k; i++) {
        if (queries[i][0] == 1) {
            t1.union_by_rank(queries[i][1], queries[i][2]);
        }
        else {
            if (t1.get(queries[i][1]) == t1.get(queries[i][2]))
                ans.push_back("YES");
            else
                ans.push_back("NO");
        }
    }
    reverse(all(ans));
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
}

int main() {

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    /*------------- Code Begins Here --------------*/

    int t = 1;
    // cin >> t;
    for(int test = 1; test <= t; test++) {
        // cout << "Case #" << test << ": ";
        solve();
    }
    
    /*-------------- Code Ends Here ---------------*/ 
    return 0;
}