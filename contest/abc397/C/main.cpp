#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    // prefix[i] will store the number of distinct integers in A[0..i]
    vector<int> prefix(N);
    vector<int> freq(N + 1, 0); // since A[i] is in range [1, N]
    int distinct = 0;
    for (int i = 0; i < N; i++)
    {
        if (freq[A[i]] == 0)
        {
            distinct++;
        }
        freq[A[i]]++;
        prefix[i] = distinct;
    }

    // suffix[i] will store the number of distinct integers in A[i..N-1]
    vector<int> suffix(N);
    fill(freq.begin(), freq.end(), 0);
    distinct = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        if (freq[A[i]] == 0)
        {
            distinct++;
        }
        freq[A[i]]++;
        suffix[i] = distinct;
    }

    // Compute the maximum sum of distinct counts by splitting between i and i+1
    int ans = 0;
    for (int i = 0; i < N - 1; i++)
    {
        ans = max(ans, prefix[i] + suffix[i + 1]);
    }

    cout << ans << "\n";
    return 0;
}
