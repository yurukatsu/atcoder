#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;

int main()
{
    int N, W;
    cin >> N >> W;

    vector<ll> w(N), v(N);
    for (int i = 0; i < N; i++)
    {
        cin >> w[i] >> v[i];
    }

    vector<vector<ll>> dp(N + 1, vector<ll>(W + 1, 0));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (j - w[i] >= 0)
            {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - w[i]] + v[i]);
            }
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
        }
    }

    cout << dp[N][W] << endl;
}
