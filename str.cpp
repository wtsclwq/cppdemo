#include <cstddef>
#include <cstring>
#include <algorithm>
#include <iostream>

class Str{
public:
    // default constructor
    Str():length_(0), capacity_(DEFAULT_CAPACITY){
        std::cout << "[default] constructor" << std::endl;
        raw_str_ = new char[capacity_]{};
    }

    // constructor for const char *
    explicit Str(const char *str){
        std::cout << "[arg] constructor for const char *" << std::endl;
        length_ = std::strlen(str);  // do not count '\0'
        capacity_ = std::max(length_ + 1, DEFAULT_CAPACITY); // need to save '\0'
        raw_str_ = new char[capacity_]{};
        std::strcpy(raw_str_, str);
    }

    // copy constructor
    Str(const  Str& other):length_(other.length_),capacity_(other.capacity_){
        std::cout << "[copy] constructor: other.raw_str_ = " << other.raw_str_ << std::endl;
        raw_str_ = new char[capacity_]{};
        std::strcpy(raw_str_, other.raw_str_);
    }

    // move constructor
    Str(Str &&other) noexcept:length_(other.length_),capacity_(other.capacity_),raw_str_(other.raw_str_){
        std::cout << "[move] constructor: other.raw_str_ = " << other.raw_str_ << std::endl;
        other.length_ = 0;
        other.capacity_ = 0;
        other.raw_str_ = nullptr;
    }

    // assign operator for const char *
    auto operator=(const char *str) -> Str&{
        std::cout << "assign operator for const char *" << std::endl;
        auto temp = Str(str);
        temp.swap(*this);
        return *this;
    }

    // assign operator for both copy and move
    auto operator=(Str other) -> Str&{
        std::cout << "copy and swap assign operator for both copy and move" << std::endl;
        other.swap(*this);
        return *this;
    }

    ~Str(){
        delete[] raw_str_;
    }

    void reserve(size_t cap){
        if(cap > capacity_){
            auto new_str = new char[capacity_]{};
            std::strcpy(new_str, raw_str_);
            delete[] raw_str_;

            capacity_ = cap;
            raw_str_ = new_str;
        }
    }

    void swap(Str &other){
        using std::swap;
        swap(other.length_, length_);
        swap(other.capacity_, capacity_);
        swap(other.raw_str_, raw_str_);
    }

    void push_back(char ch){
        if (length_ + 1 >= capacity_) {
            reserve(capacity_ * 2);
        }
        raw_str_[length_] = ch;
        raw_str_[length_ + 1] = '\0';
        length_++;
    }

    void pop_back(){
        if (length_ > 0) {
            raw_str_[length_-1] = '\0';
            length_--;
        }
    }

    auto data() -> char* {
        return raw_str_;
    }

    auto c_str() const -> const char* {
        return raw_str_;
    }

    auto operator[] (int index)-> char&{
        return raw_str_[index];
    }

    friend auto operator<<(std::ostream& os, const Str& str) -> std::ostream&{
        os << str.c_str();
        return os;
    }

private:
    char *raw_str_;
    size_t length_;
    size_t capacity_;
    static constexpr size_t DEFAULT_CAPACITY = 16;
};

int main(){
    Str sss{};
    std::cout << "\n";

    sss = "xxxxx";
    std::cout << "current sss=" << sss <<  "\n\n";

    Str str1{"str1"};
    sss = str1;
    std::cout << "current sss=" << sss <<  "\n\n";

    Str str2{"str2"};
    sss = std::move(str2);
    std::cout << "current sss=" << sss <<  std::endl;

    sss.push_back('a');
    std::cout << sss << std::endl;
    sss.pop_back();
    std::cout << sss;
}