//
// Created by Kate Trimbach on 29/11/2019.
//
#include <vector>
typedef unsigned char byte;

struct IInputStream { ;
    bool Read(byte& value);

public:
// Возвращает false, если поток закончился
IInputStream(std::vector<byte> &data): buffer_(data), position_(0) {}

private:
    std::vector<byte> buffer_;
    int position_ = 0;
};
bool IInputStream::Read(byte& value){

    if (position_ < buffer_.size()) {
        value = buffer_[position_++];
        return true;
    } else {
        return false;
    }
}

struct IOutputStream {
    void Write(byte value);
    std::vector<byte> GetBuffer(){
        return buffer_;
    }
private:
    std::vector<byte> buffer_;
};
void IOutputStream::Write(byte value){
    buffer_.push_back(value);
}