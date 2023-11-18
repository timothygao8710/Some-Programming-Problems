//@timothyg

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define vsz(a) (int)a.size()
#define f first
#define s second

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

struct Interval_Set
{
    // disjoint intervals [L, R] -> [L, intervals[R]]
    map<int, int> intervals; 

    Interval_Set(){}

    void insert(int l, int r){
        if(isDisjoint(l-1, r+1)) {
            intervals[l] = r; return;
        }

        if(getLeft(l).s >= l-1) {
            l = min(l, getLeft(l).f);
            r = max(r, getLeft(l).s);
        }

        pii right = getRight(l);
        while(right.f <= r+1){
            r = max(r, right.s);
            intervals.erase(right.f);

            if(intervals.lower_bound(l) == intervals.end()) break;
            right = *(intervals.lower_bound(l));
        }

        intervals[l] = r;
    }

    void insert_no_merge_adjacent(int l, int r){
        if(isDisjoint(l, r)) {
            intervals[l] = r; return;
        }

        if(getLeft(l).s >= l) {
            l = min(l, getLeft(l).f);
            r = max(r, getLeft(l).s);
        }

        pii right = getRight(l);
        while(right.f <= r){
            r = max(r, right.s);
            intervals.erase(right.f);

            if(intervals.lower_bound(l) == intervals.end()) break;
            right = *(intervals.lower_bound(l));
        }

        intervals[l] = r;
    }

    // remove elements that exist in [l, l+1, ... , r-1, r]
    void erase(int l, int r){
        if(isDisjoint(l, r)) return;
        pii left = getLeft(r);

        while(overlaps(l, r, left.f, left.s)){
            intervals.erase(left.f);
            if(left.f < l) intervals[left.f] = l-1;
            if(r < left.s) intervals[r+1] = left.s;
            if(intervals.empty()) break;
            left = getLeft(r);
        }
    }

    // there is an interval that fully contains [l, r]
    bool contains(int l, int r){return !intervals.empty() && getLeft(l).f <= l && r <= getLeft(l).s;}
    bool isDisjoint(int l, int r){return intervals.empty() || min_interval().f > r || (getLeft(l).s < l && getLeft(l) == getLeft(r));}
    bool overlaps(int a, int b, int c, int d){return (a <= c && c <= b) || (a <= d && d <= b) || (c <= a && a <= d);}

    // maximum L such that L <= v (use lower_bound for L < v)
    // if doesn't exist, return minimum left boundary
    pii min_interval(){assert(!intervals.empty()); return *intervals.begin();}
    pii getLeft(int v){if (min_interval().f > v) return min_interval(); return *(--intervals.upper_bound(v));}

    // minimum L such that v <= L (use upper_bound for v < L)
    // if doesn't exist, error
    pii getRight(int v){assert(intervals.lower_bound(v) != intervals.end()); return *(intervals.lower_bound(v));}
};

void run_testcase(){
    int N; cin >> N;
    Interval_Set inter;
    for(int i = 0; i<N; i++){
        int a, b; cin >> a >> b;
        inter.insert(a, b);
    }

    dbg(inter.intervals);
    for(auto i : inter.intervals){
        cout << i.f << " " << i.s << endl;
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