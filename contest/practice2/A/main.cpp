#include <iostream>
#include <vector>
using namespace std;

class UnionFind
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        else
        {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);

        if (x == y)
            return;

        if (rank[x] < rank[y])
        {
            parent[x] = y;
        }
        else
        {
            parent[y] = x;
            if (rank[x] == rank[y])
                rank[x]++;
        }
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
};

int main()
{
    int N, Q;
    cin >> N >> Q;

    UnionFind uf(N);

    for (int i = 0; i < Q; i++)
    {
        int t, u, v;
        cin >> t >> u >> v;

        if (t == 0)
        {
            uf.unite(u, v);
        }
        else
        {
            cout << (uf.same(u, v) ? 1 : 0) << endl;
        }
    }

    return 0;
}
