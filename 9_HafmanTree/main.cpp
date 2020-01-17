#include <vector>
#include <map>
#include <list>
#include "Huffman.h"


typedef unsigned char byte;
using namespace std;

//------------объявляю то, чем считываю/записываю биты-----------
class BitsReader {
public:
    bool ReadBit(bool &bit);

    BitsReader(std::vector<byte> &&buffer);


private:
    std::vector<byte> buffer_;
    size_t position_ = 0;
    size_t bits_count_ = 4;
    size_t bits_count_last = 0;
    bool encoded = true;
};

BitsReader::BitsReader(std::vector<byte> &&buffer) :
        buffer_(std::move(buffer)) {
    bits_count_last = buffer_[0] & 7;
    encoded = (buffer_[0] & 8 != 0);
}

bool BitsReader::ReadBit(bool &bit) {
    if (((position_ == buffer_.size() - 1) && (bits_count_ == bits_count_last) && (bits_count_last != 0)) ||
        (position_ == buffer_.size())) {
        return false;
    }
    byte byte_ = buffer_[position_];
    bit = (byte_ & (1 << bits_count_++)) != 0;
    if (bits_count_ == 8) {
        position_++;
        bits_count_ = 0;
    }
    return true;
}



class BitsWriter {
public:
    void WriteBit(bool bit);

    std::vector<byte> GetResult();

    void setEncoded(bool encoded) { encoded_ = encoded; }

private:
    std::vector<byte> buffer_;
    byte accumulator_ = 0;
    size_t bits_count_ = 4;
    bool encoded_ = true;
};

void BitsWriter::WriteBit(bool bit) {
    accumulator_ |= static_cast<byte>(bit) << bits_count_++;
    if (bits_count_ == 8) {
        bits_count_ = 0;
        buffer_.push_back(accumulator_);
        accumulator_ = 0;
    }
}

std::vector<byte> BitsWriter::GetResult() {
    if (bits_count_ != 0) {
        buffer_.push_back(accumulator_);
    }
    buffer_[0] |= bits_count_;
    if (encoded_) {
        buffer_[0] |= 8;
    }
    return std::move(buffer_);
}

//-----------------------
class Node {
public:
    int a; //вес
    char c; //значение листа
    Node *left, *right;

    Node() { left = right = NULL; }

    Node(Node *L, Node *R) {
        left = L;
        right = R;
        a = L->a + R->a;
    }
};

vector<bool> code;
map<char, vector<bool> > table;

vector<byte> encodeTree;

struct Compare {
    bool operator()(const Node *l, const Node *r) const { return l->a < r->a; }
};

void EncodeTree(Node *root) {

    if (root == NULL) {

        encodeTree.push_back('*');
        return;
    }


    if (root->right == NULL and root->left == NULL) {

        encodeTree.push_back('#');

        encodeTree.push_back(root->c);
        return;
    }
    encodeTree.push_back(false);
    EncodeTree(root->left);
    encodeTree.push_back(true);
    EncodeTree(root->right);
    encodeTree.push_back('*');

}

void BuildTable(Node *root) {
    if (root->left != NULL) {
        code.push_back(0);
        BuildTable(root->left);
    }

    if (root->right != NULL) {
        code.push_back(1);
        BuildTable(root->right);
    }

    if (root->left == NULL && root->right == NULL) {
        table[root->c] = code;
    }

    code.pop_back();
}

void builtTree(map<char, int> result) {

    list<Node *> t;
    for (map<char, int>::iterator itr = result.begin(); itr != result.end(); ++itr) {
        Node *p = new Node;
        p->c = itr->first;
        p->a = itr->second;
        t.push_back(p);
    }
//создаем дерево
    while (t.size() != 1) {
        t.sort(Compare());
        Node *SonL = t.front();
        t.pop_front();
        Node *SonR = t.front();
        t.pop_front();
        Node *parent = new Node(SonL, SonR);
        t.push_back(parent);
    }

    Node *root = t.front();
    BuildTable(root);
    EncodeTree(root);
}

bool areEquals(vector<bool> arr_1, vector<bool> arr_2) {
    if (arr_1.size() != arr_2.size())
        return false;
    for (int i = 0; i < arr_1.size(); i++)
        if (arr_1[i] != arr_2[i])
            return false;
    return true;
}


//------------------------------------------------------------------
void Encode(IInputStream &input, IOutputStream &output) {
    table.clear();
    code.clear();
    vector<char> arr;
    map<char, int> result;
    vector<char> test;
    byte value;


    while (input.Read(value)) {
        arr.push_back(value);
        result[value]++;
        if (arr.size() == 4){
            if ((arr[0] == 'F') and (arr[1] == 'F')  and (arr[2] == 'D') and (arr[3] == '8'))
            {
                output.Write(0);
                for(char el: arr)
                    output.Write(el);
                while(input.Read(value))
                    output.Write(value);
                return;
            }
        }
    }
    builtTree(result);
    for (char e : encodeTree) {
        test.push_back(e);
    }
    test.push_back('$');

    BitsWriter bw;

    for (char i :arr) {
        for (char res: table[i]) {
            bw.WriteBit(res == 1);
        }
    }
    vector<byte> buffer = bw.GetResult();
    for (byte el:buffer) {
        test.push_back(el);
    }

    double k = double(arr.size()) / double(test.size());

    if (k < 1) {
        //читаем как есть
        output.Write(0);
        for (byte b : arr) {
            output.Write(b);
        }
    } else {
        output.Write(1);
        for (byte b : test) {
            output.Write(b);
        }

    }
}

void Decode(IInputStream &compressed, IOutputStream &original) {
    table.clear();
    code.clear();
    vector<bool> vec;
    byte value;
    compressed.Read(value);
    vector<bool> code;
    if (value == 0) {
        while (compressed.Read(value))
            original.Write(value);
        return;
    }

    compressed.Read(value);
    while (value != '$') {
        if (value == '#') {
            compressed.Read(value);
            table[value] = code;
            code.pop_back();
        }
        if (value == '*') {
            code.pop_back();
        }
        if (value == true or value == false) {
            code.push_back((bool) value);
        }
        compressed.Read(value);
    }
    vector<byte> encode;
    while (compressed.Read(value)) {
        encode.push_back(value);
    }

    vector<byte> bytes;
    for (bool el:vec) {
        bytes.push_back((char) el);
    }
    BitsReader br(std::move(encode));

    vec.clear();
    bool bit;

    while (br.ReadBit(bit)) {
        vec.push_back(bit);
        for (map<char, vector<bool>>::iterator itr = table.begin(); itr != table.end(); ++itr) {
            if (areEquals(itr->second, vec)) {
                original.Write(itr->first);
                vec.clear();
                break;
            }
        }
    }

}
//------------------------------------------------------------------


int main() {
    hmain();
    return 0;
}

