#include <iostream>
#include <cstring>
#include <algorithm>

class Str {
public:

    // default constructor
    Str() : length_(0), capacity_(DEFAULT_CAPACITY){
        raw_str_ = new char[capacity_]{};
    }

    // constructor for const char *
     Str(const char *str):length_(std::strlen(str)),capacity_(std::max(DEFAULT_CAPACITY,length_+1)){
        raw_str_ = new char[capacity_]{};
        std::strcpy(raw_str_, str);
    }

    // copy and swap
    auto operator=(Str other) -> Str& {
        other.swap(*this);
        return *this;
    }

    void swap(Str &other){
        using std::swap;
        swap(other.length_, length_);
        swap(other.capacity_, capacity_);
        swap(other.raw_str_, raw_str_);
    }

    // 省略了其他成员函数和析构函数

private:
    char* raw_str_;
    size_t length_;
    size_t capacity_;
    static const size_t DEFAULT_CAPACITY = 16;
};

int main() {
    Str str1;
    const char *a = "ssss";
    str1 = a;
    return 0;
}
