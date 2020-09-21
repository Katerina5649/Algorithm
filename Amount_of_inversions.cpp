#include <iostream>
#include <vector>

using namespace std;
 /*
  *Напишите программу, которая для заданного массива 𝐴=⟨𝑎1,𝑎2,…,𝑎𝑛⟩ находит количество пар (𝑖,𝑗) таких, что 𝑖<𝑗 и 𝑎𝑖>𝑎𝑗.

Входные данные
Первая строка входного файла содержит натуральное число 𝑛 (1≤𝑛≤500000) — количество элементов массива. Вторая строка содержит 𝑛 попарно различных элементов массива 𝐴 (0≤𝑎𝑖≤106).

Выходные данные
В выходной файл выведите одно число — ответ на задачу.
  * */

void  merge(vector<int>& arr , int l, int med, int r, unsigned long long& inv) {
    int merger[r - l + 1];
    int k1 = l;
    int k2 = med + 1;
    int cur = 0;
    while (r - l + 1 != cur) {
        if (k2 > r) {
            merger[cur++] = arr[k1++];

        }
        else if (k1 > med) {
            merger[cur++] = arr[k2++];

        }
        else if (arr[k2] < arr[k1]) {
            merger[cur++] = arr[k2++];
            inv += med - k1 + 1;
            if (k2 > r) {
                merger[cur++] = arr[k1++];
            }
        }
        else merger[cur++] = arr[k1++];
    }
    for (int i = 0; i < cur; i++)
        arr[i + l] = merger[i];

}


void sort(vector<int>& arr, int l, int r, unsigned long long& inv) {
    if (l == r)
        return;
    if (r - l == 1) {
        if (arr[r] < arr[l]) {
            swap(arr[l], arr[r]);
            inv++;
        }

        return;
    }
    int med = (l + r) / 2;
    sort(arr, l, med, inv);
    sort(arr, med + 1, r, inv);

    merge(arr, l, med, r, inv);
}




int main() {
    // кол-во инверсий
    unsigned long long inv = 0;
    vector<int> arr;
    int n;
    string line;
    cin >> n;
    int rub;
    if (n == 0) {
        cout << 0;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> rub;
        arr.push_back(rub);
    }

    sort(arr, 0, arr.size() - 1, inv);


    cout << inv;
    return 0;
}