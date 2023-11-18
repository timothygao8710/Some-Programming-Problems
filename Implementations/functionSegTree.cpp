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
const ll INF = 1e18; //~9*INF max

template <ll (*comb)(ll, ll)>
struct segtree
{
    ll val, none;
    int l, r, mid;
    segtree<comb> *left = 0, *right = 0;

    segtree(int gL, int gR, vector<ll>& nums, ll non){ 
        l = gL, r = gR, mid = (l+r)/2, none = non;
        if (l == r){
            val = nums[l];
        }else{
            left = new segtree<comb>(l, mid, nums, none), right = new segtree<comb>(mid + 1, r, nums, none);
            val = comb(left->val, right->val);
        }
    }

    ll query(int ql, int qr){
        if (ql > r || qr < l) return none;
        if (ql == l && qr == r) return val;
        ll a = left->query(ql, min(qr, mid)), b = right->query(max(ql, mid + 1), qr);
        return comb(a, b);
    }

    void update(int idx, ll set){
        if (l == r){
            val = set;
        }else{
            if (idx <= (l + r) / 2) left->update(idx, set);
            else { right->update(idx, set); }
            val = comb(left->val, right->val);
        }
   }
};

// segtree<add_comb> sgt(0, N-1, nums, (ll)(0));
ll add_comb(ll a, ll b){
    return a + b;
}

void run_testcase(){
    int N, Q; cin >> N >> Q;
    vector<ll> nums(N); for(int i = 0; i<N; i++) cin >> nums[i];
    segtree<add_comb> sgt(0, N-1, nums, (ll)(0));
    while(Q--){
        int t, a, b; cin >> t >> a >> b;
        if ( t == 1){
            sgt.update(a-1, (ll)b);
        }else{
            cout << (sgt.query(a-1, b-1)) << '\n';
        }
    }
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