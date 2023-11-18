//Author: timg8710

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<ll, int> pii;
 
#define pb push_back
 
#define f first
#define s second

const int maxn = 2e5+9; 
const ll mod = 1e9+7;

struct mint {
	int v; explicit operator int() const { return v; }
 
	mint() { v = 0; } mint(ll _v) { v = int((-mod < _v && _v < mod) ? _v : _v % mod); if (v < 0) v += mod; }
 
	friend bool operator==(const mint& a, const mint& b) { return a.v == b.v; }
	friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
	friend bool operator<(const mint& a, const mint& b) { return a.v < b.v; }
 
	mint& operator+=(const mint& m) { if ((v += m.v) >= mod) v -= mod; return *this; }
	mint& operator-=(const mint& m) { if ((v -= m.v) < 0) v += mod; return *this; }
	mint& operator*=(const mint& m) { v = int((ll) v * m.v % mod); return *this; }
	mint& operator/=(const mint& m) { return (*this) *= inv(m); }
 
    friend mint pow(mint a, long long p) {
		mint ans = 1; for ( ; p; p /= 2, a *= a) if (p & 1) ans *= a; return ans; 
    }
	friend mint inv(const mint& a) { return pow(a, mod - 2); }
 
	mint operator-() const { return mint(-v); }
	mint& operator++() { return *this += 1; }
	mint& operator--() { return *this -= 1; }
 
	friend mint operator+(mint a, const mint& b) { return a += b; }
	friend mint operator-(mint a, const mint& b) { return a -= b; }
	friend mint operator*(mint a, const mint& b) { return a *= b; }
	friend mint operator/(mint a, const mint& b) { return a /= b; }
};

mint factorial[maxn];
void init(int N){
    assert(N <= maxn);
    factorial[0] = 1;
    for(int i = 1; i<maxn; i++) factorial[i] = factorial[i-1] * i;
}

mint choose(int a, int b){ // from a choose b
    if(a < 0 || b < 0 || a < b) return 0;
    mint denom = factorial[a-b] * factorial[b];
    mint numerator = factorial[a];
    return numerator / denom;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    init(maxn);
    cout << choose(1000, 690).v;
    return 0;
}
