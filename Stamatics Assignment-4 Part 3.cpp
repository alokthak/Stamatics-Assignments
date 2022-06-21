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
 
// Floyd Warshall's Algorithm
// All Pair Shortest Path Algorithm
// Time Complexity - O(n^3)
const ll INF = 1e15;
 
void solve() {
    int n, m;
    cin >> n >> m;

    ll dist[n+1][n+1];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            }
            else {
                dist[i][j] = INF;
            }
        }
    }
 
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        dist[u][v] = cost;
        dist[v][u] = cost;  // because it is an undirected graph.
    }

    // Floyd Warshall's Algorithm
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // update a cell to new value. And hence, update the shortest path length between
    // all affected pairs (i, j) in O(n^2) time compexity.

    int x, y, cost;
    cin >> x >> y;
    dist[x][y] = cost;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = min(dist[i][j], dist[i][x] + dist[x][y] + dist[y][j]);
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
