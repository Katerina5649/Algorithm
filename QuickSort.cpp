#include <iostream>
#include <vector>
using namespace std;

/*
 * Дан массив целых чисел. Ваша задача — отсортировать его в порядке неубывания.

Входные данные
В первой строке входного файла содержится число N (1 ≤ N ≤ 100 000) — количество элементов в массиве. Во второй строке находятся N целых чисел, по модулю не превосходящих 109.

Выходные данные
В выходной файл надо вывести этот же массив в порядке неубывания, между любыми двумя числами должен стоять ровно один пробел.
 * */
void quickSort(vector<int>& array, int l, int h) {
    int i = l;
    int j = h;
    int pivot = array[(i + j) / 2];

    while (i <= j) {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j) {
            swap(array[i], array[j]);
            i++;
            j--;
        }
    }
    if (j > l)
        quickSort(array, l, j);
    if (i < h)
        quickSort(array, i, h);
}


int main() {
   int n;
   cin >> n;
   vector<int> array;
   int elem;

   for (int i = 0; i < n; i++) {
       cin >> elem;
        array.push_back(elem);
   }

   quickSort(array, 0, n - 1);
   for (int i = 0; i < n; i ++) {
       cout << array[i] << " ";
   }
    return 0;
}