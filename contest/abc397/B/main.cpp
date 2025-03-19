#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;
    int n = S.size();

    // Ensure the starting length is even and at least n.
    int start = (n % 2 == 0 ? n : n + 1);

    int answer = 0;
    // Try all even lengths from start up to 2*n (upper bound in worst-case).
    for (int L = start; L <= 2 * n; L += 2)
    {
        int pos = 0;
        // Construct the pattern "ioioio..." on the fly.
        for (int j = 0; j < L && pos < n; j++)
        {
            char expected = (j % 2 == 0 ? 'i' : 'o');
            if (S[pos] == expected)
            {
                pos++;
            }
        }
        // If the whole S is matched, we found a valid T.
        if (pos == n)
        {
            answer = L - n;
            break;
        }
    }

    cout << answer << "\n";
    return 0;
}
