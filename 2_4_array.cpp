#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    string line;
    int n;
    vector<int> arr;
    int *res;
    int i, j;
    int k = 0;
    vector<int> V_1, V_2;


    ifstream in("input.txt");
    if (in.is_open()) {
        getline(in, line);
        sscanf(line.c_str(), "%d", &n);

        for (i = 0; i < n; i++) {
            int back;
            in >> back;
            arr.push_back(back);

        }
        in >> k;

        V_1.resize(n);
        V_2.resize(n);
        k--;

        V_2[n-1] = arr[n-1];
        // Расчитываем V_1
        for (int i = 0; (i < n) & (k != 0) &(k != n-1); i++) {
            if (i % k)
                V_1[i] = max(arr[i], V_1[i - 1]);
            else
                V_1[i] = arr[i];
        }


        // Расчитываем V_2
        // V_2.back() = arr.back();
        for (int i = n - 2; (i >= 0)  & (k != 0) & (k != n-1); i--) {
            if ((i + 1) % k)
                V_2[i] = max(arr[i], V_2[i + 1]);
            else
                V_2[i] = arr[i];
        }

    }

    for (i = 0; i< n ;i++)
        cout << V_1[i] << " ";

    cout<<endl;
    for (i = 0; i < n; i++)
        cout << V_2[i] << " ";

    ofstream out("output.txt"/*ios::app - для дозаписи*/);
    if (out.is_open()) {
        if (k == 0){
            V_2 = arr;
            V_1 = arr;
        }
        for (i = 0; (i + k  < n ) && (k != n-1); i++) {
            out<< max(V_2[i], V_1[i + k - 1]) ;
            if (i + k < n-1)
                out << " ";
        }
        if (k == n-1)
            out << V_2[n-1];
    }
    out.close();
    return 0;
}