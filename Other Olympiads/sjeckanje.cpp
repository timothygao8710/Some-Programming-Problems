using namespace std;

typedef long long ll;

struct node
{
    ll borders[2] = {}; // border values of segment
    ll dp[2][2] = {};   // take/not-take left and right border values

    node() {}
    node(ll v)
    {
        borders[0] = borders[1] = v;
        dp[0][1] = dp[1][0] = dp[0][0] = 0;
        dp[1][1] = abs(v);
    }
    // assume current is left
    node comb(node &other)
    {
        node ret;

        ret.borders[0] = borders[0];
        ret.borders[1] = other.borders[1];

        // [     ][     ]
        // l     mo     r
        // m and o same -> taken segments are combined
        for (int l = 0; l < 2; l++)
        {
            for (int m = 0; m < 2; m++)
            {
                for (int o = 0; o < 2; o++)
                {
                    for (int r = 0; r < 2; r++)
                    {
                        if (m && o)
                        {
                            // it's never optimal to take two opposite sign values
                            if ((borders[1] < 0) == (other.borders[0] < 0))
                            {
                                ret.dp[l][r] = max(ret.dp[l][r], dp[l][m] + other.dp[o][r]);
                            }
                        }
                        else
                        {
                            ret.dp[l][r] = max(ret.dp[l][r], dp[l][m] + other.dp[o][r]);
                        }
                    }
                }
            }
        }
        return ret;
    }

    // modify a single-element node segment by +v
    void upd(ll v)
    {
        borders[0] += v;
        borders[1] += v;
        dp[1][1] = abs(borders[0]);
    }
};

struct segtree
{
    node val;
    int gL, gR, mid;
    segtree *left, *right;

    segtree(int l, int r, vector<node> &nums)
    {
        gL = l;
        gR = r;
        mid = (gL + gR) / 2;
        if (l == r)
        {
            val = nums[l];
        }
        else
        {

            left = new segtree(l, mid, nums), right = new segtree(mid + 1, r, nums);
            val = left->val.comb(right->val);
        }
    }

    void update(int idx, ll updval)
    {
        if (gL == gR)
        {
            val.upd(updval);
        }
        else
        {
            if (idx <= (gL + gR) / 2)
            {
                left->update(idx, updval);
            }
            else
            {
                right->update(idx, updval);
            }
            val = left->val.comb(right->val);
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, Q;
    cin >> N >> Q;
    vector<node> D(N - 1);
    int a;
    cin >> a;
    // compute difference array
    for (int i = 0; i < N - 1; i++)
    {
        int b;
        cin >> b;
        D[i] = node(b - a);
        swap(a, b);
    }

    // a_(i + 1) - a(i)
    segtree sgt(0, N - 2, D);
    for (int q = 0; q < Q; q++)
    {
        int l, r;
        ll x;
        cin >> l >> r >> x;
        l--, r--;
        if (l - 1 >= 0)
        {
            sgt.update(l - 1, x);
        }
        if (r < N - 1)
        {
            sgt.update(r, -x);
        }
        cout << sgt.val.dp[1][1] << '\n';
    }
}