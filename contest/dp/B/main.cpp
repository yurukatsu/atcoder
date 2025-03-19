#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    int N, K;
    cin >> N;
    cin >> K;

    vector<long long> h(N);
    for (int i = 0; i < N; i++)
    {
        cin >> h[i];
    }

    vector<long long> dp(N, 1e12);
    dp[0] = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= K; j++)
        {
            if (i + j < N)
            {
                dp[i + j] = min(dp[i + j], dp[i] + abs(h[i] - h[i + j]));
            }
        }
    }

    cout << dp[N - 1] << endl;
}
