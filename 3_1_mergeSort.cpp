#include <iostream>
#include <fstream>
#include <vector>
/*
 Дана очень длинная последовательность целых чисел длины n. Требуется вывести в отсортированном виде её наименьшие k элементов.
 Последовательность может не помещаться в память. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
 */

/*
Sort - реализация сортировки MergeSort.
 */

using namespace std;


//реализация MergeSort
// использовать как mergeSort(0, arr.size() - 1)
template<class T>
class IsLessDefaultFunctor {
public:
    bool operator()(const T& l, const T& r)
    {
        return l < r;
    }
};
template<class T, class IsLess = IsLessDefaultFunctor<T>>
void  Merge(vector<T>& arr , int l, int med, int r , IsLess isLess = IsLess()){
    int aux[r - l + 1];
    int k1 = l;
    int k2 = med + 1;
    int cur = 0;
    while (r - l + 1 != cur) {
        if (k2 > r)
            aux[cur++] = arr[k1++];
        else if (k1 > med)
            aux[cur++] = arr[k2++];
        else if (isLess(arr[k2], arr[k1]))
            aux[cur++] = arr[k2++];
        else aux[cur++] = arr[k1++];

    }
    for (int i = 0; i < cur; i++)
        arr[i + l] = aux[i];

}

template<class T, class IsLess = IsLessDefaultFunctor<T>>
void Sort(vector<T>& arr , int l, int r, IsLess isLess = IsLess())
{
    if (l == r)
        return;
    if (r - l == 1) {
        if (isLess(arr[r], arr[l]))
            swap(arr[l], arr[r]);
        return;
    }
    int med = (l + r) / 2;
    Sort<T>(arr, l, med, isLess);
    Sort<T>(arr, med + 1, r, isLess);

    Merge(arr, l,med,r);
}



//выводит K элементов очень длинной последовательности , если бы она была отсортирована
int main() {
    vector<int> arr;
    int n, k;
    string line;
    ifstream in("input.txt");
    if (in.is_open()) {
        getline(in, line);
        sscanf(line.c_str(), "%d %d", &n, &k);
        int rub;
        for (int i = 0; i < n; i++) {
            in >> rub;
            arr.push_back(rub);
            if (arr.size() == 2 * k) {
                Sort<int>(arr,  k - 1, 2 * k - 1); //Т. К. у нас объявлен вектор интов, то и тип данных в сорте будет
                Merge<int>(arr, 0, k -2, 2*k - 1);
                arr.erase(arr.begin() + k,arr.begin() + arr.size() - 1 );
            }
        }
    }
    in.close();

    Sort<int>(arr, 0, arr.size() - 1);
    int size = arr.size();
    for (int j = k  ; j < size ; j++) {
        arr.erase(arr.begin() + arr.size() - 1);
    }

    ofstream out("output.txt"/*ios::app - для дозаписи*/);
    if (out.is_open()) {
        for (int i = 0; i < arr.size(); i++)
            out << arr[i] << " ";
    }
    out.close();
    return 0;
}


