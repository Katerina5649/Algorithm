#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
/*
Ребро неориентированного графа называется мостом, если удаление этого ребра из графа увеличивает число компонент связности.

Дан неориентированный граф, требуется найти в нем все мосты.

Формат ввода
Первая строка входного файла содержит два целых числа n и m — количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000).

Следующие m строк содержат описание ребер по одному на строке. Ребро номер i описывается двумя натуральными числами bi, ei — номерами концов ребра (1 ≤ bi, ei ≤ n).

Формат вывода
Первая строка выходного файла должна содержать одно натуральное число b — количество мостов в заданном графе.
На следующей строке выведите b целых чисел — номера ребер, которые являются мостами,
в возрастающем порядке. Ребра нумеруются с единицы в том порядке, в котором они заданы во входном файле.
 */
using namespace std;

//здесь будут все мосты. Мост - это пара начало/конец
class FindBridge {
private:
    set<set<int>> pairs;
    vector<bool> used;
    vector<int> tin;
    vector<int> fup;
    int timer = 0;
    vector<list<int>> G;

//добавляет мост в pairs
    void IS_BRIDGE(int to, int v) {
        set<int> way;
        way.insert(to);
        way.insert(v);
        pairs.insert(way);
    }


    void dfs(int v, int p) {
        used[v] = true;
        tin[v] = fup[v] = timer++;
        for (list<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            int to = *it;
            if (to == p) continue;
            if (!used[to]) {
                dfs(to, v);
                fup[v] = min(fup[v], fup[to]);
                if (fup[to] > tin[v]) {
                    IS_BRIDGE(to, v);
                }

            } else
                fup[v] = min(fup[v], tin[to]);
        }
    }

public:
//находим мосты
    set<set<int>> find_bridges(int n, vector<list<int>> &graph) {
        G = graph;
        used = vector<bool>(n);
        tin = vector<int>(n);
        fup = vector<int>(n);

        for (int i = 0; i < n; ++i)
            used[i] = false;
        for (int i = 0; i < n; ++i)
            if (!used[i])
                dfs(i, -1);
        return pairs;

    }
};

int main() {
    string line;
    ifstream in("bridges.in");
    int n, m;
    //для сохранения ребра и его номера во входе. vector<int> - номера ребер во входе.
    // Используется vector т.к могут быть кратные ребра
    map<set<int>, vector<int>> ribs;
    //сюда запишем номера ребер
    vector<int> res;

    if (in.is_open()) {
        getline(in, line);
        sscanf(line.c_str(), "%d %d", &n, &m);
        int a, b;
        vector<list<int>> G(n + 1);
        for (int i = 0; i < m; i++) {
            getline(in, line);
            sscanf(line.c_str(), "%d %d", &a, &b);
            set<int> s;
            s.insert(a);
            s.insert(b);
            ribs[s].push_back(i + 1);
            G[a].push_back(b);
            G[b].push_back(a);
        }

        //выводит номера пар
        FindBridge fbridge;
        set<set<int>> pairs = fbridge.find_bridges(n + 1, G);
        for (set<int> e : pairs) {
            //идет проверка на кратные ребра . == 1 значит что ребро не кратное
            if (ribs[e].size() == 1)
                res.push_back(ribs[e][0]);
        }
        sort(res.rbegin(), res.rend());
        //нам нужно вывести элементы в порядке возраствния. Так что меняем начало и конец местами
        reverse(res.begin(), res.end());

    }
    in.close();

    ofstream out("bridges.out");
    if (out.is_open()) {
        out << res.size() << endl;
        for (int e : res)
            out << e << endl;

    }
    out.close();

    return 0;
}