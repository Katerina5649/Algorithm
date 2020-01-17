#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

//обход в ширину
int getLinForLeastPath(vector<vector<int>> graph, int start, int end){
    queue<int> q,next;

    //для понимания в каком слое мы находимся
    set<int> layer , new_layer;
    q.push(start);
    layer.insert(start);
    vector<bool> used (graph.size());
    vector<int> d (graph.size()), p (graph.size());
    used[start] = true;
    //если мы дошли до конца, то больше не будем добавлять в очередь
    bool flag = true;
    //колличество минимальных путей
    vector<int> distance (graph.size());

    for (size_t i = 0; i < graph[start].size(); ++i) {
        int to = graph[start][i];
        if (to == end)
            return 1;
        distance[to]  = 1;
        used[to] = true;
        q.push(to);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        used[v] = true;
        for (size_t i = 0; i < graph[v].size(); ++i) {
            int to = graph[v][i];
            if (to == end)
                flag = false;
            if (!used[to]) {
                distance[to] += distance[v] ;
                next.push(to);
            }
        }
        if (q.empty() and flag)
        {
            q = next;
            while(!next.empty())
                next.pop();
        }
    }
    return distance[end];
}

int main() {
    int n; // число вершин
    int v;
    vector<vector<int>> graph;
    int start, end; // стартовая вершина
    int a, b;
    string line;
    ifstream in("input.txt");
    if (in.is_open()) {
        getline(in, line);
        sscanf(line.c_str(), "%d", &n);
        getline(in, line);
        sscanf(line.c_str(), "%d", &v);
        getline(in, line);
        for (int i = 0; i < n; i++) {
            vector<int> vec;
            graph.push_back(vec);
        }


        while (line != "") {
            sscanf(line.c_str(), "%d %d", &a, &b);
            getline(in, line);
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        getline(in, line);
        sscanf(line.c_str(), "%d %d", &start, &end);
    }


    ofstream out("output.txt"/*ios::app - для дозаписи*/);
    if (out.is_open()) {
        out << getLinForLeastPath(graph, start, end);
        cout << getLinForLeastPath(graph, start, end);
    }
    out.close();

    return 0;
}