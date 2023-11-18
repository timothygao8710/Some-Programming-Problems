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

/*
extended euclid: log(max(a, b))
- find (x, y) such that ax + by = 1 <==> gcd(a, b) = 1
- ax mod(y) = 1
WARNING: Overflow
*/ 
pii exd_euclid(int a, int b){
    assert(gcd(a, b) == 1);

    int A = 1, B = 0, C = 0, D = 1;

    // for a' < b', gcd(a', b') = gcd(A*a + B*b, C*a + D*b)
    while(a){
        int quotient = b / a;
        C -= A * quotient;
        D -= B * quotient;
        b -= a * quotient;

        swap(a, b);
        swap(A, C);
        swap(B, D);
    }
    assert(b == 1);
    return pii(C, D);
}

void run_testcase(){
    cout << exd_euclid(5, 7) << endl;
    cout << (exd_euclid(55555, 777777777).f * 55555 + exd_euclid(55555, 777777777).s * 777777777) << endl;
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