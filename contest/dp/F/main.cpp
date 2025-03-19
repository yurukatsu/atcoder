#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string LCS(const string &s, const string &t)
{
    int s_len = s.length();
    int t_len = t.length();

    vector<vector<int>> dp(s_len + 1, vector<int>(t_len + 1, 0));

    for (int i = 1; i <= s_len; i++)
    {
        for (int j = 1; j <= t_len; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    string lcs = "";
    int i = s_len, j = t_len;
    while (i > 0 && j > 0)
    {
        if (s[i - 1] == t[j - 1])
        {
            lcs = s[i - 1] + lcs;
            i--;
            j--;
        }
        else if (dp[i - 1][j] >= dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    return lcs;
}

int main()
{
    string s, t;
    cin >> s >> t;

    string result = LCS(s, t);
    cout << result << endl;

    return 0;
}
