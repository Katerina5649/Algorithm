/*
 Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.

Обрабатывать команды push back и pop front.

Формат ввода
В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.

a = 2 - pop front
a = 3 - push back

Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.

Формат вывода
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 */




#include <iostream>
#include <stack>
#include <algorithm>
#include <fstream>

using namespace std;

class Queue
{
private:
    stack<int> stack_1;
    stack<int> stack_2;
public:

    void push(int val) {
        if (stack_1.empty()){
        }
        stack_1.push(val);
    }

    int  pop() {
        if (stack_2.size() <= 0) {
            while (stack_1.size() > 0) {
                stack_2.push(stack_1.top());
                stack_1.pop();
            }
        }

       if (stack_2.empty())
           return -1;
       int res = stack_2.top();
       stack_2.pop();
       return res;

    }
};

int main() {
    Queue q ;

//чтение из файла
    string line;
    ifstream in; // окрываем файл для чтения
    in.open("input.txt");
    string res = "YES";
    bool flag =  true;
    if (in.is_open())
    {
        getline(in, line) ;
        while (getline(in, line) && flag)
        {
            int a, b;
            sscanf(line.c_str(), "%d %d", &a,&b);
            // cout << a << " "<< b<<  endl;
            if (a == 3)
                q.push(b);
            if (a == 2) {
                //cout << q.q_top <<" " << b <<" "  << f << endl;
                if ( q.pop() != b ) {
                    res = "NO";
                    flag = false;
                }

            }


        }
    }
    in.close();



//запись в файл
    ofstream out("output.txt"/*ios::app - для дозаписи*/);
    if (out.is_open())
    {
        out << res << endl;
    }
    out.close();

    return 0;
}









































