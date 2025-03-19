#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<ll> a(N);
    vector<ll> b(N);
    vector<ll> c(N);

    for (int i = 0; i < N; i++)
    {
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<vector<ll>> dp(N, vector<ll>(3, 0));

    dp[0][0] = a[0];
    dp[0][1] = b[0];
    dp[0][2] = c[0];

    for (int i = 1; i < N; i++)
    {
        dp[i][0] = max(dp[i - 1][1] + a[i], dp[i - 1][2] + a[i]);
        dp[i][1] = max(dp[i - 1][0] + b[i], dp[i - 1][2] + b[i]);
        dp[i][2] = max(dp[i - 1][0] + c[i], dp[i - 1][1] + c[i]);
    }

    cout << max({dp[N - 1][0], dp[N - 1][1], dp[N - 1][2]}) << endl;
}
