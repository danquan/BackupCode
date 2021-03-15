#include <iostream>
#include <cstdio>
#include <queue>
#include <cmath>
#define task "VIRUS"
using namespace std;
using ll = long long;
using ld = long double;

const int N = 1e5 + 5;
struct node
{
    node *p, *par, *child[2];
    int sum, val, en;
    node(const int &v = 0)
    {
        p = par = this;
        sum = en = 0;
        val = v;
        child[0] = child[1] = NULL;
    }
};
struct Trie
{
    node root;
    string s;
    void Add(const string &s, const int &v)
    {
        node *a = &root;
        int id = 0;
        while (1)
        {
            if (id == (int)s.size())
            {
                a->en += v;
                a->sum += v;
                return;
            }
            if (!(a->child[s[id] - '0']))
            {
                a->child[s[id] - '0'] = new node;
                a->child[s[id] - '0']->par = a;
                a->child[s[id] - '0']->val = s[id] - '0';
            }
            a = a->child[s[id] - '0'];
            ++id;
        }
    }
    ll Cal(const string &s)
    {
        ll ans(0);
        int id = 0;
        node *a = &root;
        while (1)
        {
            if (id == (int)s.size())
                break;
            while (a != (&root) && (!(a->child[s[id] - '0'])))
                a = a->p;
            if (a->child[s[id] - '0'])
            {
                ans += a->child[s[id] - '0']->sum;
                a = a->child[s[id] - '0'];
            }
            ++id;
        }
        return ans;
    }
    void Prepare()
    {
        queue<node *> ss;
        if (root.child[0])
            ss.emplace(root.child[0]);
        if (root.child[1])
            ss.emplace(root.child[1]);
        while (ss.size())
        {
            auto c = ss.front();
            ss.pop();
            auto k = c->par->p;
            if (c->par != (&root))
            {
                while (k != (&root) && (!(k->child[c->val])))
                    k = k->p;
                if (k->child[c->val])
                {
                    c->p = k->child[c->val];
                    c->sum += c->p->sum;
                }
                else
                    c->p = &root;
            }
            else
                c->p = &root;
            if (c->child[0])
                ss.emplace(c->child[0]);
            if (c->child[1])
                ss.emplace(c->child[1]);
        }
    }
    void clear(node *a)
    {
        if (a->child[0])
        {
            clear(a->child[0]);
            delete a->child[0];
        }
        if (a->child[1])
        {
            clear(a->child[1]);
            delete a->child[1];
        }
        a->child[0] = a->child[1] = NULL;
        a->p = a->par = a;
        a->sum = a->en = 0;
    }
    void Clear()
    {
        clear(&root);
    }
    void dfs(node *a, Trie &f)
    {
        if (a->en != 0)
            f.Add(s, a->en);
        if (a->child[0])
        {
            s.push_back('0');
            dfs(a->child[0], f);
            s.pop_back();
        }
        if (a->child[1])
        {
            s.push_back('1');
            dfs(a->child[1], f);
            s.pop_back();
        }
    }
    void Copy(Trie &f)
    {
        s.clear();
        dfs(&root, f);
    }
} f[20];

int q, now(0);
bool ok;

void Read()
{
    cin >> q;
    while (q--)
    {
        int x;
        string s;
        cin >> x >> s;
        if (x == 0)
        {
            ++now;
            int i = log2(now & -now);
            for (int j = 0; j < i; ++j)
            {
                f[j].Copy(f[i]);
                f[j].Clear();
            }
            f[i].Add(s, 1);
            f[i].Prepare();
        }
        else
        {
            ll ans(0);
            for (int i = 0; i < 20; ++i)
                ans += f[i].Cal(s);
            cout << ans << "\n";
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (fopen(task ".INP", "r"))
    {
        freopen(task ".INP", "r", stdin);
        freopen(task ".OUT", "w", stdout);
    }
    Read();
    //Solve();
}
