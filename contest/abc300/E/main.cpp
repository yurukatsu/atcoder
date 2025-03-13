#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

// 簡易な高速冪乗 (mod MOD)
ll modexp(ll base, ll exp, ll mod = MOD)
{
    ll res = 1 % mod;
    base %= mod;
    while (exp > 0)
    {
        if (exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;
    // N == 1 のときは初期状態すでに 1 なので答えは 1.
    if (N == 1)
    {
        cout << 1 << "\n";
        return 0;
    }

    // N を 2,3,5 で素因数分解
    ll temp = N;
    int exp2 = 0, exp3 = 0, exp5 = 0;
    while (temp % 2 == 0)
    {
        exp2++;
        temp /= 2;
    }
    while (temp % 3 == 0)
    {
        exp3++;
        temp /= 3;
    }
    while (temp % 5 == 0)
    {
        exp5++;
        temp /= 5;
    }
    // もし 2,3,5 以外の素因数を含むならば，N に一致させることはできない
    if (temp != 1)
    {
        cout << 0 << "\n";
        return 0;
    }
    // ターゲットは N = 2^(exp2) * 3^(exp3) * 5^(exp5)

    // DPの状態は (x,y,z) で表し、現在の値は 2^x * 3^y * 5^z となる．
    // 遷移は必ず指数が増加するため，x, y, z の上限はそれぞれ
    // 「2^x <= N」などの最大の x を取ればよい．
    int bound2 = 0, bound3 = 0, bound5 = 0;
    {
        ll prod = 1;
        while (prod <= N)
        {
            prod *= 2;
            bound2++;
        }
        bound2--; // 2^bound2 <= N となる最大の bound2
    }
    {
        ll prod = 1;
        while (prod <= N)
        {
            prod *= 3;
            bound3++;
        }
        bound3--;
    }
    {
        ll prod = 1;
        while (prod <= N)
        {
            prod *= 5;
            bound5++;
        }
        bound5--;
    }

    // 各種指数の累乗を前計算
    vector<ll> pow2(bound2 + 1), pow3(bound3 + 1), pow5(bound5 + 1);
    pow2[0] = 1;
    for (int i = 1; i <= bound2; i++)
    {
        pow2[i] = pow2[i - 1] * 2;
    }
    pow3[0] = 1;
    for (int i = 1; i <= bound3; i++)
    {
        pow3[i] = pow3[i - 1] * 3;
    }
    pow5[0] = 1;
    for (int i = 1; i <= bound5; i++)
    {
        pow5[i] = pow5[i - 1] * 5;
    }

    // dp[x][y][z] = 有効な操作で状態 (x,y,z) に到達する確率（mod MOD）
    vector<vector<vector<ll>>> dp(bound2 + 1, vector<vector<ll>>(bound3 + 1, vector<ll>(bound5 + 1, 0)));
    dp[0][0][0] = 1;

    // 有効な操作は 2,3,4,5,6 であり，条件付き確率は各 1/5。
    ll inv5 = modexp(5, MOD - 2);

    // 各操作の (dx, dy, dz) と掛ける乗算因子
    vector<tuple<int, int, int, ll>> moves = {
        {1, 0, 0, 2}, // 出目 2
        {0, 1, 0, 3}, // 出目 3
        {2, 0, 0, 4}, // 出目 4
        {0, 0, 1, 5}, // 出目 5
        {1, 1, 0, 6}  // 出目 6
    };

    ll ans = 0;
    // DP：現在の状態 (x,y,z) から，状態が N 未満である間だけ各操作を試す
    // 状態は必ず指数が増加するので，3重ループで順次更新可能
    for (int x = 0; x <= bound2; x++)
    {
        for (int y = 0; y <= bound3; y++)
        {
            for (int z = 0; z <= bound5; z++)
            {
                if (dp[x][y][z] == 0)
                    continue;
                ll cur = pow2[x] * pow3[y] * pow5[z]; // 現在の値
                if (cur >= N)
                    continue; // 既に N 以上なら操作はしない
                for (auto &mv : moves)
                {
                    int dx, dy, dz;
                    ll factor;
                    tie(dx, dy, dz, factor) = mv;
                    int nx = x + dx, ny = y + dy, nz = z + dz;
                    if (nx > bound2 || ny > bound3 || nz > bound5)
                        continue;
                    ll nprod = cur * factor; // 新しい値
                    if (nprod < N)
                    {
                        dp[nx][ny][nz] = (dp[nx][ny][nz] + dp[x][y][z] * inv5) % MOD;
                    }
                    else if (nprod == N)
                    {
                        ans = (ans + dp[x][y][z] * inv5) % MOD;
                    }
                    // nprod > N の場合は失敗とみなす（寄与しない）
                }
            }
        }
    }

    cout << ans % MOD << "\n";
    return 0;
}
