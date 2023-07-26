#include <cstddef>
#include <cstring>
#include <algorithm>
#include <iostream>

class Str{
public:
    // default constructor
    Str() : length_(0), capacity_(DEFAULT_CAPACITY){
        raw_str_ = new char[capacity_]{};
    }

    // constructor for const char *
     explicit Str(const char *str):length_(std::strlen(str)),capacity_(std::max(DEFAULT_CAPACITY,length_+1)){
        std::cout << "constructor for const char *: " << str <<  std::endl;
        raw_str_ = new char[capacity_]{};
        std::strcpy(raw_str_, str);
    }

    // copy constructor
    Str(const Str &other):length_(other.length_),capacity_(other.capacity_){
        std::cout << "copy constructor: " << other.raw_str_ << std::endl;
        raw_str_ = new char[capacity_];
        std::strcpy(raw_str_, other.raw_str_);
    }

    // move constructor
    Str(Str &&other) noexcept: raw_str_(other.raw_str_),length_(other.length_),capacity_(other.capacity_){
        std::cout << "move constructor: " << other.raw_str_ << std::endl;
        other.length_ = 0;
        other.capacity_ = 0;
        other.raw_str_ = nullptr;
    }

    auto operator=(const char *str)-> Str&{
        std::cout << "const char * assign operator" << std::endl;
        Str temp{str};
        temp.swap(*this);
        return *this;
    }

    // copy and swap
    auto operator=(Str other)-> Str&{
        std::cout << "copy and swap assign operator" << std::endl;
        other.swap(*this);
        return *this;
    }

    void swap(Str &other){
        using std::swap;
        swap(other.length_, length_);
        swap(other.capacity_, capacity_);
        swap(other.raw_str_, raw_str_);
    }

    void reserve(size_t new_cap){
        if (new_cap > capacity_){
            char *new_raw_str = new char[new_cap]{};
            std::strcpy(new_raw_str, raw_str_);
            delete[] raw_str_;
            raw_str_ = new_raw_str;
            capacity_ = new_cap;
        }
    }

    void resize(size_t new_size){
        if (new_size < length_) {
            length_ = new_size;
            raw_str_[length_] = '\0';
        } else if (new_size > length_ && new_size <= capacity_){
            for (size_t i = length_; i < new_size; ++i) {
                raw_str_[i] = '\0';
            }
            length_ = new_size;
            raw_str_[length_] = '\0';
        }else{
            reserve(new_size);
            length_ = new_size;
        }
    }

    auto c_str() -> const char* {
        return raw_str_;
    }

    auto data() ->char*{
        return raw_str_;
    }

    auto length() const -> size_t {
        return length_;
    }

    auto operator[](size_t index) -> char&{
        return raw_str_[index];
    }

    void push_back(char ch){
        if(length_ + 1 >= capacity_){
            reserve(capacity_ * 2);
        }
        raw_str_[length_] = ch;
        raw_str_[length_ + 1] = '\0';
        length_++;
    }

    void pop_back() {
        if (length_ > 0) {
            raw_str_[length_ - 1] = '\0';
            length_--;
        }
    }

private:
    char *raw_str_;
    size_t length_;
    size_t capacity_;
    static constexpr size_t DEFAULT_CAPACITY = 16;
};

int main(){
    Str sss{"init"};
    std::cout << "\n";

    sss = "xxxxx";
    std::cout << "current sss=" << sss.data() <<  "\n\n";

    Str str1{"str1"};
    sss = str1;
    std::cout << "current sss=" << sss.data() <<  "\n\n";

    Str str2{"str2"};
    sss = std::move(str2);
    std::cout << "current sss=" << sss.data() <<  std::endl;

    sss.push_back('a');
    std::cout << sss.data() << std::endl;
    sss.pop_back();
    std::cout << sss.data();
}