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

const int maxn = 41;
int N;
// bounding triangle : number of steps
int dp[maxn][maxn][maxn][maxn];
pii points[maxn];

bool ccw(int a, int b, int c){
    return (points[c].s-points[a].s) * (points[b].f-points[a].f) > (points[b].s-points[a].f) * (points[c].f-points[a].f);
}

// area of triangle defined by (a, b, c)
ll area(int a, int b, int c){
    ll S = (a + b + c)/2;
    return S * (S - a) * (S - b) * (S - c);
}

// check if line (a, b) intersects line (c, d)
bool Intersects(int a, int b, int c, int d){
    return ccw(a,c,d) != ccw(b,c,d) && ccw(a,b,c) != ccw(a,b,d);
}

// check if point d can be added to bounding triangle of a, b, c
int isInside(int a, int b, int c, int d){
    // first, check for intersection
    if(Intersects(a, b, c, d) || Intersects(a, c, ))
}

int recurse(int a, int b, int c, int taken = 0){
    if(taken == N) return 1;
    if(dp[a][b][c][taken] != -1) return dp[a][b][c][taken];

    int inside = 0;



}

void run_testcase(){
    cin >> N;
    for(int i = 0; i<N; i++){
        cin >> points[i].f >> points[i].s;
    }

    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            for(int k = 0; k < N; k++){
                for(int o = 0; o < N; o++){
                    dp[i][j][k][o] = -1;
                }
            }
        }
    }

    ll ret = 0;

    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            for(int k = 0; k < N; k++){
                ret = (ret + recurse(i, j, k))%mod;
            }
        }
    }

    cout << ret;

    cout << '\n';
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int T = 1;
    // cin >> T;
    while(T--){
        run_testcase();
    }
    return 0;
}