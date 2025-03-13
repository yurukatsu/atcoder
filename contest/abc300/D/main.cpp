#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> p;

void sieve(ll n)
{
    vector<bool> s(n + 1, true);
    s[0] = s[1] = false;
    for (ll i = 2; i * i <= n; i++)
    {
        if (s[i])
        {
            for (ll j = i * i; j <= n; j += i)
                s[j] = false;
        }
    }
    for (ll i = 2; i <= n; i++)
    {
        if (s[i])
            p.push_back(i);
    }
}

int main()
{
    ll n;
    cin >> n;
    sieve(1000000);
    ll c = 0;

    for (int i = 0; i < p.size(); i++)
    {
        ll p1 = p[i];
        if (p1 * p1 * p1 >= n)
            break;

        for (int j = i + 1; j < p.size(); j++)
        {
            ll p2 = p[j];
            if (p1 * p1 * p2 * p2 >= n)
                break;

            ll max_p3 = sqrt(n / (p1 * p1 * p2));
            auto it = upper_bound(p.begin() + j + 1, p.end(), max_p3);
            c += distance(p.begin() + j + 1, it);
        }
    }

    cout << c << endl;
    return 0;
}
