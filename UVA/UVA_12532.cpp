/*
	Author: Ritik Patel
*/
 
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& STL DEBUGGER &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
// #define _GLIBCXX_DEBUG       // Iterator safety; out-of-bounds access for Containers, etc.
// #pragma GCC optimize "trapv" // abort() on (signed) integer overflow.
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& LIBRARIES &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
#include <bits/stdc++.h>
using namespace std;
 
/*#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; 
*/
//find_by_order()->returns an iterator to the k-th largest element(0-based indexing)
//order_of_key()->Number of items that are strictly smaller than our item
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& DEFINES &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
#define int long long int
// #define ll long long int
#define all(i) i.begin(), i.end()
#define sz(a) (int)a.size()
 
// #define ld long double
// const ld PI  = 3.141592;
const int dx4[4] = {0, 1, 0, -1};
const int dy4[4] = {-1, 0, 1, 0};
const int dx8[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy8[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& DEBUG &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
#define XOX
vector<string> vec_splitter(string s) {
    for(char& c: s) c = c == ','?  ' ': c;
    stringstream ss; ss << s;
    vector<string> res;
    for(string z; ss >> z; res.push_back(z));
    return res;
}
 
void debug_out(vector<string> __attribute__ ((unused)) args, __attribute__ ((unused)) int idx) { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, Head H, Tail... T) {
    if(idx > 0) cerr << ", ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, T...);
}
 
#ifdef XOX
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __VA_ARGS__)
#else
#define debug(...) 42
#endif
 
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& CODE &&&&&&&&&&&&&&&&&&&&&&&&&&&

const int MAXN = 1e5 + 5;
vector<int> a(MAXN);

struct node {
    int p, n, z;
    node() {};
    node(int p, int n, int z) : p(p), n(n), z(z) {};
};
vector<node> tree(4*MAXN + 100);

inline int lc(int id) {
    return id * 2;
}

inline int rc(int id) {
    return id * 2 + 1;
}

node merge(const node &a, const node &b) {
    int p = a.p + b.p;
    int z = a.z + b.z;
    int n = a.n + b.n;
    return node(p, n, z);
}

void build(int id, int tl, int tr) {
    if(tl == tr) {
        int p = 0, n = 0, z = 0;
        if(a[tl] > 0) ++p;
        else if(a[tl] == 0) ++z;
        else ++n;
        tree[id] = node(p, n, z);
        // debug(id, tree[id].p, tree[id].n, tree[id].z);
        return;
    }
    int mid = (tl + tr) >> 1;
    build(lc(id), tl, mid);
    build(rc(id), mid + 1, tr);
    
    tree[id] = merge(tree[lc(id)], tree[rc(id)]);
    // debug(id, tl, tr, tree[id].p, tree[id].n, tree[id].z);
}

void update(int id, int tl, int tr, int pos, int val) {
    if(tl == tr) {
        int p = 0, n = 0, z = 0;
        a[tl] = val;
        if(a[tl] > 0) ++p;
        else if(a[tl] == 0) ++z;
        else ++n;
        tree[id] = node(p, n, z);
        return;
    }
    int mid = (tl + tr) >> 1;
    if(pos <= mid)
        update(lc(id), tl, mid, pos, val);
    else 
        update(rc(id), mid + 1, tr, pos, val);

    tree[id] = merge(tree[lc(id)], tree[rc(id)]);
}

node query(int id, int tl, int tr, int l, int r) {
    if(l > tr or r < tl) return node(0, 0, 0);
    if(l <= tl and r >= tr) return tree[id];
    //else there is merge of left nd right subtree.
    int mid = (tl + tr) >> 1;
    node lq = query(lc(id), tl, mid, l, r);
    node rq = query(rc(id), mid + 1, tr, l, r);
    return merge(lq, rq);
}

void solve() {
    int n, k; 
    while(cin >> n >> k) {
        for(int i = 1; i <= n; ++i)
            cin >> a[i];
        
        build(1, 1, n);

        for(int i = 1; i <= k; ++i) {
            char x; cin >> x;
            if(x == 'C') {
                int id, val;
                cin >> id >> val;
                update(1, 1, n, id, val); 
            } else {
                int l, r;
                cin >> l >> r;
                node ans = query(1, 1, n, l, r);
                // debug(ans.n, ans.p, ans.z, l, r);
                if(ans.z) {
                    cout << 0;
                } else if(ans.n%2) {
                    cout << "-";
                } else {
                    cout << "+";
                }
            }
        }
        cout << '\n';
    }
}


int32_t main(){
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout); 
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    int T = 1; 
    // cin >> T;
    for(int i = 1; i <= T; ++i){
        // cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
 
/*
Sample inp
*/
