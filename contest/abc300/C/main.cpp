#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;
    vector<string> grid(H);
    for (int i = 0; i < H; i++)
    {
        cin >> grid[i];
    }

    // 4方向（右下、左下、右上、左上）の連続 '#' 数を記録する DP 配列
    vector<vector<int>> d1(H, vector<int>(W, 0)); // 右下方向
    vector<vector<int>> d2(H, vector<int>(W, 0)); // 左下方向
    vector<vector<int>> d3(H, vector<int>(W, 0)); // 右上方向
    vector<vector<int>> d4(H, vector<int>(W, 0)); // 左上方向

    // d1: 右下方向（下から上、右から左に走査）
    for (int i = H - 1; i >= 0; i--)
    {
        for (int j = W - 1; j >= 0; j--)
        {
            if (grid[i][j] == '#')
            {
                d1[i][j] = 1;
                if (i + 1 < H && j + 1 < W)
                    d1[i][j] += d1[i + 1][j + 1];
            }
        }
    }

    // d2: 左下方向（下から上、左から右に走査）
    for (int i = H - 1; i >= 0; i--)
    {
        for (int j = 0; j < W; j++)
        {
            if (grid[i][j] == '#')
            {
                d2[i][j] = 1;
                if (i + 1 < H && j - 1 >= 0)
                    d2[i][j] += d2[i + 1][j - 1];
            }
        }
    }

    // d3: 右上方向（上から下、右から左に走査）
    for (int i = 0; i < H; i++)
    {
        for (int j = W - 1; j >= 0; j--)
        {
            if (grid[i][j] == '#')
            {
                d3[i][j] = 1;
                if (i - 1 >= 0 && j + 1 < W)
                    d3[i][j] += d3[i - 1][j + 1];
            }
        }
    }

    // d4: 左上方向（上から下、左から右に走査）
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (grid[i][j] == '#')
            {
                d4[i][j] = 1;
                if (i - 1 >= 0 && j - 1 >= 0)
                    d4[i][j] += d4[i - 1][j - 1];
            }
        }
    }

    // 各セルを中心として、形成可能なバツ印の最大サイズは、
    // t = min{d1, d2, d3, d4} であり、サイズ n のバツ印を作るには n+1 個連続していなければならないので n < t となる。
    // また、4方向のうち少なくとも1方向がちょうど n+1 個である（拡張できない）必要があります。
    int maxSize = 0;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (grid[i][j] == '#')
            {
                int t = min({d1[i][j], d2[i][j], d3[i][j], d4[i][j]});
                if (t > 0)
                {
                    maxSize = max(maxSize, t - 1);
                }
            }
        }
    }

    // S[k] (1 <= k <= maxSize) にバツ印の個数を格納する
    vector<long long> S(maxSize + 1, 0);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (grid[i][j] != '#')
                continue;
            int t = min({d1[i][j], d2[i][j], d3[i][j], d4[i][j]});
            // サイズ n のバツ印の候補は n = 1,2,...,t-1
            for (int n = 1; n < t; n++)
            {
                // 4方向のうち少なくとも1方向がちょうど n+1 個連続なら、サイズ n のバツ印成立
                if (d1[i][j] == n + 1 || d2[i][j] == n + 1 || d3[i][j] == n + 1 || d4[i][j] == n + 1)
                {
                    S[n]++;
                }
            }
        }
    }

    // 出力: S₁, S₂, …, Sₙ（n = maxSize）
    // 存在しないサイズの場合は何も出力しません
    for (int n = 1; n <= min(H, W); n++)
    {
        if (n <= maxSize)
        {
            cout << S[n] << " ";
        }
        else
        {
            cout << 0 << (n == min(H, W) ? "\n" : " ");
        }
    }

    return 0;
}
