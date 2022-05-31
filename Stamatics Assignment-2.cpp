#include<bits/stdc++.h>
using namespace std;

/*
The current code is able to solve the following CSES problem:
'Giant Pizza' in Graph Algorithms Section using 2SAT.

It also has the answers to all the questions in Assignment 2.
*/

// Vertices are n numbered from 1 to n.
class Directed_Graph {
private:
    int n;
    vector<vector<int>> adj;
    vector<int> state;
    vector<int> topo_order;
    vector<int> pre;
    vector<int> id;
    vector<int> low;
    stack<int> stk;
    int preorderCounter, numSCCs;

public:
    Directed_Graph(int nodes, vector<vector<int>>& adjacencyList) {
        n = nodes;
        adj = adjacencyList;
        state.resize(n+1);
    }

    vector<int> TopSort() {
        topo_order.clear();

        vector<int> indeg(n+1, 0);
        for (int i = 1; i <= n; i++) {
            for (auto j : adj[i])
                indeg[j]++;
        }

        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (indeg[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int curr = q.front();
            topo_order.push_back(curr);
            q.pop();

            for (auto j : adj[curr]) {
                indeg[j]--;
                if (indeg[j] == 0) {
                    q.push(j);
                }
            }
        }

        if (topo_order.size() < n) return {}; // Has a cycle
        return topo_order;
    }

    // Application of TopSort
    vector<int> Path_Problem (int u, int v) { // Assumed that the input graph is a DAG.
        int shortest_path_length[n+1], longest_path_length[n+1], total_paths[n+1];
        for (int i = 1; i <= n; i++) shortest_path_length[i] = 1e9;
        memset(longest_path_length, -1, sizeof(longest_path_length));
        memset(total_paths, 0, sizeof(total_paths));
        total_paths[u] = 1;
        shortest_path_length[u] = 0;
        longest_path_length[u] = 0;
        for (auto x : topo_order) {
            if (longest_path_length[x] == -1) continue;
            for (auto y : adj[x]) {
                if (shortest_path_length[y] != INT_MAX) {
                    shortest_path_length[y] = min(shortest_path_length[y], 1 + shortest_path_length[x]);
                    longest_path_length[y] = max(longest_path_length[y], 1 + longest_path_length[x]);
                    total_paths[y] += total_paths[x];
                }
            }
        }
        return {shortest_path_length[v], longest_path_length[v], total_paths[v]};
    }

    // Tarjan's Algorithm
    void Tarjan_dfs (int i) {
        pre[i] = preorderCounter++;
        low[i] = pre[i];
        stk.push(i);

        for (int j : adj[i]) {
            if (pre[j] == -1) {
                Tarjan_dfs(j);
            }
            
            low[i] = min(low[i], low[j]);
        }

        // Root of SCC
        if (low[i] == pre[i]) {
            numSCCs++;
            while (true) {
                int j = stk.top();
                stk.pop();
                id[j] = numSCCs;
                low[j] = n;

                if (i == j) break;
            }
        }
    }

    vector<int> SCC_decomposition () {
        // Tarjan's Algorithm
        preorderCounter = 0;
        numSCCs = 0;
        pre.assign(n+1, -1);
        id.assign(n+1, 0);
        low.assign(n+1, 0);
        // Clear all stack before any operation
        while (!stk.empty()) {
            stk.pop();
        }

        for (int i = 1; i <= n; i++) {
            if (pre[i] == -1) {
                Tarjan_dfs(i);
            }
        }
        return id;
    }
};

// 2 SAT
int neg(int a, int numTerms) {
    if (a <= numTerms) return a + numTerms;
    return a - numTerms;
}

void add_imp(int a, int b, vector<vector<int>> &adj) {
    adj[a].push_back(b);
}

void add_or(int a, int b, int numTerms, vector<vector<int>> &adj) {
    add_imp(neg(a, numTerms), b, adj);
    add_imp(neg(b, numTerms), a, adj);
}

void addEdge (int a, int u, int b, int v, int numTerms, vector<vector<int>> &adj) {
    if (a == '+' and b == '+') {
        add_or(u, v, numTerms, adj);
    }
    else if (a == '+' and b == '-') {
        add_or(u, neg(v, numTerms), numTerms, adj);
    }
    else if (a == '-' and b == '+') {
        add_or(neg(u, numTerms), v, numTerms, adj);
    }
    else {
        add_or(neg(u, numTerms), neg(v, numTerms), numTerms, adj);
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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(2*m+1);
    for (int i = 0; i < n; i++) {
        char a, b;
        int u, v;
        cin >> a >> u >> b >> v;
        addEdge(a, u, b, v, m, adj); // 2 SAT Edge
    }
    Directed_Graph G(2*m, adj);
    
    vector<int> SCC = G.SCC_decomposition();
    
    bool possible = true;

    for (int i = 1; i <= m; i++) {
        if (SCC[i] == SCC[i+m]) {
            possible = false;
            break;
        }
    }

    if (!possible) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        int ans[m+1];
        memset(ans, 0, sizeof(ans));
        for (int i = 1; i <= m; i++) {
            if (SCC[i+m] > SCC[i]) {
                ans[i] = 1;
            }
            cout << (ans[i] ? '+' : '-') << " ";
        }
        cout << endl;
    }

    // Test the code here

	// int n, m;
    // cin >> n >> m;
    // vector<vector<int>> adj(n+1);
    // for (int i = 0; i < m; i++) {
    //     int u, v;
    //     cin >> u >> v;
    //     adj[u].push_back(v); // Directed Edge
    // }
    // Directed_Graph G(n, adj);

	/*-------------- Code Ends Here ---------------*/

	return 0;
}