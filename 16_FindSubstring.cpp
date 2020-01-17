#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
/* Т.к z-функция ищет длину совпадения с началом, то для начала я объединю шаблок и строку в одну строку. */
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    ifstream in("input.txt");
    string temp, line;
    if (in.is_open()) {
        getline(in, temp);
        getline(in, line);
        //объединяю
        line = temp + line;
    }
    in.close();

    vector<int> z_func = z_function(line);
    int n = temp.size();

    ofstream out("output.txt"/*ios::app - для дозаписи*/);
    if (out.is_open()) {
        for (int i = n - 1; i < line.length(); i++) {
            if (z_func[i] >= n)
                out << i - n << " ";
        }
    }
    out.close();
    return 0;
}