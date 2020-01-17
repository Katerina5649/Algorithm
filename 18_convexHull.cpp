#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>

struct point {
    double x, y;
};

double perimeter(point a1 , point a2){
    return sqrt(pow(a1.x - a2.x , 2) + pow(a1.y - a2.y , 2));
}
using namespace std;



    bool cmp(point a, point b) {
        return a.x < b.x || a.x == b.x and a.y < b.y;
    }

    bool cw(point a, point b, point c) {
        return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
    }

    bool ccw(point a, point b, point c) {
        return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
    }


    void convex_hull(vector<point> &a) {
       if (a.size() == 1) return;
       sort(a.begin(), a.end(), &cmp);
       point p1 = a[0], p2 = a.back();
       vector<point> up, down;
       up.push_back(p1);
       down.push_back(p1);
       for (size_t i = 1; i < a.size(); ++i) {
           if (i == a.size() - 1 || cw(p1, a[i], p2)) {
               while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i]))
                   up.pop_back();
               up.push_back(a[i]);
           }
           if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
               while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i]))
                   down.pop_back();
               down.push_back(a[i]);
           }
       }
       a.clear();
       for (size_t i = 0; i < up.size(); ++i)
           a.push_back(up[i]);
       for (size_t i = down.size() - 2; i > 0; --i)
           a.push_back(down[i]);

       int k = 0;
   }

int main() {
    string line;
    int n , hull;
    ifstream in("input.txt");
    if (in.is_open()) {
       getline(in, line);
        sscanf(line.c_str(), "%d", &n);
        vector<point> vec (n);
        point p;
        for (int i = 0; i < n; i++){
            getline(in, line);
            sscanf(line.c_str(), "%lf %lf", &p.x, &p.y);
            vec.push_back(p);
        }

        convex_hull(vec);
        double per;
        for(int i = 0; i < vec.size() - 1; i++){
            per +=  perimeter(vec[i] , vec[i +1]);
        }
        per+= perimeter(vec[0] , vec[vec.size() - 1]);

        ofstream out("output.txt"/*ios::app - для дозаписи*/);
        if (out.is_open()) {
            out.precision(9);
           out << per <<setprecision(9);
        }
        out.close();
    }
    in.close();

    return 0;
}