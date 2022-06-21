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

// This code solves the 'Investigation' problem from 'Graph Algorithms' section on CSES.
 
// Dijkstra's Algorithm
// Single Source Shortest Path Algorithm
// Time Complexity - O(m * log(n))
const ll INF = 1e15;
const ll MOD = 1e9+7;
 
void solve() {
    int n, m;
    cin >> n >> m;
 
    vector<pair<int, int>> adj[n+1];
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        adj[u].push_back({v, cost});
    }
 
    vector<ll> dist(n+1, INF);   // stores the shortest distance of i from source.
    vector<int> prev(n+1, -1);   // stores the vertex before i in the shortest path.
    int min_edges[n+1], max_edges[n+1];
    ll total_paths[n+1];
    dist[1] = 0;
    min_edges[1] = 0;
    max_edges[1] = 0;
    total_paths[1] = 1;
 
    set<pair<ll, int>> q;
    q.insert({0, 1});
    while (!q.empty()) {
        int v = q.begin()->second;
        ll dist_v = q.begin()->first;
        q.erase(q.begin());
 
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;
 
            if (dist[v] + len < dist[to]) {
                q.erase({dist[to], to});
                dist[to] = dist[v] + len;
                prev[to] = v;
                q.insert({dist[to], to});
                min_edges[to] = min_edges[v] + 1;
                max_edges[to] = max_edges[v] + 1;
                total_paths[to] = total_paths[v];
            }
            else if (dist[v] + len == dist[to]) {
                min_edges[to] = min(min_edges[to], min_edges[v] + 1);
                max_edges[to] = max(max_edges[to], max_edges[v] + 1);
                total_paths[to] = (total_paths[to] + total_paths[v]) % MOD;
            }
        }
    }
 
    cout << dist[n] << " " << total_paths[n] << " " << min_edges[n] << " " << max_edges[n] << endl;
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