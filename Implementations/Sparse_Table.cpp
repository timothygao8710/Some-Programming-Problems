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

template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable {
	int n;
	vector<vector<T>> mat;
	F func;
	SparseTable() {} // For vector.
	SparseTable(const vector<T>& a, const F& f) : func(f) {
		n = a.size();
		if (n == 0) return;
		int maxLog = 32 - __builtin_clz(n);
		mat.resize(maxLog);
		mat[0] = a;
		for (int j = 1; j < maxLog; ++j) {
			mat[j].resize(n - (1 << j) + 1);
			for (int i = 0; i <= n - (1 << j); ++i) {
				mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
			}
		}
	}
	T query(int from, int to) const {
		assert(0 <= from && from <= to && to <= n - 1);
		int lg = 31 - __builtin_clz(to - from + 1);
		return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
    vector<int> test;
    test.pb(1);
    test.pb(2);
    test.pb(3);
    test.pb(4);
	SparseTable<int> minST(test, [&](int i, int j) { return min(i, j); });
	
    cout << minST.query(0, 2) << endl;
    cout << minST.query(1, 3) << endl;
    cout << minST.query(2, 3) << endl;
}