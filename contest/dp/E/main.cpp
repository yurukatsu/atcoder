#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
#define INF (1LL << 60)
using namespace std;

int main()
{
    int N;
    ll W;
    cin >> N >> W;

    vector<ll> w(N), v(N);
    for (int i = 0; i < N; i++)
    {
        cin >> w[i] >> v[i];
    }

    ll max_value = 0;
    for (int i = 0; i < N; i++)
    {
        max_value += v[i];
    }

    vector<vector<ll>> dp(N + 1, vector<ll>(max_value + 1, INF));
    dp[0][0] = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= max_value; j++)
        {
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);

            if (j >= v[i])
            {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - v[i]] + w[i]);
            }
        }
    }

    ll answer = 0;
    for (ll j = 0; j <= max_value; j++)
    {
        if (dp[N][j] <= W)
        {
            answer = j;
        }
    }

    cout << answer << endl;
    return 0;
}
