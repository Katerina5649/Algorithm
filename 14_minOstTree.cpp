/*Минимальное остовное дерево. Алгоритм Крускала с системой непересекающихся множеств
 O(MlogN)
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
class Kruskala {
public:
    Kruskala(vector < pair < int, pair<int,int> > > g, int n, int m);
    //получить вес дерева
    int getCount();
    //получить остовное дерево
    vector < pair<int,int> > getTree();
private:
    int count = 0;
    vector < pair<int,int> > res;
    vector<int> p;
    //ищу корень вершины v
    int get (int v);
    //объединяю 2 поддерева
    void unite (int a, int b);
};
vector < pair<int,int> > Kruskala::getTree() { return res;}
int Kruskala::getCount() { return count;}


int Kruskala::get(int v) {
    return (v == p[v]) ? v : (p[v] = get (p[v]));
}

void Kruskala::unite(int a, int b) {
    a = get (a);
    b = get (b);
    if (a != b)
        p[a] = b;
}
Kruskala::Kruskala(vector<pair<int, pair<int, int> > > g, int n, int m) {
    vector<int> newP (n);
    p = newP;

    sort (g.begin(), g.end());
    p.resize (n);
    for (int i=0; i<n; ++i)
        p[i] = i;
    for (int i=0; i<m; ++i) {
        int a = g[i].second.first,  b = g[i].second.second,  l = g[i].first;
        //проверка, что не принадлежат одному поддереву
        if (get(a) != get(b)) {
            count += l;
            res.push_back (g[i].second);
            unite (a, b);
        }
    }
}


int main() {
    vector < pair < int, pair<int,int> > > g ; // вес - вершина 1 - вершина 2
    int result;
    ifstream in("kruskal.in");
    string line;
    int n, m;
    if (in.is_open()) {
        getline(in, line);
        sscanf(line.c_str(), "%d %d", &n, &m);
        for (int i = 0; i < m; i++) {
            int r1, r2, weight;
            getline(in, line);
            sscanf(line.c_str(), "%d %d %d", &r1, &r2, &weight);
            g.push_back(make_pair(weight, make_pair(r1-1, r2-1)));
        }
        Kruskala k (g, n, m);
        result = k.getCount();
    }
    in.close();
    ofstream out("kruskal.out");
    if (out.is_open()) {
        out << result;
    }
    out.close();
}