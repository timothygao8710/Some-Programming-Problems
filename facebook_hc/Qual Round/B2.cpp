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

int rDir[8] = {1, -1, 0, 0, -1, 1, -1, 1};
int cDir[8] = {0, 0, 1, -1, 1, 1, -1, -1};

void run_testcase(){
    //think about which cells are bad, rather than constructively drawing a solution
    int N, M; cin >> N >> M;
    vector<vector<int>> grid(N, vector<int>(M)), bad(N, vector<int>(M));
    for(int i = 0; i<N; i++){
        string str; cin >> str;
        for(int j = 0; j<M; j++){
            if(str[j] == '^'){
                grid[i][j] = 1;
            }else if(str[j] == '#'){
                grid[i][j] = 2;
                bad[i][j] = 1;
            }
        }
    }

    auto extend = [&] (int y, int x)
    {
        queue<pii> bfs;
        bfs.push(pii(y, x));
        while(!bfs.empty()){
            pii cur = bfs.front(); bfs.pop();
            if(bad[cur.f][cur.s]) continue;
            int ok = 0;
            pii nxt(-1, -1);
            for(int n = 0; n < 4; n++){
                int dy = cur.f + rDir[n];
                int dx = cur.s + cDir[n];

                if(dy >= N || dx >= M || dy < 0 || dx < 0 ||
                bad[dy][dx]) continue;
                nxt = pii(dy, dx);
                ok += 1;
            }
            if(ok > 1) continue;
            if(nxt.f != -1){
                bfs.push(nxt);
            }
            bad[cur.f][cur.s] = 1;
        }
    };

    int ok = 1;

    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            if(bad[i][j]) continue;
            extend(i, j);
        }
    }

    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            if(bad[i][j] && grid[i][j] == 1){
                ok = 0;
            }
            if(!bad[i][j]){
                grid[i][j] = 1;
            }
        }
    }

    if(!ok){
        cout << "Impossible\n";
    }else{
        cout << "Possible\n";
        for(int i = 0; i<N; i++){
            for(int j = 0; j<M; j++){
                if(grid[i][j] == 0){
                    cout << ".";
                }else if(grid[i][j] == 1){
                    cout << "^";
                }else{
                    cout << "#";
                }
            }
            cout << '\n';
        }
    }
}

int main(){
    setIO("B2");
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