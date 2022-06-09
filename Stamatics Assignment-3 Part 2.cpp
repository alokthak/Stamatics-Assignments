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

// This solves 'Range Update Queries' problem from the 'Range Queries' section on CSES.
class Fenwick_Tree {
private:
    int n;
    vector<ll> table;
public:
    Fenwick_Tree (vector<int> &a) {
        n = a.size();
        table.resize(n+1, 0);
        // Note: comment below code for range update and point query
        // for (int i = 0; i < n; i++) {
        //     point_update(i+1, a[i]);
        // }
    }
    void point_update (int i, int delta) {
        while (i <= n) {
            table[i] += delta;
            i += (i & (-i));
        }
    }
    ll point_query (int i) {
        ll sum = 0;
        while (i) {
            sum += table[i];
            i -= (i & (-i));
        }
        return sum;
    }
    void range_update (int l, int r, int delta) {
        point_update(l, delta);
        if (r+1 <= n) point_update(r+1, -delta);
    }
    ll range_query (int l, int r) {
        if (l == 1) return point_query(r);
        return point_query(r) - point_query(l-1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    Fenwick_Tree BIT(a);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l, r, delta;
            cin >> l >> r >> delta;
            BIT.range_update(l, r, delta);
        }
        else {
            int k; cin >> k;
            cout << a[k-1] + BIT.point_query(k) << endl;
        }
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