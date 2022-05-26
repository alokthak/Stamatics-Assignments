#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define endl '\n'
#define all(v) v.begin(), v.end()
#define ff first
#define ss second

const int INF = 2e9;
int heap_size = 0;
int length = 0;

void Max_Heapify (vector<int> &v, int i) {
    int l = i<<1;
    int r = l+1;
    int largest; // stores index of the element with maximum value.
    if (l <= heap_size and v[l] > v[i]) {
        largest = l;
    }
    else largest = i;
    if (r <= heap_size and v[r] > v[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(v[i], v[largest]);
        Max_Heapify(v, largest);
    }
}

void Build_Max_Heap (vector<int> &v) {
    heap_size = length;
    for (int i = (length >> 1); i>= 1; i--) {
        Max_Heapify(v, i);
    }
}

void HeapSort (vector<int> &v) {
    Build_Max_Heap(v);
    for (int i = length; i >= 2; i--) {
        swap(v[1], v[i]);
        heap_size = heap_size - 1;
        Max_Heapify(v, 1);
    }
}

int Heap_Extract_Max (vector<int> &v) {
    if (heap_size < 1) {
        cout << "heap underflow";
    }
    int maxi = v[1];
    v[1] = v[heap_size];
    heap_size = heap_size-1;
    v.pop_back();
    length = heap_size;
    Max_Heapify(v, 1);
    return maxi;
}

void Heap_Increase_Key (vector<int> &v, int i, int x) {
    if (x < v[i]) {
        cout << "new key is smaller than current key";
    }
    v[i] = x;
    while (i > 1 and v[i>>1] < v[i]) {
        swap(v[i], v[i>>1]);
        i >>= 1;
    }
}

void Max_Heap_Insert (vector<int> &v, int x) {
    heap_size = heap_size + 1;
    if (heap_size <= length)
        v[heap_size] = -INF;
    else {
        v.push_back(-INF);
        length = length + 1;
    }
    Heap_Increase_Key(v, heap_size, x);
}

void solve() {
    int n; cin >> n;
    vector<int> v(n+1);
    length = n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    
    /*  Call your functions here  */
    // Build_Max_Heap(v);
    // Heap_Extract_Max(v);
    // Max_Heap_Insert(v, 16);
    // Max_Heap_Insert(v, 11);
    // Heap_Extract_Max(v);

    for (int i = 1; i <= length; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
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
    for(int test = 1; test <= t; test++){
        // cout << "Case #" << test << ": ";
        solve();
    }
    
    /*-------------- Code Ends Here ---------------*/ 
    return 0;
}
