#include <iostream>
#include <vector>
#include <fstream>
#include <random>
/* Выбор k-той порядковой статистики при случайном опорном элементе*/
using namespace std;
template<class T>
class IsLessDefaultFunctor {
public:
    bool operator()(const T& l, const T& r)
    {
        return l < r;
    }
};


template<class T, class IsLess = IsLessDefaultFunctor<T>>
int partition(vector<T> &arr, unsigned l, unsigned r, IsLess isLess = IsLess()) {
    if (l != r) {
        int randomElem = rand() % (r - l);
        swap(arr[l + randomElem], arr[r]);
    }
    int x = arr[r];
    int i = l - 1;
    for (int j = l; j <= r; j++) {
        if (isLess(arr[j], x) || (arr[j] == x))
            swap(arr[++i], arr[j]);
    }
    return i;
}

template<class T, class IsLess = IsLessDefaultFunctor<T>>
int k_order_stat(vector<T> arr, unsigned k, IsLess isLess = IsLess()) {
    int l = 0, r = arr.size() - 1;
    for (;;) {
        int pos = partition(arr, l, r, isLess);
        if (pos > k)
            r = pos - 1;
        else if (pos < k)
            l = pos + 1;
        else return arr[k];
    }
}

int main() {
    int n, k = 0;
    vector<int> arr;
    string line;
    ifstream in("input.txt");
    if (in.is_open()) {
        getline(in, line);
        sscanf(line.c_str(), "%d %d", &n, &k);
        for (int i = 0; i < n; i++) {
            int elem;
            in >> elem;
            arr.push_back(elem);
        }
    }
    in.close();
    int k_stat = k_order_stat(arr, k);
    ofstream out("output.txt"/*ios::app - для дозаписи*/);
    if (out.is_open()) {
        out << k_stat;
    }
    out.close();
    return 0;
}