#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
typedef long long ll;

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

int main() {
	{
		int a = 1e8, b = 1e8, c = 1e8;
		cout << (long long)a * b % mod * c % mod << "\n";  // 49000000
	}
	{
		mint a = 1e8, b = 1e8;
		ll c = 1e8;
		// cout << a * b * c << "\n";  // Errors- we have to cast this an an int
		cout << (int)(a * b * c) % mod << "\n";  // 49000000
	}
}