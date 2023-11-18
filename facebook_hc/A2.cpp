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
const int maxn = 5e5 + 100;
const int blck = 360;
const ll INF = 1e18; //~9*INF max

void setIO(string s) { // the argument is the filename without the extension
    freopen((s+".in").c_str(),"r",stdin);
    freopen((s+".out").c_str(),"w",stdout);
}

struct HashedString{
    ll moda = 1e9+7, modb = 1e9+9;
    ll base = 9973;

    vector<pii> poly; //a[i] + a[i] * x + a[i] * x^2 + a[i] * x^3 ...
    vector<pair<ll, ll>> pow;

    HashedString(){}
    HashedString(int N, vector<int> str){
        poly.resize(N+1); pow.resize(N+1); pow[0].f = pow[0].s = 1;
        for(int i = 1; i<=N; i++) {
            pow[i].f = (pow[i-1].f * base)%moda;
            pow[i].s = (pow[i-1].s * base)%modb;
        }
        for(int i = N-1; i>=0; i--){
            poly[i].f = (poly[i+1].f*base + str[i])%moda;
            poly[i].s = (poly[i+1].s*base + str[i])%modb;
        }
    }

    //inclusive
    pii get(int l, int r){
        pii ret;
        ret.f = (poly[l].f - (poly[r+1].f*(pow[r-l+1].f)%moda) + moda) % moda;
        ret.s = (poly[l].s - (poly[r+1].s*(pow[r-l+1].s)%modb) + modb) % modb;
        return ret;
    }
};

void run_testcase(){
    int N, K; cin >> N >> K;
    
    vector<int> A(N), B(N);
    for(int i = 0; i<N; i++) cin >> A[i];
    for(int i = 0; i<N; i++) cin >> B[i];
    int ok = 1;
    int same = A == B;

    if(K == 0){
      cout << (same ? "YES" : "NO") << '\n'; return;
    }

    if(N == 2){
      if(same){
        if(A[0] != A[1] && K%2){
          ok = 0;
        }
      }else{
        if(K%2 == 0){
          ok = 0;
        }
      }
      cout << (ok ? "YES" : "NO") << '\n'; return;
    }

    HashedString Ah(N, A), Bh(N, B);

    auto equal = [&] (bool first, bool sec, int a, int b, int c, int d)
    {
      //is A?
        if(b - a != d - c) return false;
        pii fi = (first ? Ah.get(a, b) : Bh.get(a, b));
        pii se = (sec ? Ah.get(c, d) : Bh.get(c, d));

        if(fi != se) return false;
        
        for(int i = 0; i<=b-a; i++){
          int v1 = first ? A[a + i] : B[a + i];
          int v2 = sec ? A[c + i] : B[c + i];
          if(v1 != v2) return false;
        }

        return true;
    };

    int occ = same;
    for(int i = 0; i<N-1 && !occ; i++){
      //move [0, i] 
      bool fi = equal(true, false, 0, i, N-1-i, N-1);
      bool se = equal(true, false, i+1, N-1, 0, N-1-i -1);

      occ = occ || (fi && se);
    }
    // cout << occ << endl;
    if(!occ){
      cout << "NO\n"; return;
    }

    if(K == 1 && same){
      //segment repetition A
      int rep = 0;
      for(int i = 2; i<N && !rep; i++){
        if(N%i != 0) continue;

        for(int j = i; j < N; j += i){
          if(equal(true, true, 0, i-1, j, j + i - 1)){
            rep = 1; break;
          }
        }
      }
      if(!rep){
        cout << "NO\n"; return;
      }
    }

    cout << "YES\n"; return;
}

int main(){
    setIO("A2");
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