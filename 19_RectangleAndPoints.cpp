
#include <iostream>
#include <string>
#include <vector>

const int HashTableSize = 8;

using namespace std;

int hash_1(const string &key, int m) {
    int hash = 0;
    int a = 11;
    for (int i = 0; i < static_cast<int>( key.size()); i++) {
        hash = (hash * a + key[i]) % m;
    }
    return hash;
}


int hash_2(const string &key, int m) {
    int hash = 0;
    int a = 17;
    for (int i = 0; i < static_cast<int>( key.size()); i++) {
        hash = (hash * a + key[i]) % m;
    }
    hash = (2 * hash + 1) % m;
    return hash;
}


int HashFunction(int h1, int h2, int i, int m) {
    if (m != 0) {
        return (h1 + i * h2) % m;
    } else {
        return 0;
    }
}

struct HashTableNode {
    HashTableNode(const string &_key) : key(_key), Del(false) {}

    string key;
    bool Del;
};

class CHashTable {
public:
    CHashTable() : table(HashTableSize, NULL), _size(0) {}

    bool Add(const string &key);

    bool Remove(const string &key);

    bool Has(const string &key) const;

    void ReTable();

private:
    vector<HashTableNode *> table;
    int _size;
};


bool CHashTable::Add(const string &key) {
    if (static_cast<double>(_size) / static_cast<double>( table.size()) >= 0.75) {
        ReTable();
    }

    int h1 = hash_1(key,  table.size());
    int h2 = hash_2(key,  table.size());
    int h = HashFunction(h1, h2, 0,  table.size());
    for (int i = 0; i < table.size() and table[h] != NULL; i++) {
        if (table[h]->key == key and table[h]->Del == false) {
            return false;
        }
        if (table[h]->Del == true) {
            table[h]->key = key;
            table[h]->Del = false;
            _size++;
            return true;
        }
        h = HashFunction(h1, h2, i + 1, table.size());
    }

    table[h] = new HashTableNode(key);
    _size++;
    return true;
}

bool CHashTable::Remove(const string &key) {
    int h1 = hash_1(key,  table.size());
    int h2 = hash_2(key, table.size());
    int j = HashFunction(h1, h2, 0,  table.size());
    for (int i = 0; i <  table.size(); i++) {
        if (table[j] != NULL) {
            if (table[j]->key == key and table[j]->Del == false) {
                table[j]->Del = true;
                _size--;
                return true;
            }
        } else {
            return false;
        }
        j = HashFunction(h1, h2, i + 1,  table.size());
    }
}

bool CHashTable::Has(const string &key) const {
    int i = 0;
    int h1 = hash_1(key, table.size());
    int h2 = hash_2(key, table.size());
    int h = h1;
    while (table[h] != NULL and i <  table.size()) {
        if (table[h]->key == key and table[h]->Del == false) {
            return true;
        }
        h = HashFunction(h1, h2, i + 1, table.size());
        i++;
    }
    return false;
}

void CHashTable::ReTable() {
    int newBufferSize =  table.size() * 2;
    vector<HashTableNode *> newBuffer(newBufferSize, NULL);
    for (int i = 0; i < table.size(); i++) {
        if (table[i] != NULL and table[i]->Del == false) {
            int j = 0;
            int h1 = hash_1(table[i]->key, newBufferSize);
            int h2 = hash_2(table[i]->key, newBufferSize);
            int h = HashFunction(h1, h2, j, newBufferSize);
            while (j < newBufferSize) {
                if (newBuffer[h] == NULL) {
                    break;
                }
                j++;
                h = HashFunction(h1, h2, j, newBufferSize);
            }
            newBuffer[h] = table[i];
        }
    }
    table = newBuffer;
}

int main() {
    CHashTable table;
    while (true) {
        char command = 0;
        string value;
        cin >> command >> value;
        if (cin.fail()) {
            break;
        }
        switch (command) {
            case '?':
                cout << (table.Has(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '+':
                cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }


    return 0;
}