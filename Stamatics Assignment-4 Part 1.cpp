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

// This code solves the 'Cycle Finding' problem from 'Graph Algorithms' section on CSES.

// Bellman Ford Algorithm
// Single Source Shortest Path Algorithm
// Time Complexity - O(n*m)
const ll INF = 1e15;

struct Edge {
    int a, b, cost;
};
 
void solve() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        Edge t;
        cin >> t.a >> t.b >> t.cost;
        edges.push_back(t);
    }
    vector<ll> dist(n+1, INF);   // stores the shortest distance of i from source.
    vector<int> prev(n+1, -1);   // stores the vertex before i in the shortest path.
    dist[1] = 0;
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (Edge e : edges) {
            if (dist[e.a] + e.cost < dist[e.b]) {
                dist[e.b] = dist[e.a] + e.cost;
                prev[e.b] = e.a;
                x = e.b;
            }
        }
    }
 
    if (x == -1) {
        cout << "NO" << endl;
    } else {
        for (int i = 0; i < n; ++i)   // for finding the vertex which is actually a part of a negative cycle.
            x = prev[x];
 
        vector<int> cycle;
        for (int v = x;; v = prev[v]) {    // for constructing the cycle
            cycle.push_back(v);
            if (v == x && cycle.size() > 1)
                break;
        }
        reverse(cycle.begin(), cycle.end());
 
        cout << "YES" << endl;
        for (int v : cycle)
            cout << v << ' ';
        cout << endl;
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
