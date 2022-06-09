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
    vector<int> size, rank;   // 2 methods of union
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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }
    sort(all(edges));
    DSU t(n);
    ll sum = 0;
    for (int i = 0; i < m; i++) {
        if (t.get(edges[i][1]) == t.get(edges[i][2])) continue;
        t.union_by_rank(edges[i][1], edges[i][2]);
        sum += edges[i][0];
    }
    cout << sum << endl;
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