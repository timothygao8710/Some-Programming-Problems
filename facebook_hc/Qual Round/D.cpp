//@timothyg

#include <bits/stdc++.h>
using namespace std;
 
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
  return os << '{' << p.first << ", " << p.second << '}';
}

template <class T, class = decay_t<decltype(*begin(declval<T>()))>,
          class = enable_if_t<!is_same<T, string>::value>>
ostream &operator<<(ostream &os, const T &c) {
  os << '[';
  for (auto it = c.begin(); it != c.end(); ++it)
    os << &", "[2 * (it == c.begin())] << *it;
  return os << ']';
}
#define _NTH_ARG(_1, _2, _3, _4, _5, _6, N, ...) N
#define _FE_0(_CALL, ...)
#define _FE_1(_CALL, x) _CALL(x)
#define _FE_2(_CALL, x, ...) _CALL(x) _FE_1(_CALL, __VA_ARGS__)
#define _FE_3(_CALL, x, ...) _CALL(x) _FE_2(_CALL, __VA_ARGS__)
#define _FE_4(_CALL, x, ...) _CALL(x) _FE_3(_CALL, __VA_ARGS__)
#define _FE_5(_CALL, x, ...) _CALL(x) _FE_4(_CALL, __VA_ARGS__)
#define FOR_EACH_MACRO(MACRO, ...)                                             \
  _NTH_ARG(dummy, ##__VA_ARGS__, _FE_5, _FE_4, _FE_3, _FE_2, _FE_1, _FE_0)     \
  (MACRO, ##__VA_ARGS__)
#define DBG_OUT(x) #x " = " << x << "; "
#define dbg(...)                                                              \
  cerr << "Line " << __LINE__ << ": " FOR_EACH_MACRO(DBG_OUT, __VA_ARGS__) << '\n'


typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define vsz(a) (int)a.size()
#define f first
#define s second

const ll mod = 1e9 + 7;
// const ll mod = 998244353;
const int maxn = 2e5 + 100;
const int blck = 360;
const ll INF = 1e18; //~9*INF max

void setIO(string s) { // the argument is the filename without the extension
    freopen((s+".in").c_str(),"r",stdin);
    freopen((s+".out").c_str(),"w",stdout);
}

int deg[maxn];
vector<array<int, 3>> edges;
vector<pii> adj[maxn], super[maxn];
map<pii, ll> twoedge;
map<pii, int> direct;

void run_testcase(){
    int N, M, Q; cin >> N >> M >> Q;

    twoedge.clear();
    direct.clear();
    edges.clear();
    for(int i = 0; i<N; i++){
        super[i].clear();
        adj[i].clear();
        deg[i] = 0;
    }

    for(int i = 0; i<M; i++){
        int u, v, c; cin >> u >> v >> c;
        --u, --v;
        edges.pb({u, v, c});

        adj[u].pb(pii(v, c));
        adj[v].pb(pii(u, c));
        direct[pii(u, v)] = c;
        direct[pii(v, u)] = c;
        deg[u]++, deg[v]++;
    }

    for(int i = 0; i<N; i++){
        int sz = vsz(adj[i]);
        if(sz < blck){
            for(int j = 0; j<sz; j++){
                for(int k = j+1; k<sz; k++){
                    int u = adj[i][j].f, v = adj[i][k].f;
                    if(u > v) swap(u, v);
                    twoedge[pii(u, v)] += min(adj[i][j].s, adj[i][k].s);
                }
            }
        }
    }

    for(auto i : edges){
        if(deg[i[0]] >= blck){
            super[i[1]].pb(pii(i[0], i[2]));
        }
        if(deg[i[1]] >= blck){
            super[i[0]].pb(pii(i[1], i[2]));
        }
    }
    //at most 2*M/blck such nodes

    for(int q = 0; q < Q; q++){
        int u, v; cin >> u >> v;
        --u, --v;

        ll ret = 2 * direct[pii(u, v)];
        ret += twoedge[pii(min(u, v), max(u, v))];

        if(vsz(super[u]) > vsz(super[v])) swap(u, v);
        for(auto n : super[u]){
            if(direct.count(pii(n.f, v))){
                ret += min(n.s, direct[pii(n.f, v)]);
            }
        }

        cout << ret << " ";
    }

    cout << '\n';
}

int main(){
    setIO("D");
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int T = 1;
    cin >> T;
    for(int t = 1; t<=T; t++){
        // clock_t z = clock();

        cout << "Case #" << t << ": ";
		run_testcase();

		// cout << "Total Time: " << ((double)(clock() - z) / CLOCKS_PER_SEC);
    }
    return 0;
}