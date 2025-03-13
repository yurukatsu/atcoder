#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cassert>
using namespace std;

const string YES = "Yes";
const string NO = "No";

void solve(long long N, std::vector<long long> A)
{
    int count = 0;
    for (int i = 1; i < N; i++)
    {
        if (A[i] == A[i - 1])
        {
            count++;
        }
        else
        {
            count = 0;
        }

        if (count == 2)
        {
            cout << YES << endl;
            return;
        }
    }
    cout << NO << endl;
}

int main()
{
    long long N;
    std::scanf("%lld", &N);
    std::vector<long long> A(N);
    for (int i = 0; i < N; i++)
    {
        std::scanf("%lld", &A[i]);
    }
    solve(N, std::move(A));
    return 0;
}
