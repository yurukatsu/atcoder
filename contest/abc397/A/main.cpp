#include <iostream>
using namespace std;

const int HIGH_FEVER = 1;
const int FEVER = 2;
const int NORMAL = 3;
const double HIGH_FEVER_TEMPERATURE = 38.0;
const double FEVER_TEMPERATURE = 37.5;

void solve(long double X)
{
    if (X >= HIGH_FEVER_TEMPERATURE)
    {
        cout << HIGH_FEVER << endl;
    }
    else if (X >= FEVER_TEMPERATURE)
    {
        cout << FEVER << endl;
    }
    else
    {
        cout << NORMAL << endl;
    }
}

int main()
{
    long double X;
    cin >> X;
    solve(X);
    return 0;
}
