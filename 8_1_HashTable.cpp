#include <iostream>
#include <string>
#include <vector>

/*
 * Тест
+ A
OK
+ b
OK
+ c
OK
+ d
OK
+ e
OK
+ t
OK
+ a
OK
+ e
FAIL
+ a
FAIL
? a
OK
- a
OK
? a
FAIL

 */

const int HashTableSize = 8;

using namespace std;

int Hash( const string& key, int m ) {
    int hash = 0;
    int a = 127;
    for( int i = 0; i < static_cast<int>( key.size() ); i++ ) {
        hash = ( hash * a + key[i] ) % m;
    }
    return hash;
}

int Proba( int h, int i, int m ) {
    if( m != 0 ) {
        return( h + i  % m) % m;
    } else {
        return 0;
    }
}

struct HashTableNode {
    HashTableNode(const string &_key): key(_key), Del(false) {}
    string key;
    bool Del;
};

class CHashTable {
public:
    CHashTable(): table(HashTableSize, NULL), _size(0) {}
    bool Insert(const string &key);
    bool Remove(const string &key);
    bool Has(const string &key) const;
    void ReHash();

private:
    vector<HashTableNode*> table;
    int _size;
};


bool CHashTable::Insert( const string &key ) {
    if( static_cast<double>(_size)/static_cast<double>(static_cast<int>( table.size())) >=0.75) {
        ReHash();
    }

    int h = Hash(key, static_cast<int>( table.size()));
    for (int i=0; i<static_cast<int>( table.size()) and table[h] != NULL; i++) {
        if(table[h]->key == key and table[h]->Del==false) {
            return false;
        }
        if(table[h]->Del==true ) {
            table[h]->key=key;
            table[h]->Del=false;
            _size++;
            return true;
        }
        h=Proba(h, i+1, static_cast<int>( table.size()));
    }

    table[h] = new HashTableNode(key);
    _size++;
    return true;
}

bool CHashTable::Remove(const string &key) {
    int h = Hash(key, static_cast<int>( table.size()));
    for( int i = 0; i < static_cast<int>( table.size()); i++ ) {
        if(table[h] != NULL) {
            if( table[h]->key == key and table[h]->Del == false) {
                table[h]->Del = true;
                _size--;
                return true;
            }
        } else {
            return false;
        }
        h = Proba( h, i+1, static_cast<int>( table.size()));
    }
}

bool CHashTable::Has( const string &key ) const {
    int i = 0;
    int h = Hash(key, static_cast<int>( table.size()));
    while( table[h] != NULL and i < static_cast<int>( table.size()) ) {
        if( table[h]->key == key and table[h]->Del==false ){
            return true;
        }
        h = Proba( h, i+1, static_cast<int>( table.size()));
        i++;
    }
    return false;
}

void CHashTable::ReHash() {
    int newBufferSize = static_cast<int>( table.size()) * 2;
    vector<HashTableNode*> buffer(newBufferSize, NULL);
    swap(table , buffer);
    _size = 0;
    for (HashTableNode* e: buffer){
        if (e != NULL)
            Insert(e->key);
    }

}

int main()
{
    CHashTable table;
    while( true ) {
        char command = 0;
        string value;
        cin >> command >> value;
        if( cin.fail() )
        {
            break;
        }
        switch( command )
        {
            case '?':
                cout << ( table.Has( value ) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '+':
                cout << ( table.Insert( value ) ? "OK" : "FAIL" ) << std::endl;
                break;
            case '-':
                cout << ( table.Remove( value ) ? "OK" : "FAIL" ) << std::endl;
                break;
        }
    }


    return 0;
}