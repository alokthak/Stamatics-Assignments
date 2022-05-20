#include<bits/stdc++.h>
using namespace std;

// Vertices are numbered from 0 to n-1.
class Undirected_Graph {

private:
	int n, dfs_timer, component;
	bool Cycle; // tells the presence of a cycle in the graph.
	vector<vector<int>> adj;  // adjacency list.
	vector<int> tin;  // stores the 'time in' in a dfs call.
	vector<int> tout;  // stores the 'time out' in a dfs call.
	vector<int> low;  // low(v) stores the tin of the highest ancestor of v to which there is a back edge from the subtree rooted at v.
	vector<bool> vis;  // stores the visited status of each vertex.
	vector<int> distance;  // stores the shortest distance from the given source vertex(s) in a bfs call.
	vector<int> componentID;  // maps each vertex to its corresponding component id.
	map<pair<int, int>, int> IS_BRIDGE;  // tells whether an edge is a bridge or not.
	vector<pair<int, int>> bridges;  // not asked
	set<pair<int, int>> back_edges;  // not asked
	
public:
	Undirected_Graph (int nodes, vector<vector<int>>& adjacencyList) {
		n = nodes;
		adj = adjacencyList;
		tin.resize(n, -1);
		tout.resize(n, -1);
		low.resize(n, -1);
		vis.resize(n, false);
		distance.resize(n, -1);
		componentID.resize(n, -1);
		dfs_timer = 0;
		Cycle = false;
	}

	void dfs(int v) {
		dfs_timer = 0;
	    vis.assign(n, false);
	    tin.assign(n, -1);
	    low.assign(n, -1);
	    back_edges.clear();
	    helper_dfs(v);
	}

	void helper_dfs(int v, int p = -1) {
		tin[v] = low[v] = dfs_timer++;
	    vis[v] = true;
	    componentID[v] = component;
	    for (int to : adj[v]) {
	        if (to == p) continue;
	        if (vis[to]) {
	            low[v] = min(low[v], tin[to]);
	            Cycle = true;
	            back_edges.insert({v, to});
	        } else {
	            helper_dfs(to, v);
	            low[v] = min(low[v], low[to]);
	            if (low[to] > tin[v]) {
	                IS_BRIDGE[{v, to}]++;
	                IS_BRIDGE[{to, v}]++;
	                bridges.push_back({v, to});
	            }
	        }
	    }
	    tout[v] = dfs_timer++;
	}

	bool isTreeEdge (int u, int v) {
		if (back_edges.find({u, v}) != back_edges.end() or back_edges.find({v, u}) != back_edges.end()) return false; // Back Edge
		return true;  // Tree Edge
	}

	vector<int> bfs (int s) {
		vis.assign(n, false);
		distance.assign(n, -1);
		queue<int> q;
		q.push(s);
		distance[s] = 0;
		vis[s] = 1;
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			for (auto nbr : adj[node]) {
				if (!vis[nbr]) {
					vis[nbr] = 1;
					distance[nbr] = distance[node] + 1;
					q.push(nbr);
				}
			}
		}
		return distance;
	}

	vector<int> connectedComponents () {
		dfs_timer = 0;
	    vis.assign(n, false);
	    tin.assign(n, -1);
	    low.assign(n, -1);
	    componentID.assign(n, -1);
		component = 1;
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				dfs(i);
				component++;
			}
		}
		return componentID;
	}

	bool hasCycle () {
		dfs_timer = 0;
	    vis.assign(n, false);
	    tin.assign(n, -1);
	    low.assign(n, -1);
		for (int i = 0; i < n; i++) {
			if (!vis[i]) {
				dfs(i);
				if (Cycle) return true;
			}
		}
		return false;
	}

	vector<pair<int, int>> find_bridges() {
		bridges.clear();
	    dfs_timer = 0;
	    vis.assign(n, false);
	    tin.assign(n, -1);
	    low.assign(n, -1);
	    for (int i = 0; i < n; i++) {
	        if (!vis[i])
	            dfs(i);
	    }
	    return bridges;
	}

	// IS_BRIDGE[{u, v}] is the marker to denote if the edge is deleted(bridge) or not.

};

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
	vector<vector<int>> adj(n);
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	Undirected_Graph G(n, adj);
	// Test the undirected graph here ...
	/*
	vector<pair<int, int>> bridges = G.find_bridges();
	cout << "Bridges:\n";
	for (auto bridge : bridges) {
		cout << "(" << bridge.first << ", " << bridge.second << ") ";
	}
	cout << endl;
	cout << "Cycle --> ";
	cout << ((G.hasCycle()) ? "Yes" : "No") << endl;
	vector<int> components = G.connectedComponents();
	cout << "Connected Components:\n";
	for (int i = 0; i < n; i++) {
		cout << components[i] << " ";
	}
	cout << endl;
	vector<int> distance = G.bfs(16);
	cout << "Distance:\n";
	for (int i = 0; i < n; i++) {
		cout << distance[i] << " ";
	}
	cout << endl;
	G.dfs(0);
	cout << ((G.isTreeEdge(6, 5)) ? "TreeEdge" : "BackEdge") << endl;
	*/

	/*-------------- Code Ends Here ---------------*/

	return 0;
}